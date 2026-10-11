// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d76e0.md and 001d45f0.md plus
// retail only. No decoder source was consulted.
//
// AverageBlock_MMX (retail 0x001D76E0) and MMX_idct1 (retail 0x001D45F0).
// The average leaves the MMX state in use: the separately installed ClearMmx
// is the caller's cleanup. The vector body is inline assembly inside an
// ordinary C function, as ReconMmx.cpp does.

extern "C" void *__cdecl memset(void *block, int value, unsigned int bytes);
#pragma intrinsic(memset)

// RVA 0x001D76E0: output words = (reference1 + reference2) >> 1, 8x8.
extern "C" void __cdecl AverageBlock_MMX(const void *reference1, const void *reference2,
	void *output, int pixelsPerLine)
{
	__asm
	{
		mov esi, reference1
		mov eax, reference2
		mov edi, output
		mov ecx, 8
		mov edx, pixelsPerLine
		pxor mm7, mm7
	nextRow:
		movq mm0, qword ptr [esi]
		movq mm1, qword ptr [eax]
		movq mm2, mm0
		punpcklbw mm0, mm7
		movq mm3, mm1
		punpcklbw mm1, mm7
		paddw mm0, mm1
		punpckhbw mm2, mm7
		psraw mm0, 1
		punpckhbw mm3, mm7
		paddw mm2, mm3
		movq qword ptr [edi], mm0
		psraw mm2, 1
		add esi, edx
		add eax, edx
		add edi, 10h
		movq qword ptr [edi - 8], mm2
		dec ecx
		jne nextRow
	}
}

// RVA 0x001D45F0: DC-only inverse transform.
extern "C" void __cdecl MMX_idct1(const short *input, const short *quantizer, short *output)
{
	short dc = input[0];

	if (dc != 0)
	{
		unsigned int value = ((quantizer[0] * dc + 15) >> 5) & 0xffff;
		unsigned int *row = (unsigned int *)output;
		int i;

		value *= 0x10001;
		for (i = 8; i != 0; --i)
		{
			row[0] = value;
			row[1] = value;
			row[2] = value;
			row[3] = value;
			row += 4;
		}
	}
	else
	{
		memset(output, 0, 128);
	}
}
