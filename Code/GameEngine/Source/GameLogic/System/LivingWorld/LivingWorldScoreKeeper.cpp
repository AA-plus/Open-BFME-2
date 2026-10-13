// cl: /O1 /G7 /arch:SSE /EHs /DNDEBUG /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// LivingWorldScoreKeeper: complete 0xFC-byte Snapshot with eight observer
// interfaces. WB10EF240 establishes the class and observer names; retail
// constructor4EEADE, destructor4EED02, primary tableC62AC4 and all eight
// secondary tables establish the offsets and callback ownership independently.
// Base Phase/RTS tablesC62A20 contain two RET8 callbacks, not deleting dtors.
// Base widths in interface order: 8,16,12,8,16,16,8,16 bytes. Final tables:
// C62ABC/C62AAC/C62AA0/C62A98/C62A88/C62A78/C62A70/C62A60.
// eventN_M names describe the proven interface and slot only; the original
// callback names remain unknown. Each override reproduces its existing retail
// body, including the compiler's secondary-this adjustment. Default slots are
// real empty methods with the target RET4/8/12 ABI. /EHs preserves the native
// destructor's four inline storage-free transitions.
// The twelve-byte map storage invokes the existing int/pointer constructor
// at33C432 and unsigned/pointer tree teardown at357C6A. Both are independently
// proven retail providers; no extra template pin is introduced. Collector/xfer
// use the established template-key/integer-count view. The storage view does
// not assert the original template spelling. Vector roles are localized too.
// Scratch raw objects, table-slot proof and EH checks: build/astra-high-d/.
#include <vector>
#include <map>
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

extern "C" __declspec(dllimport) long __cdecl time(long *);

class Rva004E06FBPtrChase32Field; class LivingWorldBattle; struct Rva004EF2ABArg; class LivingWorldLogic; class CountInputPrefix;
class LivingWorldPhaseObserver {public: ~LivingWorldPhaseObserver(){} virtual void event0_0(int,int){} virtual void event0_1(int,int){} };
class LivingWorldBuildingObserver {public: ~LivingWorldBuildingObserver(){} virtual void event1_0(Rva004E06FBPtrChase32Field*){} virtual void event1_1(int){} virtual void event1_2(int){} virtual void event1_3(const Rva004E06FBPtrChase32Field*,int){} };
class LivingWorldAutoResolveEventObserver {public: ~LivingWorldAutoResolveEventObserver(){} virtual void event2_0(int,int,int){} virtual void event2_1(int,int,int){} virtual void event2_2(int,LivingWorldBattle*,void*){} };
class LivingWorldRTSEventObserver {public: ~LivingWorldRTSEventObserver(){} virtual void event3_0(int,int){} virtual void event3_1(int,LivingWorldBattle*){} };
class LivingWorldRegionObserver {public: ~LivingWorldRegionObserver(){} virtual void event4_0(int,int,int){} virtual void event4_1(int,int,int){} virtual void event4_2(int,int){} virtual void event4_3(int,int){} };
class LivingWorldPlayerObserver {public: ~LivingWorldPlayerObserver(){} virtual void event5_0(Rva004EF2ABArg*){} virtual void event5_1(int,int,int){} virtual void event5_2(int,int,int){} virtual void event5_3(int){} };
class LivingWorldLogicObserver {public: ~LivingWorldLogicObserver(){} virtual void event6_0(int){} virtual void event6_1(LivingWorldLogic*){} };
class LivingWorldBuildingNuggetSpawnArmyObserver {public: ~LivingWorldBuildingNuggetSpawnArmyObserver(){} virtual void event7_0(int){} virtual void event7_1(int,int){} virtual void event7_2(int,int){} virtual void event7_3(CountInputPrefix*,void*){} };

struct Rva002BA8F1Listener;
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *); };
class Rva002B7250;
extern Rva002B7250 g_00E04424, g_00E02E88, g_00E044F0;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class LivingWorldPlayer;

struct Rva004EE501 : public _STL::_Vector_base<int, _STL::allocator<int> >
{
	__forceinline Rva004EE501() : _STL::_Vector_base<int, _STL::allocator<int> >(_STL::allocator<int>()) {}
	~Rva004EE501();
};

typedef _STL::map<int,void*> ScoreMapCtor;
typedef _STL::pair<const unsigned,void*> ScoreMapPair;
typedef _STL::_Rb_tree<unsigned,ScoreMapPair,_STL::_Select1st<ScoreMapPair>,_STL::less<unsigned>,_STL::allocator<ScoreMapPair> > ScoreMapDtor;
namespace _STL {template<> map<int,void*>::map();}
struct ScoreMapStorage {
 __forceinline ScoreMapStorage(){((ScoreMapCtor*)this)->ScoreMapCtor::map();}
 __forceinline ~ScoreMapStorage(){((ScoreMapDtor*)this)->ScoreMapDtor::~ScoreMapDtor();}
 char bytes[12];
};
class LivingWorldScoreKeeper : public Snapshot,
	public LivingWorldPhaseObserver,
	public LivingWorldBuildingObserver,
	public LivingWorldAutoResolveEventObserver,
	public LivingWorldRTSEventObserver,
	public LivingWorldRegionObserver,
	public LivingWorldPlayerObserver,
	public LivingWorldLogicObserver,
	public LivingWorldBuildingNuggetSpawnArmyObserver
{
public:
	LivingWorldScoreKeeper(int playerIndex, LivingWorldPlayer *player);
	virtual ~LivingWorldScoreKeeper();
 virtual void event0_1(int,int);
virtual void event1_0(Rva004E06FBPtrChase32Field*);virtual void event1_3(const Rva004E06FBPtrChase32Field*,int);
virtual void event2_2(int,LivingWorldBattle*,void*);virtual void event3_0(int,int);virtual void event3_1(int,LivingWorldBattle*);
virtual void event4_0(int,int,int);virtual void event5_0(Rva004EF2ABArg*);virtual void event6_1(LivingWorldLogic*);virtual void event7_3(CountInputPrefix*,void*);
protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
private:
	LivingWorldPlayer *m_player;		// +0x24
	Rva004EE501 m_28;
	_STL::vector<int> m_34, m_40, m_4C;
	_STL::vector<bool> m_58;
	int m_6C;
	long m_startTime;			// +0x70
	int m_74, m_78, m_7C;
	int m_80[5];
	int m_94, m_98;
	ScoreMapStorage m_9C;
	int m_A8, m_AC, m_B0;
	ScoreMapStorage m_B4, m_C0, m_CC;
	int m_D8, m_DC, m_E0, m_E4, m_E8, m_EC, m_F0;
	int m_playerIndex;			// +0xF4
	bool m_F8;
};

typedef char ScoreKeeperSize[sizeof(LivingWorldScoreKeeper)==0xFC?1:-1];

#define LW_OBSERVERS(offset) ((Rva005A0B4CList *)((char *)TheLivingWorldLogic + (offset)))

LivingWorldScoreKeeper::LivingWorldScoreKeeper(int playerIndex, LivingWorldPlayer *player) :
	m_player(player), m_6C(0), m_startTime(time(0)), m_74(0), m_78(-1), m_7C(-1),
	m_94(0), m_98(0), m_A8(0), m_AC(0), m_B0(0),
	m_D8(0), m_DC(0), m_E0(0), m_E4(0), m_E8(0), m_EC(0), m_F0(0),
	m_playerIndex(playerIndex), m_F8(false)
{
	for (int i = 0; i < 5; ++i)
		m_80[i] = 0;
	LW_OBSERVERS(0x1C)->append((Rva002BA8F1Listener *)(LivingWorldPhaseObserver *)this);
	LW_OBSERVERS(0x2C)->append((Rva002BA8F1Listener *)(LivingWorldAutoResolveEventObserver *)this);
	LW_OBSERVERS(0x3C)->append((Rva002BA8F1Listener *)(LivingWorldRTSEventObserver *)this);
	LW_OBSERVERS(0x4C)->append((Rva002BA8F1Listener *)(LivingWorldLogicObserver *)this);
	((Rva005A0B4CList *)&g_00E04424)->append((Rva002BA8F1Listener *)(LivingWorldBuildingObserver *)this);
	((Rva005A0B4CList *)&g_00E02E88)->append((Rva002BA8F1Listener *)(LivingWorldRegionObserver *)this);
	((Rva005A0B4CList *)&g_00E044F0)->append((Rva002BA8F1Listener *)(LivingWorldBuildingNuggetSpawnArmyObserver *)this);
	((Rva005A0B4CList *)m_player)->append((Rva002BA8F1Listener *)(LivingWorldPlayerObserver *)this);
}

class Rva004EF2FAPrimary { public:void rva004EEE38(int); };
void LivingWorldScoreKeeper::event0_1(int phase,int ignored) { ((Rva004EF2FAPrimary*)this)->rva004EEE38(phase); }

class Rva004EE5D2 {public:void rva004EE78A();void rva004EE5D2();};
LivingWorldScoreKeeper::~LivingWorldScoreKeeper(){((Rva004EE5D2*)this)->rva004EE78A();}

class ModuleData;
struct Rva004EE79ESub {char pad[0x2c]; int m_2C;};
class Rva004E06FBPtrChase32Field {public:int get()const;char pad[0x20];int m_20;int pad24;Rva004EE79ESub *m_28;};
class LivingWorldBattle {public:bool rva003F486C(int);int rva003F4798(int,int);};
class LivingWorldLogic {public:char pad[0xfc];const ModuleData *m_FC;};
class BfmeSelectionState {public:bool isSelectionLocked()const;};
struct Rva004EF2ABArg {char pad[0x14];int m_14;};

void LivingWorldScoreKeeper::event1_3(const Rva004E06FBPtrChase32Field*a,int b) {
 if(a->m_20==-1)return;
 if(a->get()==m_playerIndex)++m_94;
 if(b==m_playerIndex)++m_98;
}
void LivingWorldScoreKeeper::event3_0(int,int) {if(m_startTime==0)return;int now=time(0);m_6C+=now-m_startTime;m_startTime=0;}
void LivingWorldScoreKeeper::event3_1(int unused,LivingWorldBattle*p) {
 m_startTime=time(0);if(!p->rva003F486C(m_playerIndex))return;
 int tmp38=*(int*)((char*)p+0x38);int v=p->rva003F4798(tmp38,m_playerIndex);if(v>=0)++m_D8;else ++m_DC;
}
void LivingWorldScoreKeeper::event4_0(int,int a,int b) {if(a!=b){if(a==m_playerIndex)m_EC++;else if(b==m_playerIndex)m_E8++;}}
void LivingWorldScoreKeeper::event1_0(Rva004E06FBPtrChase32Field*a) {
 if(a->get()!=m_playerIndex)return;Rva004EE79ESub*s=a->m_28;if(!s)return;
 if(s->m_2C==1) {const ModuleData*sel=TheLivingWorldLogic->m_FC;((_STL::vector<const ModuleData *>*)&m_4C)->push_back(sel);}
 ++m_80[s->m_2C];
}
void LivingWorldScoreKeeper::loadPostProcess() {
 if(TheLivingWorldLogic && ((BfmeSelectionState*)TheLivingWorldLogic)->isSelectionLocked()!=0)m_startTime=time(0);else m_startTime=0;
 if(m_F8!=0)return ((Rva004EE5D2*)this)->rva004EE5D2();
}
void LivingWorldScoreKeeper::event5_0(Rva004EF2ABArg*arg) {
 if(arg->m_14==m_playerIndex){if(m_startTime!=0){m_6C+=time(0)-m_startTime;m_startTime=0;}
 int turn=(int)TheLivingWorldLogic->m_FC;m_78=turn;
 ((Rva004EF2FAPrimary*)this)->rva004EEE38(turn);((Rva004EE5D2*)this)->rva004EE78A();}
}
void LivingWorldScoreKeeper::event6_1(LivingWorldLogic*logic) {
 ((Rva004EF2FAPrimary*)this)->rva004EEE38((int)logic->m_FC);
 if(m_startTime!=0){m_6C+=time(0)-m_startTime;m_startTime=0;}
}
struct Rva004EE260Base
{
	char m_pad[0x30];
	int m_id;
};

struct Rva004EE260B
{
	char m_pad[0xB4];
	int m_b4;
};

struct Rva004EE260C
{
	char m_pad[0x113];
	unsigned char m_113;
};

struct Rva004EE260Obj
{
	char m_pad0[8];
	Rva004EE260B *m_b;
	char m_pad1[0x2C - 0xC];
	Rva004EE260C *m_c;
	int m_idx;
};

struct Rva004EE260Pair
{
	Rva004EE260Obj *m_first;
	Rva004EE260Obj *m_second;
};

struct Rva004EE260Q
{
	Rva004EE260Base *m_base;
	char m_pad[0x3C - 4];
	Rva004EE260Pair *m_begin;
	Rva004EE260Pair *m_end;
};


void LivingWorldScoreKeeper::event2_2(int unused, LivingWorldBattle *p, void *qraw)
{
	(void)unused;
	if (p->rva003F486C(m_playerIndex)) {
		int tmp38 = *(int *)((char *)p + 0x38);
		int v = p->rva003F4798(tmp38, m_playerIndex);
		if (v == -1)
			++m_E4;
		else
			++m_E0;
	}
	Rva004EE260Q *q = (Rva004EE260Q *)qraw;
	Rva004EE260Pair *end = q->m_end;
	Rva004EE260Pair *begin = q->m_begin;
	if (begin == end)
		return;
	int id = m_playerIndex;
	for (; begin != end; ++begin) {
		Rva004EE260Obj *second = begin->m_second;
		int idx2 = second->m_idx;
		if (q->m_base[idx2].m_id == id) {
			Rva004EE260B *b = second->m_b;
			if (b->m_b4 != 0)
				++m_94;
			else {
				Rva004EE260C *c = second->m_c;
				if (c && (c->m_113 & 4))
					++m_AC;
				else
					++m_A8;
			}
		}
		else {
			Rva004EE260Obj *first = begin->m_first;
			int idx1 = first->m_idx;
			if (q->m_base[idx1].m_id == id) {
				Rva004EE260B *b = second->m_b;
				if (b->m_b4 != 0)
					++m_98;
				else
					++m_B0;
			}
		}
	}
}
class ThingTemplate;
struct TemplateCountKey {
 const ThingTemplate *pointer;
 __forceinline TemplateCountKey() {}
 __forceinline TemplateCountKey(const ThingTemplate *p):pointer(p) {}
 __forceinline bool operator<(const TemplateCountKey &other)const {return pointer<other.pointer;}
};
class SpawnArmy:public Snapshot {public:
 SpawnArmy(int);virtual ~SpawnArmy();
 virtual void loadPostProcess();virtual const char *GetSnapshotName()const;virtual void xfer(Xfer*);
 char payload[0x54];
};
class Rva00319CED {public:void *rva004E23C1();};
class Rva0040CB2CIndexedField {public:int get(int)const;};
class Rva0037DCA5 {public:void *rva0037DC52();};
class CountInputPrefix {public:virtual void *get();virtual void slot1();virtual void slot2();virtual void slot3();virtual bool fill(void*,SpawnArmy*);};
struct CountInputObjectPrefix {char prefix[4];Rva004E06FBPtrChase32Field *type;};
struct CountArrayEntry {int first;void *second;};
struct CountArrayPrefix {char prefix[0x40];CountArrayEntry *begin;CountArrayEntry *end;};
struct CountEntryPrefix {char prefix[0x90];int count;};
void LivingWorldScoreKeeper::event7_3(CountInputPrefix *input,void *arg) {
 CountInputObjectPrefix *object=(CountInputObjectPrefix*)input->get();
 if (!object || object->type->get()!=m_playerIndex) return;
 SpawnArmy temp(0);
 if (input->fill(arg,&temp)) {
  CountArrayPrefix *array=(CountArrayPrefix*)((Rva00319CED*)&temp)->rva004E23C1();
  if (array) {
   int i=array->end-array->begin-1;
   for(;i>=0;--i) {
    CountEntryPrefix *entry=(CountEntryPrefix*)((Rva0040CB2CIndexedField*)array)->get(i);
    TemplateCountKey key((const ThingTemplate *)((Rva0037DCA5*)entry)->rva0037DC52());
    ((_STL::map<TemplateCountKey,int>*)&m_9C)->insert(_STL::pair<const TemplateCountKey,int>(key,0)).first->second+=entry->count;
   }
  }
 }
}

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

extern "C" __declspec(dllimport) long __cdecl time(long *timer);


class ModuleData;
struct TemplateCountKey;

typedef _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > Rva004EED02List;
typedef _STL::vector<bool, _STL::allocator<bool> > Rva004EED02BoolList;
typedef _STL::map<TemplateCountKey, Int, _STL::less<TemplateCountKey>,
	_STL::allocator<_STL::pair<const TemplateCountKey, Int> > > Rva004EED02CountMap;

struct XferVersion
{
	UnsignedByte m_first;
	UnsignedByte m_version;
	UnsignedByte m_pad[2];
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading(); // +0x04
	virtual Bool isStoring(); // +0x08
	virtual Bool isCRC(); // +0x0C
	virtual void slot10(); virtual void slot14(); virtual void slot18();
	virtual void slot1C(); virtual void slot20(); virtual void slot24();
	virtual void xferVersion(XferVersion *version); // +0x28
	virtual void slot2C(); virtual void slot30(); virtual void slot34();
	virtual void slot38(); virtual void slot3C(); virtual void slot40();
	virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58();
	virtual void slot5C(); virtual void slot60(); virtual void slot64();
	virtual void slot68(); virtual void slot6C(); virtual void slot70();
	virtual void slot74();
	virtual void xferUnsignedInt(UnsignedInt *value); // +0x78
	virtual void xferInt(Int *value); // +0x7C
	virtual void slot80(); virtual void slot84(); virtual void slot88();
	virtual void slot8C();
	virtual void xferBool(Bool *value); // +0x90
};

class Xfer0051FFF5;
void Rva004EE9E9(Xfer0051FFF5 *xfer, void *data);
void Rva0040E269(Xfer0051FFF5 *xfer, void *data);
Xfer *Rva0060C253Xfer(Xfer *xfer, Rva004EED02BoolList *list);
void xferThingTemplateCountMap(Xfer *xfer, Rva004EED02CountMap *map);
void XferLivingWorldPlayerID(Xfer *xfer, Int *id);

void LivingWorldScoreKeeper::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_first = 1;
	version.m_version = 7;
	xfer->xferVersion(&version);
	if (xfer->isCRC())
		return;

	if (xfer->isStoring() && !xfer->isCRC())
	{
		const ModuleData *current = TheLivingWorldLogic->m_FC;
		((_STL::vector<const ModuleData *>*)&m_40)->push_back(current);
	}

	Rva004EE9E9((Xfer0051FFF5 *)xfer, &m_28);
	Rva0040E269((Xfer0051FFF5 *)xfer, &m_34);
	Rva0040E269((Xfer0051FFF5 *)xfer, &m_40);
	Rva0040E269((Xfer0051FFF5 *)xfer, &m_4C);
	Rva0060C253Xfer(xfer, &m_58);

	if (!xfer->isCRC())
	{
		if (xfer->isStoring() && m_startTime != 0)
		{
			UnsignedInt stamp = time(0) + (m_6C - m_startTime);
			xfer->xferUnsignedInt(&stamp);
		}
		else
		{
			xfer->xferUnsignedInt((UnsignedInt*)&m_6C);
		}
	}

	xfer->xferInt(&m_78);
	if (version.m_version >= 6)
		xfer->xferInt(&m_7C);
	for (Int i = 0; i < 5; ++i)
		xfer->xferInt(&m_80[i]);
	xfer->xferInt(&m_94);
	xfer->xferInt(&m_98);
	xferThingTemplateCountMap(xfer, (Rva004EED02CountMap*)&m_9C);
	xfer->xferInt(&m_A8);
	xfer->xferInt(&m_AC);
	xfer->xferInt(&m_B0);
	if (version.m_version >= 4)
	{
		xfer->xferInt(&m_E0);
		xfer->xferInt(&m_E4);
	}
	else
	{
		Int unused = 0;
		xfer->xferInt(&unused);
		m_E0 = 0;
		m_E4 = 0;
	}
	xfer->xferInt(&m_E8);
	xfer->xferInt(&m_EC);
	xfer->xferInt(&m_F0);
	if (version.m_version >= 3)
	{
		xfer->xferUnsignedInt((UnsignedInt*)&m_74);
		xferThingTemplateCountMap(xfer, (Rva004EED02CountMap*)&m_B4);
		xferThingTemplateCountMap(xfer, (Rva004EED02CountMap*)&m_C0);
		xferThingTemplateCountMap(xfer, (Rva004EED02CountMap*)&m_CC);
		xfer->xferInt(&m_D8);
		xfer->xferInt(&m_DC);
	}
	XferLivingWorldPlayerID(xfer, &m_playerIndex);
	if (version.m_version >= 7)
		xfer->xferBool(&m_F8);
	else
		m_F8 = false;
}

const char *LivingWorldScoreKeeper::GetSnapshotName()const{return "LivingWorldScoreKeeper";}

// Native ScoreKeeper cleanup 0x7929f9 is the complete 11-byte member+0x28
// destructor action of parent 0x4eeade; the whole parent and EH graph
// bind this lifetime action to the existing rowed 63-byte destructor 0x004EE501.

// Native ScoreKeeper cleanup 0x792b1a is the complete 11-byte member+0x28
// destructor action of parent 0x4eed02; the whole parent and EH graph
// bind this lifetime action to the existing rowed 63-byte destructor 0x004EE501.

// Native ScoreKeeper observer cleanup 0x792a7a is the complete 20-byte
// action $L9766 of the exact 310-byte destructor and its exception graph.
// Its adjusted observer lifetime is emitted by the existing real C++ bases.

// Native ScoreKeeper observer cleanup 0x792a8e is the complete 20-byte
// action $L9767 of the exact 310-byte destructor and its exception graph.
// Its adjusted observer lifetime is emitted by the existing real C++ bases.

// Native ScoreKeeper observer cleanup 0x792aa2 is the complete 20-byte
// action $L9768 of the exact 310-byte destructor and its exception graph.
// Its adjusted observer lifetime is emitted by the existing real C++ bases.

// Native ScoreKeeper observer cleanup 0x792ab6 is the complete 20-byte
// action $L9769 of the exact 310-byte destructor and its exception graph.
// Its adjusted observer lifetime is emitted by the existing real C++ bases.

// Native ScoreKeeper observer cleanup 0x792aca is the complete 20-byte
// action $L9770 of the exact 310-byte destructor and its exception graph.
// Its adjusted observer lifetime is emitted by the existing real C++ bases.

// Native ScoreKeeper observer cleanup 0x792ade is the complete 20-byte
// action $L9771 of the exact 310-byte destructor and its exception graph.
// Its adjusted observer lifetime is emitted by the existing real C++ bases.

// Native ScoreKeeper observer cleanup 0x792af2 is the complete 20-byte
// action $L9772 of the exact 310-byte destructor and its exception graph.
// Its adjusted observer lifetime is emitted by the existing real C++ bases.

// Native ScoreKeeper observer cleanup 0x792b06 is the complete 20-byte
// action $L9773 of the exact 310-byte destructor and its exception graph.
// Its adjusted observer lifetime is emitted by the existing real C++ bases.
