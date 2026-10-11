// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d2700.md plus retail only. No decoder source was consulted.
// HorizontalLine_1_2_Scale_MMX, retail RVA 0x001D2700 (193 bytes).
// The copy is the compiler's own memcpy, not hand-written assembly: only the
// intrinsic puts the register saves between the argument loads.
extern "C" void * __cdecl memcpy(void *destination, const void *source, unsigned int bytes);

#pragma intrinsic(memcpy)

extern "C" const unsigned short g_bfmeRoundMmx[4]; // defined in VerticalBandScaleMmx.cpp

// Doubles "bytes" source pixels into 2*bytes destination pixels: each output
// pair is (original byte, round((byte + next byte) / 2)). The tail copy
// replicates the last source byte past the end so the final "next byte" read
// stays in range without an extra branch.
extern "C" void __cdecl HorizontalLine_1_2_Scale_MMX(const void *source, int bytes, void *destination)
{
	__asm
	{
		mov esi, source
		mov edi, destination
		pxor mm7, mm7
		movq mm6, g_bfmeRoundMmx
		mov ecx, bytes
	bfmeNext:
		movq mm0, [esi]
		movq mm1, qword ptr [esi+1]
		movq mm2, mm0
		movq mm3, mm1
		movq mm4, mm0
		punpcklbw mm0, mm7
		punpcklbw mm1, mm7
		paddw mm0, mm1
		paddw mm0, mm6
		punpckhbw mm2, mm7
		punpckhbw mm3, mm7
		paddw mm2, mm3
		paddw mm2, mm6
		psraw mm0, 1
		psraw mm2, 1
		packuswb mm0, mm2
		movq mm2, mm4
		punpcklbw mm2, mm0
		movq [edi], mm2
		punpckhbw mm4, mm0
		movq [edi+8], mm4
		add esi, 8
		add edi, 16
		sub ecx, 8
		cmp ecx, 8
		jg bfmeNext

		movq mm0, [esi]
		movq mm1, mm0
		movq mm2, mm0
		movq mm3, mm1
		psrlq mm1, 8
		psrlq mm3, 38h
		psllq mm3, 38h
		por mm1, mm3
		movq mm3, mm1
		movq mm4, mm0
		punpcklbw mm0, mm7
		punpcklbw mm1, mm7
		paddw mm0, mm1
		paddw mm0, mm6
		punpckhbw mm2, mm7
		punpckhbw mm3, mm7
		paddw mm2, mm3
		paddw mm2, mm6
		psraw mm0, 1
		psraw mm2, 1
		packuswb mm0, mm2
		movq mm2, mm4
		punpcklbw mm2, mm0
		movq [edi], mm2
		punpckhbw mm4, mm0
		movq [edi+8], mm4
	}
}
