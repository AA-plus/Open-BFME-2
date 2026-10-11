// FUN_0071A372
// partial score=1.0 date=2026-10-11
// cl: /O1 /MD /EHsc /arch:SSE /G7 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
// Target: 0031942B..00319517; WB names UseArmySummary, assertions 691..705.
// This is a target field view, not a claim about the complete army/summary layout.
// Existing address-derived providers retain their ledger spellings.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#include "Common/Snapshot.h"
#include "Coord2D.h"
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
class Rva004EDFFFDwordImmSetter {public:void apply();};
class CtorRegionTurnObserver {public:~CtorRegionTurnObserver(){((Rva004EDFFFDwordImmSetter*)this)->apply();}virtual void first(int,int);virtual void second(int,int);};



// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}
class ThingTemplate { public: int rva0033B479() const; };
class Rva00319CED { public: bool rva00319CED(); void *rva004E23C1(); char pad00[0x4C]; int source4C; };
struct Rva003F40EFRecord {
    Rva003F40EFRecord &operator=(const Rva003F40EFRecord &);
    char bytes[104];
};
class Rva0040CB2CIndexedField { public: int get(int) const; };
class Rva0037DCA5 { public: void *rva0037DC52(); };
class ExperienceLevelList;
class ExperienceLevelIterator {
public:
    ExperienceLevelIterator() {}
    ExperienceLevelIterator(const ExperienceLevelIterator &other) : m_node(other.m_node) {}
private: void *m_node;
};
struct ExperienceLevelHandle {
    ExperienceLevelHandle() {}
    ExperienceLevelHandle(const ExperienceLevelHandle &other) : m_list(other.m_list), m_iter(other.m_iter) {}
    ExperienceLevelList *m_list;
    ExperienceLevelIterator m_iter;
};
class ExperienceLevelStore {
public:
    ExperienceLevelHandle rva00288E21(const ThingTemplate *, int) const;
    bool IsValid(ExperienceLevelHandle) const;
    int GetRequiredExperience(ExperienceLevelHandle) const;
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;
struct ArmySummaryEntryView {
    char pad00[8];
    float requiredExperience08;
    int level0C;
    char pad10[0xC0 - 0x10];
    int sourceC0;
};
struct ArmySummaryEntryRefView { void *control; ArmySummaryEntryView *entry; };
struct ArmySummaryView {
    char pad00[0x1C];
    int owner1C;
    char pad20[0x40 - 0x20];
    _STL::vector<ArmySummaryEntryRefView> entries40;
    int size() const { return entries40.size(); }
};
class Rva00318C32Owner { public: int rva00318C32(); };
class Rva003193EC { public: void rva003198B8(Rva003193EC *); void rva003190E7(bool); };
class ArmySummaryEntry { public: void CancelUpgrades(); };
class Rva004F6093Holder { public: ArmySummaryEntry *entry; };
struct TargetRef00217D4C { void *vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva004F69C3Target { char pad00[0xAC]; TargetRef00217D4C ref; };
struct Rva0040DD3ARef {
    Rva004F69C3Target *value;
    Rva0040DD3ARef(Rva004F69C3Target *p) : value(p) { if(value) ++value->ref.references; }
    Rva0040DD3ARef(const Rva0040DD3ARef &other) : value(other.value) { if(value) ++value->ref.references; }
    ~Rva0040DD3ARef() { if(value) ReleaseTreeHintRef00217D4C(&value->ref); }
};
class Rva002E2903Player;
class Rva002BA8F1Logic { public: Rva002E2903Player *find(int,unsigned int *); };
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002E34A9 { public: void rva002E34A9(const Rva0040DD3ARef &,int); };
class ArmySummary { public: ArmySummary(); char footprint[0x68]; int AddArmyEntry(const Rva004F6093Holder &); Rva0040DD3ARef RemoveEntry(int); Rva0040DD3ARef rva0040E672(int); Rva0040DD3ARef rva0040E6A4(ArmySummaryEntry *); };
struct HeroTemplateKindView { char pad00[0x113]; unsigned char kind113; };
class LivingWorldArmy {
public:
    void UseArmySummary(Rva00319CED *source);
    void KillSummaryEntry(int index);
    void rva00319EF9(LivingWorldArmy *source,int key);
    void rva00319EA3(LivingWorldArmy *source,ArmySummaryEntry *entry);
    void TakeUnitFromArmy_Internal(LivingWorldArmy *source, const Rva004F6093Holder &entry);
    char pad00[0x20];
    int owner20;
    char pad24[0x4C - 0x24];
    int source4C;
    char pad50[4];
    int owner54;
    char pad58[0x78 - 0x58];
    ArmySummaryView *summary78;
};
void LivingWorldArmy::UseArmySummary(Rva00319CED *source)
{
    if (!TheCampaignManager) return;
    void *summary = source->rva004E23C1();
    if (!summary) return;
    *reinterpret_cast<Rva003F40EFRecord *>(summary78) = *static_cast<Rva003F40EFRecord *>(summary);
    summary78->owner1C = owner20;
    int count = summary78->size();
    for (int i = 0; i < count; ++i) {
        ArmySummaryEntryView *entry = reinterpret_cast<ArmySummaryEntryView *>(reinterpret_cast<Rva0040CB2CIndexedField *>(summary78)->get(i));
        ThingTemplate *thing = static_cast<ThingTemplate *>(reinterpret_cast<Rva0037DCA5 *>(entry)->rva0037DC52());
        if (!thing) continue;
        int level = thing->rva0033B479();
        entry->level0C = level;
        ExperienceLevelHandle handle = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->rva00288E21(thing, level);
        if (reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->IsValid(handle))
            entry->requiredExperience08 = static_cast<float>(reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetRequiredExperience(handle));
        entry->sourceC0 = source->source4C;
    }
}

void LivingWorldArmy::TakeUnitFromArmy_Internal(LivingWorldArmy *source, const Rva004F6093Holder &entry)
{
    reinterpret_cast<ArmySummary *>(summary78)->AddArmyEntry(entry);
    if (reinterpret_cast<Rva00318C32Owner *>(this)->rva00318C32() != reinterpret_cast<Rva00318C32Owner *>(source)->rva00318C32())
        entry.entry->CancelUpgrades();
    reinterpret_cast<Rva003193EC *>(this)->rva003198B8(reinterpret_cast<Rva003193EC *>(source));
}

// ABI view: retail owns an army pointer vector; the existing ModuleData pointer
// instantiation supplies its folded reserve/push/erase calls, not element identity.
class ModuleData;
namespace _STL {
template<> void vector<const ModuleData *>::reserve(unsigned int);
template<> void vector<const ModuleData *>::push_back(const ModuleData * const &);
template<> vector<void *>::iterator vector<void *>::erase(iterator,iterator);
}

struct BfmeVectorRecord00319C84 { unsigned words[4]; };
namespace _STL { template<> vector<BfmeVectorRecord00319C84>::~vector(); }
class PlayingAudioUnknown0C {public: PlayingAudioUnknown0C();void*words[2];};
class Rva00538F61 { public: __forceinline Rva00538F61(){ ((PlayingAudioUnknown0C*)this)->PlayingAudioUnknown0C::PlayingAudioUnknown0C(); } ~Rva00538F61(); void *words[2]; };
class Object;
class Rva00575674 {public:void rva00575674(Object*);};
class Rva000AD6F4 {public: ~Rva000AD6F4();void*word;};
struct ArmySummaryOwner {
 ArmySummary *word;
 ArmySummaryOwner():word(0){}
 ~ArmySummaryOwner() { ((Rva000AD6F4*)this)->Rva000AD6F4::~Rva000AD6F4(); }
 void reset(ArmySummary *x) { ((Rva00575674*)this)->rva00575674((Object*)x); }
};
struct Rva002BA8F1Listener;
class Rva005A0B4CList {public:void append(Rva002BA8F1Listener*);};
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
struct CtorArmyMinusOneWord { int word; __forceinline CtorArmyMinusOneWord(int v):word(v){_ReadWriteBarrier();} };
struct CtorArmyPair {float x,y; __forceinline CtorArmyPair():x(0),y(0){} };
struct CtorArmyLastPair {float x,y; __forceinline CtorArmyLastPair():x(0),y(0){_ReadWriteBarrier();} };

class Rva004E3184 {public: char pad00[4]; AsciiString a04,a08; char pad0C[12]; AsciiString a18; char pad1C[12]; AsciiString a28; char pad2C[24]; float f44; char pad48[8]; AsciiString a50; bool b54;};
struct Rva002B6A04Player {char pad00[20];int id14;};
class LivingWorldArmyLine {public:void rva00539141();};
class Rva0031934BOwner {public:void rva0031934B(const AsciiString*);};
struct Rva00318E8COut {float f;int i;};
class Rva00318E8C {public:Rva00318E8COut *rva00318E8C(Rva00318E8COut*);};
struct Rva003F0F13Elem {float x,y;};
class LivingWorldRegion {public:void GetGarrisonArmyPlacementSpot(Rva003F0F13Elem*);};
class Rva002104B6 {public:void*rva002104B6(void*);};
class Rva00319AA0 {public:void rva00319AA0(const Coord2D*);};
class Rva00318F64 {public:void rva00318F64();};

struct CtorArmyScalar {float x;__forceinline CtorArmyScalar(float v):x(v){} };
class Rva0031A257:public Snapshot,public Rva00330757Member,public CtorRegionTurnObserver {
public:
 Rva0031A257();
 Rva0031A257(int,Rva004E3184*,Rva002B6A04Player*);
 virtual ~Rva0031A257();
 virtual void LoadPostProcess();
 virtual const char *GetSnapshotName();
 virtual void DoXfer(Xfer*);
 virtual void first(int,int);virtual void second(int,int);
 AsciiString a18,a1C;
 int owner20;
 AsciiString a24,a28;
 CtorArmyMinusOneWord v2C; int v30;
 CtorArmyPair pos34,pos3C,pos44; CtorArmyLastPair pos4C;
 int owner54;
 bool b58,b59;
 CtorArmyScalar f5C;
 int v60;
 bool b64,b65;
 UnicodeString u68,u6C;
 int v70;
 bool b74,b75;
 ArmySummaryOwner summary78;
 _STL::vector<BfmeVectorRecord00319C84> records7C;
 int v88,v8C;
 Rva00538F61 audio90;
};
Rva0031A257::Rva0031A257(): v2C(-1),v30(0),owner54(-1),b58(true),b59(false),f5C(0),v60(1),b64(false),b65(false),v70(-1),b74(false),b75(false),v88(0),v8C(0) {
 summary78.reset(new ArmySummary);
 ((Rva005A0B4CList*)((char*)TheLivingWorldLogic+0x1C))->append((Rva002BA8F1Listener*)(CtorRegionTurnObserver*)this);
}

Rva0031A257::Rva0031A257(int owner,Rva004E3184 *desc,Rva002B6A04Player *player):a18(desc->a50),a1C(desc->a18),a24(desc->a04),a28(desc->a08),v2C(-1),v30(0),owner54(-1),b58(true),b59(false),f5C(desc->f44),v60(1),b64(false),b65(false),v70(-1),b74(desc->b54),b75(false),v88(0),v8C(0) {
 _ReadWriteBarrier();
 owner20=owner;
 if(player)owner54=player->id14;
 if(!b74)((LivingWorldArmyLine*)&audio90)->rva00539141();
 summary78.reset(new ArmySummary);
 if(((Rva00319CED*)desc)->rva00319CED())((LivingWorldArmy*)this)->UseArmySummary((Rva00319CED*)desc);
 ((ArmySummaryView*)summary78.word)->owner1C=owner;
 ((AsciiString*)((char*)summary78.word+0x20))->set(a28);
 ((Rva0031934BOwner*)this)->rva0031934B(&desc->a04);
 ((Rva003193EC*)this)->rva003190E7(false);
 if(desc->a28.isEmpty()) {
  Rva00318E8COut pos;
  ((Rva00319AA0*)this)->rva00319AA0((Coord2D*)((Rva00318E8C*)desc)->rva00318E8C(&pos));
 } else {
  Rva002104B6 *store=(Rva002104B6*)*(void**)((char*)TheLivingWorldLogic+0xB0);
  _ReadWriteBarrier();
  LivingWorldRegion *region=(LivingWorldRegion*)store->rva002104B6(&desc->a28);
  Rva00318E8COut pos;
  ((Rva00318E8C*)desc)->rva00318E8C(&pos);
  if(region)region->GetGarrisonArmyPlacementSpot((Rva003F0F13Elem*)&pos);
  ((Rva00319AA0*)this)->rva00319AA0((Coord2D*)&pos);
 }
 ((Rva00318F64*)this)->rva00318F64();v30=0;
 ((Rva005A0B4CList*)((char*)TheLivingWorldLogic+0x1C))->append((Rva002BA8F1Listener*)(CtorRegionTurnObserver*)this);
}

class Xfer {
public:
    struct Version { unsigned char current, minimum; Version(unsigned char a,unsigned char b):current(a),minimum(b){} };
    virtual void slot00();
    virtual bool IsLoading() const;
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual Xfer &xferVersion(Version &);
    virtual void slot11();
    virtual Xfer &xferSnapshot(void *);
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual Xfer &xferInt(int &);
};
void XferOwningLivingWorldArmyVec(Xfer *xfer, _STL::vector<const ModuleData *> *armies)
{
    Xfer::Version version(1,1);
    xfer->xferVersion(version);
    if (xfer->IsLoading()) {
        _STL::vector<void *> *pointerView = reinterpret_cast<_STL::vector<void *> *>(armies);
        pointerView->erase(pointerView->begin(), pointerView->end());
        int count;
        xfer->xferInt(count);
        armies->reserve(count);
        for (int i=0; i<count; ++i) {
            const ModuleData *army=reinterpret_cast<const ModuleData *>(new Rva0031A257);
            xfer->xferSnapshot(const_cast<ModuleData *>(army));
            armies->push_back(army);
        }
    } else {
        int count=armies->size();
        xfer->xferInt(count);
        for (unsigned int i=0; i<armies->size(); ++i)
            xfer->xferSnapshot(const_cast<ModuleData *>((*armies)[i]));
    }
}

void LivingWorldArmy::KillSummaryEntry(int index)
{
    if (index < 0) return;
    Rva0040DD3ARef entry(reinterpret_cast<Rva004F69C3Target *>(reinterpret_cast<Rva0040CB2CIndexedField *>(summary78)->get(index)));
    void *thing = reinterpret_cast<Rva0037DCA5 *>(entry.value)->rva0037DC52();
    if (thing && (static_cast<HeroTemplateKindView *>(thing)->kind113 & 4)) {
        Rva002E2903Player *player = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(owner54,0);
        if (!player) return;
        reinterpret_cast<Rva002E34A9 *>(player)->rva002E34A9(entry,1);
    }
    reinterpret_cast<ArmySummary *>(summary78)->RemoveEntry(index);
}

// Native319EF9..319F4F owns the returned reference through the transfer.
void LivingWorldArmy::rva00319EF9(LivingWorldArmy *source,int key)
{
 LivingWorldArmy *from=(source?source:source);
 Rva0040DD3ARef entry=reinterpret_cast<ArmySummary *>(from->summary78)->rva0040E672(key);
 TakeUnitFromArmy_Internal(from,*reinterpret_cast<const Rva004F6093Holder *>(&entry));
}

// Native319EA3..319EF9 is the owning transfer twin: the established50B
// pointer lookup40E6A4 replaces the integer-key lookup40E672. WB102B780
// confirms the common TakeUnitFromArmy_Internal and reference cleanup chain;
// the original wrapper name remains unknown.
void LivingWorldArmy::rva00319EA3(LivingWorldArmy *source,ArmySummaryEntry *entryToTake)
{
 LivingWorldArmy *from=(source?source:source);
 Rva0040DD3ARef entry=reinterpret_cast<ArmySummary *>(from->summary78)->rva0040E6A4(entryToTake);
 TakeUnitFromArmy_Internal(from,*reinterpret_cast<const Rva004F6093Holder *>(&entry));
}
