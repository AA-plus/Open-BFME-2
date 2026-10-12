#!/usr/bin/env python3
"""Git merge driver for the line ledgers .gitattributes marks merge=union.

git's built-in union merge keeps BOTH sides of every conflicting hunk, and it
cannot tell a row one side deleted or edited from a row that side kept: when an
upstream edit or retraction lands next to your own change, the old row comes
back beside the new one. 39 of Open-BFME-1's 1,028 commits on 2026-09-27
repaired exactly that by hand.

This takes union's layout and removes what union put back wrongly, decided from
the merge base: a row either side deleted stays deleted, and a row both sides
added is kept once. A row both sides EDITED differently keeps both versions, as
union does: the driver never picks a side, and that ledger's own checks decide
whether the two can stand together.

The rule, per row, from how many copies the base, ours and theirs hold: each
side's change is an addition or a removal. Two additions overlap, and so do two
removals: the larger applies once. An addition beside a removal both apply. So
two sides that each remove the same duplicate leave the copy they both kept,
and a side that removes every copy wins over one that removes fewer.

This driver only removes lines, so the result holds at most that many copies.
When union's layout holds fewer copies of a row than BOTH sides hold (they
removed different copies of a repeated row, and git merged both removals),
nothing is written and the merge is left conflicted.

It is registered under the name `union` itself, so a clone that has not
registered it keeps git's plain union instead of stopping on conflicts. The
merge.union.driver command is the one tools/setup_hooks.sh sets (and
.githooks/pre-commit, for clones set up before this existed).
"""
import collections
import subprocess
import sys


def lines(data):
    """Split on \\n only, keeping each terminator: some ledger rows end in \\r\\r\\n."""
    parts = data.split(b"\n")
    return [part + b"\n" for part in parts[:-1]] + ([parts[-1]] if parts[-1] else [])


def row(line):
    return line.rstrip(b"\r\n")


def copies(o, a, b):
    """How many copies of a row to keep, from its count in base, ours and theirs."""
    if a >= o and b >= o:
        return max(a, b)
    if a <= o and b <= o:
        return min(a, b)
    return a + b - o


def merge(union, base, ours, theirs):
    """Return (merged bytes, lines dropped from union, rows left with fewer copies than both sides hold)."""
    o, a, b = (collections.Counter(map(row, lines(side))) for side in (base, ours, theirs))
    kept, out = collections.Counter(), []
    for line in lines(union):
        key = row(line)
        if kept[key] < copies(o[key], a[key], b[key]):
            kept[key] += 1
            out.append(line)
    short = [key for key in a if kept[key] < min(a[key], b[key])]
    return b"".join(out), len(lines(union)) - len(out), short


def main(argv):
    if len(argv) != 4:
        print("usage: merge_rows.py BASE OURS THEIRS PATH", file=sys.stderr)
        return 2
    base, ours, theirs, path = argv
    union = subprocess.run(["git", "merge-file", "-p", "--union", ours, base, theirs],
                           capture_output=True)
    if union.returncode:
        print(f"merge_rows: git merge-file failed on {path}; leaving a conflict\n"
              + union.stderr.decode(errors="replace"), file=sys.stderr)
        return 1
    sides = [open(p, "rb").read() for p in (base, ours, theirs)]
    merged, dropped, short = merge(union.stdout, *sides)
    if short:
        print(f"merge_rows: {path}: leaving a conflict. Both sides removed copies of a repeated "
              "row, but different ones, and merging both removals would leave fewer copies than "
              f"each side still holds, of {len(short)} row(s):\n"
              + "\n".join("  " + key.decode(errors="replace")[:200] for key in short[:5]),
              file=sys.stderr)
        return 1
    with open(ours, "wb") as handle:
        handle.write(merged)
    if dropped:
        print(f"merge_rows: {path}: dropped {dropped} line(s) plain union would have "
              "resurrected or duplicated", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
