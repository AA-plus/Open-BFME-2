// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001b6ba0.md plus retail only.
// No decoder source was consulted.
//
// PostProcess (retail 0x001B6BA0, 1192 bytes): cdecl post-process dispatcher.
// Stores its nine control arguments in the post-processor context (+0x00 to
// +0x20) and dispatches on the level (0..8) to the deblock and dering
// passes (UpdateFragQIndex, DeblockFrame, DeblockFrameInterlaced,
// SimpleDeblockFrame, DeringFrame, DeringFrameInterlaced) and the Y copy and
// noise slots of the codec dispatch table at 0x00E22F7C (Y copy is slot 3 and
// noise is slot 0). Field reloads after calls and the separate m_c0 tails
// preserve retail codegen. The body is carried unchanged from the
// byte-identical Open-BFME-1 project donor; the context view is a scoped view
// of the offsets the retail body reads.

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

struct BfmeGridZJ;
struct Rva009AF200Context;
struct Rva009AF320Context;
struct Rva009B3800Context;
extern "C" void __cdecl UpdateFragQIndex(BfmeGridZJ *);
extern "C" void __cdecl DeblockFrame(Rva009AF200Context *, int, int);
extern "C" void __cdecl DeblockFrameInterlaced(Rva009AF320Context *, int, int);
extern "C" void __cdecl SimpleDeblockFrame(Rva009B3800Context *, int, int);

struct Rva009A6130Context;
void __cdecl d_009a8c50(void);
#define Rva009A8C50(c, f) ((void (__cdecl *)(Rva009A6130Context *, unsigned char *))d_009a8c50)((c), (f))
extern "C" void __cdecl DeringFrame(Rva009A6130Context *, unsigned char *, unsigned char *);
extern "C" void __cdecl DeringFrameInterlaced(Rva009A6130Context *, unsigned char *, unsigned char *);

typedef void (__cdecl *Rva009A6130CopyY)(unsigned char *, unsigned char *,
	unsigned int, unsigned int, unsigned int);
typedef void (__cdecl *Rva009A6130Noise)(unsigned char *, unsigned int,
	unsigned int, unsigned int, int);
typedef void (__cdecl *BfmeDispatchFn)();
struct BfmeCodecDispatchTable
{
	BfmeDispatchFn slot[26];
};
extern BfmeCodecDispatchTable g_bfmeCodecDispatch;
#define COPY_Y ((Rva009A6130CopyY)g_bfmeCodecDispatch.slot[3])
#define NOISE ((Rva009A6130Noise)g_bfmeCodecDispatch.slot[0])

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
	unsigned char m_pad24[0x6c - 0x24];
	void *m_6c;
	unsigned char m_pad70[0x78 - 0x70];
	unsigned int m_planeY;
	unsigned int m_planeU;
	unsigned int m_planeV;
	unsigned char m_pad84[0x90 - 0x84];
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_strideY;
	unsigned char m_pad9c[0xbc - 0x9c];
	unsigned char *m_bc;
	void *m_c0;
	void *m_c4;
};

// The landed helpers each declare their own view of this context.
#define FILL(c) UpdateFragQIndex((BfmeGridZJ *)(c))
#define AF200(c, a, b) DeblockFrame((Rva009AF200Context *)(c), (int)(a), (int)(b))
#define AF320(c, a, b) DeblockFrameInterlaced((Rva009AF320Context *)(c), (int)(a), (int)(b))
#define B3800(c, a, b) SimpleDeblockFrame((Rva009B3800Context *)(c), (int)(a), (int)(b))

extern "C" void __cdecl PostProcess(Rva009A6130Context *ctx, int mode, int a3,
	int level, int tableIndex, unsigned char *source, unsigned char *destination,
	unsigned char *a8, int a9, int a10)
{
	ctx->m_mode = mode;
	ctx->m_04 = a3;
	ctx->m_level = level;
	ctx->m_tableIndex = tableIndex;
	ctx->m_source = source;
	ctx->m_destination = destination;
	ctx->m_18 = a8;
	ctx->m_1c = a9;
	ctx->m_20 = a10;

	switch (ctx->m_level)
	{
	case 8:
		FILL(ctx);
		if (ctx->m_mode < 2)
		{
			AF200(ctx, ctx->m_source, ctx->m_destination);
		}
		else if (ctx->m_6c && ctx->m_c0)
		{
			B3800(ctx, ctx->m_source, ctx->m_bc);
			unsigned int bytes = ctx->m_height * ctx->m_strideY * 2;
			memcpy(ctx->m_destination + ctx->m_planeU, ctx->m_bc + ctx->m_planeU, bytes);
			memcpy(ctx->m_destination + ctx->m_planeV, ctx->m_bc + ctx->m_planeV, bytes);
			COPY_Y(ctx->m_bc + ctx->m_planeY, ctx->m_destination + ctx->m_planeY,
				ctx->m_width << 3, ctx->m_height << 3, ctx->m_strideY);
		}
		else
		{
			B3800(ctx, ctx->m_source, ctx->m_destination);
		}
		break;

	case 6:
	case 5:
		if (ctx->m_mode < 5)
			FILL(ctx);
		else if (ctx->m_6c)
		{
			if (!ctx->m_c0)
			{
				AF320(ctx, ctx->m_source, ctx->m_destination);
				Rva009A8C50(ctx, ctx->m_destination);
				DeringFrameInterlaced(ctx, ctx->m_destination, ctx->m_destination);
			}
			else
			{
				AF320(ctx, ctx->m_source, ctx->m_bc);
				Rva009A8C50(ctx, ctx->m_bc);
				DeringFrameInterlaced(ctx, ctx->m_bc, ctx->m_bc);
				unsigned int bytes = ctx->m_height * ctx->m_strideY * 2;
				memcpy(ctx->m_destination + ctx->m_planeU, ctx->m_bc + ctx->m_planeU, bytes);
				memcpy(ctx->m_destination + ctx->m_planeV, ctx->m_bc + ctx->m_planeV, bytes);
				COPY_Y(ctx->m_bc + ctx->m_planeY, ctx->m_destination + ctx->m_planeY,
					ctx->m_width << 3, ctx->m_height << 3, ctx->m_strideY);
			}
			break;
		}
		AF200(ctx, ctx->m_source, ctx->m_destination);
		Rva009A8C50(ctx, ctx->m_destination);
		DeringFrame(ctx, ctx->m_destination, ctx->m_destination);
		if (ctx->m_c4)
			NOISE(ctx->m_destination + ctx->m_planeY, ctx->m_width << 3,
				ctx->m_height << 3, ctx->m_strideY, tableIndex);
		break;

	case 7:
		if (ctx->m_mode >= 5)
		{
			if (ctx->m_6c)
			{
				if (!ctx->m_c0)
				{
					AF320(ctx, ctx->m_source, ctx->m_destination);
				}
				else
				{
					AF320(ctx, ctx->m_source, ctx->m_bc);
					unsigned int bytes = ctx->m_height * ctx->m_strideY * 2;
					memcpy(ctx->m_destination + ctx->m_planeU, ctx->m_bc + ctx->m_planeU, bytes);
					memcpy(ctx->m_destination + ctx->m_planeV, ctx->m_bc + ctx->m_planeV, bytes);
					COPY_Y(ctx->m_bc + ctx->m_planeY, ctx->m_destination + ctx->m_planeY,
						ctx->m_width << 3, ctx->m_height << 3, ctx->m_strideY);
				}
				break;
			}
		}
		else
			FILL(ctx);
		AF200(ctx, ctx->m_source, ctx->m_destination);
		Rva009A8C50(ctx, ctx->m_destination);
		DeringFrame(ctx, ctx->m_destination, ctx->m_destination);
		break;

	case 4:
		if (ctx->m_mode >= 5)
		{
			if (ctx->m_6c)
			{
				if (!ctx->m_c0)
				{
					AF320(ctx, ctx->m_source, ctx->m_destination);
				}
				else
				{
					AF320(ctx, ctx->m_source, ctx->m_bc);
					unsigned int bytes = ctx->m_height * ctx->m_strideY * 2;
					memcpy(ctx->m_destination + ctx->m_planeU, ctx->m_bc + ctx->m_planeU, bytes);
					memcpy(ctx->m_destination + ctx->m_planeV, ctx->m_bc + ctx->m_planeV, bytes);
					COPY_Y(ctx->m_bc + ctx->m_planeY, ctx->m_destination + ctx->m_planeY,
						ctx->m_width << 3, ctx->m_height << 3, ctx->m_strideY);
				}
				break;
			}
		}
		else
			FILL(ctx);
		AF200(ctx, ctx->m_source, ctx->m_destination);
		break;

	case 1:
		FILL(ctx);
		break;

	case 0:
		if (ctx->m_6c && ctx->m_c0)
		{
			unsigned int bytes = ctx->m_height * ctx->m_strideY * 2;
			memcpy(ctx->m_destination + ctx->m_planeU, ctx->m_source + ctx->m_planeU, bytes);
			memcpy(ctx->m_destination + ctx->m_planeV, ctx->m_source + ctx->m_planeV, bytes);
			COPY_Y(ctx->m_source + ctx->m_planeY, ctx->m_destination + ctx->m_planeY,
				ctx->m_width << 3, ctx->m_height << 3, ctx->m_strideY);
		}
		break;

	case 2:
	case 3:
	default:
		AF200(ctx, ctx->m_source, ctx->m_destination);
		Rva009A8C50(ctx, ctx->m_destination);
		DeringFrame(ctx, ctx->m_destination, ctx->m_destination);
		break;
	}
}
