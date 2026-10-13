# Scene LOD selector provider binding

Base checkout: `89da3d5ade6cef17deab72996661747813fad327`.
The restored legacy census measures `cb660e4d97` at 2026-10-13 04:02;
the committed repair queue measures `67e1365aa9`. Queue rankings are leads,
not interchangeable measurements. No census, index, status or history changed.

## Target evidence and repair

Newly matched RTS3DScene::Flush (RVA 0x00071606, 2106 bytes) and
renderOneObject (0x0006FB59, 2550 bytes) still referenced undefined
`?g_Va00DB5FA0@@3HA`. GlobalGetterSingles.cpp already defines the sole
integer `?LODTextureReduction@@3HA`, initialized to 2. Its getter at
0x0006E16F and all four scene DIR32 operands have zero addends and reach
retail VA 0x00DB5FA0. Retail's initial DWORD is 02000000. The before/after
relocation transcripts include strict reusable receipts and object hashes.
The census has one strong definition of LODTextureReduction and none of the
old name; both current consumers now reference the existing provider.

The change continues the established lod-selector-link-20261013 repair
across these later arrivals. Two extern declarations, four uses and one
comment now spell the existing integer owner. No datum, alias, pin, row,
layout, compiler setting or extent was added. Retail operands establish the
shared slot and access width; the existing provider supplies the identifier,
whose original retail source spelling is not independently proven.
The two bodies cover 4,641 existing authored bytes after excluding 0xCC.

## Reference review and freshness

The committed and clean BFME 1 checkout remains
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`. This session reviewed donor
link repairs 6906e0cdd, b870d563b and 0a3a4f605: direct provider binding and
single-owner data declarations apply; the functions and BFME 1 layouts do
not supply BFME 2 evidence. No donor code or headers were imported. The
prior LOD repair already reviewed 908413c254; its unchanged scan was reused.

Official master was fetched at
`24656f4d3e8ea20887e256aef9a0dfaaa7ad6aae`, beyond the verified pointer.
The overdue comparative full-byte verification remains incomplete. Earlier
preserved build/reference-update-blocker.txt reports baseline compiler
stalls in FontCharsClassGdiState_Ctor.cpp and profile_highlevel.cpp; that
older report is not a current proof against this fetched revision. No live
foreign reference claim was present when checked. This session kept the
verified inputs and did not write a freshness success stamp. Updating the
pointer requires a dedicated comparative verification pass.

## Acceptance and limits

- Before/after bounded self-strict preparation: three explicit sources,
  24/24 matched functions and one data row exact. Ordinary ./build.sh on
  those same sources passes. Eleven string literals and four float literals
  verified; zero skipped or baselined string references. Strict receipts
  establish object currency, not link closure.
- Frozen-file checks, check_csv (87954 functions, 17166 pins, 328 data rows)
  and git diff --check pass. Enforced converged-data check: eight addresses,
  zero second names and zero unjudged rows across three sources.
- The counted address-global hatches fall 2 -> 0 in Flush and 7 -> 3 in
  renderOneObject. No hatch count grows. No baseline was expanded.
- Ordinary local link preview refuses both scene units before and after:
  they are absent from census cb660e4d97. The provider's legacy preview
  passes at 136 -> 136 bytes. No consumer LINKED gain is asserted.
- Non-shadow --new-variants admission exits 1 both before and after with
  the identical existing RefRenderObjListIterator constructor COMDAT
  conflict in renderOneObject. This binding adds no variant and leaves that
  independent diagnostic visible; it is not classified as a false reject.
- Shadow data_check reports stale ledger ownership of DB5FA0 under the old
  name, plus existing animation-clock, FogEnable and DBA4E4 findings. The
  actual owner is reused rather than defining another global; no findings
  were hidden or baselined. The six outside-baseline keys are recorded.

Verified improvement: the undefined selector name disappears from both
current consumer objects, all four operands now bind the sole existing
provider, and six address-name hatch occurrences are removed. New authored
bytes: zero. Consumer closed-strict closure, a current global census and
actual full linking remain unmeasured. No maintainer-only runner was started.
