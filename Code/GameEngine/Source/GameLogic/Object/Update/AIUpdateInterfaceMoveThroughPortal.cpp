// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /ICode/Libraries/Include
// WB E3AAE0 names moveThroughPortalWithMicropath in AIUpdate.cpp;
// native 26594F..265AAB is the complete EH-framed 348B RET24 body.
// Prepend order: final, optional mid, portal end, portal start, current
// position. Native Path allocation0x28, object8/position38, path140 and goal1FC/
// 200 are measured accesses, not a full AIUpdateInterface reconstruction.
// BFME1 575ba2b0 and ZH AIUpdate.cpp have no corresponding portal body.
// Existing Path/terrain/pathfinder providers and canonical Coord3D supply
// the verified ABI. Original inline getObject is needed for argument order.
#include <new>
#include "Lib/Coord3D.h"
enum PathfindLayerEnum { LAYER_INVALID=0,LAYER_GROUND=1 };
class Object {public:char pad[0x38];Coord3D position;};
class Path {public:Path();void rva00265596(const Coord3D*,PathfindLayerEnum,int);char before[0xc];bool optimized;char after[0x28-0xd];};
class TerrainLogic {public:PathfindLayerEnum getLayerForDestination(Object*,const Coord3D*);};
extern TerrainLogic *TheTerrainLogic;
struct Rva002EDEABArg;
class Pathfinder {public:void SetDebugPath(Rva002EDEABArg*);};
class AI {public:char before[0x10];Pathfinder *pathfinder;};
extern AI *TheAI;
class GlobalData {public:char before[0x9b8];int debugPath;};
extern GlobalData *TheWritableGlobalData;
class AIUpdateInterface {public:char before[8];Object *object;char toPath[0x140-0xc];Path *path;char toGoal[0x1fc-0x144];int goalType;Coord3D goal;
 Object *getObject()const{return object;}
 void destroyPath();void moveThroughPortalWithMicropath(const Coord3D*,const Coord3D*,int,PathfindLayerEnum,const Coord3D*,const Coord3D*);
};
void AIUpdateInterface::moveThroughPortalWithMicropath(const Coord3D *portalStart,const Coord3D *portalEnd,int id,PathfindLayerEnum layer,const Coord3D *midPos,const Coord3D *finalPos) {
 destroyPath();path=new Path;
 path->rva00265596(finalPos,TheTerrainLogic->getLayerForDestination(getObject(),finalPos),id);
 if(!const_cast<Coord3D*>(midPos)->operator==(*finalPos))path->rva00265596(midPos,TheTerrainLogic->getLayerForDestination(getObject(),midPos),id);
 path->rva00265596(portalEnd,layer,id);
 path->rva00265596(portalStart,TheTerrainLogic->getLayerForDestination(getObject(),portalStart),0x7fffffff);
 Coord3D position;position.x=object->position.x;position.y=object->position.y;position.z=object->position.z;
 path->rva00265596(&position,TheTerrainLogic->getLayerForDestination(getObject(),&position),0x7fffffff);
 path->optimized=true;
 if(TheWritableGlobalData->debugPath==1)TheAI->pathfinder->SetDebugPath(reinterpret_cast<Rva002EDEABArg*>(path));
 goalType=4;goal=*finalPos;
}
