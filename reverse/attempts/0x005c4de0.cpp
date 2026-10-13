// ??0Rva005C4B56@@QAE@ABUHelper005C4D4B@@_NPBH@Z
// partial score=0.83 date=2026-10-13
// ??0Rva005C4B56@@QAE@ABUHelper005C4D4B@@_NPBH@Z
// partial score=0.828675577156744 date=2026-10-13
// ??0Rva005C4B56@@QAE@ABUHelper005C4D4B@@HH@Z
// partial score=0.828675577156744 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath
// stlport
// Partial bank only, 408B versus target415B; patched-byte alignment score0.8287.
// Native5C4DE0..5C4F7F RET12 and WB1566710 establish the complete constructor.
// The served whole182B derived unit Rva005C4280.cpp was read without editing.
// Target415B calls owned311B3FC58C, scale339B3FC291, rotation556B3FC82C,
// render395B3FCEA3, pickbox54B3FC74A, predicate48B5C4B26 and native string nodes.
// Both scale/rotation providers landed since the old32149 refusal.
// C747B8 belongs to Rva005C4B1B, C37C30 to Rva003FCE38 with legacy
// Rva003FD14DBase twin; reconcile these real owner names before any admission.
// old constructor name retained pending class reconciliation.
// HH is the existing ABI view: target arg1 reads a byte, arg2 is a colour pointer.
// The scalar wrapper and three-float array are codegen views, not target type names.
// Node inheritance is a layout view of the existing16B concat operand, not source proof.
// BF1 a10e4cbab8 refreshed reference lanes have no compatible clean donor for this body.
// EH base cleanup spelling deliberately remains unresolved; do not admit this TU.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"
#include <vector>
#include "coord3d.h"
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(float a,float b,float c) {x=a;y=b;z=c;}
struct Rva005F17C6S12 {int m0,m1,m2;};
struct Rva0020F58E { int m0,m1,m2,m3; operator AsciiString(); };
struct Rva005F17C6S16 : Rva0020F58E {
 Rva005F17C6S16(const Rva005F17C6S16 &);

};
struct AsciiStringPlusText : Rva005F17C6S12 {};
AsciiStringPlusText operator+(const AsciiString &,const char *);
Rva005F17C6S16 Rva005F17C6Build(const Rva005F17C6S12 &,int);
class RenderObjClass;
class HTreeClass;
class Rva003FB65C {public:HTreeClass *rva003FC780(const AsciiString *,int);};
class LivingWorldVisual {public:
 RenderObjClass *createRenderObject(const AsciiString &,const std::vector<AsciiString> &,int,const int *);
 RenderObjClass *createPickboxObject(const AsciiString *);
 void rva003FC291(float);
 void rva003FCCC9(bool);
};
void rva0010E4F6(void *,bool);
struct SubAC005C4B56 {
 char pad00[4]; AsciiString name04; std::vector<AsciiString> names08;
 AsciiString pick14; int pad18; float value1C,scale20,angle24;
 int shadow28,animation2C,value30; char pad34[0x54-0x34]; bool colour54;
};
struct Helper005C4D4B {
 SubAC005C4B56 *m_00; AsciiString m_str; int m_08; bool m_0C;
};
struct ThreeFloatBlock {float v[3]; ThreeFloatBlock(float a,float b,float c) {v[2]=c;v[1]=b;v[0]=a;} };
class Rva003FD14DBase {public:
 Rva003FD14DBase(int);
 ~Rva003FD14DBase();
 virtual void vbfunc();
 void rva003FC82C(float);
 char pad04[4]; void *primary08; char pad0C[0x30-0x0C];
 int value30; char pad34[0xA0-0x34]; ThreeFloatBlock scaleA0;
};
class Rva005C41C9 {public: unsigned char rva005C4B26();};
class Rva002D3627Host {public:
#define V(n) virtual void s##n();
 V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08)
 V(09) V(10) V(11) V(12) V(13) V(14) V(15) V(16)
#undef V
 virtual void insert(void *);
};
extern Rva002D3627Host *g_00DFEF18;
struct ScalarFloat { float value; ScalarFloat(float v):value(v) {} };
class Rva005C4B56 : public Rva003FD14DBase {public:
 Rva005C4B56(const Helper005C4D4B &,bool,const int *);
 virtual void derivedSlot();
 SubAC005C4B56 *m_ac; int m_b0; ScalarFloat m_b4; int m_b8;
};
typedef char BaseExtent[(sizeof(Rva003FD14DBase)==0xAC)?1:-1];
Rva005C4B56::Rva005C4B56(const Helper005C4D4B &h,bool enabled,const int *colour)
 : Rva003FD14DBase(reinterpret_cast<int>(&h.m_str)),
 m_ac(h.m_00),m_b0(h.m_08),m_b4(h.m_00->value1C),m_b8(0)
{
 const_cast<Helper005C4D4B &>(h).m_0C=true;
 _ReadWriteBarrier();
 reinterpret_cast<LivingWorldVisual *>(this)->createRenderObject(
  m_ac->name04,m_ac->names08,m_ac->shadow28,
  m_ac->colour54 ? colour : 0);
 reinterpret_cast<LivingWorldVisual *>(this)->createPickboxObject(&m_ac->pick14);
 rva0010E4F6(primary08,false);
 reinterpret_cast<LivingWorldVisual *>(this)->rva003FC291(m_ac->scale20);
 AsciiString animation=Rva005F17C6Build(m_ac->name04+".",reinterpret_cast<int>(&m_ac->name04));
 reinterpret_cast<Rva003FB65C *>(this)->rva003FC780(&animation,m_ac->animation2C);
 g_00DFEF18->insert(primary08);
 if (!enabled)
  ((reinterpret_cast<LivingWorldVisual *>(this))->*reinterpret_cast<void (LivingWorldVisual::*)(unsigned char)>(&LivingWorldVisual::rva003FCCC9))(
   reinterpret_cast<Rva005C41C9 *>(this)->rva005C4B26());
 value30=m_ac->value30;
 scaleA0=ThreeFloatBlock(1.f,1.f,1.f);
 rva003FC82C(m_ac->angle24*0.017453292f);
}
