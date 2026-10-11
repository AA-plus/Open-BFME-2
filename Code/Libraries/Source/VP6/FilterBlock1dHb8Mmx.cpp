// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d6ff0.md plus retail only.
// No decoder source was consulted.
// FilterBlock1d_hb8_mmx retail 0x001D6FF0 (134 bytes): two-tap horizontal
// filter producing an 8 wide block. MMX instructions have no C form cl can
// emit, so the body is inline assembly inside an ordinary function. The MMX
// state is left in use on return (the separately installed clear routine is
// the caller cleanup).

// Retail 0x00DB81A0: eight 16-bit rounding values of 64.
extern const unsigned short g_bfmeBinkRoundMmx[8];

extern "C" void __cdecl FilterBlock1d_hb8_mmx(const void *source, void *output,
	int sourcePixelsPerLine, int pixelStep, int outputHeight, int outputWidth,
	const void *taps)
{
	__asm
	{
		mov edi, taps
		movq mm1, qword ptr [edi]
		movq mm2, qword ptr [edi + 10h]
		mov edi, output
		mov esi, source
		mov ecx, outputHeight
		mov eax, outputWidth
		pxor mm0, mm0
	nextRow:
		movq mm3, qword ptr [esi]
		movq mm4, mm3
		punpcklbw mm3, mm0
		pmullw mm3, mm1
		psrlq mm4, 8
		movq mm5, mm4
		punpcklbw mm5, mm0
		pmullw mm5, mm2
		paddw mm3, mm5
		paddw mm3, g_bfmeBinkRoundMmx
		psraw mm3, 7
		packuswb mm3, mm0
		movd dword ptr [edi], mm3
		movq mm3, qword ptr [esi + 4]
		movq mm4, mm3
		punpcklbw mm3, mm0
		pmullw mm3, mm1
		psrlq mm4, 8
		movq mm5, mm4
		punpcklbw mm5, mm0
		pmullw mm5, mm2
		paddw mm3, mm5
		paddw mm3, g_bfmeBinkRoundMmx
		psraw mm3, 7
		packuswb mm3, mm0
		movd dword ptr [edi + 4], mm3
		add esi, sourcePixelsPerLine
		add edi, eax
		dec ecx
		jne nextRow
	}
}
