// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// stlport
#define BFME_ASCII_DTOR_DECL
#include "ascii_string.h"
#include "Coord3D.h"
#include <list>
#include <map>
//
// Two EH-guarded member factories in the 0x4E063F shape: 0x4E6745 news a
// 0x20-byte Rva004E669A with (this plus three ints) and 0x4E7F43 news a
// 0x28-byte Rva004E7D72 with (this), each stored to m_00 with this
// returned. Retail 0x004E6745 70B, 0x004E7F43 59B. Both ctors are pinned
// as honest address-derived candidates (new-expression targets); the
// 0x4E7D72 body itself is an in-range target for later recovery.

class Rva004E669A
{
public:
	Rva004E669A(void *parent, int a, int b, int c);

private:
	char m_pad[0x20];
};

class Rva004E6745
{
public:
	Rva004E6745 *rva004E6745(int a, int b, int c);

private:
	Rva004E669A *m_00;
};

// ?rva004E6745@Rva004E6745@@QAEPAURva004E6745@@HHH@Z @0x004E6745 70B.
Rva004E6745 *Rva004E6745::rva004E6745(int a, int b, int c)
{
	m_00 = new Rva004E669A(this, a, b, c);
	return this;
}

class Rva004E5610
{
public:
    Rva004E5610();
private:
    char m_pad[0x0C];
};

class Rva004E7D72
{
public:
	Rva004E7D72(void *parent);

private:
    void *m_parent;
    int m_04;
    AsciiString m_name;
    _STL::list<Coord3D> m_list0C;
    _STL::map<int, void *> m_map10;
    Rva004E5610 m_1C;
};

class Rva004E7F43
{
public:
	Rva004E7F43 *rva004E7F43();

private:
	Rva004E7D72 *m_00;
};

// ?rva004E7F43@Rva004E7F43@@QAEPAURva004E7F43@@XZ @0x004E7F43 59B.
Rva004E7F43 *Rva004E7F43::rva004E7F43()
{
	m_00 = new Rva004E7D72(this);
	return this;
}

// Native4E7D72..4E7DC8 RET4 and WB131C300 prove parent+0, scalar+4,
// string+8, list+C, map+10 and the 12-byte member+1C. Native unwind
// action792399 adjusts this by8 and jumps to rowed AsciiString::~AsciiString
// at48BA39; the old artificial-base model hid that real member lifetime.
Rva004E7D72::Rva004E7D72(void *parent)
    : m_parent(parent), m_04(0), m_name(), m_list0C(), m_map10(), m_1C()
{
}
