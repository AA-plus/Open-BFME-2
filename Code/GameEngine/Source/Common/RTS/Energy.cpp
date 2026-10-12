// cl: /O1
// RTS/Energy.cpp: the two power-bonus dispatchers retail links from this TU
// (tu_map approved), folded from two split units with these exact flags. They
// share the rowed power-add callee views.
// ?objectEnteringInfluence@Energy@@QAEXPAVObject@@@Z @ 0x004DF207 (42B)
// WorldBuilder names 0x004DF207/0x004DF231 Energy::objectEnteringInfluence and
// objectLeavingInfluence (Energy.cpp:105/131), the ZH pair: the Object's
// template energy (+4 -> +0x548) goes to consumption when negative and to
// production when positive, with the signs flipped on leaving.
// Dispatches signed value at [arg+4]+0x548 to rowed power adds (mirror of twin 0x004DF231).
// Retail negs before 0x004DF1AF (v<0 -> -v) and passes v straight to 0x004DF18D (v>0).
// Evidence: caller 0x0028D9D5 in 0x0028D99A (same as twin); callee rows 0x004DF1AF 0x004DF18D;
// twin Code/GameEngine/Source/Common/Rva004DF231Power.cpp // cl: /O1 reused.
class Rva004DF1AF
{
public:
	void rva004DF1AF(int delta);
};

class Rva004DF18D
{
public:
	void rva004DF18D(int delta);
};

struct Rva004DF207Inner
{
	char m_pad[0x548];
	int m_val;
	int m_54C;
};

struct Rva004DF207Outer
{
	char m_pad[4];
	Rva004DF207Inner *m_ptr;
};

class Object;

class Energy
{
public:
	void objectEnteringInfluence(Object *obj);
	void objectLeavingInfluence(Object *obj);
	void rva004DF25B(Rva004DF207Outer *arg);
	void rva004DF274(Rva004DF207Outer *arg);
};

void Energy::objectEnteringInfluence(Object *obj)
{
	if (!obj)
		return;
	Rva004DF207Outer *o = (Rva004DF207Outer *)obj;
	int v = o->m_ptr->m_val;
	if (v < 0)
		((Rva004DF1AF *)this)->rva004DF1AF(-v);
	else if (v > 0)
		((Rva004DF18D *)this)->rva004DF18D(v);
}

// ?objectLeavingInfluence@Energy@@QAEXPAVObject@@@Z RVA 0x004DF231 size 42
// Dispatches signed value at [arg+4]+0x548 to rowed power adds.
// Evidence: caller 0x0028D99A passes Object in stack and Player+0x1bc in ecx;
// callee rows 0x004DF1AF 0x004DF18D; twin 0x004DF207.
struct Rva004DF231Inner
{
	char m_pad[0x548];
	int m_val;
};

struct Rva004DF231Outer
{
	char m_pad[4];
	Rva004DF231Inner *m_ptr;
};

void Energy::objectLeavingInfluence(Object *obj)
{
	if (!obj)
		return;
	Rva004DF231Outer *o = (Rva004DF231Outer *)obj;
	int v = o->m_ptr->m_val;
	if (v < 0)
		((Rva004DF1AF *)this)->rva004DF1AF(v);
	else if (v > 0)
		((Rva004DF18D *)this)->rva004DF18D(-v);
}

// ?rva004DF25B@Energy@@QAEXPAURva004DF207Outer@@@Z @ 0x004DF25B (25B)
void Energy::rva004DF25B(Rva004DF207Outer *arg)
{
	if (arg)
		((Rva004DF18D *)this)->rva004DF18D(arg->m_ptr->m_54C);
}

// ?rva004DF274@Energy@@QAEXPAURva004DF207Outer@@@Z @ 0x004DF274 (28B)
void Energy::rva004DF274(Rva004DF207Outer *arg)
{
	if (arg)
		((Rva004DF18D *)this)->rva004DF18D(-arg->m_ptr->m_54C);
}

