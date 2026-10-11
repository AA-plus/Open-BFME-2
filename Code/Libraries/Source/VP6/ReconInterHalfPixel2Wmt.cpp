// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d8060.md plus retail only. No decoder
// source was consulted.
//
// SSE2 twin of MmxReconInterHalfPixel2 (retail 0x001D8060): destination is the
// truncated average of the two references plus the residual, clamped to 0..255,
// 8 rows of 8.

// RVA 0x001D8060
extern "C" void __cdecl WmtReconInterHalfPixel2(void *unusedParam, void *destination,
	const void *row0, const void *row1, const void *table, int stride)
{
	__asm
	{
		push esi
		push edi
		mov ecx, table
		mov esi, row0
		mov edi, row1
		mov ebx, destination
		mov edx, stride
		lea eax, [ecx + 80h]
		pxor xmm0, xmm0
	rvaNext:
		movq xmm2, qword ptr [esi]
		movq xmm4, qword ptr [edi]
		punpcklbw xmm2, xmm0
		punpcklbw xmm4, xmm0
		movdqa xmm6, xmmword ptr [ecx]
		paddw xmm2, xmm4
		psrlw xmm2, 1
		paddw xmm2, xmm6
		lea ecx, [ecx + 10h]
		packuswb xmm2, xmm0
		add esi, edx
		add edi, edx
		cmp ecx, eax
		movq qword ptr [ebx], xmm2
		lea ebx, [ebx + edx]
		jb rvaNext
		pop edi
		pop esi
	}
}
