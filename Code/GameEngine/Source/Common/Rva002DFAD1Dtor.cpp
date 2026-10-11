// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva002DFAD1Dtor@@QAE@XZ, retail 0x002DFAD1..0x002DFBA0 (207 bytes, EH):
// a non-virtual destructor reached from the adjustor destructor 0x0022630F
// (pinned name). It ::deletes every object of its +0x30 list; then the
// +0x3C and +0x30 buffers go to GameFree (unwind copies 0x0007FAB3) and its
// eight strings at +0x24 down to +0 die. Identity not established.
#include "ascii_string.h"

void __cdecl Rva00030830GameFree(void *);

class Rva002DFAD1Owned
{
public:
	virtual ~Rva002DFAD1Owned();
};

struct Gen_uw_0007fab3
{
	~Gen_uw_0007fab3() { if (m_begin) Rva00030830GameFree(m_begin); }
	Rva002DFAD1Owned **m_begin;
	Rva002DFAD1Owned **m_end;
	Rva002DFAD1Owned **m_capacity;
};

class Rva002DFAD1Dtor
{
public:
	~Rva002DFAD1Dtor();
private:
	AsciiString m_00;
	int m_04;
	int m_08;
	AsciiString m_0C;
	AsciiString m_10;
	AsciiString m_14;
	AsciiString m_18;
	AsciiString m_1C;
	AsciiString m_20;
	AsciiString m_24;
	int m_28;
	int m_2C;
	Gen_uw_0007fab3 m_30;
	Gen_uw_0007fab3 m_3C;
};

Rva002DFAD1Dtor::~Rva002DFAD1Dtor()
{
	Rva002DFAD1Owned **p = m_30.m_begin;
	Rva002DFAD1Owned **end = m_30.m_end;
	for (; p != end; ++p)
		::delete *p;
}
