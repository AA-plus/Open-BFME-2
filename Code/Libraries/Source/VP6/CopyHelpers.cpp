// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001ba3a0.md 001b9bf0.md 001b8e70.md
// plus retail only. No decoder source was consulted.
extern "C" void *__cdecl memcpy(void *destination, const void *source, unsigned int bytes);
#pragma intrinsic(memcpy)

// RVA 0x001BA3A0: copy row zero into the row one pitch below, per column.
extern "C" void __cdecl LastVerticalBand_1_2_Scale_C(unsigned char *band, int pitch, unsigned int width)
{
	unsigned char *p = band;
	if (width > 0) {
		do { p[pitch] = *p; ++p; } while (--width);
	}
}

// RVA 0x001B9BF0: copy source width bytes; the destination width is unused.
extern "C" void __cdecl HorizontalLine_Copy(const void *source, unsigned int sourceWidth, void *destination, unsigned int destinationWidth)
{
	memcpy(destination, source, sourceWidth);
}

// RVA 0x001B8E70: serialise with cpuid, store the low time-stamp word.
extern "C" void __cdecl VP6_readTSC(unsigned int *out)
{
	unsigned int tsc;
	__asm {
		pushad
		cpuid
		rdtsc
		mov tsc, eax
		popad
	}
	*out = tsc;
}
