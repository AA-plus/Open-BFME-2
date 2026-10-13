# ShatterSystem interpolation dependency repair

Base: `c1b1e93bad`. Supplied census index: `d753dedd98`,
2026-10-12 22:16. Committed link status measures `2a20912cc9`,
2026-10-13 08:08; these are separate artifacts. Neither was rewritten.

Replace the two already-inlined Vector3::Lerp calls in VertexClass::Lerp
with the donor's X/Y/Z expressions in their original store order. This
removes an unnecessary out-of-line interpolation definition and the
consumer's dependency on the selected interpolation COMDAT. It adds no
alias, pin, private type, compiler setting or ledger row.

The original ShatterSystem copy is itself the correct 85-byte body,
digest `d858ac913ecf`, identical to the rowed vector3.cpp provider at
0x0009AA48. The supplied census selects a wrong definition elsewhere;
this repair does not reconcile that remaining provider selection. The
current ShatterSystem object has no Lerp definition or external call to
it. All 247 common COMDATs retain identical whole-body/relocation digests,
with no new COMDAT. Object hashes, removed bytes and individual unchanged
digests are recorded in object-comparison.txt. Compiler-local EH table
labels were renumbered; their handler instruction bytes did not change.

The arithmetic semantics come from the resolved Zero Hour vector3.h at
verified BFME1 pointer `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`:
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/vector3.h`.
The dependency receipt confirms that header was actually used. Assertions
are disabled by the existing /DNDEBUG. Target byte verification establishes
the two existing matched Matrix3D bodies, not a new target identity for
VertexClass::Lerp. No new class-layout claim is made.

Reviewed BFME1 repair `d3f9000fe08615a100e844adfff57fa4a39cd615`
(TileData incidental constructor emitter removal), including its source
diff and verification account. Suppression of an unnecessary emitter is
applicable; its constructor and layout are unrelated and were not imported.
The earlier BFME2 HRawAnim interpolation repair provided a local lead;
unlike HRawAnim, this unit's removed copy is already byte-correct.

## Acceptance and measured improvement

The edited file was scope-claimed. Before and after:

```
python3 tools/link_check.py --prepare-current Code/Libraries/Source/WWVegas/WW3D2/shattersystem.cpp Code/Libraries/Source/WWVegas/WWMath/vector3.cpp
python3 tools/link_check.py Code/Libraries/Source/WWVegas/WW3D2/shattersystem.cpp Code/Libraries/Source/WWVegas/WWMath/vector3.cpp
```

Each bounded preparation passed 12/12 rows and issued strict reusable
receipts for the two explicit sources. Both final receipts are self-strict
current. The edited unit separately passes ./build.sh: 2/2 rows, 280
retail bytes, no skipped/baselined string references. Neither source was
included in a verified closed link closure.

Against the same supplied index, the legacy current-object link preview
removes ShatterSystem's Lerp selected blocker: 52 blockers become 51,
with no added blocker. The vector3.cpp selected blocker remains. Both
previews exit 1 because unrelated blockers remain, 0/2 sources clean,
LINKED 0 -> 0 bytes. No actual linker placement, closed-strict gain or
authored C++ coverage increase is claimed.

Other checks pass: new-variants admission; find_declared_unmatched;
converged data check for both sources (8 addresses, zero second names
or unjudged rows); check_csv (87,382 functions, 17,241 symbols, 307 data
rows); git diff --check. Logs accompany this record.

## Handoff

Remaining ShatterSystem blockers include material/mesh providers,
ShareBuffer/SimpleVec ownership, Matrix3D, RefCount and other math helpers;
the complete current-object list is in link-after.txt. The global Lerp
selection still needs current peer evidence. Other ranked concat,
StringBase teardown and address leads were already repaired in current
sources; the available pool-global candidate in GapBodiesGE29.cpp is
held by another worker. Those unchanged tasks were not retried.

Official BFME1 master was fetched, but the overdue verified pointer update
is held by another worker's live `file:reference/open-bfme-1` claim. Its
clean verified checkout and old freshness stamp were retained. Comparative
full-byte verification and any layout reconciliation remain outstanding
with that worker. No full census, link cycle, nightly or boot runner ran.
