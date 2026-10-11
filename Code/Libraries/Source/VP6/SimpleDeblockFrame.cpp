// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c4100.md plus retail only.
// No decoder source was consulted.
//
// SimpleDeblockFrame (retail 0x001C4100, 503 bytes): three-plane deblock of
// a frame with the simple filters. The context offsets are the plane layout
// shared with DeblockFrame (m_mode 0x00, m_tableIndex 0x0C, m_planeY/U/V
// 0x78/0x7C/0x80, m_width 0x90, m_height 0x94, m_strideY 0x98, m_strideUV
// 0x9C). The two bounding tables are retail .rdata/.bss data; the two filters
// are dispatch slots 9 (VA 0x00E22FA0) and 25 (VA 0x00E22FE0) of the codec
// dispatch table at VA 0x00E22F7C.

extern "C" void * __cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

struct Rva009B3800Context
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
	unsigned int m_scratchCount;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_strideY;
	unsigned int m_strideUV;
};

typedef void (__cdecl *Rva009B3800Filter)(
	Rva009B3800Context *, unsigned char *, unsigned int, int *);

extern int *g_rva01356A9C;
// g_rva011428E8: matched references place it at VA 0xbd8a48; retail contents, sized to the
// 0x238-byte gap before the next known global there.
int g_rva011428E8[142] = {
	30, 25, 20, 20, 15, 15, 14, 14,
	13, 13, 12, 12, 11, 11, 10, 10,
	9, 9, 8, 8, 7, 7, 7, 7,
	6, 6, 6, 6, 5, 5, 5, 5,
	4, 4, 4, 4, 3, 3, 3, 3,
	2, 2, 2, 2, 2, 2, 2, 2,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 2, 3, 4, 5, 7, 11,
	19, 35, 67, 0, -1, 0, 1, 1,
	1, 2, 2, 2, 2, 2, 2, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 0,
};
struct Rva009ACC40State;
extern int (__cdecl *g_rva01356E64)(Rva009ACC40State *, int);
// The two filters are slots 9 (VA 0x00E22FA0) and 25 (VA 0x00E22FE0) of the
// codec dispatch table at VA 0x00E22F7C that PostProcMachineSpecificConfig
// (PostProcMachineSpecificConfig.cpp) defines and fills.
typedef void (__cdecl *BfmeDispatchFn)();
struct BfmeCodecDispatchTable
{
	BfmeDispatchFn slot[26];
};
extern BfmeCodecDispatchTable g_bfmeCodecDispatch;
#define g_rva01356E84 (*(Rva009B3800Filter *)&g_bfmeCodecDispatch.slot[9])
#define g_rva01356EC4 (*(Rva009B3800Filter *)&g_bfmeCodecDispatch.slot[25])

extern "C" void __cdecl SimpleDeblockFrame(
	Rva009B3800Context *ctx, int sourceOffset, int destinationOffset)
{
	unsigned char *base = 0;
	int firstCount = (int)ctx->m_width;
	int secondCount = (int)ctx->m_height;
	int plane;
	int *bounding;
	unsigned int stride = 0;
	int mode = ctx->m_mode;
	int tableIndex = ctx->m_tableIndex;
	int selector;

	if (mode >= 2)
		selector = g_rva01356A9C[tableIndex];
	else
		selector = g_rva011428E8[tableIndex];

	bounding = (int *)g_rva01356E64((Rva009ACC40State *)ctx, selector);

	plane = 0;
	do
	{
		switch (plane)
		{
		case 0:
			firstCount = (int)ctx->m_width;
			secondCount = (int)ctx->m_height;
			stride = ctx->m_strideY;
			base = ctx->m_planeY;
			break;
		case 1:
			firstCount = (int)(ctx->m_width >> 1);
			secondCount = (int)(ctx->m_height >> 1);
			stride = ctx->m_strideUV;
			base = ctx->m_planeU;
			break;
		case 2:
			firstCount = (int)(ctx->m_width >> 1);
			secondCount = (int)(ctx->m_height >> 1);
			stride = ctx->m_strideUV;
			base = ctx->m_planeV;
			break;
		}

		unsigned char *dest = base + destinationOffset;
		memcpy(dest, base + sourceOffset, stride * 8);

		if (firstCount > 1)
		{
			unsigned char *cursor = dest + 6;
			int count = firstCount - 1;
			do
			{
				g_rva01356E84(ctx, cursor, stride, bounding);
				cursor += 8;
				--count;
			}
			while (count != 0);
		}

		base = base + stride * 8;

		if (secondCount > 1)
		{
			int rows = secondCount - 1;
			do
			{
				unsigned char *rowDest = base + destinationOffset;
				memcpy(rowDest, base + sourceOffset, stride * 8);
				g_rva01356EC4(ctx, rowDest, stride, bounding);

				if (firstCount > 1)
				{
					unsigned char *cursor = rowDest + 8;
					int count = firstCount - 1;
					do
					{
						g_rva01356E84(ctx, cursor - 2, stride, bounding);
						g_rva01356EC4(ctx, cursor, stride, bounding);
						cursor += 8;
						--count;
					}
					while (count != 0);
				}

				base = base + stride * 8;
				--rows;
			}
			while (rows != 0);
		}

		++plane;
	}
	while (plane < 3);
}
