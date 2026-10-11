// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c74b0.md plus retail only. No
// decoder source was consulted.
//
// ClampLevels_C retail 0x001C74B0 (204 bytes): generic luma level clamp.
// Builds a 256-entry byte lookup (identity, with entries below the black
// clamp raised to it and entries above 255 - white clamp lowered to that),
// then translates the luma plane region of the fifth argument's buffer into
// the fourth argument's buffer, width = blocks across * 8, height = blocks
// down * 8, one luma stride per row.

struct POSTPROC_LEVELS
{
	unsigned char m_pad00[0x78];
	unsigned char *m_plane;   // 0x78 luma plane offset in a frame buffer
	unsigned char m_pad7C[0x14];
	int m_width;              // 0x90 luma blocks across
	int m_height;             // 0x94 luma blocks down
	int m_stride;             // 0x98 luma stride
};

extern "C" void __cdecl ClampLevels_C(POSTPROC_LEVELS *context,
	int lowerLimit, int upperLimit, int destinationOffset, int sourceOffset)
{
	register unsigned char *destination = context->m_plane + destinationOffset;
	register int width = context->m_width << 3;
	register const unsigned char *source = context->m_plane + sourceOffset;
	int height = context->m_height << 3;
	int stride = context->m_stride;
	unsigned char table[256];

	for (int i = 0; i < 256; ++i)
	{
		table[i] = (unsigned char)i;
		if (i < lowerLimit)
			table[i] = (unsigned char)lowerLimit;
		if (i > 255 - upperLimit)
			table[i] = (unsigned char)(255 - upperLimit);
	}

	for (int row = 0; row < height; ++row)
	{
		for (int column = 0; column < width; ++column)
			destination[column] = table[source[column]];
		destination += stride;
		source += stride;
	}
}
