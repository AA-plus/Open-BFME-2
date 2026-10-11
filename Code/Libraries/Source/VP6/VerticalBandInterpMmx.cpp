// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d2150.md 001d23e0.md plus retail only.
// No decoder source was consulted.
//
// VerticalBand_4_5_Scale_MMX (retail 0x001D2150, 358 bytes) and
// VerticalBand_3_5_Scale_MMX (retail 0x001D23E0, 366 bytes): in-place vertical
// interpolation over a six row band (rows 0 and 5 bound it), four columns per
// step, leaving MMX state in use. The 16-bit weight tables are the retail
// constants at image 0x00BD9910 (51), 0x00BD9920 (102), 0x00BD9930 (154),
// 0x00BD9940 (205) and 0x00BD9950 (128).

namespace
{
	__declspec(align(8)) const unsigned short g_bfmeW51c[4] = { 51, 51, 51, 51 };
	__declspec(align(8)) const unsigned short g_bfmeW102c[4] = { 102, 102, 102, 102 };
	__declspec(align(8)) const unsigned short g_bfmeW154c[4] = { 154, 154, 154, 154 };
	__declspec(align(8)) const unsigned short g_bfmeW205c[4] = { 205, 205, 205, 205 };
	__declspec(align(8)) const unsigned short g_bfmeW128c[4] = { 128, 128, 128, 128 };
}

extern "C" void __cdecl VerticalBand_4_5_Scale_MMX(void *source, unsigned int stride, unsigned int bytes)
{
	__asm
	{
		mov esi, source
		mov ecx, stride
		lea edi, [esi+ecx*2]
		add edi, ecx
		pxor mm7, mm7
		mov edx, bytes
	bfmeNext:
		movq mm0, qword ptr [esi]
		movq mm1, qword ptr [esi+ecx]
		movq mm2, mm0
		punpcklbw mm0, mm7
		movq mm5, g_bfmeW51c
		punpckhbw mm2, mm7
		pmullw mm0, mm5
		movq mm3, mm1
		punpcklbw mm1, mm7
		pmullw mm2, mm5
		movq mm6, g_bfmeW205c
		movq mm4, mm1
		pmullw mm4, mm6
		punpckhbw mm3, mm7
		movq mm5, mm3
		pmullw mm5, mm6
		paddw mm0, mm4
		paddw mm2, mm5
		paddw mm0, g_bfmeW128c
		paddw mm2, g_bfmeW128c
		psrlw mm0, 8
		psrlw mm2, 8
		packuswb mm0, mm2
		movq qword ptr [esi+ecx], mm0
		movq mm0, qword ptr [esi+ecx*2]
		movq mm5, g_bfmeW102c
		movq mm2, mm0
		pmullw mm1, mm5
		movq mm6, g_bfmeW154c
		punpcklbw mm0, mm7
		pmullw mm3, mm5
		movq mm4, mm0
		punpckhbw mm2, mm7
		pmullw mm4, mm6
		movq mm5, mm2
		pmullw mm5, mm6
		paddw mm1, mm4
		paddw mm3, mm5
		paddw mm1, g_bfmeW128c
		paddw mm3, g_bfmeW128c
		psrlw mm1, 8
		psrlw mm3, 8
		packuswb mm1, mm3
		movq qword ptr [esi+ecx*2], mm1
		movq mm1, qword ptr [edi]
		pmullw mm0, mm6
		movq mm5, g_bfmeW102c
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
		paddw mm0, g_bfmeW128c
		paddw mm2, g_bfmeW128c
		psrlw mm0, 8
		psrlw mm2, 8
		packuswb mm0, mm2
		movq qword ptr [edi], mm0
		movq mm0, qword ptr [edi+ecx*2]
		movq mm5, g_bfmeW205c
		pmullw mm1, mm5
		movq mm6, g_bfmeW51c
		movq mm2, mm0
		pmullw mm3, mm5
		punpcklbw mm0, mm7
		pmullw mm0, mm6
		punpckhbw mm2, mm7
		paddw mm1, mm0
		pmullw mm2, mm6
		paddw mm3, mm2
		paddw mm1, g_bfmeW128c
		paddw mm3, g_bfmeW128c
		psrlw mm1, 8
		psrlw mm3, 8
		packuswb mm1, mm3
		movq qword ptr [edi+ecx], mm1
		add edi, 8
		add esi, 8
		sub edx, 8
		jg bfmeNext
	}
}

namespace
{
	__declspec(align(8)) const unsigned short g_bfmeW51d[4] = { 51, 51, 51, 51 };
	__declspec(align(8)) const unsigned short g_bfmeW102d[4] = { 102, 102, 102, 102 };
	__declspec(align(8)) const unsigned short g_bfmeW154d[4] = { 154, 154, 154, 154 };
	__declspec(align(8)) const unsigned short g_bfmeW205d[4] = { 205, 205, 205, 205 };
	__declspec(align(8)) const unsigned short g_bfmeW128d[4] = { 128, 128, 128, 128 };
}

extern "C" void __cdecl VerticalBand_3_5_Scale_MMX(void *source, unsigned int stride, unsigned int bytes)
{
	__asm
	{
		mov esi, source
		mov ecx, stride
		lea edi, [esi+ecx*2]
		add edi, ecx
		pxor mm7, mm7
		mov edx, bytes
	bfmeNext:
		movq mm0, qword ptr [esi]
		movq mm1, qword ptr [esi+ecx]
		movq mm2, mm0
		punpcklbw mm0, mm7
		movq mm5, g_bfmeW102d
		punpckhbw mm2, mm7
		pmullw mm0, mm5
		movq mm3, mm1
		punpcklbw mm1, mm7
		pmullw mm2, mm5
		movq mm6, g_bfmeW154d
		movq mm4, mm1
		pmullw mm4, mm6
		punpckhbw mm3, mm7
		movq mm5, mm3
		pmullw mm5, mm6
		paddw mm0, mm4
		paddw mm2, mm5
		paddw mm0, g_bfmeW128d
		paddw mm2, g_bfmeW128d
		psrlw mm0, 8
		psrlw mm2, 8
		packuswb mm0, mm2
		movq qword ptr [esi+ecx], mm0
		movq mm0, qword ptr [esi+ecx*2]
		movq mm4, mm1
		pmullw mm1, g_bfmeW205d
		movq mm5, mm3
		pmullw mm3, g_bfmeW205d
		movq mm2, mm0
		pmullw mm4, g_bfmeW51d
		punpcklbw mm0, mm7
		pmullw mm5, g_bfmeW51d
		movq mm6, mm0
		punpckhbw mm2, mm7
		pmullw mm6, g_bfmeW51d
		movq mm7, mm2
		pmullw mm7, g_bfmeW51d
		paddw mm1, mm6
		paddw mm3, mm7
		movq mm6, mm0
		pmullw mm6, g_bfmeW205d
		movq mm7, mm2
		pmullw mm7, g_bfmeW205d
		paddw mm4, mm6
		paddw mm5, mm7
		paddw mm1, g_bfmeW128d
		paddw mm3, g_bfmeW128d
		psrlw mm1, 8
		psrlw mm3, 8
		packuswb mm1, mm3
		movq qword ptr [esi+ecx*2], mm1
		paddw mm4, g_bfmeW128d
		paddw mm5, g_bfmeW128d
		psrlw mm4, 8
		psrlw mm5, 8
		packuswb mm4, mm5
		movq qword ptr [edi], mm4
		pxor mm7, mm7
		movq mm1, qword ptr [edi+ecx*2]
		movq mm5, g_bfmeW154d
		pmullw mm0, mm5
		movq mm6, g_bfmeW102d
		movq mm3, mm1
		pmullw mm2, mm5
		punpcklbw mm1, mm7
		pmullw mm1, mm6
		punpckhbw mm3, mm7
		paddw mm0, mm1
		pmullw mm3, mm6
		paddw mm2, mm3
		paddw mm0, g_bfmeW128d
		paddw mm2, g_bfmeW128d
		psrlw mm0, 8
		psrlw mm2, 8
		packuswb mm0, mm2
		movq qword ptr [edi+ecx], mm0
		add edi, 8
		add esi, 8
		sub edx, 8
		jg bfmeNext
	}
}
