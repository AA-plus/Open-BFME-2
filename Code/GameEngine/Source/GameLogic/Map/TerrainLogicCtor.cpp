// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0TerrainLogic@@QAE@XZ, retail 0x00283FAA..0x0028417C (466 bytes, EH,
// ret 0): TerrainLogic's constructor. Identity: it installs the vtable
// 0x00BFB2C8 whose slot-2 name getter returns "TerrainLogic" (the rowed
// ??_GTerrainLogic at 0x00285177 is its slot 0), and its only caller is the
// W3DTerrainLogic constructor 0x00062A7E. Bases (tables and unwind targets
// from retail, EH funclets 0x00773C57..0x00773CDE): Snapshot (0x00BBB554,
// unwind 0x0055F72C), SubsystemInterface at +4 (rowed ctor/dtor), and two
// listener interfaces at +0x10/+0x14 sharing the root table 0x00BC6F34
// (unwind 0x004EE006). Members, in the order retail builds them: three
// cleared words +0x24..+0x2C, a vector at +0x30, 1 at +0x48, an AsciiString
// at +0x4C, four owning holders +0x50..+0x5C each given a new 0x20-byte
// Rva002834C4 (rowed ctor; holder dtor 0x002833E7), the observer list at
// +0x64, the int-keyed map at +0x56C, a vector at +0x578. The body clears the
// remaining words, zeroes the 64 records at +0x68, fills the 1250-word table
// at +0x588 with -1, registers the two listener bases with the +0x54 and +0x58
// objects (rowed append 0x005A0B4C) and creates the +0x584 Rva00283081
// (rowed ctor) with 100.0f and the identity callback 0x000D1D26 (defined and
// rowed here). Member meanings beyond these offsets are not established.
#include <map>
#include <list>
#include <vector>
#include "ascii_string.h"

typedef int Int;
typedef float Real;

#include "Common/Snapshot.h"

class SubsystemInterface
{
public:
	SubsystemInterface();								// 0x001B4E63
	virtual ~SubsystemInterface();
private:
	unsigned char m_04[8];
};

// The two listener interfaces: separate classes whose identical tables fold to
// 0x00BC6F34 (retail stores each through its own immediate).
class TerrainLogicListenerA
{
public:
	TerrainLogicListenerA() {}
	virtual void vslot0();
	~TerrainLogicListenerA();
};

class TerrainLogicListenerB
{
public:
	TerrainLogicListenerB() {}
	virtual void vslot0();
	~TerrainLogicListenerB();
};

struct Rva00501875Count
{
	int m_count;
};

struct Rva004FA1FObserver;
struct Rva002BA8F1Listener;

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);			// 0x005A0B4C
};

class Rva002834C4
{
public:
	Rva002834C4() throw();								// 0x002834C4
private:
	unsigned char m_bytes[0x20];
};

class Rva002833E7Holder
{
public:
	Rva002833E7Holder(Rva002834C4 *ptr) : m_ptr(ptr) {}
	~Rva002833E7Holder();								// 0x002833E7
	Rva002834C4 *m_ptr;
};

class Rva00283081
{
public:
	Rva00283081(float f, int i) throw();				// 0x004DFC59
private:
	unsigned char m_bytes[0x24];
};

// The callback the +0x584 object receives: returns its argument.
int __cdecl Rva000D1D26Identity(int value)
{
	return value;
}

struct TerrainLogicRecord
{
	Int m_00;
	Real m_04[4];
};

class TerrainLogic : public Snapshot, public SubsystemInterface,
	public TerrainLogicListenerA, public TerrainLogicListenerB
{
public:
	TerrainLogic();
	virtual ~TerrainLogic();
	virtual void vslot0();

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	Int m_18;											// +0x18
	Int m_1C;											// +0x1C
	Int m_20;											// +0x20
	Int m_24;											// +0x24
	Int m_28;											// +0x28
	Int m_2C;											// +0x2C
	_STL::vector<Int> m_30;								// +0x30
	Int m_3C;											// +0x3C
	Int m_40;											// +0x40
	bool m_44;											// +0x44
	Int m_48;											// +0x48
	AsciiString m_4C;									// +0x4C
	Rva002833E7Holder m_50;								// +0x50
	Rva002833E7Holder m_54;								// +0x54
	Rva002833E7Holder m_58;								// +0x58
	Rva002833E7Holder m_5C;								// +0x5C
	bool m_60;											// +0x60
	_STL::list<Rva004FA1FObserver *> m_64;				// +0x64
	TerrainLogicRecord m_records[64];					// +0x68
	Int m_568;											// +0x568
	_STL::map<Int, Rva00501875Count> m_56C;				// +0x56C
	_STL::vector<Int> m_578;							// +0x578
	Rva00283081 *m_584;									// +0x584
	Int m_588[1250];									// +0x588
	Int m_1910;											// +0x1910
	bool m_1914;										// +0x1914
	Real m_1918;										// +0x1918
};

TerrainLogic::TerrainLogic()
	: m_24(0), m_28(0), m_2C(0), m_48(1),
	  m_50(new Rva002834C4), m_54(new Rva002834C4), m_58(new Rva002834C4), m_5C(new Rva002834C4)
{
	m_1914 = false;
	m_3C = 0;
	m_60 = false;
	for (Int i = 0; i < 64; ++i)
	{
		m_records[i].m_00 = 0;
		m_records[i].m_04[0] = 0.0f;
		m_records[i].m_04[1] = 0.0f;
		m_records[i].m_04[2] = 0.0f;
		m_records[i].m_04[3] = 0.0f;
	}
	m_568 = 0;
	m_40 = 0;
	m_18 = 0;
	m_44 = false;
	m_1C = 0;
	m_20 = 0;
	for (Int j = 0; j < 1250; ++j)
		m_588[j] = -1;
	m_1910 = 0;
	m_1918 = 0.0f;
	((Rva005A0B4CList *)m_54.m_ptr)->append((Rva002BA8F1Listener *)static_cast<TerrainLogicListenerA *>(this));
	((Rva005A0B4CList *)m_58.m_ptr)->append((Rva002BA8F1Listener *)static_cast<TerrainLogicListenerB *>(this));
	m_584 = new Rva00283081(100.0f, (int)&Rva000D1D26Identity);
}
