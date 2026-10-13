# Link-seat rejected trials and handoff

Checkout 1d21a3da40; available census d753dedd98 (2026-10-12 22:16).
The attached transcripts preserve the ignored build evidence cited by this
session's three re_log blocked records. All trial edits were reverted and all
trial file/RVA claims released. No gain is claimed for these candidates.

## PlayerList getter

PlayerList_getNthPlayer.cpp and PlayerListRva002A8008.cpp emit duplicate
strong definitions of getNthPlayer at 0x002A7A29. Both copies reproduce retail.
Making both definitions inline __declspec(noinline) allows merging, but
MSVC delays their compiler register summaries: five of eight rows fail,
including EDX-live loops and newGame's side-info register allocation. Both
files were restored verbatim; the restored normal gate passes 8/8. This needs
an emission repair retaining the native earlier-callee register contracts.

## Two deleting-destructor providers

FamilyDeletingDtors_Rva00587F69.cpp and FamilyDeletingDtors_muse-3298.cpp
emit wrong dummy destructors competing with native providers in
Rva00587F69Dtor.cpp and PartTheHeavensUpdateModuleDataDtor.cpp. Initial
four-source strict preparation passes 9/9, but the native novtable classes
do not emit the scalar deleting symbols at 0x00587F4D and 0x004ACCB1.
A delete-p helper appended to each native provider preserves all seven
provider rows but still does not emit the required scalar symbol, so rehoming
cannot proceed. Both helpers were removed; the restored four-source gate
passes 9/9. A supported vtable/deleting-emission or canonical-class repair
is required. The Rva provider also contains older gen-alias debt, so its class
identity is not assumed coherent. No dummy destructor was retained as a fix.

## Other leads assessed without changes

- W3DModelDrawGetCurrentBonePositions.cpp: Matrix3D copy-constructor blocker
  is the same unresolved folded Vector4 callee/import issue already recorded
  at 0x0006645C. Existing import shim exclusions cover by-value returns;
  no changed dependency or boundary justified another trial.
- FireWeaponUpdateBehaviorDtor.cpp / FireWeaponUpdateCtor.cpp: both providers
  prepare strictly and preserve 5/5 rows. name_globals --dry-run finds no
  supported replacement for secondary vtable 0x00C4C18C; its named primary
  vtable does not establish a secondary-table identity or provider.
- RampageBehaviorModuleDataCtor.cpp: name_globals --dry-run finds no named
  provider for vtable 0x00C40EF8.
- Rva004FA738ListenerWalks.cpp already uses the ledger globals; the old
  address-blocker ranking is stale for the current source.

BFME 1 repairs d3f9000fe08615a100e844adfff57fa4a39cd615,
5093777e8373a843f1f1ccfc648601ae78351aaa and
0835ab92bef30e3303e729a0ce09cf591368d0cd were reviewed for applicable provider
removal, inline reconciliation and canonical global principles. Their
classes, layouts and target addresses were not copied. These failed or
unsupported local applications are handed off pending new evidence. The
link-repair lane as a whole is not declared exhausted.
