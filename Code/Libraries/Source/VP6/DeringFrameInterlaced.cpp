// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c3440.md plus retail only.
// No decoder source was consulted.
//
// DeringFrameInterlaced (retail 0x001C3440, 1835 bytes): cdecl (post-processor
// instance / source frame / destination frame) interlaced dering pass. Two Y
// fields at doubled stride (the second one line down, the fragment-variance
// index carrying on), then U and V at half width. A variance above the third
// threshold (fourth for chroma) is strongly derung (twice more when a
// neighbour exceeds the fourth); otherwise strong, weak or a plain copy by
// the second and first thresholds. The kernels are the codec dispatch slots
// 0x01356EC0 (strong), 0x01356EA0 (weak) and 0x01356B44 (copy); the
// quantiser table is picked by m_mode. The body is carried unchanged from the
// byte-identical Open-BFME-1 project donor; it owns the two quantiser tables
// and the two kernel slot pointers.

struct Rva009A6130Context
{
	int m_mode;
	int m_04;
	int m_level;
	int m_tableIndex;
	unsigned char *m_source;
	unsigned char *m_destination;
	unsigned char *m_18;
	int m_1c;
	int m_20;
	unsigned char m_pad24[0x28 - 0x24];
	int *m_metric;
	unsigned char m_pad2c[0x78 - 0x2c];
	unsigned int m_planeY;
	unsigned int m_planeU;
	unsigned int m_planeV;
	unsigned char m_pad84[0x90 - 0x84];
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_strideY;
};

typedef void (__cdecl *Rva009B2A50Dering)(Rva009A6130Context *, unsigned char *,
	unsigned char *, int, int, const int *);
typedef void (__cdecl *Rva009B2A50Copy)(unsigned char *, unsigned char *, int);

// The two kernel slots are BFME 2 .bss 0x00E22FDC (strong) and 0x00E22FBC
// (weak), filled at run time.
Rva009B2A50Dering g_rva01356EC0;
Rva009B2A50Dering g_rva01356EA0;
extern void *g_bfmeSlotB44;
extern int g_rva01356940[64];

// The quantiser tables, read from BFME 2 .data 0x00DB7828 and 0x00DB7928.
int g_rva012D7F58[64] =
{
	9, 9, 8, 8, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2
};
int g_rva012D8058[64] =
{
	9, 9, 9, 9, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 7, 7,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5,
	4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 0, 0, 0, 0, 0
};

#define BLOCK_SRC (srcPtr + 8 * col)
#define BLOCK_DST (srcPtr + 8 * col + (dstPtr - srcPtr))
#define BLOCK_DST_FIRST (dstPtr + 8 * col)

extern "C" void __cdecl DeringFrameInterlaced(Rva009A6130Context *ctx, unsigned char *src, unsigned char *dst)
{
	int thresh1, thresh2, thresh3, thresh4;
	const int *table;
	int quality;
	unsigned char *srcPtr;
	unsigned char *dstPtr;
	unsigned int blocksAcross;
	unsigned int blocksDown;
	unsigned int index;
	unsigned int row;
	unsigned int col;
	unsigned int lineLength;

	quality = ctx->m_tableIndex;
	if (ctx->m_mode >= 5)
	{
		thresh1 = 0x180;
		thresh2 = 0x900;
		thresh3 = 0xb40;
		thresh4 = 0x1680;
	}
	else
	{
		thresh1 = 0x800;
		thresh2 = 0x7800;
		thresh3 = 0x16800;
		thresh4 = 0x1e000;
	}

	if (ctx->m_mode >= 5)
		table = g_rva012D8058;
	else if (ctx->m_mode >= 2)
		table = g_rva012D7F58;
	else
		table = g_rva01356940;

	// Y plane, first field.
	blocksAcross = ctx->m_width;
	blocksDown = ctx->m_height >> 1;
	srcPtr = src + ctx->m_planeY;
	dstPtr = dst + ctx->m_planeY;
	lineLength = ctx->m_strideY << 1;
	index = 0;

	for (row = 0; row < blocksDown; row++)
	{
		for (col = 0; col < blocksAcross; col++)
		{
			int variance = ctx->m_metric[index];
			if (ctx->m_level > 5 && variance > thresh3)
			{
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST_FIRST, lineLength, quality, table);
				if ((col > 0 && ctx->m_metric[index - 1] > thresh4) ||
					(col + 1 < blocksAcross && ctx->m_metric[index + 1] > thresh4) ||
					(row + 1 < blocksDown && ctx->m_metric[index + blocksAcross] > thresh4) ||
					(row > 0 && ctx->m_metric[index - blocksAcross] > thresh4))
				{
					g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST_FIRST, lineLength, quality, table);
					g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST_FIRST, lineLength, quality, table);
				}
			}
			else if (variance > thresh2)
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST_FIRST, lineLength, quality, table);
			else if (variance > thresh1)
				g_rva01356EA0(ctx, BLOCK_SRC, BLOCK_DST_FIRST, lineLength, quality, table);
			else
				((Rva009B2A50Copy)g_bfmeSlotB44)(BLOCK_SRC, BLOCK_DST_FIRST, lineLength);
			++index;
		}
		srcPtr += 8 * lineLength;
		dstPtr += 8 * lineLength;
	}

	// Y plane, second field.
	srcPtr = src + ctx->m_planeY + ctx->m_strideY;
	dstPtr = dst + ctx->m_planeY + ctx->m_strideY;

	for (row = 0; row < blocksDown; row++)
	{
		for (col = 0; col < blocksAcross; col++)
		{
			int variance = ctx->m_metric[index];
			if (ctx->m_level > 5 && variance > thresh3)
			{
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				if ((col > 0 && ctx->m_metric[index - 1] > thresh4) ||
					(col + 1 < blocksAcross && ctx->m_metric[index + 1] > thresh4) ||
					(row + 1 < blocksDown && ctx->m_metric[index + blocksAcross] > thresh4) ||
					(row > 0 && ctx->m_metric[index - blocksAcross] > thresh4))
				{
					g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
					g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				}
			}
			else if (variance > thresh2)
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else if (variance > thresh1)
				g_rva01356EA0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else
				((Rva009B2A50Copy)g_bfmeSlotB44)(BLOCK_SRC, BLOCK_DST, lineLength);
			++index;
		}
		srcPtr += 8 * lineLength;
		dstPtr += 8 * lineLength;
	}

	// U plane.
	blocksAcross >>= 1;
	srcPtr = src + ctx->m_planeU;
	dstPtr = dst + ctx->m_planeU;
	lineLength >>= 2;

	for (row = 0; row < blocksDown; row++)
	{
		for (col = 0; col < blocksAcross; col++)
		{
			int variance = ctx->m_metric[index];
			if (ctx->m_level > 5 && variance > thresh4)
			{
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			}
			else if (variance > thresh2)
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else if (variance > thresh1)
				g_rva01356EA0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else
				((Rva009B2A50Copy)g_bfmeSlotB44)(BLOCK_SRC, BLOCK_DST, lineLength);
			++index;
		}
		srcPtr += 8 * lineLength;
		dstPtr += 8 * lineLength;
	}

	// V plane.
	srcPtr = src + ctx->m_planeV;
	dstPtr = dst + ctx->m_planeV;

	for (row = 0; row < blocksDown; row++)
	{
		for (col = 0; col < blocksAcross; col++)
		{
			int variance = ctx->m_metric[index];
			if (ctx->m_level > 5 && variance > thresh4)
			{
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			}
			else if (variance > thresh2)
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else if (variance > thresh1)
				g_rva01356EA0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else
				((Rva009B2A50Copy)g_bfmeSlotB44)(BLOCK_SRC, BLOCK_DST, lineLength);
			++index;
		}
		srcPtr += 8 * lineLength;
		dstPtr += 8 * lineLength;
	}
}
