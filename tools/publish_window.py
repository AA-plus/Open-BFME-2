#!/usr/bin/env python3
"""A cooperative publish window on master: one ref, held by one publisher.

WHY. A header-wide change runs a ~17 minute push gate; master takes a push
every ~79 s (median, 2026-09-29), and a 17-minute gap with no push happened
1.8% of the time, so such a change never lands by racing. The landing
service (tools/landing_service.py) opens a window, lands the change while
master is quiet, and closes it.

HOW. The window is the ref `refs/landing/window` on origin, pointing at a
parentless commit whose message is JSON {owner, host, purpose, opened,
expires}. Opening creates it with an expected-absent lease (or takes over an
EXPIRED one by compare-and-swap), so two publishers cannot both hold it.
Every pre-push hook asks `check` before pushing to refs/heads/master, at the
start and again after its gates: a live window held by someone else refuses
the push. The holder's own pushes carry BFME_WINDOW_TOKEN=<window sha>.

COOPERATIVE. Only hooks that contain the check respect it: a checkout older
than this file, a --no-verify push, or a push through the GitHub API ignores
the window. The check fails OPEN when origin cannot be asked (the push itself
needs origin anyway). A window is a 10-minute lease its holder renews while
it works (renew_window, compare-and-swap, keyed on the window's nonce), so a
dead holder blocks master for at most ~10 minutes; `close --force` ends one.

HOLD CAP. A window counts for at most MAX_HOLD_MINUTES from its opening, however
often it is renewed: renew_window stops extending it, and every check and
takeover treats it as expired, so a holder that keeps renewing cannot keep
master indefinitely. Gate outside the window first (landing_service pregate)
and open a new window for whatever remains.

  python3 tools/publish_window.py status       # shows minutes held against the cap
  python3 tools/publish_window.py open [--minutes 10] [--purpose TEXT]   # prints the token
  python3 tools/publish_window.py close TOKEN | --force   # --force is logged
  python3 tools/publish_window.py check        # exit 1 while someone else holds it
  python3 tools/publish_window.py push [--purpose TEXT]   # open, rebase, git push (hooks run), close
"""
import argparse
import json
import math
import os
import re
import socket
import subprocess
import sys
import time
import uuid
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REF = "refs/landing/window"
SEEN = "refs/landing-seen/window"
TOKEN_ENV = "BFME_WINDOW_TOKEN"
# A window is a SHORT lease its holder renews while it works (renew_window),
# so a crashed holder blocks master for at most this long -- never the 90
# minutes the first version used (owner's request, 2026-09-30).
LEASE_MINUTES = 10
# The longest one window may hold master from its opening, renewals included;
# it leaves room for one ~17-minute header-wide push gate.
MAX_HOLD_MINUTES = 30
FUTURE_SKEW = 300        # seconds of clock skew tolerated on a window commit


class WindowHeld(RuntimeError):
    """Someone else holds a live window."""


def _git(*args, root=None, input_text=None, timeout=60):
    cwd = Path(root or ROOT)
    env = dict(os.environ, GIT_CEILING_DIRECTORIES=str(cwd.resolve().parent))
    try:
        return subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True,
                              input=input_text, timeout=timeout, env=env)
    except subprocess.TimeoutExpired as error:
        return subprocess.CompletedProcess(error.cmd, 124, "", f"timed out after {timeout}s")


def read(remote="origin", root=None):
    """(token, info) of the window on `remote`, (None, None) when there is
    none. Raises RuntimeError when the remote cannot be asked."""
    listed = _git("ls-remote", remote, REF, root=root, timeout=60)
    if listed.returncode:
        raise RuntimeError(f"publish_window: cannot ask {remote}: {listed.stderr.strip()}")
    line = listed.stdout.strip()
    if not line:
        return None, None
    token = line.split()[0]
    if _git("cat-file", "-e", f"{token}^{{commit}}", root=root).returncode:
        got = _git("fetch", "-q", "--no-tags", remote, f"+{REF}:{SEEN}", root=root, timeout=60)
        if got.returncode:
            raise RuntimeError(f"publish_window: cannot fetch {REF}: {got.stderr.strip()}")
    body = _git("log", "-1", "--format=%ct%n%B", token, root=root)
    if body.returncode:
        # unreadable is unknown, never "no window" or "someone else's"
        raise RuntimeError(f"publish_window: cannot read {REF} at {token[:10]}: {body.stderr.strip()}")
    stamp, _, text = body.stdout.partition("\n")
    try:
        info = json.loads(text)
    except ValueError:
        info = None
    if not valid(info):
        # Metadata not in the shape we write is unknown, never "someone
        # else's" and never "no window" (review 2026-09-30): it blocks pushes
        # and takeovers, but only for one maximum lease from the ref's own
        # commit time, so a corrupt ref cannot lock the swarm out. Our writers
        # stamp the current time: a commit more than FUTURE_SKEW in the future
        # is corrupt AND expired (counting it "from now" re-extended the
        # deadline on every read: ~70 min, review 2026-09-30).
        now = int(time.time())
        try:
            made = int(stamp)
        except ValueError:
            made = 0
        if made > now + FUTURE_SKEW:
            print(f"publish_window: {REF} at {token[:10]} has unreadable metadata and a commit "
                  f"time {made - now} s in the future; treating it as expired (anyone may take "
                  f"it over; force-close: python3 tools/publish_window.py close --force)",
                  file=sys.stderr)
            made = -LEASE_MINUTES * 60
        return token, {"owner": "? (unreadable window metadata)", "invalid": True,
                       "expires": made + LEASE_MINUTES * 60,
                       "purpose": "force-close: python3 tools/publish_window.py close --force"}
    return token, info


NONCE = re.compile(r"[0-9a-f]{32}")


def _stamp(value):
    if not isinstance(value, (int, float)) or isinstance(value, bool):
        return False
    try:
        return math.isfinite(value)
    except OverflowError:          # a JSON integer past any float (10**400): corrupt, not a crash
        return False


def valid(info, now=None):
    """The metadata shape open_window() writes: a hex nonce, and finite opening
    and expiry times, the opening not in the future and the expiry within the
    hold cap of it. Anything else is unknown metadata, which blocks for at most
    one lease (read): a valid nonce with no opening, or an expiry a year out,
    held master past the cap (GPT-6.1-Sol, Open-BFME-2 port review 2026-10-11)."""
    now = time.time() if now is None else now
    if not (isinstance(info, dict) and isinstance(info.get("nonce"), str)
            and NONCE.fullmatch(info["nonce"])):
        return False
    opened, expires = info.get("opened"), info.get("expires")
    return (_stamp(opened) and _stamp(expires) and opened <= now + FUTURE_SKEW
            and expires <= opened + MAX_HOLD_MINUTES * 60 + FUTURE_SKEW)


def hold_deadline(info):
    """When the window stops counting however it is renewed (opened +
    MAX_HOLD_MINUTES), or None when its metadata records no opening."""
    opened = (info or {}).get("opened")
    return opened + MAX_HOLD_MINUTES * 60 if isinstance(opened, (int, float)) else None


def live(info, now=None):
    now = now or time.time()
    if not info or info.get("expires", 0) <= now:
        return False
    deadline = hold_deadline(info)
    return deadline is None or now < deadline


def _commit(body, root=None):
    tree = _git("mktree", input_text="", root=root).stdout.strip()
    made = _git("-c", "user.name=window", "-c", "user.email=window@localhost",
                "commit-tree", tree, "-m", json.dumps(body, sort_keys=True), root=root)
    if made.returncode:
        raise RuntimeError(made.stderr.strip())
    return made.stdout.strip()


def renew_window(nonce, minutes=LEASE_MINUTES, remote="origin", root=None):
    """Extend the window we hold by `minutes` from now: compare-and-swap on
    the current ref, and only while it still carries our nonce. Returns the
    new expiry, or None when the window is no longer ours or has reached its
    hold cap (the extension never passes hold_deadline)."""
    current, info = read(remote, root)
    if not current or (info or {}).get("nonce") != nonce:
        return None
    now = time.time()
    deadline = hold_deadline(info)
    if deadline is not None and now >= deadline:
        return None
    expires = int(now + minutes * 60)
    body = dict(info, expires=expires if deadline is None else min(expires, int(deadline)))
    new = _commit(body, root)
    pushed = _git("push", "-q", f"--force-with-lease={REF}:{current}", remote, f"+{new}:{REF}",
                  root=root, timeout=120)
    return body["expires"] if pushed.returncode == 0 else None


def open_window(minutes=LEASE_MINUTES, purpose="", owner=None, remote="origin", root=None):
    """Hold the window; returns its NONCE, which stays valid across
    renew_window() (the ref's sha does not). Raises WindowHeld."""
    token, info = read(remote, root)
    if token and live(info):
        until = min(info["expires"], hold_deadline(info) or info["expires"])
        raise WindowHeld(f"publish window held by {info.get('owner')} "
                         f"({info.get('purpose', '')}) for {(until - time.time()) / 60:.0f} more min")
    now = time.time()
    nonce = uuid.uuid4().hex
    new = _commit({"owner": owner or f"{os.environ.get('USERNAME') or os.environ.get('USER') or '?'}"
                                     f"@{socket.gethostname()}",
                   "host": socket.gethostname(), "purpose": purpose, "nonce": nonce,
                   "opened": int(now),
                   "expires": int(now + min(minutes, MAX_HOLD_MINUTES) * 60)}, root)
    lease = f"--force-with-lease={REF}:{token or ''}"
    # the push hook skips refs/landing/* (a lock marker, like refs/claims/*)
    pushed = _git("push", "-q", lease, remote, f"+{new}:{REF}", root=root, timeout=120)
    if pushed.returncode:
        token, info = read(remote, root)
        raise WindowHeld(f"publish window taken by {info and info.get('owner')} first")
    return nonce


def close_window(token=None, force=False, remote="origin", root=None):
    """Release the window whose token we hold; True if closed. Without the
    matching token nothing is closed unless `force` is explicit (review
    2026-09-30: a rival's tokenless close deleted a live window). A forced
    close is logged to stderr and to <git common dir>/bfme-window-forced.log.
    The delete is a compare-and-swap on the token read here."""
    current, info = read(remote, root)
    if not current:
        return False
    ours = bool(token) and token in (current, (info or {}).get("nonce"))
    if not ours and not force:
        return False
    if not ours:
        line = (f"{time.strftime('%Y-%m-%dT%H:%M:%S')} forced close of {current} held by "
                f"{(info or {}).get('owner')} ({(info or {}).get('purpose', '')}) "
                f"by {os.environ.get('USERNAME') or os.environ.get('USER') or '?'}@{socket.gethostname()}")
        print(f"publish_window: {line}", file=sys.stderr)
        common = _git("rev-parse", "--git-common-dir", root=root).stdout.strip()
        if common:
            log = Path(common) if Path(common).is_absolute() else Path(root or ROOT) / common
            try:
                with (log / "bfme-window-forced.log").open("a", encoding="utf-8") as handle:
                    handle.write(line + "\n")
            except OSError:
                pass
    pushed = _git("push", "-q", f"--force-with-lease={REF}:{current}", remote,
                  f":{REF}", root=root, timeout=120)
    return pushed.returncode == 0


def check(remote="origin", root=None):
    """(allowed, message) for a push to master right now."""
    try:
        token, info = read(remote, root)
    except RuntimeError as error:
        return True, f"{error}; not checking the publish window"
    if token and info and info.get("expires", 0) > time.time() and not live(info):
        return True, (f"the publish window held by {info.get('owner')} passed its "
                      f"{MAX_HOLD_MINUTES}-minute hold cap; not honoured")
    if not token or not live(info):
        return True, ""
    if os.environ.get(TOKEN_ENV) in (token, info.get("nonce")) and os.environ.get(TOKEN_ENV):
        return True, "this push holds the publish window"
    left = (info.get("expires", 0) - time.time()) / 60
    return False, (f"master is in a publish window held by {info.get('owner')} "
                   f"({info.get('purpose', '')}), {left:.0f} min left; retry after it closes")


RENEW_RETRY_SECONDS = 30   # after a renewal push that failed while the window was still ours


def _renew_until(nonce, stop, lost, remote, root):
    """Renew our window every third of a lease until `stop`. A renewal that
    fails while the window is still ours and live is retried soon (a transport
    hiccup); confirmed loss -- another nonce, no window, or the hold cap --
    sets `lost` and ends renewal (GPT-6.1-Sol, port review 2026-10-11)."""
    every = LEASE_MINUTES * 60 / 3
    wait = every
    while not stop.wait(wait):
        try:
            if renew_window(nonce, LEASE_MINUTES, remote=remote, root=root) is not None:
                wait = every
                continue
            _, info = read(remote, root)
        except RuntimeError:
            wait = RENEW_RETRY_SECONDS
            continue
        if (info or {}).get("nonce") == nonce and live(info):
            wait = RENEW_RETRY_SECONDS
            continue
        lost.set()
        return


def _wait_seconds(remote, root):
    """Seconds until a held window ends (lease or hold cap), within 30 s..5 min."""
    try:
        _, info = read(remote, root)
    except RuntimeError:
        return 60
    until = min((info or {}).get("expires", 0), hold_deadline(info) or float("inf"))
    return min(max(until - time.time() + 5, 30), 300)


def _close_confirmed(nonce, remote, root, attempts=5):
    """Close our window and confirm it is gone, or that a VALID window with
    another nonce replaced it (as landing_service does); unreadable metadata
    confirms nothing. True when confirmed, else it names the commands."""
    for attempt in range(attempts):
        try:
            if close_window(nonce, remote=remote, root=root):
                return True
            token, info = read(remote, root)
            if not token or (valid(info) and info.get("nonce") != nonce):
                return True
        except RuntimeError:
            pass
        time.sleep(min(2 ** attempt, 10))
    print(f"publish_window: the publish window this push opened is still open; it lapses within "
          f"{LEASE_MINUTES} min, or close it now: python3 tools/publish_window.py close {nonce} --remote {remote} "
          f"(if its metadata is unreadable: close --force --remote {remote})", file=sys.stderr)
    return False


def _destination(remote, root):
    """The one repository the configured remote `remote` names for both reading
    and pushing (`git remote get-url` expands insteadOf and pushInsteadOf), or
    None for a URL given directly, a remote whose fetch and push URLs differ, or
    one that pushes to several: the window, the race check and the push must
    all see the same repository (GPT-6.1-Sol, port review rounds 1-2)."""
    fetch = _git("remote", "get-url", remote, root=root)
    if fetch.returncode:
        return None                          # not a configured remote
    pushes = [url.strip() for url in
              _git("remote", "get-url", "--all", "--push", remote, root=root).stdout.splitlines() if url.strip()]
    return remote if pushes == [fetch.stdout.strip()] else None


def _stop_tree(process):
    """End a push and everything its hooks started, and reap it: the window
    must not close while a push it protected can still land (an interrupted
    publisher left git and its hook running; GPT-6.1-Sol, port review round 2)."""
    if process.poll() is not None:
        return
    if os.name == "nt":
        subprocess.run(["taskkill", "/PID", str(process.pid), "/T", "/F"], capture_output=True)
    else:
        import signal
        try:
            os.killpg(process.pid, signal.SIGTERM)
            process.wait(timeout=30)
        except (ProcessLookupError, subprocess.TimeoutExpired):
            try:
                os.killpg(process.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
    process.wait()


# A push git refused because the branch moved under it, never because a hook
# refused it: only these are retried (GPT-6.1-Sol, port review 2026-10-11).
RACE = re.compile(r"! \[rejected\].*\((?:fetch first|non-fast-forward)\)"
                  r"|! \[remote rejected\].*\((?:incorrect old value provided|cannot lock ref[^)]*)\)"
                  r"|PUSH RACE")


def _rebase_in_progress(root):
    for name in ("rebase-merge", "rebase-apply"):
        path = _git("rev-parse", "--git-path", name, root=root).stdout.strip()
        if path and (Path(root or ROOT) / path).exists():
            return True
    return False


def push(purpose="", remote="origin", branch="master", wait_minutes=60, root=None):
    """Publish HEAD to `branch` under the window: open it (waiting while someone
    else holds it), rebase onto the remote branch, run the ordinary `git push`
    (every hook runs; its window check passes on our token) while a thread
    renews the lease, and close the window, confirmed, whatever happens. Only
    a push git rejected because the branch moved under it is retried; a hook's
    refusal is returned as is. 9: the rebase needs a person (nothing pushed);
    8: refused before anything ran (a rebase already in progress, or `remote`
    is not one configured repository for both fetch and push). An
    interruption ends the push and its hooks, and leaves the window to lapse
    (the remote may still apply what it already received).

    Best effort by design, as the window itself: a gate that outlasts the
    MAX_HOLD_MINUTES cap finishes without the window, where another push may
    win the race and this one retries -- the cap is what keeps a stuck holder
    from blocking master. The window never decides what is verified: every
    hook runs on every push either way.

    Open-BFME-2 measured why (2026-10-11): a push whose gate judges every
    source takes 10+ minutes while master takes a push every few minutes,
    so such a push lost its race again and again; GitGut's took an hour."""
    import threading
    cwd = Path(root or ROOT)
    if _rebase_in_progress(root):
        print("publish_window: a rebase is in progress here; finish or abort it first (nothing done)",
              file=sys.stderr)
        return 8
    if _destination(remote, root) is None:
        print(f"publish_window: push needs a configured remote whose fetch and push URLs are one "
              f"repository; {remote} is not (nothing done)", file=sys.stderr)
        return 8
    deadline = time.time() + wait_minutes * 60
    while True:
        try:
            nonce = open_window(LEASE_MINUTES, purpose, remote=remote, root=root)
        except WindowHeld as held:
            if time.time() >= deadline:
                print(f"publish_window: {held}; gave up after {wait_minutes:g} min", file=sys.stderr)
                return 1
            pause = _wait_seconds(remote, root)
            print(f"publish_window: {held}; waiting {pause:.0f} s", file=sys.stderr, flush=True)
            time.sleep(pause)
            continue
        print(f"publish_window: window open ({purpose or 'push'})", file=sys.stderr, flush=True)
        stop, lost = threading.Event(), threading.Event()
        renewer = threading.Thread(target=_renew_until, args=(nonce, stop, lost, remote, root), daemon=True)
        renewer.start()
        errors, interrupted = [], False
        try:
            fetched = _git("fetch", "-q", remote, branch, root=root, timeout=600)
            if fetched.returncode:
                print(f"publish_window: cannot fetch {remote} {branch}: {fetched.stderr.strip()}", file=sys.stderr)
                return 1
            base = _git("rev-parse", "FETCH_HEAD", root=root).stdout.strip()
            rebased = _git("rebase", base, root=root, timeout=600)
            if rebased.returncode:
                if _rebase_in_progress(root):          # ours: none was in progress before
                    _git("rebase", "--abort", root=root)
                print(f"publish_window: rebasing onto {remote}/{branch} needs a person (nothing pushed):\n"
                      f"{rebased.stdout}{rebased.stderr}", file=sys.stderr)
                return 9
            # Its own process group, so an interruption ends the whole push before
            # the window closes (_stop_tree).
            group = ({"creationflags": subprocess.CREATE_NEW_PROCESS_GROUP} if os.name == "nt"
                     else {"start_new_session": True})
            pushing = subprocess.Popen(["git", "push", remote, f"HEAD:refs/heads/{branch}"], cwd=cwd,
                                       env=dict(os.environ, **{TOKEN_ENV: nonce}), stderr=subprocess.PIPE,
                                       text=True, encoding="utf-8", errors="replace", bufsize=1, **group)
            try:
                for line in pushing.stderr:      # the hooks' output streams as it comes
                    sys.stderr.write(line)
                    errors.append(line)
                code = pushing.wait()
            except BaseException:
                interrupted = True
                _stop_tree(pushing)
                raise
        finally:
            stop.set()
            renewer.join(timeout=200)            # a renewal in flight finishes before the close
            if interrupted:
                # Killing the local push does not stop a receive the remote already
                # has under way, so the outcome is unknown: leave the window to lapse
                # instead of closing it (GPT-6.1-Sol, port review round 3).
                print(f"publish_window: interrupted mid-push; the remote may still apply it, so the window "
                      f"lapses by itself within {LEASE_MINUTES} min. Once {remote}/{branch} shows the outcome: "
                      f"python3 tools/publish_window.py close {nonce} --remote {remote}", file=sys.stderr)
            else:
                _close_confirmed(nonce, remote, root)
        if lost.is_set():
            print("publish_window: the window lapsed during the push (hold cap or lost lease)", file=sys.stderr)
        if code == 0:
            return 0
        if not RACE.search("".join(errors)) or time.time() >= deadline:
            return code                        # the hook refused it: its verdict stands
        print(f"publish_window: {remote}/{branch} moved during the push; trying again", file=sys.stderr)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("action", choices=["status", "open", "close", "check", "push"])
    ap.add_argument("token", nargs="?")
    ap.add_argument("--minutes", type=float, default=LEASE_MINUTES)
    ap.add_argument("--purpose", default="")
    ap.add_argument("--remote", default="origin")
    ap.add_argument("--branch", default="master", help="push: the branch to publish HEAD to")
    ap.add_argument("--wait", type=float, default=60, help="push: minutes to keep waiting and retrying")
    ap.add_argument("--force", action="store_true")
    args = ap.parse_args(argv)
    if args.action == "push":
        return push(args.purpose, args.remote, args.branch, args.wait)
    if args.action == "check":
        allowed, message = check(args.remote)
        if message:
            print(f"publish_window: {message}", file=sys.stderr)
        return 0 if allowed else 1
    if args.action == "status":
        token, info = read(args.remote)
        held = (f" held {(time.time() - info['opened']) / 60:.0f}/{MAX_HOLD_MINUTES} min"
                if token and hold_deadline(info) is not None else "")
        print("no window" if not token else
              f"{token[:10]} {'LIVE' if live(info) else 'expired'}{held} {json.dumps(info, sort_keys=True)}")
        return 0
    if args.action == "open":
        try:
            print(open_window(args.minutes, args.purpose, remote=args.remote))
        except WindowHeld as error:
            print(f"publish_window: {error}", file=sys.stderr)
            return 1
        return 0
    return 0 if close_window(args.token, args.force, args.remote) else 1


if __name__ == "__main__":
    sys.exit(main())
