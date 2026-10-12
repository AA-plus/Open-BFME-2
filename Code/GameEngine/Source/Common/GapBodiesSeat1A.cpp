// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no ledger row covered (each begins
// after its neighbour's padding or return and ends in its own ret). Retail
// bytes establish every shape below; the owning classes are not recovered, so
// each keeps an address-derived name and a view of only the members it
// touches. Callees are the ledger's existing rows under their current
// spellings.
#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class GlobalData;
extern GlobalData *TheWritableGlobalData;

// --- 0x00203582 (19B): adds the argument to the float at +0x48.
class Rva00203582
{
public:
	void rva00203582(float delta);
private:
	char m_pad00[0x48];
	float m_48;
};

void Rva00203582::rva00203582(float delta)
{
	m_48 += delta;
}

// --- 0x00203671 (23B): stores a non-negative argument into
// TheWritableGlobalData's word at +0xAC8; the receiver is unused.
struct Rva00203671GlobalDataView
{
	char m_pad000[0xAC8];
	int m_AC8;
};

class Rva00203671
{
public:
	void rva00203671(int value);
};

void Rva00203671::rva00203671(int value)
{
	if (value >= 0)
		((Rva00203671GlobalDataView *)TheWritableGlobalData)->m_AC8 = value;
}

// --- 0x00203E65 (17B): 1 when TheGameLogic->rva001DCD1C() is false, else 0
// (sibling of the rowed 0x00203688/0x00203693 wrappers).
class Rva00203E65
{
public:
	int rva00203E65();
};

int Rva00203E65::rva00203E65()
{
	return !TheGameLogic->rva001DCD1C();
}

// --- 0x00205A1B (16B): returns by value a pair {0, &this[+0x0C]}.
struct Rva00205A1BPair
{
	Rva00205A1BPair(void *p) : m_00(0), m_04(p) {}
	int m_00;
	void *m_04;
};

class Rva00205A1B
{
public:
	Rva00205A1BPair rva00205A1B();
private:
	char m_pad00[0x0C];
	int m_0C;
};

Rva00205A1BPair Rva00205A1B::rva00205A1B()
{
	return Rva00205A1BPair(&m_0C);
}

// --- 0x00210EAC (19B): returns a zero float pair by value; both word
// arguments and the receiver are unused.
struct Rva00210EACCoord2D
{
	Rva00210EACCoord2D(float ax, float ay) : x(ax), y(ay) {}
	float x;
	float y;
};

class Rva00210EAC
{
public:
	Rva00210EACCoord2D rva00210EAC(int a, int b);
};

Rva00210EACCoord2D Rva00210EAC::rva00210EAC(int, int)
{
	return Rva00210EACCoord2D(0.0f, 0.0f);
}

// --- 0x00215E5F (16B): 1 when the argument's first word equals this one's.
class Rva00215E5F
{
public:
	int rva00215E5F(const Rva00215E5F *other);
private:
	int m_00;
};

int Rva00215E5F::rva00215E5F(const Rva00215E5F *other)
{
	return other->m_00 == m_00;
}

// --- 0x00215E87 (18B): the index of the first null of two slots, else 2.
class Rva00215E87
{
public:
	unsigned int rva00215E87();
private:
	void *m_slots[2];
};

unsigned int Rva00215E87::rva00215E87()
{
	unsigned int i;
	for (i = 0; i < 2; ++i)
	{
		if (m_slots[i] == 0)
			return i;
	}
	return 2;
}

// --- 0x0021917A (18B): cdecl equality of two pointed-to words.
int Rva0021917A(const int *a, const int *b)
{
	return *b == *a;
}

// --- 0x0021982A (16B): the halfword at +4 of the node the first word points
// at, or 0 without a node.
struct Rva0021982ANode
{
	int m_00;
	unsigned short m_04;
};

class Rva0021982A
{
public:
	int rva0021982A();
private:
	Rva0021982ANode **m_node;
};

int Rva0021982A::rva0021982A()
{
	Rva0021982ANode *node = *m_node;
	if (node)
		return node->m_04;
	return 0;
}
