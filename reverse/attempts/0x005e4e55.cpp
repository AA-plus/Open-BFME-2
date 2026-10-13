// ?OnEntryAddedToArmySummary@Impl@ArmyDetailsPanel@StrategicInGameUI@@UAEXABVArmySummary@@H@Z
// partial score=0.9 date=2026-10-13
// ?OnEntryAddedToArmySummary@Impl@ArmyDetailsPanel@StrategicInGameUI@@UAEXABVArmySummary@@H@Z
// partial score=0.9 date=2026-10-11
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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
 void *handle;
 SBServer():handle(0){}
 SBServer(const SBServer &);
 ~SBServer(){if(handle)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)handle+((int **)handle)[0][1]));}
 SBServer &operator=(const SBServer &);
};
#include <map>
#include <vector>
#include "ascii_string.h"
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template<> __declspec(dllimport) __forceinline void allocator<int>::deallocate(int *p,size_t) const {if(p)Rva00030830GameFree(p);}
}

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
class ArmySummaryEntry {};
class Rva004F6093Holder {
public:
 Rva004F6093Holder():m_p(0){}
 Rva004F6093Holder(const Rva004F6093Holder &);
 ~Rva004F6093Holder(){if(m_p)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)m_p+0xAC));}
 ArmySummaryEntry *get() const {return (ArmySummaryEntry *)m_p;}
private: void *m_p;
};
struct ArmySummaryEntryRef {Rva004F6093Holder m_holder;};
struct ArmyDetailsSummaryRecord {int key;void *entry;};
class ArmySummary {public: ArmySummaryEntryRef GetEntry(int);char pad[0x40];ArmyDetailsSummaryRecord *begin,*end;};
class Rva0040CB2CIndexedField {public:int get(int) const;};
class Rva0040CC0EIndexedField {public:int get(int) const;};
struct ArmyDetailsArmyView {char pad[0x18];AsciiString name;char gap[0x78-0x1C];ArmySummary *summary;};
struct Rva005E4300Context;
class Rva005E4300Cmp {public:
 explicit Rva005E4300Cmp(Rva005E4300Context *p):m_context(p){}
 char operator()(int,int) const;
private:Rva005E4300Context *m_context;
};
int *__cdecl rva005E49FD(int *,int *,Rva005E4300Cmp,int);
class ArmyDetailsIconSlotView {public:virtual void slot0();virtual void slot1();virtual void MoveTo(int);};
struct ArmyDetailsMemberIconView {int *vbtable;char gap[8];ArmyDetailsIconSlotView *slot;};
struct Rva005E4CA3IconRef {
 ~Rva005E4CA3IconRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)ptr+ptr->vbtable[1]));}
 ArmyDetailsMemberIconView *ptr;
};
enum ScienceType {SCIENCE_NONE=0};
namespace _STL {template<> void vector<ScienceType>::reserve(unsigned);}
class Rva0040E6D6Sub {public:void forward(int *);};
namespace StrategicInGameUI {
class ArmyDetailsPanel {
public:
 class Impl {
 public:
  virtual void OnRemovingEntryFromArmySummary(const ArmySummary &,int);
  virtual void OnEntryAddedToArmySummary(const ArmySummary &,int);
  SBServer CreateIcon(int,ArmySummaryEntry *);
 private:
  char prefix[0x10-4]; ArmyDetailsArmyView *army; Rva005F22D2 *selected; char gap[4];
  _STL::map<int,SBServer> icons; int selectedID;
 };
};
}
void StrategicInGameUI::ArmyDetailsPanel::Impl::OnRemovingEntryFromArmySummary(const ArmySummary &,int entryID) {
 if(entryID==selectedID) reinterpret_cast<Rva005E39AE *>(this)->rva005E3AAA(entryID);
 icons.erase(entryID);
 selected->rva005F2295(entryID);
}

void StrategicInGameUI::ArmyDetailsPanel::Impl::OnEntryAddedToArmySummary(const ArmySummary &,int entryID) {
 ArmySummary *summary=army->summary;
 SBServer icon=CreateIcon(entryID,summary->GetEntry(entryID).m_holder.get());
 int entryCount=summary->end-summary->begin;
 _STL::vector<int> entryIDs;
 ((_STL::vector<ScienceType> *)&entryIDs)->reserve((unsigned)icons.size());
 for(int i=0;i<entryCount;++i) {
  int rawEntry=((Rva0040CB2CIndexedField *)summary)->get(i);
  if(((AsciiString *)(rawEntry+4))->compare(army->name)!=0) {
   int id=((Rva0040CC0EIndexedField *)summary)->get(i);
   ((Rva0040E6D6Sub *)&entryIDs)->forward(&id);
  }
 }
 int *first;
 int *it=rva005E49FD(first=entryIDs.begin(),entryIDs.end(),Rva005E4300Cmp((Rva005E4300Context *)army),entryID);
 ((ArmyDetailsMemberIconView *)icon.handle)->slot->MoveTo(it-first);
}
