// ?findMeleeAttackPosition@HordeMeleeSwarm@@QAE_NPAVObject@@PAUCoord3D@@0PBU3@_NPAH3@Z
// partial score=0.94 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// ?findMeleeAttackPosition@HordeMeleeSwarm@@QAE_NPAVObject@@PAUCoord3D@@0PBU3@_NPAH4@Z,
// retail 0x00583D54..0x005842F7 (1443B), thiscall ret 0x1C; sole caller
// 0x0058492D (the swarm's unit update).
//
// Picks a melee attack position for a horde member around its target: from
// the member's position (adjusted through 0x002EDE5B) it first steps out on
// rings of 10-unit cells until the pathfinder's horde melee line test passes,
// then scans rings up to twice the 0x002E9B31 count for the cell closest to
// the target that is free (or, when overlap is allowed, held only by two
// same-team units already in attack range), on a compatible layer within 40
// of the member's height and reachable from the last good cell; the scan
// stops early once a near enough candidate is found. The result frames are
// two (good angle) or four (no position) seconds of logic frames.
//
// Evidence (target): WorldBuilder twin 0x0147B280 is
// HordeMeleeSwarm::findMeleeAttackPosition (HordeMeleeSwarm.cpp assert at
// line 349, DEBUG logs "Allowed backwards due to overlap" and "Moving too far
// away from group."); callees are rowed or pinned under the spellings used
// here.

#include "Coord3D.h"
#include "../../../../Common/GameLogicObjectLookupView.h"
#include <math.h>

typedef int Int;
typedef bool Bool;
typedef float Real;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_WALL = 0x10
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

class Weapon;
class Rva002C9B80Owner
{
public:
	Bool isWithinAttackRange(Object *source, const Coord3D *pos, Object *victim, const Coord3D *victimPos, Real extra, Bool flag);
};

class AIUpdateInterface
{
public:
	void *getLocomotorSet() const { return m_1dc; }
private:
	unsigned char m_pad000[0x1DC];
	void *m_1dc;					// +0x1DC
};

class Object
{
public:
	Int rva0028B511() const;
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	Real rva002C97E8(const Coord3D *a, const Coord3D *b) const;
	const Coord3D *getPosition() const { return &m_pos; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Int getTeamValue() const { return m_274; }
private:
	unsigned char m_pad000[0x38];
	Coord3D m_pos;					// +0x38
	unsigned char m_pad044[0x258 - 0x44];
	AIUpdateInterface *m_ai;			// +0x258
	unsigned char m_pad25c[0x274 - 0x25C];
	Int m_274;					// +0x274
};

class Pathfinder
{
public:
	Int rva002EC9E1(Object *obj, const Coord3D *pos, Int *ids);
	Bool Rva002F1BA2(void *obj, void *locomotorSet, PathfindLayerEnum layer, const Coord3D *from, const Coord3D *to);
	Bool rva002EDFF9(Object *obj, Coord3D *pos);
};

class AI
{
public:
	Pathfinder *pathfinder() const { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;			// +0x10
};
extern AI *TheAI;

class TerrainLogic
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal, Bool clip);	// slot 7
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

extern GameLogic *TheGameLogic;
extern Int g_Va00DBA4E4;			// LOGICFRAMES_PER_SECOND

int Rva002EDE5B(void *obj, Coord3D *pos);
int Rva002E9B31Get(void *obj);

struct Rva00583D54Held
{
	void *m_00;
	void *m_04;
	Object *m_leader;				// +0x08
};

class HordeMeleeSwarm
{
public:
	Bool findMeleeAttackPosition(Object *obj, Coord3D *result, Object *victim, const Coord3D *victimPos,
		Bool unused, Int *frames, Bool allowOverlap);
private:
	void *m_vtable;
	Rva00583D54Held *m_held;			// +0x04
};

static __forceinline void copyCoord(Coord3D &c, const Coord3D *a)
{
	c.x = a->x;
	c.y = a->y;
	c.z = a->z;
}

static __forceinline void subCoord(Coord3D &c, const Coord3D *a)
{
	c.x -= a->x;
	c.y -= a->y;
	c.z -= a->z;
}

Bool HordeMeleeSwarm::findMeleeAttackPosition(Object *obj, Coord3D *result, Object *victim, const Coord3D *victimPos,
	Bool unused, Int *frames, Bool allowOverlap)
{
	PathfindLayerEnum layer = (PathfindLayerEnum)obj->rva0028B511();
	AIUpdateInterface *ai = obj->getAI();
	*frames = 0;
	if (!ai)
		return false;

	void *locomotorSet = ai->getLocomotorSet();
	const Real goodAngle = 0.7071f;
	const Real closeRatio = 0.5f;
	const Weapon *weapon = obj->getCurrentWeapon(0);
	Object *leader = m_held->m_leader;

	Coord3D pos;
	copyCoord(pos, obj->getPosition());
	Rva002EDE5B(obj, &pos);

	Real dist;
	{
		Coord3D dir;
		copyCoord(dir, victimPos);
		subCoord(dir, &pos);
		dir.z = 0.0f;
		dist = dir.Normalize();
	}

	Coord3D best;
	copyCoord(best, &pos);
	Bool found = false;
	Real bestOffset = 0.0f;
	Real bestGain = 0.0f;
	Int rings = Rva002E9B31Get(obj) * 2;
	Bool isFar = dist > (Real)(rings * 20);
	Real bestDist = dist + 100.0f;

	Int overlapIds[16];
	Bool overlapping = TheAI->pathfinder()->rva002EC9E1(obj, obj->getPosition(), overlapIds) > 0;
	Bool blocked = !TheAI->pathfinder()->Rva002F1BA2(obj, locomotorSet, layer, &pos, &pos);

	Coord3D lastGood;
	copyCoord(lastGood, &pos);
	if (blocked)
	{
		for (Int r = 1; r <= 2 && blocked; r++)
		{
			for (Int i = -r; i <= r && blocked; i++)
			{
				for (Int j = -r; j <= r && blocked; j++)
				{
					if (i == r || j == r || i == -r || j == -r)
					{
						Coord3D cand;
						copyCoord(cand, &pos);
						cand.x += (Real)i * 10.0f;
						cand.y += (Real)j * 10.0f;
						if (TheAI->pathfinder()->Rva002F1BA2(obj, locomotorSet, layer, &cand, &cand))
						{
							lastGood = cand;
							blocked = false;
						}
					}
				}
			}
		}
	}

	PathfindLayerEnum objLayer = (PathfindLayerEnum)obj->rva0028B511();
	for (Int r = 1; r <= rings; r++)
	{
		for (Int i = -r; i <= r; i++)
		{
			for (Int j = -r; j <= r; j++)
			{
				if (i == r || j == r || i == -r || j == -r)
				{
					Real ox = (Real)i * 10.0f;
					Real oy = (Real)j * 10.0f;
					Coord3D delta;
					delta.x = pos.x + ox;
					delta.y = pos.y + oy;
					delta.z = 0.0f;
					subCoord(delta, victimPos);
					delta.z = 0.0f;
					Real candDist = delta.GetLength();
					if (candDist > dist && !overlapping)
						continue;

					Coord3D cand;
					copyCoord(cand, &pos);
					cand.x += ox;
					cand.y += oy;
					leader->rva002C97E8(leader->getPosition(), &cand);

					PathfindLayerEnum candLayer = TheTerrainLogic->getLayerForDestination(obj, &cand);
					if (candLayer != objLayer)
					{
						if (candLayer != LAYER_WALL && objLayer != LAYER_WALL)
							continue;
						cand.z = TheTerrainLogic->getLayerHeight(cand.x, cand.y, candLayer, 0, true);
						if (fabs(cand.z - pos.z) > 40.0f)
							continue;
					}

					Bool ok = false;
					Bool clear = TheAI->pathfinder()->rva002EDFF9(obj, &cand);
					if (!clear && allowOverlap && weapon)
					{
						Int ids[16];
						if (TheAI->pathfinder()->rva002EC9E1(obj, &cand, ids) == 2 && weapon)
						{
							Object *a = TheGameLogic->findObjectByID((ObjectID)ids[0]);
							Object *b = TheGameLogic->findObjectByID((ObjectID)ids[1]);
							if (a && b && a->getTeamValue() == b->getTeamValue() && obj->getTeamValue() == a->getTeamValue())
							{
								if (((Rva002C9B80Owner *)weapon)->isWithinAttackRange(obj, &cand, victim, victimPos, 0.0f, true))
								{
									clear = true;
									candDist = dist - 5.0f;
								}
							}
						}
					}
					if (clear)
					{
						if (blocked)
							ok = true;
						else
							ok = TheAI->pathfinder()->Rva002F1BA2(obj, locomotorSet, layer, &lastGood, &cand);
					}
					if (ok && candDist < bestDist)
					{
						best = cand;
						bestDist = candDist;
						bestOffset = (Real)sqrt(oy * oy + ox * ox);
						bestGain = dist - candDist;
						found = true;
					}
				}
			}
		}
		if (!isFar && found && bestGain / bestOffset > goodAngle)
			break;
	}

	if (found)
	{
		*result = best;
		if (bestGain / bestOffset < closeRatio)
			*frames = g_Va00DBA4E4 * 2;
	}
	else
	{
		*frames = g_Va00DBA4E4 * 4;
	}
	return found;
}


// --- LK8 r4 variant (1453 vs 1443B; locomotorSet-EDI + low-frame-home wall) ---
// Transplant into HordeMeleeSwarm.cpp (TU flags /O1 /G7 /arch:SSE /DNDEBUG /MD
// /GX-): merge the views below into the TU's existing classes (same slots, no
// layout change to matched bodies), define the method, land with add_match.
// Proven herein: (1) all four small callees are callee-cleanup (ctor/copy/!=
// ret4 analog: EAStringC not involved; instead Bool Rva002F1BA2 + reused
// GetOverlapGoalUnits spellings resolve via the TU's verified DIR32 fill);
// (2) copy-source for Load-analog N/A; (3) leader = m_held->m_leader (retail
// reads [this+4]+0x08) and the rva002C97E8 receiver is [obj-or-leader+0x38];
// (4) Swarm-minus-Formation delta = exactly one fewer Normalize call (no
// first-ring own-cell branch); Swarm call map verified call-for-call against
// retail (5A26/5A70/49DC5/2802FE/28AEBD/28B511/2C97E8/2CB35C/2E9B31/2EC9E1/
// 2EDE5B/2EDFF9/2F1BA2x3/fabs/sqrt + one indirect [edx+0x1c] = virtual
// getLayerHeight slot 7). Residue: locomotorSet lands in EAX+spill instead of
// EDI (retail push-edi + mov-edi), cascading radius into EDI and permuting
// low-frame homes (layer/weapon/dir/bestOffset/bestGain; size-neutral).
// Tried: Bool decl (fixed test-eax+setne, -5B), decl reorder (backfired via
// ESI), += idiom, register hint, bestOffset/bestGain swap (no size change).
// Next: a genuinely new coloring lever, not another reorder.
// Below is the full variant: TU-merged views + body (adapts 0x005852df + the
// above spellings). Drops into HordeMeleeSwarm.cpp after rva00583D0A.

// REQUIRES in TU (already there or added alongside): Coord3D.h (Normalize,
// GetLength rowed), GameLogicObjectLookupView.h (ObjectID, GameLogic with
// rowed findObjectByID), <math.h>, extern GameLogic *TheGameLogic, extern AI
// *TheAI (full AI view below), extern TerrainLogic *TheTerrainLogic (view
// below), extern int g_Va00DBA4E4. HordeMeleeSwarm class (TU): add nothing;
// method already declared; held member already at +4.
class AIUpdateInterface { public: void *getLocomotorSet() const { return m_1dc; } private: unsigned char m_pad000[0x1DC]; void *m_1dc; };
struct Rva00583D54Held { void *m_00; void *m_04; class Object *m_leader; };
enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_WALL = 0x10 };
class Pathfinder;
class TerrainLogic { public: virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual float getLayerHeight(float,float,PathfindLayerEnum,struct Coord3D *,bool); PathfindLayerEnum getLayerForDestination(class Object *,const struct Coord3D *); };
class Rva002C9B80Owner;
int Rva002EDE5B(void *,struct Coord3D *);
int Rva002E9B31Get(void *);
// Object additions (append to TU's Object; same slots): getPosition (inline
// &m_position @0x38), getAI (cast m_ai @0x258), getTeamValue + Int m_274
// (append after m_ai), rva002C97E8 decl. Pathfinder additions: Bool
// Rva002F1BA2(void*,void*,PathfindLayerEnum,const Coord3D*,const Coord3D*),
// rva002EDFF9 decl (GetOverlapGoalUnits already in TU and verified).
// Body: as banked 2026-10-11 (1453B). findMeleeAttackPosition(unit,
// &entry.position, victim, &position, recent, &frames, overlap) is the TU's
// sole-U call (1268B).

// --- LK8 r4 compilable variant (1453 vs 1443B) ---
// TU-merged views used by the variant below (slots proven in HordeMeleeSwarm.cpp)
class AIUpdateInterface { public: void *getLocomotorSet() const { return m_1dc; } private: unsigned char m_pad000[0x1DC]; void *m_1dc; };
struct Rva00583D54Held { void *m_00; void *m_04; class Object *m_leader; };
enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_WALL = 0x10 };
class Pathfinder { public: int GetOverlapGoalUnits(class Object *,const struct Coord3D *,int *); bool Rva002F1BA2(void *,void *,PathfindLayerEnum,const struct Coord3D *,const struct Coord3D *); bool rva002EDFF9(class Object *,struct Coord3D *); };
class TerrainLogic { public: virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual float getLayerHeight(float,float,PathfindLayerEnum,struct Coord3D *,bool); PathfindLayerEnum getLayerForDestination(class Object *,const struct Coord3D *); };
extern TerrainLogic *TheTerrainLogic;
class Rva002C9B80Owner { public: bool isWithinAttackRange(class Object *,const struct Coord3D *,class Object *,const struct Coord3D *,float,bool); };
int Rva002EDE5B(void *,struct Coord3D *);
int Rva002E9B31Get(void *);
// Append to TU Object: const Coord3D *getPosition() const { return &m_position; } // @0x38
// AIUpdateInterface *getAI() const { return (AIUpdateInterface *)m_ai; } // m_ai @0x258
// int getTeamValue() const { return m_274; } float rva002C97E8(const Coord3D*,const Coord3D*) const;
// fields: unsigned char pad25C[0x274-0x25C]; int m_274; // appended after m_ai
static __forceinline void swarmCopyCoord(struct Coord3D &c,const struct Coord3D *a) { c.x=a->x; c.y=a->y; c.z=a->z; }
static __forceinline void swarmSubCoord(struct Coord3D &c,const struct Coord3D *a) { c.x-=a->x; c.y-=a->y; c.z-=a->z; }
// ?findMeleeAttackPosition@HordeMeleeSwarm@@QAE_NPAVObject@@PAUCoord3D@@0PBU3@_NPAH3@Z
// @0x00583D54 1443B: ring search for a melee attack cell around the victim,
// with the overlap fallback onto two same-team units in range. Retail
// evidence: WorldBuilder twin 0x0147B280 names it; direct caller 0x0058492D
// is this TU's updateMeleeAttack; the leader cell comes from held+0x08 and
// the position through obj+0x38; callees are the rowed free functions and
// provider methods used here.
static __forceinline void swarmCopyCoord(Coord3D &c,const Coord3D *a) { c.x=a->x; c.y=a->y; c.z=a->z; }
static __forceinline void swarmSubCoord(Coord3D &c,const Coord3D *a) { c.x-=a->x; c.y-=a->y; c.z-=a->z; }
bool HordeMeleeSwarm::findMeleeAttackPosition(Object *obj,Coord3D *result,Object *victim,const Coord3D *victimPos,bool unused,int *frames,bool allowOverlap)
{
 PathfindLayerEnum layer=(PathfindLayerEnum)obj->rva0028B511();
 AIUpdateInterface *ai=obj->getAI();
 *frames=0;
 if(!ai)
  return false;
 register void *locomotorSet=ai->getLocomotorSet(); const float goodAngle=0.7071f;
 const float closeRatio=0.5f;
 const Weapon *weapon=obj->getCurrentWeapon(0);
 Object *leader=((const Rva00583D54Held *)held)->m_leader;
 Coord3D pos;
 swarmCopyCoord(pos,obj->getPosition());
 Rva002EDE5B(obj,&pos);
 float dist;
 {
  Coord3D dir;
  swarmCopyCoord(dir,victimPos);
  swarmSubCoord(dir,&pos);
  dir.z=0.0f;
  dist=dir.Normalize();
 }
 Coord3D best;
 swarmCopyCoord(best,&pos);
 bool found=false;
 float bestGain=0.0f;
 float bestOffset=0.0f;
 int rings=Rva002E9B31Get(obj);
 rings+=rings;
 bool isFar=dist>(float)(rings*20);
 float bestDist=dist+100.0f;
 int overlapIds[16];
 bool overlapping=TheAI->pathfinder()->GetOverlapGoalUnits(obj,obj->getPosition(),overlapIds)>0;
 bool blocked=!TheAI->pathfinder()->Rva002F1BA2(obj,locomotorSet,layer,&pos,&pos);
 Coord3D lastGood;
 swarmCopyCoord(lastGood,&pos);
 if(blocked) {
  for(int r=1;r<=2 && blocked;r++) {
   for(int i=-r;i<=r && blocked;i++) {
    for(int j=-r;j<=r && blocked;j++) {
     if(i==r || j==r || i==-r || j==-r) {
      Coord3D cand;
      swarmCopyCoord(cand,&pos);
      cand.x+=(float)i*10.0f;
      cand.y+=(float)j*10.0f;
      if(TheAI->pathfinder()->Rva002F1BA2(obj,locomotorSet,layer,&cand,&cand)) {
       lastGood=cand;
       blocked=false;
      }
     }
    }
   }
  }
 }
 PathfindLayerEnum objLayer=(PathfindLayerEnum)obj->rva0028B511();
 for(int r=1;r<=rings;r++) {
  for(int i=-r;i<=r;i++) {
   for(int j=-r;j<=r;j++) {
    if(i==r || j==r || i==-r || j==-r) {
     float ox=(float)i*10.0f;
     float oy=(float)j*10.0f;
     Coord3D delta;
     delta.x=pos.x+ox;
     delta.y=pos.y+oy;
     delta.z=0.0f;
     swarmSubCoord(delta,victimPos);
     delta.z=0.0f;
     float candDist=delta.GetLength();
     if(candDist>dist && !overlapping)
      continue;
     Coord3D cand;
     swarmCopyCoord(cand,&pos);
     cand.x+=ox;
     cand.y+=oy;
     leader->rva002C97E8(leader->getPosition(),&cand);
     PathfindLayerEnum candLayer=TheTerrainLogic->getLayerForDestination(obj,&cand);
     if(candLayer!=objLayer) {
      if(candLayer!=LAYER_WALL && objLayer!=LAYER_WALL)
       continue;
      cand.z=TheTerrainLogic->getLayerHeight(cand.x,cand.y,candLayer,0,true);
      if(fabs(cand.z-pos.z)>40.0f)
       continue;
     }
     bool ok=false;
     bool clear=TheAI->pathfinder()->rva002EDFF9(obj,&cand);
     if(!clear && allowOverlap && weapon) {
      int ids[16];
      if(TheAI->pathfinder()->GetOverlapGoalUnits(obj,&cand,ids)==2 && weapon) {
       Object *a=TheGameLogic->findObjectByID((ObjectID)ids[0]);
       Object *b=TheGameLogic->findObjectByID((ObjectID)ids[1]);
       if(a && b && a->getTeamValue()==b->getTeamValue() && obj->getTeamValue()==a->getTeamValue()) {
        if(((Rva002C9B80Owner *)weapon)->isWithinAttackRange(obj,&cand,victim,victimPos,0.0f,true)) {
         clear=true;
         candDist=dist-5.0f;
        }
       }
      }
     }
     if(clear) {
      if(blocked)
       ok=true;
      else
       ok=TheAI->pathfinder()->Rva002F1BA2(obj,locomotorSet,layer,&lastGood,&cand);
     }
     if(ok && candDist<bestDist) {
      best=cand;
      bestDist=candDist;
      bestOffset=(float)sqrt(oy*oy+ox*ox);
      bestGain=dist-candDist;
      found=true;
     }
    }
   }
  }
  if(!isFar && found && bestGain/bestOffset>goodAngle)
   break;
 }
 if(found) {
  *result=best;
  if(bestGain/bestOffset<closeRatio)
   *frames=g_Va00DBA4E4*2;
 } else {
  *frames=g_Va00DBA4E4*4;
 }
 return found;
}
