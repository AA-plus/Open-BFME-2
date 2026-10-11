// FUN_008E119C
// partial score=0.92 date=2026-10-11
// cl: /ICode/Libraries/Include/Lib /Ireference/shims/moduledata /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?DoXfer@LivingWorldBuilding@@UAEXPAVXfer@@@Z retail 0x004E0E78..0x004E119C (804B)
// WorldBuilder 0x010D9A80 names LivingWorldBuilding::DoXfer in
// System/LivingWorld/LivingWorldBuilding.cpp (asserts 618..734) and the
// "LivingWorldBuildingNuggetBlock" block name. Retail vtable 0x00861610 slot 5
// holds this body (RET 4). Version 6: Coord2D +48 then int +1C then the
// version-gated +20 then the template name (lookup through the template store
// with the emergency backup fallback) then the nugget snapshots then the
// army summary entry holder +3C then the CRC-only building/region IDs then the
// version-6 bool +51. Xfer slots follow the native table 0x007BB910.
// Callee rows: Lookup 0x002B931C / getEmergencyBackupTemplateForBadLoads
// 0x004E0D4E / rva0052B17F pin 0x0052B17F / compare 0x000069D6 / nugget scan
// 0x004E0809 / holder release 0x004E0790 and set 0x004E08F6 / ArmySummaryEntry
// ctor 0x0040C351 / ID xfers 0x004E075F 0x003EFE82 / setter 0x004E060C.
#include "ascii_string.h"
// stlport
#include <vector>
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

class Coord2D;
class Snapshot;
class Xfer
{
public:
	virtual void slot00();
	virtual bool isLoading();
	virtual void slot02();
	virtual bool isCRC();
	virtual void slot04();
	virtual void beginBlock(const char *name);
	virtual void endBlock();
	virtual void skipBlock(const char *name);
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(void *version);
	virtual void slot11();
	virtual void xferSnapshot(void *snapshot);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void xferCoord2D(Coord2D *value);
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(AsciiString *value);
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void xferInt(int *value);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void xferBool(bool *value);
};

struct BuildingXferVersion
{
	unsigned char minimum;
	unsigned char current;
};

class Rva004E075FObj;
int Rva004E075FGet(Rva004E075FObj *o, int a);
struct Rva003EFE82Obj;
int __cdecl Rva003EFE82Get(struct Rva003EFE82Obj *obj, void *out);

struct Rva0059E647Entry;
struct Rva0059E647Factory
{
	Rva0059E647Entry *Lookup(int *);
};
class LivingWorldBuildingTemplate;
class LivingWorldBuildingTemplateStore
{
public:
	const LivingWorldBuildingTemplate *getEmergencyBackupTemplateForBadLoads();
};
class Rva0022C0CDSubsystem;
extern Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;

class Rva0052B17F
{
public:
	void rva0052B17F();
};

struct Rva004E0790Inner;
class ArmySummaryEntry
{
public:
	ArmySummaryEntry();
	char m_pad[0xC8];
};
class Rva004E0790
{
public:
	void rva004E0790();
	void rva004E08F6(Rva004E0790Inner *p);
	__forceinline Rva004E0790():m_ptr(0) {}
 ~Rva004E0790();
 Rva004E0790Inner *m_ptr;
};

struct BuildingNuggetTemplateView
{
	char m_pad00[4];
	AsciiString m_name;
};
struct BuildingNuggetView
{
	char m_pad00[8];
	BuildingNuggetTemplateView *m_template;
	BuildingNuggetTemplateView *getTemplate() const { return m_template; }
};
struct BuildingRegionView
{
	char m_pad00[0x12C];
	int m_id;
};

class Rva004E0809
{
public:
	void rva004E0809();
};
class Rva004E060C
{
public:
	void rva004E060C(unsigned char v);
};

class LivingWorldBuilding:public Snapshot,public Rva00330757Member,public CtorRegionTurnObserver
{
public:
	LivingWorldBuilding(BuildingRegionView *,const Coord2D &,const struct Rva003F1BD3TemplateView *,int);
 virtual ~LivingWorldBuilding();
 virtual void LoadPostProcess();
 virtual const char *GetSnapshotName();
 virtual void DoXfer(Xfer *xfer);
 void createIcon();

	
	int m_id;
	int m_1C;
	int m_20;
	BuildingRegionView *m_region;
	const AsciiString *m_template;
	Rva0052B17F *m_2C;
	_STL::vector<BuildingNuggetView *> m_nuggets;
	Rva004E0790 m_armyEntry;
	int word40,word44;
	Coord2D m_position;
	bool m_pad50;
	bool m_51;
};

void LivingWorldBuilding::DoXfer(Xfer *xfer)
{
	BuildingXferVersion version;
	version.minimum = 1;
	version.current = 6;
	xfer->xferVersion(&version);
	xfer->xferCoord2D(&m_position);
	xfer->xferInt(&m_1C);
	if (version.current == 4) {
		bool flag = false;
		xfer->xferBool(&flag);
		if (xfer->isLoading()) {
			if (flag)
				m_20 = -1;
			else
				m_20 = m_1C + 1;
		}
	} else if (version.current >= 5) {
		xfer->xferInt(&m_20);
	} else if (xfer->isLoading()) {
		m_20 = m_1C + 1;
	}

	if (xfer->isLoading()) {
		AsciiString templateName;
		xfer->xferAsciiString(&templateName);
		m_template = (const AsciiString *)((Rva0059E647Factory *)TheLivingWorldBuildingTemplateStore)->Lookup((int *)&templateName);
		if (m_template == 0)
			m_template = (const AsciiString *)((LivingWorldBuildingTemplateStore *)TheLivingWorldBuildingTemplateStore)->getEmergencyBackupTemplateForBadLoads();
		if (m_20 != -1 && m_2C != 0)
			m_2C->rva0052B17F();
		if (version.current >= 2) {
			int count;
			xfer->xferInt(&count);
			for (int i = 0; i < count; ++i) {
				AsciiString nuggetName;
				xfer->xferAsciiString(&nuggetName);
				BuildingNuggetView **it = m_nuggets.begin();
				BuildingNuggetView **end = m_nuggets.end();
				bool found = false;
				while (!found && it != end) {
					BuildingNuggetView *nugget = *it;
					if (nugget->getTemplate()->m_name.compare(nuggetName) == 0) {
						xfer->beginBlock("LivingWorldBuildingNuggetBlock");
						xfer->xferSnapshot(nugget);
						xfer->endBlock();
						found = true;
					} else {
						++it;
					}
				}
				if (!found)
					xfer->skipBlock("LivingWorldBuildingNuggetBlock");
			}
		}
		((Rva004E0809 *)this)->rva004E0809();
	} else {
		AsciiString templateName(*m_template);
		xfer->xferAsciiString(&templateName);
		int count = m_nuggets.end() - m_nuggets.begin();
		xfer->xferInt(&count);
		BuildingNuggetView **it = m_nuggets.begin();
		BuildingNuggetView **end = m_nuggets.end();
		while (it != end) {
			BuildingNuggetView *nugget = *it;
			AsciiString nuggetName(nugget->getTemplate()->m_name);
			xfer->xferAsciiString(&nuggetName);
			xfer->beginBlock("LivingWorldBuildingNuggetBlock");
			xfer->xferSnapshot(nugget);
			xfer->endBlock();
			++it;
		}
	}

	if (version.current >= 3) {
		bool hasArmyEntry = m_armyEntry.m_ptr != 0;
		xfer->xferBool(&hasArmyEntry);
		if (xfer->isLoading()) {
			m_armyEntry.rva004E0790();
			if (hasArmyEntry)
				m_armyEntry.rva004E08F6((Rva004E0790Inner *)new ArmySummaryEntry);
		}
		if (m_armyEntry.m_ptr)
			xfer->xferSnapshot(m_armyEntry.m_ptr);
	}

	if (xfer->isCRC()) {
		Rva004E075FGet((Rva004E075FObj *)xfer, (int)&m_id);
		if (m_region) {
			int regionId = m_region->m_id;
			Rva003EFE82Get((Rva003EFE82Obj *)xfer, &regionId);
		}
	}

	if (!xfer->isCRC() && version.current >= 6) {
		xfer->xferBool(&m_51);
		if (xfer->isLoading())
			((Rva004E060C *)this)->rva004E060C(m_51);
	}
}

struct Rva003F1BD3TemplateView {char opaque00[9];bool army;char pad0A[2];AsciiString armyType;};
struct Rva002BA8F1Listener;
class Rva005A0B4CList{public:void append(Rva002BA8F1Listener*);};
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class Rva002E00F9 {public:void rva002E00F9(void*,void*);};
LivingWorldBuilding::LivingWorldBuilding(BuildingRegionView *region,const Coord2D &position,const Rva003F1BD3TemplateView *definition,int id)
 :m_id(id),m_1C(-1),m_20(-1),m_region(region),m_template((const AsciiString*)definition),m_2C(0),m_nuggets(_STL::allocator<BuildingNuggetView*>()),word40(0),word44(0),m_position(position),m_pad50(false),m_51(false)
{
 createIcon();
 ((Rva002E00F9*)m_template)->rva002E00F9(this,&m_nuggets);
 const Rva003F1BD3TemplateView *d=(const Rva003F1BD3TemplateView*)m_template;
 if(d->army && !((const StringBase<char>*)&d->armyType)->isEmpty()) {
  m_armyEntry.rva004E08F6((Rva004E0790Inner*)new ArmySummaryEntry);
  ((StringBase<char>*)((char*)m_armyEntry.m_ptr+4))->set(*(const StringBase<char>*)&((const Rva003F1BD3TemplateView*)m_template)->armyType);
  *(int*)((char*)m_armyEntry.m_ptr+0xB4)=m_id;
 }
 ((Rva004E0809*)this)->rva004E0809();
 ((Rva005A0B4CList*)((char*)TheLivingWorldLogic+0x1C))->append((Rva002BA8F1Listener*)(CtorRegionTurnObserver*)this);
}
