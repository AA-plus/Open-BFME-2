// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehavior.cpp); this unit had no counterpart under Code/.
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: BridgeTowerBehavior.cpp //////////////////////////////////////////////////////////////////
// Author: Colin Day, July 2002
// Desc:   Behavior module for the towers attached to bridges that can be targeted
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameClient/InGameUI.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/BridgeBehavior.h"
#include "GameLogic/Module/BridgeTowerBehavior.h"
#include "GameLogic/TerrainLogic.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

BridgeTowerBehavior::BridgeTowerBehavior( Thing *thing, const ModuleData *moduleData )
									 : BehaviorModule( thing, moduleData )
{

	m_bridgeID = INVALID_ID;

}  // end BridgeTowerBehavior

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
BridgeTowerBehavior::~BridgeTowerBehavior( void )
{

}  // end ~BridgeTowerBehavior

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BridgeTowerBehavior::setBridge( Object *bridge )
{

	if( bridge == NULL )
		m_bridgeID = INVALID_ID;
	else
		m_bridgeID = bridge->getID();

}  // end setBridge

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?getBridgeID@BridgeTowerBehavior@@ present-unmatched
ObjectID BridgeTowerBehavior::getBridgeID( void )
{

	return m_bridgeID;

}  // end getBridge

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?setTowerType@BridgeTowerBehavior@@ present-unmatched
void BridgeTowerBehavior::setTowerType( BridgeTowerType type )
{

	m_type = type;

}  // end setTowerType

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?onBodyDamageStateChange@BridgeTowerBehavior@@ present-unmatched
void BridgeTowerBehavior::onBodyDamageStateChange( const DamageInfo* damageInfo, 
																									 BodyDamageType oldState, 
																									 BodyDamageType newState )
{

}  // end onBodyDamageStateChange

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BridgeTowerBehavior::onDie( const DamageInfo *damageInfo )
{

	// kill the bridge object, this will kill all the towers.  BFME 2 numbers
	// DamageType differently from the Zero Hour Damage.h this unit includes:
	// retail passes 8, BFME 2's DAMAGE_UNRESISTABLE (as SpawnBehavior_onSpawnDeath.cpp
	// declares it), where Zero Hour's default argument would push 11.
	Object *bridge = TheGameLogic->findObjectByID( getBridgeID() );
	if( bridge )
		bridge->kill( (DamageType)8 /* DAMAGE_UNRESISTABLE */ );

}  // end onDie

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
/** Given an object, return a bridge tower interface if that object has one */
// ------------------------------------------------------------------------------------------------
// BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject: defined in BridgeTowerBehaviorGetInterfaceFromObject.cpp (its row's unit).
  // getBridgeTowerBehaviorInterfaceFromObject

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@BridgeTowerBehavior@@ present-unmatched
void BridgeTowerBehavior::crc( Xfer *xfer )
{

	// extend base class
	BehaviorModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// BridgeTowerBehavior::xfer: defined in BridgeTowerBehaviorXfer.cpp (its row's unit).
  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@BridgeTowerBehavior@@ present-unmatched
void BridgeTowerBehavior::loadPostProcess( void )
{

	// extend base class
	BehaviorModule::loadPostProcess();

}  // end loadPostProcess
