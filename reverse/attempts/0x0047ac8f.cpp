// ?rva0047AC8F@AODHordeContain@@QAEXXZ
// partial score=0.8684 date=2026-10-13
// ?rva0047AC8F@AODHordeContain@@UAEPAUCoord3D@@PAU2@PAVObject@@H@Z
// partial score=0.84325016 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include
// Native 47AC8F..47B2AA: AOD interface at +11C, output-pointer/RET12 ABI.
// WB1161040 names getUnitsIntendedPosition; original hidden-result shape is
// represented explicitly to use canonical Coord3D without a private class.
// Banked semantic reconstruction retained; physical fields are target accesses.
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
#include <math.h>
template<class T> __forceinline volatile T &r1_vwrite(T &value) { return *(volatile T *)&value; }
float Cos(float);
float Sin(float);
struct AODSway : Coord2D 

{
 AODSway() 
 
 {
  
 }
 AODSway(const Coord2D &v) 
 
 {
  x=v.x;
  y=v.y;
  
 }
 AODSway(const AODSway &v) 
 
 {
  x=v.x;
  y=v.y;
  
 }
 ~AODSway() 
 
 {
  
 }
 
}
;
class Rva00468E98Point 

{
 public: float x,y;
 Rva00468E98Point(const Rva00468E98Point &,float);
 Rva00468E98Point(const Rva00468E98Point &p) 
 
 {
  x=p.x;
  y=p.y;
  
 }
 
}
;
class Rva00468E98 

{
 public: Rva00468E98Point rotate(Rva00468E98Point);
 
}
;
enum KindOfType

{
 KINDOF_INVALID = -1
 
}
;
enum PathfindLayerEnum

{
 LAYER_INVALID = 0
 
}
;
class Rva0008BB38FloatField

{
 public:
 float get() const;
 
}
;
class Rva001E46E1

{
 public:
 float rva001E46E1(class Object *obj);
 
}
;
class Locomotor;
class AIUpdateInterface

{
 public:
 char m_pad00[0x1F0];
 Locomotor *m_curLocomotor;
// +0x1F0
 
}
;
class Thing

{
 public:
 const Coord3D *getUnitDirectionVector2D() const;
 
}
;
class GeometryInfo 

{
 public: float getMaxHeightAbovePosition() const;
 
}
;
enum ObjectID 

{
 INVALID_ID=0 
 
}
;
class Object : public Thing

{
 public:
 bool isKindOf(KindOfType t) const;
 int rva0028B511() const;
 char m_pad00[0x38];
 Coord3D m_position;
 char m_pad44[0x74-0x44];
 int m_id;
// +0x74
 char m_pad78[0xA8-0x78];
 GeometryInfo m_geometry;
 char m_padA9[0x258-0xA9];
 AIUpdateInterface *m_ai;
// +0x258
 
}
;
template <int N> class AODTerrainSlots : public AODTerrainSlots<N - 1>

{
 public:
 virtual void gap(char (*)[N]);
 
}
;
template <> class AODTerrainSlots<0>

{
 
}
;
class TerrainLogic : public AODTerrainSlots<7>

{
 public:
 virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer, Coord3D *normal, bool clip);
// slot 7
 virtual void s08();
 virtual void s09();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual bool isUnderwater(float x, float y, float *waterZ, float *terrainZ, int unused);
// slot 19
 
}
;
extern TerrainLogic *TheTerrainLogic;
class GameLogic

{
 public:
 Object *findObjectByID(ObjectID id);
 unsigned int getFrame() const 
 
 {
  return m_frame;
  
 }
 private:
 char m_pad00[0x40];
 unsigned int m_frame;
 
}
;
extern GameLogic *TheGameLogic;
struct AODHordeContainModuleData

{
 char m_pad00[0x274];
 float m_274;
 float m_278;
 float m_27C;
 float m_280;
 float m_284;
 float m_288;
 float m_28C;
 float m_290;
 float m_294;
 float m_298;
 float m_29C;
 float m_2A0;
 float m_2A4;
 float m_2A8;
 unsigned int m_2AC;
 float m_2B0;
 float m_2B4;
 float m_2B8;
 
}
;
class Rva0046ACF6

{
 public:
 int rva0046ACF6(int id);
 
}
;
struct AODOffsetRecord

{
 int m_00;
 Coord2D m_offset;
// +0x04
 char m_pad0C[0x1C - 0x0C];
 
}
;
struct AODWave

{
 float m_00, m_04, m_08, m_0C, m_10, m_14;
 
}
;
struct AODFormationSlot

{
 float m_key;
// +0x00
 float m_angle;
// +0x04
 Coord3D m_pos;
// +0x08
 int m_14;
 
}
;
class HordeContainPrimary

{
 public:
 virtual void p00();
 const AODHordeContainModuleData *m_moduleData;
// +0x04
 Object *m_object;
// +0x08
 char m_pad0C[0x11C - 0x0C];
 
}
;
class HordeContainIface

{
 public:
 virtual void i00();
 virtual void i01();
 virtual void i02();
 virtual void i03();
 virtual void i04();
 virtual void i05();
 virtual void i06();
 virtual Coord3D *rva0047AC8F(Coord3D *out,Object *obj, int word) = 0;
 bool m_04;
// +0x04
 char m_pad05[0x6C - 0x05];
 AODOffsetRecord *m_records;
// +0x6C
 char m_pad70[0x7C - 0x70];
 bool m_7C;
// +0x7C
 char m_pad7D[0x184 - 0x7D];
 int m_184;
// +0x184
 char m_pad188[0x1F0 - 0x188];
 AODWave *m_wavesBegin;
// +0x1F0
 AODWave *m_wavesEnd;
// +0x1F4
 char m_pad1F8[0x1FC - 0x1F8];
 ObjectID m_trackedLargeUnit;
// +0x1FC
 unsigned int m_200;
// +0x200
 Coord3D m_trackedPosition;
// +0x204
 float m_largeUnitHeightFactor;
// +0x210
 float m_largeUnitHeight;
// +0x214
 float m_218;
// +0x218
 char m_pad21C[0x5E0 - 0x21C];
 AODFormationSlot m_slots[20];
// +0x5E0
 int m_slotCount;
// +0x7C0
 
}
;
// HordeContain's own slot 7, called non-virtually with the interface this.
class Rva00474B51

{
 public:
 Coord3D *rva00474B51(Coord3D *out,Object *obj, int word);
 
}
;
class HordeContain : public HordeContainPrimary, public HordeContainIface

{
 public:
 virtual Coord3D *rva0047AC8F(Coord3D *out,Object *obj, int word);
 Coord2D *rva0046A5B1(Coord2D *out, int index);
 
}
;
class AODHordeContain : public HordeContain

{
 public:
 virtual Coord3D *rva0047AC8F(Coord3D *out,Object *obj, int word);
 void refreshTrackedLargeUnit();
 
}
;
static __forceinline float AODHeightFalloff(float x)

{
 float a = (float)sqrt(x) * x;
 float b = x * x;
 b *= 1.0f - x;
 return a + b;
 
}
Coord3D *AODHordeContain::rva0047AC8F(Coord3D *out,Object *obj,int word)

{
 if (m_184)
 
 {
  ((Rva00474B51 *)((char *)this+0x11C))->rva00474B51(out,obj,word);
  return out;
  
 }
 int index = reinterpret_cast<Rva0046ACF6 *>(this)->rva0046ACF6(obj->m_id);
 AODSway offset(m_records[index].m_offset);
 int i;
 for (i = m_slotCount - 1; i > 0; --i)
 
 {
  if (m_slots[i].m_key == offset.x)
  break;
  
 }
 if (i < 0)
 i = 0;
 Coord3D pos;
 pos = m_slots[i].m_pos;
 float angle = m_slots[i].m_angle;
 pos.x += -offset.y * (float)sin(angle);
 pos.y += (float)cos(angle) * offset.y;
 const AODHordeContainModuleData *md = m_moduleData;
 if (!m_7C || (unsigned int)index >= (unsigned int)(m_wavesEnd - m_wavesBegin))
 
 {
  out->x=pos.x;
  out->y=pos.y;
  out->z=pos.z;
  return out;
  
 }
 Object *me = m_object;
 float speedRatio = 0.0f;
 if (me->m_ai)
 
 {
  Locomotor *loco = me->m_ai->m_curLocomotor;
  speedRatio = reinterpret_cast<Rva0008BB38FloatField *>(loco)->get() / reinterpret_cast<Rva001E46E1 *>(loco)->rva001E46E1(me);
  
 }
 float t = md->m_284;
 if (t < 0.0f)
 t = 0.0f;
 if (t > 1.0f)
 t = 1.0f;
 if (t > 0.01f)
 m_04 = true;
 float speedFactor = (1.0f - t) * speedRatio + t;
 AODWave *wave = &m_wavesBegin[index];
 AODSway sway;
 sway.y = (float)sin(wave->m_00 + wave->m_08 * ((float)TheGameLogic->getFrame() * md->m_274)) * wave->m_04;
 sway.y = speedFactor * md->m_27C * sway.y;
 sway.x = 0.0f;
 Rva00468E98Point dir=((Rva00468E98 *)this)->rotate(reinterpret_cast<const Rva00468E98Point &>(sway));
 float len = sway.length();
 angle = sway.toAngle() + angle;
 dir.x = Cos(angle);
 dir.y = Sin(angle);
 dir.x *= len;
 dir.y *= len;
 t = md->m_298;
 if (t < 0.0f)
 t = 0.0f;
 if (t > 1.0f)
 t = 1.0f;
 if (t > 0.01f)
 m_04 = true;
 speedFactor = (1.0f - t) * speedRatio + t;
 volatile float bob = (float)sin(wave->m_0C + wave->m_14 * ((float)TheGameLogic->getFrame() * md->m_288)) * wave->m_10 + 0.95f;
 bob = speedFactor * md->m_290 * bob;
 if (obj->isKindOf((KindOfType)0xD7))
 
 {
  Coord2D temporary;
  Coord2D spread = *rva0046A5B1(&temporary, index);
  spread.normalize();
  float s = md->m_2B4 * m_218;
  s = (float)(index % 5) * md->m_2B8 * m_218 * 0.25f + s;
  spread.x *= s;
  spread.y *= s;
  dir.x += spread.x;
  dir.y += spread.y;
  
 }
 pos.x += dir.x;
 pos.y += dir.y;
 float waterZ;
 if (TheTerrainLogic->isUnderwater(pos.x, pos.y, &waterZ, 0, 0))
 pos.z = waterZ;
 else
 pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, (PathfindLayerEnum)me->rva0028B511(), 0, true);
 pos.z += bob;
 if (m_trackedLargeUnit)
 
 {
  float maxHeight = md->m_2A0 * m_largeUnitHeight;
  if (maxHeight > md->m_2A8)
  maxHeight = md->m_2A8;
  if (maxHeight < md->m_2A4)
  maxHeight = md->m_2A4;
  unsigned int elapsed = TheGameLogic->getFrame() - m_200;
  if (elapsed >= md->m_2AC)
  
  {
   m_trackedLargeUnit = INVALID_ID;
   
   {
    out->x=pos.x;
    out->y=pos.y;
    out->z=pos.z;
    return out;
    
   }
   
  }
  float falloff = 1.0f;
  int half = md->m_2AC / 2;
  if (elapsed > (unsigned int)half)
  falloff = 1.0f - (float)(elapsed - half) / half;
  Coord3D delta;
  const Coord3D *origin = &m_trackedPosition;
  r1_vwrite(delta.x) = pos.x - origin->x;
  delta.y = pos.y - origin->y;
  const Coord3D *facing = me->getUnitDirectionVector2D();
  Coord3D forward;
  forward.x=facing->x;
  forward.y=facing->y;
  Coord3D side;
  r1_vwrite(side.x) = -forward.y;
  side.y = forward.x;
  float along = (float)fabs(delta.x * forward.x + delta.y * forward.y);
  float across = (float)fabs(delta.x * side.x + delta.y * side.y);
  across -= m_largeUnitHeightFactor;
  if (across < 0.0f)
  across = 0.0f;
  float dist = along + across;
  float radius = md->m_2B0 * maxHeight;
  if (dist < radius)
  
  {
   float lift = (1.0f - AODHeightFalloff(dist / radius)) * maxHeight;
   lift *= falloff;
   pos.z += lift;
   
  }
  
 }
 if (obj->isKindOf((KindOfType)0xD7))
 
 {
  float rank = md->m_2B4 * md->m_29C * m_218;
  rank = (float)((index + 2) % 5) * md->m_2B8 * md->m_29C * m_218 * 0.25f + rank;
  pos.z += rank;
  
 }
 
 {
  out->x=pos.x;
  out->y=pos.y;
  out->z=pos.z;
  return out;
  
 }
 
}
void AODHordeContain::refreshTrackedLargeUnit()

{
 Object *unit = TheGameLogic->findObjectByID(m_trackedLargeUnit);
 if (unit == 0)
 
 {
  m_trackedLargeUnit = INVALID_ID;
  return;
  
 }
 m_trackedPosition = unit->m_position;
 m_largeUnitHeightFactor = 17.0f;
 m_largeUnitHeight = unit->m_geometry.getMaxHeightAbovePosition();
 
}
