// ??0Rva005FAD8D@@QAE@PAX0@Z
// partial score=0.97 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common
#include "string_base.h"
#include "BattlePromptCallbackPayloadView.h"
// ??1Rva005FAD8D@@QAE@XZ, retail 0x005FAD8D, 98 bytes.
// Non-virtual dtor (QAE) with derived vptr 0x00879ED4 then base vptr 0x00875284,
// erase via rowed 0x002B7250 through +4->+0x14->+8, conditional virtual calls
// on +0x10 slot4 and +0x0C slot9 when +0x14 != 0, implicit member dtor
// rowed 0x005F23B2 at +0x18, inline empty base for second vptr + EH state 1.
// Evidence: callees rowed 0x002B7250 0x005F23B2; callers 0x005FAF44 0x005FAFBE.
// Retail vptr loads (Capstone over game.dat at 0x005FAD8D): C7 06 D4 9E C7 00
// installs derived VA 0x00C79ED4 at [esi]; C7 06 84 52 C7 00 restores base VA
// 0x00C75284 at [esi]. True CreateAHeroData vtable is VA 0x00C38D88 (RVA
// 0x838D88 slot2 = 0x809353 typeName "CreateAHeroData" at 0x409353; copy/dtor
// rowed); VA 0x00C75284 holds code pointers (slot0 0x0087A69C), no hero string.
// The base installs vftable 0x00875284 (VA 0x00C75284). CreateAHeroData's own is
// 0x00838D88 (VA 0x00C38D88), so the base is named after its vtable; spelling
// it CreateAHeroData gave that vtable symbol two addresses (full-gate DIR32
// consistency C38D88 vs C75284 in CI 37307445275, same pattern as the C6E330
// fix in Rva005CD651Dtor). The erase callee keeps its rowed CreateAHeroData
// pointer parameter through a cast.
class CreateAHeroData;
class Rva00875284Base
{
public:
	virtual void f0();
	virtual void f1();
	~Rva00875284Base() {}
};

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

struct Rva005FAD8DOuter
{
	char m_pad[8];
	Rva002B7250 m_w08;
};

struct Rva005FAD8DMid
{
	char m_pad[0x14];
	Rva005FAD8DOuter *m_14;
};

class Rva005FAD8DV10
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
};

class Rva005FAD8DV0C
{
public:
	virtual void t0();
	virtual void t1();
	virtual void t2();
	virtual void t3();
	virtual void t4();
	virtual void t5();
	virtual void t6();
	virtual void t7();
	virtual void t8();
	virtual void t9();
};

class Rva005F2381 { public: Rva005F2381(); private: char storage[0x1C]; };
class Rva005F23B2 : public Rva005F2381
{
public:
	~Rva005F23B2();
};

// The native constructor 005FAFE8 passes 005FA892 to the owned plain
// vector constructor iterator (00001423) with count 3 and stride 8 at +34.
// This 10-byte callback ends at RET 005FA89B, immediately before the owned
// panel constructor 005FA89C. It initializes both integer slots to -1.
// Later accesses in 005FAFE8 put an army index in slot 0 and its panel index
// in slot 1. The original element identity is unknown.
struct Rva005FA892Pair
{
	Rva005FA892Pair();
	int m_armyIndex;
	int m_panelIndex;
};

Rva005FA892Pair::Rva005FA892Pair() : m_armyIndex(-1), m_panelIndex(-1)
{
}

class Rva003F4DCA { public: int rva003F4DCA(int,int); };
class LivingWorldBattle { public: int rva003F48FE(int,int,int); };
class Rva005FFED5 { public: void rva005FFED5(int); };
class Rva005FFEDD { public: void rva005FFEDD(const TreeHintRef00217D4C &); };
class Rva005FFEE5 { public: int rva005FFEE5(const TreeHintRef00217D4C &); };
class Rva00600052 { public: void rva00600052(int,bool); };
class Rva0060005A { public: void rva0060005A(int,bool); };
class Rva005A0B4CList { public: void append(struct Rva002BA8F1Listener *); };
class Rva005FAAA1 { public: struct Payload { int v[2]; }; };
RvaCloneResult<Rva005FAAA1> Rva005FAC2BCreate(const Rva005FAAA1::Payload *);
struct BattleOwnerSource { char prefix[0xC]; int wordC; Rva005FAD8DV0C *word10; Rva005FAD8DV10 *word14; };
struct BattleOwnerLayout { char prefix[0x14]; void *battle14; int side18; int army1C; };
struct BattleArmyEntry { char prefix[0x18]; StringBase<char> name18; };

class Rva005FAD8D : public Rva00875284Base
{
public:
	Rva005FAD8D(void *,void *);
	~Rva005FAD8D();
private:
	Rva005FAD8DMid *m_04;
	int m_08;
	Rva005FAD8DV0C *m_0C;
	Rva005FAD8DV10 *m_10;
	int m_flag14;
	Rva005F23B2 m_18;
	Rva005FA892Pair m_entries34[3];
	int m_count4C;
	int m_selected50;
};

Rva005FAD8D::~Rva005FAD8D()
{
	Rva005FAD8DOuter *outer = m_04->m_14;
	outer->m_w08.rva002B7250((CreateAHeroData *)this);
	if (m_flag14 != 0) {
		m_10->s4();
		m_0C->t9();
	}
}

Rva005FAD8D::Rva005FAD8D(void *owner,void *source)
 :m_04((Rva005FAD8DMid*)owner),m_08(((BattleOwnerSource*)source)->wordC),
 m_0C(((BattleOwnerSource*)source)->word10),m_10(((BattleOwnerSource*)source)->word14),
 m_flag14(0),m_count4C(0),m_selected50(-1)
{
 void *clip=(char*)m_04+8;
 ((Rva005FFED5*)clip)->rva005FFED5(0);
 BattleOwnerLayout *layout=(BattleOwnerLayout*)m_04;
 void *battle=layout->battle14;
 int side=layout->side18, army=layout->army1C;
 int count=((Rva003F4DCA*)battle)->rva003F4DCA(side,army);
 if(count>0) {
 Rva005FAAA1::Payload payload;
 payload.v[1]=(int)this;
 for(int index=0;index<count;++index) {
  BattleArmyEntry *entry=(BattleArmyEntry*)((LivingWorldBattle*)battle)->rva003F48FE(side,army,index);
  payload.v[0]=(int)entry;
  RvaCloneResult<Rva005FAAA1> result=Rva005FAC2BCreate(&payload);
  if (!entry->name18.isEmpty()) {
   Rva005FA892Pair &item=m_entries34[m_count4C++];
   item.m_armyIndex=index;
   item.m_panelIndex=((Rva005FFEE5*)clip)->rva005FFEE5(result);
  } else ((Rva005FFEDD*)clip)->rva005FFEDD(result);
 }
 }
 for(int button=0;button<2;++button) {
  ((Rva00600052*)clip)->rva00600052(button,m_count4C>=button+2);
  ((Rva0060005A*)clip)->rva0060005A(button,m_count4C>=button+2);
 }
 ((Rva005A0B4CList*)((char*)battle+8))->append((Rva002BA8F1Listener*)this);
}
