// _DeringBlockWeak_C
// partial score=0.724770642201835 date=2026-10-13
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: approved specs 001c22c0 and 001c1ad0 plus the complete retail body.
// No external decoder source was consulted.
// Full weak deringing: all weights precede output; immediate pixel stores retain
// retail overlapping-buffer behavior. Horizontal source and weight pointers
// improve byte alignment; vertical and output register/slot shape remain nonexact.
// Normal mismatch compile:1485 versus1526 bytes, frame0x160, first difference+15.
// 288 observed differential cases match retail and an independent spec oracle;
// not exhaustive behavior or byte identity. Existing sharpen global reused.
extern "C" int Vp6FilterEdgeTagTable[];

extern "C" void __cdecl DeringBlockWeak_C(void *instance, const unsigned char *source,
	unsigned char *destination, int pitch, int qIndex, const int *scaleTable)
{
	int quality = scaleTable[qIndex];
	int sharpen = Vp6FilterEdgeTagTable[qIndex];
	const unsigned char *above = source - pitch;
	const unsigned char *below = source + pitch;
	int cap = 3 * quality;
	short vertical[72];
	short horizontal[72];
	int r;
	int c;

	if (cap > 24)
		cap = 24;

	for (r = 0; r < 9; r++) {
		for (c = 0; c < 8; c++) {
			int difference = source[(r - 1) * pitch + c + pitch] - source[(r - 1) * pitch + c];
			int weight;
			if (difference <= 0)
				difference = source[(r - 1) * pitch + c] - source[(r - 1) * pitch + c + pitch];
			weight = quality + 2 * (16 - difference);
			if (weight < -64)
				weight = sharpen;
			else if (weight < 0)
				weight = 0;
			else if (weight > cap)
				weight = cap;
			vertical[r * 8 + c] = (short)weight;
		}
	}
	const unsigned char *hrow = source;
	short *hweight = horizontal;
	for (r = 8; r != 0; --r) {
		for (c = 0; c < 9; c++) {
			int difference = hrow[c] - hrow[c - 1];
			int weight;
			if (difference <= 0) difference = hrow[c - 1] - hrow[c];
			weight = quality + 2 * (16 - difference);
			if (weight < -64) weight = sharpen;
			else if (weight < 0) weight = 0;
			else if (weight > cap) weight = cap;
			hweight[c] = (short)weight;
		}
		hrow += pitch;
		hweight += 9;
	}

	for (r = 0; r < 8; r++) {
		for (c = 0; c < 8; c++) {
			int up = vertical[r * 8 + c];
			int down = vertical[r * 8 + c + 8];
			int left = horizontal[r * 9 + c];
			int right = horizontal[r * 9 + c + 1];
			int value = ((128 - right - down - up - left) * source[r * pitch + c]
				+ down * below[r * pitch + c] + left * source[r * pitch + c - 1]
				+ right * source[r * pitch + c + 1] + up * above[r * pitch + c] + 64) >> 7;
			if (value < 0)
				value = 0;
			else if (value > 255)
				value = 255;
			destination[r * pitch + c] = (unsigned char)value;
		}
	}
}
