// cl: /O1 /G7 /arch:SSE /EHsc /MD
// Constructor 576DF1..576ED9 is 232 bytes, RET8, in the same 0x48-byte
// object allocated by the owned 576ED9 caller. Native table C6E430 and the
// derived C6E7F0 table both have translateGameMessage in slot0 and a deleting
// destructor in slot1. The carrier BDBA74 starts with purecall and a deleting
// destructor too; the old destructor-only slot0 declaration was incomplete.
// Only this translator prefix is represented here. The named phase's other
// slots and methods remain in StrategicInGameUIResolveBattlesBehavior.cpp.
// Member offsets and three-base lifetime are target facts. Owner+10 and
// values+14/+18 belong to the derived object; the +C listener occupies4B.
// The record at20 receives one saved owner->m_p receiver and the +4 base.
// Callee identities come from their existing matched providers; the owning
// phase is named by WB/vtable evidence but this retained destructor spelling
// is address-derived. No original member type identity is asserted.
// ??1Rva00576C4B@@UAE@XZ @0x00576C4B 186B: virtual dtor unregistering listener base at +0xC via rowed erase 0x002B7250 then conditional ptr-chase release then member teardown. Evidence: three vtable stores plus base restores 0x0086E7F0/0x0086E7E8/0x0086E7E4 to 0x007DBA74/0x0086E788; erase caller plus deleting-dtor caller at 0x00576DD5; callees all rowed.
enum GameMessageDisposition { KEEP_MESSAGE, DESTROY_MESSAGE };
class GameMessage;
class Rva002BA8F1Logic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};
class Rva002BA8F1Logic
{
public:
	char m_pad[0x5c];
	Rva002B7250 m_holder;
};

class Rva00328A83PtrChaseField
{
public:
	int get() const;
};
class Rva0042D6AEPtrChaseField
{
public:
	int get() const;
};
class VirtObj00576C4B
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
};
struct Inner00576C4B
{
	char m_pad[4];
	Rva00328A83PtrChaseField *m_p;
};
class Rva000AD6F4
{
public:
	Rva000AD6F4() : m_ptr(0) {}
	~Rva000AD6F4();
	void clear();
	void *m_ptr;
};
class Rva005CD1A9;
class Rva00574A98 { public: void *rva00574A98(); };
class Rva005CD7BD { public: Rva005CD7BD(void *,int,int); private: int native[4]; };

class Rva005CD7DA
{
public:
	__forceinline Rva005CD7DA(void *source,Rva005CD1A9 *owner) : data(((Rva00574A98*)source)->rva00574A98(),((Rva00328A83PtrChaseField*)source)->get(),(int)owner) {}
	void rva005CD7DA();
	Rva005CD7BD data;
};
// Native +1C/+40 cleanups call the complete29B owning-pointer destructor.
// Use its existing real member lifetime instead of an unbound forwarding wrapper.
typedef Rva000AD6F4 WrapClear00576C4B;
struct Wrap2000576C4B
{
	__forceinline Wrap2000576C4B(void *source,Rva005CD1A9 *owner) : m_m(source,owner) {}
	~Wrap2000576C4B() { m_m.rva005CD7DA(); }
	Rva005CD7DA m_m;
};
class Rva005CD651
{
public:
	Rva005CD651(int);
	virtual ~Rva005CD651();
	char m_pad[12];
};
class Rva005CD1A9
{
public:
	Rva005CD1A9();
	virtual ~Rva005CD1A9();
	void *m_ptr;
};
class Base0_00576C4B
{
public:
	Base0_00576C4B();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *) = 0;
	virtual ~Base0_00576C4B() {}
};
// ??0Base0_00576C4B@@QAE@XZ @0x001DB0AC 9B: the default constructor, storing the
// class's own vtable (VA 0x00BDBA74) and returning this.
Base0_00576C4B::Base0_00576C4B()
{
}
class PhaseTranslator00576DF1 : public Base0_00576C4B
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *);
};

class Listener00576C4B
{
public:
	Listener00576C4B();
	virtual ~Listener00576C4B() {}

};
// ??0Listener00576C4B@@QAE@XZ @0x00576674 9B: the default constructor, storing the
// class's own vtable (VA 0x00C6E788) and returning this.
Listener00576C4B::Listener00576C4B()
{
}
class Rva00576B5E;
class Rva005A0B4CList { public: void append(struct Rva002BA8F1Listener *); };
struct ResolveWorldView { char prefix[0x98]; int player; };
void Rva00576753Func(int,int,int);
namespace StrategicInGameUI { class ResolveBattlesBehavior { public: class Impl { public: void CreateResolveRegionOwnershipChecklistItems(); void rva00576AF3(); }; }; }

class Rva00576C4B : public PhaseTranslator00576DF1, public Rva005CD1A9, public Listener00576C4B
{
public:
	Rva00576C4B(Rva00576B5E *,int);
	virtual GameMessageDisposition translateGameMessage(const GameMessage *);
	virtual ~Rva00576C4B();
private:
	Inner00576C4B *m_s;
	int m_value14;
	int m_player18;
	WrapClear00576C4B m_1c;
	Wrap2000576C4B m_20;
	Rva005CD651 m_30;
	WrapClear00576C4B m_40;
	bool m_flag44;
};
Rva00576C4B::~Rva00576C4B()
{
	(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_holder.rva002B7250((CreateAHeroData *)(Listener00576C4B *)this);
	if (m_flag44) {
		int v1 = m_s->m_p->get();
		int v2 = ((Rva0042D6AEPtrChaseField *)v1)->get();
		if (v2)
			((VirtObj00576C4B *)v2)->f3();
	}
}

Rva00576C4B::Rva00576C4B(Rva00576B5E *owner, int value)
	: m_s((Inner00576C4B *)owner), m_value14(value),
	  m_player18(((ResolveWorldView *)TheLivingWorldLogic)->player),
	  m_20(m_s->m_p, this), m_30(m_s->m_p->get()), m_flag44(false)
{
	Rva00576753Func(m_player18, (int)(Rva005CD1A9 *)this, m_value14);
	((StrategicInGameUI::ResolveBattlesBehavior::Impl *)this)->CreateResolveRegionOwnershipChecklistItems();
	((Rva005A0B4CList *)((char *)TheLivingWorldLogic + 0x5C))
		->append((Rva002BA8F1Listener *)(Listener00576C4B *)this);
	((StrategicInGameUI::ResolveBattlesBehavior::Impl *)this)->rva00576AF3();
}
