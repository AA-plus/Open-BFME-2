# Float and laser math-wrapper link repair

Source base c2b990a011b6fce2c907c16ef7ffbcd3ec6495a9. Available local
census index measures cb660e4d97, 2026-10-13 04:02 UTC; committed
link_status.csv measures 2a20912cc9 and supplied discovery only. Neither
record nor the index is changed. No data-back artifact or ranking is used.

FloatUpdateUpdate and W3DLaserDrawBfmeDoDraw emit surplus MSVC float
math wrappers. Their actual operations already inline. Include the original
math.h overloads with static inline linkage before other headers, following
the verified texture/geometry repair. Compiler flags, source provenance,
identities, class views, layouts, behavior and call bindings are preserved.

Target evidence in object-proof.json:

- Float removes exactly sin(float), cosf and sinf COMDATs; all 20 retained
  copies have identical bytes, sizes, relocation tuples, digests and verdicts.
- Laser removes exactly cos(float), sqrt(float), cosf and sqrtf COMDATs;
  all 32 retained copies are identical by the same comparison.
- Neither object adds a COMDAT. Strong definitions, undefined references
  and weak bindings are unchanged. There is no new provider dependency.
  Source/object hashes and strict currency bind the comparisons. Full facts
  and source backups remain in build/float-math-link-20261013 and its laser
  sibling; the committed proof retains hashes for every unchanged copy and
  the complete removed copies.

Acceptance: both units pass strict reusable self preparation before and
after. Ordinary ./build.sh passes 2/2 whole rows (945 and 1689 bytes), one
string and 21 compiler float literals, with zero skipped/baselined references.
The laser's one EH graph is EXACT; Float has none. New-variants admission,
class gate, declared-definition check, CSV and whitespace checks pass.
Enforced converged-data check finds zero second names/unjudged rows across
eight addresses. Shadow data retains one existing finding within baseline;
all retained relocation-bearing bodies are unchanged. No hatch is introduced.

Same legacy local preview: Float blockers 5 -> 4, Laser 5 -> 4, with no new
blocker. Cohort remains 0/2 clean, LINKED 0 -> 0. This removes seven external
emitters and two link blockers, with +0 authored C++ bytes. Self-strict
verification is established; closed-strict closure, actual link.exe placement
and new measured census gains are not claimed. No full census, link cycle,
nightly or boot runner was started.

Remaining Float blockers: competing update definition/selected body,
getInstanceMatrix copy, selected Matrix3D copy constructor. Remaining laser
blockers: GameGetColorComponentsReal, the two address-derived apply providers,
and Coord3D::scale. These need separate supported provider/class repairs.

Donor review: retained clean verified BFME1 checkout/gitlink
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Reviewed its laser cosine
operations and FloatUpdate unit, preserving existing donor uncertainty; no
donor layout or new identity is imported. Reviewed linking repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d: suppressing surplus non-retail
inline copies is applicable; its string constructor/pin mechanism is
inapplicable. The unchanged broader donor scan in prior texture/concat
evidence is reused.

Official BFME1 master fetched as 9778a932c11c43066d2674eafc0ce24b7cdcd517.
The due verified-pointer update remains held by codex-a44d-root's live
file:reference/open-bfme-1 claim. Verified inputs and the old success stamp
are preserved; comparative full verification and pointer publication remain
outstanding with that worker. Freshness was not marked successful.

Queue probes also found Rva001E46E1Ratios, Rva003FA781,
StrafeAreaUpdateRva003A4FDA, CylindricalEmissionVelocityModuleSample and
collisionmanager_data already locally clean. They were not edited, and the
two exploratory file claims were released. No unchanged blocker was retried.
