// cl: /I. /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
#include "reference/shims/wwmath/Vector2.h"
struct GateOffset {
 float X,Y,Z;
 GateOffset(float a,float b,float z):X(a),Y(b),Z(z){}
 __forceinline void rotate(float s,float c) {
  float tx=X,ty=Y;
  X=c*tx-s*ty;
  Y=s*tx+c*ty;
 }
};
// Native callback4B09E7 is embedded in loadTrigger4B0AAA at4B0BBC;
// complete entry through4B0A24 is61B. It classifies the entering/leaving
// object relative to owner+8 and adjusts counters28/2C; names unresolved.
enum Relationship { RELATION_0,RELATION_1,RELATION_2 };
class Object {public:Relationship getRelationship(const Object *) const;char pad[0x38];float px,py,pz,angle;};
class AIGateUpdate {public:
 static void rva004B09E7(Object *,AIGateUpdate *,bool);
 Vector2 rva004B0A24(float,float);
 char pad[8];Object *object;char pad0C[0x1C];int count28,count2C;
};
void AIGateUpdate::rva004B09E7(Object *o,AIGateUpdate *gate,bool entered) {
 Relationship r=o->getRelationship(gate->object);
 if(entered) {
  switch(r) {case RELATION_0:++gate->count2C;break;case RELATION_2:++gate->count28;break;}
 } else {
  switch(r) {case RELATION_0:--gate->count2C;break;case RELATION_2:--gate->count28;break;}
 }
}

// Native4B0A24..4B0AAA RET12, called four times by loadTrigger.
// Rotate the supplied XY by owner Object angle44 and translate by position38/3C.
// Helper name unknown. Retail proves an eight-byte XY result; Vector2 is the
// donor-compatible representation, not an independently recovered target type.
// WB122F5A0 inlines Vector3::Rotate_Z from vector3.h. GateOffset preserves that
// donor pattern at BFME1 revision9e3be919; local type spelling is neutral.
Vector2 AIGateUpdate::rva004B0A24(float x,float y) {
 GateOffset v(x,y,0);
 float a=object->angle;
 float s=(float)sin(a),c=(float)cos(a);
 const float &ss=s,&cc=c;
 v.rotate(ss,cc);
 return Vector2(object->px+v.X,object->py+v.Y);
}
