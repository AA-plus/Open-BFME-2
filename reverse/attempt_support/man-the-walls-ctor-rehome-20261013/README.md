# ManTheWalls entry-constructor ownership repair, 2026-10-13

Session base: `43f90982ef`. The runner-provided census index was measured at
`cb660e4d97` on 2026-10-13 04:02 UTC. The committed link-status snapshot is a
queue lead, not this measurement. No per-row data-back artifact was used.

## Verified repair

Move the existing 22-byte `Rva004BA1B2` constructor row at `0x004BA1B2` into
ManTheWallsSpecialPower.cpp and delete Rva004BA1B2Ctor.cpp. The home already
emits the exact constructor and calls it from its matched `0x004C78AF` body.
The split object defines it exclusively; the home emits an identical retail
COMDAT. Deleting the split removes one duplicate-definition cause. Neither
the constructor body nor compiler settings change; authored C++ coverage
does not grow.

`object-proof.txt` records the whole relocated body, current strict compiler
receipt, historical provider inventory, sole remaining ledger owner and
absence of the deleted source. The retained target evidence establishes the
16-byte Object/member-vector record through callers and same-file helpers.
Its original class name remains unknown. No identity, layout, pin, alias,
global or escape hatch was added.

## Donor review

Reviewed BFME 1 repair `63955ed0f3d52748d67c899cfa5e60d72848300e`, which
re-homes helper rows into existing callers and removes competing definitions.
Its ownership principle applies; its concrete FVF code and ABI do not apply
here. Also reviewed `1926a8216469e2ed59c96901e5f0ba6905f734db`'s existing
data-owner repair while assessing global blockers. No donor body was imported.

The retained verified BFME 1 pointer is
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`. This session fetched official
master to `fe21e3cb11f8b4e03651e9c3c84dd76d6d7b3809`. The overdue pointer
update remains under the foreign `codex-a44d-root` claim on
`file:reference/open-bfme-1`; the checkout, committed pointer and successful
freshness stamp were preserved.

## Acceptance and remaining blockers

- `rehome_rows.py --limit 8` reported an exact home match for this row. The
  broader read-only search was interrupted once this supported task was found.
- `add_match.py --replace-existing`: home byte gate **11/11**, row verified.
- `link_check.py --prepare-current` before on home and split: **11/11** across
  two units. After on home: **11/11**, strict reusable compiler receipt, zero
  skipped/baselined references. These prove self-strict compiler currency and
  byte identity, not self-strict or closed-strict link closure.
- Ordinary local `link_check.py` before and after: **0 linked bytes**. Both
  transcripts are retained. The historical index still includes the deleted
  split object, so its stale duplicate appears in the after preview. No
  deletion-adjusted index was substituted and no index/status file was edited.
  The next runner census must measure the ownership improvement.
- Declared-definition check, `check_csv.py` and `git diff --check` pass.
- `data_check.py --converged`: one source, eight addresses, zero second names
  and zero unjudged rows.

The home still has Object/E8 vector COMDAT disagreements, filter deleting
destructors, wrong-retail BfmeResultA cleanup and allocator selections. These
require coordinated dependency work; no full link cycle, census build/history,
nightly or boot runner was started.
