// cl: /DNDEBUG /MD /EHsc
// Clean room: reverse/vp6_cleanroom/specs/001bb5f0.md and 001bb6c0.md plus
// retail only. No decoder source was consulted.
// Debug overlay helpers (retail 0x001BB5F0 and 0x001BB6C0): both print into
// the luma plane through vp6_xprintf.

extern "C" int vp6_xprintf(void *pbi, int offset, const char *format, ...);

// Retail 0x00BD8800 (76 bytes): the statistics format string.
// g_rva011426A0 was the retail address of this format string (RVA 0x007D8800); the literal itself is the source.

struct ShowInfoInstance
{
	unsigned char pad000[0x13C];
	int *quantizer;                  // 0x13C
	unsigned char pad140[0x160 - 0x140];
	int boolDecoderPosition;         // 0x160
	unsigned char pad164[0x19C - 0x164];
	unsigned char version;           // 0x19C
	unsigned char pad19D[0x1A0 - 0x19D];
	int level;                       // 0x1A0
	unsigned char pad1A4[0x1AC - 0x1A4];
	unsigned char frameType;         // 0x1AC
	unsigned char pad1AD[0x1B8 - 0x1AD];
	int yStride;                     // 0x1B8
	unsigned char pad1BC[0x1E8 - 0x1BC];
	int frameSize;                   // 0x1E8
	unsigned char pad1EC[0x1F4 - 0x1EC];
	int verticalFragments;           // 0x1F4
	int horizontalFragments;         // 0x1F8
	unsigned char pad1FC[0x22C - 0x1FC];
	int macroblockRows;              // 0x22C
	int macroblockColumns;           // 0x230
	unsigned char pad234[0x698 - 0x234];
	int refreshGolden;               // 0x698
	unsigned char pad69C[0x6F0 - 0x69C];
	unsigned char *predictionModes;  // 0x6F0
	unsigned char pad6F4[0x914 - 0x6F4];
	int averageDecodeTime;           // 0x914
	unsigned char pad918[0x938 - 0x918];
	int averagePostProcessTime;      // 0x938
	int pad93C;
	unsigned int averageBlitTime;    // 0x940
};

// RVA 0x001BB5F0
extern "C" void __cdecl vp6_showinfo2(ShowInfoInstance *pbi)
{
	vp6_xprintf(
		pbi,
		((pbi->yStride + 1) * 3) << 4,
		"F:%d G:%d Q:%d S:%d B: %d W:%d H:%d V:%d Decode:%8d, Blit:%8d, PP:%8d, P:%d",
		pbi->frameType,
		pbi->refreshGolden,
		*pbi->quantizer,
		pbi->frameSize,
		pbi->boolDecoderPosition,
		pbi->horizontalFragments,
		pbi->verticalFragments,
		pbi->version,
		pbi->averageDecodeTime,
		pbi->averageBlitTime,
		pbi->averagePostProcessTime,
		pbi->level);
}

// RVA 0x001BB6C0
extern "C" void __cdecl vp6_showinfo(ShowInfoInstance *pbi)
{
	unsigned int rows = pbi->macroblockRows;
	unsigned int columns = pbi->macroblockColumns;
	unsigned int row = 0;

	if (rows > 0)
	{
		int rowOffset = 5;
		do
		{
			unsigned int column = 0;
			if (columns > 0)
			{
				unsigned int columnOffset = 0;
				do
				{
					int value = ((const signed char *)pbi->predictionModes)[pbi->macroblockColumns * row + column];
					int offset = pbi->yStride * rowOffset + columnOffset + 5;
					vp6_xprintf(pbi, offset, "%d", value);
					++column;
					columnOffset += 0x10;
				} while (column < columns);
			}
			++row;
			rowOffset += 0x10;
		} while (row < rows);
	}
}
