// ?bfmeClearAll@@YAXXZ, retail 0x006B5830 (53 bytes).
// BFME1 Bfme5SeventySeven.cpp donor, trimmed to bfmeClearAll; the file's
// other bodies live at other game.dat addresses and land separately.
// Retail-measured BFME2 repair: the four cleared tables bake to their
// BFME2 absolutes (the donor's externs carry the BFME1 addresses).

extern "C" void * __cdecl memset(void *destination, int value, unsigned int bytes);

#pragma intrinsic(memset)

// Address-derived dword buffers: bfmeClearAll's memset lengths establish the
// extents, and game.dat shows their initial bytes are all zero (.data/bss).
// The four nbench1 weight arrays (declared in nbench1.h, defined by the nbench1 unit).
extern double mid_wt_change[][35];
extern double mid_wt_cum_change[][35];
extern double out_wt_change[][8];
extern double out_wt_cum_change[][8];

// ?bfmeClearAll@@YAXXZ
void __cdecl bfmeClearAll(void)
{
	memset(mid_wt_change, 0, 0x230 * 4);
	memset(mid_wt_cum_change, 0, 0x230 * 4);
	memset(out_wt_change, 0, 0x80 * 4);
	memset(out_wt_cum_change, 0, 0x80 * 4);
}
