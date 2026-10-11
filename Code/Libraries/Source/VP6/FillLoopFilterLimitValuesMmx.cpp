// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d1610.md plus retail only.
// No decoder source was consulted.
//
// FillLoopFilterLimitValues_MMX retail 0x001D1610..0x001D1648 (57 bytes),
// cdecl and argument free. Expands the active 64-entry loop-filter limit
// table (pointer at retail 0x00E22CE0) for the SIMD filters: the low 16 bits
// of entry i are written four times at 0x00E229E0 + 8i. The data ledger
// names both globals today.
extern int *g_bfmeFilterLimit;

// The expanded table this routine fills: 256 16-bit entries (four per limit),
// .bss VA 0x00E229E0; the next referenced datum starts 0x200 bytes later.
// Owned here since the placeholder unit that defined it was retired.
unsigned short Rva009C0D10Table[0x100];

extern "C" void __cdecl FillLoopFilterLimitValues_MMX()
{
	const int *limits = g_bfmeFilterLimit;
	for (int i = 0; i < 64; ++i) {
		Rva009C0D10Table[4 * i] = (unsigned short)limits[i];
		Rva009C0D10Table[4 * i + 1] = (unsigned short)limits[i];
		Rva009C0D10Table[4 * i + 2] = (unsigned short)limits[i];
		Rva009C0D10Table[4 * i + 3] = (unsigned short)limits[i];
	}
}
