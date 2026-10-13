# Shroud and light-environment math emitter repair

Source base: 4282cfcd7b. The runner's available index measures cb660e4d97
at 2026-10-13 04:02 UTC; object-proof.json records its SHA256. The committed
link_status.csv measures 2a20912cc9 and served discovery only. No census,
index, status or history was written, and no per-row data-back ranking was used.

Both units emit surplus MSVC math.h float overloads. Include the original
header with scoped static inline linkage, before wwmath.h in lightenvironment.
The matched operations already inline. Compiler flags, arithmetic, layouts,
identities, literals, external call bindings and ledger rows are unchanged.
No pin, alias, global, shared header, marker or optimization pragma was added.

Target evidence is the existing complete byte-verified rows, rather than a
new name or layout inference. Shroud's 21 rows retain their BFME2 20-player
layout and target-specific rotated polygon operations. Lightenvironment's
29 rows retain their existing light and matrix views. Existing donor naming
and layout uncertainties remain as recorded in the ledger.

Object comparison:

- Shroud removes exactly six COMDATs: cos(float), sin(float), floor(float),
  cosf, sinf and floorf. All 39 retained copies have identical raw bytes,
  sizes, relocation tuples, digests and retail verdicts.
- Lightenvironment removes exactly floorf. All 73 retained copies have the
  same complete byte-and-relocation facts.
- Neither unit adds a copy or changes strong definitions, undefined symbols
  or weak bindings. The proof records source/object hashes and aggregate
  hashes of the identical retained sets. Full snapshots and source backups
  remain under build/shroud-math-link-20261013 and build/lightenv-math-link-20261013.
- Unchanged TerrainLogicAmbientColorRva0027DA6A.cpp owns the 18-byte retail
  floorf; SlowDeathRandomForceRva0045D636.cpp owns the 17-byte retail cosf
  and sinf. All three providers have strict-current objects and are judged
  retail, with their raw bodies and relocation tuples retained in the proof.

Acceptance:

- Strict reusable self preparation passes before/after: Shroud 21/21 and
  lightenvironment 29/29. The unchanged provider pair passes 5/5.
- Ordinary ./build.sh over all four units passes 55/55 complete rows,
  one string, 44 float literals and 12 named imports; no skipped/baselined refs.
- Same-index ordinary legacy preview: Shroud findings 6 -> 2;
  lightenvironment 15 -> 14. Exactly five findings disappear; none is added.
  The final consumer/provider cohort remains 2/4 clean, LINKED 983 -> 983
  bytes, all from the unchanged providers. Both consumers remain blocked.
- Declared-definition and class checks pass. The one applicable EH graph
  is EXACT. New-variants admission passes. Shadow data has zero findings;
  enforced converged-data checks report zero second names or unjudged rows
  across eight addresses. Whitespace and CSV checks pass.

The verified improvement is seven removed external emitters and five fewer
legacy link findings, with zero new authored or preview linked bytes.
Self-strict verification is proven. Closed-strict closure, actual link.exe
placement and measured census gains are not claimed. No full census, link
cycle, nightly or boot runner was started.

Donor review: retained verified BFME1 checkout/gitlink
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Its ShroudManagerImpl008FBA40.cpp
and lightenvironment.cpp supply the existing semantic provenance; no donor
body, offset or identity was imported. Reviewed linking repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d supports suppressing surplus
inline emitters; its string constructor/pin mechanism is inapplicable.
The prior broader donor scan recorded by the concat/geometry repairs is reused.

Official BFME1 master was fetched as
3f8a13fd01f0082fa385ac0610bdef5bb107e804. Its overdue verified-pointer
update remains foreign-claimed by codex-a44d-root. Retained inputs and the
old freshness success stamp are preserved; comparative full verification
and pointer publication remain outstanding with the update owner.

Remaining blockers: Shroud's two unresolved polygon raster providers
Rva0073BFE0Raster and Rva0073C450Raster. Lightenvironment retains separate
WWMath, Matrix3D, LightClass, RGB/HSV and Reset provider/emitter findings;
all are listed in lightenv-link-after.txt. These require supported provider
or class repairs. Unchanged blocked reconstruction was not retried.
Unrelated untracked dumps and ZH sweep preparation are preserved.
