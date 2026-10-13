# Mapper Vector2 COMDAT repair

Source base: 325d050a41ed6aaa1b52a6c497d5c834a4ffc9c4. The runner index
measures cb660e4d97 at 2026-10-13 04:02 UTC; index-meta.json records its
SHA256. The committed link queue at e181b4b6c5 was discovery evidence only.
No census, index, status/history or data-back artifact was created or changed.

mapper.cpp emitted non-retail scalar Vector2 multiplication and division
copies. Load wwmath.h normally, then vector2.h inside the existing gsy size
optimization block before the iterator anchor. The pattern follows matched
StreakRendererCtor.cpp. Restore the original optimization state before the
mapper definitions. MSVC's existing local math.h overload setup moves before
these dependencies. No shared header, algorithm, ABI/layout, compiler flag,
ledger row, pin, global, marker or anchor changes. The keyed escape-hatch
counts are identical before and after: the existing pragmas are reused.

Both complete emitted operators now equal the unchanged W3DRoadBuffer.cpp
providers, including raw bytes, extents and relocation tuples: multiplication
at 0x000D4451 (39 bytes), division at 0x0007B2AC (49 bytes). Provider ownership
is established by existing byte-verified ledger rows; no new identity or
layout claim was made. The before/after consumer changes exactly those two
COMDATs from wrong to retail. All 193 other consumer COMDATs and all 261
provider COMDATs are identical, with no name added or removed. Strong,
undefined and weak external facts are identical. All 30 consumer and 20
provider normalized EH sections are identical. Ordinary sections, excluding
debug metadata and normalizing sxdata symbol indices, are identical as well.
object-proof.json binds these comparisons to source/object/index hashes.
Full snapshots and scripts remain in ignored build/mapper-vector2-link-20261013.

Acceptance:

- Bounded strict-current preparation before and after, then build.sh: 177/177
  matched rows in consumer and unchanged provider. All 39 literals, one empty
  string and 172 compiler float references verified; none skipped/baselined.
  Three renamed funclet labels verified through parent EH placement.
- Same-index ordinary legacy link preview: mapper findings 11 -> 9, exactly
  the two operator conflicts disappear, no finding is added. Provider findings
  remain unchanged. Cohort remains 0/2 clean; local LINKED stays 0 bytes.
- EH verifier: all 24 applicable row graphs EXACT, no baseline exceptions.
- Enforced converged data: two sources, eight addresses, zero second names
  or unjudged rows. Ordinary shadow data: zero findings.
- Declared-definition, class, new-variants admission, CSV and whitespace checks
  pass. Placement resweep: zero new bodies or pins.

This repairs two local link blockers with zero new authored C++ and zero
local linked-byte growth. Self-strict byte/object evidence is established.
Closed-strict gains, actual link.exe placement and measured census gains
are not claimed; broader closure remains outstanding.

Reused the unchanged broader BFME1 linking scan and reviewed donor repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d. Its surplus-emitter diagnosis is
applicable; its constructor pin/alias mechanism is inapplicable here. No donor
body was imported. Verified BFME1 checkout/gitlink remains
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Official master was fetched as
49e35f6636748b0e1116265ce543de2f7aca0d39. The overdue old/new full-gate
comparison remains incomplete: the previous attempt stopped at the full-build
lock with 5337 stale TUs and no newer full baseline is available. No donor
inputs were advanced, and the freshness-success stamp was not changed.

Remaining mapper findings: three missing Apply/Calculate_Texture_Matrix
providers, RefCount scalar deleting destructor disagreement, non-retail
GridTextureMapper copy constructor and initialize definitions/selections,
and selected RefCount constructor. Names are recorded in link-after.txt.
These independent class/provider repairs were not retried. Unrelated
untracked dumps and ZH sweep preparation are preserved.
