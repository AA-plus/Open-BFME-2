// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b8050.md plus retail only. No
// decoder source was consulted.
//
// FilterBlock1d (retail 0x001B8050): four-tap one-dimensional filter from an
// 8-bit source into 16-bit samples. Each output is the weighted sum of the
// pixels one step before, at, one and two steps after, plus 64, shifted
// right 7 and clamped to 0..255. The sum is written in retail's evaluation
// order.

// RVA 0x001B8050
extern "C" void __cdecl FilterBlock1d(
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
	int value;
	for (row = 0; row < rows; row++)
	{
		for (column = 0; column < columns; column++)
		{
			value = (source[2 * pixelStep] * weights[3] + source[0] * weights[1] +
				source[pixelStep] * weights[2] + source[-(int)pixelStep] * weights[0] + 0x40) >> 7;
			if (value < 0)
				value = 0;
			else if (value > 255)
				value = 255;
			destination[column] = (unsigned short)value;
			source++;
		}
		source += sourcePitch - columns;
		destination += columns;
	}
}
