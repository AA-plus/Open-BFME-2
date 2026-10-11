// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b7fc0.md plus retail only.
// No decoder source was consulted.
// Copy12x12_C retail 0x001B7FC0 (113 bytes): 12 rows of 12 bytes, each side
// advancing by its own stride. Unreferenced in retail (the dispatch table
// always installs the MMX version).
extern "C" void __cdecl Copy12x12_C(const unsigned char *source,
	unsigned char *destination, int sourceStride, int destinationStride)
{
	destination += 2;
	source += 2;
	int rows = 12;
	do
	{
		destination[-2] = source[-2];
		destination[-1] = source[-1];
		destination[0] = source[0];
		destination[1] = source[1];
		destination[2] = source[2];
		destination[3] = source[3];
		destination[4] = source[4];
		destination[5] = source[5];
		destination[6] = source[6];
		destination[7] = source[7];
		destination[8] = source[8];
		destination[9] = source[9];
		source += sourceStride;
		destination += destinationStride;
	} while (--rows);
}
