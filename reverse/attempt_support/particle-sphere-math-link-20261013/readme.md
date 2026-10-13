# Particle-buffer and sphere local math emission repair

Source base: `db9c7faa32`.
Available census index: `cb660e4d97`, 2026-10-13 04:02 UTC, SHA256
`4bc4fd38c27a025c8545b51f02fd25445391b93e51e964dfb8077a45aea9244e`.
The committed status sheet measures `e181b4b6c5`; it is not the index used here.
No census, history, full link cycle or maintainer runner was started.

## Change and evidence

Both consumers include MSVC math.h first with its inline definitions made
TU-local, then restore the inline macro. Matched operations already inline.
No shared headers, compiler flags, algorithms, class layouts, data, ledger
rows, pins or baselines change.

The paired current objects remove these surplus external COMDATs:

- part_buf.cpp: `_fabsf`, `?fabs@@YAMM@Z`.
- sphereobj.cpp: `_fabsf`, `?fabs@@YAMM@Z`, `_cosf`, `_sinf`.

These wrappers have no retail address in the available index. Its legacy
first-copy rule rejects them; they are not six recovered retail functions.
All 779 retained COMDATs preserve raw bytes, relocations, sizes, digests and
retail verdicts. All 98 normalized EH sections preserve bytes and symbolic
relocations. Strong, undefined and weak external facts are identical; no
provider dependency is added or removed. The adjacent object-proof.json binds
these assertions to source/object hashes and the measurement index. Complete
snapshots and source backups remain in ignored
build/particle-buffer-math-link-20261013/.

## Acceptance and limits

`link_check.py --prepare-current` passes separately before and after for both
units, establishing self-strict verification and current reusable receipts.
`./build.sh` on the final cohort passes 151/151 rows, 11 string literals and
144 compiler float literals, with zero baselines or unverified/skipped refs.
`eh_verify.py` gives 13/13 applicable graphs EXACT, zero baseline/missing graphs;
sphere has no applicable row EH graph. Retained object EH data is also identical.

`check_csv.py`, `find_declared_unmatched.py` on both sources, `class_gate.py`,
`data_check.py --converged` (eight addresses, zero second names/unjudged), shadow
data check (zero findings), `link_check.py --new-variants` and `git diff --check`
pass. Existing whitelisted unclaimed definitions remain untouched.
`place_bodies.py` on each unit finds zero bodies and zero pins.

Paired local legacy previews remove exactly two particle-buffer and four
sphere findings, with no new finding: 54 -> 52 and 96 -> 92. Both remain
unclean: combined LINKED 0 -> 0 bytes. Exit 1 of the legacy preview is the
expected remaining-blocker result. Authored C++ bytes grow by zero. No
closed-strict, measured census or actual link.exe gain is claimed.

## Reference review and handoff

Retained verified BFME 1 input: cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Freshness fetch finds official upstream b870d563b7f4e8b58f433635a39783fb0d7d55cb;
the submodule file remains claimed by codex-a44d-root. Pointer and successful
check stamp are preserved; that owner's comparative update verification is
outstanding. Prior dedicated-lane donor review is reused. BFME 1 repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d supports suppressing surplus wrappers,
but its string constructor owner-pin mechanism is inapplicable. The newer
b870d563b compareNoCase self-contained repair is also inapplicable to this math
cause. No donor body, identity or layout claim is imported; the proof is current
BFME 2 object preservation and the target byte gate.

The supported-cause sweep finds mapper.cpp, GridTextureMapperClassInitialize.cpp
and TextureMapperFXShaderConvert.cpp already repaired, as are meshgeometry.cpp
and streakRender.cpp. collisionmanager_data.cpp already hides its fabs helpers.
These stale-index findings were not retried.

Particle-buffer still has RefCount/RenderObj and container COMDAT/selected-owner
blockers. Sphere additionally has Quaternion duplicate, matrix/animation/renderer
blockers and unresolved DynamicVBAccess/WriteLock, PredictiveLODOptimizer and
VisRasterizer dependencies. Exact names are in link-after.txt and
sphere-link-after.txt. Broader closure verification remains outstanding.
