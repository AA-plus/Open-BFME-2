// ?rva005852DF@Rva005852DF@@QAEXXZ
// partial score=0.8957 date=2026-10-13
// ?findMeleeAttackPosition@HordeMeleeFormation@@QAE_NPAVObject@@PAUCoord3D@@0PBU3@_NPAH3@Z
// partial score=0.986842 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX- /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// W7-SOL5 bank: complete owner snapshot, primary1556B currently1549B.
// Existing3 neighbors intact. GetLength43/Normalize66 emitted exact; explicit
// double locals retain native x87 GetLength under this /G7 /arch:SSE caller.
// hordeLine invokes the existing Int method through its native low-AL bool ABI.
// victimPos formal is volatile and main-ring limit is read through volatile ref;
// together they recover the native initial EDI locomotorSet and leader home.
// Remaining: layer/objLayer/bestDist/coordinate/i-j frame cycle and later ring
// counter retention, SSE schedules, loop return/cleanup. Constructor-based
// delta is identical; volatile outer-r test backfires to1561B.
// stlport
// Native00586083..0058619F is284B RET4. WB1472FE0 names
// HordeMeleeFormation::startMeleeAttack (source lines75/83); the native
// constructor00586D8E installs table0086FD90 with this body at slot3.
// The84B record layout and deque+28 follow the existing verified constructor,
// assignment and snapshot transfer00587075. BfmeE12 is an element-size stand-in.
// clear0058592D has the existing neutral BfmeE8 owner: this storage projection
// invokes its verified scalar cleanup, not an element-identity or alias claim.
// Only the external clear declaration is emitted; no second provider or pin.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "Coord3D.h"
#include <vector>
#include <deque>
class Object;
class AIUpdateInterface;
class Weapon;
enum WeaponSlotType 
{
 PRIMARY_WEAPON=0 
}
;
enum ObjectStatusTypes 
{
 FORMATION_STATUS_1C=0x1c 
}
;
enum CommandSourceType 
{
 FORMATION_COMMAND=2 
}
;
template<int N> class FormationSlots : public FormationSlots<N-1> 
{
 public: virtual void gap(char (*)[N])=0;
 
}
;
template<> class FormationSlots<0> 
{
 
}
;
class FormationRangeQuery : public FormationSlots<18> 
{
 public: virtual Object *query(int,const Coord3D *,float,int,int)=0;
 
}
;
class FormationContainer : public FormationSlots<31> 
{
 public: virtual FormationRangeQuery *rangeQuery()=0;
 
}
;
class FormationAI : public FormationSlots<110> 
{
 public: virtual bool idleBlocked()=0;
 virtual bool specialState()=0;
 virtual void slot112()=0;
 virtual void slot113()=0;
 virtual void slot114()=0;
 virtual void slot115()=0;
 virtual void slot116()=0;
 virtual void slot117()=0;
 virtual void slot118()=0;
 virtual void slot119()=0;
 virtual void slot120()=0;
 virtual void slot121()=0;
 virtual void slot122()=0;
 virtual void slot123()=0;
 virtual void slot124()=0;
 virtual void slot125()=0;
 virtual void slot126()=0;
 virtual void slot127()=0;
 virtual void slot128()=0;
 virtual void slot129()=0;
 virtual void slot130()=0;
 virtual void slot131()=0;
 virtual void slot132()=0;
 virtual void slot133()=0;
 virtual void slot134()=0;
 virtual void slot135()=0;
 virtual void resetAttack()=0;
 
}
;
class AICommandInterface 
{
 public: void aiIdle(CommandSourceType);
 
}
;
class Object 
{
 public:
 bool testStatus(ObjectStatusTypes) const;
 int rva0028B511() const;
 const Weapon *getCurrentWeapon(WeaponSlotType *) const;
 float rva002C97E8(const Coord3D *,const Coord3D *) const;
 const Coord3D *getPosition()const
 {
  return &m_position;
  
 }
 AIUpdateInterface *getAI()const
 {
  return (AIUpdateInterface *)m_ai;
  
 }
 int getTeamValue()const
 {
  return m_274;
  
 }
 void rva0028ACEE(int,int);
 unsigned char pad0[4];
 void *m_template;
 unsigned char pad8[0x38-8];
 Coord3D m_position;
 unsigned char pad44[0x74-0x44];
 int m_id;
 unsigned char pad78[0x250-0x78];
 FormationContainer *m_container;
 unsigned char pad254[4];
 FormationAI *m_ai;
 unsigned char pad25C[0x274-0x25C];
 int m_274;
 
}
;
struct FormationNode 
{
 FormationNode *next,*prev;
 Object *object;
 
}
;
struct FormationList 
{
 FormationNode *head;
 
}
;
struct FormationRange 
{
 void *owner;
 FormationList *list;
 unsigned int size() const 
 {
  unsigned int n=0;
  for(FormationNode *p=list->head->next;p!=list->head;p=p->next) ++n;
  return n;
  
 }
 
}
;
class FormationListProvider : public FormationSlots<70> 
{
 public: virtual void fill(FormationRange *)=0;
 
}
;
struct FormationHeld 
{
 unsigned char pad0[8];
 Object *m_leader;
 unsigned char padC[0x120-0xC];
 bool active;
 
}
;
class Rva0046ACF6 
{
 public: int rva0046ACF6(int);
 
}
;
struct BfmeE8 
{
 int a,b;
 
}
;
struct BfmeE12 
{
 float x,y,z;
 
}
;
namespace _STL 
{
 template<> void deque<BfmeE8>::clear();
 
}
struct FormationAttackEntry 
{
 int state;
 Coord3D position;
 int unknown10[3];
 bool needsPosition;
 char pad[3];
 int a,b;
 _STL::deque<BfmeE12> path;
 int tail;
 
}
;
class HordeMeleeFormation 
{
 public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void startMeleeAttack(Object *);
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual bool rva00585017(int,Coord3D *);
 bool findMeleeAttackPosition(Object *,Coord3D *,Object *,const Coord3D *,bool,int *,bool);
 FormationHeld *held;
 _STL::vector<FormationAttackEntry> attacks;
 bool force;
 void *other;
 
}
;
void HordeMeleeFormation::startMeleeAttack(Object *victim)

{
 held->active=true;
 FormationRange range;
 ((FormationListProvider *)((char *)held+0x20))->fill(&range);
 for(FormationNode *node=range.list->head->next;node!=range.list->head;node=node->next) 
 {
  Object *unit=node->object;
  if(!unit) continue;
  FormationAI *ai=unit->m_ai;
  if(ai && *(int *)((char *)ai+0x1fc)==4 && *(int *)((char *)ai+0x140)) continue;
  int index=((Rva0046ACF6 *)held)->rva0046ACF6(unit->m_id);
  if(index<0 || index>=attacks.size()) continue;
  if(!unit->testStatus(FORMATION_STATUS_1C)) 
  {
   if(!ai) continue;
   if(!ai->idleBlocked()) ((AICommandInterface *)((char *)ai+0x20))->aiIdle(FORMATION_COMMAND);
   
  }
  FormationAttackEntry &entry=attacks[index];
  entry.position=unit->m_position;
  entry.needsPosition=true;
  ((_STL::deque<BfmeE8> *)&entry.path)->clear();
  unit->rva0028ACEE((int)&unit->m_position,unit->rva0028B511());
  unit->m_ai->resetAttack();
  
 }
 
}
// Native585017..585059 is66B RET8. WB1474BB0 and the constructor
// table slot13 establish index/output ABI; the original spelling is unknown.
// The following10B deque iterator body at585059 is outside this extent.
bool HordeMeleeFormation::rva00585017(int index,Coord3D *result)

{
 if(index>=0 && index<attacks.size() && !attacks[index].needsPosition) 
 {
  *result=attacks[index].position;
  return true;
  
 }
 return false;
 
}
// STLport4.5.3 reverse_iterator equality for this formation's12B path entries.
// Native00584D14..00584D3F copies both16B iterators and compares current pointers.
// Formation update005863E5 calls it at0058678D and005867B8; WB1473460
// independently shows that reverse traversal. Keep the instantiation with
// its actual FormationAttackEntry deque, sharing the observed element view.
namespace _STL 
{
 template bool operator==<deque<BfmeE12>::iterator>(
 const reverse_iterator<deque<BfmeE12>::iterator> &,
 const reverse_iterator<deque<BfmeE12>::iterator> &);
 
}
#include "GameLogicObjectLookupView.h"
typedef int Int;
typedef bool Bool;
typedef float Real;
#include <math.h>
enum PathfindLayerEnum

{
 LAYER_INVALID = 0,
 LAYER_WALL = 0x10
 
}
;
class Weapon;
class Rva002C9B80Owner

{
 public:
 Bool isWithinAttackRange(Object *source, const Coord3D *pos, Object *victim, const Coord3D *victimPos, Real extra, Bool flag);
 
}
;
class AIUpdateInterface

{
 public:
 void *getLocomotorSet() const 
 {
  return m_1dc;
  
 }
 private:
 unsigned char m_pad000[0x1DC];
 void *m_1dc;
// +0x1DC
 
}
;
class Pathfinder

{
 public:
 Int GetOverlapGoalUnits(Object *obj, const Coord3D *pos, Int *ids);
 Int IsHordeMeleeLinePassable(void *obj, void *locomotorSet, PathfindLayerEnum layer, const Coord3D *from, const Coord3D *to);
 Bool hordeLine(void *obj,void *locomotorSet,PathfindLayerEnum layer,const Coord3D *from,const Coord3D *to) 
 {
  typedef Bool(Pathfinder::*Line)(void*,void*,PathfindLayerEnum,const Coord3D*,const Coord3D*);
  return (this->*reinterpret_cast<Line>(&Pathfinder::IsHordeMeleeLinePassable))(obj,locomotorSet,layer,from,to);
  
 }
 Bool rva002EDFF9(Object *obj, Coord3D *pos);
 
}
;
class AI

{
 public:
 Pathfinder *pathfinder() const 
 {
  return m_pathfinder;
  
 }
 private:
 unsigned char m_pad00[0x10];
 Pathfinder *m_pathfinder;
// +0x10
 
}
;
extern AI *TheAI;
class TerrainLogic

{
 public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal, Bool clip);
// slot 7
 PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
 
}
;
extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;
extern Int g_Va00DBA4E4;
// LOGICFRAMES_PER_SECOND
int Rva002EDE5B(void *obj, Coord3D *pos);
int Rva002E9B31Get(void *obj);
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
__declspec(noinline) inline float Coord3D::GetLength() const

{
 double x_value=x, y_value=y, z_value=z;
 return (float)sqrt(x_value*x_value+y_value*y_value+z_value*z_value);
 
}
__declspec(noinline) inline float Coord3D::Normalize()

{
 float len=GetLength();
 float scale=1.0f/len;
 x*=scale;
 y*=scale;
 z*=scale;
 return len;
 
}
Bool HordeMeleeFormation::findMeleeAttackPosition(Object *obj, Coord3D *result, Object *victim, const Coord3D * volatile victimPos,
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
 Object *leader = held->m_leader;
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
 const volatile Int &ringLimit=rings;
 Int overlapIds[16];
 Bool overlapping = TheAI->pathfinder()->GetOverlapGoalUnits(obj, obj->getPosition(), overlapIds) > 0;
 Bool blocked = !TheAI->pathfinder()->hordeLine(obj, locomotorSet, layer, &pos, &pos);
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
      if (TheAI->pathfinder()->hordeLine(obj, locomotorSet, layer, &cand, &cand))
      
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
 _ReadWriteBarrier();
 for (Int r = 1; r <= ringLimit; r++)
 
 {
  for (Int i = -r; i <= r; i++)
  
  {
   for (Int j = -r; j <= r; j++)
   
   {
    if ((i == 0 && j == 0 && r <= 1) || i == r || j == r || i == -r || j == -r)
    
    {
     Real ox = (Real)i * 10.0f;
     Real oy = (Real)j * 10.0f;
     Coord3D delta;
     delta.x = pos.x + ox;
     delta.y = pos.y + oy;
     delta.z = 0.0f;
     subCoord(delta, victimPos);
     delta.z = 0.0f;
     Real candDist;
     if (i == 0 && j == 0)
     
     {
      candDist = 0.0f;
      delta.Normalize();
      delta.x *= 14.0f;
      delta.y *= 14.0f;
      delta.z *= 14.0f;
      ox = -delta.x;
      oy = -delta.y;
      
     }
     else
     
     {
      candDist = delta.GetLength();
      if (candDist > dist && !overlapping)
      continue;
      
     }
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
      if (TheAI->pathfinder()->GetOverlapGoalUnits(obj, &cand, ids) == 2 && weapon)
      
      {
       Object *a = TheGameLogic->findObjectByID((ObjectID)ids[0]);
       Object *b = TheGameLogic->findObjectByID((ObjectID)ids[1]);
       if (a && b && a->getTeamValue() == b->getTeamValue() && obj->getTeamValue() == a->getTeamValue())
       
       {
        if (((Rva002C9B80Owner *)weapon)->isWithinAttackRange(obj, &cand, victim, victimPos, 0.0f, true))
        
        {
         clear = true;
         candDist = dist + 1.0f;
         
        }
        
       }
       
      }
      
     }
     if (clear)
     
     {
      if (blocked)
      ok = true;
      else
      ok = TheAI->pathfinder()->hordeLine(obj, locomotorSet, layer, &lastGood, &cand);
      
     }
     if (ok && candDist < bestDist)
     
     {
      best = cand;
      bestDist = candDist;
      bestOffset = (Real)sqrt(oy * oy + ox * ox);
      bestGain = dist - candDist;
      found = true;
      _ReadWriteBarrier();
      
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
