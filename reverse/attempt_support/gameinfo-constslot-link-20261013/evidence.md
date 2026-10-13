# GameInfo::getConstSlot donor-copy repair

Local checkout: 41c21a33d3. Census index measurement: d753dedd98,
2026-10-12 22:16. The committed status used for discovery describes
e956901d31 instead; it is not the basis for this comparison. No census,
status, full link cycle or closed-strict artifact was produced or changed.

## Evidence and change

Retail 0x003FF2BE is a complete 24-byte range-checked accessor, reading
the slot pointer at this + 0x18 + index * 4. The ledger's owner in
GameSlotApparent.cpp and the additional GameInfoPlayerCounts.cpp copy
already emit that whole body. The unrowed GameInfo_Rva003FF374.cpp copy
instead read +0x14, as declared by the BFME 1 donor GameInfo header.
All three copies are relocation-free NODUPLICATES COMDATs (selection 1).
The before/after snapshots record whole section bytes and object hashes.

Only the donor-backed BFME 2 source changes: its accessor uses an explicit
local view of the target slot array. This makes its entire body equal to
retail and the other providers. The offset and body are target facts;
the name and operation are supported by the existing owner and BFME 1/ZH
source provenance. No other donor fields, shared headers or identities are
reconciled or claimed by this repair.

Reviewed BFME 1 linking repair 35bf0d0b18da30aefe812143de4a8add3ea21565
(MeshGeometryClass::get_bone_links): it corrects a donor/header offset view
from retail evidence and reconciles competing definitions. Its mesh ABI
and body do not apply here; only the repair approach is adapted. BFME 1's
verified checkout/gitlink remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Official master was fetched at 89b77071f7afb040d02affb2f1396c81d76f5e23.
The overdue update is held by codex-a44d-root's live reference-submodule
claim; checkout, pointer and freshness stamp were preserved.

## Checks and result

- Explicit self-strict provider preparation before/after: 3 sources,
  37/37 matched bodies, reusable receipts; ordinary source, literal, float
  and import gates pass. This establishes provider currency, not closure.
- ./build.sh on the three sources: 37/37 bodies exact, 32 literals and
  14 empty-string references, 22 imports verified.
- Local legacy link_check preview, all three current providers together:
  the donor copy's getConstSlot wrong-COMDAT finding disappears. Three
  duplicate findings remain. 0/3 files link cleanly and LINKED stays 0 B;
  both preview commands intentionally exit 1 for the unresolved blockers.
- check_csv and find_declared_unmatched pass. Converged data: 3 sources,
  8 addresses, no second names or unjudged rows. Ordinary shadow data
  check has no findings. No escape hatch or baseline was added.

Plain-inline and noinline-inline coalescing trials each changed 11/37
matched caller bodies: MSVC lost the known callee register preservation.
Both trials were reverted. Their byte-gate transcripts are retained and
the blocked coalescing attempt is logged. Future work must preserve that
compiler knowledge while arranging one acceptable provider or identical
select-any copies; repeating those unchanged variants is not useful.

There are zero new authored C++ bytes and zero clean-file linked-byte
gain. The verified improvement is removal of a retail-wrong provider.
Other duplicates, donor layout and library dependencies remain as listed
in preview-after.txt. Closed-strict and maintainer-only linker verification
remain outstanding.

Transcripts: sources.txt, strict-before.txt, strict-after.txt, byte-after.txt,
preview-before.txt, preview-after.txt, data-after.txt, data-converged-after.txt,
coalescing-inline-failed.txt, coalescing-noinline-failed.txt.
objects-before.json and objects-after.json prove the complete copies.
