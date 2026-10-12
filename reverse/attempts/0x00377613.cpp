// ?logicMessageDispatcher@GameLogic@@QAEXPAVGameMessage@@PAX@Z
// partial score=0.17406817647804096 date=2026-10-12
// ?logicMessageDispatcher@GameLogic@@QAEXPAVGameMessage@@PAX@Z
// cl-provenance: BFME1 cee35b7d8ca077d7255f1c39cb69e9fd9627aa85,
// game/GameEngine/Source/GameLogic/System/GameLogicDispatch.cpp (ZH-derived).
// Bank only. No row or pins. This is a diagnostic donor-guided scaffold:
// native enum values, null guard, Living World forwarding and four-argument
// rally handling are adapted from independently read BFME2 retail/WB bytes.
// Remaining added message cases, target layouts and ABI owners are unresolved.
// See reverse/attempt_evidence/logicdispatch/provider-closure.tsv and case-diff.tsv.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/shims/aicommandoutofline /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#define Matrix4x4 Matrix4

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"

#include "Common/CRCDebug.h"
#include "Common/GameAudio.h"
#include "Common/GameEngine.h"
#include "Common/GlobalData.h"
#include "Common/NameKeyGenerator.h"
#include "Common/ThingFactory.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/PlayerTemplate.h"
#include "Common/MessageStream.h"
#include "Common/MultiplayerSettings.h"
#include "Common/Recorder.h"
#include "Common/BuildAssistant.h"
#include "Common/SpecialPower.h"
#include "Common/ThingTemplate.h"
#include "Common/Upgrade.h"
#include "Common/StatsCollector.h"
#include "Common/Radar.h"

#include "GameLogic/AIPathfind.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/ObjectIter.h"

#include "GameLogic/AI.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/OpenContain.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/ScriptActions.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/VictoryConditions.h"
#include "GameLogic/Weapon.h"

#include "GameClient/CommandXlat.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/Eva.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GuiCallbacks.h"
#include "GameClient/InGameUI.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/Mouse.h"
#include "GameClient/ParticleSys.h"
#include "GameClient/Shell.h"
#include "GameClient/Module/BeaconClientUpdate.h"
#include "GameClient/LookAtXlat.h"

#include "GameNetwork/NetworkInterface.h"

#ifdef _INTERNAL

#endif

#define MAX_PATH_SUBJECTS 64
static Bool theBuildPlan = false;
static Object *thePlanSubject[ MAX_PATH_SUBJECTS ];
static int thePlanSubjectCount = 0;

static void doMoveTo( Object *obj, const Coord3D *pos )
{
	AIUpdateInterface *ai = obj->getAIUpdateInterface();
	DEBUG_ASSERTCRASH(ai, ("Attemped doMoveTo() on an Object with no AI\n"));
	if (ai)
	{
		if (theBuildPlan)
		{
			int i;

			for( i=0; i<thePlanSubjectCount; i++ )
				if (thePlanSubject[i] == obj)
					break;

			if (i == thePlanSubjectCount)
				thePlanSubject[ thePlanSubjectCount++ ] = obj;

			ai->queueWaypoint( pos );
		}
		else
		{
			ai->clearWaypointQueue();
			obj->leaveGroup();
			obj->releaseWeaponLock(LOCKED_TEMPORARILY);

			ai->aiMoveToPosition( pos, CMD_FROM_PLAYER );
		}
	}
}

void doSetRallyPoint(Object *, const Coord3D &);

static Object * getSingleObjectFromSelection(const AIGroup *currentlySelectedGroup)
{
	if( currentlySelectedGroup )
	{
		const VecObjectID& selectedObjects = currentlySelectedGroup->getAllIDs();
		DEBUG_ASSERTCRASH(selectedObjects.size() == 1, ("Trying to get single object from multiple selection!"));
		VecObjectID::const_iterator it = selectedObjects.begin();
		return TheGameLogic->findObjectByID(*it);
	}
	return NULL;
}

void GameLogic::clearGameData( Bool showScoreScreen )
{
	if( !isInGame() )
	{
		DEBUG_CRASH(("We tried to clear the game data when we weren't in a game"));
		return;
	}

	setClearingGameData( TRUE );

	if(TheStatsCollector)
		TheStatsCollector->writeFileEnd();

	TheScriptActions->closeWindows(FALSE);

	Bool shellGame = FALSE;
	if ((!isInShellGame() || !isInGame()) && showScoreScreen)
	{
		shellGame = TRUE;
		TheTransitionHandler->setGroup("FadeWholeScreen");
		TheShell->push("Menus/ScoreScreen.wnd");
		TheShell->showShell(FALSE);

		TheTransitionHandler->reverse("FadeWholeScreen");

		void FixupScoreScreenMovieWindow( void );
		FixupScoreScreenMovieWindow();
	}

	TheGameEngine->reset();
	setGameMode(GAME_NONE);

	if (TheGlobalData->m_initialFile.isEmpty() == FALSE)
	{
		TheGameEngine->setQuitting(TRUE);
	}

	HideControlBar();
	closeWindows();

	TheMouse->setVisibility(TRUE);

	if(m_background)
	{
		m_background->destroyWindows();
		m_background->deleteInstance();
		m_background = NULL;
	}

	setClearingGameData( FALSE );

}


// Native entry 377639..377661 forwards the Living World range before player
// selection. This provider remains unrowed; no provisional pin is supplied.
class LivingWorldLogic { public: void logicMessageDispatcher(GameMessage *, void *); };
extern LivingWorldLogic *TheLivingWorld;
Bool Rva0037711ADoSetRallyPoint(Object *, const Coord3D *, Bool, Object *);
void Rva003774ABSetGlobalRallyPoint(Object *, const Coord3D *);

void GameLogic::logicMessageDispatcher( GameMessage *msg, void *userData )
{
    if (!msg) return;
    int nativeType = (int)msg->getType();
    if (nativeType >= 0x6A4 && nativeType <= 0x76B)
    {
        if (TheLivingWorld) TheLivingWorld->logicMessageDispatcher(msg, userData);
        return;
    }

#ifdef _DEBUG
	DEBUG_ASSERTCRASH(msg != NULL && msg != (GameMessage*)0xdeadbeef, ("bad msg"));
#endif

	Player *thisPlayer = ThePlayerList->getNthPlayer( msg->getPlayerIndex() );
	DEBUG_ASSERTCRASH( thisPlayer, ("logicMessageDispatcher: Processing message from unknown player (player index '%d')\n",
																	msg->getPlayerIndex()) );

	AIGroup *currentlySelectedGroup = NULL;

	if (isInGame())
	{
		if (msg->getType() >= ((GameMessage::Type)1000) && msg->getType() <= ((GameMessage::Type)1999))
		{
			if (msg->getType() != ((GameMessage::Type)1098) && msg->getType() != ((GameMessage::Type)1095))
			{
				currentlySelectedGroup = TheAI->createGroup();

				CRCGEN_LOG(( "Creating AIGroup %d in GameLogic::logicMessageDispatcher()\n", (currentlySelectedGroup)?currentlySelectedGroup->getID():0 ));
				thisPlayer->getCurrentSelectionAsAIGroup(currentlySelectedGroup);

				if (currentlySelectedGroup->isEmpty())
				{
					TheAI->destroyGroup(currentlySelectedGroup);
					currentlySelectedGroup = NULL;
				}

				if (currentlySelectedGroup)
					if (currentlySelectedGroup->removeAnyObjectsNotOwnedByPlayer(thisPlayer))
						currentlySelectedGroup = NULL;

				if(TheStatsCollector)
					TheStatsCollector->collectMsgStats(msg);
			}
		}
	}

#ifdef DEBUG_LOGGING
	AsciiString commandName;

	commandName = msg->getCommandAsAsciiString();
	if (msg->getType() < ((GameMessage::Type)1000) || msg->getType() > ((GameMessage::Type)1999))
	{
		commandName.concat(" (NON-LOGIC-MESSAGE!!!)");
	}
	else if (msg->getType() == ((GameMessage::Type)1000))
	{
		commandName = " (CRC message!)";
	}
#if 0
	if (commandName.isNotEmpty()
)
	{
		DEBUG_LOG(("Frame %d: GameLogic::logicMessageDispatcher() saw a %s from player %d (%ls)\n", getFrame(), commandName.str(),
			msg->getPlayerIndex(), thisPlayer->getPlayerDisplayName().str()));
	}
#endif
#endif

	GameMessage::Type msgType = msg->getType();
	switch( msgType )
	{

		case ((GameMessage::Type)30):
		{

			Int gameMode = msg->getArgument( 0 )->integer;
			Int rankPoints = 0;
			GameDifficulty diff = DIFFICULTY_NORMAL;
			if ( msg->getArgumentCount() >= 2 )
				diff = (GameDifficulty)msg->getArgument( 1 )->integer;
			if ( msg->getArgumentCount() >= 3 )
				rankPoints = msg->getArgument( 2 )->integer;

			if ( msg->getArgumentCount() >= 4 )
			{
				Int maxFPS = msg->getArgument( 3 )->integer;
				if (maxFPS < 1 || maxFPS > 1000)
					maxFPS = TheGlobalData->m_framesPerSecondLimit;
				DEBUG_LOG(("Setting max FPS limit to %d FPS\n", maxFPS));
				TheGameEngine->setFramesPerSecondLimit(maxFPS);
				TheWritableGlobalData->m_useFpsLimit = true;
			}

			prepareNewGame( gameMode, diff, rankPoints );

			startNewGame( FALSE );

			break;

		}

		case ((GameMessage::Type)29):
		{

#if defined(_DEBUG) || defined(_INTERNAL)
			if (TheDisplay && TheGlobalData->m_dumpAssetUsage)
				TheDisplay->dumpAssetUsage(TheGlobalData->m_mapName.str());
#endif

			if (currentlySelectedGroup)
				TheAI->destroyGroup(currentlySelectedGroup);
			currentlySelectedGroup = NULL;
			TheGameLogic->clearGameData();
			break;

		}

		case ((GameMessage::Type)114):
		{
			DEBUG_LOG(("META: begin path build\n"));
			DEBUG_ASSERTCRASH(!theBuildPlan, ("mismatched theBuildPlan"));

			if (theBuildPlan == false)
			{
				theBuildPlan = true;
				thePlanSubjectCount = 0;
			}

			break;
		}

		case ((GameMessage::Type)115):
		{
			DEBUG_LOG(("META: end path build\n"));
			DEBUG_ASSERTCRASH(theBuildPlan, ("mismatched theBuildPlan"));

			for( int i=0; i<thePlanSubjectCount; i++ )
			{
				AIUpdateInterface *ai = thePlanSubject[i]->getAIUpdateInterface();
				if (ai)
					ai->executeWaypointQueue();
			}

			theBuildPlan = false;
			thePlanSubjectCount = 0;

			break;
		}

		case ((GameMessage::Type)1043):
		{
			Object *obj = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );
			Coord3D dest = msg->getArgument( 1 )->location;
            Bool global = msg->getArgument(2)->boolean;
            Object *positionSource = TheGameLogic->findObjectByID(msg->getArgument(3)->objectID);
            if (obj)
            {
                if (global && !positionSource)
                    Rva003774ABSetGlobalRallyPoint(obj, &dest);
                else
                    Rva0037711ADoSetRallyPoint(obj, &dest, true, 0);
            }

			break;

		}

		case ((GameMessage::Type)1037):
		{
			WeaponSlotType weaponSlot = (WeaponSlotType)msg->getArgument( 0 )->integer;
			Int maxShotsToFire = msg->getArgument( 1 )->integer;

			if( currentlySelectedGroup && currentlySelectedGroup->setWeaponLockForGroup( weaponSlot, LOCKED_TEMPORARILY ))
			{
				currentlySelectedGroup->groupAttackPosition( NULL, maxShotsToFire, CMD_FROM_PLAYER );
			}

			break;
		}





		case ((GameMessage::Type)1039):
		{

			WeaponSlotType weaponSlot = (WeaponSlotType)msg->getArgument( 0 )->integer;
			Object *targetObject = TheGameLogic->findObjectByID( msg->getArgument( 1 )->objectID );
			Int maxShotsToFire = msg->getArgument( 2 )->integer;

			if( targetObject == NULL )
				break;

			if( currentlySelectedGroup )
			{

				if (currentlySelectedGroup->setWeaponLockForGroup( weaponSlot, LOCKED_TEMPORARILY ))
					currentlySelectedGroup->groupAttackObject( targetObject, maxShotsToFire, CMD_FROM_PLAYER );
			}

			break;

		}

		case ((GameMessage::Type)1082):
		{

			WeaponSlotType weaponSlot = (WeaponSlotType)msg->getArgument( 0 )->integer;

			if( currentlySelectedGroup )
				currentlySelectedGroup->setWeaponLockForGroup( weaponSlot, LOCKED_PERMANENTLY );
			break;
		}

		case ((GameMessage::Type)1099):
		{
			if( currentlySelectedGroup )
			{
				currentlySelectedGroup->setMineClearingDetail(true);
			}
			break;
		}

		case ((GameMessage::Type)1122):
		{

			Int playerIndex = msg->getArgument( 0 )->integer;
			Bool enableRetaliation = msg->getArgument( 1 )->boolean;

			Player *player = ThePlayerList->getNthPlayer( playerIndex );
			if( player )
			{
				player->setLogicalRetaliationModeEnabled( enableRetaliation );
			}
			break;
		}

		case ((GameMessage::Type)1038):
		{
			WeaponSlotType weaponSlot = (WeaponSlotType)msg->getArgument( 0 )->integer;
			Coord3D targetLoc = msg->getArgument( 1 )->location;
			Int maxShotsToFire = msg->getArgument( 2 )->integer;

			if( currentlySelectedGroup )
			{

				if (currentlySelectedGroup->setWeaponLockForGroup( weaponSlot, LOCKED_TEMPORARILY ))
					currentlySelectedGroup->groupAttackPosition( &targetLoc, maxShotsToFire, CMD_FROM_PLAYER );

			}

			break;

		}

		case ((GameMessage::Type)1040):
		{

			UnsignedInt specialPowerID = msg->getArgument( 0 )->integer;

			UnsignedInt options = msg->getArgument( 1 )->integer;

			ObjectID sourceID = msg->getArgument(2)->objectID;
			Object* source = TheGameLogic->findObjectByID(sourceID);
			if (source != NULL)
			{
				AIGroup* theGroup = TheAI->createGroup();
				theGroup->add(source);
				theGroup->groupDoSpecialPower( specialPowerID, options );
				TheAI->destroyGroup(theGroup);
			}
			else
			{

				if( currentlySelectedGroup )
				{
					currentlySelectedGroup->groupDoSpecialPower( specialPowerID, options );
				}
			}
			break;

		}

		case ((GameMessage::Type)1041):
		{

			UnsignedInt specialPowerID = msg->getArgument( 0 )->integer;

			Coord3D targetCoord = msg->getArgument(1)->location;

			Real angle = msg->getArgument(2)->real;

			ObjectID objectID = msg->getArgument( 3 )->objectID;
			Object *objectInWay = TheGameLogic->findObjectByID( objectID );

			UnsignedInt options = msg->getArgument( 4 )->integer;

			ObjectID sourceID = msg->getArgument(5)->objectID;
			Object* source = TheGameLogic->findObjectByID(sourceID);
			if (source != NULL)
			{
				AIGroup* theGroup = TheAI->createGroup();
				theGroup->add(source);
				theGroup->groupDoSpecialPowerAtLocation( specialPowerID, &targetCoord, angle, objectInWay, options );
				TheAI->destroyGroup(theGroup);
			}
			else
			{

				if( currentlySelectedGroup )
				{
					currentlySelectedGroup->groupDoSpecialPowerAtLocation( specialPowerID, &targetCoord, angle, objectInWay, options );
				}
			}
			break;

		}

		case ((GameMessage::Type)1042):
		{

			UnsignedInt specialPowerID = msg->getArgument( 0 )->integer;

			ObjectID targetID = msg->getArgument(1)->objectID;
			Object *target = TheGameLogic->findObjectByID( targetID );
			if( !target )
			{
				break;
			}

			UnsignedInt options = msg->getArgument( 2 )->integer;

			ObjectID sourceID = msg->getArgument(3)->objectID;
			Object* source = TheGameLogic->findObjectByID(sourceID);
			if (source != NULL)
			{
				AIGroup* theGroup = TheAI->createGroup();
				theGroup->add(source);
				theGroup->groupDoSpecialPowerAtObject( specialPowerID, target, options );
				TheAI->destroyGroup(theGroup);
			}
			else
			{
				if( currentlySelectedGroup )
				{
					currentlySelectedGroup->groupDoSpecialPowerAtObject( specialPowerID, target, options );
				}
			}
			break;

		}

		case ((GameMessage::Type)1072):
		{
			Coord3D dest = msg->getArgument( 0 )->location;

			if (currentlySelectedGroup)
			{
				currentlySelectedGroup->releaseWeaponLockForGroup(LOCKED_TEMPORARILY);

				currentlySelectedGroup->groupAttackMoveToPosition( &dest, NO_MAX_SHOTS_LIMIT, CMD_FROM_PLAYER );
			}

			break;
		}

		case ((GameMessage::Type)1073):
		{
			Coord3D dest = msg->getArgument( 0 )->location;

			if (currentlySelectedGroup)
			{
				currentlySelectedGroup->releaseWeaponLockForGroup(LOCKED_TEMPORARILY);

				currentlySelectedGroup->groupMoveToPosition( &dest, false, CMD_FROM_PLAYER );
			}

			break;
		}

		case ((GameMessage::Type)1090):
		case ((GameMessage::Type)1071):
		{
			Coord3D dest = msg->getArgument( 0 )->location;

			if( currentlySelectedGroup )
			{

				currentlySelectedGroup->releaseWeaponLockForGroup(LOCKED_TEMPORARILY);

				currentlySelectedGroup->groupMoveToPosition( &dest, false, CMD_FROM_PLAYER );
			}

			break;
		}

		case ((GameMessage::Type)1074):
		{
			Coord3D dest = msg->getArgument( 0 )->location;

			if( currentlySelectedGroup )
			{

				currentlySelectedGroup->releaseWeaponLockForGroup(LOCKED_TEMPORARILY);

				currentlySelectedGroup->groupMoveToPosition( &dest, true, CMD_FROM_PLAYER );
			}

			break;
		}

		case ((GameMessage::Type)1075):
		{
			Coord3D loc = msg->getArgument( 0 )->location;
			GuardMode gm = (GuardMode)msg->getArgument( 1 )->integer;
			if (currentlySelectedGroup)
			{
				currentlySelectedGroup->groupGuardPosition(&loc, gm, CMD_FROM_PLAYER);
			}

			break;
		}

		case ((GameMessage::Type)1076):
		{
			Object* obj = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );
			if (!obj)
				break;

			GuardMode gm = (GuardMode)msg->getArgument( 1 )->integer;
			if (currentlySelectedGroup)
			{
				currentlySelectedGroup->groupGuardObject(obj, gm, CMD_FROM_PLAYER);
			}

			break;
		}

		case ((GameMessage::Type)1077):
		{
			if (currentlySelectedGroup)
			{
				currentlySelectedGroup->groupIdle(CMD_FROM_PLAYER);
			}

			break;
		}

		case ((GameMessage::Type)1078):
		{
			if (currentlySelectedGroup)
			{
				currentlySelectedGroup->groupScatter(CMD_FROM_PLAYER);
			}

			break;
		}

		case ((GameMessage::Type)1097):
		{
			if (currentlySelectedGroup)
			{
				currentlySelectedGroup->groupCreateFormation(CMD_FROM_PLAYER);
			}

			break;
		}



		case ((GameMessage::Type)1080):
		{

			if( currentlySelectedGroup )
			{
				currentlySelectedGroup->groupCheer( CMD_FROM_PLAYER );
			}
			break;
		}

#if defined(_DEBUG) || defined(_INTERNAL) || defined (_ALLOW_DEBUG_CHEATS_IN_RELEASE)






#endif

#ifdef ALLOW_SURRENDER


#endif

		case ((GameMessage::Type)1068):
		{
			Object *enter = TheGameLogic->findObjectByID( msg->getArgument( 1 )->objectID );

			if( enter == NULL )
				break;

			if( currentlySelectedGroup )
			{
				currentlySelectedGroup->releaseWeaponLockForGroup(LOCKED_TEMPORARILY);

				currentlySelectedGroup->groupEnter( enter, CMD_FROM_PLAYER );
			}

			break;

		}

		case ((GameMessage::Type)1053):
		{
			Object *objectWantingToExit = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );
			Object *objectContainingExiter = getSingleObjectFromSelection(currentlySelectedGroup);

			if( objectWantingToExit == NULL )
				break;

			if( objectContainingExiter == NULL )
				break;

			if( objectWantingToExit->getControllingPlayer() != thisPlayer )
				break;

			objectWantingToExit->releaseWeaponLock(LOCKED_TEMPORARILY);

			AIUpdateInterface *ai = objectWantingToExit->getAIUpdateInterface();
			if( ai )
				ai->aiExit( objectContainingExiter, CMD_FROM_PLAYER );

			break;

		}

		case ((GameMessage::Type)1054):
		{

			if( currentlySelectedGroup )
			{

				currentlySelectedGroup->releaseWeaponLockForGroup(LOCKED_TEMPORARILY);

				currentlySelectedGroup->groupEvacuate( CMD_FROM_PLAYER );

			}

			break;

		}





		case ((GameMessage::Type)1064):
		{
			Object *repairDepot = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );

			if( repairDepot == NULL )
				break;

			if( currentlySelectedGroup )
				currentlySelectedGroup->groupGetRepaired( repairDepot, CMD_FROM_PLAYER );

			break;

		}

		case ((GameMessage::Type)1069):
		{
			Object *dockBuilding = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );

			if( dockBuilding == NULL )
				break;

			if( currentlySelectedGroup )
				currentlySelectedGroup->groupDock( dockBuilding, CMD_FROM_PLAYER );

			break;

		}

		case ((GameMessage::Type)1065):
		{
			Object *healDest = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );

			if( healDest == NULL )
				break;

			if( currentlySelectedGroup )
				currentlySelectedGroup->groupGetHealed( healDest, CMD_FROM_PLAYER );

			break;

		}

		case ((GameMessage::Type)1066):
		{
			Object *repairTarget = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );

			if( repairTarget == NULL )
				break;

			if( currentlySelectedGroup )
				currentlySelectedGroup->groupRepair( repairTarget, CMD_FROM_PLAYER );

			break;

		}

		case ((GameMessage::Type)1067):
		{
			Object *constructTarget = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );

			if( constructTarget == NULL )
				break;

			if( currentlySelectedGroup )
				currentlySelectedGroup->groupResumeConstruction( constructTarget, CMD_FROM_PLAYER );

			break;

		}

		case ((GameMessage::Type)1089):
		{
			const Coord3D *loc = &msg->getArgument( 0 )->location;
			SpecialPowerType spType = (SpecialPowerType)msg->getArgument( 1 )->integer;

			ObjectID sourceID = msg->getArgument(2)->objectID;
			Object* source = TheGameLogic->findObjectByID(sourceID);
			if (source != NULL)
			{
				AIGroup* theGroup = TheAI->createGroup();
				theGroup->add(source);
				theGroup->groupOverrideSpecialPowerDestination( spType, loc, CMD_FROM_PLAYER );
				TheAI->destroyGroup(theGroup);
			}
			else
			{
				if( currentlySelectedGroup )
				{
					currentlySelectedGroup->groupOverrideSpecialPowerDestination( spType, loc, CMD_FROM_PLAYER );
				}
			}
		}

		case ((GameMessage::Type)1061):
		{
			Object *enemy = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );

			if (enemy)
			{
				if (currentlySelectedGroup)
				{

					currentlySelectedGroup->releaseWeaponLockForGroup(LOCKED_TEMPORARILY);

					currentlySelectedGroup->groupAttackObject( enemy, NO_MAX_SHOTS_LIMIT, CMD_FROM_PLAYER );

				}

			}

			break;

		}

		case ((GameMessage::Type)1062):
		{
			Object *enemy = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );

			if (enemy)
			{
				if (currentlySelectedGroup)
				{
					currentlySelectedGroup->releaseWeaponLockForGroup(LOCKED_TEMPORARILY);

					currentlySelectedGroup->groupForceAttackObject( enemy, NO_MAX_SHOTS_LIMIT, CMD_FROM_PLAYER );
				}

			}

			break;

		}

		case ((GameMessage::Type)1063):
		{
			const Coord3D *pos = &msg->getArgument( 0 )->location;

			if (currentlySelectedGroup)
			{

				Bool forceAttackRequiresPrimaryWeapon = !currentlySelectedGroup->isIdle();
				if ( forceAttackRequiresPrimaryWeapon )
				{
					currentlySelectedGroup->setWeaponLockForGroup( PRIMARY_WEAPON, LOCKED_TEMPORARILY );
					currentlySelectedGroup->groupAttackPosition( pos, NO_MAX_SHOTS_LIMIT, CMD_FROM_PLAYER );
					currentlySelectedGroup->releaseWeaponLockForGroup(LOCKED_TEMPORARILY);
				}
				else

				{
					currentlySelectedGroup->releaseWeaponLockForGroup(LOCKED_TEMPORARILY);
					currentlySelectedGroup->groupAttackPosition( pos, NO_MAX_SHOTS_LIMIT, CMD_FROM_PLAYER );
				}

			}

			break;

		}

		case ((GameMessage::Type)1045):
		{
			const UpgradeTemplate *upgradeT = TheUpgradeCenter->findUpgradeByKey( (NameKeyType)(msg->getArgument( 1 )->integer) );
			if (!upgradeT)

				break;

			if (currentlySelectedGroup)
				currentlySelectedGroup->queueUpgrade( upgradeT );

			break;

		}

		case ((GameMessage::Type)1046):
		{
			Object *producer = getSingleObjectFromSelection(currentlySelectedGroup);
			const UpgradeTemplate *upgradeT = TheUpgradeCenter->findUpgradeByKey( (NameKeyType)(msg->getArgument( 0 )->integer) );

			if( producer == NULL || upgradeT == NULL )
				break;

			if( producer->getControllingPlayer() != thisPlayer )
				break;

				ProductionUpdateInterface *pu = producer->getProductionUpdateInterface();
				if( pu == NULL )
				break;

			pu->cancelUpgrade( upgradeT );

			break;

		}

		case ((GameMessage::Type)1047):
		{
			Object *producer = getSingleObjectFromSelection(currentlySelectedGroup);
			const ThingTemplate *whatToCreate;
			ProductionID productionID;

			whatToCreate = TheThingFactory->findByTemplateID( msg->getArgument( 0 )->integer );
			productionID = (ProductionID)msg->getArgument( 1 )->integer;

			if ( producer == NULL || whatToCreate == NULL )
				break;

			ProductionUpdateInterface *pu = producer->getProductionUpdateInterface();
			if( pu == NULL )
			{

				DEBUG_ASSERTCRASH( 0, ("MSG_QUEUE_UNIT_CREATE: Producer '%s' doesn't have a unit production interface\n",
															producer->getTemplate()->getName().str()) );
				break;

			}

			pu->queueCreateUnit( whatToCreate, productionID );

			break;

		}

		case ((GameMessage::Type)1048):
		{
			Object *producer = getSingleObjectFromSelection(currentlySelectedGroup);
			ProductionID productionID = (ProductionID)msg->getArgument( 0 )->integer;

			if( producer == NULL )
				break;

			if( producer->getControllingPlayer() != thisPlayer )
				break;

			ProductionUpdateInterface *pu = producer->getProductionUpdateInterface();
			if( pu == NULL )
				return;

			pu->cancelUnitCreate( productionID );

			break;

		}

		case ((GameMessage::Type)1050):


		case ((GameMessage::Type)1051):
		{

			Object *building = getSingleObjectFromSelection(currentlySelectedGroup);
			if( building == NULL )
				break;

			if( building->getControllingPlayer() != thisPlayer )
				break;

			if( !building->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION) )
				break;

			if( !building->testStatus(OBJECT_STATUS_RECONSTRUCTING))
			{
				Money *money = thisPlayer->getMoney();
				UnsignedInt amount = building->getTemplate()->calcCostToBuild( thisPlayer );
				money->deposit( amount );
			}

			building->kill();

			break;

		}

		case ((GameMessage::Type)1052):
		{

			if( currentlySelectedGroup )
				currentlySelectedGroup->groupSell( CMD_FROM_PLAYER );

			break;

		}



#ifdef ALLOW_SURRENDER



#endif

#ifdef ALLOW_SURRENDER



#endif

		case ((GameMessage::Type)1002):
		case ((GameMessage::Type)1001):
		{
			Bool createNewGroup = msg->getArgument( 0 )->boolean;
			Player *player = ThePlayerList->getNthPlayer(msg->getPlayerIndex());

			if (player == NULL) {
				DEBUG_CRASH(("GameLogicDispatch - MSG_CREATE_SELECTED_GROUP had an invalid player nubmer"));
				break;
			}

			Bool firstObject = TRUE;

			for (Int i = 1; i < msg->getArgumentCount(); ++i) {
				Object *obj = TheGameLogic->findObjectByID( msg->getArgument( i )->objectID );
				if (!obj) {
					continue;
				}

				TheGameLogic->selectObject(obj, createNewGroup && firstObject, player->getPlayerMask());
				firstObject = FALSE;
			}

			break;

		}

		case ((GameMessage::Type)1005):
		{
			Player *player = ThePlayerList->getNthPlayer(msg->getPlayerIndex());

			if (player == NULL) {
				DEBUG_CRASH(("GameLogicDispatch - MSG_CREATE_SELECTED_GROUP had an invalid player nubmer"));
				break;
			}

			for (Int i = 0; i < msg->getArgumentCount(); ++i) {
				ObjectID objID = msg->getArgument(i)->objectID;
				Object *objToRemove = TheGameLogic->findObjectByID(objID);
				if (!objToRemove) {
					continue;
				}

				TheGameLogic->deselectObject(objToRemove, player->getPlayerMask());
			}

			break;

		}

		case ((GameMessage::Type)1004):
		{
			Player *player = ThePlayerList->getNthPlayer(msg->getPlayerIndex());
			if (player != NULL)
			{
				player->setCurrentlySelectedAIGroup(NULL);
			}

			break;

		}



		case ((GameMessage::Type)1092):
		{

			Coord3D pos = msg->getArgument( 0 )->location;
			Region3D r;
			TheTerrainLogic->getExtent(&r);
			if (!r.isInRegionNoZ(&pos))
				pos = TheTerrainLogic->findClosestEdgePoint(&pos);
			const ThingTemplate *thing = TheThingFactory->findTemplate( thisPlayer->getPlayerTemplate()->getBeaconTemplate() );
			if (thing && !TheVictoryConditions->hasSinglePlayerBeenDefeated(thisPlayer))
			{
				Int count;
				thisPlayer->countObjectsByThingTemplate( 1, &thing, false, &count );
				DEBUG_LOG(("Player already has %d beacons active\n", count));
				if (count >= TheMultiplayerSettings->getMaxBeaconsPerPlayer())
				{
					if (thisPlayer == ThePlayerList->getLocalPlayer())
					{

						TheInGameUI->message( TheGameText->fetch("GUI:TooManyBeacons") );

						static AudioEventRTS aSound("BeaconPlacementFailed");
						aSound.setPosition(&pos);
						aSound.setPlayerIndex(thisPlayer->getPlayerIndex());
						TheAudio->addAudioEvent(&aSound);
					}

					break;
				}
				Object *object = TheThingFactory->newObject( thing, thisPlayer->getDefaultTeam() );
				object->setPosition( &pos );
				object->setProducer(NULL);

				if (thisPlayer->getRelationship( ThePlayerList->getLocalPlayer()->getDefaultTeam() ) == ALLIES || ThePlayerList->getLocalPlayer()->isPlayerObserver())
				{

					UnicodeString s;
					s.format(TheGameText->fetch("GUI:BeaconPlaced"), thisPlayer->getPlayerDisplayName().str());
					TheInGameUI->message( s );

					static AudioEventRTS aSound("BeaconPlaced");
					aSound.setPlayerIndex(thisPlayer->getPlayerIndex());
					aSound.setPosition(&pos);
					TheAudio->addAudioEvent(&aSound);

					TheRadar->createEvent( object->getPosition(), RADAR_EVENT_INFORMATION );

					if (ThePlayerList->getLocalPlayer()->getRelationship(thisPlayer->getDefaultTeam()) == ALLIES)
						TheEva->setShouldPlay(EVA_BeaconDetected);

					TheControlBar->markUIDirty();

				}
				else
				{

					Int updateCount = 0;
					static NameKeyType nameKeyClientUpdate = NAMEKEY("BeaconClientUpdate");
					ClientUpdateModule ** clientModules = object->getDrawable()->getClientUpdateModules();
					if (clientModules)
					{
						while (*clientModules)
						{
							if ((*clientModules)->getModuleNameKey() == nameKeyClientUpdate)
							{
								(*(BeaconClientUpdate **)clientModules)->hideBeacon();
								++updateCount;
							}

							++clientModules;
						}
					}
					DEBUG_ASSERTCRASH(updateCount == 1, ("Saw %d update modules for the beacon!", updateCount));

				}
			}
			else
			{

				TheInGameUI->message( TheGameText->fetch("GUI:BeaconPlacementFailed") );

				static AudioEventRTS aSound("BeaconPlacementFailed");
				aSound.setPosition(&pos);
				aSound.setPlayerIndex(thisPlayer->getPlayerIndex());
				TheAudio->addAudioEvent(&aSound);
			}
			break;
		}

		case ((GameMessage::Type)1093):
		{

			AIGroup *allSelectedObjects = NULL;
			allSelectedObjects = TheAI->createGroup();
			thisPlayer->getCurrentSelectionAsAIGroup(allSelectedObjects);

			if( allSelectedObjects )
			{
				const VecObjectID& selectedObjects = allSelectedObjects->getAllIDs();
				for (VecObjectID::const_iterator it = selectedObjects.begin(); it != selectedObjects.end(); ++it)
				{
					Object *beacon = findObjectByID(*it);
					if (beacon)
					{
						const ThingTemplate *thing = TheThingFactory->findTemplate( beacon->getControllingPlayer()->getPlayerTemplate()->getBeaconTemplate() );
						if (thing->isEquivalentTo(beacon->getTemplate()))
						{
							if (beacon->getControllingPlayer() == thisPlayer)
							{
								TheGameLogic->destroyObject(beacon);

								TheControlBar->markUIDirty();

							}
							else if (thisPlayer == ThePlayerList->getLocalPlayer())
							{
								Drawable *beaconDrawable = beacon->getDrawable();
								if (beaconDrawable)
								{

									static NameKeyType nameKeyClientUpdate = NAMEKEY("BeaconClientUpdate");
									ClientUpdateModule ** clientModules = beaconDrawable->getClientUpdateModules();
									if (clientModules)
									{
										while (*clientModules)
										{
											if ((*clientModules)->getModuleNameKey() == nameKeyClientUpdate)
												(*(BeaconClientUpdate **)clientModules)->hideBeacon();

											++clientModules;
										}
									}
								}
							}
						}
					}
				}
				if (allSelectedObjects->isEmpty())
				{
					TheAI->destroyGroup(allSelectedObjects);
					allSelectedObjects = NULL;
				}
			}
			break;
		}

		case ((GameMessage::Type)1094):
		{
			if( currentlySelectedGroup )
			{
				const VecObjectID& selectedObjects = currentlySelectedGroup->getAllIDs();
				for (VecObjectID::const_iterator it = selectedObjects.begin(); it != selectedObjects.end(); ++it)
				{
					Object *beacon = findObjectByID(*it);
					if (beacon)
					{
						Drawable *beaconDrawable = beacon->getDrawable();
						if (beaconDrawable)
						{
							UnicodeString s;
							for( int i=0; i<msg->getArgumentCount(); i++ )
							{
								s.concat( msg->getArgument(i)->wChar );
							}

							if (s.isEmpty())
								beaconDrawable->clearCaptionText();
							else
								beaconDrawable->setCaptionText(s);
						}
					}
				}
			}
			break;
		}

		case ((GameMessage::Type)1096):
		{
			if (msg->getArgument(0)->boolean)
			{

				for (Int i=0; i<ThePlayerList->getPlayerCount(); ++i)
				{
					if (i != msg->getPlayerIndex())
					{
						Player *otherPlayer = ThePlayerList->getNthPlayer(i);
						if (thisPlayer->getRelationship(otherPlayer->getDefaultTeam()) == ALLIES &&
							otherPlayer->getRelationship(thisPlayer->getDefaultTeam()) == ALLIES)
						{
							if (TheVictoryConditions->hasSinglePlayerBeenDefeated(otherPlayer))
								continue;

							otherPlayer->transferAssetsFromThat(thisPlayer);
							thisPlayer->killPlayer();

							break;
						}
					}
				}
				if (i == ThePlayerList->getPlayerCount())
				{

					thisPlayer->killPlayer();
				}
			}
			else
			{
				thisPlayer->killPlayer();
			}

			break;
		}

		case ((GameMessage::Type)1095):
		{
			if (TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK && TheGlobalData->m_useCameraInReplay && TheControlBar->getObserverLookAtPlayer() == thisPlayer)
			{
				if (TheTacticalView->isCameraMovementFinished())
				{
					ViewLocation loc;
					Coord3D pos;
					Real pitch, angle, zoom;
					pos = msg->getArgument( 0 )->location;
					angle = msg->getArgument( 1 )->real;
					pitch = msg->getArgument( 2 )->real;
					zoom = msg->getArgument( 3 )->real;
					loc.init(pos.x, pos.y, pos.z, angle, pitch, zoom);
					TheTacticalView->setLocation( &loc );

					if (!TheLookAtTranslator->hasMouseMovedRecently())
					{
						TheMouse->setCursor( (Mouse::MouseCursor)(msg->getArgument( 4 )->integer) );
						ICoord2D mousePos = msg->getArgument( 5 )->pixel;
						TheMouse->setPosition( mousePos.x, mousePos.y );
						TheLookAtTranslator->setCurrentPos( mousePos );
					}
				}
			}
			break;
		}

		case ((GameMessage::Type)1006):
		case ((GameMessage::Type)1007):
		case ((GameMessage::Type)1008):
		case ((GameMessage::Type)1009):
		case ((GameMessage::Type)1010):
		case ((GameMessage::Type)1011):
		case ((GameMessage::Type)1012):
		case ((GameMessage::Type)1013):
		case ((GameMessage::Type)1014):
		case ((GameMessage::Type)1015):
		{
			Int playerIndex = msg->getPlayerIndex();
			Player *player = ThePlayerList->getNthPlayer(playerIndex);
			DEBUG_ASSERTCRASH(player != NULL, ("Could not find player for create team message"));

			if (player == NULL)
			{
				break;
			}

			player->processCreateTeamGameMessage(msg->getType() - ((GameMessage::Type)1006), msg);
			break;
		}

		case ((GameMessage::Type)1016):
		case ((GameMessage::Type)1017):
		case ((GameMessage::Type)1018):
		case ((GameMessage::Type)1019):
		case ((GameMessage::Type)1020):
		case ((GameMessage::Type)1021):
		case ((GameMessage::Type)1022):
		case ((GameMessage::Type)1023):
		case ((GameMessage::Type)1024):
		case ((GameMessage::Type)1025):
		{
			Int playerIndex = msg->getPlayerIndex();
			Player *player = ThePlayerList->getNthPlayer(playerIndex);
			DEBUG_ASSERTCRASH(player != NULL, ("Could not find player for select team message"));

			if (player == NULL)
			{
				break;
			}

			player->processSelectTeamGameMessage(msg->getType() - ((GameMessage::Type)1016), msg);
			break;
		}

		case ((GameMessage::Type)1026):
		case ((GameMessage::Type)1027):
		case ((GameMessage::Type)1028):
		case ((GameMessage::Type)1029):
		case ((GameMessage::Type)1030):
		case ((GameMessage::Type)1031):
		case ((GameMessage::Type)1032):
		case ((GameMessage::Type)1033):
		case ((GameMessage::Type)1034):
		case ((GameMessage::Type)1035):
		{
			Int playerIndex = msg->getPlayerIndex();
			Player *player = ThePlayerList->getNthPlayer(playerIndex);
			DEBUG_ASSERTCRASH(player != NULL, ("Could not find player for add team message"));

			if (player == NULL)
			{
				break;
			}

			player->processAddTeamGameMessage(msg->getType() - ((GameMessage::Type)1026), msg);
			break;
		}

		case ((GameMessage::Type)1098):
		{
			if (TheNetwork)
			{
				Int slotIndex = -1;
				for (Int i=0; i<MAX_SLOTS; ++i)
				{
					if (thisPlayer->getPlayerType() == PLAYER_HUMAN && TheNetwork->getPlayerName(i) == thisPlayer->getPlayerDisplayName())
					{
						slotIndex = i;
						break;
					}
				}

				if (slotIndex < 0 || !TheNetwork->isPlayerConnected(slotIndex))
					break;

				if (thisPlayer->isLocalPlayer())
				{
#if defined(_DEBUG) || defined(_INTERNAL)

					if (!TheDebugIgnoreSyncErrors)
					{
#endif
						m_shouldValidateCRCs = TRUE;
#if defined(_DEBUG) || defined(_INTERNAL)
					}
#endif
				}

				UnsignedInt newCRC = msg->getArgument(0)->integer;

				m_cachedCRCs[msg->getPlayerIndex()] = newCRC;

			}
			else if (TheRecorder && TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK)
			{
				UnsignedInt newCRC = msg->getArgument(0)->integer;

				TheRecorder->handleCRCMessage(newCRC, thisPlayer->getPlayerIndex(), (msg->getArgument(1)->boolean));
			}
			break;

		}

		case ((GameMessage::Type)1044):
		{
			ScienceType science = (ScienceType)msg->getArgument( 0 )->integer;

			if( science == SCIENCE_INVALID || thisPlayer == NULL )
				break;

			thisPlayer->attemptToPurchaseScience(science);

			break;

		}

	}

	if (currentlySelectedGroup && TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK && TheGlobalData->m_useCameraInReplay && TheControlBar->getObserverLookAtPlayer() == thisPlayer
)
	{
		const VecObjectID& selectedObjects = currentlySelectedGroup->getAllIDs();
		TheInGameUI->deselectAllDrawables();
		for (VecObjectID::const_iterator it = selectedObjects.begin(); it != selectedObjects.end(); ++it)
		{
			const Object *obj = findObjectByID(*it);
			if (obj)
			{
				Drawable *draw = obj->getDrawable();
				if (draw)
					TheInGameUI->selectDrawable(draw);
			}
		}
	}

	if( currentlySelectedGroup != NULL )
	{
		TheAI->destroyGroup(currentlySelectedGroup);
	}

}
