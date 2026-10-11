// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b9f90.md plus retail only.
// No decoder source was consulted.
//
// HorizontalLine_3_5_Scale_C (retail 0x001B9F90, 265 bytes): upsamples a line
// by 5/3. Each group of three source pixels yields five outputs with the
// 3-to-5 weights; the final group repeats its last source pixel at the right
// edge instead of blending with a following group.

// RVA 0x001B9F90
extern "C" void __cdecl HorizontalLine_3_5_Scale_C(const void *source, int bytes, void *destination)
{
	const unsigned char *src = (const unsigned char *)source;
	unsigned char *dst = (unsigned char *)destination;
	int remaining = bytes - 3;

	if (remaining != 0)
	{
		unsigned int groups = (unsigned int)(remaining - 1) / 3 + 1;
		do
		{
			unsigned int first = src[0];
			unsigned int second = src[1];
			dst[0] = (unsigned char)first;
			dst[1] = (unsigned char)((first * 102 + second * 154 + 128) >> 8);

			unsigned int third = src[2];
			dst[2] = (unsigned char)((second * 205 + third * 51 + 128) >> 8);
			dst[3] = (unsigned char)((second * 51 + third * 205 + 128) >> 8);

			unsigned int fourth = src[3];
			dst[4] = (unsigned char)((third * 154 + fourth * 102 + 128) >> 8);
			src += 3;
			dst += 5;
			--groups;
		}
		while (groups != 0);
	}

	unsigned int first = src[0];
	unsigned int second = src[1];
	dst[0] = (unsigned char)first;
	dst[1] = (unsigned char)((first * 102 + second * 154 + 128) >> 8);

	unsigned int third = src[2];
	dst[2] = (unsigned char)((second * 205 + third * 51 + 128) >> 8);
	dst[3] = (unsigned char)((second * 51 + third * 205 + 128) >> 8);
	dst[4] = (unsigned char)third;
}
