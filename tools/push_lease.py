#!/usr/bin/env python3
"""A push window on origin/master for full-gate pushes, so they can land.

WHY. A push whose scope needs the ordinary full gate spends ~13 minutes
byte-verifying before git sends it. With several contributors pushing small
scoped batches every few minutes, master moves during almost every such gate
and the push is rejected; on 2026-10-12 one batch passed the full gate ten
times and never landed. Nobody did anything wrong, so nothing but a turn can
fix it.

HOW. The window is a shared claim (tools/claims.py) on the scope
`lease:master`, i.e. the ref refs/claims/lease/master on origin, with a short
TTL (BFME_PUSH_LEASE_MINUTES, default 23). It inherits everything claims
already guarantee: creating it is atomic across hosts, only its owner releases
it, an expired one is taken over by compare-and-swap, and `claims.py list`
shows who holds it.

  * .githooks/pre-push ACQUIRES it before running the full gate for a push to
    master (waiting its turn if another pusher holds it) and RELEASES it when
    the hook ends, pass or fail.
  * Every other push to master WAITS at the end of its hook while another
    owner holds a live window, so a scoped push cannot move master under a
    full gate in progress.
  * A crashed or abandoned holder blocks others for at most the TTL. A waiter
    gives up waiting after BFME_PUSH_LEASE_WAIT_MINUTES (default TTL + 2) and
    pushes anyway; the window is a courtesy, never a reason to fail a push.
  * Fail-open: when origin's claims cannot be read, acquire and wait warn and
    return; the push then races exactly as it did before this window existed.

  python3 tools/push_lease.py status
  python3 tools/push_lease.py acquire          # prints the lease token
  python3 tools/push_lease.py wait
  python3 tools/push_lease.py release TOKEN
"""
import argparse
import os
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import claims  # noqa: E402

SCOPE = "lease:master"
KEY = claims.key_of(SCOPE)
MINUTES = float(os.environ.get("BFME_PUSH_LEASE_MINUTES", "23"))
WAIT_MINUTES = float(os.environ.get("BFME_PUSH_LEASE_WAIT_MINUTES", str(MINUTES + 2)))
POLL_SECONDS = float(os.environ.get("BFME_PUSH_LEASE_POLL_SECONDS", "30"))


def holder(root=None):
    """(owner, expires) of the live window, or None. Raises ClaimsUnavailable."""
    if not claims.fetch(root):
        raise claims.ClaimsUnavailable("push_lease: cannot fetch refs/claims/* from origin")
    entry = claims.live(claims._read_local(root)).get(KEY)
    return (entry[1].get("owner"), entry[1].get("expires", 0)) if entry else None


def acquire(minutes=MINUTES, wait_minutes=WAIT_MINUTES, poll=POLL_SECONDS, root=None, say=print):
    """Take the window, waiting while another owner holds it. Returns the
    lease token, or None when origin's claims are unreachable (fail-open) or
    the wait ran out."""
    deadline = time.time() + wait_minutes * 60
    while True:
        try:
            got = claims.claim([SCOPE], ttl_hours=minutes / 60, note="full-gate push to master", root=root)
        except claims.ClaimsUnavailable as why:
            say(f"push_lease: {why}; pushing without a window", file=sys.stderr)
            return None
        if got.claimed:
            return got.tokens[KEY]
        now = time.time()
        if now >= deadline:
            say(f"push_lease: still held after {wait_minutes:g} min; pushing without a window",
                file=sys.stderr)
            return None
        try:
            held = holder(root)
        except claims.ClaimsUnavailable:
            held = None
        if held:
            say(f"push_lease: {held[0]} holds the master push window for "
                f"{max(0, int(held[1] - now)) // 60} more min; waiting", file=sys.stderr)
        time.sleep(min(poll, max(0.0, deadline - now)))


def wait(wait_minutes=WAIT_MINUTES, poll=POLL_SECONDS, root=None, say=print):
    """Block while ANOTHER owner holds a live window. Always returns (True when
    the window is free or ours, False when the wait ran out or origin's claims
    are unreachable)."""
    me = claims._names(claims.owner(root), root)
    deadline = time.time() + wait_minutes * 60
    told = False
    while True:
        try:
            held = holder(root)
        except claims.ClaimsUnavailable as why:
            say(f"push_lease: {why}; pushing without waiting", file=sys.stderr)
            return False
        if not held or held[0] in me:
            return True
        now = time.time()
        if now >= deadline:
            say(f"push_lease: {held[0]} still holds the window after {wait_minutes:g} min; pushing",
                file=sys.stderr)
            return False
        if not told:
            say(f"push_lease: {held[0]} is landing a full-gate push; waiting up to "
                f"{max(0, int(held[1] - now)) // 60 + 1} min for the master push window", file=sys.stderr)
            told = True
        time.sleep(min(poll, max(0.0, deadline - now)))


def release(token, root=None):
    """Release our window if `token` still holds it; True when released."""
    try:
        return claims.release([SCOPE], tokens={KEY: token}, root=root) == [KEY]
    except claims.ClaimsUnavailable:
        return False


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("status", help="who holds the master push window")
    sub.add_parser("acquire", help="take the window (waiting your turn); prints the token")
    sub.add_parser("wait", help="wait while another owner holds the window")
    rel = sub.add_parser("release", help="release the window you hold")
    rel.add_argument("token")
    args = ap.parse_args(argv)
    if args.cmd == "status":
        try:
            held = holder()
        except claims.ClaimsUnavailable as why:
            print(why, file=sys.stderr)
            return 2
        print("free" if not held else f"held by {held[0]} for {max(0, int(held[1] - time.time()))} s")
        return 0
    if args.cmd == "acquire":
        token = acquire()
        if token:
            print(token)
        return 0
    if args.cmd == "wait":
        wait()
        return 0
    release(args.token)
    return 0


if __name__ == "__main__":
    sys.exit(main())
