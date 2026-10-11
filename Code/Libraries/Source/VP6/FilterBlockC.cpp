// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b8560.md plus retail only.
// No decoder source was consulted.
//
// FilterBlock_C (retail 0x001B8560, 993 bytes): cdecl scalar sub-pixel block
// predictor into a 16-bit block. Orders the two reference pointers then
// picks the one-dimensional bicubic or two-tap pass for a difference of one
// or a pitch and the two-dimensional pass for pitch -1 or pitch +1. The
// weight tables are defined here.

extern const int g_012D7798[8][4] =
{
	{ 0, 128, 0, 0 }, { -4, 118, 16, -2 }, { -7, 106, 34, -5 }, { -8, 90, 53, -7 },
	{ -8, 72, 72, -8 }, { -7, 53, 90, -8 }, { -5, 34, 106, -7 }, { -2, 16, 118, -4 }
};
extern const int g_012D7818[8][2] =
{
	{ 128, 0 }, { 112, 16 }, { 96, 32 }, { 80, 48 },
	{ 64, 64 }, { 48, 80 }, { 32, 96 }, { 16, 112 }
};

extern "C" void __cdecl FilterBlock1d(const unsigned char *, unsigned short *,
	unsigned int, unsigned int, unsigned int, unsigned int, const int *);
extern "C" void __cdecl FilterBlock2d(void *, void *, void *, void *, void *);
extern "C" void __cdecl FilterBlock2dBil(
	const unsigned char *, unsigned short *, int, const int *, const int *);

// Two-tap 8-bit to 16-bit filter; retail inlines it (standalone copy at 0x009A7870).
static void TwoTapFilter(
	const unsigned char *source,
	unsigned short *destination,
	unsigned int sourcePitch,
	unsigned int pixelStep,
	unsigned int rows,
	unsigned int columns,
	const int *weights)
{
	unsigned int row;
	unsigned int column;
	for (row = 0; row < rows; row++)
	{
		for (column = 0; column < columns; column++)
		{
			destination[column] = (unsigned short)(
				(source[pixelStep] * weights[1] + source[0] * weights[0] + 0x40) >> 7);
			source++;
		}
		source += sourcePitch - columns;
		destination += columns;
	}
}

extern "C" void __cdecl FilterBlock_C(
	const unsigned char *source1,
	const unsigned char *source2,
	unsigned short *destination,
	unsigned int sourcePitch,
	int modeX,
	int modeY,
	int useBicubic)
{
	int diff = source2 - source1;
	if (diff < 0)
	{
		const unsigned char *temp = source1;
		source1 = source2;
		source2 = temp;
		diff = source2 - source1;
	}

	if (diff == 1)
	{
		if (useBicubic)
			FilterBlock1d(source1, destination, sourcePitch, 1, 8, 8, g_012D7798[modeX]);
		else
			TwoTapFilter(source1, destination, sourcePitch, 1, 8, 8, g_012D7818[modeX]);
	}
	else if (diff == (int)sourcePitch)
	{
		if (useBicubic)
			FilterBlock1d(source1, destination, sourcePitch, sourcePitch, 8, 8, g_012D7798[modeY]);
		else
			TwoTapFilter(source1, destination, sourcePitch, sourcePitch, 8, 8, g_012D7818[modeY]);
	}
	else if (diff == (int)(sourcePitch - 1))
	{
		if (useBicubic)
			FilterBlock2d((void *)(source1 - 1), destination, (void *)sourcePitch,
				(void *)g_012D7798[modeX], (void *)g_012D7798[modeY]);
		else
			FilterBlock2dBil(source1 - 1, destination, sourcePitch, g_012D7818[modeX], g_012D7818[modeY]);
	}
	else if (diff == (int)(sourcePitch + 1))
	{
		if (useBicubic)
			FilterBlock2d((void *)source1, destination, (void *)sourcePitch,
				(void *)g_012D7798[modeX], (void *)g_012D7798[modeY]);
		else
			FilterBlock2dBil(source1, destination, sourcePitch, g_012D7818[modeX], g_012D7818[modeY]);
	}
}
