// ?areAllSelected@@YA_NABV?$list@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@_STL@@@Z
// partial score=1.0 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Evidence bank only; no functions.csv recovery or production link claim.
// Complete retail helper 0042FA0D..0042FA63 (86B), with private EBX list-ref input.
// The full real parent at 0043003C is retained because it determines that ABI;
// the parent itself is still nonmatching and must not be rowed from this bank.
// areAllSelected name/algorithm is inferred from the clean BFME1 donor and ZH
// translateGameMessage use, not a named target symbol. Layout offsets FC/274,
// template flag115.20 and selected43C are independent native accesses.
// Donor: reference/open-bfme-1 9e3be919b10ae956e3c8a13995e0d62f2be1d016,
// game/GameEngine/Source/GameClient/MessageStream/SelectionXlat.cpp.
// The Object header from inputs/reference/.../GameEngine/Include/GameLogic is
// embedded below with getDrawable declaration-only: the existing target pin
// at5508E2 is used rather than the donor's wrong inline +80 field accessor.
// All other donor/header layouts are context only, not target layout claims.
// Reproduce using tools/explain_mismatch.py with the line-1 symbol, --rva
// 0x0042FA0D --size 86 --source this-file. No build-local headers are required.
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
#define Matrix4x4 Matrix4  // BFME renamed it
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "Lib/BaseType.h"
#include "Common/Geometry.h"
#include "Common/Snapshot.h"
#include "Common/SpecialPowerMaskType.h"
#include "Common/DisabledTypes.h"
#include "Common/Thing.h"
#include "Common/ObjectStatusTypes.h"
#include "Common/Upgrade.h"
#include "GameClient/Color.h"
#include "GameLogic/Damage.h" //for kill()
#include "GameLogic/WeaponBonusConditionFlags.h"
#include "GameLogic/WeaponSet.h"
#include "GameLogic/WeaponSetFlags.h"
#include "GameLogic/Module/StealthUpdate.h"
class AIGroup;
class AIUpdateInterface;
class Anim2DTemplate;
class BehaviorModule;
class BehaviorModuleInterface;
class BodyModuleInterface;
class CollideModule;
class CollideModuleInterface;
class CommandButton;
class ContainModuleInterface;
class CountermeasuresBehaviorInterface;
class CreateModuleInterface;
class DamageInfo;
class DamageInfoInput;
class DamageModule;
class DamageModuleInterface;
class DestroyModuleInterface;
class DockUpdateInterface;
class Dict;
class DieModule;
class DieModuleInterface;
class ExitInterface;
class ExperienceTracker;
class FiringTracker;
class Module;
class PartitionData;
class PhysicsBehavior;
class PhysicsUpdate;
class Player;
class PolygonTrigger;
class ProductionUpdateInterface;
class ProjectileUpdateInterface;
class RadarObject;
class SightingInfo;
class SpawnBehaviorInterface;
class SpecialAbilityUpdate;
class SpecialPowerCompletionDie;
class SpecialPowerModuleInterface;
class SpecialPowerTemplate;
class SpecialPowerUpdateInterface;
class Team;
class UpdateModule;
class UpdateModuleInterface;
class UpgradeModule;
class UpgradeModuleInterface;
class UpgradeTemplate;
class ObjectHeldHelper;
class ObjectDisabledHelper;
class ObjectSMCHelper;
class ObjectRepulsorHelper;
class StatusDamageHelper;
class SubdualDamageHelper;
class TempWeaponBonusHelper;
class ObjectWeaponStatusHelper;
class ObjectDefectionHelper;
enum CommandSourceType;
enum HackerAttackMode;
enum NameKeyType;
enum SpecialPowerType;
enum WeaponBonusConditionType;
enum WeaponChoiceCriteria;
enum WeaponSetConditionType;
enum WeaponSetType;
enum ArmorSetType;
enum WeaponStatus;
enum RadarPriorityType;
enum CanAttackResult;
#include "Common/ObjectStatusTypes.h"
#include "GameLogic/ObjectScriptStatusBits.h"
struct TTriggerInfo

{
 const PolygonTrigger*	pTrigger;
///< The trigger area that the object is inside.
 Byte									entered;
///< True if the object entered this trigger area this frame.
 Byte									exited;
///< True if the object entered this trigger area this frame.
 Byte									isInside;
///< True if the object is inside this trigger area this frame.
 Byte									padding;
///< unused.
 TTriggerInfo() : entered(false), exited(false), isInside(false), padding(false), pTrigger(NULL) 
 {
  
 }
 
}
;
enum CrushSquishTestType

{
 TEST_CRUSH_ONLY,
 TEST_SQUISH_ONLY,
 TEST_CRUSH_OR_SQUISH
 
}
;
class Object : public Thing, public Snapshot

{
 MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(Object, "ObjectPool" )
 MEMORY_POOL_DELETEINSTANCE_VISIBILITY(protected)
 public:
 Object(const ThingTemplate *thing, const ObjectStatusMaskType &objectStatusMask, Team *team);
 void initObject();
 void onDestroy();
///< run during TheGameLogic::destroyObject
 Object* getNextObject() 
 {
  return m_next;
  
 }
 const Object* getNextObject() const 
 {
  return m_next;
  
 }
 void updateObjValuesFromMapProperties(Dict* properties);
///< Brings in properties set in the editor.
 ObjectID getID() const 
 {
  return m_id;
  
 }
///< this object's unique ID
 void friend_bindToDrawable( Drawable *draw );
///< set drawable association. for use ONLY by GameLogic!
 Drawable* getDrawable() const;
///< drawable (if any) bound to obj
 ObjectID getProducerID() const 
 {
  return m_producerID;
  
 }
 void setProducer(const Object* obj);
 ObjectID getBuilderID() const 
 {
  return m_builderID;
  
 }
 void setBuilder( const Object *obj );
 void enterGroup( AIGroup *group );
///< become a member of the AIGroup
 void leaveGroup( void );
///< leave our current AIGroup
 AIGroup *getGroup(void);
 Bool isMobile() const;
///< returns true if object is currently able to move
 Bool isAbleToAttack() const;
///< returns true if object currently has some kind of attack capability
 void maskObject( Bool mask );
///< mask/unmask object
 Bool checkAndDetonateBoobyTrap(const Object *victim);
 Bool isDestroyed() const 
 {
  return m_status.test( OBJECT_STATUS_DESTROYED );
  
 }
///< Returns TRUE if object has been destroyed
 Bool isAirborneTarget() const 
 {
  return m_status.test( OBJECT_STATUS_AIRBORNE_TARGET );
  
 }
///< Our locomotor will control marking us as a valid target for anti air weapons or not
 Bool isUsingAirborneLocomotor( void ) const;
///< returns true if the current locomotor is an airborne one
 void onCapture( Player *oldOwner, Player *newOwner );
 void onDie( DamageInfo *damageInfo );
 void attemptDamage( DamageInfo *damageInfo );
///< damage object as specified by the info
 void attemptHealing(Real amount, const Object* source);
///< heal object as specified by the info
 Bool attemptHealingFromSoleBenefactor ( Real amount, const Object* source, UnsignedInt duration );
///< for the non-stacking healers like ambulance and propaganda
 ObjectID getSoleHealingBenefactor( void ) const;
 Real estimateDamage( DamageInfoInput& damageInfo ) const;
 void kill( DamageType damageType = DAMAGE_UNRESISTABLE, DeathType deathType = DEATH_NORMAL );
///< kill the object with an optional type of damage and death.
 void healCompletely();
///< Restore max health to this Object
 void notifySubdualDamage( Real amount );
///< At this level, we just pass this on to our helper and do a special tint
 void doStatusDamage( ObjectStatusTypes status, Real duration );
///< At this level, we just pass this on to our helper
 void doTempWeaponBonus( WeaponBonusConditionType status, UnsignedInt duration );
///< At this level, we just pass this on to our helper
 void scoreTheKill( const Object *victim );
///< I just killed this object.
 void onVeterancyLevelChanged( VeterancyLevel oldLevel, VeterancyLevel newLevel, Bool provideFeedback = TRUE );
///< I just achieved this level right this moment
 ExperienceTracker* getExperienceTracker() 
 {
  return m_experienceTracker;
  
 }
 const ExperienceTracker* getExperienceTracker() const 
 {
  return m_experienceTracker;
  
 }
 VeterancyLevel getVeterancyLevel() const;
 inline const AsciiString& getName() const 
 {
  return m_name;
  
 }
 inline void setName( const AsciiString& newName ) 
 {
  m_name = newName;
  
 }
 inline Team* getTeam() 
 {
  return m_team;
  
 }
 inline const Team *getTeam() const 
 {
  return m_team;
  
 }
 void restoreOriginalTeam();
 void setTeam( Team* team );
///< sets the unit's team AND original team
 void setTemporaryTeam( Team* team );
///< sets the unit's team BUT NOT its original team
 Player* getControllingPlayer() const;
 Relationship getRelationship(const Object *that) const;
 Color getIndicatorColor() const;
 Color getNightIndicatorColor() const;
 Bool hasCustomIndicatorColor() const 
 {
  return m_indicatorColor != 0;
  
 }
 void setCustomIndicatorColor(Color c);
 void removeCustomIndicatorColor();
 Bool isLocallyControlled() const;
 Bool isNeutralControlled() const;
 Bool getIsUndetectedDefector(void) const 
 {
  return BitTest(m_privateStatus, UNDETECTED_DEFECTOR);
  
 }
 void friend_setUndetectedDefector(Bool status);
 inline Bool isOffMap() const 
 {
  return BitTest(m_privateStatus, OFF_MAP);
  
 }
 inline Bool isCaptured() const 
 {
  return BitTest(m_privateStatus, CAPTURED);
  
 }
 void setCaptured(Bool isCaptured);
 inline const GeometryInfo& getGeometryInfo() const 
 {
  return m_geometryInfo;
  
 }
 void setGeometryInfo(const GeometryInfo& geom);
 void setGeometryInfoZ( Real newZ );
 void onCollide( Object *other, const Coord3D *loc, const Coord3D *normal );
 Real getCarrierDeckHeight() const;
 Bool areModulesReady() const 
 {
  return m_modulesReady;
  
 }
 BehaviorModule** getBehaviorModules() const 
 {
  return m_behaviors;
  
 }
 BodyModuleInterface* getBodyModule() const 
 {
  return m_body;
  
 }
 ContainModuleInterface* getContain() const 
 {
  return m_contain;
  
 }
 StealthUpdate*          getStealth() const 
 {
  return m_stealth;
  
 }
 SpawnBehaviorInterface* getSpawnBehaviorInterface() const;
 ProjectileUpdateInterface* getProjectileUpdateInterface() const;
 inline AIUpdateInterface *getAIUpdateInterface() 
 {
  return m_ai;
  
 }
 inline const AIUpdateInterface* getAIUpdateInterface() const 
 {
  return m_ai;
  
 }
 inline AIUpdateInterface *getAI() 
 {
  return m_ai;
  
 }
 inline const AIUpdateInterface* getAI() const 
 {
  return m_ai;
  
 }
 inline PhysicsBehavior* getPhysics() 
 {
  return m_physics;
  
 }
 inline const PhysicsBehavior* getPhysics() const 
 {
  return m_physics;
  
 }
 void topple( const Coord3D *toppleDirection, Real toppleSpeed, UnsignedInt options );
 UpdateModule* findUpdateModule(NameKeyType key) const 
 {
  return (UpdateModule*)findModule(key);
  
 }
 DamageModule* findDamageModule(NameKeyType key) const 
 {
  return (DamageModule*)findModule(key);
  
 }
 Bool isSalvageCrate() const;
 ProductionUpdateInterface* getProductionUpdateInterface( void );
 DockUpdateInterface *getDockUpdateInterface( void );
 SpecialPowerModuleInterface* findSpecialPowerModuleInterface( SpecialPowerType type ) const;
 SpecialPowerModuleInterface* findAnyShortcutSpecialPowerModuleInterface() const;
 SpecialAbilityUpdate* findSpecialAbilityUpdate( SpecialPowerType type ) const;
 SpecialPowerCompletionDie* findSpecialPowerCompletionDie() const;
 SpecialPowerUpdateInterface* findSpecialPowerWithOverridableDestinationActive( SpecialPowerType type = SPECIAL_INVALID ) const;
 SpecialPowerUpdateInterface* findSpecialPowerWithOverridableDestination( SpecialPowerType type = SPECIAL_INVALID ) const;
 CountermeasuresBehaviorInterface* Object::getCountermeasuresBehaviorInterface();
 const CountermeasuresBehaviorInterface* Object::getCountermeasuresBehaviorInterface() const;
 inline ObjectStatusMaskType getStatusBits() const 
 {
  return m_status;
  
 }
 inline Bool testStatus( ObjectStatusTypes bit ) const 
 {
  return m_status.test( bit );
  
 }
 void setStatus( ObjectStatusMaskType objectStatus, Bool set = true );
 inline void clearStatus( ObjectStatusMaskType objectStatus ) 
 {
  setStatus( objectStatus, false );
  
 }
 void updateUpgradeModules();
///< We need to go through our Upgrade Modules and see which should be activated
 UpgradeMaskType getObjectCompletedUpgradeMask() const 
 {
  return m_objectUpgradesCompleted;
  
 }
///< Upgrades I complete locally
 void forceRefreshSubObjectUpgradeStatus();
 inline Bool testScriptStatusBit(ObjectScriptStatusBit b) const 
 {
  return BitTest(m_scriptStatus, b);
  
 }
 void setScriptStatus( ObjectScriptStatusBit bit, Bool set = true );
 inline void clearScriptStatus( ObjectScriptStatusBit bit ) 
 {
  setScriptStatus(bit, false);
  
 }
 void setSelectable(Bool selectable);
 Bool isSelectable() const;
 Bool isMassSelectable() const;
 void setFormationID(enum FormationID id) 
 {
  m_formationID = id;
  
 }
 enum FormationID getFormationID(void) const 
 {
  return m_formationID;
  
 }
 void setFormationOffset(const Coord2D& offset) 
 {
  m_formationOffset = offset;
  
 }
 void getFormationOffset(Coord2D* offset) const 
 {
  *offset = m_formationOffset;
  
 }
 void getHealthBoxPosition(Coord3D& pos) const;
 Bool getHealthBoxDimensions(Real &healthBoxHeight, Real &healthBoxWidth) const;
 inline Bool isEffectivelyDead() const 
 {
  return (m_privateStatus & EFFECTIVELY_DEAD) != 0;
  
 }
 void setEffectivelyDead(Bool dead);
 void markSingleUseCommandUsed() 
 {
  m_singleUseCommandUsed = true;
  
 }
 Bool hasSingleUseCommandBeenUsed() const 
 {
  return m_singleUseCommandUsed;
  
 }
 Bool canCrushOrSquish(Object *otherObj, CrushSquishTestType testType = TEST_CRUSH_OR_SQUISH) const;
 UnsignedByte getCrusherLevel() const;
 UnsignedByte getCrushableLevel() const;
 Bool hasUpgrade( const UpgradeTemplate *upgradeT ) const ;
///< does this object already have this upgrade
 Bool affectedByUpgrade( const UpgradeTemplate *upgradeT ) const ;
///< can the object even "have" this upgrade, will it do something?
 void giveUpgrade( const UpgradeTemplate *upgradeT );
///< give upgrade to this object
 void removeUpgrade( const UpgradeTemplate *upgradeT );
///< remove upgrade from this object
 Bool hasCountermeasures() const;
 void reportMissileForCountermeasures( Object *missile );
 ObjectID calculateCountermeasureToDivertTo( const Object& victim );
 void calcNaturalRallyPoint(Coord2D *pt);
///< calc the "natural" starting rally point
 void setConstructionPercent( Real percent ) 
 {
  m_constructionPercent = percent;
  
 }
 Real getConstructionPercent() const 
 {
  return m_constructionPercent;
  
 }
 void setLayer( PathfindLayerEnum layer );
 PathfindLayerEnum getLayer() const 
 {
  return m_layer;
  
 }
 void setDestinationLayer( PathfindLayerEnum layer );
 PathfindLayerEnum getDestinationLayer() const 
 {
  return m_destinationLayer;
  
 }
 void prependToList(Object **pListHead);
 void removeFromList(Object **pListHead);
 Bool isInList(Object **pListHead) const;
 void friend_deleteInstance() 
 {
  deleteInstance();
  
 }
 void friend_setPartitionData(PartitionData *pd) 
 {
  m_partitionData = pd;
  
 }
 PartitionData *friend_getPartitionData() const 
 {
  return m_partitionData;
  
 }
 const PartitionData *friend_getConstPartitionData() const 
 {
  return m_partitionData;
  
 }
 void onPartitionCellChange();
///< We have moved a 'significant' amount, so do maintenence that can be considered 'cell-based'
 void handlePartitionCellMaintenance();
///< Undo and redo all shroud actions.  Call when something has changed, like position or ownership or Death
 Real getVisionRange() const;
///< How far can you see?  This is dynamic so it is in Object.
 void setVisionRange( Real newVisionRange );
///< Access to setting someone's Vision distance
 Real getShroudRange() const;
///< How far can you shroud?  Even more dynamic since it'll start at zero for everyone.
 void setShroudRange( Real newShroudRange );
///< Access to setting someone's shrouding distance
 Real getShroudClearingRange() const;
///< How far do you clear shroud?
 void setShroudClearingRange( Real newShroudClearingRange );
///< Access to setting someone's clear shroud distance
 void setVisionSpied(Bool setting, Int byWhom);
///< Change who is looking through our eyes
 void friend_prepareForMapBoundaryAdjust(void);
 void friend_notifyOfNewMapBoundary(void);
 void friend_setRadarData( RadarObject *rd ) 
 {
  m_radarData = rd;
  
 }
 RadarObject *friend_getRadarData() 
 {
  return m_radarData;
  
 }
 RadarPriorityType getRadarPriority() const;
 inline Object *getContainedBy() 
 {
  return m_containedBy;
  
 }
 inline const Object *getContainedBy() const 
 {
  return m_containedBy;
  
 }
 inline UnsignedInt getContainedByFrame() const 
 {
  return m_containedByFrame;
  
 }
 inline Bool isContained() const 
 {
  return m_containedBy != NULL;
  
 }
 void onContainedBy( Object *containedBy );
 void onRemovedFrom( Object *removedFrom );
 Int getTransportSlotCount() const;
 void friend_setContainedBy( Object *containedBy ) 
 {
  m_containedBy = containedBy;
  
 }
 SpecialPowerModuleInterface *getSpecialPowerModule( const SpecialPowerTemplate *specialPowerTemplate ) const;
 void doSpecialPower( const SpecialPowerTemplate *specialPowerTemplate, UnsignedInt commandOptions, Bool forced = false );
///< execute power
 void doSpecialPowerAtObject( const SpecialPowerTemplate *specialPowerTemplate, Object *obj, UnsignedInt commandOptions, Bool forced = false );
///< execute power
 void doSpecialPowerAtLocation( const SpecialPowerTemplate *specialPowerTemplate, const Coord3D *loc, Real angle, UnsignedInt commandOptions, Bool forced = false );
///< execute power
 void doSpecialPowerUsingWaypoints( const SpecialPowerTemplate *specialPowerTemplate, const Waypoint *way, UnsignedInt commandOptions, Bool forced = false );
///< execute power
 void doCommandButton( const CommandButton *commandButton, CommandSourceType cmdSource );
 void doCommandButtonAtObject( const CommandButton *commandButton, Object *obj, CommandSourceType cmdSource );
 void doCommandButtonAtPosition( const CommandButton *commandButton, const Coord3D *pos, CommandSourceType cmdSource );
 void doCommandButtonUsingWaypoints( const CommandButton *commandButton, const Waypoint *way, CommandSourceType cmdSource );
 const AsciiString& getCommandSetString() const;
 void setCommandSetStringOverride( AsciiString newCommandSetString ) 
 {
  m_commandSetStringOverride = newCommandSetString;
  
 }
 Bool Object::canProduceUpgrade( const UpgradeTemplate *upgrade );
 void reloadAllAmmo(Bool now);
 Bool isOutOfAmmo() const;
 Bool hasAnyWeapon() const;
 Bool hasAnyDamageWeapon() const;
//Kris: a should be used for real weapons that directly inflict damage... not deploy, hack, etc.
 Bool hasWeaponToDealDamageType(DamageType typeToDeal) const;
 Real getLargestWeaponRange() const;
 UnsignedInt getMostPercentReadyToFireAnyWeapon() const;
 Weapon* getWeaponInWeaponSlot(WeaponSlotType wslot) const 
 {
  return m_weaponSet.getWeaponInWeaponSlot(wslot);
  
 }
 UnsignedInt getWeaponInWeaponSlotCommandSourceMask( WeaponSlotType wSlot ) const 
 {
  return m_weaponSet.getNthCommandSourceMask( wSlot );
  
 }
 const Bool isReloadTimeShared() const 
 {
  return m_weaponSet.isSharedReloadTime();
  
 }
 Weapon* getCurrentWeapon(WeaponSlotType* wslot = NULL);
 const Weapon* getCurrentWeapon(WeaponSlotType* wslot = NULL) const;
 void setFiringConditionForCurrentWeapon() const;
 void adjustModelConditionForWeaponStatus();
///< Check to see if I should change my model condition.
 void fireCurrentWeapon(Object *target);
 void fireCurrentWeapon(const Coord3D* pos);
 void preFireCurrentWeapon( const Object *victim );
 UnsignedInt getLastShotFiredFrame() const;
///< Get the frame a shot was last fired on
 ObjectID getLastVictimID() const;
///< Get the last victim we shot at
 Weapon* findWaypointFollowingCapableWeapon();
 Bool getAmmoPipShowingInfo(Int& numTotal, Int& numFull) const;
 void notifyFiringTrackerShotFired( const Weapon* weaponFired, ObjectID victimID ) ;
 CanAttackResult getAbleToAttackSpecificObject( AbleToAttackType t, const Object* target, CommandSourceType commandSource, WeaponSlotType specificSlot = (WeaponSlotType)-1 ) const;
 CanAttackResult getAbleToUseWeaponAgainstTarget( AbleToAttackType attackType, const Object *victim, const Coord3D *pos, CommandSourceType commandSource, WeaponSlotType specificSlot = (WeaponSlotType)-1 ) const;
 Bool chooseBestWeaponForTarget(const Object* target, WeaponChoiceCriteria criteria, CommandSourceType cmdSource);
 void setModelConditionState( ModelConditionFlagType a );
 void clearModelConditionState( ModelConditionFlagType a );
 void clearAndSetModelConditionState( ModelConditionFlagType clr, ModelConditionFlagType set );
 void setSpecialModelConditionState( ModelConditionFlagType set, UnsignedInt frames = 0 );
 void clearSpecialModelConditionStates();
 void clearModelConditionFlags( const ModelConditionFlags& clr );
 void setModelConditionFlags( const ModelConditionFlags& set );
 void clearAndSetModelConditionFlags( const ModelConditionFlags& clr, const ModelConditionFlags& set );
 void setWeaponSetFlag(WeaponSetType wst);
 void clearWeaponSetFlag(WeaponSetType wst);
 inline Bool testWeaponSetFlag(WeaponSetType wst) const 
 {
  return m_curWeaponSetFlags.test(wst);
  
 }
 inline const WeaponSetFlags& getWeaponSetFlags() const 
 {
  return m_curWeaponSetFlags;
  
 }
 Bool setWeaponLock( WeaponSlotType weaponSlot, WeaponLockType lockType )
 {
  return m_weaponSet.setWeaponLock( weaponSlot, lockType );
  
 }
 void releaseWeaponLock(WeaponLockType lockType)
 {
  m_weaponSet.releaseWeaponLock(lockType);
  
 }
 Bool isCurWeaponLocked() const 
 {
  return m_weaponSet.isCurWeaponLocked();
  
 }
 void setArmorSetFlag(ArmorSetType ast);
 void clearArmorSetFlag(ArmorSetType ast);
 Bool testArmorSetFlag(ArmorSetType ast) const;
 Bool hasSpecialPower( SpecialPowerType type ) const;
 Bool hasAnySpecialPower() const;
 void setWeaponBonusCondition(WeaponBonusConditionType wst);
 void clearWeaponBonusCondition(WeaponBonusConditionType wst);
 Bool testWeaponBonusCondition(WeaponBonusConditionType wst) const 
 {
  return (m_weaponBonusCondition & (1 << wst)) != 0;
  
 }
 inline WeaponBonusConditionFlags getWeaponBonusCondition() const 
 {
  return m_weaponBonusCondition;
  
 }
 Bool getSingleLogicalBonePosition(const char* boneName, Coord3D* position, Matrix3D* transform) const;
 Bool getSingleLogicalBonePositionOnTurret(WhichTurretType whichTurret, const char* boneName, Coord3D* position, Matrix3D* transform) const;
 Int getMultiLogicalBonePosition(const char* boneNamePrefix, Int maxBones, Coord3D* positions, Matrix3D* transforms, Bool convertToWorld = TRUE ) const;
 Bool didEnter(const PolygonTrigger *pTrigger) const;
 Bool didExit(const PolygonTrigger *pTrigger) const;
 Bool isInside(const PolygonTrigger *pTrigger) const;
 ExitInterface *getObjectExitInterface() const;
///< get exit interface is present
 Bool hasExitInterface() const 
 {
  return getObjectExitInterface() != 0;
  
 }
 ObjectShroudStatus getShroudedStatus(Int playerIndex) const;
 DisabledMaskType getDisabledFlags() const 
 {
  return m_disabledMask;
  
 }
 Bool isDisabled() const 
 {
  return m_disabledMask.any();
  
 }
 Bool clearDisabled( DisabledType type );
 void setDisabled( DisabledType type );
 void setDisabledUntil( DisabledType type, UnsignedInt frame );
 Bool isDisabledByType( DisabledType type ) const 
 {
  return TEST_DISABLEDMASK( m_disabledMask, type );
  
 }
 UnsignedInt getDisabledUntil( DisabledType type = DISABLED_ANY ) const;
 void pauseAllSpecialPowers( const Bool disabling ) const;
 void checkDisabledStatus();
 void clearLeechRangeModeForAllWeapons();
 Int getNumConsecutiveShotsFiredAtTarget( const Object *victim) const;
 void setHealthBoxOffset( const Coord3D& offset ) 
 {
  m_healthBoxOffset = offset;
  
 }
///< for special amorphous like angry mob
 void defect( Team *newTeam, UnsignedInt detectionTime );
 void goInvulnerable( UnsignedInt time );
 virtual void reactToTurretChange( WhichTurretType turret, Real oldRotation, Real oldPitch );
 Bool isStructure(void) const;
 Bool isFactionStructure(void) const;
 Bool isNonFactionStructure(void) const;
 Bool isHero(void) const;
 Bool getReceivingDifficultyBonus() const 
 {
  return m_isReceivingDifficultyBonus;
  
 }
 void setReceivingDifficultyBonus(Bool receive);
 inline UnsignedInt getSafeOcclusionFrame(void) 
 {
  return m_safeOcclusionFrame;
  
 }
//< this is an object specific frame at which it's safe to enable building occlusion.
 inline void	setSafeOcclusionFrame(UnsignedInt frame) 
 {
  m_safeOcclusionFrame = frame;
  
 }
 void friend_adjustPowerForPlayer( Bool incoming );
 protected:
 void setOrRestoreTeam( Team* team, Bool restoring );
 void onDisabledEdge(Bool becomingDisabled);
 void crc( Xfer *xfer );
 void xfer( Xfer *xfer );
 void loadPostProcess();
 void handleShroud();
 void handleValueMap();
 void handleThreatMap();
 Module* findModule(NameKeyType key) const;
 Bool didEnterOrExit() const;
 void setID( ObjectID id );
 virtual Object *asObjectMeth() 
 {
  return this;
  
 }
 virtual const Object *asObjectMeth() const 
 {
  return this;
  
 }
 virtual Real calculateHeightAboveTerrain(void) const;
// Calculates the actual height above terrain.  Doesn't use cache.
 void updateTriggerAreaFlags(void);
 void setTriggerAreaFlagsForChangeInPosition(void);
 void look();
 void unlook();
 void shroud();
 void unshroud();
 void addValue();
 void removeValue();
 void addThreat();
 void removeThreat();
 virtual void reactToTransformChange(const Matrix3D* oldMtx, const Coord3D* oldPos, Real oldAngle);
 private:
 enum ObjectPrivateStatusBits
 
 {
  EFFECTIVELY_DEAD		= (1 << 0),		///< Object is effectively dead
  UNDETECTED_DEFECTOR	= (1 << 1),		///< set to true when I defect from my team; set to false when I attack anything or when time runs out
  CAPTURED						= (1 << 2),		///< set to true if I've been captured, otherwise, its false. (Note: Never becomes false once it's true)
  OFF_MAP							= (1 << 3)		///< set to true if I am known to be OFF the current map.
  
 }
 ;
 ObjectID			m_id;
///< this object's unique ID
 ObjectID			m_producerID;
///< object that produced us, if any
 ObjectID			m_builderID;
///< object that is building or has built us (dozers or workers are builders)
 Drawable*			m_drawable;
///< drawable (if any) for this object
 AsciiString		m_name;
///< internal name
 Object *			m_next;
 Object *			m_prev;
 ObjectStatusMaskType		m_status;
///< status bits (see ObjectStatusMaskType)
 GeometryInfo	m_geometryInfo;
 AIGroup*			m_group;
///< if non-NULL, we are part of this group of agents
 SightingInfo		*m_partitionLastLook;
///< Where and for whom I last looked, so I can undo its effects when I stop
 SightingInfo		*m_partitionRevealAllLastLook;
///< And a seperate look to reveal at a different range if so marked
 Int							m_visionSpiedBy[MAX_PLAYER_COUNT];
///< Reference count of having units spied on by players.
 PlayerMaskType	m_visionSpiedMask;
///< For quick lookup and edge triggered maintenance
 SightingInfo	*m_partitionLastShroud;
///< Where and for whom I last shrouded, so I can undo its effects when I stop
 SightingInfo	*m_partitionLastThreat;
///< Where and for whom I last delt with threat, so I can undo its effects when I stop
 SightingInfo	*m_partitionLastValue;
///< Where and for whom I last delt with value, so I can undo its effects when I stop
 Real					m_visionRange;
///< looking range
 Real					m_shroudClearingRange;
///< looking range for shroud ONLY
 Real					m_shroudRange;
///< like looking range, this is how far I shroud others' looks
 DisabledMaskType	m_disabledMask;
 UnsignedInt				m_disabledTillFrame[ DISABLED_COUNT ];
 UnsignedInt		m_smcUntil;
 enum 
 {
  NUM_SLEEP_HELPERS = 8 
 }
 ;
 ObjectRepulsorHelper*					m_repulsorHelper;
 ObjectSMCHelper*							m_smcHelper;
 ObjectWeaponStatusHelper*			m_wsHelper;
 ObjectDefectionHelper*				m_defectionHelper;
 StatusDamageHelper*						m_statusDamageHelper;
 SubdualDamageHelper*					m_subdualDamageHelper;
 TempWeaponBonusHelper*				m_tempWeaponBonusHelper;
 FiringTracker*								m_firingTracker;
///< Tracker is really a "helper" and is included NUM_SLEEP_HELPERS
 BehaviorModule**							m_behaviors;
// BehaviorModule, not BehaviorModuleInterface
 ContainModuleInterface*				m_contain;
 BodyModuleInterface*					m_body;
 StealthUpdate*                m_stealth;
 AIUpdateInterface*						m_ai;
///< ai interface (if any), cached for handy access. (duplicate of entry in the module array!)
 PhysicsBehavior*							m_physics;
///< physics interface (if any), cached for handy access. (duplicate of entry in the module array!)
 PartitionData*								m_partitionData;
///< our PartitionData
 RadarObject*									m_radarData;
///< radar data
 ExperienceTracker*						m_experienceTracker;
///< Manages experience, gaining levels, and value when killed
 Object*												m_containedBy;
 ObjectID											m_xferContainedByID;
///< xfer uses IDs to store pointers and looks them up after
 UnsignedInt										m_containedByFrame;
///< frame we were contained by m_containedBy
 Real													m_constructionPercent;
///< for objects being built ... this is the amount completed (0.0 to 100.0)
 UpgradeMaskType								m_objectUpgradesCompleted;
///< Bit field of upgrades locally completed.
 Team*													m_team;
///< team that is current owner of this guy
 AsciiString										m_originalTeamName;
///< team that was the original ("birth") team of this guy
 Color													m_indicatorColor;
///< if nonzero, use this instead of controlling player's color
 Coord3D												m_healthBoxOffset;
///< generally zero, except for special amorphous ones like angry mob
 MAKE_DLINK(Object, TeamMemberList)			///< other Things that are members of the same team
 WeaponSet											m_weaponSet;
 WeaponSetFlags								m_curWeaponSetFlags;
 WeaponBonusConditionFlags			m_weaponBonusCondition;
 Byte													m_lastWeaponCondition[WEAPONSLOT_COUNT];
 SpecialPowerMaskType					m_specialPowerBits;
///< bits determining what kind of special abilities this object has access to.
 ObjectID m_soleHealingBenefactorID;
///< who is the only other object that can give me this non-stacking heal benefit?
 UnsignedInt m_soleHealingBenefactorExpirationFrame;
///< on what frame can I accept healing (thus to switch) from a new benefactor
 enum 
 {
  MAX_TRIGGER_AREA_INFOS = 5 
 }
 ;
 TTriggerInfo									m_triggerInfo[MAX_TRIGGER_AREA_INFOS];
 UnsignedInt										m_enteredOrExitedFrame;
 ICoord3D											m_iPos;
 PathfindLayerEnum							m_layer;
// Layer object is pathing on.
 PathfindLayerEnum							m_destinationLayer;
// Layer of current path goal.
 FormationID										m_formationID;
 Coord2D												m_formationOffset;
 AsciiString										m_commandSetStringOverride;
///< To allow specific object to switch command sets
 UnsignedInt										m_safeOcclusionFrame;
///<flag used by occlusion renderer so it knows when objects have exited their production building.
 Bool													m_isSelectable;
 Bool													m_modulesReady;
#if defined(_DEBUG) || defined(_INTERNAL)
 Bool													m_hasDiedAlready;
#endif
 UnsignedByte									m_scriptStatus;
///< status as set by scripting, corresponds to ORed ObjectScriptStatusBits
 UnsignedByte									m_privateStatus;
///< status bits that are never directly accessible to outside world
 Byte													m_numTriggerAreasActive;
 Bool													m_singleUseCommandUsed;
 Bool													m_isReceivingDifficultyBonus;
 
}
;
// end class Object
#ifdef DEBUG_LOGGING
AsciiString DescribeObject(const Object *obj);
#endif // DEBUG_LOGGING
#if defined(_DEBUG) || defined(_INTERNAL)
	#define DEBUG_OBJECT_ID_EXISTS
#else
	#undef DEBUG_OBJECT_ID_EXISTS
#endif
#ifdef DEBUG_OBJECT_ID_EXISTS
extern ObjectID TheObjectIDToDebug;
#endif
#endif // _OBJECT_H_
// This must go first in EVERY cpp file int the GameEngine
#include "Common/ActionManager.h"
#include "Common/GameAudio.h"
#include "Common/GameEngine.h"
#include "Common/MessageStream.h"
#include "Common/MiscAudio.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ThingTemplate.h"
#include "GameLogic/Damage.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Squad.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/UpdateModule.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Display.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Keyboard.h"
#include "GameClient/SelectionInfo.h"
#include "GameClient/SelectionXlat.h"
#include "GameClient/TerrainVisual.h"
namespace _STL

{
 extern template _Vector_base<Object *, allocator<Object *> >::_Vector_base(
 size_t, const allocator<Object *> &);
 
}
#ifdef _INTERNAL
#endif
#if defined(_DEBUG) || defined(_INTERNAL)
static Bool TheHurtSelectionMode = false;
static Bool TheDebugSelectionMode = false;
#endif
static Bool currentlyLookingForSelection( )

{
 return TheInGameUI->getGUICommand() == NULL;
 
}
static Bool areAllSelected(const DrawableList& listToCheck)

{
 for (DrawableList::const_iterator it = listToCheck.begin(); it != listToCheck.end(); ++it) 
 {
  Drawable *draw = *it;
  if (!draw) continue;
  Object *obj = *reinterpret_cast<Object **>(reinterpret_cast<char *>(draw) + 0xFC);
  if (obj) 
  {
   Object *redirect = *reinterpret_cast<Object **>(reinterpret_cast<char *>(obj) + 0x274);
   if (redirect) 
   {
    const char *templ = *reinterpret_cast<const char **>(reinterpret_cast<char *>(redirect) + 4);
    if ((static_cast<unsigned char>(templ[0x115]) & 0x20) != 0) 
    {
     Drawable *replacement = redirect->getDrawable();
     if (replacement) draw = replacement;
     
    }
    
   }
   
  }
  if (!*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(draw) + 0x43C))
  return false;
  
 }
 return true;
 
}
// ?SelectionTranslator::translateGameMessage present-unmatched  // retail 0x0043003C body is a banked partial; retained because it fixes the private EBX call ABI of the 0x0042FA0D helper
static void deselectAll()

{
 TheInGameUI->deselectAllDrawables();
 
}
static Bool selectSingleDrawableWithoutSound( Drawable *draw )

{
 deselectAll();
 TheInGameUI->selectDrawable( draw );
 Object *obj = draw->getObject();
 if (obj != NULL) 
 {
  GameMessage *msg = TheMessageStream->appendMessage(GameMessage::MSG_CREATE_SELECTED_GROUP_NO_SOUND);
  msg->appendBooleanArgument(TRUE);
  msg->appendObjectIDArgument(obj->getID());
  
 }
 return true;
 
}
GameMessageDisposition SelectionTranslator::translateGameMessage(const GameMessage *msg)

{
 GameMessageDisposition disp = KEEP_MESSAGE;
 if(	!TheInGameUI->getInputEnabled() )
 
 {
  if( m_dragSelecting )
  
  {
   m_dragSelecting = FALSE;
   TheInGameUI->setSelecting( FALSE );
   TheInGameUI->endAreaSelectHint(NULL);
   TheTacticalView->setMouseLock( FALSE );
   
  }
  return KEEP_MESSAGE;
  
 }
 GameMessage::Type t = msg->getType();
 switch (t)
 
 {
  case GameMessage::MSG_META_BEGIN_FORCEATTACK:
  TheInGameUI->setForceAttackMode( true );
  break;
  case GameMessage::MSG_META_END_FORCEATTACK:
  TheInGameUI->setForceAttackMode( false );
  break;
  case GameMessage::MSG_RAW_MOUSE_POSITION:
  
  {
   ICoord2D pixel;
   pixel = msg->getArgument( 0 )->pixel;
   if (m_leftMouseButtonIsDown)
   
   {
    ICoord2D delta;
    delta.x = abs(pixel.x - m_selectFeedbackAnchor.x);
    delta.y = abs(pixel.y - m_selectFeedbackAnchor.y);
    if (delta.x > TheMouse->m_dragTolerance || delta.y > TheMouse->m_dragTolerance)
    
    {
     if (m_dragSelecting == false)
     
     {
      m_dragSelecting = true;
      TheTacticalView->setMouseLock( TRUE );
      TheInGameUI->setSelecting( TRUE );
      
     }
     
    }
    if (m_dragSelecting)
    
    {
     GameMessage *hintMsg = TheMessageStream->appendMessage( GameMessage::MSG_AREA_SELECTION_HINT );
     IRegion2D pixelRegion;
     buildRegion( &m_selectFeedbackAnchor, &pixel, &pixelRegion );
     hintMsg->appendPixelRegionArgument( pixelRegion );
     
    }
    
   }
   else //left button is not down (not drag select)
   
   {
    GameMessage *mouseoverMessage;
    UnsignedInt pickType = getPickTypesForContext( true  );
    Drawable *underCursor = TheTacticalView->pickDrawable( &pixel, TheInGameUI->isInForceAttackMode(), (PickType) pickType );
    Object *objUnderCursor = underCursor ? underCursor->getObject() : NULL;
    if( objUnderCursor && (!objUnderCursor->isEffectivelyDead() || objUnderCursor->isKindOf( KINDOF_ALWAYS_SELECTABLE )) )
    
    {
     mouseoverMessage = TheMessageStream->appendMessage( GameMessage::MSG_MOUSEOVER_DRAWABLE_HINT );
     mouseoverMessage->appendDrawableIDArgument( underCursor->getID() );
     
    }
    else// else this is a mouseover terrain
    
    {
     Coord3D position;
     TheTacticalView->screenToTerrain( &pixel, &position );
     mouseoverMessage = TheMessageStream->appendMessage( GameMessage::MSG_MOUSEOVER_LOCATION_HINT );
     mouseoverMessage->appendLocationArgument( position );
     
    }
    
   }
   break;
   
  }
  case GameMessage::MSG_MOUSE_LEFT_DOUBLE_CLICK:
  
  {
   Int modifiers = msg->getArgument(1)->integer;
   if (TheInGameUI->isInForceAttackMode())
   break;
   const IRegion2D& region = msg->getArgument(0)->pixelRegion;
   if (region.height() == 0 && region.width() == 0)
   
   {
    Bool selectAcrossMap = (BitTest(modifiers, KEY_STATE_ALT) ? TRUE : FALSE);
    Drawable *picked = TheTacticalView->pickDrawable( &region.lo, FALSE, PICK_TYPE_SELECTABLE);
    if (picked == NULL)
    break;
    if (!picked->isMassSelectable())
    break;
    Object *pickedObj = picked->getObject();
    if (pickedObj == NULL || !pickedObj->isLocallyControlled())
    break;
    DrawableList listOfSelectedDrawables;
    if (TheInGameUI->isInPreferSelectionMode()) 
    {
     listOfSelectedDrawables	= *TheInGameUI->getAllSelectedDrawables();
     
    }
    selectSingleDrawableWithoutSound(picked);
    if (selectAcrossMap)
    TheInGameUI->selectMatchingAcrossMap();
    else
    TheInGameUI->selectMatchingAcrossScreen();
    GameMessage *pickMsg = TheMessageStream->appendMessage( GameMessage::MSG_AREA_SELECTION );
    pickMsg->appendDrawableIDArgument( picked->getID() );
/// note we are putting in a drawable id
    if (TheInGameUI->isInPreferSelectionMode() && !listOfSelectedDrawables.empty()) 
    {
     GameMessage *selectMore = TheMessageStream->appendMessage( GameMessage::MSG_CREATE_SELECTED_GROUP_NO_SOUND );
     selectMore->appendBooleanArgument(FALSE);
     for (DrawableListIt it = listOfSelectedDrawables.begin(); it != listOfSelectedDrawables.end(); ++it) 
     {
      Drawable *draw = *it;
      if (draw && draw->isSelectable()) 
      {
       TheInGameUI->selectDrawable(draw);
       selectMore->appendObjectIDArgument(draw->getObject()->getID());
       
      }
      
     }
     
    }
    disp = DESTROY_MESSAGE;
    
   }
   break;
   
  }
  case GameMessage::MSG_MOUSEOVER_DRAWABLE_HINT:
  
  {
   if (TheInGameUI->isScrolling()) 
   {
    break;
    
   }
   DrawableID id = msg->getArgument(0)->drawableID;
   Drawable *draw = TheGameClient->findDrawableByID(id);
   if (!draw) 
   {
    break;
    
   }
   GameMessage::Type msgType = TheGameClient->evaluateContextCommand(draw, draw->getPosition(), CommandTranslator::EVALUATE_ONLY);
   if( msgType == GameMessage::MSG_INVALID )
   
   {
    TheInGameUI->createMouseoverHint(msg);
// this sets the cursor
    disp = DESTROY_MESSAGE;
    const CommandButton *command = TheInGameUI->getGUICommand();
    Bool ignoreCommand = FALSE;
    if( command )
    
    {
     if( command->getCommandType() == GUI_COMMAND_ATTACK_MOVE ||
     command->getCommandType() == GUI_COMMAND_GUARD ||
     command->getCommandType() == GUI_COMMAND_GUARD_WITHOUT_PURSUIT ||
     command->getCommandType() == GUI_COMMAND_GUARD_FLYING_UNITS_ONLY )
     
     {
      ignoreCommand = TRUE;
      
     }
     
    }
    if( !ignoreCommand && !draw->getTemplate()->isKindOf( KINDOF_SHRUBBERY ) )
    
    {
     if( CanSelectDrawable( draw, FALSE ) )
     
     {
      TheMouse->setCursor(Mouse::SELECTING);
      
     }
     else
     
     {
      TheMouse->setCursor( Mouse::ARROW );
      
     }
     
    }
    
   }
   break;
   
  }
  case GameMessage::MSG_MOUSE_LEFT_CLICK:
  
  {
   if (TheInGameUI->isQuitMenuVisible())
   
   {
    disp = DESTROY_MESSAGE;
    break;
    
   }
   IRegion2D selectionRegion = msg->getArgument(0)->pixelRegion;
   Bool isPoint = (selectionRegion.height() == 0 && selectionRegion.width() == 0);
   DrawableList drawablesThatWillSelect;
   PickDrawableStruct pds;
   pds.drawableListToFill = &drawablesThatWillSelect;
   TheTacticalView->iterateDrawablesInRegion(&selectionRegion, addDrawableToList, &pds);
   if (drawablesThatWillSelect.empty())
   
   {
    break;
    
   }
   const DrawableList *currentList = TheInGameUI->getAllSelectedDrawables();
   if (!currentlyLookingForSelection())
   
   {
    break;
    
   }
   SelectionInfo si;
   if (contextCommandForNewSelection(currentList, &drawablesThatWillSelect, &si, isPoint))
   
   {
    break;
    
   }
   Bool addToGroup = TheInGameUI->isInPreferSelectionMode();
   if (si.currentCountEnemies > 0 ||
   si.currentCountCivilians > 0 ||
   si.currentCountFriends > 0 ||
   si.currentCountMineBuildings > 0)
   
   {
    addToGroup = FALSE;
    
   }
   if (si.newCountMine > 0)
   
   {
    si.selectMine = TRUE;
    if ( si.newCountMineBuildings == 1 && si.newCountMine == 1 )
    
    {
     addToGroup = FALSE;
     si.selectMineBuildings = TRUE;
     
    }
    else if ( si.newCountMineBuildings > 0 )////////////// SO SORRY, I KNOW THIS IS MICKEY MOUSE ///////////////////
    
    {
// What we are after here is to allow the drag select to get the building,
     Bool onlyTheOneBuildingIsSelectableAnyway = TRUE;
     DrawableID buildingID = INVALID_DRAWABLE_ID;
     for (DrawableListIt it = drawablesThatWillSelect.begin(); it != drawablesThatWillSelect.end(); ++it)
     
     {
      const Drawable *d = *it;
      if ( d->isKindOf( KINDOF_STRUCTURE ) )
      
      {
// make sure there is really only the one building in the list, as it may be multiply listed
       if ( buildingID == INVALID_DRAWABLE_ID ) // this is the first building
       buildingID = d->getID();
       else if ( buildingID != d->getID() )//oops, more than one building!
       onlyTheOneBuildingIsSelectableAnyway = FALSE;
       
      }
      else if ( d->isSelectable() )
      onlyTheOneBuildingIsSelectableAnyway = FALSE;
      if ( ! onlyTheOneBuildingIsSelectableAnyway )
      break;
      
     }
     if ( onlyTheOneBuildingIsSelectableAnyway )
     
     {
      addToGroup = FALSE;
      si.selectMineBuildings = TRUE;
      
     }
     
    }
    
   }
   else if (si.newCountEnemies > 0 && si.newCountCivilians > 0 && si.newCountFriends > 0)
   
   {
    break;
    
   }
   else if (si.newCountEnemies == 1)
   
   {
    addToGroup = FALSE;
    si.selectEnemies = TRUE;
    
   }
   else if (si.newCountCivilians == 1)
   
   {
    addToGroup = FALSE;
    si.selectCivilians = TRUE;
    
   }
   else if (si.newCountFriends == 1)
   
   {
    addToGroup = FALSE;
    si.selectFriends = TRUE;
    
   }
   if (!(si.selectMine || si.selectEnemies || si.selectCivilians || si.selectFriends))
   
   {
    break;
    
   }
   disp = DESTROY_MESSAGE;
   m_lastGroupSelGroup = -1;
   if (TheInGameUI->isInPreferSelectionMode() && isPoint && areAllSelected(drawablesThatWillSelect))
   
   {
    GameMessage *newMsg = TheMessageStream->appendMessage(GameMessage::MSG_REMOVE_FROM_SELECTED_GROUP);
    Drawable *draw = NULL;
    DrawableListIt it;
    for (it = drawablesThatWillSelect.begin(); it != drawablesThatWillSelect.end(); ++it)
    
    {
     draw = *it;
     if (!draw)
     
     {
      continue;
      
     }
     Object *objToDeselect = draw->getObject();
     if (!objToDeselect)
     
     {
      continue;
      
     }
     newMsg->appendObjectIDArgument(objToDeselect->getID());
     TheInGameUI->deselectDrawable(draw);
     
    }
    
   }
   else
   
   {
    if (!addToGroup)
    
    {
     deselectAll();
     
    }
    GameMessage *newMsg = TheMessageStream->appendMessage(GameMessage::MSG_CREATE_SELECTED_GROUP);
    newMsg->appendBooleanArgument(!addToGroup);
    Player *localPlayer = ThePlayerList->getLocalPlayer();
    Int newDrawablesSelected = 0;
    Drawable *draw = NULL;
    DrawableListIt it;
    for (it = drawablesThatWillSelect.begin(); it != drawablesThatWillSelect.end(); ++it)
    
    {
     draw = *it;
     if (!draw)
     
     {
      continue;
      
     }
     Object *obj = draw->getObject();
     if (!obj)
     
     {
      continue;
      
     }
     if (obj && obj->getContainedBy() != NULL)
     
     {
      continue;
      
     }
     Drawable *drawToSelect = NULL;
     ObjectID objToAppend = INVALID_ID;
     if (si.selectMine && obj->isLocallyControlled())
     
     {
      if (!obj->isKindOf(KINDOF_STRUCTURE) || si.selectMineBuildings)
      
      {
       drawToSelect = draw;
       objToAppend = obj->getID();
       
      }
      
     }
     else
     
     {
      Relationship rel = localPlayer->getRelationship(obj->getTeam());
      if (si.selectEnemies && rel == ENEMIES)
      
      {
       drawToSelect = draw;
       objToAppend = obj->getID();
       
      }
      else if (si.selectCivilians && rel == NEUTRAL)
      
      {
       drawToSelect = draw;
       objToAppend = obj->getID();
       
      }
      else if (si.selectFriends && rel == ALLIES)
      
      {
       drawToSelect = draw;
       objToAppend = obj->getID();
       
      }
      
     }
     if (drawToSelect && objToAppend != INVALID_ID)
     
     {
      newMsg->appendObjectIDArgument(objToAppend);
      TheInGameUI->selectDrawable(drawToSelect);
      ++newDrawablesSelected;
      
     }
     
    }
    if( newDrawablesSelected > 1 )
    
    {
     localPlayer->getAcademyStats()->recordDragSelection();
     
    }
    if (newDrawablesSelected == 1 && draw)
    
    {
#if defined(_DEBUG) || defined(_INTERNAL)
     if (m_HandOfGodSelectionMode && draw)
     
     {
      Object* obj = draw->getObject();
      if (obj)
      
      {
       TheAudio->addAudioEvent(&TheAudio->getMiscAudio()->m_noCanDoSound);
       GameMessage* msg = TheMessageStream->appendMessage( GameMessage::MSG_DEBUG_KILL_OBJECT );
       msg->appendObjectIDArgument(obj->getID());
       
      }
      disp = DESTROY_MESSAGE;
      break;
      
     }
     else
     if (TheHurtSelectionMode && draw)
     
     {
      Object* obj = draw->getObject();
      if (obj)
      
      {
       TheAudio->addAudioEvent(&TheAudio->getMiscAudio()->m_noCanDoSound);
       GameMessage* msg = TheMessageStream->appendMessage( GameMessage::MSG_DEBUG_HURT_OBJECT );
       msg->appendObjectIDArgument(obj->getID());
       
      }
      disp = DESTROY_MESSAGE;
      break;
      
     }
  #ifdef DEBUG_OBJECT_ID_EXISTS
     if (TheDebugSelectionMode && draw && draw->getObject())
     
     {
      if (TheObjectIDToDebug == 0)
      
      {
       TheObjectIDToDebug = draw->getObject()->getID();
       AsciiString msg;
       msg.format("Item %s %08x selected for debugging",draw->getTemplate()->getName().str(),TheObjectIDToDebug);
       UnicodeString msgu;
       msgu.translate(msg);
       TheInGameUI->message(msgu);
       disp = DESTROY_MESSAGE;
       break;
       
      }
      
     }
  #endif
#endif
#if defined(_ALLOW_DEBUG_CHEATS_IN_RELEASE)
     if (m_HandOfGodSelectionMode && draw)
     
     {
      Object* obj = draw->getObject();
      if (obj)
      
      {
       TheAudio->addAudioEvent(&TheAudio->getMiscAudio()->m_noCanDoSound);
       GameMessage* msg = TheMessageStream->appendMessage( GameMessage::MSG_DEBUG_KILL_OBJECT );
       msg->appendObjectIDArgument(obj->getID());
       
      }
      disp = DESTROY_MESSAGE;
      break;
      
     }
#endif
     
    }
    
   }
   if (disp == DESTROY_MESSAGE)
   TheInGameUI->clearAttackMoveToMode();
   break;
   
  }
  case GameMessage::MSG_RAW_MOUSE_LEFT_BUTTON_DOWN:
  
  {
   m_leftMouseButtonIsDown = true;
   m_selectFeedbackAnchor = msg->getArgument( 0 )->pixel;
   break;
   
  }
  case GameMessage::MSG_RAW_MOUSE_LEFT_BUTTON_UP:
  
  {
   m_leftMouseButtonIsDown = FALSE;
   if (m_dragSelecting) 
   {
    m_dragSelecting = FALSE;
    TheTacticalView->setMouseLock( FALSE );
    TheInGameUI->setSelecting( FALSE );
    TheInGameUI->endAreaSelectHint(NULL);
    GameMessage *dragMsg = TheMessageStream->appendMessage( GameMessage::MSG_AREA_SELECTION );
    IRegion2D selectionRegion;
    buildRegion( &m_selectFeedbackAnchor, &msg->getArgument(0)->pixel, &selectionRegion );
    dragMsg->appendPixelRegionArgument( selectionRegion );
    
   }
   else
   
   {
    if( !TheInGameUI->getGUICommand() && !TheKeyboard->isShift() && !TheKeyboard->isCtrl() && !TheKeyboard->isAlt() )
    
    {
     if( TheGlobalData->m_useAlternateMouse && TheInGameUI->getPendingPlaceSourceObjectID() == INVALID_ID )
     
     {
      if( !TheInGameUI->getPreventLeftClickDeselectionInAlternateMouseModeForOneClick() )
      
      {
       deselectAll();
       
      }
      else
      
      {
       TheInGameUI->setPreventLeftClickDeselectionInAlternateMouseModeForOneClick( FALSE );
       
      }
      
     }
     
    }
    
   }
   break;
   
  }
  case GameMessage::MSG_RAW_MOUSE_RIGHT_BUTTON_DOWN:
  
  {
   m_deselectFeedbackAnchor = msg->getArgument( 0 )->pixel;
   m_lastClick = (UnsignedInt) msg->getArgument( 2 )->integer;
   TheTacticalView->getPosition(&m_deselectDownCameraPosition);
   break;
   
  }
  case GameMessage::MSG_RAW_MOUSE_RIGHT_BUTTON_UP:
  
  {
   ICoord2D delta, pixel;
   UnsignedInt currentTime;
   Coord3D cameraPos;
   TheTacticalView->getPosition(&cameraPos);
   cameraPos.sub(&m_deselectDownCameraPosition);
   pixel = msg->getArgument( 0 )->pixel;
   currentTime = (UnsignedInt) msg->getArgument( 2 )->integer;
   delta.x = m_deselectFeedbackAnchor.x - pixel.x;
   delta.y = m_deselectFeedbackAnchor.y - pixel.y;
   Bool isClick = TRUE;
   if (isClick &&
   abs(delta.x) > TheMouse->m_dragTolerance ||
   abs(delta.y) > TheMouse->m_dragTolerance)
   
   {
    isClick = FALSE;
    
   }
   if (isClick &&
   currentTime - m_lastClick > TheMouse->m_dragToleranceMS)
   
   {
    isClick = FALSE;
    
   }
   if (isClick &&
   cameraPos.length() > TheMouse->m_dragTolerance3D)
   
   {
    isClick = FALSE;
    
   }
   if (isClick)
   
   {
    if( TheInGameUI->getGUICommand() )
    
    {
     TheInGameUI->setGUICommand( NULL );
     disp = DESTROY_MESSAGE;
     TheInGameUI->setScrolling( FALSE );
     
    }
    else
    
    {
     if (! TheGlobalData->m_useAlternateMouse || TheInGameUI->getPendingPlaceSourceObjectID() != INVALID_ID)
     
     {
      deselectAll();
      
     }
     
    }
    
   }
   break;
   
  }
  case GameMessage::MSG_META_CREATE_TEAM0:
  case GameMessage::MSG_META_CREATE_TEAM1:
  case GameMessage::MSG_META_CREATE_TEAM2:
  case GameMessage::MSG_META_CREATE_TEAM3:
  case GameMessage::MSG_META_CREATE_TEAM4:
  case GameMessage::MSG_META_CREATE_TEAM5:
  case GameMessage::MSG_META_CREATE_TEAM6:
  case GameMessage::MSG_META_CREATE_TEAM7:
  case GameMessage::MSG_META_CREATE_TEAM8:
  case GameMessage::MSG_META_CREATE_TEAM9:
  
  {
   Int group = t - GameMessage::MSG_META_CREATE_TEAM0;
   if ( group >= 0 && group < 10 )
   
   {
    DEBUG_LOG(("META: create team %d\n",group));
    GameMessage *newmsg = TheMessageStream->appendMessage((GameMessage::Type)(GameMessage::MSG_CREATE_TEAM0 + group));
    Drawable *drawable = TheGameClient->getDrawableList();
    while (drawable != NULL)
    
    {
     if (drawable->isSelected() && drawable->getObject() && drawable->getObject()->isLocallyControlled())
     
     {
      newmsg->appendObjectIDArgument(drawable->getObject()->getID());
      
     }
     drawable = drawable->getNextDrawable();
     
    }
    
   }
   disp = DESTROY_MESSAGE;
   break;
   
  }
  case GameMessage::MSG_META_SELECT_TEAM0:
  case GameMessage::MSG_META_SELECT_TEAM1:
  case GameMessage::MSG_META_SELECT_TEAM2:
  case GameMessage::MSG_META_SELECT_TEAM3:
  case GameMessage::MSG_META_SELECT_TEAM4:
  case GameMessage::MSG_META_SELECT_TEAM5:
  case GameMessage::MSG_META_SELECT_TEAM6:
  case GameMessage::MSG_META_SELECT_TEAM7:
  case GameMessage::MSG_META_SELECT_TEAM8:
  case GameMessage::MSG_META_SELECT_TEAM9:
  
  {
   Int group = t - GameMessage::MSG_META_SELECT_TEAM0;
   if ( group >= 0 && group < 10 )
   
   {
    DEBUG_LOG(("META: select team %d\n",group));
    UnsignedInt now = TheGameLogic->getFrame();
    if ( m_lastGroupSelTime == 0 )
    
    {
     m_lastGroupSelTime = now;
     
    }
    if ( now - m_lastGroupSelTime < 20 && group == m_lastGroupSelGroup )
    
    {
     DEBUG_LOG(("META: DOUBLETAP select team %d\n",group));
     Player *player = ThePlayerList->getLocalPlayer();
     if (player)
     
     {
      Squad *selectedSquad = player->getHotkeySquad(group);
      if (selectedSquad != NULL)
      
      {
       VecObjectPtr objlist = selectedSquad->getLiveObjects();
       Int numObjs = objlist.size();
       if (numObjs > 0)
       
       {
        TheTacticalView->lookAt( objlist[numObjs-1]->getDrawable()->getPosition() );
        
       }
       
      }
      
     }
     
    }
    else
    
    {
     TheInGameUI->deselectAllDrawables( false );
//No need to post message because we're just creating a new group!
     TheMessageStream->appendMessage((GameMessage::Type)(GameMessage::MSG_SELECT_TEAM0 + group));
     Player *player = ThePlayerList->getLocalPlayer();
     if (player)
     
     {
      Squad *selectedSquad = player->getHotkeySquad(group);
      if (selectedSquad != NULL)
      
      {
       VecObjectPtr objlist = selectedSquad->getLiveObjects();
       Int numObjs = objlist.size();
       for (Int i = 0; i < numObjs; ++i)
       
       {
        if( objlist[i]->getControllingPlayer() == player )
        
        {
         TheInGameUI->selectDrawable(objlist[i]->getDrawable());
         
        }
        
       }
       
      }
      
     }
     
    }
    m_lastGroupSelTime = now;
    m_lastGroupSelGroup = group;
    
   }
   disp = DESTROY_MESSAGE;
   break;
   
  }
  case GameMessage::MSG_META_ADD_TEAM0:
  case GameMessage::MSG_META_ADD_TEAM1:
  case GameMessage::MSG_META_ADD_TEAM2:
  case GameMessage::MSG_META_ADD_TEAM3:
  case GameMessage::MSG_META_ADD_TEAM4:
  case GameMessage::MSG_META_ADD_TEAM5:
  case GameMessage::MSG_META_ADD_TEAM6:
  case GameMessage::MSG_META_ADD_TEAM7:
  case GameMessage::MSG_META_ADD_TEAM8:
  case GameMessage::MSG_META_ADD_TEAM9:
  
  {
   Int group = t - GameMessage::MSG_META_ADD_TEAM0;
   if ( group >= 0 && group < 10 )
   
   {
    DEBUG_LOG(("META: select team %d\n",group));
    UnsignedInt now = TheGameLogic->getFrame();
    if ( m_lastGroupSelTime == 0 )
    
    {
     m_lastGroupSelTime = now;
     
    }
    if ( now - m_lastGroupSelTime < 20 && group == m_lastGroupSelGroup )
    
    {
     DEBUG_LOG(("META: DOUBLETAP select team %d\n",group));
     Player *player = ThePlayerList->getLocalPlayer();
     if (player)
     
     {
      Squad *selectedSquad = player->getHotkeySquad(group);
      if (selectedSquad != NULL)
      
      {
       VecObjectPtr objlist = selectedSquad->getLiveObjects();
       Int numObjs = objlist.size();
       if (numObjs > 0)
       
       {
        TheTacticalView->lookAt( objlist[numObjs-1]->getDrawable()->getPosition() );
        
       }
       
      }
      
     }
     
    }
    else
    
    {
     Drawable *draw = TheInGameUI->getFirstSelectedDrawable();
     if( draw && draw->isKindOf( KINDOF_STRUCTURE ) )
     
     {
      TheInGameUI->deselectAllDrawables();
      
     }
     TheMessageStream->appendMessage((GameMessage::Type)(GameMessage::MSG_ADD_TEAM0 + group));
     Player *player = ThePlayerList->getLocalPlayer();
     if (player)
     
     {
      Squad *selectedSquad = player->getHotkeySquad(group);
      if (selectedSquad != NULL)
      
      {
       VecObjectPtr objlist = selectedSquad->getLiveObjects();
       Int numObjs = objlist.size();
       for (Int i = 0; i < numObjs; ++i)
       
       {
        TheInGameUI->selectDrawable(objlist[i]->getDrawable());
        
       }
       
      }
      
     }
     
    }
    m_lastGroupSelTime = now;
    m_lastGroupSelGroup = group;
    
   }
   disp = DESTROY_MESSAGE;
   break;
   
  }
  case GameMessage::MSG_META_VIEW_TEAM0:
  case GameMessage::MSG_META_VIEW_TEAM1:
  case GameMessage::MSG_META_VIEW_TEAM2:
  case GameMessage::MSG_META_VIEW_TEAM3:
  case GameMessage::MSG_META_VIEW_TEAM4:
  case GameMessage::MSG_META_VIEW_TEAM5:
  case GameMessage::MSG_META_VIEW_TEAM6:
  case GameMessage::MSG_META_VIEW_TEAM7:
  case GameMessage::MSG_META_VIEW_TEAM8:
  case GameMessage::MSG_META_VIEW_TEAM9:
  
  {
   Int group = t - GameMessage::MSG_META_VIEW_TEAM0;
   if ( group >= 1 && group <= 10 )
   
   {
    DEBUG_LOG(("META: view team %d\n",group));
    Player *player = ThePlayerList->getLocalPlayer();
    if (player)
    
    {
     Squad *selectedSquad = player->getHotkeySquad(group);
     if (selectedSquad != NULL)
     
     {
      VecObjectPtr objlist = selectedSquad->getLiveObjects();
      Int numObjs = objlist.size();
      if (numObjs > 0)
      
      {
       TheTacticalView->lookAt( objlist[ numObjs-1 ]->getDrawable()->getPosition() );
       
      }
      
     }
     
    }
    
   }
   disp = DESTROY_MESSAGE;
   break;
   
  }
  case GameMessage::MSG_META_OPTIONS:
  
  {
   m_leftMouseButtonIsDown = FALSE;
   break;
   
  }
#if defined(_DEBUG) || defined(_INTERNAL)
  case GameMessage::MSG_META_DEMO_TOGGLE_HAND_OF_GOD_MODE:
  
  {
   if ( !TheGameLogic->isInMultiplayerGame() )
   
   {
    m_HandOfGodSelectionMode = !m_HandOfGodSelectionMode;
    TheInGameUI->message( UnicodeString( L"Meta Hand-Of-God Mode is %s" ), m_HandOfGodSelectionMode ? L"ON" : L"OFF" );
    disp = DESTROY_MESSAGE;
    
   }
   break;
   
  }
#endif
#if defined(_ALLOW_DEBUG_CHEATS_IN_RELEASE)
  case GameMessage::MSG_CHEAT_TOGGLE_HAND_OF_GOD_MODE://NOTICE THE DIFFERENT NAME!!!!!!!!!!!!!!!!!!!!!!!!!!ML
  
  {
   if ( !TheGameLogic->isInMultiplayerGame() )
   
   {
    m_HandOfGodSelectionMode = !m_HandOfGodSelectionMode;
    TheInGameUI->message( UnicodeString( L"Hand-Of-God Mode is %s" ), m_HandOfGodSelectionMode ? L"ON" : L"OFF" );
    disp = DESTROY_MESSAGE;
    
   }
   break;
   
  }
#endif
#if defined(_DEBUG) || defined(_INTERNAL)
  case GameMessage::MSG_META_DEMO_TOGGLE_HURT_ME_MODE:
  
  {
   if ( !TheGameLogic->isInMultiplayerGame() )
   
   {
    TheHurtSelectionMode = !TheHurtSelectionMode;
    TheInGameUI->message( UnicodeString( L"Hurt-Me Mode is %s" ), TheHurtSelectionMode ? L"ON" : L"OFF" );
    disp = DESTROY_MESSAGE;
    
   }
   break;
   
  }
#endif
#if defined(_DEBUG) || defined(_INTERNAL)
  case GameMessage::MSG_META_DEMO_DEBUG_SELECTION:
  
  {
   TheDebugSelectionMode = !TheDebugSelectionMode;
   TheInGameUI->message( UnicodeString( L"Debug-Selected-Item Mode is %s" ), TheDebugSelectionMode ? L"ON" : L"OFF" );
		#ifdef DEBUG_OBJECT_ID_EXISTS
   TheObjectIDToDebug = INVALID_ID;
		#endif
   disp = DESTROY_MESSAGE;
   break;
   
  }
#endif
  
 }
 return disp;
 
}
