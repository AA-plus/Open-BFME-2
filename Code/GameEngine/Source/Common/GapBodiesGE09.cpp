// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no Ghidra function covers (ninth
// batch; see GapBodiesGE01.cpp). Retail bytes establish every shape; owning
// classes are not recovered, so each keeps an address-derived name and a view
// of only the members it touches. Callees and globals use the ledger's
// existing spellings.

// --- 0x003B940A (4B): set the +0x00 flag; 0x003B940E (10B): the
// create-a-hero screen flag (g_Va00DFD944); 0x003B9418 (9B): clear +0x08 and
// +0x0C; 0x003B9421 (10B): the +0x2C flag; 0x003B9433 (10B): the asset
// colouring flag (g_Va00DB6218).
extern unsigned char g_Va00DFD944;
extern bool g_Va00DB6218;

class Rva003B940A
{
public:
	void rva003B940A();
	void rva003B9418();
	void rva003B9421(bool flag);
private:
	bool m_00;
	char m_pad01[7];
	int m_08;
	int m_0C;
	char m_pad10[0x2C - 0x10];
	bool m_2C;
};

void Rva003B940A::rva003B940A()
{
	m_00 = true;
}

void Rva003B940E(unsigned char flag)
{
	g_Va00DFD944 = flag;
}

void Rva003B940A::rva003B9418()
{
	m_08 = 0;
	m_0C = 0;
}

void Rva003B940A::rva003B9421(bool flag)
{
	m_2C = flag;
}

void Rva003B9433(bool flag)
{
	g_Va00DB6218 = flag;
}

// --- 0x003BD52F (61B, cdecl): the index of the name in the table at VA
// 0x00DBE9B0 (case-insensitive), 6 when absent.
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
extern const char *TheRva003BD52FNames[];

int Rva003BD52F(const char *name)
{
	if (!name)
		return 6;
	const char **p = TheRva003BD52FNames;
	for (int i = 0; p; ++p, ++i)
	{
		if (!*p)
			break;
		if (!_strcmpi(*p, name))
			return i;
	}
	return 6;
}

// --- 0x0048FF77 (29B): vtable 0x00C4D040 with an int and a flag;
// 0x005E9FFB / 0x005EA026 (18B): vtables 0x00C78134 / 0x00C78174 over one
// word; 0x005EA00D (25B): vtable 0x00C78154 over two words.
class Rva0048FF77
{
public:
	Rva0048FF77(int value, bool flag);
	virtual ~Rva0048FF77() {}
private:
	int m_04;
	int m_08;
	bool m_0C;
};

Rva0048FF77::Rva0048FF77(int value, bool flag) : m_04(0), m_08(value), m_0C(flag)
{
}

struct GapWordBase04
{
	int m_04;
	GapWordBase04(int a) : m_04(a) {}
};

#define GAP_VTABLE_WORD_CTOR(NAME) \
	class NAME : public GapWordBase04 \
	{ \
	public: \
		NAME(int a); \
		virtual ~NAME() {} \
	}; \
	NAME::NAME(int a) : GapWordBase04(a) \
	{ \
	}

GAP_VTABLE_WORD_CTOR(Rva005E9FFB)
GAP_VTABLE_WORD_CTOR(Rva005EA026)

class Rva005EA00D
{
public:
	Rva005EA00D(int a, int b);
	virtual ~Rva005EA00D() {}
private:
	int m_04;
	int m_08;
};

Rva005EA00D::Rva005EA00D(int a, int b) : m_04(a), m_08(b)
{
}
