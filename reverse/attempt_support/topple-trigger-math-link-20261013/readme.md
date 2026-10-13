# Topple and trigger-area math-wrapper link repair

Starting BFME2 revision: 482404dbaec9d33a6b4b9ae14fc5018d5f9b4986.
Available local index: cb660e4d97, 2026-10-13 04:02 UTC. Committed
link_status.csv instead measures 2a20912cc9 and served discovery only.
Neither census record nor the index was changed.

ToppleUpdate.cpp emits a non-retail atan2f header wrapper even though its
matched applyTopplingForce body calls retail's external 0x000422CD adapter.
Include the original MSVC math.h float overloads with static inline linkage,
following the verified geometry and portal repairs. Give only the header's
unused atan2f helper a private name while including it, then retain the real
external declaration. This leaves no private helper emitted or bound. The
first trial without that distinction inlined the adapter and lengthened
applyTopplingForce by 13 bytes; that trial was replaced, not banked as code.
No compiler flags, identities, types, class layouts or runtime semantics change.

A same-cause sweep finds ObjectSetTriggerAreaFlagsForChangeInPosition.cpp's
sin/cos copies. Include math.h there with the same scoped static inline
linkage. Its operations already inline and its complete 1016-byte body
remains unchanged. The particle-terrain collision unit is foreign-claimed;
AptCIHProceduralAllocation is already locally clean; neither was edited.
LivingWorldEyeTowerAim was probed, still has three separate Matrix3 emitter
blockers beyond atan2f, and was left for its own class/provider repair.

Target facts:

- Topple removes exactly seven surplus COMDATs, adding none. All 29 retained
  COMDATs have identical raw bytes, relocation tuples, sizes and digests.
  Strong definitions and weak bindings are unchanged. Undefined _atan2 is
  replaced by _atan2f: the removed wrapper formerly referenced _atan2,
  while the unchanged caller now binds the existing retail adapter provider.
- Trigger removes exactly four surplus COMDATs, adding none. All 17 retained
  COMDATs have identical raw bytes, relocation tuples, sizes and digests.
  Strong definitions, undefined externals and weak bindings are unchanged.
- Unchanged provider Rva000422A0.cpp has a strict-current 25-byte _atan2f
  COMDAT judged retail. Unchanged AptMathCallbacksBFME2.cpp has strict-current
  7-byte sin(float)/cos(float) COMDATs judged retail. Provider hashes and
  verdicts are retained in provider-proof.json. No pins or aliases were added.

Acceptance:

- Before/after strict reusable self verification: Topple 4/4, trigger 1/1.
  Unchanged provider pair passes 23/23 strict rows. Ordinary ./build.sh over
  all four units passes 28/28 with two strings, ten float literals and two
  named imports verified. Both applicable EH graphs are EXACT.
- Same legacy local preview: Topple blockers 2 -> 1; trigger 4 -> 2. No new
  blocker. Remaining Topple blocker is the selected Matrix3D copy constructor
  ??0Matrix3D@@QAE@ABV0@@Z. Trigger retains unresolved g_Va00DBD0F4 with
  its Rva002E373CHolder type and Rva004DD843::rva004DE2ED.
- Consumer/provider cohort remains 2/4 clean, LINKED 1402 -> 1402 bytes.
  Both consumer totals (2318 and 1014 real bytes) remain blocked. This is
  a verified reduction in link debt, +0 authored and +0 preview linked bytes.
- New-variants admission, declared-definition check, class gate, CSV and
  whitespace checks pass. Enforced converged-data check finds no second
  name or unjudged row across two sources and eight addresses. Shadow data
  still reports the pre-existing trigger global name and Topple function-local
  static guard name; their raw DIR32 relocation-bearing bodies are unchanged.

Self-strict verification is established. Closed-strict closure, actual link.exe
placement, and new measured census gains are not claimed. Only bounded explicit
strict preparation and normal local previews refreshed these objects; no full
census, link cycle, nightly or boot runner was started. Source/object snapshots
and full facts remain under build/topple-math-link-20261013 and the trigger
sibling directory. The final implementation removes 11 external emitters and
three legacy preview blockers while preserving every matched body.

Donor review: clean retained BFME1 gitlink/checkout cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Reviewed ToppleUpdateApplyTopplingForce.cpp and ToppleUpdateBfme.cpp:
the semantic donor and purpose are inherited, while BFME2's layouts and calls
remain target facts from the existing rows. Reviewed donor linking repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d: suppressing surplus non-retail
inline copies is applicable; its string constructor/pin solution is inapplicable.
The broader donor linking scan retained by the concat/geometry repairs was not
repeated without a relevant input change. No donor source or pin was imported.

Official BFME1 master fetched as 4fe1d0ff4462cabc7593685dc00559689d55da02.
The due verified-pointer update remains under codex-a44d-root's live
file:reference/open-bfme-1 claim. Verified inputs and success stamp were
preserved; comparative full verification and pointer publication remain with
that worker. Freshness was not marked successful.
