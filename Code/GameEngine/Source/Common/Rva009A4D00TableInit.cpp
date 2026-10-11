// ?Rva009A4D00Init@@YAXXZ
// Address-derived: two opaque setup helpers seed a global, a 64-entry signed
// 16-bit table is halved (rounding toward zero) and offset by 2 into an int
// array, then an opaque helper and InitVPUtil run in tail position.

extern void d_009a8430();
extern void d_009a5aa0();
// VP6 clean-room InitVPUtil (Code/Libraries/Source/VP6/InitVPUtil.cpp).
extern "C" void __cdecl InitVPUtil(void);

extern void __cdecl bfmeQueryCpuTierFlags(int *pTierA, int *pTierB, int *pTierC);
extern void __cdecl initBlocksRva009B3EC0(void *self);
extern void __cdecl initBlocksRva009B3E40(void *self);

typedef int (__cdecl *Fn009A8430)();
typedef void (__cdecl *Fn009A5AA0)(void *, void *, void *, int);

// BFME2 data addresses drifted from BFME1 (0x013571E0/0x0134C6D8/0x01141D08/
// 0x01141D88); declared extern so the objects carry DIR32 slots the gate
// patches with the retail BFME2 bytes (0x00E23300/0x00DFD950/0x00BD7E60/
// 0x00BD7EE0). Values are sacrificial, like the g_rva01142408 pair below.
extern int g_rva00E23300;
extern int g_bfmeSharedJX;
extern int g_rva00DFD950[];
extern const short g_rva00BD7E60[];
extern const short g_rva00BD7EE0[];

// Rva009A4D00Init (90B @0x001B57D0) needs these same four addresses as
// immediate constants: the extern spellings above emit lea-form address
// materialization (93B) where retail uses mov-imm form (90B). The immediates
// are the retail BFME2 bytes, verified by the gate, not guesses.
static int *const g_00E23300 = (int *)&g_bfmeSharedJX;
static int *const g_00DFD950 = (int *)0x00DFD950;
static const short *const g_00BD7E60 = (const short *)0x00BD7E60;
static const short *const g_00BD7EE0 = (const short *)0x00BD7EE0;

typedef void (__cdecl *Rva009A8550Fn)(void *);
extern Rva009A8550Fn volatile g_rva01356DA0;
extern "C" void __cdecl VP6_BuildQuantIndex_Generic(void *quantizer);

// g_rva01142408: matched references place it at VA 0xbd8560; retail contents, sized to the
// 0x200-byte gap before the next known global there.
int g_rva01142408[128] = {
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23,
	24, 25, 26, 27, 28, 29, 30, 31,
	32, 33, 34, 35, 36, 37, 38, 39,
	40, 41, 42, 43, 44, 45, 46, 47,
	48, 49, 50, 51, 52, 53, 54, 55,
	56, 57, 58, 59, 60, 61, 62, 63,
	0, 1, 5, 6, 14, 15, 27, 28,
	2, 4, 7, 13, 16, 26, 29, 42,
	3, 8, 12, 17, 25, 30, 41, 43,
	9, 11, 18, 24, 31, 40, 44, 53,
	10, 19, 23, 32, 39, 45, 52, 54,
	20, 22, 33, 38, 46, 51, 55, 60,
	21, 34, 37, 47, 50, 56, 59, 61,
	35, 36, 48, 49, 57, 58, 62, 63,
};
extern int g_rva01142308[];
struct Rva009A6600Context { unsigned char prefix[0x13c]; int *table; unsigned char cells[64]; };

// Retail [0x009A8550, 0x009A859F): choose the codec block initializer for
// the detected CPU tier.  The generic body is the direct retail target at
// RVA 0x009A6600; its complete 37-byte body is verified above.
void Rva009A8550Init(void)
{
	int tierC;
	int tierA;
	int tierB;

	bfmeQueryCpuTierFlags(&tierA, &tierB, &tierC);

	if (tierC != 0)
	{
		g_rva01356DA0 = (Rva009A8550Fn)&initBlocksRva009B3EC0;
		return;
	}

	if (tierA != 0)
	{
		g_rva01356DA0 = (Rva009A8550Fn)&initBlocksRva009B3E40;
	}
	else
	{
		g_rva01356DA0 = (Rva009A8550Fn)&initBlocksRva009B3E40;
		g_rva01356DA0 = (Rva009A8550Fn)&VP6_BuildQuantIndex_Generic;
	}
}

void Rva009A4D00Init(void)
{
	*g_00E23300 = reinterpret_cast<Fn009A8430>(d_009a8430)();
	Rva009A8550Init();

	int *dst = g_00DFD950;
	for (const short *src = g_00BD7E60; (int)src < (int)g_00BD7EE0; ++src, ++dst)
		*dst = *src / 2 + 2;

	reinterpret_cast<Fn009A5AA0>(d_009a5aa0)(g_00DFD950, g_00DFD950, g_00DFD950, 7);
	InitVPUtil();
}
