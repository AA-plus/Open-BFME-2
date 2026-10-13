# FloatUpdate home-unit math emitter repair

The source base is b59bc407ef. The available runner index measures cb660e4d97
at 2026-10-13 04:02 UTC; index-meta.json records its SHA256. The committed
link queue measures e181b4b6c5 and was used only for discovery. No census,
index, link-status/history, data-back artifact or maintainer-only runner was
created or changed.

FloatUpdate.cpp still emitted an unused non-retail sin(float) wrapper,
independently of the already repaired FloatUpdateUpdate.cpp. Include MSVC
math.h with scoped static inline linkage before PreRTS.h, restoring the inline
token afterward. The existing operations inline. No compiler flag, algorithm,
layout, ledger row, pin, global, marker, shared header or emission anchor changes.
Existing ZH provenance and its layout uncertainties remain unchanged. The
identity evidence is the existing byte-verified constructor and Matrix3D row;
no donor identity or layout was newly inferred.

Strict object evidence removes exactly sin(float), cosf and sinf COMDATs.
All 631 retained consumer copies and all 24 unchanged Apt provider copies
preserve their complete raw bytes, extents, relocation tuples, digests and
retail verdicts. Strong definitions, external undefined names and weak bindings
are identical. All seven normalized EH sections preserve bytes and relocation
facts. The unchanged provider owns the complete seven-byte retail sin(float)
and cos(float) bodies at 0x0002FBB0/0x0002FBC0 and has a strict-current receipt.
The other two removed wrappers were not conflicting findings in this index;
no external reference is added by their removal. object-proof.json binds the
comparisons to source/object/index hashes. Full before/after snapshots and
proof scripts remain under ignored build/float-home-math-link-20261013.

Acceptance:

- Bounded strict-current preparation before and after, then ordinary build.sh:
  22/22 matched rows across consumer and unchanged provider; three compiler
  float references, zero skipped/baselined string or import references.
- Same-index ordinary legacy preview: consumer findings 9 -> 8, exactly the
  competing sine copy disappears, no finding is added. The provider stays
  LINKS. Cohort remains 1/2 clean, LINKED 1332 -> 1332 bytes.
- Declared-definition and class checks pass. Five pre-existing marked
  unmatched definitions remain untouched. EH verifier has zero applicable
  matched EH graphs; complete object EH equality is separately proven.
- Enforced converged data: two sources, eight addresses, zero second names or
  unjudged rows. Ordinary shadow data: zero findings. New-variants admission,
  CSV and whitespace checks pass. Placement resweep reports zero bodies/pins.

This is three fewer unused external emitters and one fewer local legacy link
finding, with zero authored C++ and zero local linked-byte growth. Self-strict
byte verification is established. Closed-strict gains, actual link.exe
placement and measured census gains are not claimed.

Reused the unchanged broader linking donor scan and reviewed BFME1 repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d: removing surplus emitters applies;
its constructor pin/alias mechanism does not. No donor body was imported.
The clean verified BFME1 checkout/gitlink stays cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Official upstream was fetched as 49e35f6636748b0e1116265ce543de2f7aca0d39.
The previous foreign pointer reservation has expired; a probe claim was
released without changing inputs. The overdue old/new full-gate comparison
remains incomplete: the previous attempt stopped at the full-build lock with
5337 stale TUs, and no newer full baseline is available. This bounded repair
does not resolve that separate pointer-update task or record freshness success.

Remaining independent consumer findings are DISABLEDMASK_NONE,
BehaviorModule/UpdateModule crc, Drawable::setInstanceMatrix, the duplicate
non-retail FloatUpdate::update definition/selection and the selected Matrix3D
copy constructor. They require provider/class/ownership repairs. No unchanged
reconstruction was retried. Full names are in link-after.txt. Broader closure
and full-link verification remain outstanding. Unrelated untracked dumps and
ZH sweep preparation are preserved.
