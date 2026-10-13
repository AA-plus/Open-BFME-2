// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /I. /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// Lookup via g_009FF000 Rva002D06CA 0x002D06CA, GlobalData guard +0x1110,
// set<AsciiString> ctor 0x000D3A71 + notify 0x0033CF34 + merge 0x0061F010,
// CreateMask via ji_006291ae, ThingFactory::newObject 0x002D0A23,
// Thing::setOrientation 0x0030AB9D + setPosition 0x0030AA80, pathfind + adjust.
// Evidence: callers at 0x002411BF 0x00241DA1 0x00242195, prev 0x00240DF1 next 0x002418E2.
#include "ascii_string.h"
#include <math.h>
#define _OPERATOR_NEW_DEFINED_
#include "vector3.h"
#include <set>

#include "../../Code/Libraries/Include/Lib/Coord3D.h"
struct Rva001408C0Target;
class AssetList {public:AssetList():pad(0),changed(true){} private:_STL::set<Rva001408C0Target*> prototypes;unsigned pad;bool changed;};
struct AssetLoadMode{bool alternate;AssetLoadMode():alternate(false){}};
class ThingTemplate;
class ThingFactory;
class Team;
class Object;
class Thing;
class LocomotorSet;
class Pathfinder;
class BFMEPathfinderMapShim;
class GlobalData;
class AI;
struct CreateMask;

extern ThingFactory *TheThingFactory;

class GlobalData
{
public:
	char m_pad[0x1110];
	unsigned char m_1110;
};

extern GlobalData *TheWritableGlobalData;

void __cdecl bfmeMergeReceiverKeys(int value);

extern "C" void *__cdecl memset(void *,int,unsigned int);
#pragma function(memset)

struct CreateMask
{
	char m_data[0x10];
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);	// 0x002D06CA
public:
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, bool flag);
};

class Thing
{
public:
	void setOrientation(float v);
	void setPosition(const Coord3D *pos);
};

class ThingTemplate
{
public:
	char m_pad[0x108];
	unsigned char m_flags108;
	char m_pad2[0x4D0 - 0x109];
	float m_orient4D0;
	void GetAssetList(int a, int b);
};

class Team
{
public:
	char m_pad[0x5D];
	unsigned char m_5d;
	unsigned char m_5e;
};

class LocomotorSet
{
public:
	char m_data[4];
};

class AIUpdateInterface
{
public:
	char m_pad[0x1CC];
	LocomotorSet m_loco;
};

enum NameKeyType {NetworkNameKeyUnknown};
class Module;
class Object
{
public:
	void rva0028ACEE(int a, int b);
protected: Module *findModule(NameKeyType) const;
public: Module *lookupModule(NameKeyType n) const {return findModule(n);}
};

class Rva0028CBFD
{
public:
	void rva0028CBFD();
};

class BFMEPathfinderMapShim
{
public:
	void addObjectToPathfindMap(Object *obj);
};

class Pathfinder
{
public:
 void AddObjectToPathfindMap(Object*);
	bool AdjustDestination(Object *obj, const LocomotorSet &set, Coord3D *dst, const Coord3D *group);
};

class AI
{
public:
	char m_pad[0x10];
	Pathfinder *m_pf;
};

extern AI *TheAI;

class Player
{
public:
	char m_pad[0x2EC];
	Team *m_team;
	char pad2F0[0x3AC-0x2F0];
	int livingId;
	void onStructureCreated(Object*,Object*);
	void onUnitCreated(Object*,Object*);
	void onStructureConstructionComplete(Object*,Object*,bool);
};

static Object *placeObjectAtPosition(int slot, AsciiString name, const Coord3D *pos, Player *player, const void *playerTemplate)
{
	void *tmplRaw = (void *)TheThingFactory->findTemplate(name);
	if (tmplRaw == 0)
		return 0;
	ThingTemplate *tmpl = (ThingTemplate *)tmplRaw;
	if (TheWritableGlobalData->m_1110 == 0) {
		AssetLoadMode mode;
		AssetList receivers;
		tmpl->GetAssetList((int)&receivers, (int)&mode);
		bfmeMergeReceiverKeys((int)&receivers);
	}
	Object *obj;
	{
	CreateMask mask;
	memset(&mask, 0, 0x10);
	Team *team = player->m_team;
	obj = TheThingFactory->newObject((const ThingTemplate *)tmpl, team, &mask, false);
	}
	if (obj) {
	ThingTemplate *t2 = *(ThingTemplate **)((char *)obj + 4);
	((Thing *)obj)->setOrientation(t2->m_orient4D0);
	((Thing *)obj)->setPosition(pos);
	Team *t = player->m_team;
	((Rva0028CBFD *)obj)->rva0028CBFD();
	if (t != 0) {
		if (t->m_5d == 0) {
			t->m_5e = 1;
			t->m_5d = 1;
		}
	}
	TheAI->m_pf->AddObjectToPathfindMap(obj);
	AIUpdateInterface *aiu = *(AIUpdateInterface **)((char *)obj + 0x258);
	if (aiu && !((*(ThingTemplate **)((char *)obj + 4))->m_flags108 & 4)) {
		LocomotorSet *loco = &aiu->m_loco;
		Pathfinder *pf = TheAI->m_pf;
		if (pf->AdjustDestination(obj, *loco, (Coord3D *)pos, 0)) {
			obj->rva0028ACEE((int)pos, 1);
			((Thing*)obj)->setPosition(pos);
		}
	}
	}
	return obj;
}


#include "../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Rva003F468D;
class Rva0020E89C;
class Rva002E2903Player;
class Rva0020E6B7RegionManager {public:Rva003F468D *rva0020E6B7();};
class Rva0020EAF6View {public:Rva0020E89C *rva0020EAF6(int);};
class Rva002BA8F1Logic {public:char pad[0xB0];Rva0020E6B7RegionManager *regions;char padB4[4];int currentRegion;Rva002E2903Player *find(int,unsigned*);};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class LivingWorldBattle {public:void *rva003F4FBD(void*);};
struct LivingArmy {char pad[0x20];int id;};
struct LivingBuildingTemplate {char pad[0xC];AsciiString name;};
class LivingWorldBuilding {public:char pad[0x18];int id;char pad1C[0xC];const AsciiString &getName()const {const LivingBuildingTemplate &d=*definition;return d.name;} LivingBuildingTemplate *definition;};
class LivingWorldRegion {public:char pad[0x13C];int owner;int GetOwner()const{return owner;} int rva003F05CE();LivingWorldBuilding *GetBuildingByIndex(int)const;};
class Waypoint {public:Waypoint(unsigned,AsciiString,const Coord3D*,AsciiString,AsciiString,AsciiString,bool,int,AsciiString);virtual ~Waypoint();char pad[8];Coord3D position;char rest[0xC0-0x18];};
Waypoint *Rva00506CC3FindWaypoint(const AsciiString&);
void ValidateLivingWorldBuildPlotWaypoints(Waypoint*,int);
class Rva0040D280Sub {public:void method(Object*,int);};
class PlayerTemplate;
// WB 0x00CFC810 identifies this GameLogic.cpp placement pass. Retail
// 0x0024104A..0x00241230 reads Player +0x3AC and region owner +0x13C;
// The caller at 0x00241D34 retains Player/template/slot on the stack.
// WB 0x00CFC810 exposes all five source arguments; forwarding template and
// slot into the static object placer preserves that ABI although their final
// machine-code uses disappear. The 486-byte helper itself is unchanged.
// Keep the inline owner and building-name accessors: their compiler lifetimes
// reproduce the saved player ID and retail register allocation without volatile.
static void PlaceLivingWorldObjectsForPlayer(Player *player,const PlayerTemplate *pt,int startIndex,int slot,Waypoint *rally) {
 if(TheGameLogic->m_114==3) return;
 LivingWorldRegion *region; int armyId;
 {
 int livingId=player->livingId;
 if(livingId==-1) return;
 LivingWorldBattle *battle=(LivingWorldBattle*)((Rva002BA8F1Logic*)TheLivingWorldLogic)->regions->rva0020E6B7();
 if(!battle) return;
 Rva002E2903Player *worldPlayer=((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(livingId,0);
 if(!worldPlayer) return;
 LivingArmy *army=(LivingArmy*)battle->rva003F4FBD(worldPlayer);
 armyId=army?army->id:0;
 if(!armyId) return;

 int currentRegion=((Rva002BA8F1Logic*)TheLivingWorldLogic)->currentRegion;
 Rva0020EAF6View *manager=(Rva0020EAF6View*)((Rva002BA8F1Logic*)TheLivingWorldLogic)->regions;
 region=(LivingWorldRegion*)manager->rva0020EAF6(currentRegion);
 if(!region) return;
 if(region->GetOwner()!=livingId) return;
 }
 {
 AsciiString waypointName("Player_1_Start");
 Waypoint *start=Rva00506CC3FindWaypoint(waypointName);
 if(!start) return;
 ValidateLivingWorldBuildPlotWaypoints(start,region->rva003F05CE());
 for(int i=0;i<region->rva003F05CE();++i){
  LivingWorldBuilding *building=region->GetBuildingByIndex(i);
  const AsciiString &name=building->getName();
  if(name.isEmpty()) continue;
  waypointName.format("Player_1_BuildPlot_%d",i+1);
  Waypoint *waypoint=Rva00506CC3FindWaypoint(waypointName);
  if(!waypoint) continue;
  Coord3D pos; pos.x=waypoint->position.x;pos.y=waypoint->position.y;pos.z=waypoint->position.z;
  Object *obj=placeObjectAtPosition(slot,name,&pos,player,pt);
  if(!obj) continue;
  player->onStructureCreated(0,obj);
  player->onStructureConstructionComplete(0,obj,false);
  ((Rva0040D280Sub*)((char*)TheGameLogic+0x184))->method(obj,armyId);
  *(int*)((char*)obj+0x464)=building->id;
 }
}

}

// Reference: GeneralsMD GameLogic.cpp:548 network-start placement, via
// Open-BFME-1 cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Donor supplies the
// purpose and base flow; WB CFABB0 confirms the BFME additions. Native
// 0x00241C75..0x002421F5 supplies every offset,
// mode branch, CastleBehavior radius, ten starting offsets and polar math.
class GameSlot {public:char pad[0x10];int startPos;};
class PlayerTemplate {public:char pad[0x44];AsciiString startingBuilding;};
class Rva001FD19E {public:const char *rva001FD19E(int);};
class Rva001FD2D9 {public:Coord3D *rva001FD2D9(Coord3D*,int);};
struct FindPositionOptions {unsigned flags;float minRadius,maxRadius,startAngle,maxZDelta;void *ignoreObject;const void *sourceToPathToDest;void *relationshipObject;};
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;
class NetworkPartitionDispatch {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void update();};
class TerrainLogic {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual float getGroundHeight(float,float,Coord3D*);};
extern TerrainLogic *TheTerrainLogic;
struct NetworkObjectPrefix {char pad[0x88];AsciiString name;char pad8C[0xB8-0x8C];float radius,width;float getWidth()const{return width;}};
class Rva00395A60 {public:float rva00395A60();};
class CastleBehavior {public:static NameKeyType rva0003955DA();};
class Rva002A9BF2 {public:void rva002A9D02(int,Object*,int);};
void rva00241C75(int slotNum,const GameSlot *slot,Player *player,const PlayerTemplate *pt) {
 int startPos=slot->startPos;
 AsciiString waypointName;waypointName.format("Player_%d_Start",startPos+1);
 AsciiString rallyName;rallyName.format("Player_%d_Rally",startPos+1);
 Waypoint *start=Rva00506CC3FindWaypoint(waypointName);
 Waypoint *rally=Rva00506CC3FindWaypoint(rallyName);
 if(!start)return;
 Coord3D pos;pos.x=start->position.x;pos.y=start->position.y;pos.z=start->position.z;
 pos.z=TheTerrainLogic->getGroundHeight(pos.x,pos.y,0);
 if(TheGameLogic->m_114!=3){PlaceLivingWorldObjectsForPlayer(player,pt,startPos+1,slotNum,rally?rally:start);return;}
 AsciiString buildingName(pt->startingBuilding);
 float radius=50.0f;
 // Retail saves the yard at [ebp-1C] before its null branch. This local
 // preserves that stack home and leaves EBX available for the shared zero.
 // Volatile here is a codegen choice, not a claim about the original type.
 Object *volatile yard=0;
 if(!buildingName.isEmpty() && *(const int*)((const char*)start+0x60)==0) {
  Object *object=placeObjectAtPosition(slotNum,buildingName,&pos,player,pt);
  yard=object;
  if(!object)return;
  NetworkObjectPrefix *view=reinterpret_cast<NetworkObjectPrefix*>(object);
  radius=view->radius;
  Module *castle=object->lookupModule(CastleBehavior::rva0003955DA());
  if(castle)radius=reinterpret_cast<Rva00395A60*>(castle)->rva00395A60();
  AsciiString name;name.format("BASE_FLAG_%d",startPos+1);view->name=name;
  player->onStructureCreated(0,object);
  reinterpret_cast<Rva002A9BF2*>(player)->rva002A9D02(0,object,0);
  pos.y-=view->getWidth()/2.0f;
  pos.z=TheTerrainLogic->getGroundHeight(pos.x,pos.y,0);
 }
 if(rally){pos=rally->position;pos.z=TheTerrainLogic->getGroundHeight(pos.x,pos.y,0);}
 Coord3D origin;origin.x=start->position.x;origin.y=start->position.y;origin.z=start->position.z;
 Object *savedYard=yard;if(savedYard)origin=*reinterpret_cast<const Coord3D*>((const char*)savedYard+0x38);
 for(int i=0;i<10;++i) {
  const AsciiString &unitTemplate=*reinterpret_cast<const AsciiString*>(reinterpret_cast<Rva001FD19E*>(const_cast<PlayerTemplate*>(pt))->rva001FD19E(i));
  AsciiString unitName(unitTemplate);
  if(!unitName.isEmpty()){
  Coord3D offset;reinterpret_cast<Rva001FD2D9*>(const_cast<PlayerTemplate*>(pt))->rva001FD2D9(&offset,i);
  Coord3D zero={0.0f,0.0f,0.0f};Coord3D objPos;
  bool noOffset=(offset==zero);if(noOffset)objPos=pos;
  else {
   Vector3 direction=*reinterpret_cast<const Vector3*>(&offset);direction.Normalize();
   Vector3 delta(1.0f,-1.0f,0.0f);delta.Normalize();
   Vector3 reference(0.0f,1.0f,0.0f);
   float angle=(float)acos(Vector3::Dot_Product(direction,reference));
   if(direction.X*reference.Y-direction.Y*reference.X<0.0f)angle*=-1.0f;
   delta.Rotate_Z(angle);delta*=offset.GetLength();
   objPos=*reinterpret_cast<const Coord3D*>(&delta);
   objPos.x+=origin.x;objPos.y+=origin.y;objPos.z+=origin.z;
  }
  FindPositionOptions options={0,0,0,-99999.9f,10000000000.0f,0,0,0};options.minRadius=radius;options.maxRadius=radius*1.4f;
  reinterpret_cast<NetworkPartitionDispatch*>(ThePartitionManager)->update();
  Coord3D zero2={0.0f,0.0f,0.0f};
  bool found=(offset==zero2)?PartitionManager::findPositionAround(&objPos,&options,&objPos):true;
  if(found){Object *unit=placeObjectAtPosition(slotNum,unitName,&objPos,player,pt);if(unit)player->onUnitCreated(0,unit);}
 }
 }
}
