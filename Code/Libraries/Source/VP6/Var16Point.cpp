// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001d8a30.md plus retail only.
// No decoder source was consulted.
// Var16Point retail 0x001D8A30 (130 bytes): variance style mismatch metric
// over the 16 samples at columns 0, 2, 4, 6 of rows 0, 2, 4, 6 of an 8x8
// block: ((Q << 4) - S * S) >> 8 with S the sum and Q the sum of squares.
extern "C" unsigned int __cdecl Var16Point(const unsigned char *block, int stride)
{
	unsigned int squareSum = 0;
	int y = 0;
	const unsigned char *p = block;
	unsigned int sum = 0;

	while (y < 8) {
		sum += p[0] + p[2] + p[4] + p[6];
		squareSum += p[0] * p[0] + p[2] * p[2]
			+ p[4] * p[4] + p[6] * p[6];
		p += 2 * stride;
		y += 2;
	}

	return (16 * squareSum - sum * sum) >> 8;
}
