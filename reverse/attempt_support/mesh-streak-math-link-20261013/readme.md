# Mesh/streak local math emission repair

Source base: `f22ea1defc11d32d6cb97b1f90df9fa340aaa7ef`.
Available census index: `cb660e4d97`, 2026-10-13 04:02 UTC, SHA256
`4bc4fd38c27a025c8545b51f02fd25445391b93e51e964dfb8077a45aea9244e`.
The committed status sheet measures e181b4b6c5; it is not the index used here.
No census, status history, full link cycle or maintainer runner was started.

## Change and evidence

Both listed consumers include MSVC math.h first with its inline definitions
made TU-local, then restore the inline macro. Their matched operations already
inline. No shared headers, algorithms, compiler flags, data, layout, pins or
ledger rows change.

Before/after current objects remove only these surplus seven-byte COMDATs:

- meshgeometry.cpp: `_fabsf`, `_sqrtf`, `?fabs@@YAMM@Z`, `?sqrt@@YAMM@Z`.
- streakRender.cpp: `_fabsf`, `?fabs@@YAMM@Z`.

The index gives those emitters no retail address and rejects them by its legacy
first-copy rule. They are not six recovered retail functions. All 240 retained
COMDATs preserve bytes, relocations and retail verdicts; all 30 normalized EH
sections preserve bytes and symbolic relocations. Strong, undefined and weak
external facts are identical, so no new provider dependency is introduced.
`object-proof.json` binds these comparisons to source/object hashes and the
unchanged measurement index. Full snapshots and preparation backups remain in
ignored `build/mesh-streak-math-link-20261013/`.

## Acceptance

`link_check.py --prepare-current` separately passes before and after for each
unit: mesh 40/40 rows and nine floats; streak 21/21 rows and seven floats.
Both final strict-current receipts are valid. These establish self byte
verification, not a closed-strict link result.

`./build.sh` on both sources passes 61/61 rows and 16 floats, no baseline or
skipped rows. `eh_verify.py --sources-from sources.txt --json ...` gives 10/10
applicable EH graphs EXACT, no baseline/missing graphs, identical verdicts.
`check_csv.py`, `find_declared_unmatched.py` on both units, `class_gate.py`,
`data_check.py --converged` (eight addresses, zero second names/unjudged),
shadow data check (zero findings), `link_check.py --new-variants` and
`git diff --check` pass. Existing whitelisted unclaimed definitions were left
untouched. `place_bodies.py` on both sources finds zero bodies and zero pins.

Legacy `link_check.py` previews remove exactly four mesh and two streak
findings, without introducing another finding: 24 -> 20 and 34 -> 32.
The combined preview remains 0/2 clean and LINKED 0 -> 0 bytes; its exit 1
is the expected remaining-blocker result. No authored C++ bytes or measured
linked bytes grow. No closed-strict or actual link.exe gain is claimed.

## Donor review and remaining work

The retained BFME 1 pointer is cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Freshness fetch finds upstream 61eff927bb71d52854f461c9eeba2a731d679b1e;
its submodule file is claimed by codex-a44d-root. The pointer and successful-check
stamp are preserved pending that owner's verified update. The earlier donor
linking review was reused, and d2e21369067f2f2c762c1c7ec2792c75f1ecf53d
supports removing surplus inline wrappers; its BfmeStrVKI owner-pin mechanism
does not apply. Compare repairs 6906e0cddbf9dd70263e1a475665fb2afa5852a3
and 6ffd3f498c98872efbb0ad242c3afea4640e4ef5 are also inapplicable.
The donor Compute_Bounds and subdivision_util implementations have different
layouts. This repair imports no donor body, identity or layout claim; target
preservation rests on the current BFME 2 objects and gates.

Mesh still has constructor-iterator, Matrix3D/4, RefCount/MultiList, brute-force
collision and selected-owner blockers. Streak still has DynamicVBAccess and
WriteLock unresolveds, duplicate renderer bodies, Matrix/WWMath/RefCount,
texture/shader/DX8 and selected-owner blockers. Complete names remain in
`link-after.txt`. Those need independent supported repairs; broader closure
verification remains outstanding.
