// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b8100.md plus retail only. No
// decoder source was consulted.
//
// FilterBlock2dFirstPass (retail 0x001B8100): the FilterBlock1d four-tap
// computation from an 8-bit source, with the clamped results stored as
// 32-bit values.

// RVA 0x001B8100
extern "C" void __cdecl FilterBlock2dFirstPass(
	int sourceAddress, int *table, void *sourcePitch, int sourceDelta,
	int rows, int columns, void *weights)
{
	const int *coefficient = (const int *)weights;
	const unsigned char *&source = *(const unsigned char **)&sourceAddress;
	for (unsigned int row = 0; row < (unsigned int)rows; ++row)
	{
		unsigned int column = 0;
		if ((unsigned int)columns > 0)
		do
		{
			const unsigned char *previous = source - sourceDelta;
			int value = source[sourceDelta + sourceDelta] * coefficient[3];
			value += source[0] * coefficient[1];
			value += source[sourceDelta] * coefficient[2];
			value = (value + previous[0] * coefficient[0] + 0x40) >> 7;
			if (value < 0)
				value = 0;
			else if (value > 0xFF)
				value = 0xFF;
			++source;
			table[column] = value;
			++column;
		}
		while (column < (unsigned int)columns);
		source += (int)sourcePitch - columns;
		table += columns;
	}
}
