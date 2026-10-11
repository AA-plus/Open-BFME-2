// cl: /O1 /DNDEBUG /MD
//
// Field-pointer virtual forwarders: each loads an object pointer from a fixed
// field of its own object and tail-jumps one of that object's virtual slots
// (mov ecx, [ecx+<field>]; mov eax, [ecx]; jmp [eax+4*slot]). The tail jump
// hands any stack arguments and the return value through unchanged, so the
// real parameter lists and return types are not recoverable from these bodies;
// each is declared void() over a slot-only target view. Owners and targets
// are unknown; names are address-derived and no referencing site was found
// for these in this pass.
class Rva0001BC90SlotTarget
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
};

// 0x0001BC90: [this+0x40] -> slot 8
class Rva0001BC90Owner
{
public:
	void rva0001BC90();
private:
	char m_pad00[0x40];
	Rva0001BC90SlotTarget *m_target;
};
void Rva0001BC90Owner::rva0001BC90()
{
	m_target->slot08();
}

// 0x0009076A: [this+0x2C] -> slot 0
class Rva0009076AOwner
{
public:
	void rva0009076A();
private:
	char m_pad00[0x2C];
	Rva0001BC90SlotTarget *m_target;
};
void Rva0009076AOwner::rva0009076A()
{
	m_target->slot00();
}

// 0x001F352B: [this+0xA4] -> slot 7
class Rva001F352BOwner
{
public:
	void rva001F352B();
private:
	char m_pad00[0xA4];
	Rva0001BC90SlotTarget *m_target;
};
void Rva001F352BOwner::rva001F352B()
{
	m_target->slot07();
}

// 0x003F3F97: [this+0x0] -> slot 0
class Rva003F3F97Owner
{
public:
	void rva003F3F97();
private:
	Rva0001BC90SlotTarget *m_target;
};
void Rva003F3F97Owner::rva003F3F97()
{
	m_target->slot00();
}

// 0x0043DA95: [this+0x58] -> slot 21
class Rva0043DA95Owner
{
public:
	void rva0043DA95();
private:
	char m_pad00[0x58];
	Rva0001BC90SlotTarget *m_target;
};
void Rva0043DA95Owner::rva0043DA95()
{
	m_target->slot21();
}

// 0x004A9914: [this+0x4C8] -> slot 6
class Rva004A9914Owner
{
public:
	void rva004A9914();
private:
	char m_pad00[0x4C8];
	Rva0001BC90SlotTarget *m_target;
};
void Rva004A9914Owner::rva004A9914()
{
	m_target->slot06();
}

// 0x004E56B0: [this+0x0] -> slot 4
class Rva004E56B0Owner
{
public:
	void rva004E56B0();
private:
	Rva0001BC90SlotTarget *m_target;
};
void Rva004E56B0Owner::rva004E56B0()
{
	m_target->slot04();
}

// 0x005C1A85: [this+0x2C] -> slot 2
class Rva005C1A85Owner
{
public:
	void rva005C1A85();
private:
	char m_pad00[0x2C];
	Rva0001BC90SlotTarget *m_target;
};
void Rva005C1A85Owner::rva005C1A85()
{
	m_target->slot02();
}

// 0x005D0081: [this+0x1C] -> slot 1
class Rva005D0081Owner
{
public:
	void rva005D0081();
private:
	char m_pad00[0x1C];
	Rva0001BC90SlotTarget *m_target;
};
void Rva005D0081Owner::rva005D0081()
{
	m_target->slot01();
}

// 0x005E18C9: [this+0x0] -> slot 6
class Rva005E18C9Owner
{
public:
	void rva005E18C9();
private:
	Rva0001BC90SlotTarget *m_target;
};
void Rva005E18C9Owner::rva005E18C9()
{
	m_target->slot06();
}

// 0x005E2178: [this+0x8] -> slot 7
class Rva005E2178Owner
{
public:
	void rva005E2178();
private:
	char m_pad00[0x8];
	Rva0001BC90SlotTarget *m_target;
};
void Rva005E2178Owner::rva005E2178()
{
	m_target->slot07();
}

// Self-virtual forwarders: a member that only calls another virtual slot of
// its own object (mov eax, [ecx]; jmp [eax+4*slot]); same caveats as above.
// 0x000B3779 is referenced by three vtables; 0x00481832 by one.
class Rva000B3779SlotSelf
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
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
	void rva000B3779();
	void rva00481832();
	void rva006C1670();
};

// 0x000B3779: own slot 25
void Rva000B3779SlotSelf::rva000B3779()
{
	slot25();
}

// 0x00481832: own slot 13
void Rva000B3779SlotSelf::rva00481832()
{
	slot13();
}

// 0x006C1670: own slot 9
void Rva000B3779SlotSelf::rva006C1670()
{
	slot09();
}
