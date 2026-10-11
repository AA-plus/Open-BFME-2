// cl: /O1 /Oy- /arch:SSE /G7 /MD /DNDEBUG /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Include
// Thing::convertBonePosToWorldPos; target 0x0030A528/746.
// Reference semantics: BF1 f98983a7d ZH GeneralsMD Common/Thing/Thing.cpp341.
// Target native and WB0xCEE0D0 independently show the optional matrix product
// and optional point transformation; WB's inline assertion is Matrix3D.h1562.
// Native this+8 is the transform (the reference's layout differs).
// Keep the reference member-method form: static matrix helpers perturb SSE
// allocation. The target-proven matrix association and ordinary Transform_Vector
// alias handling together reproduce all746 bytes with O1/SSE/G7/Oy-.
// Coord3D's canonical trivial copy restores the native12B temporary and MOVSDs.
// The Matrix3D view contains exactly three four-float rows; no own data or vptr.
#include "Lib/Coord3D.h"
#include "vector3.h"
#include "vector4.h"
// LINK: file-static helpers and direct Row fields replace Vector3's MMM ctor and
// operator=, Vector4/Matrix3D operator[] and Matrix3D::mul: identical inlined
// bytes, but this TU no longer emits their loser COMDAT copies. No flags touched.
static __forceinline void bfmeCopyV3(Vector3 &d,const Vector3 &s) {d.X=s.X;d.Y=s.Y;d.Z=s.Z;}
static __forceinline void bfmeSetV3(Vector3 &v,float x,float y,float z) {v.X=x;v.Y=y;v.Z=z;}
static __forceinline float boneSubmul(const Vector4 &row,float x,float y,float z) {return row.Z*z+row.Y*y+row.X*x;}
class Matrix3D {public:
 Vector4 Row[3];
 __forceinline void bfme_mul_bp(const Matrix3D &a,const Matrix3D &b) {
  float x,y,z;
  x=b.Row[0].X;y=b.Row[1].X;z=b.Row[2].X;
  Row[0].X=boneSubmul(a.Row[0],x,y,z);
  Row[1].X=boneSubmul(a.Row[1],x,y,z);
  Row[2].X=boneSubmul(a.Row[2],x,y,z);
  x=b.Row[0].Y;y=b.Row[1].Y;z=b.Row[2].Y;
  Row[0].Y=boneSubmul(a.Row[0],x,y,z);
  Row[1].Y=boneSubmul(a.Row[1],x,y,z);
  Row[2].Y=boneSubmul(a.Row[2],x,y,z);
  x=b.Row[0].Z;y=b.Row[1].Z;z=b.Row[2].Z;
  Row[0].Z=boneSubmul(a.Row[0],x,y,z);
  Row[1].Z=boneSubmul(a.Row[1],x,y,z);
  Row[2].Z=boneSubmul(a.Row[2],x,y,z);
  x=b.Row[0].W;y=b.Row[1].W;z=b.Row[2].W;
  Row[0].W=boneSubmul(a.Row[0],x,y,z)+a.Row[0].W;
  Row[1].W=boneSubmul(a.Row[1],x,y,z)+a.Row[1].W;
  Row[2].W=boneSubmul(a.Row[2],x,y,z)+a.Row[2].W;
  }
 static __forceinline void Transform_Vector(const Matrix3D &a,const Vector3 &in,Vector3 *out) {
  Vector3 tmp;
  Vector3 *v;
  if(out==&in) {bfmeCopyV3(tmp,in);v=&tmp;} else v=(Vector3 *)&in;
  out->X=a.Row[0].X*v->X+a.Row[0].Y*v->Y+a.Row[0].Z*v->Z+a.Row[0].W;
  out->Y=a.Row[1].X*v->X+a.Row[1].Y*v->Y+a.Row[1].Z*v->Z+a.Row[1].W;
  out->Z=a.Row[2].X*v->X+a.Row[2].Y*v->Y+a.Row[2].Z*v->Z+a.Row[2].W;
 }
};
class Thing {public:
 void convertBonePosToWorldPos(const Coord3D *,const Matrix3D *,Coord3D *,Matrix3D *) const;
 char prefix[8];Matrix3D transform;
};
void Thing::convertBonePosToWorldPos(const Coord3D *bonePos,const Matrix3D *boneTransform,Coord3D *worldPos,Matrix3D *worldTransform) const {
 if(worldTransform) worldTransform->bfme_mul_bp(transform,*boneTransform);
 if(worldPos) {
  Vector3 vector;bfmeSetV3(vector,bonePos->x,bonePos->y,bonePos->z);
  Matrix3D::Transform_Vector(transform,vector,&vector);
  *worldPos=*reinterpret_cast<const Coord3D *>(&vector);
 }
}
