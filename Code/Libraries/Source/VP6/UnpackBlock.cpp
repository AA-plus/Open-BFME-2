// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b7cf0.md plus retail only. No
// decoder source was consulted.
//
// Widens an 8x8 byte block to 64 packed 16-bit values (retail 0x001B7CF0);
// the source advances by the line step per row, the output by eight values.

// RVA 0x001B7CF0
extern "C" void __cdecl UnpackBlock_C(const unsigned char *src, unsigned short *dst, int srcStride)
{
	int rows = 8;
	do
	{
		dst[0] = src[0];
		dst[1] = src[1];
		dst[2] = src[2];
		dst[3] = src[3];
		dst[4] = src[4];
		dst[5] = src[5];
		dst[6] = src[6];
		dst[7] = src[7];
		src += srcStride;
		dst += 8;
	} while (--rows);
}
