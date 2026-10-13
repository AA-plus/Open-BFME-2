// ?rva0009B28C@Rva0009B28C@@QAEXPBUCoord2D@@@Z
// partial score=0.9755 date=2026-10-13
// ?rva0009B28C@Rva0009B28C@@QAEXPBUCoord2D@@@Z
// partial score=0.9755330933 date=2026-10-13
// ?rva0009B28C@Rva0009B28C@@QAEXPBUCoord2D@@@Z
// partial score=0.9755330933 date=2026-10-12
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
#include <math.h>
struct Coord2D {float x,y;};
class WWMath {public: static float __fastcall Inv_Sqrt(float);};
struct Vector3 {
 float X,Y,Z;
 Vector3() {}
 Vector3(float x,float y,float z):X(x),Y(y),Z(z) {}
 Vector3(const Vector3 &v):X(v.X),Y(v.Y),Z(v.Z) {}
 __forceinline Vector3 operator-() const {return Vector3(-X,-Y,-Z);}
 __forceinline Vector3 &operator=(const Vector3 &v) {X=v.X;Y=v.Y;Z=v.Z;return *this;}
 void set(float x,float y,float z) {X=x;Y=y;Z=z;}
 void set(const Vector3 &v) {X=v.X;Y=v.Y;Z=v.Z;}
 __forceinline float Length2() const {return X*X+Y*Y+Z*Z;}
 __forceinline void Normalize() {float l=Length2();if(l!=0.f) {float r=WWMath::Inv_Sqrt(l);X*=r;Y*=r;Z*=r;}}
 void scale(float f) {X*=f;Y*=f;Z*=f;}
};
struct Matrix3D {
 float Row[3][4];
 Matrix3D(bool) {
  Row[0][0]=1.f;Row[0][1]=0.f;Row[0][2]=0.f;Row[0][3]=0.f;
  Row[1][0]=0.f;Row[1][1]=1.f;Row[1][2]=0.f;Row[1][3]=0.f;
  Row[2][0]=0.f;Row[2][1]=0.f;Row[2][2]=1.f;Row[2][3]=0.f;
 }
};
#define V4(p) virtual void p##0();virtual void p##1();virtual void p##2();virtual void p##3();
#define V16(p) V4(p##0) V4(p##1) V4(p##2) V4(p##3)
class Light9B28C {public:
 V16(s0) V4(s1) virtual void s20();
 virtual void Set_Transform(const Matrix3D &);
 char pad04[0xd4-4]; Vector3 ambient,diffuse,specular;
};
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
struct Color9B28C {float X,Y,Z;};
struct Light9B28CManagerView {char pad[0x60];Color9B28C color;};
class W3DShadowManager;
extern W3DShadowManager *TheW3DShadowManager;
class W3DGameClientShadowShim {public:void setLightPosition(int,float,float,float);};
class Rva0009B28C {public:
 void rva0009B28C(const Coord2D *);
 char pad00[0xc8];Light9B28C *light;char padCC[0x1a0-0xcc];Vector3 position;
};
void Rva0009B28C::rva0009B28C(const Coord2D *angles) {
 if(light) {
  Color9B28C color=((Light9B28CManagerView *)TheLivingWorldManager)->color;
  Vector3 direction;
  direction.X=sin((float)(angles->x*.017453292f+1.5707964f))*(float)cos(angles->y*.017453292f);
  direction.Y=sin((float)(angles->x*.017453292f+1.5707964f))*(float)sin(angles->y*.017453292f);
  direction.Z=cos((float)(angles->x*.017453292f+1.5707964f));
  position = -direction;
  position.Normalize();position.scale(10000.f);
  light->ambient.set(0.f,0.f,0.f);light->specular.set(0.f,0.f,0.f);light->diffuse.set(color.X,color.Y,color.Z);
  Matrix3D tm(true);
  tm.Row[0][0]=1.f;tm.Row[0][1]=0.f;tm.Row[0][2]=direction.X;tm.Row[0][3]=0.f;
  tm.Row[1][0]=0.f;tm.Row[1][1]=1.f;tm.Row[1][2]=direction.Y;tm.Row[1][3]=0.f;
  tm.Row[2][0]=0.f;tm.Row[2][1]=0.f;tm.Row[2][2]=direction.Z;tm.Row[2][3]=0.f;
  light->Set_Transform(tm);
 }
 ((W3DGameClientShadowShim *)TheW3DShadowManager)->setLightPosition(0,position.X,position.Y,position.Z);
}
