// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d7820.md and 001d78c0.md plus
// retail only. No decoder source was consulted.
//
// SSE2 four-tap one-dimensional filters (retail 0x001D7820 horizontal,
// 0x001D78C0 vertical): for each output row, eight outputs are the sums of
// four weighted samples (weights from the four 16-byte groups of the taps
// table), plus the rounding vector 64, shifted right 7 and packed to bytes
// with unsigned saturation. Horizontal taps apply to x-1, x, x+1, x+2 and are
// extracted from two unaligned loads with byte shifts; vertical taps apply to
// the rows above, at, below and two below. 'pixelStep' is unused.

// Retail 0x009B84D0: eight 16-bit lanes of 64. SSE2 memory operands require
// 16-byte alignment.
extern __declspec(align(16)) const unsigned short g_bfmeBinkRound[8] = {
    64, 64, 64, 64, 64, 64, 64, 64
};

// RVA 0x001D7820
extern "C" void __cdecl FilterBlock1d_h_wmt(const void *source, void *destination,
	int sourceStride, int unused, int count, int destinationStride,
	const void *weights)
{
	__asm
	{
		mov edi, weights
		movdqa xmm1, [edi]
		movdqa xmm2, [edi + 10h]
		movdqa xmm6, [edi + 20h]
		movdqa xmm7, [edi + 30h]
		mov edi, destination
		mov esi, source
		dec esi
		mov ecx, count
		mov eax, destinationStride
		pxor xmm0, xmm0
	rvaNext:
		movdqu xmm3, [esi]
		movdqu xmm4, xmm3
		punpcklbw xmm3, xmm0
		pmullw xmm3, xmm1
		psrldq xmm4, 3
		movdqa xmm5, xmm4
		punpcklbw xmm5, xmm0
		pmullw xmm5, xmm7
		paddsw xmm3, xmm5
		movdqu xmm4, [esi + 1]
		movdqa xmm5, xmm4
		punpcklbw xmm5, xmm0
		pmullw xmm5, xmm2
		paddsw xmm3, xmm5
		psrldq xmm4, 1
		movdqa xmm5, xmm4
		punpcklbw xmm5, xmm0
		pmullw xmm5, xmm6
		paddsw xmm3, xmm5
		paddsw xmm3, g_bfmeBinkRound
		psraw xmm3, 7
		packuswb xmm3, xmm0
		movdq2q mm0, xmm3
		movq qword ptr [edi], mm0
		add esi, dword ptr sourceStride
		add edi, eax
		dec ecx
		jne rvaNext
	}
}

// RVA 0x001D78C0
extern "C" void __cdecl FilterBlock1d_v_wmt(const void *source, void *destination,
	int sourceStride, int unused, int count, int destinationStride,
	const void *weights)
{
	__asm
	{
		mov edi, weights
		movdqa xmm1, [edi]
		movdqa xmm2, [edi + 10h]
		movdqa xmm6, [edi + 20h]
		movdqa xmm7, [edi + 30h]
		mov edx, sourceStride
		mov edi, destination
		mov esi, source
		sub esi, sourceStride
		mov ecx, count
		mov eax, destinationStride
		pxor xmm0, xmm0
	rvaNext:
		movdqu xmm3, [esi]
		punpcklbw xmm3, xmm0
		pmullw xmm3, xmm1
		add esi, edx
		movdqu xmm4, [esi + edx * 2]
		punpcklbw xmm4, xmm0
		pmullw xmm4, xmm7
		paddsw xmm3, xmm4
		movdqu xmm4, [esi]
		punpcklbw xmm4, xmm0
		pmullw xmm4, xmm2
		paddsw xmm3, xmm4
		movdqu xmm4, [esi + edx]
		punpcklbw xmm4, xmm0
		pmullw xmm4, xmm6
		paddsw xmm3, xmm4
		paddsw xmm3, g_bfmeBinkRound
		psraw xmm3, 7
		packuswb xmm3, xmm0
		movdq2q mm0, xmm3
		movq qword ptr [edi], mm0
		add edi, eax
		dec ecx
		jne rvaNext
	}
}
