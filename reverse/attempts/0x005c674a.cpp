// ?rva005C674A@Rva005C674A@@QAEXXZ
// partial score=0.820314917892695 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /ICode/Libraries/Include/Lib
// stlport
#include <map>
#include <math.h>
#include "Coord2D.h"
struct RadialIntPoint {int x,y;};
class Rva005C6599 {public:void rva005C6599(float,float);};
class Display;
extern Display *TheDisplay;
class RadialDisplayView {public:
virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();
virtual void slot04();virtual void slot05();virtual void slot06();virtual void slot07();
virtual void slot08();virtual void slot09();virtual void slot10();virtual void slot11();
virtual void slot12();virtual void slot13();virtual void slot14();virtual void slot15();
virtual const Coord2D*getScale();
};

// WB MathCoord2D::Rotate and retail both include sin/cos calls followed
// by FSINCOS. VC7 has no C++ intrinsic for the latter; this bounded x87
// helper models that math codegen blocker, rather than lifting the body.
static __forceinline void rotateRadialDirection(Coord2D &v,float angle) {
 float sine=(float)sin(angle),cosine=(float)cos(angle);
 __asm {
 fld angle
 fsincos
 fstp cosine
 fstp sine
 }
 float x=v.x*cosine-v.y*sine;
 v.y=v.x*sine+v.y*cosine;v.x=x;
}
class Rva005C674A {public:
 virtual void slot0();virtual void slot1();
 virtual void position(int,const RadialIntPoint&,const RadialIntPoint&);
 virtual void enable(int,bool);virtual void slot4();virtual void update();
 bool active;char pad5[3];int count;RadialIntPoint center,size;
 unsigned radius;unsigned unknown20;unsigned elapsed;
 float scale,step;
 _STL::map<int,int> buttons;
 void rva005C674A();
};
void Rva005C674A::rva005C674A(){
 if(count<=0)return;
 update();if(!active)return;
 Coord2D dir;dir.x=0.0f;dir.y=(float)(count<=1?0:-1);
 if(count>1){
  float fraction;
  if((*reinterpret_cast<float*>(0x00E065C4))!=0.0f) fraction=((*reinterpret_cast<float*>(0x00E065C4))<(float)elapsed?(*reinterpret_cast<float*>(0x00E065C4)):(float)elapsed)/(*reinterpret_cast<float*>(0x00E065C4));
  else fraction=1.0f;
  rotateRadialDirection(dir,1.0f-fraction);
 }
 for(int i=0;i<count;++i){
  RadialIntPoint extent;
  extent.x=(int)(((float)size.x-1.0f)*(scale>1.0f?1.0f:scale)+1.0f);
  extent.y=(int)(((float)size.y-1.0f)*(scale>1.0f?1.0f:scale)+1.0f);
  float distance=((float)radius-0.1f)*scale+0.1f;
  int x=(int)((float)center.x+dir.x*distance);
  int y=(int)((float)center.y+dir.y*distance);
  _STL::map<int,int>::iterator b=buttons.find(i);
  if(b!=buttons.end()) {
   const Coord2D *factor=((RadialDisplayView*)TheDisplay)->getScale();
   ((Rva005C6599*)b->second)->rva005C6599((float)x*factor->x,(float)y*factor->y);
  }
  RadialIntPoint location;location.x=x-extent.x/2;location.y=y-extent.y/2;
  position(i,location,extent);
  rotateRadialDirection(dir,step);
  enable(i,(float)elapsed>=0.0f);
 }
 if((float)elapsed>(*reinterpret_cast<float*>(0x00E065C4)))active=false;
}
