// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d7960.md and 001d79d0.md plus retail only. No decoder
// source was consulted.
//
// SSE2 two-tap one-dimensional filters (retail 0x001D7960 horizontal and
// 0x001D79D0 vertical): eight outputs per row, weight group 0 times the sample
// plus weight group 1 times the right neighbour (horizontal) or the sample one row
// below (vertical), plus 64, shifted right 7 and packed to bytes with unsigned
// saturation. The pixel step argument is unused.

extern const unsigned short g_bfmeBinkRound[8]; // 0x009B84D0 eight 16-bit 64 (rounding)

// RVA 0x001D7960
extern "C" void __cdecl FilterBlock1d_hb8_wmt(const void *source, void *destination,
	int sourceStride, int unused, int count, int destinationStride,
	const void *weights)
{
	__asm
	{
		mov edi, weights
		movdqa xmm1, [edi]
		movdqa xmm2, [edi + 10h]
		mov edi, destination
		mov esi, source
		mov ecx, count
		mov eax, destinationStride
		pxor xmm0, xmm0
	rvaNext:
		movdqu xmm3, [esi]
		movdqu xmm5, xmm3
		punpcklbw xmm3, xmm0
		pmullw xmm3, xmm1
		psrldq xmm5, 1
		punpcklbw xmm5, xmm0
		pmullw xmm5, xmm2
		paddw xmm3, xmm5
		paddw xmm3, g_bfmeBinkRound
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

// RVA 0x001D79D0
extern "C" void __cdecl FilterBlock1d_vb8_wmt(const void *source, void *destination,
	int sourceStride, int unused, int count, int destinationStride,
	const void *weights)
{
	__asm
	{
		mov edi, weights
		movdqa xmm1, [edi]
		movdqa xmm2, [edi + 10h]
		mov edx, sourceStride
		mov edi, destination
		mov esi, source
		mov ecx, count
		mov eax, destinationStride
		pxor xmm0, xmm0
	rvaNext:
		movdqu xmm3, [esi]
		punpcklbw xmm3, xmm0
		pmullw xmm3, xmm1
		movdqu xmm4, [esi + edx]
		punpcklbw xmm4, xmm0
		pmullw xmm4, xmm2
		paddw xmm3, xmm4
		paddw xmm3, g_bfmeBinkRound
		psraw xmm3, 7
		packuswb xmm3, xmm0
		movdq2q mm0, xmm3
		movq qword ptr [edi], mm0
		add esi, edx
		add edi, eax
		dec ecx
		jne rvaNext
	}
}
