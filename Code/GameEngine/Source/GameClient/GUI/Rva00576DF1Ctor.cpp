// cl: /O1 /MD /EHsc /DNDEBUG
// ??0Rva00576DF1@@QAE@PAVRva00576B5E@@H@Z, retail 0x00576DF1..0x00576ED9
// (232 bytes, EH, ret 8): the constructor of StrategicInGameUI::
// ResolveBattlesBehavior's 0x48-byte Impl (pinned under its address name;
// its body calls the rowed Impl members CreateResolveRegionOwnershipChecklist-
// Items 0x00576BDD and 0x00576AF3). The resolve-battles sibling of
// Rva0057621ACtor.cpp and Rva005776A7Ctor.cpp. Bases, each table read from
// retail and each unwind target from the EH funclets 0x0079B579..0x0079B5BE:
//   +0x00 the phase interface (0x00C6E430; unwind carrier 0x00429191),
//   +0x04 the rowed Rva005CD1A9 base (ctor 0x005CD167),
//   +0x0C the listener base (0x00C6E788; unwind 0x00576456), appended to
//         TheLivingWorldLogic's +0x5C list.
// Own tables 0x00C6E7F0/+4 0x00C6E7E8/+C 0x00C6E7E4. Members: +0x10 owner,
// +0x14 the int argument, +0x18 TheLivingWorldLogic's +0x98 word, +0x1C and
// +0x40 owning pointers (unwind 0x000AD6F4), +0x20 the record built from the
// owner's +4 object and the +4 base, +0x30 the rowed Rva005CD651 from that
// object, +0x44 a flag cleared before the rowed setup call 0x00576753.
// Identities beyond these addresses are not established.
class Gen_uwm_00429191
{
public:
	virtual void s0();
	~Gen_uwm_00429191() {}
};

class Rva005776A7Interface : public Gen_uwm_00429191
{
public:
	virtual void r0();
};



class Rva005CD1A9
{
public:
	Rva005CD1A9();
	virtual ~Rva005CD1A9();
private:
	int m_04;
};



struct Rva005772BFTarget;

class Rva00576B5E
{
public:
	virtual ~Rva00576B5E();
	Rva005772BFTarget *m_04;			// +0x04
};

class Rva00328A83PtrChaseField
{
public:
	int get() const;
};

class Rva00574A98
{
public:
	void *rva00574A98();
};


class Rva000AD6F4
{
public:
	Rva000AD6F4() : m_ptr(0) {}
	~Rva000AD6F4();
private:
	void *m_ptr;
};

class Rva005CD7BD
{
public:
	Rva005CD7BD(void *source, int value, int owner);
	~Rva005CD7BD();
private:
	unsigned char m_data[0x10];
};

class Rva005CD651
{
public:
	Rva005CD651(int value);
	virtual ~Rva005CD651();
private:
	unsigned char m_pad04[0x10 - 4];
};

// The +0x30 record built from the owner's +4 object (read once).
class Rva005CD7BDHolder : public Rva005CD7BD
{
public:
	__forceinline Rva005CD7BDHolder(Rva005772BFTarget *source, Rva005CD1A9 *owner)
		: Rva005CD7BD(((Rva00574A98 *)source)->rva00574A98(), ((const Rva00328A83PtrChaseField *)source)->get(), (int)owner) {}
	~Rva005CD7BDHolder() {}
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva00576DF1LogicView
{
public:
	unsigned char m_pad00[0x5C];
	unsigned char m_list5C[0x98 - 0x5C];		// +0x5C
	int m_98;					// +0x98
};

struct Rva002BA8F1Listener;

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

class Rva00576456Listener
{
public:
	virtual void vslot0();
	~Rva00576456Listener();
};

void Rva00576753Func(int a, int b, int c);

class StrategicInGameUI
{
public:
	class ResolveBattlesBehavior
	{
	public:
		class Impl
		{
		public:
			void CreateResolveRegionOwnershipChecklistItems();
			void rva00576AF3();
		};
	};
};

class Rva00576DF1 : public Rva005776A7Interface, public Rva005CD1A9, public Rva00576456Listener
{
public:
	Rva00576DF1(Rva00576B5E *owner, int value);
	virtual ~Rva00576DF1();
	virtual void r0();
	virtual void vslot0();
private:
	Rva00576B5E *m_owner;				// +0x10
	int m_value;					// +0x14
	int m_18;					// +0x18
	Rva000AD6F4 m_1C;				// +0x1C
	Rva005CD7BDHolder m_20;				// +0x20
	Rva005CD651 m_30;				// +0x30
	Rva000AD6F4 m_40;				// +0x40
	bool m_44;					// +0x44
};

Rva00576DF1::Rva00576DF1(Rva00576B5E *owner, int value)
	: m_owner(owner), m_value(value),
	  m_18(((Rva00576DF1LogicView *)TheLivingWorldLogic)->m_98),
	  m_20(m_owner->m_04, this),
	  m_30(((const Rva00328A83PtrChaseField *)m_owner->m_04)->get())
{
	m_44 = false;
	Rva00576753Func(m_18, (int)static_cast<Rva005CD1A9 *>(this), m_value);
	((StrategicInGameUI::ResolveBattlesBehavior::Impl *)this)->CreateResolveRegionOwnershipChecklistItems();
	((Rva005A0B4CList *)((Rva00576DF1LogicView *)TheLivingWorldLogic)->m_list5C)
		->append((Rva002BA8F1Listener *)static_cast<Rva00576456Listener *>(this));
	((StrategicInGameUI::ResolveBattlesBehavior::Impl *)this)->rva00576AF3();
}
