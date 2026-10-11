// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d7bc0.md and 001d7c20.md plus retail only. No decoder
// source was consulted.
//
// SSE2 two-tap one-dimensional filters (retail 0x001D7BC0 horizontal and
// 0x001D7C20 vertical) producing eight int16 values per row: first weight group
// (taps offset 0) times the sample plus second group (offset 16) times the right
// neighbour or the sample one row below, plus 64, shifted right 7 arithmetically.
// Output rows are 16 bytes apart; the pixel step argument is unused.

extern const unsigned short g_bfmeBinkRound[8]; // 0x009B84D0 eight 16-bit 64 (rounding)

// RVA 0x001D7BC0
extern "C" void __cdecl FilterUnpackBlock1d_hb8_wmt(const void *source, void *destination,
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
		movdqu [edi], xmm3
		add esi, sourceStride
		add edi, eax
		dec ecx
		jne rvaNext
	}
}

// RVA 0x001D7C20
extern "C" void __cdecl FilterUnpackBlock1d_vb8_wmt(const void *source, void *destination,
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
		movdqu [edi], xmm3
		add esi, edx
		add edi, eax
		dec ecx
		jne rvaNext
	}
}
