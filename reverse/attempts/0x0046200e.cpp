// ?beginSlowDeath@GiantBirdSlowDeathBehavior@@UAEXPBVDamageInfo@@@Z
// partial score=0.97 date=2026-10-13
// ?beginSlowDeath@GiantBirdSlowDeathBehavior@@UAEXPBVDamageInfo@@@Z
// partial score=0.97 date=2026-10-11
// cl: /O1 /G7 /MD /EHsc /arch:SSE
#include <math.h>
struct Coord3D { float x,y,z; };
class DamageInfo;
class ModuleData;
class Thing;
class AIUpdateInterface;
enum KindOfType { KIND_GIANT_BIRD=61 };
struct PhysicsBehavior { char prefix[0x5d]; bool crashFlag,landed; void rva00390557(const Coord3D *,float,float,int,int); };
class Object { public:
 char pad0[0x38]; Coord3D position; float orientation;
 char pad48[0x258-0x48]; AIUpdateInterface *ai; PhysicsBehavior *physics;
 bool isKindOf(KindOfType) const;
};
class ObjectModule { public: virtual ~ObjectModule(); const void *data; Object *object; };
class BehaviorInterface { public: virtual void unknownBehaviorSlot(); };
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1 };
class UpdateModuleInterface { public: virtual UpdateSleepTime update()=0; };
class UpdateModule : public ObjectModule,public BehaviorInterface,public UpdateModuleInterface { int fields[3]; };
class DieModuleInterface { public: virtual void dieSlot(); };
class SlowDeathBehaviorInterface { public: virtual void beginSlowDeath(const DamageInfo *)=0; };
class SlowDeathBehavior : public UpdateModule,public DieModuleInterface,public SlowDeathBehaviorInterface { public:
 virtual UpdateSleepTime update(); virtual void beginSlowDeath(const DamageInfo *);
 char gap[0x3c-0x28]; unsigned flags; bool needsLanding;
 char gap41[0x50-0x41];
};
class GiantBirdSlowDeathBehavior : public SlowDeathBehavior { public:
 virtual UpdateSleepTime update(); virtual void beginSlowDeath(const DamageInfo *);
 unsigned unknown50; Coord3D target; float unknown60; bool unknown64;
};
UpdateSleepTime GiantBirdSlowDeathBehavior::update() {
 PhysicsBehavior *physics=object->physics;
 if(physics->landed)needsLanding=true;
 if(flags&1)SlowDeathBehavior::update();
 return UPDATE_SLEEP_NONE;
}
class BfmeFixedStorage0004543D { public:
 char bytes[28]; ~BfmeFixedStorage0004543D() {} __declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &);
};
struct GiantBirdDeathData { char pad[0x19c]; BfmeFixedStorage0004543D mask; float range; };
class CrashData { public: char prefix[0x538]; float speed; };
class AIUpdateInterface { public:
#define SLOT(N) virtual void unused##N();
 SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
 SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
 SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
 SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
 SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49)
 SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59)
 SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69)
 SLOT(70) SLOT(71) SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79)
 SLOT(80) SLOT(81) SLOT(82) SLOT(83) SLOT(84) SLOT(85) SLOT(86) SLOT(87) SLOT(88) SLOT(89)
 SLOT(90) SLOT(91) SLOT(92) SLOT(93) SLOT(94) SLOT(95) SLOT(96) SLOT(97)
#undef SLOT
 virtual const CrashData *getCrashData();
 bool findMeACrashSite(float,const Coord3D *,Coord3D *,BfmeFixedStorage0004543D);
};
class TerrainLogic { public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void slot3(); virtual void slot4(); virtual void slot5();
 virtual float getGroundHeight(float,float,void *);
};
extern TerrainLogic *TheTerrainLogic;
void GiantBirdSlowDeathBehavior::beginSlowDeath(const DamageInfo *damage)
{
 const GiantBirdDeathData *config=static_cast<const GiantBirdDeathData *>(data);
 SlowDeathBehavior::beginSlowDeath(damage);
 Object *owner=object;
 Coord3D pos={owner->position.x,owner->position.y,owner->position.z};
 AIUpdateInterface *ai=owner->ai;
 PhysicsBehavior *physics=owner->physics;
 if(ai) {
  if(owner->isKindOf(KIND_GIANT_BIRD)) {
   const CrashData *crash=ai->getCrashData();
   if(!crash) return;
   float distance=crash->speed*5.0f;
   if(distance>50.0f) {
    float angle=owner->orientation;
    pos.x+=cos((double)angle)*distance;
    pos.y+=sin((double)angle)*distance;
    physics->crashFlag=true;
   }
  }
  ai->findMeACrashSite(config->range,&pos,&pos,config->mask);
 }
 pos.z=TheTerrainLogic->getGroundHeight(pos.x,pos.y,0);
 target=pos;
 physics->rva00390557(&target,0.0f,30.0f,0,0);
}
