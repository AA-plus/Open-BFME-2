// ?rva0029FFFF@Rva0029C138@@QAEHP6AHPAVDrawable@@PAX@Z1@Z
// partial score=0.9886 date=2026-10-13
// ?rva0029FFFF@Rva0029C138@@QAEHP6AHPAVDrawable@@PAX@Z1@Z
// partial score=0.96 date=2026-10-13
// ?rva0029FFFF@Rva0029C138@@QAEHP6AHPAVDrawable@@PAX@Z1@Z
// partial score=0.9 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /ICode/Libraries/Include/Lib
// stlport
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <list>
#include "Coord3D.h"
struct ICoord2D { int x,y; };
struct IRegion2D { ICoord2D lo,hi; __forceinline bool isPoint() const { return hi.y-lo.y==0 && hi.x-lo.x==0; } };
struct Rva0087DC00Vec { int x,y,z; };
class Rva0087DC00 { public: void get(Rva0087DC00Vec*); };
class Rva00270FEE { public: char* rva00270FEE(); };
class Rva00276470Drawable { public: const Coord3D* rva00276470() const; };
template<int N> class BitFlags { public: bool test(const void*) const; };
class Drawable {
public:
 char pad00[4]; char* thingTemplate;
 char pad08[0x104-8]; Drawable* next;
};
class SelectionData { public: char pad[0x24]; BitFlags<69> excluded; };
class GameClientView {
public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16)
#undef V
 virtual Drawable* firstDrawable();
};
class GameClient; extern GameClient* TheGameClient;
class TacticalView {
public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8)
 virtual Drawable* pick(const ICoord2D*,bool,unsigned);
 V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
 V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
 V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
 V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
 V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
 V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
 V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
 V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87)
#undef V
 virtual void project(const Coord3D*,ICoord2D*);
};
class View; extern View* TheTacticalView;
unsigned Rva0030F099(bool);
class Rva0029C138 {
public:
 bool rva0029C163(const ICoord2D&);
 int rva0029FFFF(int (*callback)(Drawable*,void*),void* data);
private:
 char prefix[0x8b8]; bool forceAttack;
 char pad8b9[0x910-0x8b9]; _STL::list<ICoord2D> points;
 IRegion2D bounds;
};
int Rva0029C138::rva0029FFFF(int (*callback)(Drawable*,void*),void* data) {
 int count=0;
 _ReadWriteBarrier();
 bool point=false;
 if(points.size()<3 || bounds.isPoint()) point=true;
 Drawable* only=0;
 if(point) {
  bool attack=forceAttack;
  only=((TacticalView*)TheTacticalView)->pick(&bounds.lo,true,Rva0030F099(attack));
  if(!only) return 0;
 }
 Drawable* draw=((GameClientView*)TheGameClient)->firstDrawable();
 for(;(draw) && (draw->thingTemplate != 0 || draw->thingTemplate == 0);draw=draw->next) {
  if(only) draw=only;
  else {
   if(((SelectionData*)data)->excluded.test(draw->thingTemplate+0x108)) continue;
   Coord3D pos;
   ((Rva0087DC00*)((Rva00270FEE*)draw)->rva00270FEE())->get((Rva0087DC00Vec*)&pos);
   const Coord3D* base=((Rva00276470Drawable*)draw)->rva00276470();
   pos.x+=base->x; pos.y+=base->y; pos.z+=base->z;
   ICoord2D screen;
   ((TacticalView*)TheTacticalView)->project(&pos,&screen);
   if(!rva0029C163(screen)) continue;
  }
  int result=callback(draw,data);
  if(result==0) ++count;
  else if(result==1) count=1;
  if(only) break;
 }
 return count;
}


