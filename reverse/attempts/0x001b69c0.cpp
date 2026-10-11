// _PlaneAddNoise_C
// partial score=0.6 date=2026-10-11
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b69c0.md plus retail only.
// No decoder source was consulted.
#include <stdlib.h>
#include <math.h>

static double gaussian(double sigma, double mu, double x)
{
	return exp(-((x - mu) * (x - mu)) / (sigma * sigma + sigma * sigma)) / (sigma * sqrt(6.2831853));
}

extern "C" void __cdecl PlaneAddNoise_C(unsigned char *start, unsigned width, unsigned height, int pitch, int q)
{
	signed char dist[300];
	unsigned char noise[2048];
	double sigma = 1 + 0.012698412698412698 * (63 - q);
	int next = 0;
	double x;
	unsigned i;
	for (x = -32; x < 32; x++) {
		int count = (int)(256 * gaussian(sigma, 0, x) + 0.5);
		if (count) {
			int k;
			for (k = 0; k < count; k++)
				dist[next + k] = (signed char)(int)x;
			next += k;
		}
	}
	for (; next < 256; next++)
		dist[next] = 0;
	int k;
	for (k = 0; k < 2048; k++)
		noise[k] = dist[rand() & 0xff];
	signed char first = dist[0];
	unsigned char *row = start;
	while (height) {
		unsigned char *n = &noise[rand() & 0xff];
		unsigned j;
		for (j = 0; j < width; j++) {
			unsigned char *p = row + j;
			if (*p < -first) *p = (unsigned char)-first;
			if (*p > 255 - first) *p = (unsigned char)(255 - first);
			*p += n[j];
		}
		row += pitch;
		height--;
	}
}
