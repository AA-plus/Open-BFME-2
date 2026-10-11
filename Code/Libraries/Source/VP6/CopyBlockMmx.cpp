// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d7630.md plus retail only. No decoder
// source was consulted.
//
// 8x8 byte block copy (retail 0x001D7630): two groups of four 64-bit loads and
// stores, source and destination advancing by the same stride. The MMX state is
// left in use for the caller to clear.

// RVA 0x001D7630
extern "C" void __cdecl CopyBlockMMX(const void *source, void *destination, int stride)
{
	const void *src = source;
	void *dst = destination;
	int str = stride;
	__asm
	{
		mov ecx, str
		mov eax, src
		mov ebx, dst
		lea edx, [ecx + ecx*2]
		movq mm0, qword ptr [eax]
		movq mm1, qword ptr [eax + ecx]
		movq mm2, qword ptr [eax + ecx*2]
		movq mm3, qword ptr [eax + edx]
		lea eax, [eax + ecx*4]
		movq qword ptr [ebx], mm0
		movq qword ptr [ebx + ecx], mm1
		movq qword ptr [ebx + ecx*2], mm2
		movq qword ptr [ebx + edx], mm3
		lea ebx, [ebx + ecx*4]
		movq mm0, qword ptr [eax]
		movq mm1, qword ptr [eax + ecx]
		movq mm2, qword ptr [eax + ecx*2]
		movq mm3, qword ptr [eax + edx]
		movq qword ptr [ebx], mm0
		movq qword ptr [ebx + ecx], mm1
		movq qword ptr [ebx + ecx*2], mm2
		movq qword ptr [ebx + edx], mm3
	}
}
