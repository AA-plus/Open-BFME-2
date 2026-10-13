# Terrain extent getter emitter repair

Starting checkout: 6fa6c0fee2127d4a6c8a615e016f8e4f2ba3ea16.
Local index: cb660e4d97, 2026-10-13 04:02 UTC. Committed link_status.csv
reports a separate measurement, 3906ea7b97; it is discovery evidence only.
No census, link status or index was changed.

Suppress the out-of-line WorldHeightMap::getXExtent/getYExtent copies in
W3DTerrainBackgroundMarkTileGrid.cpp and BaseHeightMapInitHeightData.cpp.
The existing scoped prefix accessors remain visible inline with the same
+0x08/+0x0C field loads. MSVC's imported forced-inline form prevents their
incidental COMDAT emission. No import reference is emitted. No class layout,
header, compiler flag, pin, global, ledger name or extent changes.

These four-byte COMDATs have no known retail address. The local check rejects
them because they differ from the first definition in link order, not because
retail proves those getter bodies wrong. No original getter identity or
canonical class layout is established by this repair. Native matched caller
bytes prove the retained inline accesses. Both objects lose exactly the two
getter definitions; every other whole COMDAT byte sequence and relocation
name/addend is unchanged. Undefined references are unchanged. The comparison
normalizes COFF symbol-table indices, which move when definitions disappear.

Acceptance:

- Before and after, bounded link_check.py --prepare-current verifies all
  touched bodies with strict reusable self receipts. The unchanged grid
  setter provider Rva000AD9ABFinish.cpp is checked alongside its consumer.
- Final ./build.sh verifies 11/11 ledger rows across the three units, one
  string plus one empty-string reference, three floats, and zero named
  imports. The base-height-map funclet label renumbers from $L5378 to $L5376;
  the ordinary EH verifier proves its same retail placement at 0075EAC6.
- Tile-grid unit at 00111FCF (124 bytes): two COMDAT blockers -> none;
  ordinary local link_check exits 0. With the unchanged 684-byte grid-setter
  provider, the successful pair has LINKED 684 -> 808 bytes.
- Base-height-map unit: 18 -> 16 local blockers, only those same two getters
  removed; LINKED remains 0 -> 0 bytes. No new blocker appears.
- Final three-unit local preview: 2/3 clean, LINKED 684 -> 808 bytes.
  New-variants admission exits 0. Declared-definition, class, CSV and
  whitespace checks pass. Enforced converged-data check reports zero second
  names and zero unjudged rows; ordinary shadow data check has zero findings.

This is a 124-byte local legacy link-preview gain with self-strict touched
objects. New authored C++ bytes: zero. No closed-strict gain, new census count
or full executable placement is claimed. No maintainer-only link cycle,
nightly or boot runner was started.

Donor review: retained verified BFME1 gitlink/checkout
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85; reviewed repair
d3f9000fe08615a100e844adfff57fa4a39cd615 (TileData incidental constructor
suppression) and its diff/verification record. Its emitter-suppression
principle applies; its body and layout were not transferred. The BFME1
W3DTerrainBackground family uses the same extent-getter source structure;
BFME2's unchanged native callers provide local byte evidence. The existing
broader donor ownership sweep is recorded in concat-link-20261012 and was
not repeated without new relevant inputs.

Official BFME1 master was fetched at 6b09fe52a922804903f292646834ffb4572f5dc1.
The overdue pointer update remains foreign-claimed as file:reference/open-bfme-1
by codex-a44d-root. Its clean checkout, committed pointer and old freshness
success stamp were retained. Comparative full-byte update verification remains
with that worker; this session claims no successful freshness update.

The index sweep found exactly these two emitters charged for the non-const
extent getter names. BaseHeightMapInitHeightData still needs an existing
provider for detailOpaqueShader and reconciliation of BoundedShortGrid's
rva00062A58 and STL tree/allocator copies. Those are separate dependencies
and were not retried. No preserved untracked preparation was removed.
