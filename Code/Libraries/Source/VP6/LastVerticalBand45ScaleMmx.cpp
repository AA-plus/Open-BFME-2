// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d22c0.md plus retail only.
// No decoder source was consulted.
//
// LastVerticalBand_4_5_Scale_MMX (retail 0x001D22C0, 288 bytes): in-place 4-to-5 vertical scaling of the last band of an image, four rows from the band at 8 columns per step; row 4 is a copy of the original row 3 because no row 5 exists.
// The 16-bit weight tables are the retail constants at image 0x00BD9910 (51),
// 0x00BD9920 (102), 0x00BD9930 (154), 0x00BD9940 (205) and 0x00BD9950 (128).

namespace
{
	__declspec(align(8)) const unsigned short g_bfmeW51[4] = { 51, 51, 51, 51 };
	__declspec(align(8)) const unsigned short g_bfmeW102[4] = { 102, 102, 102, 102 };
	__declspec(align(8)) const unsigned short g_bfmeW154[4] = { 154, 154, 154, 154 };
	__declspec(align(8)) const unsigned short g_bfmeW205[4] = { 205, 205, 205, 205 };
	__declspec(align(8)) const unsigned short g_bfmeW128[4] = { 128, 128, 128, 128 };
}

// RVA 0x001D22C0
extern "C" void __cdecl LastVerticalBand_4_5_Scale_MMX(void *band, int pitch, int width)
{
	__asm
	{
		mov esi, band
		mov ecx, pitch
		lea edi, [esi+ecx*2]
		add edi, ecx
		pxor mm7, mm7
		mov edx, width
	bfmeNext:
		movq mm0, qword ptr [esi]
		movq mm1, qword ptr [esi+ecx]
		movq mm2, mm0
		punpcklbw mm0, mm7
		movq mm5, g_bfmeW51
		punpckhbw mm2, mm7
		pmullw mm0, mm5
		movq mm3, mm1
		punpcklbw mm1, mm7
		pmullw mm2, mm5
		movq mm6, g_bfmeW205
		movq mm4, mm1
		pmullw mm4, mm6
		punpckhbw mm3, mm7
		movq mm5, mm3
		pmullw mm5, mm6
		paddw mm0, mm4
		paddw mm2, mm5
		paddw mm0, g_bfmeW128
		paddw mm2, g_bfmeW128
		psrlw mm0, 8
		psrlw mm2, 8
		packuswb mm0, mm2
		movq qword ptr [esi+ecx], mm0
		movq mm0, qword ptr [esi+ecx*2]
		movq mm5, g_bfmeW102
		movq mm2, mm0
		pmullw mm1, mm5
		movq mm6, g_bfmeW154
		punpcklbw mm0, mm7
		pmullw mm3, mm5
		movq mm4, mm0
		punpckhbw mm2, mm7
		pmullw mm4, mm6
		movq mm5, mm2
		pmullw mm5, mm6
		paddw mm1, mm4
		paddw mm3, mm5
		paddw mm1, g_bfmeW128
		paddw mm3, g_bfmeW128
		psrlw mm1, 8
		psrlw mm3, 8
		packuswb mm1, mm3
		movq qword ptr [esi+ecx*2], mm1
		movq mm1, qword ptr [edi]
		movq qword ptr [edi+ecx], mm1
		pmullw mm0, mm6
		movq mm5, g_bfmeW102
		movq mm3, mm1
		pmullw mm2, mm6
		punpcklbw mm1, mm7
		movq mm4, mm1
		punpckhbw mm3, mm7
		pmullw mm4, mm5
		movq mm6, mm3
		pmullw mm6, mm5
		paddw mm0, mm4
		paddw mm2, mm6
		paddw mm0, g_bfmeW128
		paddw mm2, g_bfmeW128
		psrlw mm0, 8
		psrlw mm2, 8
		packuswb mm0, mm2
		movq qword ptr [edi], mm0
		add edi, 8
		add esi, 8
		sub edx, 8
		jg bfmeNext
	}
}
