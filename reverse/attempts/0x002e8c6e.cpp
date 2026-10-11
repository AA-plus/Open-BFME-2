// ?AdjustMeleeOffset@Pathfinder@@QAEXPAVObject@@0PAUCoord3D@@@Z
// partial score=0.82 date=2026-10-09
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /ICode/Libraries/Include/Lib
// WB D36700 plus native2E8C6E..2E8D74 RET12 establish identity.
#include "Coord3D.h"
class AIUpdateInterface;
struct PathfinderTemplateView { unsigned char prefix[0x108]; unsigned char kinds[24]; };
class Object {
public:
 int rva0028B511() const;
 void rva0028C2DD(Coord3D *) const;
 void *vtable; PathfinderTemplateView *m_template;
 char prefix08[0x38-8]; float position[3];
 char prefix44[0x258-0x44]; AIUpdateInterface *ai;
};
class AIUpdateInterface { public: bool findNearestLabeledContactPointOnTarget(Object *,Coord3D *,const Coord3D *,bool); };
struct PathfindCell { char prefix[12]; unsigned int info; };
int Rva002E6E8AGet(int);
class Pathfinder {
public:
 void AdjustMeleeOffset(Object *,Object *,Coord3D *);
 void *rva001E3647Pos(int,const Coord3D *);
};
struct PathMeleeCoord : Coord3D {
 PathMeleeCoord(const Coord3D &p) { x=p.x; y=p.y; z=p.z; }
 void Scale(float scale) { x*=scale; y*=scale; z*=scale; }
 void Add(const Coord3D &p) { x+=p.x; y+=p.y; z+=p.z; }
};
static __forceinline void scale(Coord3D &p,float k) { p.x*=k; p.y*=k; p.z*=k; }
void Pathfinder::AdjustMeleeOffset(Object *object,Object *target,Coord3D *offset)
{
 int layer=target->rva0028B511();
 int i=0;
 if (object->ai && object->ai->findNearestLabeledContactPointOnTarget(target,offset,(const Coord3D *)object->position,(bool)i)) return;
 Coord3D center;
 target->rva0028C2DD(&center);
 for (;i<20;++i) {
  PathMeleeCoord point(*offset);
  point.Scale((float)i);
  point.Add(center);
  PathfindCell *cell=(PathfindCell *)rva001E3647Pos(layer,&point);
  if (!cell) return;
  if (target->m_template->kinds[7]&0x10) {
   if ((unsigned char)Rva002E6E8AGet((cell->info>>4)&0x3f)) continue;
  } else if ((cell->info&0xf)==4) continue;
  scale(*offset,(float)i);
  return;
 }
}

// --- LK8 r4 TU transplant (266 vs 262B; z-scale scheduling wall) ---
// LK8 r4 TU-merged views (append to TU classes; same slots, no layout change):
// Object += int rva0028B511() const; void rva002C2DD->rva0028C2DD(Coord3D*) const (NOTE spelling: 28C2DD, rowed+matched);
//   split m_pad00[0x38] into m_pad00[0x04]+void*m_template+m_pad08[0x38-0x08]; append m_pad78[0x258-0x78]+AIUpdateInterface*ai;
// AIUpdateInterface + findNearestLabeledContactPointOnTarget(Object*,Coord3D*,const Coord3D*,bool) (rowed 471B);
// Pathfinder += void*rva001E3647Pos(int,const Coord3D*) (rowed 50B); PathfinderTemplateView/PathfindCell/Rva002E6E8AGet as in 0.82 stash.
// ?AdjustMeleeOffset@Pathfinder@@QAEXPAVObject@@0PAUCoord3D@@@Z @0x002E8C6E,
// 262B: melee-offset search around the target. Retail evidence: WorldBuilder
// twin D36700; three-argument ABI; the AI contact-point early return; the
// 20-step scaled offset search with layer/wall gating. All callees are the
// rowed providers declared above; the template kinds view matches the
// reader at [ebx+4]+0x10f.
struct PathMeleeCoord : Coord3D {
 PathMeleeCoord(const Coord3D &p) { x=p.x; y=p.y; z=p.z; }
 void Scale(float scale) { x*=scale; y*=scale; z*=scale; }
 void Add(const Coord3D &p) { x+=p.x; y+=p.y; z+=p.z; }
};
static __forceinline void meleeScale(Coord3D &p,float k) { p.x*=k; p.y*=k; p.z*=k; }
void Pathfinder::AdjustMeleeOffset(Object *object,Object *target,Coord3D *offset)
{
 int layer=target->rva0028B511();
 int i=0;
 if (object->ai && object->ai->findNearestLabeledContactPointOnTarget(target,offset,(const Coord3D *)&object->m_position,(bool)i)) return;
 Coord3D center;
 target->rva0028C2DD(&center);
 for (;i<20;++i) {
  PathMeleeCoord point(*offset);
  point.Scale((float)i);
  point.Add(center);
  PathfindCell *cell=(PathfindCell *)rva001E3647Pos(layer,&point);
  if (!cell) return;
  if (((PathfinderTemplateView *)target->m_template)->kinds[7]&0x10) {
   if ((unsigned char)Rva002E6E8AGet((cell->info>>4)&0x3f)) continue;
  } else if ((cell->info&0xf)==4) continue;
  float fi=(float)i;
  offset->x*=fi;
  float scaledY=offset->y*fi;
  offset->z=fi*offset->z;
  offset->y=scaledY;
  return;
 }
}
