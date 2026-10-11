// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001ba320.md 001ba360.md 001ba4d0.md
// plus retail only. No decoder source was consulted.
// Generic C scaler callbacks of the image scaler dispatch table.

// RVA 0x001BA320: double a line, interleaving rounded neighbour averages.
extern "C" void __cdecl HorizontalLine_1_2_Scale_C(const void *source, int sourceWidth, void *destination, int destinationWidth)
{
	unsigned char *dst = (unsigned char *)destination;
	const unsigned char *src = (const unsigned char *)source;
	int remaining = sourceWidth - 1;
	if (remaining != 0)
	{
		do
		{
			unsigned int first = src[0];
			unsigned int second = src[1];
			dst[0] = (unsigned char)first;
			dst[1] = (unsigned char)((first + second + 1) >> 1);
			++src;
			dst += 2;
			--remaining;
		}
		while (remaining != 0);
	}
	unsigned int last = src[0];
	dst[0] = (unsigned char)last;
	dst[1] = (unsigned char)last;
}

// RVA 0x001BA360: row one pitch down becomes the average of rows 0 and 2 pitches.
extern "C" void __cdecl VerticalBand_1_2_Scale_C(unsigned char *band, int pitch, unsigned int width)
{
	unsigned char *cursor = band;
	while (width > 0)
	{
		unsigned int upper = cursor[0];
		unsigned int lower = cursor[pitch * 2];
		cursor[pitch] = (unsigned char)((upper + lower + 1) >> 1);
		++cursor;
		--width;
	}
}

// RVA 0x001BA4D0: 2-to-1 point-sampling downsampler.
extern "C" void __cdecl Scale1D_2t1_ps(unsigned char *source, int sourceStep, int sourceScale, int sourceLength, unsigned char *destination, int destinationStep, int destinationScale, int destinationLength)
{
	int step = sourceStep;
	int sourceDelta = step + step;
	int pitch = destinationStep;
	unsigned int limit = (unsigned int)pitch * (unsigned int)destinationLength;
	unsigned int offset = 0;
	if (limit > 0)
	{
		unsigned char *d = destination;
		unsigned char *s = source;
		do
		{
			*(unsigned char *)(offset + (unsigned int)d) = *s;
			offset += (unsigned int)pitch;
			s += sourceDelta;
		}
		while (offset < limit);
	}
}
