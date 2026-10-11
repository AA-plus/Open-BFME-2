// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d2680.md plus retail only.
// No decoder source was consulted.
//
// VerticalBand_1_2_Scale_MMX (retail 0x001D2680): row 1 of the band becomes
// the rounded-up average of rows 0 and 2, eight columns per step. The MMX
// state is left in use: the separately installed ClearMmx is the caller's
// cleanup. The vector body is inline assembly inside an ordinary C function.

// Retail 0x00BD9960: four 16-bit ones, the rounding addend. Also read by the
// expand kernel in Bfme5ThirtySix.cpp.
extern "C" __declspec(align(8)) const unsigned short g_bfmeRoundMmx[4] = { 1, 1, 1, 1 };

// RVA 0x001D2680
extern "C" void __cdecl VerticalBand_1_2_Scale_MMX(void *band, int pitch, int width)
{
	__asm
	{
		mov esi, band
		mov ecx, pitch
		pxor mm7, mm7
		mov edx, width
	nextColumns:
		movq mm0, [esi]
		movq mm1, [esi+ecx*2]
		movq mm2, mm0
		movq mm3, mm1
		punpcklbw mm0, mm7
		movq mm6, g_bfmeRoundMmx
		punpcklbw mm1, mm7
		paddw mm0, mm1
		punpckhbw mm2, mm7
		paddw mm0, mm6
		punpckhbw mm3, mm7
		paddw mm2, mm3
		psraw mm0, 1
		paddw mm2, mm6
		psraw mm2, 1
		packuswb mm0, mm2
		movq [esi+ecx], mm0
		add esi, 8
		sub edx, 8
		jg nextColumns
	}
}
