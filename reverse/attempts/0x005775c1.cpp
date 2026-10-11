// ?rva005775C1@Rva005775C1@@UAEXURva005775C1Key@@@Z
// partial score=0.9 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// Two 115-byte twins that keep one current 0x1C-byte record in an owner's
// +0x14 slot: if the current record's +0x0C key already equals the argument
// it is refreshed (rowed 0x00576FBA); otherwise the slot is cleared (rowed
// 0x0057702E) and a new record for (owner, key) is constructed (unrowed
// 0x005774E3, pinned by address) and installed (rowed 0x0057704C).
// ?rva005775C1@Rva005775C1@@UAEXH@Z, retail 0x005775C1: slot 15 of table
// 0x0086E8A8, owner pointer at +0x08.
// ?rva00577634@Rva00577634@@UAEXH@Z, retail 0x00577634: the same body with
// the owner pointer at +0x18.
// Address-derived names; the views emit no vtables.
struct Rva005775C1Key
{
	int m_value;
	bool operator==(const Rva005775C1Key &that) const { return m_value == that.m_value; }
};

struct Rva0057702EBase
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void *f4(int);
};

class Rva005774E3 : public Rva0057702EBase
{
public:
	Rva005774E3(void *owner, Rva005775C1Key key);
	unsigned char m_pad04[0x0C - 0x04];
	Rva005775C1Key m_key;		// +0x0C
	unsigned char m_pad10[0x1C - 0x10];
};

class Rva00576FBA { public: void rva00576FBA(); };
class Rva0057702E { public: void rva0057702E(); };
class Rva0057704C { public: void rva0057704C(Rva0057702EBase *n); };

struct Rva005775C1Slot
{
	Rva005774E3 *m_current;
};
struct Rva005775C1Owner
{
	unsigned char m_pad00[0x14];
	Rva005775C1Slot m_slot;	// +0x14
};

class Rva005775C1
{
public:
	virtual void rva005775C1(Rva005775C1Key key);
private:
	unsigned char m_pad04[0x08 - 0x04];
	Rva005775C1Owner *m_owner;	// +0x08
};

class Rva00577634
{
public:
	virtual void rva00577634(Rva005775C1Key key);
private:
	unsigned char m_pad04[0x18 - 0x04];
	Rva005775C1Owner *m_owner;	// +0x18
};

void Rva005775C1::rva005775C1(Rva005775C1Key key)
{
	Rva005775C1Slot *slot = &m_owner->m_slot;
	Rva005774E3 *current = slot->m_current;
	if (current && current->m_key == key)
	{
		((Rva00576FBA *)current)->rva00576FBA();
		return;
	}
	((Rva0057702E *)slot)->rva0057702E();
	((Rva0057704C *)&m_owner->m_slot)->rva0057704C(new Rva005774E3(m_owner, key));
}

void Rva00577634::rva00577634(Rva005775C1Key key)
{
	Rva005775C1Slot *slot = &m_owner->m_slot;
	Rva005774E3 *current = slot->m_current;
	if (current && current->m_key == key)
	{
		((Rva00576FBA *)current)->rva00576FBA();
		return;
	}
	((Rva0057702E *)slot)->rva0057702E();
	((Rva0057704C *)&m_owner->m_slot)->rva0057704C(new Rva005774E3(m_owner, key));
}
