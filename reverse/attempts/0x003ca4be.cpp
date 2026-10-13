// ?executeAction@ScriptActions@@UAEXPAVScriptAction@@@Z
// partial score=0.9571488135077614 date=2026-10-14
// ?executeAction@ScriptActions@@UAEXPAVScriptAction@@@Z
// partial score=0.9196112177903024 date=2026-10-13
// cl: /G7 /arch:SSE /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /I.
// stlport
// Partial, not recovery credit. Native switch and donor provenance/residue:
// reverse/attempt_evidence/executeaction/report.txt.
#include "reverse/attempt_evidence/executeaction/owner_context.inc"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#define TEXT(n) (pAction->getParameter(n)->getString())
#define INTEGER(n) (pAction->getParameter(n)->getInt())
#define REAL(n) (pAction->getParameter(n)->getReal())
#define PARAM(n) (pAction->getParameter(n))
#define INLINE_TEXT(n) (pAction->getParameterInline(n)->getString())
#define INLINE_INTEGER(n) (pAction->getParameterInline(n)->getInt())
#define INLINE_REAL(n) (pAction->getParameterInline(n)->getReal())
#define INLINE_PARAM(n) (pAction->getParameterInline(n))
void ScriptActions::executeAction(ScriptAction *pAction)
{
if (!pAction->isEnabled())
return;
switch (pAction->getActionType()) {
case 386:
{
doBuildBuildingOnFoundation(INLINE_TEXT(0), *(AsciiString const *)(INLINE_PARAM(1)));
return;
}
case 0:
{
TheScriptEngine->AppendDebugMessage(INLINE_TEXT(0), true);
return;
}
case 104:
{
TheScriptEngine->AppendDebugMessage(INLINE_TEXT(0), false);
return;
}
case 12:
{
Rva003BE9DBSet(INLINE_TEXT(0), INLINE_REAL(1));
return;
}
case 13:
{
Rva003BEA10Do(&INLINE_TEXT(0), (void *)(&INLINE_TEXT(1)));
return;
}
case 544:
{
Rva003BEB01Do(&INLINE_TEXT(0), (void *)(&INLINE_TEXT(1)));
return;
}
case 564:
{
rva003C7914(INLINE_TEXT(0), INLINE_PARAM(1));
return;
}
case 455:
{
Rva003BEBD6Do(&INLINE_TEXT(0));
return;
}
case 38:
{
Rva003C7A30Do(INLINE_PARAM(0), (int)(&INLINE_TEXT(1)));
return;
}
case 546:
{
Rva003C7AF3Do(INLINE_PARAM(0), (int)(&INLINE_TEXT(1)));
return;
}
case 37:
{
doSetTeamState(INLINE_TEXT(0), INLINE_TEXT(1));
return;
}
case 490:
{
Rva003BECCDSet(INLINE_TEXT(0), INLINE_TEXT(1), (INLINE_INTEGER(2) != 0));
return;
}
case 36:
{
doTeamFollowWaypoints(INLINE_TEXT(0), INLINE_TEXT(1), (INLINE_INTEGER(2) != 0), (INLINE_INTEGER(3) != 0));
return;
}
case 545:
{
doTeamAttackMoveFollowWaypoints(INLINE_TEXT(0), INLINE_TEXT(1), (INLINE_INTEGER(2) != 0), (INLINE_INTEGER(3) != 0));
return;
}
case 285:
{
doTeamFollowWaypointsExact(INLINE_TEXT(0), (int)(&INLINE_TEXT(1)), (INLINE_INTEGER(2) != 0));
return;
}
case 286:
{
doNamedAttackFollowWaypoints(INLINE_PARAM(0), INLINE_TEXT(1));
return;
}
case 249:
{
doTeamFollowSkirmishApproachPath(INLINE_TEXT(0), INLINE_TEXT(1), (INLINE_INTEGER(2) != 0));
return;
}
case 253:
{
doTeamMoveToSkirmishApproachPath(INLINE_TEXT(0), INLINE_TEXT(1));
return;
}
case 34:
{
rva003C7BBB(INLINE_TEXT(0), INLINE_TEXT(1), false);
return;
}
case 444:
{
rva003C7BBB(INLINE_TEXT(0), INLINE_TEXT(1), true);
return;
}
case 499:
{
doNamedSetTeam(INLINE_PARAM(0), INLINE_TEXT(1));
return;
}
case 290:
{
Rva003BB163Set(INLINE_TEXT(0), (int)(&INLINE_TEXT(1)));
return;
}
case 419:
{
Rva003BB1A4Grant(INLINE_TEXT(0), INLINE_TEXT(1));
return;
}
case 180:
{
Rva003BF9FADo(INLINE_TEXT(0), INLINE_REAL(1), AsciiString::TheEmptyString);
return;
}
case 181:
{
Rva003BF9FADo(INLINE_TEXT(0), INLINE_REAL(1), INLINE_TEXT(2));
return;
}
case 7:
{
doPlaySoundEffect(INLINE_TEXT(0));
return;
}
case 417:
{
Rva003BA96F(INLINE_REAL(0), INLINE_REAL(1), INLINE_REAL(2), INLINE_REAL(3), INLINE_REAL(4));
return;
}
case 441:
{
Rva003BA9AF((int)(&TEXT(0)));
return;
}
case 442:
{
Rva003BA9CA((int)(&TEXT(0)));
return;
}
case 443:
{
Rva003BA9E5();
return;
}
case 437:
{
Rva003BA9FA(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 438:
{
Rva003BAA2D(REAL(0));
return;
}
case 14:
{
Rva003BAAE4(TEXT(0), REAL(1), REAL(2), REAL(3), REAL(4));
return;
}
case 117:
{
Rva003BAD15(TEXT(0), REAL(1), REAL(2), TEXT(3));
return;
}
case 120:
{
Rva003BAB7A(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 389:
{
Rva003BABCB(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 121:
{
Rva003BAC1C(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 346:
{
Rva003BAC6D(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 122:
{
Rva003BAA46(PARAM(0), (PARAM(1) && INTEGER(1) != 0), REAL(2));
return;
}
case 135:
{
Rva003BAAD6();_ReadWriteBarrier();
return;
}
case 123:
{
Rva003BACCA((Parameter *)(INTEGER(0)));
return;
}
case 32:
{
Rva003C4D5CDo(&TEXT(0));
return;
}
case 31:
{
Rva003C4DC2Do(TEXT(0));
return;
}
case 17:
{
Rva003BB0C7Set((int)(&TEXT(0)), REAL(1), REAL(2), REAL(3), REAL(4), REAL(5), 0);
return;
}
case 390:
{
Rva003BB0C7Set((int)(&TEXT(0)), REAL(1), REAL(2), REAL(3), REAL(4), REAL(5), 1);
return;
}
case 550:
{
Rva003BB141Notify(*(StringBase<char> const *)(&TEXT(0)));
return;
}
case 18:
{
Rva003BAECA(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 529:
{
Rva003BAF1D(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 340:
{
Rva003BAF95(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 185:
{
Rva003BAFE8(PARAM(0), REAL(1), REAL(2), REAL(3), REAL(4), REAL(5));
return;
}
case 210:
{
Rva003BB05FSet((int)(&TEXT(0)), REAL(1), REAL(2), REAL(3), (INTEGER(4) != 0));
return;
}
case 19:
{
Rva003C4E28Find(TEXT(0), REAL(1), REAL(2), REAL(3));
return;
}
case 35:
{
Rva003BAE04();
return;
}
case 21:
{
((ScriptActionViewSlots *)TheTacticalView)->slot35();
return;
}
case 28:
{
((ScriptActionViewSlots *)TheTacticalView)->slot36();
return;
}
case 26:
{
((ScriptActionViewSlots *)TheTacticalView)->slot31(REAL(0), REAL(1), REAL(2));
return;
}
case 27:
{
((ScriptActionViewSlots *)TheTacticalView)->slot34(REAL(0), REAL(1), REAL(2));
return;
}
case 29:
{
((ScriptActionViewSlots *)TheTacticalView)->slot33(INTEGER(0));
return;
}
case 30:
{
((ScriptActionViewSlots *)TheTacticalView)->slot32(INTEGER(0));
return;
}
case 22:
{
((ScriptActionViewSlots *)TheTacticalView)->slot56(INTEGER(0));
return;
}
case 24:
{
((ScriptActionAudioSlots *)TheAudio)->slot16(2, 1, 1);
return;
}
case 25:
{
((ScriptActionAudioSlots *)TheAudio)->slot17(2, 1, 1);
return;
}
case 11:
{
doPlaySoundEffectAt(TEXT(0), TEXT(1));
return;
}
case 510:
{
doPlaySoundEffectAtTeam(TEXT(0), TEXT(1));
return;
}
case 334:
{
((ScriptActionGlobalData *)TheWritableGlobalData)->m_value950 = REAL(0);
return;
}
case 327:
{
((Rva003BD598 *)this)->rva003BD598();
return;
}
case 3:
{
((Rva003BE5C9 *)this)->rva003C3B4A();
return;
}
case 511:
{
((Rva003BE5C9 *)this)->rva003BE5C9();
return;
}
case 4:
{
((Rva003BE6CB *)this)->rva003BE6CB();
return;
}
case 299:
{
((Rva003BE7ED *)this)->rva003BE7ED();
return;
}
case 23:
{
Coord3D temp36; PARAM(2)->getCoord3D(&temp36);
doCreateObject(AsciiString::TheEmptyString, TEXT(0), TEXT(1), (Coord3D *)(&temp36), REAL(3));
return;
}
case 33:
{
doTeamAttackTeam(TEXT(0), TEXT(1));
return;
}
case 39:
{
Rva003C82EADo(PARAM(0), PARAM(1));
return;
}
case 40:
case 590:
{
createUnitOnTeamAt(TEXT(0), TEXT(1), TEXT(2), TEXT(3));
return;
}
case 41:
{
createUnitOnTeamAt(AsciiString::TheEmptyString, TEXT(0), TEXT(1), TEXT(2));
return;
}
case 42:
{
Rva003BB1FFAttack(PARAM(0), TEXT(1));
return;
}
case 43:
{
rva003BEDD1(TEXT(0), TEXT(1));
return;
}
case 44:
{
Rva003BB233Set(TEXT(0), INTEGER(1));
return;
}
case 45:
{
Rva003BB274Ai(PARAM(0), INTEGER(1));
return;
}
case 46:
{
updateTeamSetAttitude(TEXT(0), INTEGER(1));
return;
}
case 235:
{
doNamedSetRepulsor(*(AsciiString const *)(PARAM(0)), (INTEGER(1) != 0));
return;
}
case 236:
{
doTeamSetRepulsor(TEXT(0), (INTEGER(1) != 0));
return;
}
case 47:
{
doNamedAttackArea(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 48:
{
doNamedAttackAreaForSeconds(*(AsciiString const *)(PARAM(0)), TEXT(1), INTEGER(2));
return;
}
case 49:
{
doNamedAttackTeam(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 50:
{
doTeamAttackArea(TEXT(0), TEXT(1));
return;
}
case 51:
{
doTeamAttackNamed(TEXT(0), *(AsciiString const *)(PARAM(1)));
return;
}
case 52:
{
rva003C8482(TEXT(0));
return;
}
case 53:
{
doNamedEnterNamed(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 54:
{
doTeamEnterNamed(TEXT(0), TEXT(1));
return;
}
case 55:
{
doNamedExitAll(*(AsciiString const *)(PARAM(0)));
return;
}
case 56:
{
doTeamExitAll(TEXT(0));
return;
}
case 57:
{
doNamedFollowWaypoints(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 547:
{
doNamedFollowWaypointsExact(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 58:
{
doNamedGuard(*(AsciiString const *)(PARAM(0)));
return;
}
case 59:
{
doTeamGuard(TEXT(0));
return;
}
case 206:
{
Rva003BF71EDo(TEXT(0), TEXT(1));
return;
}
case 207:
{
Rva003BF7ACDo(TEXT(0), PARAM(1));
return;
}
case 208:
{
AsciiString temp8("");
Rva003BF813Do(TEXT(0), TEXT(1), temp8);
return;
}
case 487:
{
Rva003BF813Do(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 452:
{
doUnitGuardPosition(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 453:
{
Rva003C89D1Guard(PARAM(0), PARAM(1));
return;
}
case 454:
{
AsciiString temp16("");
Rva003C8A15Do(PARAM(0), TEXT(1), temp16);
return;
}
case 486:
{
Rva003C8A15Do(PARAM(0), TEXT(1), TEXT(2));
return;
}
case 60:
{
Rva003C8A95Do(PARAM(0));
return;
}
case 61:
{
Rva003BF8B4Hunt(TEXT(0));
return;
}
case 282:
{
doTeamHuntWithCommandButton(TEXT(0), TEXT(1));
return;
}
case 99:
{
Rva003BB29D(TEXT(0));
return;
}
case 468:
{
Rva003BF903Do(TEXT(0), (int)(&TEXT(1)));
return;
}
case 62:
{
Rva003BB2DFClear(TEXT(0));
return;
}
case 63:
{
Rva003BB31DClear(TEXT(0));
return;
}
case 64:
{
Rva003BB35B(TEXT(0), (int)(&TEXT(1)));
return;
}
case 65:
{
Rva003BB39EClear(TEXT(0));
return;
}
case 66:
{
Rva003BB3DCSet(TEXT(0));
return;
}
case 67:
{
Rva003BB41A(TEXT(0), (int)(&TEXT(1)));
return;
}
case 257:
{
Rva003BF96FDo(TEXT(0), TEXT(1));
return;
}
case 68:
{
Rva003BB45DSet(TEXT(0));
return;
}
case 70:
{
Rva003BF9C8Do(TEXT(0));
return;
}
case 71:
{
Rva003BFA77Do(*(Parameter const *)(PARAM(0)), INTEGER(1));
return;
}
case 436:
{
doKillHordeMembers(PARAM(0), REAL(1));
return;
}
case 72:
{
Rva003BB49BDestroy(PARAM(0));
return;
}
case 73:
{
Rva003BFAC3Set(TEXT(0), 0);
return;
}
case 330:
{
Rva003BFAC3Set(TEXT(0), 1);
return;
}
case 115:
{
Rva003C8ABFDo(TEXT(0), TEXT(1));
return;
}
case 237:
{
Rva003C8B62Do(TEXT(0));
return;
}
case 238:
{
Rva003BFAF4Do(TEXT(0));
return;
}
case 562:
{
Rva003BFB8CDo(TEXT(0), INTEGER(1));
return;
}
case 239:
{
Rva003BFC27Do(TEXT(0));
return;
}
case 563:
{
Rva003BFCBFDo(TEXT(0), INTEGER(1));
return;
}
case 116:
{
Rva003C8BCBDo(TEXT(0), TEXT(1));
return;
}
case 74:
{
Rva003BB4BDApply(PARAM(0), REAL(1), REAL(2), REAL(3), (int)(&TEXT(4)));
return;
}
case 75:
{
Rva003BB4F7Kill(PARAM(0));
return;
}
case 76:
{
Rva003BFD5ASet(TEXT(0));
return;
}
case 77:
{
Rva003BB518Clear(TEXT(0));
return;
}
case 78:
{
doDisplayText(TEXT(0));
return;
}
case 219:
{
doDisplayCinematicText(TEXT(0), TEXT(1), INTEGER(2));
return;
}
case 79:
{
doCameoFlash(TEXT(0), INTEGER(1));
return;
}
case 80:
{
Rva003BB5B7Do(PARAM(0), INTEGER(1), (RGBColor *)(0));
return;
}
case 81:
{
Rva003BFF50Do(&TEXT(0), INTEGER(1), (RGBColor *)(0));
return;
}
case 246:
{
RGBColor color; color.red = color.green = color.blue = 1.0f;
Rva003BB5B7Do(PARAM(0), INTEGER(1), &color);
return;
}
case 252:
{
doNamedCustomColor(PARAM(0), INTEGER(1));
return;
}
case 247:
{
RGBColor color; color.red = color.green = color.blue = 1.0f;
Rva003BFF50Do(&TEXT(0), INTEGER(1), &color);
return;
}
case 82:
{
Rva003BFFECDo(TEXT(0), (INTEGER(1) != 0));
return;
}
case 83:
{
Rva003BB61E(TEXT(0));
return;
}
case 84:
{
doSoundPlayFromNamed(TEXT(0), *(AsciiString const *)(PARAM(1)));
return;
}
case 85:
{
doSpeechPlay(TEXT(0), (INTEGER(1) != 0));
return;
}
case 86:
{
bfmeLinkObjectsA70((void *)(&TEXT(0)), (void *)(&TEXT(1)));
return;
}
case 87:
{
Rva003BD884Set(PARAM(0), &TEXT(1));
return;
}
case 315:
{
Rva003BB6C0Clear(TEXT(0));
return;
}
case 317:
{
Rva003BB700(true);
return;
}
case 318:
{
Rva003BB700(false);
return;
}
case 88:
{
Rva003BB713Set(TEXT(0), (Object *)(INTEGER(2)), TEXT(1));
return;
}
case 90:
{
Coord3D temp36; PARAM(0)->getCoord3D(&temp36);
Rva003BB76EDo((Coord3D *)(&temp36), (void *)(INTEGER(1)));
return;
}
case 217:
{
Rva003BB79DDo(PARAM(0), (void *)(INTEGER(1)));
return;
}
case 218:
{
Rva003C00CEDo(&TEXT(0), (void *)(INTEGER(1)));
return;
}
case 91:
{
Rva003BB7E2();
return;
}
case 92:
{
Rva003BB7F0();
return;
}
case 530:
{
doNamedEnableCameraFading(PARAM(0), (INTEGER(1) != 0));
return;
}
case 295:
{
doNamedEnableStealth(*(AsciiString const *)(PARAM(0)), (INTEGER(1) != 0));
return;
}
case 296:
{
doTeamEnableStealth(TEXT(0), (INTEGER(1) != 0));
return;
}
case 432:
{
rva003BBD61(*(AsciiString const *)(PARAM(0)), (INTEGER(1) != 0));
return;
}
case 433:
{
rva003C05DE(TEXT(0), (INTEGER(1) != 0));
return;
}
case 93:
{
Rva003BB8EDReveal(TEXT(0), REAL(1), TEXT(2));
return;
}
case 552:
{
rva003C013C(TEXT(0), TEXT(1));
return;
}
case 105:
{
Rva003BB94CReveal(TEXT(0));
return;
}
case 233:
{
Rva003BB9C6Reveal(true, TEXT(0));
return;
}
case 234:
{
Rva003BB9C6Reveal(false, TEXT(0));
return;
}
case 149:
{
Rva003BBA59Reveal(TEXT(0));
return;
}
case 94:
{
doTeamAvailableForRecruitment(TEXT(0), (INTEGER(1) != 0));
return;
}
case 96:
{
doMergeTeamIntoTeam(TEXT(0), TEXT(1));
return;
}
case 250:
{
doIdleAllPlayerUnits(AsciiString::TheEmptyString);
return;
}
case 251:
{
doResumeSupplyTruckingForIdleUnits(AsciiString::TheEmptyString);
return;
}
case 97:
{
((Rva003BBAD3 *)this)->rva003BBAD3();
return;
}
case 98:
{
Rva003BBB36Enable();
return;
}
case 321:
{
doSetBorderShroud(false);
return;
}
case 322:
{
doSetBorderShroud(true);
return;
}
case 100:
{
Rva003BBC61Set(true);
return;
}
case 101:
{
Rva003BBC61Set(false);
return;
}
case 102:
{
Rva003C0308Do(TEXT(0), (INTEGER(1) != 0), (INTEGER(2) != 0), 4294954951, AsciiString::TheEmptyString, 1);
return;
}
case 450:
{
Rva003C0425Do(TEXT(0), (INTEGER(1) != 0), (INTEGER(2) != 0), 4294954951, AsciiString::TheEmptyString, 1);
return;
}
case 451:
{
Rva003BBC81Set((INTEGER(0) != 0), (INTEGER(1) != 0), 1);
return;
}
case 471:
{
Rva003C0308Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), AsciiString::TheEmptyString, 1);
return;
}
case 472:
{
Rva003C0308Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), TEXT(4), 1);
return;
}
case 473:
{
Rva003C0425Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), AsciiString::TheEmptyString, 1);
return;
}
case 474:
{
Rva003C0425Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), TEXT(4), 1);
return;
}
case 456:
{
Rva003C0308Do(TEXT(0), (INTEGER(1) != 0), (INTEGER(2) != 0), 4294954951, AsciiString::TheEmptyString, 0);
return;
}
case 457:
{
Rva003C0425Do(TEXT(0), (INTEGER(1) != 0), (INTEGER(2) != 0), 4294954951, AsciiString::TheEmptyString, 0);
return;
}
case 458:
{
Rva003BBC81Set((INTEGER(0) != 0), (INTEGER(1) != 0), 0);
return;
}
case 475:
{
Rva003C0308Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), AsciiString::TheEmptyString, 0);
return;
}
case 476:
{
Rva003C0308Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), TEXT(4), 0);
return;
}
case 477:
{
Rva003C0425Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), AsciiString::TheEmptyString, 0);
return;
}
case 478:
{
Rva003C0425Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), TEXT(4), 0);
return;
}
case 459:
{
Rva003BBCB3Set((INTEGER(0) != 0));
return;
}
case 460:
{
Rva003BBCD2Set((INTEGER(0) != 0), (INTEGER(1) != 0));
return;
}
case 461:
{
doResetMusicScripting((INTEGER(0) != 0));
return;
}
case 106:
{
doTeamGarrisonSpecificBuilding(TEXT(0), TEXT(1), false);
return;
}
case 570:
{
doTeamGarrisonSpecificBuilding(TEXT(0), TEXT(1), true);
return;
}
case 573:
{
rva003C6EFC(TEXT(0), TEXT(1), true);
return;
}
case 107:
{
Rva003C8C6EDo(TEXT(0));
return;
}
case 108:
{
doTeamGarrisonNearestBuilding(TEXT(0));
return;
}
case 109:
{
Rva003C8E2BExit(TEXT(0));
return;
}
case 110:
{
doUnitGarrisonSpecificBuilding(*(AsciiString const *)(PARAM(0)), TEXT(1), false);
return;
}
case 567:
{
doUnitGarrisonSpecificBuilding(*(AsciiString const *)(PARAM(0)), TEXT(1), true);
return;
}
case 111:
{
doUnitGarrisonNearestBuilding(*(AsciiString const *)(PARAM(0)));
return;
}
case 112:
{
Rva003C90B1Exit(PARAM(0));
return;
}
case 113:
{
rva003BBD84(TEXT(0));
return;
}
case 114:
{
rva003BBDC4(TEXT(0));
return;
}
case 118:
{
Rva003BBE04(true);
return;
}
case 119:
{
Rva003BBE04(false);
return;
}
case 347:
{
HideControlBar(true);
return;
}
case 348:
{
ShowControlBar(false);
return;
}
case 349:
{
Rva003BBE91Set(true, INTEGER(0));
return;
}
case 350:
{
Rva003BBE91Set(false, INTEGER(0));
return;
}
case 128:
{
Rva003BBE44Set(true, (PARAM(0) ? INTEGER(0) : 0));
return;
}
case 129:
{
Rva003BBE44Set(false, (PARAM(0) ? INTEGER(0) : 0));
return;
}
case 136:
{
Rva003BB898((INTEGER(0) != 0), (INTEGER(1) != 0));
return;
}
case 137:
{
Rva003BB7FESet((int)(&TEXT(0)), (INTEGER(1) != 0));
return;
}
case 138:
{
((ScriptActionViewSlots *)TheTacticalView)->slot45(INTEGER(0) + 16);
((ScriptActionViewSlots *)TheTacticalView)->slot47(2);
return;
}
case 139:
{
((ScriptActionViewSlots *)TheTacticalView)->slot45(13);
((ScriptActionViewSlots *)TheTacticalView)->slot47(2);
return;
}
case 484:
{
((Rva00239A40 *)TheGameClient)->rva00239A40(TEXT(0));
return;
}
case 485:
{
((Rva00239A40 *)TheGameClient)->rva00239A40(AsciiString(""));
return;
}
case 140:
{
Rva003BBEDE();
return;
}
case 141:
{
Rva003BBEE9();
return;
}
case 142:
{
Rva003BBEF4((int)(&TEXT(0)), REAL(1));
return;
}
case 144:
{
rva003C062D(TEXT(0), REAL(1));
return;
}
case 146:
{
if (INTEGER(0) == 0)
((ScriptActionGameEngineSlots *)TheGameEngine)->slot18(((ScriptActionGlobalData *)TheWritableGlobalData)->m_value28);
else
((ScriptActionGameEngineSlots *)TheGameEngine)->slot18(INTEGER(0));
((ScriptActionGlobalData *)TheWritableGlobalData)->m_flag26 = true;
return;
}
case 159:
{
Rva003BBF8F();
return;
}
case 160:
{
Rva003BBFA0();
return;
}
case 161:
{
Rva003BBFB1Select(PARAM(0));
return;
}
case 162:
{
Rva003BBFD6Select(PARAM(0));
return;
}
case 145:
{
Rva003BBF51Set(PARAM(0), REAL(1));
return;
}
case 229:
{
Rva003BBF23Disable(PARAM(0), (INTEGER(1) != 0));
return;
}
case 147:
{
Rva003BBFFBSet(1, REAL(0));
return;
}
case 319:
{
Rva003BBFFBSet(22, REAL(0));
return;
}
case 320:
{
Rva003BBFFBSet(8, REAL(0));
return;
}
case 156:
{
rva003C90DD(TEXT(0), TEXT(1));
return;
}
case 157:
{
Rva003BC048Set(TEXT(0), INTEGER(1));
return;
}
case 158:
{
Rva003BC0A7Set(TEXT(0), INTEGER(1));
return;
}
case 163:
{
Rva003C549DDo(TEXT(0), TEXT(1));
return;
}
case 164:
{
Rva003C5535Do(TEXT(0));_ReadWriteBarrier();
return;
}
case 240:
{
Rva003C5405Do(TEXT(0), TEXT(1));
return;
}
case 241:
{
Rva003C5535Do(TEXT(0));
return;
}
case 166:
{
Rva003BC107();
return;
}
case 165:
{
Rva003BC115();
return;
}
case 167:
{
Rva003C3E75Apply(PARAM(0), TEXT(1), (void *)(1));
return;
}
case 168:
{
Rva003C3E75Apply(PARAM(0), TEXT(1), (void *)(0));
return;
}
case 169:
{
Rva003C3EC5Apply(PARAM(0), TEXT(1), INTEGER(2));
return;
}
case 170:
{
Rva003C3F9EApply(PARAM(0), TEXT(1), INTEGER(2));
return;
}
case 578:
{
doPlayerSetSpecialPowerCountdown(TEXT(0), TEXT(1), INTEGER(2));
return;
}
case 171:
{
Rva003C4003Apply(PARAM(0), TEXT(1), (void *)(&TEXT(2)));
return;
}
case 571:
{
doFireSpecialPowerAtWaypoint(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 255:
{
rva003C4070(TEXT(0), TEXT(1));
return;
}
case 445:
{
rva003C56D6((void *)(&TEXT(0)), TEXT(1), TEXT(2), TEXT(3));
return;
}
case 446:
{
rva003C55A6((void *)(&TEXT(0)), TEXT(1), TEXT(2), TEXT(3), TEXT(4));
return;
}
case 447:
{
rva003C4145(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 172:
{
Rva003C4245Do(PARAM(0), TEXT(1), TEXT(2));
return;
}
case 173:
{
Rva003BC1A0Forward();
return;
}
case 177:
{
Rva003C91D1Idle(PARAM(0));
return;
}
case 178:
{
((Rva003C08CC *)this)->rva003C08CC(&TEXT(0), false);
return;
}
case 179:
{
((Rva003C08CC *)this)->rva003C08CC(&TEXT(0), true);
return;
}
case 174:
{
Rva003BC1B2Do(PARAM(0), (INTEGER(1) != 0), REAL(2));
return;
}
case 175:
{
Rva003BAAD6();
return;
}
case 176:
{
Rva003BC22EDo(REAL(0), REAL(1), REAL(2));
return;
}
case 182:
{
rva003C0983(TEXT(0), TEXT(1), (Object *)(INTEGER(2)));
return;
}
case 183:
{
rva003C09DA(TEXT(0), TEXT(1));
return;
}
case 184:
{
rva003C0A2E(TEXT(0));
return;
}
case 187:
{
Rva003C43F3Do(TEXT(0), TEXT(1), (Object *)(INTEGER(2)));
return;
}
case 188:
{
Rva003C4449Do(TEXT(0), TEXT(1));
return;
}
case 189:
{
Rva003C4350Do(TEXT(0), TEXT(1), (Object *)(INTEGER(2)));
return;
}
case 190:
{
Rva003C43A3Do(TEXT(0), TEXT(1));
return;
}
case 186:
{
doNamedFireWeaponFollowingWaypointPath(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 244:
{
Rva003C57A9Do(PARAM(0), TEXT(1));
return;
}
case 202:
{
Rva003C5825Do(PARAM(0), TEXT(1), TEXT(2));
return;
}
case 203:
{
Rva003C58C9Do(PARAM(0), TEXT(1), (int)(&TEXT(2)));
return;
}
case 424:
{
rva003BD905(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 425:
{
rva003BDB03(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 426:
{
rva003BDC65(*(AsciiString const *)(PARAM(0)), TEXT(1), INTEGER(2));
return;
}
case 427:
{
rva003BDE5D(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 428:
{
rva003BDFA5(*(AsciiString const *)(PARAM(0)), TEXT(1), INTEGER(2));
return;
}
case 429:
{
rva003C42B9(PARAM(0), TEXT(1), TEXT(2));
return;
}
case 572:
{
doNamedBuildStructureAtWaypoint(PARAM(0), TEXT(1), REAL(2), TEXT(3));
return;
}
case 245:
{
Rva003C075BDo(&TEXT(0), &TEXT(1));
return;
}
case 242:
{
Rva003C07C1Do(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 243:
{
Rva003C0849Do(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 266:
{
Rva003C1020Do(TEXT(0), TEXT(1), PARAM(2));
return;
}
case 267:
{
doTeamUseCommandButtonOnNearestEnemy(TEXT(0), TEXT(1));
return;
}
case 268:
{
doTeamUseCommandButtonOnNearestGarrisonedBuilding(TEXT(0), TEXT(1));
return;
}
case 269:
{
doTeamUseCommandButtonOnNearestKindof(TEXT(0), TEXT(1), INTEGER(2));
return;
}
case 270:
{
doTeamUseCommandButtonOnNearestBuilding(TEXT(0), TEXT(1));
return;
}
case 271:
{
doTeamUseCommandButtonOnNearestBuildingClass(TEXT(0), TEXT(1), INTEGER(2));
return;
}
case 272:
{
rva003C449C(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 273:
{
doTeamPartialUseCommandButton(REAL(0), TEXT(1), TEXT(2));
return;
}
case 191:
{
doUnitStartSequentialScript(PARAM(0), TEXT(1), 0);
return;
}
case 192:
{
doUnitStartSequentialScript(PARAM(0), TEXT(1), (INTEGER(2) - 1));
return;
}
case 193:
{
Rva003BC259Remove(PARAM(0));
return;
}
case 194:
{
doTeamStartSequentialScript(TEXT(0), TEXT(1), 0);
return;
}
case 195:
{
doTeamStartSequentialScript(TEXT(0), TEXT(1), (INTEGER(2) - 1));
return;
}
case 196:
{
Rva003C0C3ESet(TEXT(0));
return;
}
case 197:
{
doUnitGuardForFramecount(*(AsciiString const *)(PARAM(0)), INTEGER(1), false);
return;
}
case 198:
{
doUnitIdleForFramecount(*(AsciiString const *)(PARAM(0)), INTEGER(1), false);
return;
}
case 328:
{
rva003C0D6A(*(AsciiString const *)(PARAM(0)), INTEGER(1), (INTEGER(2) != 0));
return;
}
case 329:
{
rva003C0D90(TEXT(0), INTEGER(1), (INTEGER(2) != 0));
return;
}
case 434:
{
rva003C596A(*(AsciiString const *)(PARAM(0)), TEXT(1), REAL(2), REAL(3));
return;
}
case 435:
{
Rva003C5A00Do(TEXT(0), TEXT(1), REAL(2), REAL(3));
return;
}
case 344:
{
Rva003BC2E4Do(PARAM(0), (INTEGER(1) != 0));
return;
}
case 345:
{
Rva003C0DE1Do(TEXT(0), (INTEGER(1) != 0));
return;
}
case 199:
case 200:
{
doTeamIdleForFramecount(TEXT(0), INTEGER(1), false);
return;
}
case 201:
{
Rva003BC306Do((Parameter *)(&TEXT(0)), REAL(1));
return;
}
case 204:
{
Rva003BC33DDo((Parameter *)(&TEXT(0)), REAL(1), REAL(2), REAL(3));
return;
}
case 205:
{
doBorderSwitch(INTEGER(0));
return;
}
case 371:
{
((ScriptActionGlobalData *)TheWritableGlobalData)->m_valueD40 = REAL(0);
return;
}
case 372:
{
((Rva003BC392Holder *)this)->set((INTEGER(0) != 0));
return;
}
case 209:
{
doForceObjectSelection(TEXT(0), TEXT(1), (INTEGER(2) != 0), TEXT(3));
return;
}
case 211:
{
Rva003BC421Do(PARAM(0), 0);
return;
}
case 212:
{
((ScriptActionRadarFlags *)TheRadar)->m_flag11 = true;
return;
}
case 213:
{
((ScriptActionRadarFlags *)TheRadar)->m_flag11 = false;
return;
}
case 214:
{
Rva003BC47ADo(INTEGER(0));
return;
}
case 215:
{
Rva003BC4ABSet(TEXT(0), INTEGER(1));
return;
}
case 228:
{
rva003C0E32(TEXT(0), INTEGER(1));
return;
}
case 216:
{
Rva003C0E87Do(TEXT(0), INTEGER(1));
return;
}
case 221:
{
Rva003BC4E8Do((int)(&TEXT(0)));
return;
}
case 222:
{
Rva003BC4D1Do((int)(&TEXT(0)));
return;
}
case 223:
{
Rva003BC4FFForward();
return;
}
case 325:
{
Rva003BC510Do((int)(&TEXT(0)));
return;
}
case 224:
{
Rva003BC524Set(TEXT(0), REAL(1));
return;
}
case 225:
{
Rva003BC54FDo((int)(&TEXT(0)));
return;
}
case 226:
{
Rva003BC566Forward();
return;
}
case 230:
{
Coord3D position; PARAM(1)->getCoord3D(&position);
TheScriptEngine->rva0035818E(TEXT(0), &position);
return;
}
case 231:
{
doMoveUnitTowardsNearest(*(AsciiString const *)(PARAM(0)), TEXT(1), TEXT(2));
return;
}
case 548:
{
rva003C951B(*(AsciiString const *)(PARAM(0)), TEXT(1), AsciiString::TheEmptyString);
return;
}
case 232:
{
doMoveTeamTowardsNearest(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 549:
{
doAttackMoveTeamTowardsNearest(TEXT(0), TEXT(1), AsciiString::TheEmptyString);
return;
}
case 565:
{
doAttackMoveTeamTowardsNearest(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 566:
{
rva003C0F09(TEXT(0), INTEGER(1));
return;
}
case 256:
{
doUnitReceiveUpgrade(PARAM(0), TEXT(1));
return;
}
case 261:
{
doSkirmishAttackNearestGroupWithValue(TEXT(0), INTEGER(1), INTEGER(2));
return;
}
case 262:
{
rva003C7018(TEXT(0), TEXT(1), REAL(2), (INTEGER(3) != 0));
return;
}
case 265:
{
doTeamSpinForFramecount(TEXT(0), INTEGER(1));
return;
}
case 551:
{
int framecount = (int)Rva000422BBCeil((float)BfmeLogicFramesPerSecond * REAL(1));
doTeamSpinForFramecount(TEXT(0), framecount);
return;
}
case 274:
{
doTeamCaptureNearestUnownedFactionUnit(TEXT(0));
return;
}
case 275:
{
((Rva003C1E69 *)this)->rva003C1E69(TEXT(0), TEXT(1));
return;
}
case 276:
{
Rva003BC582Set(TEXT(0), INTEGER(1));
return;
}
case 538:
{
Rva003BC8F0Set((INTEGER(0) != 0));
return;
}
case 277:
{
Rva003BC5CESet(TEXT(0), INTEGER(1));
return;
}
case 278:
{
Rva003BC626Set(TEXT(0), INTEGER(1));
return;
}
case 592:
{
Rva003BC67ASet(TEXT(0), INTEGER(1));
return;
}
case 279:
{
Rva003BC6C7Set(INTEGER(0));
return;
}
case 280:
{
Rva003BC6D9Set(TEXT(0), TEXT(1));
return;
}
case 281:
{
Rva003BC72FSet(TEXT(0), TEXT(1));
return;
}
case 302:
{
Rva003BC785Set(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 287:
{
Rva003C1F0A(TEXT(0), *(StringBase<char> const *)(&TEXT(1)), REAL(2));
return;
}
case 288:
{
Rva003BC996Do(PARAM(0), *(StringBase<char> const *)(&TEXT(1)), REAL(2));
return;
}
case 291:
{
TheScriptEngine->doObjectTypeListMaintenance(TEXT(0), TEXT(1), true);
return;
}
case 292:
{
TheScriptEngine->doObjectTypeListMaintenance(TEXT(0), TEXT(1), false);
return;
}
case 293:
{
Rva003BC9E0Do(TEXT(0), REAL(1), TEXT(2), TEXT(3));
return;
}
case 294:
{
Rva003BCA43Do(TEXT(0));_ReadWriteBarrier();
return;
}
case 554:
{
Rva003BCA12Do(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 555:
{
Rva003BCA43Do(TEXT(0));
return;
}
case 297:
{
Rva003BCA5DSet((INTEGER(0) != 0));
return;
}
case 298:
{
Rva003BCA68Set((INTEGER(0) != 0));
return;
}
case 300:
{
Rva003BCA7BSet((INTEGER(0) != 0));
return;
}
case 335:
{
Rva003BCADAForward(TEXT(0), TEXT(1));
return;
}
case 336:
{
Rva003BCAE8Forward();
return;
}
case 337:
{
Rva003BCAF6Do((Parameter *)(&TEXT(0)), REAL(1), REAL(2), REAL(3));
return;
}
case 301:
{
Rva003BCA8ESet((INTEGER(0) != 0));
return;
}
case 306:
{
Rva003BCAA1Set(REAL(0));
return;
}
case 307:
{
doNamedFaceNamed(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 308:
{
doNamedFaceWaypoint(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 309:
{
doTeamFaceNamed(TEXT(0), TEXT(1));
return;
}
case 310:
{
doTeamFaceWaypoint(TEXT(0), TEXT(1));
return;
}
case 303:
{
doAffectObjectPanelFlagsUnit(PARAM(0), TEXT(1), (INTEGER(2) != 0));
return;
}
case 304:
{
doAffectObjectPanelFlagsTeam(TEXT(0), TEXT(1), (INTEGER(2) != 0));
return;
}
case 305:
{
Rva003BCB37Set(TEXT(0), INTEGER(1));
return;
}
case 311:
{
doRemoveCommandBarButton(TEXT(0), TEXT(1));
return;
}
case 312:
{
Rva003BCB7A(TEXT(0), TEXT(1), INTEGER(2));
return;
}
case 313:
{
Coord3D temp36; PARAM(3)->getCoord3D(&temp36);
doCreateObject(TEXT(0), TEXT(1), TEXT(2), (Coord3D *)(&temp36), REAL(4));
return;
}
case 314:
{
Rva003BCBC7Set(TEXT(0), REAL(1));
return;
}
case 316:
{
Rva003C1F6CDo(&TEXT(0), INTEGER(1));
return;
}
case 323:
{
((ScriptActionWindowSlots *)this)->slot16(INTEGER(0) != 0);
return;
}
case 326:
{
rva003C9BAD(TEXT(0));
return;
}
case 331:
{
Rva003BCC08Do(REAL(0), REAL(1));
return;
}
case 332:
{
Rva003C1FADDestroy();
return;
}
case 333:
{
Rva003BCC6ESet((INTEGER(0) != 0));
return;
}
case 338:
{
rva003BA943(PARAM(0), true);
return;
}
case 339:
{
rva003BA943(PARAM(0), false);
return;
}
case 341:
{
Rva003BCC81Set(true);
return;
}
case 342:
{
Rva003BCC81Set(false);
return;
}
case 351:
{
Rva003BC7EFSet(TEXT(0), INTEGER(1));
return;
}
case 352:
{
Rva003BC830Clear(TEXT(0));
return;
}
case 353:
{
Rva003BC86ESet(TEXT(0), TEXT(1));
return;
}
case 354:
{
Rva003BC8AFSet(TEXT(0), (int)(&TEXT(1)));
return;
}
case 355:
{
Rva003C4570Do(TEXT(0), TEXT(1));
return;
}
case 356:
{
Rva003C1E8CSet(TEXT(0), INTEGER(1));
return;
}
case 357:
{
Rva003C1EC2Set(TEXT(0), INTEGER(1));
return;
}
case 358:
{
Rva003C45D4Apply(PARAM(0), TEXT(1));
return;
}
case 359:
{
Rva003BC903Do(PARAM(0), INTEGER(1));
return;
}
case 360:
{
rva003BC93C(PARAM(0), INTEGER(1));
return;
}
case 591:
{
Rva003BC96FDo(PARAM(0), INTEGER(1));
return;
}
case 361:
{
Coord3D temp36; PARAM(2)->getCoord3D(&temp36);
return;
}
case 363:
{
Coord3D temp48; PARAM(2)->getCoord3D(&temp48);
return;
}
case 366:
{
Rva003BCC94Do();
return;
}
case 367:
{
Rva003BCCA2Do();
return;
}
case 368:
{
((Rva003C1FDE *)this)->rva003C1FDE(TEXT(0), (INTEGER(1) != 0));
return;
}
case 369:
{
Rva003BCCC6Do(PARAM(0), PARAM(1));
return;
}
case 370:
{
Rva003BCD1BDo(PARAM(0));
return;
}
case 376:
{
doSetUnitReference(TEXT(0), PARAM(1), false);
return;
}
case 377:
{
rva003C20CA(TEXT(0), PARAM(1), false);
return;
}
case 378:
{
doSetUnitReference(TEXT(0), PARAM(1), true);
return;
}
case 379:
{
rva003C20CA(TEXT(0), PARAM(1), true);
return;
}
case 462:
{
rva003C4625(TEXT(0), PARAM(1), TEXT(2));
return;
}
case 488:
{
doSetUnitReferenceToHomeBaseOfPlayer(TEXT(0), TEXT(1), (INTEGER(2) != 0));
return;
}
case 463:
{
Rva003BCDD7Do(PARAM(0));
return;
}
case 464:
{
Rva003BCD45Do(PARAM(0));
return;
}
case 498:
{
rva003C207C(PARAM(0), PARAM(1), (INTEGER(2) != 0));
return;
}
case 380:
{
rva003C4751(PARAM(0));
return;
}
case 402:
{
rva003C49AE(PARAM(0), PARAM(1));
return;
}
case 403:
{
Rva003C2121Grant(TEXT(0), TEXT(1));
return;
}
case 381:
{
doUnpackBase(PARAM(0), &TEXT(1), 0);
return;
}
case 493:
{
doUnpackBase(PARAM(0), &TEXT(1), 1);
return;
}
case 383:
{
doBuildBaseBuilding(TEXT(0), PARAM(1), TEXT(2));
return;
}
case 384:
{
doBuildBaseBuildingInSlot(TEXT(0), PARAM(1), PARAM(2), TEXT(3));
return;
}
case 385:
{
rva003C66F1(TEXT(0), PARAM(1), TEXT(2), PARAM(3), TEXT(4));
return;
}
case 391:
{
Rva003C2260Do(TEXT(0), INTEGER(1));
return;
}
case 392:
{
Rva003C239FDo(TEXT(0), INTEGER(1), PARAM(2));
return;
}
case 393:
{
rva003C2662(TEXT(0), TEXT(1));
return;
}
case 394:
{
rva003C276A(TEXT(0), TEXT(1), PARAM(2));
return;
}
case 395:
{
doCounterMathCounter(PARAM(0), PARAM(1), PARAM(2));
return;
}
case 396:
{
doCounterMathValue(PARAM(0), PARAM(1), PARAM(2));
return;
}
case 397:
{
rva003C2166(TEXT(0), INTEGER(1), TEXT(2));
return;
}
case 556:
{
doSetCounterToThreatFinderThreat(TEXT(0), TEXT(1), TEXT(2), TEXT(3));
Rva003C21E5Do(&TEXT(0), INTEGER(1), &TEXT(2), &TEXT(3));
return;
}
case 398:
{
Rva003C21E5Do(&TEXT(0), INTEGER(1), &TEXT(2), &TEXT(3));
return;
}
case 535:
{
rva003CA322(TEXT(0), INTEGER(1), TEXT(2), TEXT(3));
return;
}
case 399:
{
Rva003C2A29Do(TEXT(0), TEXT(1));
return;
}
case 400:
{
Rva003C2A9FDo(TEXT(0), INTEGER(1));
return;
}
case 401:
{
Rva003C9C0AAttack(PARAM(0), INTEGER(1));
return;
}
case 404:
{
Rva003C2BC0Do(PARAM(0), PARAM(1));
return;
}
case 405:
{
Rva003C2C28Do(PARAM(0), PARAM(1));
return;
}
case 406:
{
Rva003C2C8FDo(PARAM(0), PARAM(1));
return;
}
case 407:
{
Rva003C2CD8Do(PARAM(0), PARAM(1));
return;
}
case 408:
{
Rva003C2D34Do(PARAM(0), PARAM(1));
return;
}
case 409:
{
Rva003C2D90Do(PARAM(0), PARAM(1));
return;
}
case 410:
{
Rva003C2DEADo(PARAM(0), PARAM(1));
return;
}
case 411:
{
doUnitGuardForFramecount(*(AsciiString const *)(PARAM(0)), INTEGER(1), true);
return;
}
case 412:
{
doUnitIdleForFramecount(*(AsciiString const *)(PARAM(0)), INTEGER(1), true);
return;
}
case 413:
case 414:
{
doTeamIdleForFramecount(TEXT(0), INTEGER(1), true);
return;
}
case 387:
{
Rva003BD062Set(PARAM(0), &TEXT(1), (INTEGER(2) != 0));
return;
}
case 388:
{
rva003C606C(PARAM(0), (INTEGER(1) != 0));
return;
}
case 418:
{
Rva003BD0C8Set(TEXT(0), (INTEGER(1) != 0));
return;
}
case 420:
{
Rva003C2E61Do((void const *)(PARAM(0)), (void const *)(PARAM(1)), (void const *)(PARAM(2)));
return;
}
case 421:
{
Rva003C2EC9Do((void const *)(PARAM(0)), (void const *)(PARAM(1)), (void const *)(PARAM(2)));
return;
}
case 422:
{
rva003C5F1B((ScriptAction *)(pAction), PARAM(0), PARAM(1), PARAM(2), true);
return;
}
case 522:
{
rva003C5F1B((ScriptAction *)(pAction), PARAM(0), PARAM(1), PARAM(2), false);
return;
}
case 509:
{
doSetCounterToPlayerOwnershipOfUnitsWithModelCondition(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 423:
{
Rva003C301DDo(PARAM(0), PARAM(1));
return;
}
case 431:
{
Rva003BD032Set(PARAM(0), PARAM(1));
return;
}
case 448:
{
Rva003BB62C((int)(&TEXT(0)));
return;
}
case 449:
{
Rva003BB641();
return;
}
case 525:
{
rva003C004D(TEXT(0), REAL(1));
return;
}
case 526:
{
rva003C0091(TEXT(0));
return;
}
case 527:
{
Rva003BB654();
return;
}
case 465:
{
Rva003C6A0EDo(PARAM(0), PARAM(1), PARAM(2));
return;
}
case 466:
{
Rva003C6B7BDo(PARAM(0), PARAM(1), PARAM(2));
return;
}
case 467:
{
Rva003C6D4FDo(PARAM(0), PARAM(1), PARAM(2));
return;
}
case 469:
{
Rva003C30D9Do(TEXT(0), (INTEGER(1) != 0));
return;
}
case 470:
{
Rva003C3175Do(TEXT(0), (INTEGER(1) != 0));
return;
}
case 479:
{
rva003C9D0D(TEXT(0), REAL(1));
return;
}
case 480:
{
rva003C9E4E(TEXT(0), TEXT(1));
return;
}
case 482:
{
rva003C32CC(TEXT(0), TEXT(1), INTEGER(2) != 0);
return;
}
case 481:
{
Rva003C31F3Do(TEXT(0), TEXT(1), (INTEGER(2) != 0));
return;
}
case 483:
{
Rva003BCFC9Set((INTEGER(0) != 0));
return;
}
case 513:
{
Rva003BCFD4Set((INTEGER(0) != 0));
return;
}
case 528:
{
Rva003BD01FSet((INTEGER(0) != 0));
return;
}
case 574:
{
Rva003BCFE7Forward(INTEGER(0) != 0);
return;
}
case 575:
{
Rva003BCFF5Forward(INTEGER(0) != 0);
return;
}
case 576:
{
Rva003BD003Forward(INTEGER(0) != 0);
return;
}
case 577:
{
Rva003BD011Forward(INTEGER(0) != 0);
return;
}
case 489:
{
rva003C739D(PARAM(0), PARAM(1), PARAM(2), PARAM(3), PARAM(4));
return;
}
case 491:
{
rva003C33C9(PARAM(0), PARAM(1), PARAM(2), PARAM(3), false);
return;
}
case 492:
{
rva003C33C9(PARAM(0), PARAM(1), PARAM(2), PARAM(3), true);
return;
}
case 494:
{
doSellBuildingOnFoundation(PARAM(0));
return;
}
case 496:
{
Rva003BD108SetGamePaused();
return;
}
case 500:
{
doUnitStandGround(PARAM(0), PARAM(1));
return;
}
case 501:
{
doTeamStandGround(PARAM(0), PARAM(1));
return;
}
case 502:
{
Rva003BD116Set(PARAM(0), (void *)(&TEXT(1)));
return;
}
case 503:
{
Rva003C353BDo(PARAM(0), (void *)(&TEXT(1)));
return;
}
case 504:
{
Rva003BD153Set(PARAM(0), INTEGER(1), INTEGER(2));
return;
}
case 505:
{
Rva003BD19CSet(PARAM(0), PARAM(1));
return;
}
case 506:
{
Rva0042F9DAEmit();
return;
}
case 507:
{
Rva003C35AADo(&TEXT(0), (INTEGER(1) != 0), false);
return;
}
case 512:
{
doHeroSelectButtonFlash((int)(&TEXT(0)), INTEGER(1));
return;
}
case 514:
{
rva003C3609(PARAM(0));
return;
}
case 515:
{
doUnitAssimilateWithFirstWalkOnArmy(PARAM(0));
return;
}
case 516:
{
Rva003C36C0Do(PARAM(0), (INTEGER(1) != 0));
return;
}
case 517:
{
Rva003C36FEDo(PARAM(0), (INTEGER(1) != 0));
return;
}
case 518:
{
rva003BD2A6((INTEGER(0) != 0));
return;
}
case 519:
{
doUnitForceEmotion(PARAM(0), INTEGER(1), REAL(2));
return;
}
case 520:
{
doTeamForceEmotion(PARAM(0), INTEGER(1), REAL(2));
return;
}
case 521:
{
doPlayerForceEmotion(PARAM(0), INTEGER(1), REAL(2));
return;
}
case 523:
{
rva003BD306(PARAM(0), (INTEGER(1) != 0));
return;
}
case 524:
{
Rva003C388EDo(PARAM(0), (INTEGER(1) != 0));
return;
}
case 531:
{
rva003BD32B(INTEGER(0));
return;
}
case 532:
{
rva003BD34D(INTEGER(0));
return;
}
case 533:
{
rva003BD36F(INTEGER(0));
return;
}
case 534:
{
rva003BD391(INTEGER(0));
return;
}
case 536:
{
bfmeGoFGE(PARAM(0), (void *)(INTEGER(1)), (INTEGER(2) != 0));
return;
}
case 537:
{
rva003C38EF(PARAM(0), (ObjectStatusTypes)(INTEGER(1)), (INTEGER(2) != 0));
return;
}
case 557:
{
rva003C6279(TEXT(0), TEXT(1));
return;
}
case 558:
{
rva003CA418(TEXT(0), INTEGER(1), TEXT(2));
return;
}
case 559:
{
rva003C3943(TEXT(0), TEXT(1));
return;
}
case 560:
{
doLivingWorldSetRegionRefToAdjacentRegion(TEXT(0), TEXT(1), (INTEGER(2) != 0), (INTEGER(3) != 0));
return;
}
case 561:
{
rva003C39B8(TEXT(0), TEXT(1));
return;
}
case 568:
{
rva003BD3CB((void *)(&TEXT(0)), REAL(1), INTEGER(2));
return;
}
case 569:
{
Rva003C3A3FSet(TEXT(0), INTEGER(1));
return;
}
case 579:
{
doCreateDelayedCarryoverUnitAtWaypoint(TEXT(0), TEXT(1), TEXT(2), TEXT(3));
return;
}
case 596:
{
doCreateUnitRevivalEntryFromDelayedCarryoverHero(TEXT(0), TEXT(1));
return;
}
case 595:
{
doCreateUnitRevivalEntry(TEXT(0), TEXT(1), -1);
return;
}
case 597:
{
doCreateUnitRevivalEntry(TEXT(0), TEXT(1), INTEGER(2));
return;
}
case 580:
{
Rva003BD405Set((unsigned char)(1));
return;
}
case 581:
{
Rva003BD405Set((unsigned char)(0));
return;
}
case 582:
{
Rva003BD412Set((unsigned char)(1));
return;
}
case 583:
{
Rva003BD412Set((unsigned char)(0));
return;
}
case 598:
{
Rva004E400DEnable();
return;
}
case 584:
{
doEnablePlanningMode((unsigned char)(1));
return;
}
case 585:
{
doEnablePlanningMode((unsigned char)(0));
return;
}
case 586:
{
doFlashSpellStoreButton(INTEGER(0));
return;
}
case 587:
{
doFlashObjectivesButton(INTEGER(0));
return;
}
case 588:
{
doFlashPlanningModeButton(INTEGER(0));
return;
}
case 589:
{
doDisplayNotificationBox(TEXT(0), TEXT(1), INTEGER(2), AsciiString::TheEmptyString);
return;
}
case 593:
{
doDisplayNotificationBox(TEXT(0), TEXT(1), INTEGER(2), TEXT(3));
return;
}
case 594:
{
doSelectBuilderButtonFlash(INTEGER(0));
return;
}
default:
return;
}
}
