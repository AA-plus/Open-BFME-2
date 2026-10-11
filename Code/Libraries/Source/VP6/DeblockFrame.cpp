// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001bfbf0.md plus retail only.
// No decoder source was consulted.
//
// DeblockFrame (retail 0x001BFBF0, 278 bytes): zeroes the fragment variance
// array, builds the deblock bounding array (version >= 2) from the limit for
// the frame Q index, then deblocks the frame: with version >= 5 through
// DeblockPlaneNew for Y, U and V, otherwise through DeblockPlane for channels
// 0, 1 and 2. The two offsets are the source and destination frame offsets.

extern "C" void * __cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

struct Rva009ACBA0Context;
extern "C" int *__cdecl SetupDeblockValueArray_Generic(Rva009ACBA0Context *ctx, int flimit);

extern int *g_rva01356A9C;
extern const unsigned int *g_rva01356AA0;
extern const unsigned int *g_rva01356A98;

struct Rva009AF200Context;
extern "C" void __cdecl DeblockPlaneNew(Rva009AF200Context *, unsigned, int, unsigned, unsigned, unsigned char *, unsigned char *, const unsigned int *);
// Retail 0x001BF8D0 DeblockPlane (ledger name from its owning unit).
void copyPlane009AEEE0(Rva009AF200Context *, int, int, int);

struct Rva009AF200Context
{
	int m_mode;
	unsigned char m_pad04[8];
	int m_tableIndex;
	unsigned char m_pad10[0x28 - 0x10];
	void *m_scratch;
	unsigned char m_pad2C[0x38 - 0x2C];
	int *m_bounding;
	unsigned char m_pad3C[0x78 - 0x3C];
	unsigned char *m_planeY;
	unsigned char *m_planeU;
	unsigned char *m_planeV;
	unsigned char m_pad84[0x8C - 0x84];
	unsigned m_scratchCount;
	unsigned m_width;
	unsigned m_height;
	unsigned m_strideY;
	unsigned m_strideUV;
};

// RVA 0x001BFBF0
extern "C" void __cdecl DeblockFrame(Rva009AF200Context *ctx, int x, int y)
{
	memset(ctx->m_scratch, 0, ctx->m_scratchCount * 4);

	if (ctx->m_mode >= 2) {
		int value = g_rva01356A9C[ctx->m_tableIndex];
		ctx->m_bounding = SetupDeblockValueArray_Generic(
			(Rva009ACBA0Context *)ctx, value);
	}

	if (ctx->m_mode >= 5) {
		DeblockPlaneNew(
			ctx,
			ctx->m_strideY,
			0,
			ctx->m_width,
			ctx->m_height,
			ctx->m_planeY + x,
			ctx->m_planeY + y,
			g_rva01356AA0);
		DeblockPlaneNew(
			ctx,
			ctx->m_strideUV,
			0,
			ctx->m_width >> 1,
			ctx->m_height >> 1,
			ctx->m_planeU + x,
			ctx->m_planeU + y,
			g_rva01356A98);
		DeblockPlaneNew(
			ctx,
			ctx->m_strideUV,
			0,
			ctx->m_width >> 1,
			ctx->m_height >> 1,
			ctx->m_planeV + x,
			ctx->m_planeV + y,
			g_rva01356A98);
	} else {
		copyPlane009AEEE0(ctx, x, y, 0);
		copyPlane009AEEE0(ctx, x, y, 1);
		copyPlane009AEEE0(ctx, x, y, 2);
	}
}
