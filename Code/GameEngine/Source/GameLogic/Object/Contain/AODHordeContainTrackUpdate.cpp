// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0047B628@Rva0047B628@@QAEXHPAX@Z @0x0047B628 76B: large-unit tracker
// update. Gap between ??1 (0x0047B563) and ??_G (0x0047B674) in the AODHordeContain
// TU; same flags. Validates the second arg (null, +0x438 flag, +0x4 -> +0x5F5 ==
// 2), stores +0x74 to +0x1FC (full +0x318) unless equal, refreshes via full-0x11C,
// then +0x200 (full +0x31C) from TheGameLogic+0x40. Callees rowed:
// refreshTrackedLargeUnit 0x0047B2AA, TheGameLogic ?TheGameLogic@@3PAVGameLogic@@A.
//
// Register-allocation note (established from the byte match): retail never
// materialises arg1 and loads the arg pointer straight into ecx. Reproducing
// that needs the m_1FC member to be reached through an address local that stays
// live across the compare and the store, which keeps this-derived pointers in
// esi and drops the unused arg1 preload.
#include <vector>

class Thing;
class ModuleData;

struct Iface00 { virtual void f00(); unsigned char m_pad[8]; };
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };
struct Iface20 { virtual void f20(); };
struct Iface24 { virtual void f24(); };
struct Iface28 { virtual void f28(); };
struct Iface2C { virtual void f2C(); };
struct Iface30 { virtual void f30(); };
struct Iface34 { virtual void f34(); unsigned char m_pad[0xFC - 0x38]; };
struct IfaceFC { virtual void fFC(); unsigned char m_pad[0x11C - 0x100]; };
struct Iface11C { virtual void f11C(); unsigned char m_pad[0x30C - 0x11C - 4]; };

class HordeContain
	: public Iface00
	, public Iface0C
	, public Iface10
	, public Iface20
	, public Iface24
	, public Iface28
	, public Iface2C
	, public Iface30
	, public Iface34
	, public IfaceFC
	, public Iface11C
{
public:
	virtual ~HordeContain();
};

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

struct AODDtorElem16
{
	~AODDtorElem16();
	float m_f[4];
};

// ??1AODDtorElem16@@QAE@XZ present-unmatched
AODDtorElem16::~AODDtorElem16()
{
}

struct AODDtorElem24
{
	~AODDtorElem24();
	float m_f[5];
	unsigned char m_b;
	unsigned char m_pad[3];
};

// ??1AODDtorElem24@@QAE@XZ present-unmatched
AODDtorElem24::~AODDtorElem24()
{
}

class GameLogic
{
public:
	unsigned char m_pad[0x40];
	int m_40;
};

extern GameLogic *TheGameLogic;

class Rva0047B628
{
public:
	void rva0047B628(int a, void *b);

private:
	unsigned char m_pad[0x1FC];
	int m_1FC;
	int m_200;
};

class AODHordeContain : public HordeContain
{
public:
	virtual ~AODHordeContain();
	void refreshTrackedLargeUnit();

private:
	_STL::vector<BfmeE16> m_vector;
	int m_318;
	int m_31C;
	float m_320[3];
	float m_32C;
	float m_330;
	float m_334;
	AODDtorElem16 m_arrayA[0x3C];
	int m_6F8;
	AODDtorElem24 m_arrayB[0x14];
	int m_8DC;
};

// ??1AODHordeContain@@UAE@XZ present-unmatched
// Gap between ??1 (0x0047B563) and ??_G (0x0047B674) in this TU; same flags.
// Large-unit tracker update: validates the second arg (null, +0x438 flag,
// +0x4 -> +0x5F5 == 2), stores +0x74 to +0x1FC (full +0x318) unless equal,
// refreshes via full-0x11C, then +0x200 (full +0x31C) from TheGameLogic+0x40.
// Callers: none rowed. Callees rowed: refreshTrackedLargeUnit 0x0047B2AA,
// TheGameLogic ?TheGameLogic@@3PAVGameLogic@@A.
void Rva0047B628::rva0047B628(int a, void *b)
{
	if (b == 0)
		return;
	if (*((unsigned char *)b + 0x438) & 1)
		return;
	void *p = *(void **)((char *)b + 4);
	if (*((unsigned char *)p + 0x5F5) != 2)
		return;
	int *ap = &m_1FC;
	int v = *(int *)((char *)b + 0x74);
	if (v == *ap)
		return;
	*ap = v;
	((AODHordeContain *)((char *)this - 0x11C))->refreshTrackedLargeUnit();
	m_200 = TheGameLogic->m_40;
}
