// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d6d70.md plus retail only. No decoder source was consulted.
// FilterBlock1d_v_mmx, retail RVA 0x001D6D70 (196 bytes).
//
// MMX sibling of FilterBlock1d_v_wmt: same four-tap vertical fixed-point
// filter (taps at -stride, 0, +stride, +stride*2), but each MMX register
// only holds four pixels, so the eight-pixel-wide strip is done as two
// four-pixel passes with their own qword store, and the rounding table is
// the shared MMX vector at BFME2 VA 0x00DB81A0.  Retail 0x009C6470, 196 bytes.

extern const unsigned short g_bfmeBinkRoundMmx[8];	// retail 0x00DB81A0

extern "C" void __cdecl FilterBlock1d_v_mmx(const void *source, void *destination,
	int sourceStride, int unused, int count, int destinationStride,
	const void *weights)
{
	__asm
	{
		mov edi, weights
		movq mm1, qword ptr [edi]
		movq mm2, qword ptr [edi + 10h]
		movq mm6, qword ptr [edi + 20h]
		movq mm7, qword ptr [edi + 30h]
		mov edx, sourceStride
		mov edi, destination
		mov esi, source
		sub esi, sourceStride
		mov ecx, count
		mov eax, destinationStride
		pxor mm0, mm0
	rvaNext:
		movq mm3, qword ptr [esi]
		punpcklbw mm3, mm0
		pmullw mm3, mm1
		add esi, edx
		movq mm4, qword ptr [esi + edx * 2]
		punpcklbw mm4, mm0
		pmullw mm4, mm7
		paddsw mm3, mm4
		movq mm4, qword ptr [esi]
		punpcklbw mm4, mm0
		pmullw mm4, mm2
		paddsw mm3, mm4
		movq mm4, qword ptr [esi + edx]
		punpcklbw mm4, mm0
		pmullw mm4, mm6
		paddsw mm3, mm4
		paddsw mm3, qword ptr g_bfmeBinkRoundMmx
		psraw mm3, 7
		packuswb mm3, mm0
		movd dword ptr [edi], mm3
		sub esi, edx
		movq mm3, qword ptr [esi + 4]
		punpcklbw mm3, mm0
		pmullw mm3, mm1
		add esi, edx
		movq mm4, qword ptr [esi + edx * 2 + 4]
		punpcklbw mm4, mm0
		pmullw mm4, mm7
		paddsw mm3, mm4
		movq mm4, qword ptr [esi + 4]
		punpcklbw mm4, mm0
		pmullw mm4, mm2
		paddsw mm3, mm4
		movq mm4, qword ptr [esi + edx + 4]
		punpcklbw mm4, mm0
		pmullw mm4, mm6
		paddsw mm3, mm4
		paddsw mm3, qword ptr g_bfmeBinkRoundMmx
		psraw mm3, 7
		packuswb mm3, mm0
		movd dword ptr [edi + 4], mm3
		add edi, eax
		dec ecx
		jne rvaNext
	}
}
