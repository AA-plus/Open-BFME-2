// cl: /O1 /MD /EHsc /arch:SSE /G7 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
// Target: 0031942B..00319517; WB names UseArmySummary, assertions 691..705.
// This is a target field view, not a claim about the complete army/summary layout.
// Existing address-derived providers retain their ledger spellings.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/Snapshot.h"

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
class Rva00319CED { public: void *rva004E23C1(); char pad00[0x4C]; int source4C; };
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
    int nativeSize() const { const ArmySummaryEntryRefView *last=entries40.end(); return last-entries40.begin(); }
};
class Rva00318C32Owner { public: int rva00318C32(); };
class Rva003193EC { public: void rva003198B8(Rva003193EC *); };
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
class ArmySummary { public: int AddArmyEntry(const Rva004F6093Holder &); Rva0040DD3ARef RemoveEntry(int); Rva0040DD3ARef rva0040E672(int); Rva0040DD3ARef rva0040E6A4(ArmySummaryEntry *); };
struct HeroTemplateKindView { char pad00[0x113]; unsigned char kind113; };
void __cdecl Rva00030830GameFree(void *);

class Rva003197EEListener
{
public:
 virtual void slot0(void *owner); virtual void slot1(void *); virtual void slot2(void *); virtual void slot3(void *); virtual void slot4(void *);
};

class Rva003197EEList
{
public:
	~Rva003197EEList() { if (m_begin) Rva00030830GameFree(m_begin); }
	void forEach(void (Rva003197EEListener::*notify)(void *), void *owner);
private:
	Rva003197EEListener **m_begin;
	Rva003197EEListener **m_end;
	Rva003197EEListener **m_capacity;
	unsigned int m_index;
};

// Retail's unwind map tracks three bases in construction order: Snapshot,
// the listener list (+8, null-checked conversion) and this observer (+4,
// table 0x00C0C824 reset to 0x00C62A20); MSVC lays the polymorphic
// observer out before the plain list.
class Rva00319D01ObserverBase
{
public:
	__forceinline ~Rva00319D01ObserverBase() {}
 virtual void BeginTurn(int,int) {}
 virtual void EndTurn(int,int) {}
};

class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *data);
};

class LivingWorldRegion
{
public:
	void rva003F0FA3(void *army);
};

struct RegionPointerHandleView {
 LivingWorldRegion *value;
 __forceinline LivingWorldRegion *operator->()const {return value;}
};
struct Rva00319D01RegionOwner
{
	unsigned char m_pad00[0x2C];
	_STL::vector<RegionPointerHandleView> m_regions;	// +0x2C
};

struct Rva00319D01RegionHolder
{
	_STL::vector<RegionPointerHandleView> *regions()
	{
		if (m_owner)
			return &m_owner->m_regions;
		return 0;
	}
	unsigned char m_pad00[8];
	Rva00319D01RegionOwner *m_owner;		// +0x08
};

extern LivingWorldLogic *TheLivingWorldLogic;

class Rva000AD6F4
{
public:
	~Rva000AD6F4();
	ArmySummaryView *m_summary;
};

class Rva00538F61
{
public:
	~Rva00538F61();
private:
	int m_00;
	void *m_04;
};

class Rva00319D01Status
{
public:
	virtual ~Rva00319D01Status();
};

struct BfmeVectorRecord00319C84 { unsigned int words[4]; };
namespace _STL {
template<> vector<BfmeVectorRecord00319C84>::~vector();
}


class Rva00318BEB { public: void rva00318BEB(); };
struct ArmyDestructorLogicView { unsigned char pad00[0x1C]; Rva002B7250 registry1C; unsigned char pad20[0xB0-0x20]; Rva00319D01RegionHolder *regionsB0; };

class LivingWorldArmy : public Snapshot, public Rva003197EEList, public Rva00319D01ObserverBase {
public:
    virtual ~LivingWorldArmy();
    virtual void BeginTurn(int,int); virtual void EndTurn(int,int);
    virtual void crc(Xfer *); virtual void xfer(Xfer *); virtual void loadPostProcess();
    void UseArmySummary(Rva00319CED *source);
    void KillSummaryEntry(int index);
    void rva00319EF9(LivingWorldArmy *source,int key);
    void rva00319EA3(LivingWorldArmy *source,ArmySummaryEntry *entry);
    void TakeUnitFromArmy_Internal(LivingWorldArmy *source, const Rva004F6093Holder &entry);
    AsciiString name18,name1C;
    int owner20;
    AsciiString name24,name28;
    char pad2C[0x4C - 0x2C];
    int source4C;
    char pad50[4];
    int owner54;
    char pad58[0x68 - 0x58];
    UnicodeString text68,text6C;
    char pad70[8];
    Rva000AD6F4 summary78;
    _STL::vector<BfmeVectorRecord00319C84> records7C;
    Rva00319D01Status *status88;
    char pad8C[4];
    Rva00538F61 member90;
};
typedef char LivingWorldArmyExtentCheck[(sizeof(LivingWorldArmy)==0x98)?1:-1];

void LivingWorldArmy::UseArmySummary(Rva00319CED *source)
{
    if (!TheCampaignManager) return;
    void *summary = source->rva004E23C1();
    if (!summary) return;
    *reinterpret_cast<Rva003F40EFRecord *>(summary78.m_summary) = *static_cast<Rva003F40EFRecord *>(summary);
    summary78.m_summary->owner1C = owner20;
    int count = summary78.m_summary->size();
    for (int i = 0; i < count; ++i) {
        ArmySummaryEntryView *entry = reinterpret_cast<ArmySummaryEntryView *>(reinterpret_cast<Rva0040CB2CIndexedField *>(summary78.m_summary)->get(i));
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
    reinterpret_cast<ArmySummary *>(summary78.m_summary)->AddArmyEntry(entry);
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
class Rva0031A257 {
public: Rva0031A257(); char bytes[0x98];
};
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
    Rva0040DD3ARef entry(reinterpret_cast<Rva004F69C3Target *>(reinterpret_cast<Rva0040CB2CIndexedField *>(summary78.m_summary)->get(index)));
    void *thing = reinterpret_cast<Rva0037DCA5 *>(entry.value)->rva0037DC52();
    if (thing && (static_cast<HeroTemplateKindView *>(thing)->kind113 & 4)) {
        Rva002E2903Player *player = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(owner54,0);
        if (!player) return;
        reinterpret_cast<Rva002E34A9 *>(player)->rva002E34A9(entry,1);
    }
    reinterpret_cast<ArmySummary *>(summary78.m_summary)->RemoveEntry(index);
}

// Native319EF9..319F4F owns the returned reference through the transfer.
void LivingWorldArmy::rva00319EF9(LivingWorldArmy *source,int key)
{
 LivingWorldArmy *from=(source?source:source);
 Rva0040DD3ARef entry=reinterpret_cast<ArmySummary *>(from->summary78.m_summary)->rva0040E672(key);
 TakeUnitFromArmy_Internal(from,*reinterpret_cast<const Rva004F6093Holder *>(&entry));
}

// Native319EA3..319EF9 is the owning transfer twin: the established50B
// pointer lookup40E6A4 replaces the integer-key lookup40E672. WB102B780
// confirms the common TakeUnitFromArmy_Internal and reference cleanup chain;
// the original wrapper name remains unknown.
void LivingWorldArmy::rva00319EA3(LivingWorldArmy *source,ArmySummaryEntry *entryToTake)
{
 LivingWorldArmy *from=(source?source:source);
 Rva0040DD3ARef entry=reinterpret_cast<ArmySummary *>(from->summary78.m_summary)->rva0040E6A4(entryToTake);
 TakeUnitFromArmy_Internal(from,*reinterpret_cast<const Rva004F6093Holder *>(&entry));
}

// Native319D01..319E76 RET0; WB102A540 names the army destructor.
// Target fields and twelve-state unwind map establish the base/member order.
// The region span contains four-byte pointer handles; their accessor adds no
// ownership operation. Observer base has two callbacks and no virtual dtor.
LivingWorldArmy::~LivingWorldArmy()
{
	forEach(&Rva003197EEListener::slot0, this);
	reinterpret_cast<Rva00318BEB *>(this)->rva00318BEB();
	if (reinterpret_cast<ArmyDestructorLogicView *>(TheLivingWorldLogic)->regionsB0)
	{
		_STL::vector<RegionPointerHandleView> *regions = reinterpret_cast<ArmyDestructorLogicView *>(TheLivingWorldLogic)->regionsB0->regions();
		if (regions)
		{
			for (unsigned int i = 0; i < regions->size(); ++i)
				(*regions)[i]->rva003F0FA3(this);
		}
	}
	::delete status88;
	for (int i = summary78.m_summary->nativeSize() - 1; i >= 0; --i)
		KillSummaryEntry(i);
	reinterpret_cast<ArmyDestructorLogicView *>(TheLivingWorldLogic)->registry1C.rva002B7250(
		reinterpret_cast<CreateAHeroData *>(static_cast<Rva00319D01ObserverBase *>(this)));
}
