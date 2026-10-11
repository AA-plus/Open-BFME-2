// _UpdateUMVBorder
// partial score=0.3 date=2026-10-11
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b96a0.md plus retail only.
// No decoder source was consulted.
#include <string.h>
#pragma intrinsic(memcpy, memset)

struct PostProcInstanceUmv
{
	unsigned char pad0[0x78];
	int reconYOffset;  // 0x78
	int reconUOffset;  // 0x7C
	int reconVOffset;  // 0x80
	unsigned char pad1[0x90 - 0x84];
	int horizFrags;    // 0x90
	int vertFrags;     // 0x94
	int yStride;       // 0x98
	int uvStride;      // 0x9C
	unsigned char pad2[0xB4 - 0xA0];
	int border;        // 0xB4
};

static void ExtendPlane(unsigned char *left, int rows, int width, int stride, int border, unsigned char *bufTop, int topRows)
{
	int i;
	unsigned char *right = left + width - 1;
	unsigned char *dst = left - border;
	unsigned char *rdst = right + 1;
	for (i = rows; i > 0; i--) {
		memset(dst, *left, border);
		memset(rdst, *right, border);
		left += stride;
		right += stride;
		dst += stride;
		rdst += stride;
	}
}

extern "C" void __cdecl UpdateUMVBorder(PostProcInstanceUmv *pbi, unsigned char *buf)
{
	int rows = pbi->vertFrags * 8;
	int stride = pbi->yStride;
	int border = pbi->border;
	unsigned char *left = buf + pbi->reconYOffset;
	unsigned char *right = left + pbi->horizFrags * 8 - 1;
	unsigned char *dst = left - border;
	unsigned char *rdst = right + 1;
	int i;
	for (i = rows; i > 0; i--) {
		memset(dst, *left, border);
		memset(rdst, *right, border);
		left += stride;
		right += stride;
		dst += stride;
		rdst += stride;
	}
	{
		unsigned char *first = buf + stride * border;
		unsigned char *last = first + (pbi->vertFrags * 8 - 1) * stride;
		unsigned char *bot = last + stride;
		unsigned char *top = buf;
		for (i = border; i > 0; i--) {
			memcpy(top, first, stride);
			memcpy(top + (bot - buf), last, stride);
			top += stride;
		}
	}
}
