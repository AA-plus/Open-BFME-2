// cl: /O1 /arch:SSE /G7 /EHsc /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii
//
// ??0Rva0030C1FCOwner@@QAE@H@Z, retail 0x0030C4DE (317 bytes, EH, RET 8: one
// int and the hidden most-derived flag): the constructor of the river area
// whose destructor 0x0030C40A (Rva0030C1FCOwnerDtor.cpp) and broadcast slots
// (Rva0030C1FCNotifiers.cpp) are rowed; RiverAreasDataChunkParser::parse
// 0x0030C6C8 and the river importer 0x00329339 allocate it (new 0x94).
// Target evidence: it installs the destructor's tables (0x00C088FC at +0,
// 0x00C088E0 on the shared interface 0x00C6EE28 at +0x90 behind a vtordisp)
// over the rowed primary base Rva0053805DBase 0x005380A8 and the listener
// list 0x00330757 (a second base at +0x30, as in the destructor), then
// builds four AsciiStrings at +0x40 (eh vector constructor iterator), 1.0 at
// +0x50..+0x58, the water transparency setting's +0x40 at +0x5C, -1 at +0x60,
// 0 at +0x64 and the quad strip at +0x68 (rowed constructor 0x005388AB),
// whose storage the int reserves (rowed QuadStrip2D 0x0053892C, WorldBuilder
// RiverArea::reserveStipSpace). The strings default to the setting's +0x3C
// texture, "Noise0000.tga", "TWAlphaEdge.tga" and
// "WaterSurfaceBubbles.tga". Field meanings are not established; names are
// address-derived.
#include "ascii_string.h"

void __cdecl Rva00030830GameFree(void *);

class VBase00C6EE28
{
public:
	virtual void s0() = 0;
	~VBase00C6EE28();
};

// The base as Rva0053805DBaseCtor.cpp lays it out.
class __declspec(novtable) Rva0007DF07
{
public:
	Rva0007DF07() : count(0) {}
	virtual ~Rva0007DF07();
private:
	unsigned int count;
};

class Rva00330757Member
{
public:
	Rva00330757Member() throw();
	~Rva00330757Member();
private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
	unsigned int m_index;
};

class Rva0053805DBase : public Rva0007DF07, public Rva00330757Member,
	public virtual VBase00C6EE28
{
public:
	Rva0053805DBase();
	virtual ~Rva0053805DBase();
	virtual bool slot1() const;
	virtual void rva0053805D();
	virtual void rva0053806C();
private:
	unsigned char m_pad1C[0x30 - 0x1C];
};

class Overridable
{
public:
	Overridable *friend_getFinalOverride();
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
private:
	void *m_vtbl;
	Overridable *m_nextOverride;	// +0x04
};

class WaterTransparencySetting : public Overridable
{
public:
	unsigned char m_pad08[0x3C - 0x08];
	AsciiString m_3C;	// +0x3C
	int m_40;		// +0x40
};

template <class T> class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_overridable)
			return 0;
		return (const T *)m_overridable->getFinalOverride();
	}
private:
	T *m_overridable;
};
extern OVERRIDE<WaterTransparencySetting> TheWaterTransparency;

// The quad strip at +0x68: rowed constructor 0x005388AB (Rva005388ABCtor.cpp)
// and reserve 0x0053892C (rowed on QuadStrip2D).
class QuadStrip2D
{
public:
	void rva0053892C(unsigned int count);
};

class Rva005388AB
{
public:
	Rva005388AB();
	~Rva005388AB() { if (m_data) Rva00030830GameFree(m_data); }
private:
	void *m_data;
	unsigned char m_pad04[0x24 - 0x04];
};

class Rva0030C1FCOwner : public Rva0053805DBase, public Rva00330757Member
{
public:
	Rva0030C1FCOwner(int count);
	virtual ~Rva0030C1FCOwner();
	virtual void s0();
private:
	AsciiString m_40[4];		// +0x40
	float m_50;			// +0x50
	float m_54;
	float m_58;
	int m_5C;			// +0x5C
	int m_60;			// +0x60
	int m_64;			// +0x64
	Rva005388AB m_68;		// +0x68
};

Rva0030C1FCOwner::Rva0030C1FCOwner(int count)
	: m_50(1.0f), m_54(1.0f), m_58(1.0f), m_5C(TheWaterTransparency->m_40), m_60(-1), m_64(0)
{
	reinterpret_cast<QuadStrip2D *>(&m_68)->rva0053892C(count);
	m_40[0] = TheWaterTransparency->m_3C;
	m_40[1] = "Noise0000.tga";
	m_40[2] = "TWAlphaEdge.tga";
	m_40[3] = "WaterSurfaceBubbles.tga";
}
