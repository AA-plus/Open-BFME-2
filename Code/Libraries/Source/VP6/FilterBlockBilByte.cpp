// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b8950.md and 001b89c0.md plus retail only. No decoder
// source was consulted.
//
// Bilinear two-tap filters with byte outputs (retail 0x001B8950 from byte samples
// and 0x001B89C0 from dword samples): (weight0 * sample + weight1 * sample one step
// after + 64) >> 7, low 8 bits stored; the output advances by width per row.

// RVA 0x001B8950
extern "C" void __cdecl FilterBlock1dBil_8(
	const unsigned char *source,
	unsigned char *destination,
	int sourcePitch,
	int startIndex,
	int rows,
	int columns,
	const int *weights)
{
	if ((unsigned int)rows > 0)
	{
		unsigned int rowCount = (unsigned int)rows;
		const unsigned char *sourcePointer = source;
		do
		{
			unsigned int column = 0;
			if ((unsigned int)columns > 0)
			{
				do
				{
					int value = sourcePointer[startIndex] * weights[1];
					value += sourcePointer[0] * weights[0];
					value = (value + 0x40) >> 7;
					destination[column] = (unsigned char)value;
					++sourcePointer;
					++column;
				}
				while (column < (unsigned int)columns);
			}
			sourcePointer += sourcePitch - columns;
			destination += columns;
			--rowCount;
		}
		while (rowCount != 0);
	}
}

// RVA 0x001B89C0
extern "C" void __cdecl FilterBlock2dBil_SecondPass_8(
	int *table,
	unsigned char *destination,
	int sourcePitch,
	int startIndex,
	int rows,
	int columns,
	const int *weights)
{
	if ((unsigned int)rows > 0)
	{
		int sourceStride = (sourcePitch - columns) * 4;
		unsigned int rowCount = (unsigned int)rows;
		int *source = table;
		do
		{
			unsigned int column = 0;
			if ((unsigned int)columns > 0)
			{
				do
				{
					int value = source[startIndex] * weights[1];
					value += source[0] * weights[0];
					value = (value + 0x40) >> 7;
					destination[column] = (unsigned char)value;
					++source;
					++column;
				}
			while (column < (unsigned int)columns);
			}
			source = (int *)((char *)source + sourceStride);
			destination += columns;
		}
		while (--rowCount != 0);
	}
}
