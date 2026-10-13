# Taint singleton binding repair, 2026-10-13

Eight consumers now reference the data-ledger owner
`?TheTaintManager@@3PAVBfmeTaintManager@@A` at RVA `0x009FE750`
(VA `0x00DFE750`). The existing definition remains in
`Code/GameEngine/Source/Common/System/SubsystemSingletonPointers.cpp`.
The duplicate `void *g_Va00DFE750` definition in GameStateInit is removed;
address-named declarations and declarations with the distinct `TaintManager`
decoration are replaced. Local ABI views and their casts are retained where
needed, including GameLogic::getCRC's Snapshot base adjustment.

## Inputs and identity evidence

Base checkout: `e7706571be3262eb6de3398232b4f1b96341b996`.
The existing census index identifies measurement `d753dedd98`, dated
2026-10-12 22:16. Both previews use this same index and the nine current objects
(eight changed consumers plus the unchanged provider). The committed link-status
measurement is different; it is not used to claim a gain here.

Target evidence: the existing data ledger identifies the owner at this slot;
the verified GameEngine initialization registers it as `TheTaintManager`, and
GameState registers `CHUNK_TaintManager`. The relocation transcripts enumerate
15 executable DIR32 references whose retail operand minus compiled addend equals
VA `0x00DFE750`. All have zero addend. Before the repair these objects had two
strong data definitions for the slot's spellings; afterwards exactly one remains,
the existing provider's owner. All 15 references now use its exact decoration.
Object SHA256 values are recorded with the relocation evidence. Funclets with
renumbered local labels were read through the normal parent-EH-data resolver.

Donor review: verified BFME1 checkout
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`; reviewed upstream repair
`0835ab92bef30e3303e729a0ce09cf591368d0cd` in
`game/Libraries/Source/EA/Apt/PayloadCtorRva008AD100.cpp`. Its owner-typed extern
and cast-at-use repair is applicable as a binding pattern. Its Apt layout and
addresses are not imported. No new target class layout is inferred by this change.
BFME1 freshness was checked by fetching official master (observed
`8eb567945`), but advancing the pointer is held by another worker's live
`file:reference/open-bfme-1` claim. The verified pointer and success timestamp
were preserved; this pending update remains a separate blocker.

## Acceptance and measured improvement

- `link_check.py --prepare-current --paths-from sources.txt` before and after:
  all 184 matched code rows pass the ordinary byte gate, with strict reusable
  self receipts for all eight consumers. Two associated data rows, 225 literals,
  14 empty-string references, 29 floating literals and 26 named imports pass;
  zero skips or baselined literal references. The ordinary `./build.sh` check
  also passes (see byte-gate.txt).
- `./build.sh Code/GameEngine/Source/Common/System/SubsystemSingletonPointers.cpp`:
  all 12 data rows pass; the unchanged provider object is receipt-current.
- Local `link_check.py --paths-from sources.txt
  Code/GameEngine/Source/Common/System/SubsystemSingletonPointers.cpp`, before
  and after: three unresolved references removed, none added. Two occurrences
  of `?TheTaintManager@@3PAVTaintManager@@A` and one of
  `?g_00DFE750@@3PAVTaintManager@@A` disappear. The preview remains 2/9 clean,
  2,078 -> 2,078 linked C++ bytes; it exits 1 because other blockers remain.
- `data_check.py` on the eight sources: 28 -> 20 shadow findings,
  24 -> 17 outside baseline. All eight findings for the taint slot disappear.
- `data_check.py --converged`: eight registered addresses checked, zero second
  names and zero unjudged. The protected convergence list is unchanged.
- Hatch scan of the touched files: 70 -> 50 textual occurrences, with no
  counter growing. Twenty address-global occurrences are removed.
- `find_declared_unmatched.py` succeeds for all eight sources;
  `check_csv.py`, `check_case_collisions.py`, and `git diff --check` pass.

The verified improvement is shared-data binding and debt removal. Authored C++
coverage and clean-unit linked bytes both grow by zero. Strict evidence is for
each unit's own bytes; the link result is a local preview against the existing
legacy census. No closed-strict gain or full link-cycle result is claimed.
No census measurement, link cycle, nightly or boot runner was started.

## Remaining blockers

The before/after link transcripts retain the concrete independent blockers.
W3DTaint and W3DShroudCtor still have helper/STL COMDAT blockers; PlayerList has
callback and neutral-player blockers; TerrainLogic needs `rva0027F1DD`;
GameLogic::getCRC still references collision and CRC-flag spellings without
providers. GameLogicInit and GameEngineInit retain other singleton, constructor
and selected-COMDAT blockers. Collision slot `0x009FE754` is a possible separate
owner-binding repair; none of those dependencies was changed here.

`sources.txt` is the exact touched cohort. The other files preserve raw acceptance
outputs and before/after evidence. No ledger rows, pins, baselines, headers or gate
code were changed.
