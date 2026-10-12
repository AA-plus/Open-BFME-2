// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (thirty-eighth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.
#include "../../../Libraries/Include/Lib/RGBColor.h"

// Declaration-only view of the STLport vector member these bodies call; no
// container code is instantiated here.
namespace _STL {
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	T *erase(T *first, T *last);
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

// --- 0x005D48BE (29B): two words and a float.
class Rva005D48BE
{
public:
	Rva005D48BE(int a, int b, float c);
private:
	int m_a;
	int m_b;
	float m_c;
};

Rva005D48BE::Rva005D48BE(int a, int b, float c) : m_a(a), m_b(b), m_c(c)
{
}

// --- 0x005D833E (28B) / 0x005D851D (28B), cdecl: empty the 8-byte-record
// vectors at 0x00E06654 / 0x00E06670 (rowed erase 0x003FA4DB).
struct BfmePod8;
extern unsigned g_Va00E06654;
extern unsigned g_Va00E06670;

typedef _STL::vector<BfmePod8> Rva005D833EVector;

void Rva005D833E()
{
	Rva005D833EVector &records = *(Rva005D833EVector *)&g_Va00E06654;
	if (records.m_start != records.m_finish)
		records.erase(records.m_start, records.m_finish);
}

void Rva005D851D()
{
	Rva005D833EVector &records = *(Rva005D833EVector *)&g_Va00E06670;
	if (records.m_start != records.m_finish)
		records.erase(records.m_start, records.m_finish);
}

// --- 0x005DBB7A (43B): the (row, column) word of the +0x738 8x8 table, 0
// outside it.
class Rva005DBB7A
{
public:
	int rva005DBB7A(unsigned short row, unsigned short column) const;
private:
	char m_pad[0x738];
	int m_table[8][8];
};

int Rva005DBB7A::rva005DBB7A(unsigned short row, unsigned short column) const
{
	if (row < 8 && column < 8)
		return m_table[row][column];
	return 0;
}

// --- 0x005DD7FB (39B): the +0x14 flag of the indexed 24-byte record, false
// past the end.
struct Rva005DD7FBRecord
{
	int m_words[5];
	bool m_14;
};

struct Rva005DD7FBVector
{
	__forceinline unsigned size() const { return m_end - m_begin; }
	__forceinline const Rva005DD7FBRecord &operator[](unsigned i) const { return m_begin[i]; }
	Rva005DD7FBRecord *m_begin;
	Rva005DD7FBRecord *m_end;
};

class Rva005DD7FB
{
public:
	bool rva005DD7FB(unsigned index) const;
private:
	int m_00;
	Rva005DD7FBVector m_records;
};

bool Rva005DD7FB::rva005DD7FB(unsigned index) const
{
	if (index >= m_records.size())
		return false;
	return m_records[index].m_14;
}

// --- 0x005E18EA (28B, cdecl): the colour of TheLivingWorldLogic's +0x98
// player (+0x184) with full alpha (rowed RGBColor::getAsInt).
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva005E18EAPlayer
{
	char m_pad[0x184];
	RGBColor m_color;
};

struct Rva005E18EALogic
{
	char m_pad[0x98];
	Rva005E18EAPlayer *m_player;
};

int Rva005E18EA()
{
	return ((Rva005E18EALogic *)TheLivingWorldLogic)->m_player->m_color.getAsInt() | 0xFF000000;
}

// --- 0x005E21AB (23B): the button image of the +0x20 record, or the
// fallback image of the receiver (rowed 0x005F02E0, 0x005F0318).
class Image;

namespace StrategicInGameUI {
const Image *GetButtonImage(void *record);					// 0x005F02E0
}

const Image *Rva005F0318Get(void *owner);					// 0x005F0318

class Rva005E21AB
{
public:
	const Image *rva005E21AB();
private:
	char m_pad[0x20];
	void *m_record;
};

const Image *Rva005E21AB::rva005E21AB()
{
	if (m_record)
		return StrategicInGameUI::GetButtonImage(m_record);
	return Rva005F0318Get(this);
}

// --- 0x005E3EE2 (12B): a handle of the +0x10 word.
struct Rva005E3EE2Handle
{
	Rva005E3EE2Handle(int value) : m_value(value) {}
	int m_value;
};

class Rva005E3EE2
{
public:
	Rva005E3EE2Handle rva005E3EE2() const;
private:
	char m_pad[0x10];
	int m_10;
};

Rva005E3EE2Handle Rva005E3EE2::rva005E3EE2() const
{
	return Rva005E3EE2Handle(m_10);
}
