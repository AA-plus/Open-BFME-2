// cl: /O1 /G7 /arch:SSE /GX- /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no ledger row covered (each begins
// after its neighbour's padding or return and ends in its own ret). Retail
// bytes establish every shape below; the owning classes are not recovered, so
// each keeps an address-derived name and a view of only the members it
// touches. Callees are the ledger's existing rows under their current
// spellings.
#include "GameLogicObjectLookupView.h"
#include "ascii_string.h"

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

// --- 0x002224DE (32B): false past the fourteenth 0x28-byte record at +0xF0,
// else the inverse of that record's second flag bit.
struct Rva002224DERecord
{
	unsigned char m_flag0 : 1;
	unsigned char m_flag1 : 1;
	char m_pad01[0x27];
};

class Rva002224DE
{
public:
	bool rva002224DE(unsigned int index);
private:
	char m_pad00[0xF0];
	Rva002224DERecord m_records[14];
};

bool Rva002224DE::rva002224DE(unsigned int index)
{
	if (index >= 14)
		return false;
	return !m_records[index].m_flag1;
}

// --- 0x002226A2 (28B): constructor from a flag and an eight-byte pair.
struct Rva002226A2Pair
{
	int m_00;
	int m_04;
};

class Rva002226A2
{
public:
	Rva002226A2(const bool &flag, const Rva002226A2Pair &pair);
private:
	bool m_00;
	Rva002226A2Pair m_04;
};

Rva002226A2::Rva002226A2(const bool &flag, const Rva002226A2Pair &pair) : m_00(flag), m_04(pair)
{
}

// --- 0x00225A81 (18B): copies an eight-byte pair to +0x38.
class Rva00225A81
{
public:
	void rva00225A81(const Rva002226A2Pair &pair);
private:
	char m_pad00[0x38];
	Rva002226A2Pair m_38;
};

void Rva00225A81::rva00225A81(const Rva002226A2Pair &pair)
{
	m_38 = pair;
}

// --- 0x0022CF6E, 0x0022CF9F (18B each): the rowed timing hooks applied to
// the argument twice, as the rowed 0x0022D189 setter calls the first.
int Rva0022CB5CHook(int a, int b);
int Rva0022CC0EHook(int a, int b);

class Rva0022CF6E
{
public:
	int rva0022CF6E(int value);
	int rva0022CF9F(int value);
};

int Rva0022CF6E::rva0022CF6E(int value)
{
	return Rva0022CB5CHook(value, value);
}

int Rva0022CF6E::rva0022CF9F(int value)
{
	return Rva0022CC0EHook(value, value);
}

// --- 0x0022D979 (20B): sets the timing value from the pointed word through
// the rowed 0x0022D189 setter and returns this.
class Rva00077710Value
{
public:
	void rva0022D189(int value);
	Rva00077710Value &rva0022D979(const int &value);
	int m_a;
	int m_b;
};

Rva00077710Value &Rva00077710Value::rva0022D979(const int &value)
{
	rva0022D189(value);
	return *this;
}

// --- 0x0023262C (23B): whether the halfword at +6 of the indexed 8-byte
// record at +0x18 shares a bit with the mask.
struct Rva0023262CRecord
{
	char m_pad00[6];
	unsigned short m_bits;
};

class Rva0023262C
{
public:
	int rva0023262C(unsigned char index, int mask);
private:
	char m_pad00[0x18];
	Rva0023262CRecord m_records[1];
};

int Rva0023262C::rva0023262C(unsigned char index, int mask)
{
	return (m_records[index].m_bits & mask) != 0;
}

// --- 0x0023426A (30B): constructor from an eight-byte pair and a halfword;
// 0x002342C5 (16B): copies the first halfword out and returns 1.
class Rva0023426A
{
public:
	Rva0023426A(const Rva002226A2Pair &pair, const short &value);
	int rva002342C5(short *out) const;
private:
	Rva002226A2Pair m_00;
	short m_08;
};

Rva0023426A::Rva0023426A(const Rva002226A2Pair &pair, const short &value) : m_00(pair), m_08(value)
{
}

int Rva0023426A::rva002342C5(short *out) const
{
	*out = *(const short *)&m_00;
	return 1;
}

// --- 0x00239B11 (24B): one node from the freelist pool at VA 0x00DBA5E0
// (rowed pop), none for a count above one; the second word is unused.
class FreelistPool
{
public:
	void *pop();
};
extern FreelistPool g_freelistPool00DBA5E0;

class Rva00239B11
{
public:
	void *rva00239B11(unsigned int count, const void *hint);
};

void *Rva00239B11::rva00239B11(unsigned int count, const void *)
{
	if (count > 1)
		return 0;
	return g_freelistPool00DBA5E0.pop();
}

// --- 0x0023DB48 (16B): latches +0x38 into an unset +0x40 and returns it.
class Rva0023DB48
{
public:
	int rva0023DB48();
private:
	char m_pad00[0x38];
	int m_38;
	int m_3C;
	int m_40;
};

int Rva0023DB48::rva0023DB48()
{
	if (m_40 == 0)
		m_40 = m_38;
	return m_40;
}

// --- 0x0023E887 (28B): constructor copying a word and building the string
// at +4 from the source's text.
struct Rva0023E887Source
{
	int m_00;
	const char *m_text;
};

class Rva0023E887
{
public:
	Rva0023E887(const Rva0023E887Source &source);
private:
	int m_00;
	AsciiString m_text;
};

Rva0023E887::Rva0023E887(const Rva0023E887Source &source) : m_00(source.m_00), m_text(source.m_text)
{
}

// --- 0x00254628 (34B) and 0x002546EB (34B): module-data field parsers,
// each the rowed base table 0x004CE29D at offset 8 then its own table (VA
// 0x00BF247C, VA 0x00BF2534); 0x0025464A (52B) and 0x0025470D (52B): their
// INI factories over 0x11C-byte data built by the rowed constructors
// 0x0025460F and 0x002546D2 (the latter folds with RadarUpgradeModuleData's).
struct FieldParse;
class ModuleData;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *table, unsigned int offset);	// 0x0002BC6E
};

class INI
{
public:
	void initFromINIMultiProc(void *what, void (*proc)(MultiIniFieldParse &p));	// 0x0002DEB5
};

int Rva004CE29DGet(void);
extern const FieldParse s_Rva00254628FieldParse[];			// VA 0x00BF247C
extern const FieldParse s_Rva002546EBFieldParse[];			// VA 0x00BF2534

class Rva0025460F
{
public:
	Rva0025460F();
private:
	char m_pad[0x11C];
};

class RadarUpgradeModuleData
{
public:
	RadarUpgradeModuleData();
private:
	unsigned char m_pad[0x11C];
};

class Rva00254628ModuleData
{
public:
	static void rva00254628(MultiIniFieldParse &p);
	static ModuleData *rva0025464A(INI *ini);
};

void Rva00254628ModuleData::rva00254628(MultiIniFieldParse &p)
{
	p.add((const FieldParse *)Rva004CE29DGet(), 8);
	p.add(s_Rva00254628FieldParse, 0);
}

ModuleData *Rva00254628ModuleData::rva0025464A(INI *ini)
{
	Rva0025460F *data = new Rva0025460F;
	if (ini)
		ini->initFromINIMultiProc(data, rva00254628);
	return (ModuleData *)data;
}

class Rva002546EBModuleData
{
public:
	static void rva002546EB(MultiIniFieldParse &p);
	static ModuleData *rva0025470D(INI *ini);
};

void Rva002546EBModuleData::rva002546EB(MultiIniFieldParse &p)
{
	p.add((const FieldParse *)Rva004CE29DGet(), 8);
	p.add(s_Rva002546EBFieldParse, 0);
}

ModuleData *Rva002546EBModuleData::rva0025470D(INI *ini)
{
	RadarUpgradeModuleData *data = new RadarUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, rva002546EB);
	return (ModuleData *)data;
}
