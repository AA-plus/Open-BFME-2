// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c7580.md 001cdf60.md and
// 001d1540.md plus retail only. No decoder source was consulted.
//
// Vertical 1-2-1 deinterlace over one column of an image, in its generic,
// MMX and SSE2 forms (retail 0x001C7580, 0x001CDF60, 0x001D1540): the first
// and last rows are copied verbatim and every row between becomes
// (above + 2 * row + below + 2) >> 2. The row copies are the compiler's own
// inline memcpy.

extern "C" void * __cdecl memcpy(void *destination, const void *source, unsigned int bytes);
#pragma intrinsic(memcpy)

namespace
{
	__declspec(align(8)) const unsigned short g_bfmeBlurBiasMmx[4] = { 2, 2, 2, 2 };
	__declspec(align(16)) const unsigned short g_bfmeBlurBias[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
}

// CFastDeInterlace retail 0x001C7580 (183 bytes): scalar form.
extern "C" void __cdecl CFastDeInterlace(void *src, void *dst, unsigned int width, int count, int stride)
{
	unsigned char *out;
	const unsigned char *cur;
	const unsigned char *next;
	const unsigned char *prev;
	int x;
	int i;
	unsigned int w;

	cur = (const unsigned char *)src;
	prev = cur;
	w = width;
	out = (unsigned char *)dst;
	memcpy(out, cur, w);
	for (i = 1; i < count - 1; i++) {
		prev = cur;
		cur += stride;
		next = cur + stride;
		out += stride;
		for (x = 0; x < (int)w; x++)
			out[x] = (unsigned char)((prev[x] + 2u * cur[x] + 2u + next[x]) >> 2);
	}
	memcpy(out + stride, cur + stride, w);
}

// MmxFastDeInterlace retail 0x001CDF60 (232 bytes): eight pixels per step.
extern "C" void __cdecl MmxFastDeInterlace(void *src, void *dst, unsigned int width, int count, int stride)
{
	const unsigned char *cur = (const unsigned char *)src;
	unsigned char *out = (unsigned char *)dst;
	int i;

	memcpy(out, cur, width);
	for (i = 1; i < count - 1; i++) {
		out += stride;
		__asm
		{
			mov esi, cur
			mov edi, out
			xor ecx, ecx
			mov edx, stride
			lea eax, [esi + edx]
			lea edx, [eax + edx]
			mov ebx, width
			pxor mm7, mm7
		bfmeInner:
			movq mm0, qword ptr [esi + ecx]
			movq mm1, qword ptr [eax + ecx]
			movq mm3, mm0
			punpcklbw mm0, mm7
			movq mm2, qword ptr [edx + ecx]
			punpckhbw mm3, mm7
			movq mm4, mm1
			punpcklbw mm1, mm7
			paddw mm0, g_bfmeBlurBiasMmx
			paddw mm3, g_bfmeBlurBiasMmx
			punpckhbw mm4, mm7
			psllw mm1, 1
			psllw mm4, 1
			movq mm5, mm2
			punpcklbw mm2, mm7
			paddw mm0, mm1
			paddw mm3, mm4
			punpckhbw mm5, mm7
			paddw mm0, mm2
			paddw mm3, mm5
			psraw mm0, 2
			psraw mm3, 2
			packuswb mm0, mm3
			movq qword ptr [edi + ecx], mm0
			add ecx, 8
			cmp ecx, ebx
			jl bfmeInner
		}
		cur += stride;
	}
	cur += stride;
	out += stride;
	memcpy(out, cur, width);
}

// WmtFastDeInterlace retail 0x001D1540 (200 bytes): SSE2 form, eight pixels
// per step.
extern "C" void __cdecl WmtFastDeInterlace(void *src, void *dst, unsigned int width, int count, int stride)
{
	const unsigned char *cur = (const unsigned char *)src;
	unsigned char *out = (unsigned char *)dst;
	int i;

	memcpy(out, cur, width);
	for (i = 1; i < count - 1; i++) {
		out += stride;
		__asm
		{
			mov esi, cur
			mov edi, out
			xor ecx, ecx
			mov edx, stride
			lea eax, [esi + edx]
			lea edx, [eax + edx]
			mov ebx, width
			pxor xmm7, xmm7
		bfmeInner:
			movq xmm0, qword ptr [esi + ecx]
			movq xmm1, qword ptr [eax + ecx]
			punpcklbw xmm0, xmm7
			movq xmm2, qword ptr [edx + ecx]
			punpcklbw xmm1, xmm7
			paddw xmm0, g_bfmeBlurBias
			psllw xmm1, 1
			punpcklbw xmm2, xmm7
			paddw xmm0, xmm1
			paddw xmm0, xmm2
			psraw xmm0, 2
			packuswb xmm0, xmm7
			movq qword ptr [edi + ecx], xmm0
			add ecx, 8
			cmp ecx, ebx
			jl bfmeInner
		}
		cur += stride;
	}
	cur += stride;
	out += stride;
	memcpy(out, cur, width);
}
