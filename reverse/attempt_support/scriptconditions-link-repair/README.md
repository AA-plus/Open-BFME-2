# ScriptConditions provider and helper repair

The existing rows in `ScriptConditions.cpp` remain exact. This repair adds
no recovered coverage.

Upstream independently corrected the Eva signature and helper linkage in
`f54bfb2b8b`. The obsolete non-const integer-signature pin is removed. The
parameter accesses use the existing public integer field instead of emitting
a competing private `Parameter::getInt` COMDAT, and the TU's float-ceil helper
has internal linkage upstream. The special-power store declaration uses its real
global, owned by `SpecialPowerStoreFind.cpp`, rather than a second datum at
the same address. The merged `/G7` settings preserve all four current bodies.

Before the rebase, `build.sh` verified all three bodies, source claims,
literals, and imports. The scoped `link_check.py` preview changed this unit from 0 to 396 linking
bytes against the existing census index (2026-10-10 19:06, `7bcd61f5c1`).
This is a scoped prediction, not a new whole-repository census. Attempting
to prepare the current Eva provider was refused because its include inventory
contains an unresolved macro or parent-traversing include; that refresh was
not reported as successful and no verifier was changed.

During rebase, upstream commit `ad936a52db` landed the same 188-byte
`evaluateSkirmishCanFireSpecialPowerOnTeam` body. Its row and implementation
are preserved, and the obsolete bank is not restored. The merged unit passes
the ordinary four-body byte gate. Its link preview now reports zero linking
bytes: the 3,521-byte ActionManager callee at `0x0041D60B` remains unrowed,
and the pointer-return Team centroid declaration lacks a compiled provider.
`link-preview-rebased.txt` records that current result. The earlier 396-byte
preview is historical evidence of the repaired helper/provider bindings,
not the final unit's link status.
