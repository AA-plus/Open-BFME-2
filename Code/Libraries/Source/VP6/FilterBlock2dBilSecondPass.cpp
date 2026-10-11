// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b83b0.md plus retail only.
// No decoder source was consulted.
// FilterBlock2dBil_SecondPass retail 0x001B83B0 (127 bytes): two-tap filter
// over 32-bit intermediates, (w0 * entry + w1 * entry[step] + 64) >> 7
// stored as 16 bits.
extern "C" void __cdecl FilterBlock2dBil_SecondPass(const int *source,
	unsigned short *output, int entriesPerLine, int step, int height, int width,
	const int *weights)
{
	if ((unsigned int)height > 0)
	{
		int sourceStride = (entriesPerLine - width) * 4;
		unsigned int rowCount = (unsigned int)height;
		const int *row = source;
		do
		{
			unsigned int column = 0;
			if ((unsigned int)width > 0)
			{
				do
				{
					int value = row[step] * weights[1];
					value += row[0] * weights[0];
					value = (value + 0x40) >> 7;
					output[column] = (unsigned short)value;
					++row;
					++column;
				}
				while (column < (unsigned int)width);
			}
			row = (const int *)((const char *)row + sourceStride);
			output = (unsigned short *)((char *)output + width * 2);
		}
		while (--rowCount != 0);
	}
}
