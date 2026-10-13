# Texture mapper math-wrapper link repair

Source base: a21ee1a19a (full hashes in receipts.json). The available local
index measures cb660e4d97, 2026-10-13 04:02 UTC. Committed link_status.csv
instead measures 2a20912cc9 and supplied discovery only. No census, index,
status, ledger row, pin or baseline is changed; no data-back artifact is used.

TextureMapperFXShaderConvert emits unused out-of-line MSVC fabs(float) and
fabsf copies that lose to the first copies in link order. Its actual fabs
operations inline. Include the original math.h overloads with static inline
linkage before other headers, following the verified geometry repair. Sweep
the same supported cause in GridTextureMapperClassInitialize and mapper.cpp:
their inlined fabs operations also remain unchanged under this scoped include.
Compiler flags, class views, ABI, identities and behavior are preserved.

Target evidence: each object removes exactly ?fabs@@YAMM@Z and _fabsf,
adding no COMDAT. All 25, 6 and 195 retained COMDATs respectively have
identical raw bytes, relocation tuples, sizes and digests. Strong definitions,
undefined externals and weak bindings are unchanged. There is no new external
provider dependency. Full source/object facts and backups remain in
build/texture-math-link-20261013; retained receipt hashes bind these proofs.

Acceptance:

- Strict reusable self verification before and after: conversion 4/4 rows,
  initializer/mapper 71/71. Ordinary ./build.sh on all three: 75/75 rows,
  50 string literals plus six empty strings and 33 compiler floats verified,
  zero baselined/skipped references. All 18 applicable EH graphs are EXACT.
- Same legacy local preview: conversion blockers 3 -> 1, initializer 3 -> 1,
  mapper 13 -> 11. All six fabs blockers disappear; no new blocker appears.
  Cohort remains 0/3 clean, LINKED 0 -> 0. Existing real authored totals
  1552, 258 and 5784 bytes remain held by independent blockers.
  cohort-intermediate.txt explicitly follows the first conversion repair and
  precedes the initializer/mapper edits; link-before.txt is the conversion's
  original three-blocker baseline.
- New-variants admission, class gate, declared-definition and CSV checks
  pass. The initializer's existing unclaimed unemitted anchor remains a
  non-refusing note; no declaration marker is added. Enforced converged-data
  check: three sources, eight addresses, no second names or unjudged rows.
  Shadow data check has zero findings. Whitespace check passes.

This is six fewer link blockers and six fewer external emitters, +0 authored
C++ bytes and +0 legacy preview linked bytes. Self-strict verification is
established. Closed-strict closure, actual link.exe placement and new measured
census gains are not claimed. Only explicit scoped preparation and local
previews ran; no full census, link cycle, nightly or boot runner was started.

Remaining blockers are recorded in cohort-after.txt: conversion's non-retail
Rva0007BB16Record scalar destructor; initializer's selected non-retail
GridTextureMapperClass::initialize; mapper's three missing virtual providers,
RefCount scalar destructor, two Vector2 operators, grid initialization/copy
constructor and selected RefCount constructor. These need separate supported
class/provider repairs; none was retried as a reconstruction in this task.

Donor review: retained clean verified BFME1 checkout/gitlink
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Reviewed donor linking repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d: suppressing surplus non-retail
inline copies is applicable; its BfmeStrVKI constructor/pin mechanism is
inapplicable. No donor implementation, layout or identity is imported.
The unchanged broader ownership scan in prior concat/geometry evidence is
reused. Existing source provenance and uncertainties remain.

Official BFME1 master fetched as 022c5f26aa2dacd9407651b03d1d055b6e957aff.
The due verified-pointer update remains held by codex-a44d-root's live
file:reference/open-bfme-1 claim. Verified inputs and the old success stamp
were preserved; comparative full verification and pointer publication remain
outstanding with that worker. Freshness was not marked successful.
