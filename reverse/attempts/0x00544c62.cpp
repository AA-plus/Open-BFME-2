// ?onEnter@Rva00544EB1@@UAE?AW4StateReturnType@@XZ
// partial score=0.501057 date=2026-10-13
// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /GX-
// Complete native 00544C62..00544E3B (473B), WB 0134AC10/632.
// Target vtable C69E08 slot4 is this body; slot2's getter returns C69E50,
// the literal AIHarvestApproachSiteState. Existing constructor owner Rva00544EB1
// installs that table, so its neutral spelling is retained pending owner rename.
// BF1 cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 clean donor:
// game/GameEngine/Source/GameLogic/AI/AIHarvestApproachSiteState_onEnter.cpp.
// Donor supplies the control-flow guide. Target separately proves machine18,
// owner14, AI258/slot95, locomotor1CC, goal20 and record10/18/1C offsets.
// Corrections to the earlier bank: 12-byte goal copy, no arguments at slot1C,
// slot44 on the target receiver, destination Z initialized from the offset,
// offset halved after every failed retry, and refreshed pathfinder per call.
// Each of the six direct callees already has a matched target row. No new pins.
// Current canonical Coord3D and normal O1/G7/SSE emit474B versus473: state/position
// spill slots swap, scale scheduling and loop-register allocation differ.
// Bounded return/guard/lifetime/compiler trials did not close it. Isolated
// special-member diagnostics also left the mismatch; no shared header change.
#include "Code/Libraries/Include/Lib/Coord3D.h"
enum StateReturnType { STATE_CONTINUE=0, STATE_FAILURE=-2 };
class HarvestTarget {
public:
 virtual void slot00(); virtual void slot01(); virtual void slot02();
 virtual void slot03(); virtual void slot04(); virtual void slot05();
 virtual void slot06(); virtual float slot1C();
 virtual void slot08(); virtual void slot09(); virtual void slot10();
 virtual void slot11(int);
 virtual void slot12(); virtual void slot13(); virtual void slot14();
 virtual void slot15(); virtual void slot16(); virtual void slot44(int);
};
template<int N> class HarvestAISlots : public HarvestAISlots<N-1> {
public: virtual void unused(char (*)[N]);
};
template<> class HarvestAISlots<0> {};
class LocomotorSet;
class AIUpdateInterface : public HarvestAISlots<95> {
public:
 virtual HarvestTarget *getHarvestTarget();
 LocomotorSet &getLocomotorSet() { return *(LocomotorSet *)((char *)this+0x1cc); }
};
class Object {
public:
 char unknown00[0x258]; AIUpdateInterface *ai;
 AIUpdateInterface *getAI() const { return ai; }
};
class StateMachine {
public:
 char unknown00[0x14]; Object *owner;
 Object *getOwner() const { return owner; }
};
struct HarvestRecord {
 char unknown00[0x10]; int owner;
 char unknown14[4]; unsigned char adjust;
 char unknown19[3]; Coord3D offset;
};
class BfmeThingCME { public: int rva0027F108(void *,float,int,int); };
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class Pathfinder {
public:
 bool AdjustDestination(Object *,const LocomotorSet &,Coord3D *,const Coord3D *);
 bool IsPointOnWall(int,bool);
 bool IsPointOnRamp(const Coord3D *);
};
class AI;
extern AI *TheAI;
struct HarvestAIView { char unknown00[0x10]; Pathfinder *pathfinder; };
inline Pathfinder *getPathfinder() { return ((HarvestAIView *)TheAI)->pathfinder; }
float GetGameLogicRandomValueReal(float,float,char *,int);
class AIInternalMoveToState {
public:
 virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
 virtual StateReturnType onEnter();
};
class Rva00544EB1 : public AIInternalMoveToState {
public:
 virtual StateReturnType onEnter();
 char unknown04[0x18-4]; StateMachine *machine;
 char unknown1c[4]; Coord3D goal;
 Object *getMachineOwner() const { return machine->getOwner(); }
};
inline void copyCoord(Coord3D &to,const Coord3D &from) {
 to.x=from.x; to.y=from.y; to.z=from.z;
}
inline void scaleCoord(Coord3D &value,float scale) {
 value.x*=scale; value.y*=scale; value.z*=scale;
}
StateReturnType Rva00544EB1::onEnter()
{
 HarvestTarget *targetPointer=machine->owner->ai->getHarvestTarget();
 if (!targetPointer) return STATE_FAILURE;
 HarvestTarget &target=*targetPointer;
 Coord3D *position=(Coord3D *)((char *)machine+0x24);
 if (!position) return STATE_FAILURE;
 HarvestRecord *record=(HarvestRecord *)((BfmeThingCME *)TheTerrainLogic)->rva0027F108(position,target.slot1C(),0,0);
 if (!record) { target.slot11(1); return STATE_FAILURE; }
 target.slot44(record->owner);
 goal=*position;
 if (!record->adjust) return AIInternalMoveToState::onEnter();
 Coord3D offset;
 copyCoord(offset,record->offset);
 float scale=GetGameLogicRandomValueReal(0.5f,5.0f,
  "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Ai\\AIHarvest.cpp",95);
 scaleCoord(offset,scale);
 int attempt=0;
 for (;attempt<5;++attempt) {
  Coord3D destination;
  destination.z=offset.z;
  destination.x=goal.x+offset.x;
  destination.y=goal.y+offset.y;
  if (getPathfinder()->AdjustDestination(getMachineOwner(),getMachineOwner()->getAI()->getLocomotorSet(),&destination,0)
      && !getPathfinder()->IsPointOnWall((int)&destination,0)
      && !getPathfinder()->IsPointOnRamp(&destination)) {
   goal=destination;
   return AIInternalMoveToState::onEnter();
  }
  offset.x*=0.5f; offset.y*=0.5f; offset.z*=0.5f;
 }
 return AIInternalMoveToState::onEnter();
}
