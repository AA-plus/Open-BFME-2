// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b82d0.md and 001b8340.md plus retail only. No decoder
// source was consulted.
//
// Bilinear two-tap filters with wide outputs (retail 0x001B82D0 16-bit and
// 0x001B8340 32-bit): (weight0 * sample + weight1 * sample one step after + 64)
// >> 7 per column; the source advances one byte per column then by (pixels per
// line - width) per row.

// RVA 0x001B82D0
extern "C" void __cdecl FilterBlock1dBil(
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

// RVA 0x001B8340
extern "C" void __cdecl FilterBlock2dBil_FirstPass(const unsigned char *source, int *destination,
                int sourcePitch, int startIndex, int rows, int columns,
                const int *weights)
{
    if ((unsigned)rows > 0) {
        unsigned rowCount = (unsigned)rows;
        do {
            unsigned column = 0;
            if ((unsigned)columns > 0) {
                do {
                    int value = source[startIndex] * weights[1];
                    value += source[0] * weights[0];
                    destination[column] = (value + 0x40) >> 7;
                    ++source;
                    ++column;
                } while (column < (unsigned)columns);
            }
            source += sourcePitch - columns;
            destination += columns;
        } while (--rowCount != 0);
    }
}
