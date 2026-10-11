// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d75b0.md plus retail only. No decoder
// source was consulted.
//
// Half-pixel inter reconstruction (retail 0x001D75B0), 8 rows of 8: truncated
// average of two references plus the 16-bit residual row (wrapping), packed with
// unsigned saturation. The MMX state is left in use for the caller to clear.

// RVA 0x001D75B0
extern "C" void __cdecl MmxReconInterHalfPixel2(void *unusedParam, void *destination,
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
		pxor mm0, mm0
	rvaNext:
		movq mm2, qword ptr [esi]
		movq mm4, qword ptr [edi]
		movq mm3, mm2
		punpcklbw mm2, mm0
		movq mm5, mm4
		movq mm6, qword ptr [ecx]
		punpckhbw mm3, mm0
		movq mm7, qword ptr [ecx + 8]
		punpcklbw mm4, mm0
		punpckhbw mm5, mm0
		paddw mm2, mm4
		paddw mm3, mm5
		psrlw mm2, 1
		psrlw mm3, 1
		paddw mm2, mm6
		paddw mm3, mm7
		lea ecx, [ecx + 10h]
		packuswb mm2, mm3
		add esi, edx
		add edi, edx
		cmp ecx, eax
		movq qword ptr [ebx], mm2
		lea ebx, [ebx + edx]
		jb rvaNext
		pop edi
		pop esi
	}
}
