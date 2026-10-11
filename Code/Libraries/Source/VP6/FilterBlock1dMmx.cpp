// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d7080.md plus retail only. No decoder
// source was consulted.
//
// MMX vertical two-tap filter (retail 0x001D7080): eight outputs per row, weight
// group 0 times the sample plus weight group 1 times the sample one row below,
// plus 64, shifted right 7 and packed to bytes with unsigned saturation. The MMX
// state is left in use for the caller to clear.

extern const unsigned short g_bfmeBinkRoundMmx[8]; // 0x009B81A0 eight 16-bit 64 (rounding)

// RVA 0x001D7080
extern "C" void __cdecl FilterBlock1d_vb8_mmx(const void *source, void *destination,
	int sourceStride, int unused, int count, int destinationStride,
	const void *weights)
{
	__asm
	{
		mov edi, weights
		movq mm1, qword ptr [edi]
		movq mm2, qword ptr [edi + 10h]
		mov edx, sourceStride
		mov edi, destination
		mov esi, source
		mov ecx, count
		mov eax, destinationStride
		pxor mm0, mm0
	rvaNext:
		movq mm3, qword ptr [esi]
		punpcklbw mm3, mm0
		pmullw mm3, mm1
		movq mm4, qword ptr [esi + edx]
		punpcklbw mm4, mm0
		pmullw mm4, mm2
		paddw mm3, mm4
		paddw mm3, g_bfmeBinkRoundMmx
		psraw mm3, 7
		packuswb mm3, mm0
		movd dword ptr [edi], mm3
		movq mm3, qword ptr [esi + 4]
		punpcklbw mm3, mm0
		pmullw mm3, mm1
		movq mm4, qword ptr [esi + edx + 4]
		punpcklbw mm4, mm0
		pmullw mm4, mm2
		paddw mm3, mm4
		paddw mm3, g_bfmeBinkRoundMmx
		psraw mm3, 7
		packuswb mm3, mm0
		movd dword ptr [edi + 4], mm3
		add esi, edx
		add edi, eax
		dec ecx
		jne rvaNext
	}
}
