# Camera math-wrapper emission repair

Source base: c352a3aacaeca798c83e28daf779e1a08d51ec3c. The available runner
index measures cb660e4d97 at 2026-10-13 04:02 UTC. Its metadata and SHA256
are recorded in object-proof.json. The committed link-status queue measures
e181b4b6c5 and was used for discovery only. No census/index/status/history
or per-row data-back artifact was generated or changed.

camera.cpp emitted surplus MSVC math.h atan2(float,float) and atan2f copies.
The first conflicts with the matched 11-byte provider at 0x001333F0 in
SlowDeathBehavior.cpp; the second differs from the matched 25-byte provider
at 0x000422CD in Rva000422A0.cpp. Both unchanged providers prepare with strict
reusable receipts and are independently judged retail. Their full bodies,
relocations and hashes are included in the proof.

Include the original math.h with scoped static inline linkage before the
camera's first math-consuming header. Existing operations already inline;
the repair removes only the two unused external copies. Compiler flags,
algorithms, layouts, identities, literal values, ledger rows and existing
emission anchors remain unchanged. No pin, alias, global, shared header,
marker, new class view or optimization pragma is introduced.

The target evidence is the complete existing byte-verified rows and actual
provider bodies, rather than a new identity or layout inference. Existing
camera donor provenance remains intact. Reviewed BFME1 linking repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d: its suppress-surplus-emission
principle applies, while its string-constructor and alias-scaffold mechanism
does not. BFME2's Rva00106F82TangentField and prior shroud/light-environment
repairs establish the local header technique. No donor body was imported.
The unchanged broader donor scan recorded by those repairs was reused.

Official BFME1 master was fetched as
49e35f6636748b0e1116265ce543de2f7aca0d39. The clean verified checkout and
gitlink remain cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. The foreign
file:reference/open-bfme-1 claim held by codex-a44d-root owns the overdue
comparative update. Retained verified inputs and the prior success stamp;
no pointer-update success is claimed.

Acceptance:

- Before/after bounded strict preparation and final ordinary ./build.sh
  pass 64/64 matched rows across camera and both providers, 43 compiler float
  references and one named import; zero baselined/skipped references.
- Object comparison removes exactly the two wrappers. All 217 retained
  COMDATs preserve raw bytes, extents, relocation tuples, digests and retail
  verdicts. Strong definitions, undefined names and weak bindings are identical.
  All six normalized EH sections preserve complete bytes and relocation facts;
  the EH verifier independently reports both applicable graphs EXACT.
- Same-index ordinary legacy preview: camera findings 46 -> 44, exactly
  the atan2f losing copy and selected atan2 finding removed, none added.
  SlowDeathBehavior retains its 24 independent findings and Rva000422A0
  remains LINKS. Cohort stays 1/3 clean and LINKED 70 -> 70 bytes.
- Declared-definition, class, new-variants, CSV, converged-data, ordinary
  shadow data and whitespace checks all pass; checks.json records exit codes.

This is a verified removal of two competing emitters and two local link
findings, with zero new authored C++ or legacy preview linked bytes.
Self-strict byte receipts are established; closed-strict closure, actual
link.exe placement and measured census gains are not claimed. No maintainer
link cycle, census build/measure/history, nightly or boot runner was started.

Sibling reassessment: sphereobj.cpp, vehiclecurve.cpp and meshgeometry.cpp
already use the same local-math repair. gridcull.cpp's current local preview
has only its independent CullLink deleting-destructor and OBBox extent
selected-provider findings, so no math-header change was made there.

Remaining camera blockers include Camera Class_ID ownership, Matrix3D,
Matrix4, Frustum, RenderObj, RefCount and CollisionMath providers/emission
variants; the after transcript lists all 44 findings. These need supported
class/provider repairs, not another trial of the repaired math copies.
The provider cohort's broader closure and BFME1 comparative update remain
outstanding. Source/object backups and the proof script are retained under
ignored build/camera-math-link-20261013. Unrelated untracked preparation
was preserved.
