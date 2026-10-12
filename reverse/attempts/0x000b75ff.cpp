// ?rva000B75FF@Rva000B75FF@@QAE_N_N@Z
// partial score=0.935 date=2026-10-12
// Retail B75FF..B77B2 is complete435B RET4; returnAL=1 and byte arg guard.
// W3DModelDraw client particle update family from adjacent matched calls and
// WB92EF60; exact original name remains unknown (secondary receiver+0C).
// Native proves state+8/render44/list58 and data at this-8/drawable this-4;
// MD byte12A selects name lookup; particle flag1A7 and record0 ID/4bone/8text.
// Manager/private handle-return1F5B0A, handle cleanup4CBC0/factory1FCBD7,
// record copyB757D and StringBase release36410, Drawable272835 HH ABI,
// particle setter1F38C1 struct12word ABI and byte methods1F384A/52/1F3C13
// are all owned providers. Render slots51 hidden48B return and53 bool query
// are established from target pushes/AL. Donor W3DModelDraw particle method
// supplies purpose; new name-based path and inactive flag are target additions.
// Full435B candidate: remaining delayed EBX/EDI saves, iterator/handle slot
// packing and early-empty cleanup flow. Baseline430B wrapping-if source skips
// native early EH-state reset; explicit continue restores it but allocator
// moves iterator into EBX and adds first-iteration bypass. All runtime work
// resolved; inline/realSTL iterators, guard shape, dtor throw and empty ctor
// variants do not fix the allocation. Keep this complete bank for next seat.
// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
#include <list>
#include "ascii_string.h"
namespace _STL {template<class I,class L,class R>static inline bool operator!=(const _List_iterator<I,L>&a,const _List_iterator<I,R>&b){return a._M_node!=b._M_node;}}
class ParticleSystem;
ParticleSystem *Make001FCBD7();
class RvaSmartPtr12 {public:void rva0004CBC0()throw();};
class BfmeParticleSystemHandle {public:
 ParticleSystem *ptr;void *previous,*next;
 __forceinline ~BfmeParticleSystemHandle()throw(){if(ptr)((RvaSmartPtr12*)this)->rva0004CBC0();}
 __forceinline operator bool()const{return ptr!=0;}
 __forceinline ParticleSystem *operator->()const{return ptr?ptr:Make001FCBD7();}
};
enum ParticleSystemID {INVALID_PARTICLE_SYSTEM_ID=0};
class Rva000B75FF;
class ParticleSystemManager {BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID);friend class Rva000B75FF;};
extern ParticleSystemManager *TheParticleSystemManager;
class Rva001F3852ByteOneSetter {public:void enable();};
class Rva001F384AByteZeroSetter {public:void disable();};
class Rva001F3C13ByteSlot {public:void set(unsigned char);};
struct Rva001F38C1Arg {int words[12];};
class Rva001F38C1Slot {public:void set(const Rva001F38C1Arg&);};
struct ParticleFlagView {char pad[0x1a7];bool active;};
struct ParticleMDView {char pad[0x12a];bool useDrawableBones;};
struct BfmeStringRecord000B757D {unsigned word0,word1;AsciiString text;unsigned word2;unsigned char tail;BfmeStringRecord000B757D(const BfmeStringRecord000B757D&);};
struct ParticleTrackerNode {ParticleTrackerNode*next,*previous;BfmeStringRecord000B757D value;};
class Drawable {public:bool rva00272835(int,int);};
struct ParticleMatrixView {float values[12];};
class ParticleRenderCallView {public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void s19();
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual void s31();
 virtual void s32();
 virtual void s33();
 virtual void s34();
 virtual void s35();
 virtual void s36();
 virtual void s37();
 virtual void s38();
 virtual void s39();
 virtual void s40();
 virtual void s41();
 virtual void s42();
 virtual void s43();
 virtual void s44();
 virtual void s45();
 virtual void s46();
 virtual void s47();
 virtual void s48();
 virtual void s49();
 virtual void s50();
 virtual ParticleMatrixView Get_Bone_Transform(int)const;
 virtual void s52();
 virtual bool Is_Bone_Captured(int)const;
};
class Rva000B75FF {public:
 char pad00[8];void *state;char pad0c[0x44-0xc];ParticleRenderCallView *render;char pad48[0x58-0x48];_STL::list<BfmeStringRecord000B757D> systems;
 __forceinline const ParticleMDView *data()const{return *(const ParticleMDView*const*)((const char*)this-8);}
 __forceinline Drawable *drawable()const{return *(Drawable*const*)((const char*)this-4);}
 bool rva000B75FF(bool ignoreInactive);
};
bool Rva000B75FF::rva000B75FF(bool ignoreInactive){
 if(state && render && drawable()) {
  for(_STL::list<BfmeStringRecord000B757D>::const_iterator it=systems.begin();it!=systems.end();++it) {
   const BfmeStringRecord000B757D &entry=*it;
   BfmeParticleSystemHandle sys=TheParticleSystemManager->findParticleSystemByID((ParticleSystemID)entry.word0);
   if(!sys)continue; {
    if(!((ParticleFlagView*)sys.ptr)->active && ignoreInactive)return true;
    int bone=entry.word1;
    if(data()->useDrawableBones) {
     BfmeStringRecord000B757D record(entry);
     ParticleMatrixView transform;
     if(drawable()->rva00272835((int)record.text.str(),(int)&transform)) {
      ((Rva001F38C1Slot*)sys.operator->())->set(*(const Rva001F38C1Arg*)&transform);
      ((Rva001F3C13ByteSlot*)sys.operator->())->set(1);
     }
    }else if(bone) {
     if(render->Is_Bone_Captured(bone))((Rva001F384AByteZeroSetter*)sys.operator->())->disable();
     else ((Rva001F3852ByteOneSetter*)sys.operator->())->enable();
     const ParticleMatrixView transform=render->Get_Bone_Transform(bone);
     ((Rva001F38C1Slot*)sys.operator->())->set(*(const Rva001F38C1Arg*)&transform);
     ((Rva001F3C13ByteSlot*)sys.operator->())->set(1);
    }
   }
  }
 }
 return true;
}
