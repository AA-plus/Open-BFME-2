// ?findMeACrashSite@AIUpdateInterface@@QAE_NMPBUCoord3D@@PAU2@VBfmeFixedStorage0004543D@@@Z
// partial score=0.9325 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /ICode/GameEngine/Source /ICode/Libraries/Include
#include "Common/PartitionRangeQueryCallView.h"
#include "Lib/Coord3D.h"
float Sin(float);
float Cos(float);
class BfmeFixedStorage0004543D { public: BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D&) throw(); unsigned char bytes[28]; };
extern const BfmeFixedStorage0004543D g_009FEFA4;
class Rva000421C8 { public: virtual ~Rva000421C8() {} virtual bool allow(Object*)=0; virtual int getPlayerMask() {return -1;} Rva000421C8 *next; };
class Rva0004584D: public Rva000421C8 { public: Rva0004584D(const BfmeFixedStorage0004543D &, const BfmeFixedStorage0004543D &); virtual ~Rva0004584D() {} virtual bool allow(Object*); BfmeFixedStorage0004543D accepted,rejected; };
extern PartitionManager *ThePartitionManager;
class Object {public: char pad[0x38];Coord3D position;char beforeRadius[0xbc-0x44];float radius;
 __forceinline float Get2DCenterDistanceSquared(const Coord3D *pos) const {float dx=position.x-pos->x,dy=position.y-pos->y;return dx*dx+dy*dy;}
};
struct HitRange {void *begin,*end;char opaque[4];void *cursor;};
static __forceinline float crashSpacing(const float &a,const float &b) { return a<b?b:a; }
class AIUpdateInterface { char pad[8];Object *object; public: bool findMeACrashSite(float,const Coord3D*,Coord3D*,BfmeFixedStorage0004543D); };
bool AIUpdateInterface::findMeACrashSite(float maxRange,const Coord3D *startPos,Coord3D *output,BfmeFixedStorage0004543D mask) {
 Object *self=object;if(!self)return false;
 float spacing=crashSpacing(self->radius,10.0f);
 BfmeWideResult hits=ThePartitionManager->iterateObjectsInRange(startPos,maxRange,0,&Rva0004584D(mask,g_009FEFA4),1);
 for(float range=spacing;range<=maxRange;range+=spacing) {
  float numPoints=(6.2831855f*range)/spacing;
  float step=6.2831855f/numPoints;
  for(float angle=-3.1415927f;angle<=3.1415927f;angle+=step) {
   Coord3D candidate;candidate.x=startPos->x;candidate.y=startPos->y;candidate.z=startPos->z;
   candidate.x+=Sin(angle)*range;
   candidate.y+=Cos(angle)*range;
   bool clear=true;
   HitRange *payload=static_cast<HitRange*>(hits.m_value);payload->cursor=payload->begin;
   for(Object *ob=hits.next();ob;ob=hits.next()) {
    float size=ob->radius+spacing;
    float limit=size*size;
    if(ob->Get2DCenterDistanceSquared(&candidate)<limit){clear=false;break;}
   }
   if(clear){*output=candidate;return true;}
  }
 }
 return false;
}
