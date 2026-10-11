// _ClampLevels_mmx
// partial score=0.9 date=2026-10-11
// cl: /O2 /G6 /Z7 /MD
// Clean room: reverse/vp6_cleanroom/specs/001cde70.md plus retail only.
// No decoder source was consulted.
extern "C" void *__cdecl memset(void *block, int value, unsigned int bytes);
#pragma intrinsic(memset)

struct POSTPROC_LEVELS_MMX
{
	unsigned char m_pad00[0x78];
	unsigned char *m_plane;   // 0x78
	unsigned char m_pad7C[0x14];
	int m_width;              // 0x90
	int m_height;             // 0x94
	int m_stride;             // 0x98
};

extern "C" void __cdecl ClampLevels_mmx(POSTPROC_LEVELS_MMX *context,
	int black, int white, int sourceOffset, int destinationOffset)
{
	__declspec(align(8)) double blackVec[2];
	__declspec(align(8)) double sumVec[2];
	__declspec(align(8)) double whiteVec[2];
	int width = context->m_width << 3;
	unsigned char *src = context->m_plane + sourceOffset;
	unsigned char *dst = context->m_plane + destinationOffset;
	int height;
	int stride;

	height = context->m_height << 3;
	stride = context->m_stride;
	memset(sumVec, (unsigned char)(black + white), 8);

	memset(whiteVec, white, 8);
	memset(blackVec, black, 8);
	for (; height > 0; height--) {
		int x;
		__asm
		{
			mov esi, src
			mov edi, dst
			xor eax, eax
			mov ecx, width
		L:
			movq mm1, qword ptr [esi + eax]
			psubusb mm1, qword ptr blackVec
			paddusb mm1, qword ptr sumVec
			psubusb mm1, qword ptr whiteVec
			movq qword ptr [edi + eax], mm1
			add eax, 8
			cmp eax, ecx
			jl L
		}
		src += stride;
		dst += stride;
	}
}
