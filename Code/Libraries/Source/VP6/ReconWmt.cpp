// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d7d50.md 001d7fd0.md and
// 001d8010.md plus retail only. No decoder source was consulted.
//
// SSE2 block helpers of the reconstruction path, cdecl leaves. The vector
// bodies are inline assembly inside ordinary C functions that name their own
// arguments (the compiler supplies the frame and register saves): cl 13.10
// has no C form for these SSE2 instructions.

// Retail 0x00DB87E0 (data RVA 0x009B87E0): eight bias bytes of 0x80.
__declspec(align(8)) const unsigned char g_bfmeXor80Sse[8] =
	{ 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 };

// UnpackBlock_wmt retail 0x001D7D50..0x001D7D80 (49 bytes). Zero-extends an
// 8x8 byte block to 16-bit entries one row per step: source rows
// pixelsPerLine apart, output rows 8 entries apart. The same operation is
// inlined in 0x001D7DF0; this out-of-line copy has no caller.
extern "C" void __cdecl UnpackBlock_wmt(const unsigned char *source, short *output,
	unsigned int pixelsPerLine)
{
	__asm
	{
		mov edi, output
		mov esi, source
		mov ecx, 8
		mov eax, 10h
		pxor xmm0, xmm0
	nextRow:
		movdqu xmm3, [esi]
		punpcklbw xmm3, xmm0
		movdqu [edi], xmm3
		add esi, pixelsPerLine
		add edi, eax
		dec ecx
		jne nextRow
	}
}

// WmtReconIntra retail 0x001D7FD0..0x001D800D (62 bytes). SSE2 twin of
// MMXReconIntra: per row the eight residual words pack to signed bytes with
// saturation and the exclusive or with 0x80 gives residual plus 128 clamped
// to 0..255. Residual rows 8 entries apart, destination rows stride apart;
// the first argument is unused.
extern "C" void __cdecl WmtReconIntra(void *scratch, unsigned char *destination,
	const short *residual, unsigned int stride)
{
	__asm
	{
		push ebx
		mov eax, residual
		mov edx, destination
		movq xmm0, qword ptr [g_bfmeXor80Sse]
		pxor xmm3, xmm3
		mov ebx, stride
		lea ecx, [eax + 80h]
	nextRow:
		movdqa xmm2, xmmword ptr [eax]
		packsswb xmm2, xmm3
		pxor xmm2, xmm0
		lea eax, [eax + 10h]
		cmp eax, ecx
		movq qword ptr [edx], xmm2
		lea edx, [edx + ebx]
		jb nextRow
		pop ebx
	}
}

// WmtReconInter retail 0x001D8010..0x001D8054 (69 bytes). SSE2 twin of
// MmxReconInter: reference bytes widen to words, add the residual row with
// signed saturation and pack back with unsigned saturation. Reference and
// destination rows are stride apart, residual rows 8 entries apart; the
// first argument is unused.
extern "C" void __cdecl WmtReconInter(void *scratch, unsigned char *destination,
	const unsigned char *reference, const short *residual, unsigned int stride)
{
	__asm
	{
		push edi
		mov ebx, reference
		mov ecx, residual
		mov eax, destination
		mov edx, stride
		pxor xmm0, xmm0
		lea edi, [ecx + 80h]
	nextRow:
		movq xmm2, qword ptr [ebx]
		movdqa xmm4, xmmword ptr [ecx]
		punpcklbw xmm2, xmm0
		add ebx, edx
		paddsw xmm2, xmm4
		lea ecx, [ecx + 10h]
		packuswb xmm2, xmm0
		cmp ecx, edi
		movq qword ptr [eax], xmm2
		lea eax, [eax + edx]
		jb nextRow
		pop edi
	}
}
