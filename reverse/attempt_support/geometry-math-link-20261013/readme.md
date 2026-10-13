# Geometry math-wrapper link repair

Starting BFME2 revision: e77156e948cf9a274cf6ea52321a03029d9878f2.
The available local census index measures cb660e4d97, 2026-10-13 04:02 UTC.
The committed link_status.csv measures 2a20912cc9; it was used for discovery,
not as the baseline for these previews. Neither record was changed.

GeometryInfoCalcPitches emitted surplus MSVC math.h float wrappers. Apply
its existing static-inline inclusion pattern from the verified portal repair
e77156e948. The original math overload definitions, flags, class views,
ABI, literals, row extents and function behavior remain unchanged. A sweep
of the geometry family's matching blockers found GeometryInfoCalcBoundingStuff
with the same supported sqrt/fabs emission cause. Include math.h there with
the same scoped inline definition before its other headers. No shared header,
pin, alias, global definition, marker or ledger row was added or changed.

Target verification establishes complete body preservation, not new identity
or layout facts. The existing rows carry donor identities and their original
uncertainties. Both objects have identical retained COMDAT names, sizes and
byte-and-relocation digests (three in pitches, 23 in bounds). Exactly four
math COMDATs disappear from each object; no new or changed retained COMDAT
exists. Strong definitions, undefined externals and weak bindings are unchanged.
The scratch source/object backups and complete COFF facts remain under build/.

Acceptance:

- Strict reusable self receipts before and after: pitches 1/1, bounds 5/5;
  all five bounds compiler float literals exact. Ordinary ./build.sh over
  both changed sources also passes 6/6 with source/string/float/import checks.
- The unchanged extent providers GeometryInfo_getMaxHeightBelowPosition.cpp
  and GeometryInfo_getMaxHeightAbovePosition.cpp pass strict preparation:
  4/4 rows and seven compiler float literals exact. No provider is edited.
- Same legacy local preview: pitches four blockers -> zero, 0/1 -> 1/1 clean,
  LINKED 0 -> 159 existing bytes. With both unchanged providers, 3/3 clean,
  census/preview LINKED 310 -> 469 bytes. This includes 159 repaired bytes;
  the two provider totals remain 101 and 209 bytes.
- Bounds controlled local preview: ten blockers -> six, removing fabs(float),
  sqrt(float), fabsf and sqrtf. 0/1 remains linkable, LINKED 0 -> 0 bytes.
  Its existing 1,440 real bytes remain blocked by GeometryNames plus
  Coord3D::zero, StringBase/AsciiString constructors and bfmeMin/bfmeMax copies.
  These need separate supported data/class/provider work; no unchanged
  blocked reconstruction was retried.
- New-variants admission, class gate, declared-definition check, CSV and
  whitespace checks pass. EH has no applicable rows. Converged data check
  finds zero second names and zero unjudged rows.

The results are +159 existing bytes in the legacy preview, eight fewer
surplus external COMDAT emitters, and +0 authored C++ bytes. Strict self
verification is proven. Closed-strict closure, actual link.exe placement,
and new measured census gains are not claimed. No maintainer-only runner
was started. Broad --refresh was not needed: each touched unit was compiled
through scoped strict preparation and refreshed together in the local preview.

Donor review: retained clean BFME1 checkout/gitlink
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Its System/GeometryInfoCalcPitches.cpp
and GeometryInfoCalcBoundingStuff.cpp were inspected; existing arithmetic and
class-purpose provenance is retained. The prior reviewed linking repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d supports suppressing surplus inline
emitters, but its BfmeStrVKI constructor/pin solution is inapplicable. No donor
code, type, address, pin or header was imported. The unchanged broader donor
scan recorded by the portal/concat repairs was not repeated.

Official BFME1 master fetched as 8a584a7e69e17263c8f3c35e80c91f4155554f53.
The due pointer update is held by codex-a44d-root's live reference submodule
file claim. Verified inputs and freshness success stamp were preserved;
the comparative full-byte update remains outstanding with that worker.
