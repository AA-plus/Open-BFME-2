// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva0030902E@@UAE@XZ, retail 0x0030902E..0x0030912A (252 bytes, EH):
// the destructor of the owner whose broadcast slots Rva00308AA4Notifiers.cpp
// rows (scalar deleting destructor 0x00309332; tables 0x00C07F80 at +0,
// 0x00C07F4C at +0x30, 0x00C07F30 on the shared virtual base behind its
// vtordisp). The same three-base shape as Rva0030CAA9OwnerDtor.cpp: it tells
// every listener through slot 0 (the generic vcall thunk 0x001FF3A9), frees
// its +0x98 array, releases the +0x84 reference, sets +0x88 and runs the
// rowed StandingWaterArea::rva003080CE on itself. Then its +0x8C/+0x80
// strings, the two +0x78 strings, the listener storage (GameFree; unwind copy
// 0x0007FAB3), the secondary base (rowed 0x002E3E51) and the primary base
// (0x00538133) die. The virtual base sits at +0xD8.
#include "ascii_string.h"

void __cdecl Rva00030830GameFree(void *);
void operator delete[](void *p);

class VBase00C6EE28
{
public:
	virtual void s0();
};

class Rva00538133Root
{
public:
	virtual void s1();
private:
	unsigned char m_pad04[0x18 - 4];
};

class Rva0053805DBase : public Rva00538133Root, public virtual VBase00C6EE28
{
public:
	virtual ~Rva0053805DBase();
	virtual void s0();
private:
	unsigned char m_pad1C[0x30 - 0x1C];
};

class Rva002E3E51 : public virtual VBase00C6EE28
{
public:
	virtual ~Rva002E3E51();
	virtual void s0();
private:
	void *m_08;
	unsigned char m_pad0C[0x38 - 0x0C];
};

class Rva00308AA4Owner;

class Rva00308AA4Listener
{
public:
	virtual void notify00(Rva00308AA4Owner *owner);
};

class Rva003089CFList
{
public:
	~Rva003089CFList() { if (m_begin) Rva00030830GameFree(m_begin); }
	void forEach(void (Rva00308AA4Listener::*notify)(Rva00308AA4Owner *), Rva00308AA4Owner *owner);
private:
	Rva00308AA4Listener **m_begin;
	Rva00308AA4Listener **m_end;
	Rva00308AA4Listener **m_capacity;
	unsigned int m_index;
};

class StandingWaterArea
{
public:
	void rva003080CE();
};

class Rva0030902ERef
{
public:
	virtual void Delete_This();
	void Release_Ref() { if (--m_refs == 0) Delete_This(); }
private:
	int m_refs;
};

class Rva0030902E : public Rva0053805DBase, public Rva002E3E51, public Rva003089CFList
{
public:
	virtual ~Rva0030902E();
	virtual void s0();
private:
	AsciiString m_78[2];			// +0x78
	AsciiString m_80;			// +0x80
	Rva0030902ERef *m_84;			// +0x84
	bool m_88;				// +0x88
	AsciiString m_8C;			// +0x8C
	int m_90;
	int m_94;
	unsigned char *m_98;			// +0x98
	unsigned char m_pad9C[0xD4 - 0x9C];
};

Rva0030902E::~Rva0030902E()
{
	forEach(&Rva00308AA4Listener::notify00, (Rva00308AA4Owner *)this);
	if (m_98)
	{
		delete[] m_98;
		m_98 = 0;
	}
	if (m_84)
	{
		m_84->Release_Ref();
		m_84 = 0;
	}
	m_88 = true;
	((StandingWaterArea *)this)->rva003080CE();
}
