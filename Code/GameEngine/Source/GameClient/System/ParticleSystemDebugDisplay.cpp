// partial score=0.98 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_MALLOC
// stlport
// BF1 readonly9cbfb551 ParticleSystemDebugDisplay semantic donor.
// Native001FA04B..001FA4401013B has identical statistics literals and
// list/template-tree purpose, with target slots and layout witnessed below.
// This unit retains only independently verified STL helper instantiations.
// The1013B caller is banked at reverse/attempts/0x001fa04b.cpp.
#include "ascii_string.h"
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_USE_STATIC_LIB
#include <map>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}
bool operator<(const AsciiString &,const AsciiString &);
namespace _STL { template<> struct less<AsciiString> { bool operator()(const AsciiString &a,const AsciiString &b) const { return a<b; } }; }

class DebugDisplayInterface;
struct _iobuf;
class ParticleSystemManager;
class GlobalData;
extern ParticleSystemManager *TheParticleSystemManager;
extern GlobalData *TheWritableGlobalData;

// Address-derived views: only slots/offsets used by this retail body are asserted.
struct Rva001FA04BDisplay {
 virtual void slot00();
 virtual void print(const char *, ...);
 virtual void slot08();
 virtual void cursor(int, int);
 virtual void slot10(); virtual void slot14(); virtual void slot18();
 virtual void slot1c();
 virtual void margin(int);
};
struct Rva001FA04BManager {
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0c(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1c(); virtual void slot20();
 virtual void slot24();virtual void slot28();virtual void slot2c();virtual void slot30();virtual void slot34();
 virtual int onScreen();
};
namespace FXParticleSystem { class ParticleSystemTemplate { public: AsciiString getName() const; }; }
struct Rva001FA04BParticleModule {
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();
 virtual void slot4();virtual void slot5();virtual void slot6();virtual int getCount();
};
class ParticleSystem {
public:
 char pad00[0xa4];Rva001FA04BParticleModule *countA4;
 unsigned padA8;float costAC;
 char padB0[0x198-0xb0];FXParticleSystem::ParticleSystemTemplate *template198;
 FXParticleSystem::ParticleSystemTemplate *getTemplate() const{return template198;}
 int getParticleCount() const{return countA4->getCount();}
 float getCost() const{return costAC;}
};
ParticleSystem *Make001FCBD7();
class RvaSmartPtr12 {
public:
 ParticleSystem *particle;void *previous,*next;
 RvaSmartPtr12(const RvaSmartPtr12&);
 ~RvaSmartPtr12();
 ParticleSystem *get() const{return particle?particle:Make001FCBD7();}
};
class Rva0004CCFF {public:void *destroyDelete(unsigned int);};
// Native list clear1F65AF destroys the12B value through4CCFF(flags0).
// Keep this observed cleanup ABI without claiming a virtual pointer layout.
namespace _STL {template<> __forceinline void _Destroy(RvaSmartPtr12 *p){((Rva0004CCFF *)p)->destroyDelete(0);}}
#include <list>
template<> _STL::list<RvaSmartPtr12>::list(const _STL::list<RvaSmartPtr12>&);
class Rva001F81EC {public:void rva001F81EC();};
typedef _STL::list<RvaSmartPtr12> ParticleDebugList;

// Native1013B statistics caller proves these typed int/float map and
// handle-list instantiations. Their full bodies and every call target are
// byte-and-relocation twins of the existing owners; zero unique-byte gain.
// The calling diagnostic body remains banked while its print register differs.
// This TU's class instantiation below would otherwise emit a second
// map<AsciiString,float>::operator[] COMDAT differing from the rowed
// 0x5B67C provider in AsciiStringTableSubscripts.cpp; a declaration-only
// member specialization keeps this TU's copy out so callers bind retail's.
namespace _STL {
template <> float &map<AsciiString, float, less<AsciiString>, allocator<pair<const AsciiString, float> > >::operator[](const AsciiString &);
}
template class _STL::map<AsciiString,int>;
template class _STL::map<AsciiString,float>;
template class _STL::_List_base<RvaSmartPtr12,_STL::allocator<RvaSmartPtr12> >;
template class _STL::pair<AsciiString,int>;
template class _STL::pair<AsciiString,float>;
template class _STL::pair<const AsciiString,int>;
template class _STL::pair<const AsciiString,float>;
template _STL::pair<AsciiString,int> _STL::make_pair(const AsciiString&,const int&);
template _STL::pair<AsciiString,float> _STL::make_pair(const AsciiString&,const float&);
template _STL::pair<const AsciiString,int>::pair(const _STL::pair<AsciiString,int>&);
template _STL::pair<const AsciiString,float>::pair(const _STL::pair<AsciiString,float>&);
