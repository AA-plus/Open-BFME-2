// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bc390.md 001c01f0.md 001b6970.md
// plus retail only. No decoder source was consulted.
#include <math.h>

extern unsigned char g_bfmeVp6SelectorMap[40]; // 0x00BD8D00 mode-to-frame table

struct MacroblockInfo
{
	int pad0;
	const unsigned short *coefficients; // 0x04
	unsigned int mode;                  // 0x08
	void *blockModes[1];                // 0x0C
};

struct BlockContext
{
	unsigned char pad0[4];
	void *blockMode;           // 0x04
	unsigned short frame;      // 0x08
	unsigned short dc;         // 0x0A
};

// RVA 0x001BC390
extern "C" void __cdecl VP6_UpdateContext(MacroblockInfo *mb, BlockContext *context, unsigned int block)
{
	context->blockMode = mb->blockModes[block];
	context->dc = mb->coefficients[block * 64];
	context->frame = ((const unsigned short *)g_bfmeVp6SelectorMap)[mb->mode * 2];
}

// RVA 0x001C01F0
extern "C" int __cdecl Bound(int limit, int value)
{
	int mask = value >> 31;
	int magnitude = (value ^ mask) - mask;
	int below = (magnitude < limit + limit) ? 1 : 0;
	int t = below * magnitude - limit;
	int tmask = t >> 31;
	int abst = (t ^ tmask) - tmask;
	int r = -abst;
	r = r + mask;
	r = r + limit;
	r = r ^ mask;
	return r;
}

// RVA 0x001B6970
extern "C" double __cdecl gaussian(double sigma, double mu, double x)
{
	return exp(-((x - mu) * (x - mu)) / (sigma * sigma + sigma * sigma)) / (sigma * sqrt(6.2831853));
}
