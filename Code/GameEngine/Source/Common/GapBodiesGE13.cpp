// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (thirteenth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered unless named, so each keeps an
// address-derived name and a view of only the members it touches. Callees and
// globals use the ledger's existing spellings.
#include "ascii_string.h"

extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);

// --- 0x0056FAC4 / 0x0056FAD6 / 0x0056FAE8 / 0x0056FAF9: forward one value
// as both arguments of the rowed hooks (the third from a short).
int Rva0056F742Hook(int a, int b);							// 0x0056F742
int Rva0056F79BHook(int a, int b);							// 0x0056F79B
int Rva0056F7F4Hook(int a, int b);							// 0x0056F7F4
int Rva0056F84DHook(int a, int b);							// 0x0056F84D

class Rva0056FAC4
{
public:
	int rva0056FAC4(int value);
	int rva0056FAD6(int value);
	int rva0056FAE8(short value);
	int rva0056FAF9(int value);
};

int Rva0056FAC4::rva0056FAC4(int value) { return Rva0056F742Hook(value, value); }
int Rva0056FAC4::rva0056FAD6(int value) { return Rva0056F79BHook(value, value); }
int Rva0056FAC4::rva0056FAE8(short value) { return Rva0056F7F4Hook(value, value); }
int Rva0056FAC4::rva0056FAF9(int value) { return Rva0056F84DHook(value, value); }

// --- 0x005C4D1B (20B): the house colour reaches LivingWorldVisual's own
// setHouseColor only while the +0xAC object's +0x54 flag is set.
class LivingWorldVisual
{
public:
	virtual void setHouseColor(const int &color);			// 0x003FB602
};

struct Rva005C4D1BState
{
	char m_pad[0x54];
	bool m_54;
};

class Rva005C4D1B : public LivingWorldVisual
{
public:
	void rva005C4D1B(const int &color);
private:
	char m_pad[0xAC - 4];
	Rva005C4D1BState *m_AC;
};

void Rva005C4D1B::rva005C4D1B(const int &color)
{
	if (m_AC->m_54)
		LivingWorldVisual::setHouseColor(color);
}

// --- 0x002B2C9F (10B, cdecl): whether the value is non-zero.
bool Rva002B2C9F(int value)
{
	return value != 0;
}

// --- 0x002BEA63 (73B): every entry of the container (virtual slots 28 and
// 30) goes through the rowed 0x0010E4F6 and drops a reference (+0x04,
// releasing through virtual slot 0 at zero).
void rva0010E4F6(void *obj, bool flag);						// 0x0010E4F6

class Rva002BEA63Entry
{
public:
	virtual void destroy();
	int m_refs;												// +0x04
};

class Rva002BEA63Container
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual int count();
	virtual void s29();
	virtual Rva002BEA63Entry *entry(int index);
};

class Rva002BEA63
{
public:
	void rva002BEA63(Rva002BEA63Container *container);
};

void Rva002BEA63::rva002BEA63(Rva002BEA63Container *container)
{
	for (int i = 0; i < container->count(); ++i)
	{
		Rva002BEA63Entry *entry = container->entry(i);
		if (entry)
		{
			rva0010E4F6(entry, false);
			if (--entry->m_refs == 0)
				entry->destroy();
		}
	}
}

// --- 0x005B5B92 (74B): a numeric (1-based, under 11) string naming the
// current +0x24 entry clears the hero-powers description and the selection.
void Rva005B23D7HeroPowersDescription(void *owner, const AsciiString &a, const AsciiString &b);	// 0x005B23D7

class Rva005B5B92
{
public:
	void rva005B5B92(const char *text);
private:
	char m_pad[0x24];
	int m_current;
};

void Rva005B5B92::rva005B5B92(const char *text)
{
	if (text && isdigit(*text))
	{
		int index = atoi(text) - 1;
		if (index >= 0 && index < 10 && index == m_current)
		{
			Rva005B23D7HeroPowersDescription(0, AsciiString::TheEmptyString, AsciiString::TheEmptyString);
			m_current = -1;
		}
	}
}
