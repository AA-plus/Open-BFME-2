// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001bfd10.md plus retail only.
// No decoder source was consulted.
//
// DeblockFrameInterlaced (retail 0x001BFD10, 368 bytes): builds the deblock
// bounding array for the frame Q index (generic builder for version >= 2,
// else the platform pointer), zeroes the fragment variances, then deblocks
// the Y plane as two fields (line step twice the stride, the variance pointer
// advanced for the odd field) and the U and V planes with their own scales.


extern "C" void * __cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

struct Rva009ACBA0Context;
extern "C" int *__cdecl SetupDeblockValueArray_Generic(Rva009ACBA0Context *ctx, int flimit);

extern int *g_rva01356A9C;
struct Rva009ACC40State;
extern int (__cdecl *g_rva01356E64)(Rva009ACC40State *, int);
extern const unsigned int *g_rva01356AA0;
extern const unsigned int *g_rva01356A98;

struct Rva009AF320Context;
extern "C" void __cdecl DeblockPlaneNew(Rva009AF320Context *, unsigned, int, unsigned, unsigned, unsigned char *, unsigned char *, const unsigned int *);

struct Rva009AF320Context
{
	int m_mode;
	unsigned char m_pad04[8];
	int m_tableIndex;
	unsigned char m_pad10[0x28 - 0x10];
	unsigned char *m_scratch;
	unsigned char m_pad2C[0x38 - 0x2C];
	int *m_bounding;
	unsigned char m_pad3C[0x78 - 0x3C];
	unsigned char *m_planeY;
	unsigned char *m_planeU;
	unsigned char *m_planeV;
	int m_extra84;
	int m_extra88;
	unsigned m_scratchCount;
	unsigned m_width;
	unsigned m_height;
	unsigned m_strideY;
	unsigned m_strideUV;
};

extern "C" void __cdecl DeblockFrameInterlaced(Rva009AF320Context *ctx, int a, int b)
{
	int *bound;
	if (ctx->m_mode >= 2) {
		int value = g_rva01356A9C[ctx->m_tableIndex];
		bound = SetupDeblockValueArray_Generic(
			(Rva009ACBA0Context *)ctx, value);
	} else {
		int value = g_rva01356A9C[ctx->m_tableIndex];
		bound = (int *)g_rva01356E64(
			(Rva009ACC40State *)ctx, value);
	}

	unsigned char *saved = ctx->m_scratch;
	int aa = a;
	ctx->m_bounding = bound;
	memset(saved, 0, ctx->m_scratchCount * 4);

	DeblockPlaneNew(
		ctx,
		ctx->m_strideY << 1,
		0,
		ctx->m_width,
		ctx->m_height >> 1,
		ctx->m_planeY + aa,
		ctx->m_planeY + b,
		g_rva01356AA0);

	{
		unsigned h = ctx->m_height;
		unsigned w = ctx->m_width;
		unsigned bytes = w * h;
		bytes = bytes / 2;
		bytes = bytes * 4;
		ctx->m_scratch += bytes;
	}

	DeblockPlaneNew(
		ctx,
		ctx->m_strideY << 1,
		0,
		ctx->m_width,
		ctx->m_height >> 1,
		ctx->m_planeY + ctx->m_strideY + aa,
		ctx->m_planeY + ctx->m_strideY + b,
		g_rva01356AA0);

	ctx->m_scratch = saved;

	DeblockPlaneNew(
		ctx,
		ctx->m_strideUV,
		ctx->m_extra84,
		ctx->m_width >> 1,
		ctx->m_height >> 1,
		ctx->m_planeU + aa,
		ctx->m_planeU + b,
		g_rva01356A98);

	DeblockPlaneNew(
		ctx,
		ctx->m_strideUV,
		ctx->m_extra84 + ctx->m_extra88,
		ctx->m_width >> 1,
		ctx->m_height >> 1,
		ctx->m_planeV + aa,
		ctx->m_planeV + b,
		g_rva01356A98);
}
