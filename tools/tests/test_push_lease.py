"""The master push window (tools/push_lease.py): one full-gate pusher at a time,
everyone else waits its turn, and nothing ever blocks a push for good.

Two hosts against a local bare origin, as in test_claims.py: no test reaches a
network or this checkout's origin.
"""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import claims  # noqa: E402
import push_lease  # noqa: E402


def _git(cwd, *args):
    return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True).stdout


@pytest.fixture
def hosts(tmp_path, monkeypatch):
    origin = tmp_path / "origin.git"
    _git(tmp_path, "init", "-q", "--bare", str(origin))
    clones = {}
    for name in ("a", "b"):
        clone = tmp_path / name
        _git(tmp_path, "init", "-q", str(clone))
        _git(clone, "remote", "add", "origin", str(origin))
        _git(clone, "config", "user.name", name)
        _git(clone, "config", "user.email", f"{name}@example.com")
        clones[name] = clone
    monkeypatch.delenv("BFME_RUN_ID", raising=False)
    monkeypatch.setattr(claims, "NS", "refs/claims/")
    monkeypatch.setattr(claims, "REMOTE", "origin")
    monkeypatch.setattr(push_lease.time, "sleep", lambda s: None)

    def act(name):
        monkeypatch.setattr(claims, "ROOT", clones[name])
        monkeypatch.setenv("BFME_CLAIM_OWNER", name)
        claims.active.cache_clear()
        claims.mirrored.cache_clear()
        assert Path(claims._git("remote", "get-url", "origin").stdout.strip()) == origin
        return clones[name]
    return act


def quiet(*args, **kwargs):
    pass


def test_lease_keys_are_validated():
    assert claims.key_of("lease:master") == "lease/master"
    assert claims.key_of("lease/master") == "lease/master"
    assert claims.ref_of("lease/master") == claims.NS + "lease/master"
    for bad in ("lease:", "lease:Master", "lease:a/b", "lease:x y", "lease/../x"):
        with pytest.raises(ValueError):
            claims.key_of(bad)


def test_one_full_gate_pusher_holds_the_window_at_a_time(hosts):
    hosts("a")
    token = push_lease.acquire(say=quiet)
    assert token
    assert push_lease.holder()[0] == "a"
    hosts("b")
    # b's turn does not come while a holds it; with no wait left it gives up
    # (and pushes without a window) rather than failing the push
    assert push_lease.acquire(wait_minutes=0, say=quiet) is None
    assert push_lease.wait(wait_minutes=0, say=quiet) is False
    hosts("a")
    assert push_lease.release(token)
    hosts("b")
    assert push_lease.wait(wait_minutes=0, say=quiet) is True
    assert push_lease.acquire(wait_minutes=0, say=quiet)
    assert push_lease.holder()[0] == "b"


def test_the_holder_never_waits_for_itself(hosts):
    hosts("a")
    assert push_lease.acquire(say=quiet)
    assert push_lease.wait(wait_minutes=0, say=quiet) is True


def test_an_abandoned_window_expires_and_is_taken_over(hosts):
    hosts("a")
    assert push_lease.acquire(minutes=-1, say=quiet)       # already expired: a crashed holder
    hosts("b")
    assert push_lease.holder() is None
    assert push_lease.wait(wait_minutes=0, say=quiet) is True
    assert push_lease.acquire(wait_minutes=0, say=quiet)
    assert push_lease.holder()[0] == "b"


def test_only_the_holder_releases_and_a_stale_token_cannot(hosts):
    hosts("a")
    old = push_lease.acquire(minutes=-1, say=quiet)
    hosts("b")
    new = push_lease.acquire(wait_minutes=0, say=quiet)
    assert not push_lease.release(new.replace(new[0], "0" if new[0] != "0" else "1"))
    hosts("a")
    assert not push_lease.release(old)                      # taken over since
    assert push_lease.holder()[0] == "b"


def test_a_waiter_proceeds_once_the_holder_releases(hosts, monkeypatch):
    hosts("a")
    token = push_lease.acquire(say=quiet)
    hosts("b")
    polls = []

    def release_on_second_poll(seconds):
        polls.append(seconds)
        if len(polls) == 2:
            hosts("a")
            assert push_lease.release(token)
            hosts("b")
    monkeypatch.setattr(push_lease.time, "sleep", release_on_second_poll)
    assert push_lease.wait(wait_minutes=60, say=quiet) is True
    assert len(polls) == 2


def test_unreachable_claims_fail_open(hosts, monkeypatch):
    hosts("a")
    monkeypatch.setattr(claims, "fetch", lambda root=None: False)
    assert push_lease.acquire(say=quiet) is None
    assert push_lease.wait(say=quiet) is False


def test_the_window_is_invisible_to_body_pickers(hosts):
    hosts("a")
    assert push_lease.acquire(say=quiet)
    assert claims.busy_rvas() == set()
    assert claims.key_of("lease:master") in claims.active()
