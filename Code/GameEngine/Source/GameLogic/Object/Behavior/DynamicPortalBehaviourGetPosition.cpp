// cl: /I. /O1 /G7 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB
// stlport
// Native460DF6..460F18 RET4; WB10AD000 names IsEndPortalAboveWall.
// Primary+4 data/+8 object; data118 bone count/11C name/120 waypoint vec/140 selected index.
// Existing 12-byte BfmeRadarWorldPoint view owns the byte-and-relocation-twin
// empty coordinate callbacks47A6A9/B3FD0. Reuse the owned callbacks without
// creating a private Coord3D or pin. Original coordinate C++ lifetime type is
// not claimed by this ABI view; the target array stride and callbacks are native.
#include "Code/Libraries/Include/Lib/Coord3D.h"
class Matrix3D;
struct BfmeRadarWorldPoint : Coord3D {
 BfmeRadarWorldPoint(); ~BfmeRadarWorldPoint();
};
typedef char PortalPointSize[(sizeof(BfmeRadarWorldPoint)==12)?1:-1];
class Object { public:
 int getMultiLogicalBonePosition(const char *,int,Coord3D *,Matrix3D *,bool,int) const;
 const Coord3D *getPosition() const { return &position; }
 char pad[0x38]; Coord3D position;
};
// WB10AD000 IsEndPortalAboveWall and native460DF6..460F18 RET4.
// Default coordinate callbacks are already rowed at47A6A9/B3FD0. Existing
// TU's coordinate view retains those declarations without a header-wide edit.
struct PortalQueryPoint {float x,y,z;__forceinline PortalQueryPoint(const Coord3D&r){x=r.x;y=r.y;z=r.z;}};
// stlport
#include <vector>
struct PortalWaypointDescriptor {int boneIndex,observed4; __forceinline PortalWaypointDescriptor(const PortalWaypointDescriptor&r):boneIndex(r.boneIndex),observed4(r.observed4){} };
class DynamicPortalBehaviourModuleData {public:
 char pad0[0x118];int numberOfBones;const char *nameBuffer;
 std::vector<PortalWaypointDescriptor> waypoints;
 char pad12C[0x140-0x12C];int aboveWallIndex;
};
class Pathfinder {public:bool IsPointOnWall(int,bool);};
class AI;
extern AI *TheAI;
struct PortalAIView {char pad0[0x10];Pathfinder *pathfinder;};
class DynamicPortalBehaviour {public:
 bool IsEndPortalAboveWall(Coord3D *out);
 void *vptr;const DynamicPortalBehaviourModuleData *data;Object *object;
};
bool DynamicPortalBehaviour::IsEndPortalAboveWall(Coord3D *out)
{
 const DynamicPortalBehaviourModuleData *portalData=data;
 if(portalData->aboveWallIndex<0)goto fallback; if(portalData->aboveWallIndex>=(int)portalData->waypoints.size()) { fallback:
  if(out) {const Object *obj=object; *out=obj->position;} return true;
 }
 BfmeRadarWorldPoint bones[16];
 const char *buf=portalData->nameBuffer;Object *obj=object;
 obj->getMultiLogicalBonePosition(buf ? buf+8 : "", portalData->numberOfBones,bones,0,true,0);
 PortalWaypointDescriptor way=portalData->waypoints[portalData->aboveWallIndex]; PortalQueryPoint selected(bones[way.boneIndex]);
 if(out)*out=*(const Coord3D*)&selected;
 PortalAIView *ai=(PortalAIView*)TheAI; Pathfinder *path=ai->pathfinder; bool result=path->IsPointOnWall((int)&selected,false); return result;
}
