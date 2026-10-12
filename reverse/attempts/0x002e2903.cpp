// ??0Rva002E2903Player@@QAE@PAURva002BA8F1Input@@PAX@Z
// partial score=1.0 date=2026-10-12
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii
// stlport
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include <vector>
#include "ascii_string.h"
#include <set>
#include <string.h>
void Rva00030830FreeAllocation(void*);
struct BfmeE16{float x,y,z,w;};
namespace _STL{
template<>void allocator<BfmeE16>::deallocate(pointer p,size_type)const{Rva00030830FreeAllocation(p);}
template<>__declspec(nothrow) __declspec(noinline) _Vector_base<BfmeE16,allocator<BfmeE16> >::_Vector_base(const allocator<BfmeE16>&a):_M_start(0),_M_finish(0),_M_end_of_storage(a,0){}
}
struct Header:public _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >{
 __forceinline Header():_STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >(_STL::allocator<BfmeE16>()){}
};
class Rva00330757Member:public Header{public:__declspec(noinline) Rva00330757Member();__forceinline ~Rva00330757Member(){}int flag;};
inline Rva00330757Member::Rva00330757Member(){flag|=-1;}

struct Rva002BA8F1Input { char unknown00[36]; bool flag; };

class Rva002E0EF7 {public:__declspec(nothrow) Rva002E0EF7();};
class Rva002E0F1E {public:~Rva002E0F1E();};
class Rva002E0A0A {public:
 __forceinline Rva002E0A0A(){((Rva002E0EF7*)this)->Rva002E0EF7::Rva002E0EF7();}
 Rva002E0A0A(const Rva002E0A0A&);
 __forceinline ~Rva002E0A0A(){((Rva002E0F1E*)this)->Rva002E0F1E::~Rva002E0F1E();}
 char bytes[40];
};
class LivingWorldAI { public: LivingWorldAI(); ~LivingWorldAI(); char bytes[308]; };
class Rva001EAE6FHelper { public: __declspec(nothrow) Rva001EAE6FHelper*clear80(); };
struct ClearStorage { char bytes[128]; ClearStorage(){ ((Rva001EAE6FHelper*)this)->clear80(); } };
class LivingWorldArmy;
struct PlayerPointerArray:public _STL::_Vector_base<LivingWorldArmy*,_STL::allocator<LivingWorldArmy*> > { __forceinline PlayerPointerArray():_STL::_Vector_base<LivingWorldArmy*,_STL::allocator<LivingWorldArmy*> >(_STL::allocator<LivingWorldArmy*>()){} };
class RefSlot {public:RefSlot(int x):value(x){}~RefSlot();int value;};
struct Color { float x,y,z; Color(float v):x(v),y(v),z(v){} };
class Rva000D1930 { public:__declspec(nothrow) Rva000D1930(); ~Rva000D1930();char bytes[28]; };

class LivingWorldPlayer;
class Rva004EED02 {public:~Rva004EED02();};
class LivingWorldScoreKeeper {public:
 LivingWorldScoreKeeper(int,LivingWorldPlayer*);
 __forceinline ~LivingWorldScoreKeeper(){((Rva004EED02*)this)->Rva004EED02::~Rva004EED02();}
 char bytes[252];
};
class Rva002B317CBumpCounter {public:int bump();};
extern Rva002B317CBumpCounter *TheLivingWorldLogic;
class Rva002E2903Player : public Snapshot, public Rva00330757Member {
public:
 Rva002E2903Player(); Rva002E2903Player(Rva002BA8F1Input*,void*);
 virtual ~Rva002E2903Player();
 virtual void loadPostProcess(); virtual const char*GetSnapshotName()const; virtual void xfer(Xfer*);
 int id;
 Rva002E0A0A input;
 void *p40; int kind; AsciiString zero48;
 LivingWorldAI ai;
 int colorIndex;Color color1,color2,color3;
 _STL::vector<int> records;AsciiString zero1B4;
 PlayerPointerArray armies;int zero1C4;float value1C8;
 _STL::vector<int> list1CC;
 ClearStorage storage;
 Rva000D1930 member258,member274;
 int zero290,zero294,zero298;
 _STL::set<int> set29C,set2A8;
 char zero2B4[16];int zero2C4;
 LivingWorldScoreKeeper member2C8;
 bool flag3C4,flag3C5;
};
Rva002E2903Player::Rva002E2903Player()
 : id(-1),p40(0),kind(0),colorIndex(-1),color1(1.0f),color2(1.0f),color3(1.0f),zero1C4(0),value1C8(1.0f),zero290(0),zero294(0),zero298(0),zero2C4(0),member2C8(id,(LivingWorldPlayer*)(Rva00330757Member*)this),flag3C4(false),flag3C5(false)
 {memset(&storage,0,128);memset(zero2B4,0,16);}
Rva002E2903Player::Rva002E2903Player(Rva002BA8F1Input*src,void*context)
 : id(TheLivingWorldLogic->bump()),input(*(const Rva002E0A0A*)src),p40(context),kind(src->flag?2:0),colorIndex(-1),color1(1.0f),color2(1.0f),color3(1.0f),zero1C4(0),value1C8(1.0f),zero290(0),zero294(0),zero298(0),zero2C4(0),member2C8(id,(LivingWorldPlayer*)(Rva00330757Member*)this),flag3C4(false),flag3C5(false)
 {memset(&storage,0,128);memset(zero2B4,0,16);}
