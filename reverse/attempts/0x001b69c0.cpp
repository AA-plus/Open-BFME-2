// PlaneAddNoise_C
// partial score=0.8 date=2026-10-13
// cl: /O2 /G6 /DNDEBUG /MD
#include <stdlib.h>
#include <math.h>

static void FillBytes(unsigned char *destination, unsigned char value, int count)
{
	int k;
	for (k = 0; k < count; k++)
		destination[k] = value;
}

extern "C" void __cdecl PlaneAddNoise_C(unsigned char *start, unsigned width, unsigned height, int pitch, int q)
{
	unsigned i;
	double sigma;
	double x;
	int next;
	signed char dist[300];
	unsigned char noise[2048];
	unsigned char *row;
	unsigned rows;

	sigma = 1 + 0.012698412698412698 * (63 - q);
	next = 0;
	for (x = -32; x < 32; x++) {
		int count = (int)(256 * (exp(-((x - 0) * (x - 0)) / (sigma * sigma + sigma * sigma)) / (sigma * sqrt(6.2831853))) + 0.5);
		if (count) {
			int k;
			for (k = 0; k < count; k++)
				dist[next + k] = (signed char)(int)x;
			next += k;
		}
	}
	for (; next < 256; next++)
		dist[next] = 0;
	for (i = 0; i < 2048; i++)
		noise[i] = dist[rand() & 0xff];
	signed char first = dist[0];
	signed char negFirst = -first;
	for (row = start, rows = height; rows; rows--) {
		unsigned char *src = row;
		unsigned char *noisePtr = &noise[rand() & 0xff];
		for (i = 0; i < width; i++) {
			if (src[i] < negFirst)
				src[i] = negFirst;
			if (src[i] > 255 - first)
				src[i] = 255 - first;
			src[i] += noisePtr[i];
		}
		row += pitch;
	}
}
