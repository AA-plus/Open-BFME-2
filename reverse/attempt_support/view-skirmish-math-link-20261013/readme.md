# View/skirmish math emitter repair

Source base: f0d6aa14003c365705a41b38d15baed476320dd6. The runner index measures
cb660e4d97 at 2026-10-13 04:02 UTC; its SHA256 is in
index-meta.json. The committed link queue measures e181b4b6c5 and was used
only for discovery. No census, link status/history, data-back artifact or
maintainer-only runner was generated or changed.

## Change and target evidence

W3DView.cpp and AISkirmishPlayer.cpp now include MSVC math.h with its inline
definitions scoped static, restoring the inline token immediately afterward.
The existing matched operations already inline. No algorithm, compiler flag,
layout, literal, pin, ledger row, global, shared header or emission anchor changes.
Existing donor provenance remains in each source.

The strict-current before/after objects remove ten unused external copies:
W3DView removes float cos/sin/sqrt overloads and _cosf/_sinf/_sqrtf;
AISkirmishPlayer removes float cos/sin overloads and _cosf/_sinf.
Only four copies were conflicting findings in the available index: the two
cos/sin overloads in each consumer. Those overloads promote via a double CRT
call; the unchanged AptMathCallbacksBFME2 provider emits the complete verified
seven-byte x87 cos/sin bodies at 0x0002FBC0/0x0002FBB0.
The extra removed _cosf/_sinf copies were retail twins, not bad bodies; they
and both sqrt copies have other providers in the index. External undefined
names do not change. The separate ledger CRT float owner's receipt is stale,
and it was not prepared; no broader current provider closure is claimed.

All 145 retained consumer COMDATs plus all 24 unchanged Apt provider COMDATs
preserve complete raw bytes, extents, relocation tuples, digests and retail
verdicts. Strong, undefined and weak external facts remain identical.
All 12 normalized EH sections remain identical. object-proof.json binds these
comparisons to the source/object/index hashes. Complete snapshots, source/object
backups and the proof script remain under ignored build/view-skirmish-math-link-20261013.

## Acceptance and limits

- Bounded link_check.py --prepare-current before and after: 53/53 rows across
  the explicit two consumers and provider, valid reusable strict receipts.
  Ten data rows, 23 literals plus three empty strings and 32 floats pass;
  no baselined or skipped string references.
- Final ./build.sh on that cohort: 53/53 rows, same constants/data checks.
- eh_verify.py: all six applicable graphs EXACT, zero missing or baselined.
- find_declared_unmatched.py and class_gate.py on both consumers pass;
  AISkirmishPlayer's existing permitted unclaimed definition is untouched.
- Converged data: three sources, eight addresses, zero second names/unjudged;
  shadow data: both consumers, zero findings. check_csv.py, new-variants
  admission and git diff --check pass. place_bodies.py: zero bodies/pins.
- Same-index legacy preview: W3DView findings 7 -> 5; AISkirmishPlayer 8 -> 6;
  unchanged Apt provider stays LINKS. Exactly four findings disappear and
  none are added. Cohort remains 1/3 clean, LINKED 1332 -> 1332 bytes.

This is a verified emitter/link-finding repair, with zero authored C++ gain
and zero local legacy linked-byte gain. Self-strict byte verification is
established. Closed-strict gains, actual link.exe placement and future census
improvements are not claimed.

## Donor review and handoff

Reviewed BFME1 d2e21369067f2f2c762c1c7ec2792c75f1ecf53d: suppression of
surplus inline copies applies; its constructor pin/alias mechanism does not.
Reused the unchanged broader linking donor review from the prior camera/math
pass; the fetched 6906e0cdd/6ffd3f498 string comparison repairs do not address
this supported math cause. No donor identity, layout or body was newly imported.
Official BFME1 master was fetched as 49e35f6636748b0e1116265ce543de2f7aca0d39;
the clean verified checkout/gitlink remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Its overdue comparative update remains under foreign file:reference/open-bfme-1
claim codex-a44d-root. The verified inputs and success stamp were preserved;
no freshness success is claimed.

W3DView still needs CameraShakerSystem and rva00312118 providers plus the
CameraClass viewport copies/selected owner repair. AISkirmishPlayer still needs
TeamInQueue, TeamFactory/findTeam, queue prepend, BuildListInfo/template-name,
selectTeamToReinforce and getNext emission repairs. The full names are in
link-after.txt. These are independent causes, not further math trials.
Other math-only queued units checked (Ratios, CylindricalEmissionVelocity,
Rva003FA781, CloudArcs, AIGateTrigger, FakePathfindPortal, StrafeArea) already
preview LINKS with current objects, so their stale index findings were not
retried. Broader closure/full-link verification remains outstanding.
