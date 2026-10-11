// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d7520.md 001d7560.md
// 001d76a0.md 001d7740.md 001d7780.md and 001d77d0.md plus retail only.
// No decoder source was consulted.
//
// The MMX block reconstruction helpers (retail 0x001D7520..0x001D7811). All
// are cdecl leaves that leave the MMX state in use: the separately installed
// ClearMmx (0x001D7620) is the caller's cleanup. MMX instructions have no C
// form cl 13.10 can emit, so the vector bodies are inline assembly inside
// ordinary C functions that name their own arguments (the compiler supplies
// the frame and register saves). Copy12x12_MMX is plain integer code.

// Retail 0x00DB84C0 (data RVA 0x009B84C0): eight bias bytes of 0x80.
__declspec(align(8)) const unsigned char g_bfmeXor80Mmx[8] =
	{ 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 };

// MMXReconIntra retail 0x001D7520..0x001D7556 (55 bytes). Per row the eight
// residual words pack to signed bytes with saturation and the exclusive or
// with 0x80 maps them onto 0..255 (residual plus 128 clamped). Residual rows
// are 16 bytes apart and destination rows stride apart; the first argument
// is unused.
extern "C" void __cdecl MMXReconIntra(void *scratch, unsigned char *destination,
	const short *residual, unsigned int stride)
{
	__asm
	{
		mov eax, residual
		mov edx, destination
		movq mm0, qword ptr [g_bfmeXor80Mmx]
		mov ebx, stride
		lea ecx, [eax + 80h]
	nextRow:
		movq mm2, qword ptr [eax]
		packsswb mm2, qword ptr [eax + 8]
		por mm0, mm0
		pxor mm2, mm0
		lea eax, [eax + 10h]
		cmp eax, ecx
		movq qword ptr [edx], mm2
		lea edx, [edx + ebx]
		jb nextRow
	}
}

// MmxReconInter retail 0x001D7560..0x001D75AA (75 bytes). Per row the eight
// reference bytes widen to words, add the residual row with signed
// saturation and pack back with unsigned saturation (0..255). Reference and
// destination rows are stride apart, residual rows 8 entries apart; the
// first argument is unused.
extern "C" void __cdecl MmxReconInter(void *scratch, unsigned char *destination,
	const unsigned char *reference, const short *residual, unsigned int stride)
{
	__asm
	{
		push edi
		mov ebx, reference
		mov ecx, residual
		mov eax, destination
		mov edx, stride
		pxor mm0, mm0
		lea edi, [ecx + 80h]
	nextRow:
		movq mm2, qword ptr [ebx]
		movq mm4, qword ptr [ecx]
		movq mm3, mm2
		movq mm5, qword ptr [ecx + 8]
		punpcklbw mm2, mm0
		paddsw mm2, mm4
		punpckhbw mm3, mm0
		paddsw mm3, mm5
		add ebx, edx
		packuswb mm2, mm3
		lea ecx, [ecx + 10h]
		cmp ecx, edi
		movq qword ptr [eax], mm2
		lea eax, [eax + edx]
		jb nextRow
		pop edi
	}
}

// Copy12x12_MMX retail 0x001D76A0..0x001D76D2 (51 bytes). Copies a 12x12
// byte block as 12 rows of three 32-bit words; each side advances by its own
// stride. Plain integer code despite the name.
extern "C" void __cdecl Copy12x12_MMX(const unsigned char *source, unsigned char *destination,
	unsigned int sourceStride, unsigned int destinationStride)
{
	for (int row = 12; row; --row) {
		((unsigned int *)destination)[0] = ((const unsigned int *)source)[0];
		((unsigned int *)destination)[1] = ((const unsigned int *)source)[1];
		((unsigned int *)destination)[2] = ((const unsigned int *)source)[2];
		source += sourceStride;
		destination += destinationStride;
	}
}

// UnpackBlock_MMX retail 0x001D7740..0x001D7774 (53 bytes). Zero-extends an
// 8x8 byte block to 16-bit entries: source rows pixelsPerLine apart, output
// rows 8 entries apart.
extern "C" void __cdecl UnpackBlock_MMX(const unsigned char *source, short *output,
	unsigned int pixelsPerLine)
{
	__asm
	{
		mov esi, source
		mov edi, output
		mov ecx, 8
		mov edx, pixelsPerLine
		pxor mm7, mm7
	nextRow:
		movq mm0, qword ptr [esi]
		movq mm2, mm0
		punpcklbw mm0, mm7
		movq qword ptr [edi], mm0
		punpckhbw mm2, mm7
		add esi, edx
		movq qword ptr [edi + 8], mm2
		add edi, 10h
		dec ecx
		jne nextRow
	}
}

// SubtractBlock_MMX retail 0x001D7780..0x001D77C1 (66 bytes). For 8 rows of
// 8: target = zero-extended source byte minus target, 16-bit wrapping. Source
// rows advance by the line step, target rows by 8 entries.
extern "C" void __cdecl SubtractBlock_MMX(const unsigned char *source, short *target,
	unsigned int lineStep)
{
	__asm
	{
		mov esi, source
		mov edi, target
		mov edx, lineStep
		mov ecx, 8
		pxor mm7, mm7
	nextRow:
		movq mm0, qword ptr [esi]
		movq mm1, qword ptr [edi]
		movq mm2, mm0
		punpcklbw mm0, mm7
		movq mm3, qword ptr [edi + 8]
		psubw mm0, mm1
		punpckhbw mm2, mm7
		movq qword ptr [edi], mm0
		psubw mm2, mm3
		add esi, edx
		movq qword ptr [edi + 8], mm2
		add edi, 10h
		dec ecx
		jne nextRow
	}
}

// ReconBlock_MMX retail 0x001D77D0..0x001D7811 (66 bytes). Per row adds the
// block and prediction words with 16-bit wrap-around and packs the sums to
// bytes with unsigned saturation. Both inputs advance 16 bytes per row, the
// destination by the line step; the inputs are never written.
extern "C" void __cdecl ReconBlock_MMX(const short *block, const short *prediction,
	unsigned char *destination, unsigned int lineStep)
{
	__asm
	{
		mov esi, block
		mov eax, prediction
		mov edi, destination
		mov ecx, 8
		mov edx, lineStep
		pxor mm7, mm7
	nextRow:
		movq mm0, qword ptr [esi]
		movq mm1, qword ptr [eax]
		movq mm2, qword ptr [esi + 8]
		movq mm3, qword ptr [eax + 8]
		paddw mm0, mm1
		paddw mm2, mm3
		packuswb mm0, mm2
		movq qword ptr [edi], mm0
		add esi, 10h
		add eax, 10h
		add edi, edx
		dec ecx
		jne nextRow
	}
}
