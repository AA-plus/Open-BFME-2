// ?CreateIcon@Impl@ArmyDetailsPanel@StrategicInGameUI@@QAE?AUSBServer@@HPAVArmySummaryEntry@@@Z
// partial score=0.86 date=2026-10-13
// ?CreateIcon@Impl@ArmyDetailsPanel@StrategicInGameUI@@QAE?AUSBServer@@HPAVArmySummaryEntry@@@Z
// partial score=0.75 date=2026-10-11
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native5E4B6F..5E4B9D is the complete46B RET8 callback. WB15F9D40
// independently names ArmyDetailsPanel::Impl::OnRemovingEntryFromArmySummary:
// compare entryID with selected28; invoke same-this existing deselection;
// erase iconMap1C by entryID; remove selected entry through member14.
// Constructor5E4AE2 and CreateIcon5E4CA3 witness the same primary receiver,
// offsets and twelve-byte map. Icon insertion uses the existing four-byte
// refcounted value ABI. Retain that provider's provisional SBServer spelling;
// its actual original handle type remains unknown and no GameSpy role is
// asserted. No handle methods or vtables are defined in this consumer.
// Map key erase is a formally proven whole-body/relocation fold onto5E46A8,
// with its42/33/37/37B bound/distance helpers proved recursively. The provider
// instantiation is emitted here by the vendor definition. Its complete
// body and every recursively called helper are admitted by the fold proof;
// keeping that definition visible preserves retail's cached entryID.
struct TargetRef00217D4C {void *vtable;int count;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct SBServer {
 void *volatile handle;
 SBServer():handle(0){}
 inline __declspec(noinline) SBServer(const SBServer &src):handle(src.handle) {if(handle)++*(int *)((char *)handle+((int **)handle)[0][1]+4);}
 ~SBServer(){if(handle)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)handle+((int **)handle)[0][1]));}
 SBServer &operator=(const SBServer &);
 void Rva005E3E8A(void *);
};
#include <map>
#include "ascii_string.h"
template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
class Rva005E39AE { public: void rva005E3AAA(int); };
class Rva005F22D2 { public: void rva005F2295(int); };
class ArmySummary;
class ArmySummaryEntry {};
class ThingTemplate;
class ThingFactory {public:const ThingTemplate *findTemplate(const AsciiString &);};
extern ThingFactory *TheThingFactory;
namespace StrategicInGameUI {
template<class Entry> static __declspec(noinline) const ThingTemplate *Rva005E3967Factory(Entry *e) {
 return TheThingFactory->findTemplate(*(const AsciiString *)((const char *)e+4));
}}
struct Rva005E39F3Reference {void *vbtable;};
struct Rva005E3BD5Prefix {char bytes[0x10];};
struct Rva005E3C90Prefix {char bytes[0x1C];};
class Rva005E3BD5Icon:public Rva005E3BD5Prefix,public Rva005E39F3Reference {public:char rest[0x30-0x14];Rva005E3BD5Icon(void *,void *,int,ArmySummaryEntry *,bool);};
class Rva005E3C90Icon:public Rva005E3C90Prefix,public Rva005E39F3Reference {public:char rest[0x3C-0x20];Rva005E3C90Icon(void *,void *,int,ArmySummaryEntry *,bool);};
class Rva005F2278 {public:bool rva005F2278(int) const;};
class Rva005F3F41Outer {public:void set(unsigned char);};
namespace StrategicInGameUI {
class ArmyDetailsPanel {
public:
 class Impl {
 public:
  virtual void OnRemovingEntryFromArmySummary(const ArmySummary &,int);
  SBServer CreateIcon(int,ArmySummaryEntry *);
 private:
  char prefix[0xC-4]; void *clip;void *army;Rva005F22D2 *selected; char gap[4];
  _STL::map<int,SBServer> icons; int selectedID;
 };
};
}
void StrategicInGameUI::ArmyDetailsPanel::Impl::OnRemovingEntryFromArmySummary(const ArmySummary &,int entryID) {
 if(entryID==selectedID) reinterpret_cast<Rva005E39AE *>(this)->rva005E3AAA(entryID);
 icons.erase(entryID);
 selected->rva005F2295(entryID);
}

SBServer StrategicInGameUI::ArmyDetailsPanel::Impl::CreateIcon(int entryID,ArmySummaryEntry *entry) {
 SBServer icon;
 const ThingTemplate *type=StrategicInGameUI::Rva005E3967Factory(entry);
 void *reference;
 if(*(const unsigned int *)((const char *)type+0x110)&(1u<<26)) {
  Rva005E3BD5Icon *p=new Rva005E3BD5Icon(this,clip,entryID,entry,true);
  reference=static_cast<Rva005E39F3Reference *>(p);
 } else {
  Rva005E3C90Icon *p=new Rva005E3C90Icon(this,clip,entryID,entry,true);
  reference=static_cast<Rva005E39F3Reference *>(p);
 }
 icon.Rva005E3E8A(reference);
 icons[entryID]=icon;
 if(((Rva005F2278 *)selected)->rva005F2278(entryID)) {
  char *base=(char *)__vref(icon.handle)+((int **)icon.handle)[0][1];
  ((Rva005F3F41Outer *)base)->set(1);
 }
 return icon;
}
