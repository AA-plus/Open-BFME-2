"""The cooperative publish window (tools/publish_window.py), ported from
Open-BFME-1, and `push`, which publishes through it."""
import os
import shutil
import stat
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
REPO = TOOLS.parent
sys.path.insert(0, str(TOOLS))

import publish_window as pw  # noqa: E402


def _git(cwd, *args):
    return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True,
                          text=True).stdout.strip()


@pytest.fixture
def clones(tmp_path, monkeypatch):
    monkeypatch.delenv(pw.TOKEN_ENV, raising=False)
    origin = tmp_path / "origin.git"
    _git(tmp_path, "init", "-q", "--bare", str(origin))
    out = {}
    for name in ("service", "seat"):
        clone = tmp_path / name
        _git(tmp_path, "init", "-q", str(clone))
        _git(clone, "remote", "add", "origin", str(origin))
        _git(clone, "config", "user.name", name)
        _git(clone, "config", "user.email", f"{name}@example.com")
        _git(clone, "config", "core.hooksPath", "no-hooks")
        _git(clone, "config", "core.autocrlf", "false")
        assert Path(_git(clone, "remote", "get-url", "origin")) == origin   # never the real origin
        out[name] = clone
    out["origin"] = origin
    return out


def test_one_holder_at_a_time_and_its_own_pushes_pass(clones, monkeypatch):
    token = pw.open_window(30, purpose="header stack", owner="svc", root=clones["service"])
    with pytest.raises(pw.WindowHeld):
        pw.open_window(30, owner="rival", root=clones["seat"])
    allowed, why = pw.check(root=clones["seat"])
    assert not allowed and "svc" in why and "header stack" in why
    monkeypatch.setenv(pw.TOKEN_ENV, token)
    assert pw.check(root=clones["seat"])[0]
    monkeypatch.delenv(pw.TOKEN_ENV)
    assert not pw.close_window("not-the-token", root=clones["seat"])
    assert pw.close_window(token, root=clones["service"])
    assert pw.check(root=clones["seat"]) == (True, "")


def test_an_expired_window_is_taken_over_and_blocks_nothing(clones):
    pw.open_window(-1, owner="crashed", root=clones["service"])
    assert pw.check(root=clones["seat"]) == (True, "")
    token = pw.open_window(30, owner="next", root=clones["seat"])
    assert pw.read(root=clones["service"])[1]["nonce"] == token


def test_an_unreachable_origin_does_not_block_pushes(clones):
    _git(clones["seat"], "remote", "set-url", "origin", str(clones["origin"].parent / "gone.git"))
    allowed, why = pw.check(root=clones["seat"])
    assert allowed and "not checking" in why


def test_the_pre_push_hook_refuses_master_while_someone_else_holds_the_window(clones):
    seat = clones["seat"]
    (seat / "tools").mkdir()
    shutil.copy(TOOLS / "publish_window.py", seat / "tools" / "publish_window.py")
    # the hook's ledger and spelling guards run before the window check; this seat has no ledgers
    (seat / "tools" / "ledger_guard.py").write_text("raise SystemExit(0)\n")
    (seat / "tools" / "check_case_collisions.py").write_text("raise SystemExit(0)\n")
    token = pw.open_window(30, purpose="header stack", owner="svc", root=clones["service"])
    hook = REPO / ".githooks" / "pre-push"
    line = "refs/heads/master " + "1" * 40 + " refs/heads/master " + "0" * 40 + "\n"

    def run(env_token=None, refs=line):
        env = {k: v for k, v in os.environ.items() if k != pw.TOKEN_ENV}
        if env_token:
            env[pw.TOKEN_ENV] = env_token
        return subprocess.run(["bash", str(hook), "origin", str(clones["origin"])], cwd=seat,
                              env=env, input=refs, capture_output=True, text=True)
    blocked = run()
    assert blocked.returncode != 0 and "publish window" in blocked.stderr and "svc" in blocked.stderr
    held = run(token)               # the holder gets past the window (and fails later, on the fake sha)
    assert "this push holds the publish window" in held.stderr
    assert "FAILED: publish window" not in held.stderr and "ledger integrity" in held.stderr
    other_ref = run(refs=line.replace("refs/heads/master", "refs/heads/topic"))
    assert "publish window" not in other_ref.stderr
    window_ref = run(refs=line.replace("refs/heads/master", pw.REF))
    assert window_ref.returncode == 0          # the lock marker itself is not gated


def test_closing_someone_elses_window_needs_the_token_or_an_explicit_force(clones):
    token = pw.open_window(30, owner="holder", purpose="stack", root=clones["service"])
    assert not pw.close_window(root=clones["seat"])                     # tokenless: refused
    assert not pw.close_window("wrong", root=clones["seat"])
    assert pw.read(root=clones["service"])[1]["nonce"] == token
    assert pw.close_window(force=True, root=clones["seat"])             # explicit, logged
    log = Path(_git(clones["seat"], "rev-parse", "--absolute-git-dir")) / "bfme-window-forced.log"
    assert "forced close" in log.read_text() and "holder" in log.read_text()
    assert pw.read(root=clones["service"]) == (None, None)


def test_a_window_is_a_short_lease_its_holder_renews(clones, monkeypatch):
    assert pw.LEASE_MINUTES <= 10
    nonce = pw.open_window(owner="drainer", root=clones["service"])
    token, info = pw.read(root=clones["service"])
    assert info["expires"] - info["opened"] <= pw.LEASE_MINUTES * 60
    expires = pw.renew_window(nonce, 5, root=clones["service"])
    new_token, info = pw.read(root=clones["service"])
    assert expires and new_token != token and info["nonce"] == nonce
    monkeypatch.setenv(pw.TOKEN_ENV, nonce)                  # the holder's pushes still pass
    assert pw.check(root=clones["seat"])[0]
    monkeypatch.delenv(pw.TOKEN_ENV)
    assert pw.renew_window("not-ours", 5, root=clones["seat"]) is None
    assert pw.close_window(nonce, root=clones["service"])


def test_a_dead_holder_blocks_only_until_its_short_lease_expires(clones):
    pw.open_window(-0.01, owner="crashed drainer", root=clones["service"])   # never renewed
    assert pw.check(root=clones["seat"]) == (True, "")


def _later(monkeypatch, minutes):
    real = pw.time.time
    monkeypatch.setattr(pw.time, "time", lambda: real() + minutes * 60)


def test_renewals_never_carry_a_window_past_its_hold_cap(clones, monkeypatch):
    nonce = pw.open_window(owner="drainer", root=clones["service"])
    opened = pw.read(root=clones["service"])[1]["opened"]
    _later(monkeypatch, pw.MAX_HOLD_MINUTES - 2)
    expires = pw.renew_window(nonce, pw.LEASE_MINUTES, root=clones["service"])
    assert expires == opened + pw.MAX_HOLD_MINUTES * 60      # clipped to the cap
    _later(monkeypatch, pw.MAX_HOLD_MINUTES + 1)
    assert pw.renew_window(nonce, pw.LEASE_MINUTES, root=clones["service"]) is None


def test_a_window_past_its_hold_cap_blocks_nothing_and_is_taken_over(clones, monkeypatch):
    pw.open_window(owner="hog", root=clones["service"])
    info = pw.read(root=clones["service"])[1]
    opened = info["opened"] - (pw.MAX_HOLD_MINUTES + 1) * 60                     # renewed all along,
    body = dict(info, opened=opened, expires=opened + pw.MAX_HOLD_MINUTES * 60 + 200)   # its lease past the cap
    new = pw._commit(body, clones["service"])
    _git(clones["service"], "push", "-q", "origin", f"+{new}:{pw.REF}")
    allowed, why = pw.check(root=clones["seat"])
    assert allowed and "hog" in why and "hold cap" in why
    token = pw.open_window(owner="next", root=clones["seat"])
    assert pw.read(root=clones["service"])[1]["nonce"] == token


def test_open_caps_its_lease_and_status_shows_the_time_held(clones, monkeypatch, capsys):
    pw.open_window(10 * pw.MAX_HOLD_MINUTES, owner="svc", root=clones["service"])
    info = pw.read(root=clones["service"])[1]
    assert info["expires"] - info["opened"] <= pw.MAX_HOLD_MINUTES * 60
    monkeypatch.setattr(pw, "ROOT", clones["seat"])          # status reads the test origin
    assert pw.main(["status"]) == 0
    assert f"LIVE held 0/{pw.MAX_HOLD_MINUTES} min" in capsys.readouterr().out


# ---- push: publish through the window (Open-BFME-2, 2026-10-11) ----

def _commit_file(clone, name, text, message):
    (clone / name).write_text(text)
    _git(clone, "add", name)
    _git(clone, "commit", "-qm", message)


def _seeded(clones):
    """origin/master holds one commit; the seat works on a branch from it."""
    _commit_file(clones["service"], "a.txt", "a\n", "base")
    _git(clones["service"], "push", "-q", "origin", "HEAD:refs/heads/master")
    _git(clones["seat"], "fetch", "-q", "origin", "master")
    _git(clones["seat"], "checkout", "-q", "-B", "work", "FETCH_HEAD")
    _commit_file(clones["seat"], "b.txt", "b\n", "seat work")
    return clones["seat"]


def _master_log(clones):
    return _git(clones["origin"], "log", "--format=%s", "master").splitlines()


def _hook(clone, body):
    """A pre-push hook for this clone only (the fixture's hooksPath holds none)."""
    hooks = clone / "test-hooks"
    hooks.mkdir(exist_ok=True)
    script = hooks / "pre-push"
    # As the real pre-push: read the refs git writes (an unread pipe can stall git),
    # and pass the window's own lock-marker pushes (open, renew, close) untouched.
    script.write_text('#!/bin/sh\nrefs=$(cat)\ncase "$refs" in *refs/landing/*) exit 0 ;; esac\n' + body,
                      newline="\n")
    script.chmod(script.stat().st_mode | stat.S_IEXEC)
    _git(clone, "config", "core.hooksPath", str(hooks).replace("\\", "/"))


def test_push_rebases_publishes_under_the_window_and_closes_it(clones):
    seat = _seeded(clones)
    _commit_file(clones["service"], "c.txt", "c\n", "meanwhile")      # master moved since the seat branched
    _git(clones["service"], "push", "-q", "origin", "HEAD:refs/heads/master")
    _hook(seat, f'git ls-remote origin {pw.REF} > window-during-push.txt\n'
                f'env | grep -q "^{pw.TOKEN_ENV}=" && echo token >> window-during-push.txt\nexit 0\n')
    assert pw.push("seat work", root=seat) == 0
    assert _master_log(clones) == ["seat work", "meanwhile", "base"]
    during = (seat / "window-during-push.txt").read_text()
    assert pw.REF in during and "token" in during                     # held, and the hook saw our token
    assert pw.read(root=seat) == (None, None)                         # closed afterwards


def test_push_waits_while_someone_else_holds_the_window(clones, monkeypatch):
    seat = _seeded(clones)
    rival = pw.open_window(owner="rival", purpose="long gate", root=clones["service"])
    waits = []

    def sleep(seconds):
        waits.append(seconds)
        pw.close_window(rival, root=clones["service"])                # the rival finishes
    monkeypatch.setattr(pw.time, "sleep", sleep)
    assert pw.push("seat work", root=seat) == 0
    assert len(waits) == 1 and 30 <= waits[0] <= 300
    assert _master_log(clones)[0] == "seat work"


def test_push_gives_up_after_its_wait(clones, monkeypatch):
    seat = _seeded(clones)
    pw.open_window(owner="rival", root=clones["service"])
    monkeypatch.setattr(pw.time, "sleep", lambda seconds: None)
    assert pw.push("seat work", root=seat, wait_minutes=0) == 1
    assert _master_log(clones) == ["base"]


def test_a_rebase_conflict_pushes_nothing_and_leaves_no_rebase_behind(clones):
    seat = _seeded(clones)
    _commit_file(seat, "a.txt", "seat\n", "seat edits a")
    _commit_file(clones["service"], "a.txt", "service\n", "service edits a")
    _git(clones["service"], "push", "-q", "origin", "HEAD:refs/heads/master")
    assert pw.push("seat work", root=seat) == 9
    assert _master_log(clones) == ["service edits a", "base"]
    git_dir = Path(_git(seat, "rev-parse", "--absolute-git-dir"))
    assert not (git_dir / "rebase-merge").exists() and not (git_dir / "rebase-apply").exists()
    assert pw.read(root=seat) == (None, None)


def test_a_hook_refusal_is_returned_not_retried(clones):
    seat = _seeded(clones)
    _hook(seat, 'echo attempt >> attempts.txt\necho "PRE-PUSH FAILED: byte gate" >&2\nexit 1\n')
    assert pw.push("seat work", root=seat) != 0
    assert (seat / "attempts.txt").read_text().splitlines() == ["attempt"]
    assert _master_log(clones) == ["base"] and pw.read(root=seat) == (None, None)


def test_a_hook_refusal_is_not_retried_even_when_master_moved_meanwhile(clones):
    """Port review: a refusal while another checkout advanced master was rebased
    and re-run; only git's own race rejection is retried."""
    seat = _seeded(clones)
    service = str(clones["service"]).replace("\\", "/")
    _hook(seat, 'echo attempt >> attempts.txt\n'
                '(unset GIT_DIR GIT_WORK_TREE GIT_INDEX_FILE GIT_PREFIX\n'
                f' cd "{service}" && git commit -q --allow-empty -m mover && git push -q origin HEAD:refs/heads/master)\n'
                'echo "PRE-PUSH FAILED: byte gate" >&2\nexit 1\n')
    assert pw.push("seat work", root=seat) != 0
    assert (seat / "attempts.txt").read_text().splitlines() == ["attempt"]


def test_push_refuses_a_rebase_already_in_progress_and_keeps_its_resolution(clones):
    """Port review BLOCKER: a paused conflicted rebase was aborted, its staged
    resolution lost."""
    seat = _seeded(clones)
    _commit_file(seat, "a.txt", "seat\n", "seat edits a")
    _commit_file(clones["service"], "a.txt", "service\n", "service edits a")
    _git(clones["service"], "push", "-q", "origin", "HEAD:refs/heads/master")
    _git(seat, "fetch", "-q", "origin", "master")
    assert subprocess.run(["git", "rebase", "FETCH_HEAD"], cwd=seat, capture_output=True).returncode
    (seat / "a.txt").write_text("resolved\n")
    _git(seat, "add", "a.txt")
    assert pw.push("seat work", root=seat) == 8
    git_dir = Path(_git(seat, "rev-parse", "--absolute-git-dir"))
    assert (git_dir / "rebase-merge").exists() or (git_dir / "rebase-apply").exists()
    assert _git(seat, "diff", "--cached", "--", "a.txt") and (seat / "a.txt").read_text() == "resolved\n"
    assert pw.read(root=seat) == (None, None)                         # no window was opened


def test_push_refuses_a_remote_whose_push_url_differs(clones, tmp_path):
    seat = _seeded(clones)
    elsewhere = tmp_path / "elsewhere.git"
    _git(tmp_path, "init", "-q", "--bare", str(elsewhere))
    _git(seat, "remote", "set-url", "--push", "origin", str(elsewhere))
    assert pw.push("seat work", root=seat) == 8
    assert pw.read(root=seat) == (None, None)


def test_a_window_that_will_not_close_is_reported_with_its_close_command(clones, monkeypatch, capsys):
    seat = _seeded(clones)
    monkeypatch.setattr(pw, "close_window", lambda *a, **k: False)
    monkeypatch.setattr(pw.time, "sleep", lambda seconds: None)
    assert pw.push("seat work", root=seat) == 0                        # the work did land
    err = capsys.readouterr().err
    nonce = pw.read(root=seat)[1]["nonce"]
    assert "still open" in err and f"python3 tools/publish_window.py close {nonce}" in err


def test_renewal_retries_a_failed_push_and_stops_only_on_confirmed_loss(monkeypatch):
    import threading
    monkeypatch.setattr(pw, "LEASE_MINUTES", 0.0015)                  # renew every ~0.03 s
    monkeypatch.setattr(pw, "RENEW_RETRY_SECONDS", 0.01)
    calls, owner = [], {"nonce": "a" * 32}
    monkeypatch.setattr(pw, "renew_window", lambda *a, **k: calls.append(1) and None)   # every push fails
    now = time_now = pw.time.time()
    monkeypatch.setattr(pw, "read", lambda *a, **k: ("sha", dict(owner, opened=time_now, expires=time_now + 600)))
    stop, lost = threading.Event(), threading.Event()
    worker = threading.Thread(target=pw._renew_until, args=("a" * 32, stop, lost, "origin", None), daemon=True)
    worker.start()
    pw.time.sleep(0.3)
    assert len(calls) >= 3 and not lost.is_set()                     # still ours: retried, not abandoned
    owner["nonce"] = "b" * 32                                          # now someone else's
    worker.join(timeout=2)
    assert lost.is_set() and not worker.is_alive()
    stop.set()
    assert now


def test_metadata_without_a_bounded_opening_blocks_one_lease_at_most(clones, monkeypatch):
    """Port review: a valid nonce with no opening, or an expiry a year out, held
    master past the hold cap."""
    now = pw.time.time()
    good = {"nonce": "c" * 32, "opened": now, "expires": now + 600}
    assert pw.valid(good)
    for bad in ({"nonce": "c" * 32, "expires": now + 600},                          # no opening
                dict(good, expires=now + 365 * 86400),                              # past the cap
                dict(good, opened=float("nan")), dict(good, expires=float("inf")),
                dict(good, opened=True), dict(good, opened=now + 3600)):            # bool, future
        assert not pw.valid(bad), bad
    body = {"nonce": "c" * 32, "owner": "hog", "expires": int(now + 365 * 86400)}
    _git(clones["service"], "push", "-q", "origin", f"+{pw._commit(body, clones['service'])}:{pw.REF}")
    assert not pw.check(root=clones["seat"])[0]                        # unknown: blocks, for one lease
    _later(monkeypatch, pw.LEASE_MINUTES + 1)
    assert pw.check(root=clones["seat"])[0]


def test_a_push_that_loses_its_race_rebases_and_tries_again(clones):
    """A checkout whose hook predates the window can still push meanwhile; the
    push then fails on a moved master, and `push` rebases and tries again."""
    seat = _seeded(clones)
    service = str(clones["service"]).replace("\\", "/")
    _hook(seat, 'if [ ! -f raced.txt ]; then\n'
                '    touch raced.txt\n'
                '    (unset GIT_DIR GIT_WORK_TREE GIT_INDEX_FILE GIT_PREFIX\n'
                f'     cd "{service}" && git commit -q --allow-empty -m racer\\\n'
                '         && git push -q origin HEAD:refs/heads/master)\n'
                'fi\nexit 0\n')
    assert pw.push("seat work", root=seat) == 0
    assert _master_log(clones) == ["seat work", "racer", "base"]


# ---- port review round 2 (GPT-6.1-Sol, 2026-10-11) ----

class _InterruptOn:
    """stderr that raises KeyboardInterrupt when a line carrying `marker` arrives."""

    def __init__(self, real, marker):
        self.real, self.marker = real, marker

    def write(self, text):
        if self.marker in text:
            raise KeyboardInterrupt
        return self.real.write(text)

    def flush(self):
        self.real.flush()


def test_an_interrupted_push_ends_git_and_its_hook_and_leaves_the_window_to_lapse(clones, monkeypatch, capsys):
    """Rounds 2-3: an interrupted publisher closed its window while git and its
    hook kept running (round 2); and killing local git cannot stop a receive the
    remote already has under way (round 3). The push and its hooks are ended, and
    the window is left to lapse instead of closed."""
    seat = _seeded(clones)
    _hook(seat, 'echo hook-started >&2\nsleep 8\nexit 0\n')
    monkeypatch.setattr(sys, "stderr", _InterruptOn(sys.stderr, "hook-started"))
    with pytest.raises(KeyboardInterrupt):
        pw.push("seat work", root=seat)
    monkeypatch.undo()
    token, info = pw.read(root=seat)
    assert token and pw.live(info)                                    # left open, to lapse within a lease
    assert f"close {info['nonce']} --remote origin" in capsys.readouterr().err
    pw.time.sleep(10)                                                 # the local hook was ended: nothing lands
    assert _master_log(clones) == ["base"]


def test_push_needs_a_configured_remote_not_a_url(clones):
    """Round 2: a URL given directly skipped the destination check (pushInsteadOf
    could send the push elsewhere than the window and the race check read)."""
    seat = _seeded(clones)
    assert pw.push("seat work", remote=str(clones["origin"]), root=seat) == 8
    assert _master_log(clones) == ["base"]


def test_a_remote_whose_path_has_spaces_is_one_destination(clones, tmp_path):
    seat = _seeded(clones)
    spaced = tmp_path / "with space" / "origin.git"
    spaced.parent.mkdir()
    _git(tmp_path, "init", "-q", "--bare", str(spaced))
    _git(seat, "remote", "add", "spaced", str(spaced))
    _git(seat, "push", "-q", "spaced", "HEAD~1:refs/heads/master")
    assert pw.push("seat work", remote="spaced", root=seat) == 0
    assert _git(spaced, "log", "--format=%s", "master").splitlines() == ["seat work", "base"]


def test_unreadable_metadata_never_confirms_a_close(clones, monkeypatch, capsys):
    """Round 2: corrupt metadata read as another owner's window, so a window
    still open was reported closed."""
    seat = clones["seat"]
    nonce = pw.open_window(owner="seat", root=seat)
    corrupt = pw._commit({"owner": "?"}, seat)                         # no nonce, no times
    _git(seat, "push", "-q", "origin", f"+{corrupt}:{pw.REF}")
    monkeypatch.setattr(pw.time, "sleep", lambda seconds: None)
    assert pw._close_confirmed(nonce, "origin", seat, attempts=2) is False
    err = capsys.readouterr().err
    assert f"close {nonce} --remote origin" in err and "close --force --remote origin" in err


def test_a_huge_integer_in_metadata_is_corrupt_not_a_crash(clones, monkeypatch):
    now = pw.time.time()
    assert not pw.valid({"nonce": "d" * 32, "opened": 10 ** 400, "expires": now + 600})
    assert not pw.valid({"nonce": "d" * 32, "opened": now, "expires": 10 ** 400})
    body = {"nonce": "d" * 32, "owner": "big", "opened": 10 ** 400, "expires": 10 ** 400}
    _git(clones["service"], "push", "-q", "origin", f"+{pw._commit(body, clones['service'])}:{pw.REF}")
    assert not pw.check(root=clones["seat"])[0]                        # unknown: blocks, for one lease
    _later(monkeypatch, pw.LEASE_MINUTES + 1)
    assert pw.check(root=clones["seat"])[0]
