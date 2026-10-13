# Curve and Apt factory math emitter repair

Source base: 36c6bbbb17. The available runner census index measures cb660e4d97
at 2026-10-13 04:02 UTC; object-proof.json records its SHA256. The committed
link_status.csv instead measures 2a20912cc9 and served discovery only.
Neither index, census status nor history was changed. No per-row data-back
artifact or ranking was used.

Include the original MSVC math.h with scoped static inline linkage before
other headers in AptFactoryConstructors, vehiclecurve and bezier_segment.
These units already inline the matched operations. Preserve compiler flags,
source algorithms, class layouts, ABI, names, literals and ledger rows. No
shared header, global, pin, alias, marker or optimization pragma was added.

Target evidence is complete byte preservation of existing rows, rather
than a new identity or layout inference. VehicleCurve and Bezier donor
provenance remains as recorded. Apt factory PDB/MAP/native factory evidence
and later donor semantic guidance retain their original distinctions.

Object proof:

- Apt factory removes only cosf and sinf; all 54 retained COMDATs are exact
  before/after byte-and-relocation twins.
- Vehiclecurve removes six math COMDATs: acos(float), atan2(float,float),
  sqrt(float), acosf, atan2f and sqrtf. All 81 retained COMDATs are unchanged.
- Bezier removes sqrt(float) and sqrtf; all 23 retained COMDATs are unchanged.
- No unit adds or changes a retained COMDAT. Strong definitions, undefined
  externals and weak bindings remain identical in all three units. The proof
  records aggregate SHA256 digests of all 158 retained complete body and
  relocation records, plus source/object hashes and strict-current currency.
  Full snapshots and owned source/object backups remain under build/curve-factory-math-link-20261013.
- All 20 Apt associative exception sections have identical raw bytes and
  symbolic relocation facts. EH verdicts are identical before/after: eight
  EXACT and the existing baselined callback006F2760 one-byte .text$x mismatch
  at 0x007A9CA0. No new EH debt and no baseline edit.
- Unchanged SlowDeathRandomForceRva0045D636 owns retail's 17-byte cosf/sinf;
  unchanged Rva000422A0 owns retail's 25-byte atan2f. All three full bodies,
  relocations and retail verdicts are recorded from strict-current objects.
  The acos/sqrt copies have no retail address in the census; their removed
  first-copy conflicts do not establish a new retail identity.

Acceptance:

- Strict reusable self preparation before/after passes all 32 consumer rows,
  23 strings and 25 compiler float literals. The unchanged provider pair
  passes 6/6 rows. Final ordinary ./build.sh over all five paths passes 38/38,
  24 strings, 28 compiler float literals and one named import, with zero
  baselined or skipped reference checks.
- Same-index ordinary legacy link preview: factory findings 20 -> 18,
  vehiclecurve 21 -> 15, Bezier 12 -> 10. Exactly ten findings disappear;
  none is added. The final cohort remains 2/5 clean, LINKED 528 -> 528 bytes,
  all from unchanged providers. Consumer totals remain blocked.
- find_declared_unmatched, class_gate and link_check --new-variants pass.
  Enforced converged-data check: three sources, eight addresses, zero second
  names and zero unjudged rows. Shadow data: zero findings. check_csv and
  git diff --check pass.

This verifies ten fewer external emitters and ten fewer legacy link findings,
with +0 authored and +0 preview linked bytes. Self-strict verification is
proven. Closed-strict closure, actual link.exe placement and measured census
gains are not claimed. No full census, link cycle, nightly, boot or publisher
verification runner was started. Bounded strict preparation and the normal
local preview refreshed only explicitly owned units.

Donor review: retained clean BFME1 gitlink/checkout
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Its vehiclecurve.cpp and
bezier_segment.cpp supply the existing source provenance. Reviewed newer
linking repair d2e21369067f2f2c762c1c7ec2792c75f1ecf53d supports removing
surplus inline emitters; its string constructor/pin solution is inapplicable
here. The prior broader donor scan retained by the concat/geometry repairs
is reused; no donor body, address, layout or pin was imported.

Official BFME1 master was fetched as
3f8a13fd01f0082fa385ac0610bdef5bb107e804. The overdue verified-pointer
update remains foreign-claimed by codex-a44d-root. Retained inputs and the
old freshness success stamp are preserved; comparative full verification
and pointer publication remain outstanding with the update owner.

Remaining blockers: Apt base/vtable providers, factoryCreateString and data
owners; VehicleCurve PersistFactory/SaveLoad providers and separate WWMath,
Vector and Matrix emitters; Bezier's forward-iterator provider family,
Coord3D and STLport variants. Full remaining findings are in link-after.txt.
These require supported class/provider repairs; no unchanged blocked
reconstruction was retried. Preserved unrelated untracked dumps and ZH
sweep preparation are untouched.
