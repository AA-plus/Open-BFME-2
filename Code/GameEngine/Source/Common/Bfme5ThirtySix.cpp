// BFME1 byte-identical donor: reference/open-bfme-1/Code/GameEngine/Source/Common/Bfme5ThirtySix.cpp
// Trimmed to the bodies that reproduce game.dat bytes. The file's counted-handle
// and bounded-read members (BfmeHandleCX/bfmeGet, Gen_009CBC90/bfmeAt) are BFME1-only
// shapes with no matching body here; they stay out so every defined function
// has a ledger row. bfmeBlurRowsSse is the donor's own hand-written bare-assembly
// kernel (register saves scoped by hand, a proven codegen blocker), reused
// verbatim — not a dump lift — and the gate verifies it byte-exact.

// The copy is the compiler's own memcpy, not hand-written assembly: only the
// intrinsic puts the register saves between the argument loads.
extern "C" void * __cdecl memcpy(void *destination, const void *source, unsigned int bytes);

#pragma intrinsic(memcpy)

namespace
{
	__declspec(align(8)) const unsigned short g_bfmeRoundMmx[4] = { 1, 1, 1, 1 };
	__declspec(align(16)) const unsigned short g_bfmeBlurBias[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
}

// ?bfmeAverageMmx@@YAXPAXHH@Z
// Blends the row two strides below "source" into the row one stride below it,
// eight bytes at a time. "offset" is an assembler keyword, so the stride
// cannot carry that name.
void __cdecl bfmeAverageMmx(void *source, int stride, int bytes)
{
	__asm
	{
		mov esi, source
		mov ecx, stride
		pxor mm7, mm7
		mov edx, bytes
	bfmeNext:
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
		jg bfmeNext
	}
}

// ?bfmeBlurRowsSse@@YAXPAXPAXIHH@Z
// Copies the first and last row verbatim, then rebuilds every row between
// them as a (row-1 + 2*row + row+1 + 2) >> 2 vertical box blend, eight bytes
// of pixels at a time. "count" holds the local row counter, decremented
// once up front for the rows already handled by the two straight copies.
void __declspec(naked) __cdecl bfmeBlurRowsSse(void *src, void *dst, unsigned int width, int count, int stride)
{
	__asm
	{
		push ebp
		mov ebp, esp
		mov ecx, width
		mov eax, dst
		mov edx, ecx
		push ebx
		push esi
		mov esi, src
		shr ecx, 2
		push edi
		mov src, esi
		mov edi, eax
		rep movsd
		mov ecx, edx
		and ecx, 3
		rep movsb
		mov ecx, count
		dec ecx
		cmp ecx, 1
		jle bfmeTail
		dec ecx
		mov count, ecx
		nop
	bfmeLoop:
		add eax, stride
		mov dst, eax
		mov esi, src
		mov edi, dst
		xor ecx, ecx
		mov edx, stride
		lea eax, [esi+edx]
		lea edx, [eax+edx]
		mov ebx, width
		pxor xmm7, xmm7
	bfmeInner:
		movq xmm0, qword ptr [esi+ecx]
		movq xmm1, qword ptr [eax+ecx]
		punpcklbw xmm0, xmm7
		movq xmm2, qword ptr [edx+ecx]
		punpcklbw xmm1, xmm7
		paddw xmm0, g_bfmeBlurBias
		psllw xmm1, 1
		punpcklbw xmm2, xmm7
		paddw xmm0, xmm1
		paddw xmm0, xmm2
		psraw xmm0, 2
		packuswb xmm0, xmm7
		movq qword ptr [edi+ecx], xmm0
		add ecx, 8
		cmp ecx, ebx
		jl bfmeInner

		mov eax, stride
		mov ecx, src
		add ecx, eax
		dec count
		mov eax, dst
		mov src, ecx
		jnz bfmeLoop

	bfmeTail:
		mov ecx, stride
		mov esi, src
		add esi, ecx
		add eax, ecx
		mov ecx, width
		mov edx, ecx
		shr ecx, 2
		mov edi, eax
		rep movsd
		mov ecx, edx
		and ecx, 3
		rep movsb
		pop edi
		pop esi
		pop ebx
		pop ebp
		ret
	}
}

// ?bfmeExpandMmx@@YAXPBXHPAX@Z
// Doubles "bytes" source pixels into 2*bytes destination pixels: each output
// pair is (original byte, round((byte + next byte) / 2)). The tail copy
// replicates the last source byte past the end so the final "next byte" read
// stays in range without an extra branch.
void __cdecl bfmeExpandMmx(const void *source, int bytes, void *destination)
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
