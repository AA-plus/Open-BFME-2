// _DeringBlockStrong_C
// partial score=0.09 date=2026-10-13
// _DeringBlockStrong_C
// partial score=0.09 date=2026-10-13
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c1ad0.md plus retail only.
// No decoder source was consulted.
extern "C" int Vp6FilterEdgeTagTable[];

extern "C" void __cdecl DeringBlockStrong_C(void *instance, const unsigned char *source,
	unsigned char *destination, int pitch, int qIndex, const int *scaleTable)
{
	int quality = scaleTable[qIndex];
	int sharpen = Vp6FilterEdgeTagTable[qIndex];
	int cap = 3 * quality;
	short vertical[72];
	short horizontal[72];
	int r;
	int c;

	if (cap > 32)
		cap = 32;

	for (r = 0; r < 9; r++) {
		const unsigned char *pair = source + (r - 1) * pitch;
		short *weights = vertical + r * 8;
		for (c = 0; c < 8; c += 4) {
			int w0, w1, w2, w3;
			int d0 = pair[c + pitch] - pair[c];
			int d1 = pair[c + 1 + pitch] - pair[c + 1];
			int d2 = pair[c + 2 + pitch] - pair[c + 2];
			int d3 = pair[c + 3 + pitch] - pair[c + 3];
			if (d0 <= 0) d0 = pair[c] - pair[c + pitch];
			if (d1 <= 0) d1 = pair[c + 1] - pair[c + 1 + pitch];
			if (d2 <= 0) d2 = pair[c + 2] - pair[c + 2 + pitch];
			if (d3 <= 0) d3 = pair[c + 3] - pair[c + 3 + pitch];
			w0 = quality + 32 - d0;
			w1 = quality + 32 - d1;
			w2 = quality + 32 - d2;
			w3 = quality + 32 - d3;
			if (w0 < -64) w0 = sharpen; else if (w0 < 0) w0 = 0; else if (w0 > cap) w0 = cap;
			if (w1 < -64) w1 = sharpen; else if (w1 < 0) w1 = 0; else if (w1 > cap) w1 = cap;
			if (w2 < -64) w2 = sharpen; else if (w2 < 0) w2 = 0; else if (w2 > cap) w2 = cap;
			if (w3 < -64) w3 = sharpen; else if (w3 < 0) w3 = 0; else if (w3 > cap) w3 = cap;
			weights[c] = (short)w0;
			weights[c + 1] = (short)w1;
			weights[c + 2] = (short)w2;
			weights[c + 3] = (short)w3;
		}
	}

	const unsigned char *hrow = source;
	short *hweight = horizontal;
	for (r = 8; r != 0; --r) {
		for (c = 0; c < 9; c += 3) {
			int w0, w1, w2;
			int d0 = hrow[c] - hrow[c - 1];
			int d1 = hrow[c + 1] - hrow[c];
			int d2 = hrow[c + 2] - hrow[c + 1];
			if (d0 <= 0) d0 = hrow[c - 1] - hrow[c];
			if (d1 <= 0) d1 = hrow[c] - hrow[c + 1];
			if (d2 <= 0) d2 = hrow[c + 1] - hrow[c + 2];
			w0 = quality + 32 - d0;
			w1 = quality + 32 - d1;
			w2 = quality + 32 - d2;
			if (w0 < -64) w0 = sharpen; else if (w0 < 0) w0 = 0; else if (w0 > cap) w0 = cap;
			if (w1 < -64) w1 = sharpen; else if (w1 < 0) w1 = 0; else if (w1 > cap) w1 = cap;
			if (w2 < -64) w2 = sharpen; else if (w2 < 0) w2 = 0; else if (w2 > cap) w2 = cap;
			hweight[c] = (short)w0;
			hweight[c + 1] = (short)w1;
			hweight[c + 2] = (short)w2;
		}
		hrow += pitch;
		hweight += 9;
	}

	const unsigned char *above = source - pitch;
	const unsigned char *below = source + pitch;
	for (r = 0; r < 8; r++) {
		int temp[8];
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
			temp[c] = value;
		}
		for (c = 0; c < 8; c++)
			destination[r * pitch + c] = (unsigned char)temp[c];
	}
}
