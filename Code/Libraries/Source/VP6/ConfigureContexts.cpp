// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c6da0.md plus retail only.
// No decoder source was consulted.
//
// VP6_ConfigureContexts (retail 0x001C6DA0, 331 bytes): after calling the
// system-state clear callback, derives the DC node contexts (instance offset
// 0x542, per plane three contexts of five bytes) from the DC probabilities
// (0x3A0, 11 per plane): ((probability * slope + 128) >> 8) + offset, clamped
// to 1..255, using the (slope, offset) line equations per (node, context).

// The type keeps its address-derived name: it is part of the ledger name of
// the table global below (?g_bfmeToneCoef@@3PAURva009B64A0Coef@@A).
struct Rva009B64A0Coef
{
	int m_scale;
	int m_bias;
};

extern Rva009B64A0Coef g_bfmeToneCoef[15];		// image 0x00BD9430
extern void (__cdecl *g_bfmeToneReady)();		// image 0x00E22D10

// g_bfmeToneCoef: sole definition so this file links (no other TU defines it).
Rva009B64A0Coef g_bfmeToneCoef[15];

#define DC_CONTEXT(dstIndex, srcIndex, tap)						\
	{															\
		int v = ((src[srcIndex] * g_bfmeToneCoef[tap * 3 + j].m_scale	\
				+ 0x80) >> 8) + g_bfmeToneCoef[tap * 3 + j].m_bias;	\
		if (v > 255)											\
			v = 255;											\
		else if (v < 1)											\
			v = 1;												\
		dst[dstIndex] = (unsigned char)v;						\
	}

// RVA 0x001C6DA0
extern "C" void __cdecl VP6_ConfigureContexts(unsigned char *pbi)
{
	g_bfmeToneReady();

	unsigned char *dst = pbi + 0x543;
	unsigned char *src = pbi + 0x3A1;
	int row;

	for (row = 2; row != 0; --row) {
		unsigned j;
		for (j = 0; j < 3; ++j) {
			DC_CONTEXT(-1, -1, 0)
			DC_CONTEXT(0, 0, 1)
			DC_CONTEXT(1, 1, 2)
			DC_CONTEXT(2, 2, 3)
			DC_CONTEXT(3, 3, 4)
			dst += 5;
		}
		src += 11;
	}
}
