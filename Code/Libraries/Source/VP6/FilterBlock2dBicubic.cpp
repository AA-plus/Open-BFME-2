// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d72d0.md 001d7d90.md and
// 001b8280.md plus retail only. No decoder source was consulted.
//
// Separable bicubic 8x8 two-pass filters (retail 0x001D72D0 MMX,
// 0x001D7D90 SSE2, 0x001B8280 generic): a horizontal pass over eleven rows
// starting one line above the source into a pitch-8 buffer, then a vertical
// pass from buffer row 1 into the output.

extern "C" void __cdecl FilterBlock1d_h_mmx(const void *, void *, int, int, int, int, const void *); // 0x001D6C90
extern "C" void __cdecl FilterBlock1d_v_mmx(const void *, void *, int, int, int, int, const void *); // 0x001D6D70
extern "C" void __cdecl FilterBlock1d_h_wmt(const void *, void *, int, int, int, int, const void *); // 0x001D7820
extern "C" void __cdecl FilterBlock1d_v_wmt(const void *, void *, int, int, int, int, const void *); // 0x001D78C0
extern "C" void __cdecl FilterBlock2dFirstPass(int, int *, void *, int, int, int, void *); // 0x001B8100
extern "C" void __cdecl FilterBlock2dSecondPass(int *, void *, int, int, int, int, void *); // 0x001B81C0 FilterBlock2dSecondPass

// Retail 0x00DFDA58: the generic filter's scratch rows (8 dwords per row).
int g_bfmeTableC7E0;
// Retail 0x00DFDA78: scratch row 1.
int g_bfmeTableC800;

// RVA 0x001D72D0
extern "C" void __cdecl FilterBlock2d_mmx(const void *source, void *output,
	int pixelsPerLine, const void *horizontalTaps, const void *verticalTaps)
{
	unsigned char scratch[256];

	FilterBlock1d_h_mmx((const unsigned char *)source - pixelsPerLine, scratch,
		pixelsPerLine, 1, 11, 8, horizontalTaps);
	FilterBlock1d_v_mmx(scratch + 8, output, 8, 8, 8, 8, verticalTaps);
}

// RVA 0x001D7D90
extern "C" void __cdecl FilterBlock2d_wmt(const unsigned char *source, unsigned char *output,
	int pixelsPerLine, const void *horizontalTaps, const void *verticalTaps)
{
	unsigned char scratch[256];

	FilterBlock1d_h_wmt(source - pixelsPerLine, scratch, pixelsPerLine, 1, 11, 8, horizontalTaps);
	FilterBlock1d_v_wmt(scratch + 8, output, 8, 8, 8, 8, verticalTaps);
}

// RVA 0x001B8280
extern "C" void __cdecl FilterBlock2d(void *source, void *output,
	void *pixelsPerLine, void *horizontalTaps, void *verticalTaps)
{
	FilterBlock2dFirstPass((char *)source - (char *)pixelsPerLine, &g_bfmeTableC7E0, pixelsPerLine,
		1, 11, 8, horizontalTaps);
	FilterBlock2dSecondPass(&g_bfmeTableC800, output, 8, 8, 8, 8, verticalTaps);
}
