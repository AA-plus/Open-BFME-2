// cl: /O2 /G6 /Z7 /MD
// Clean room: reverse/vp6_cleanroom/specs/001c7680.md plus retail only.
// No decoder source was consulted.
//
// DeblockLoopFilteredBand_MMX (retail 0x001C7680, 5028 bytes): MMX band
// deblocker for the loop-filtered profile. Pass 1 filters the horizontal
// edge above every block of the band (eight columns per step as two
// four-lane halves, q from the block below the edge, q of 3 or less copies
// rows -4..+3 unchanged); pass 2 filters the vertical edges between
// neighbouring blocks in place on the destination, eight rows up, staging
// each row's ten samples as 16-bit values. Each side's activity is summed
// from two four-lane partials into the per-block variance accumulators.

// Retail 0x009B7F90: four 16-bit lanes of 3.
extern "C" unsigned short g_vp6MmxThrees[4] = {
	3, 3, 3, 3
};
// Retail 0x009B7FA0: four 16-bit lanes of 4 (shared with the wide
// accumulator unit that owns it).
extern "C" unsigned char Vp6WideAccumConst86D0[8];

// Post-processor instance view: per-block q index and variance arrays.
struct DeblockBandMmxContext
{
	unsigned char m_pad00[0x24];
	unsigned int *m_qIndex;
	int *m_variance;
};

extern "C" void __cdecl DeblockLoopFilteredBand_MMX(DeblockBandMmxContext *ctx, unsigned char *source, unsigned char *destination, unsigned int stride, unsigned int count, unsigned int first, const unsigned int *limits)
{
	__declspec(align(16)) unsigned short staging[64];
	__declspec(align(16)) unsigned short rows[80];
	__declspec(align(16)) unsigned short smoothLimit[4];
	__declspec(align(16)) unsigned short qv[4];
	__declspec(align(16)) unsigned short lowerActivity[4];
	__declspec(align(16)) unsigned short upperActivity[4];
	__declspec(align(16)) unsigned short lowerActivity2[4];
	__declspec(align(16)) unsigned short upperActivity2[4];
	unsigned char *src;
	unsigned char *dst;
	unsigned int index;
	unsigned int end;
	unsigned int q;

	src = source;
	index = first;
	dst = destination;
	end = first + count;
	for (; index < end; index++) {
		q = limits[ctx->m_qIndex[index + count]];
		if (q > 3) {
			qv[0] = (unsigned short)q;
			qv[1] = (unsigned short)q;
			qv[2] = (unsigned short)q;
			qv[3] = (unsigned short)q;
			__asm {
		push eax
		push ebp
		push ecx
		push edx
		push esi
		push edi
		movq mm0, qword ptr qv
		movq mm1, qword ptr g_vp6MmxThrees
		pmullw mm1, mm0
		pmullw mm1, mm0
		psrlw mm1, 5
		movq qword ptr smoothLimit, mm1
		mov eax, dword ptr src
		xor edx, edx
		lea esi, staging
		lea edi, rows
		mov ecx, stride
		pxor mm7, mm7
		sub edx, ecx
		lea eax, [eax+edx*4]
		movq mm0, qword ptr [eax+edx]
		movq mm1, mm0
		punpcklbw mm0, mm7
		movq mm2, qword ptr [eax]
		movq mm3, mm2
		punpckhbw mm1, mm7
		movq qword ptr [edi], mm0
		punpcklbw mm2, mm7
		punpckhbw mm3, mm7
		movq qword ptr [edi+8], mm1
		movq mm4, qword ptr [eax+ecx]
		movq qword ptr [edi+0x10], mm2
		movq qword ptr [edi+0x18], mm3
		movq mm5, mm4
		punpcklbw mm4, mm7
		movq mm0, qword ptr [eax+ecx*2]
		punpckhbw mm5, mm7
		movq mm1, mm0
		movq qword ptr [edi+0x20], mm4
		punpcklbw mm0, mm7
		lea eax, [eax+ecx*4]
		movq qword ptr [edi+0x28], mm5
		punpckhbw mm1, mm7
		movq mm2, qword ptr [eax+edx]
		movq qword ptr [edi+0x30], mm0
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq qword ptr [edi+0x38], mm1
		punpckhbw mm3, mm7
		movq mm4, qword ptr [eax]
		movq qword ptr [edi+0x40], mm2
		movq mm5, mm4
		movq qword ptr [edi+0x48], mm3
		punpcklbw mm4, mm7
		punpckhbw mm5, mm7
		movq mm0, qword ptr [eax+ecx]
		movq qword ptr [edi+0x50], mm4
		movq mm1, mm0
		movq qword ptr [edi+0x58], mm5
		punpcklbw mm0, mm7
		punpckhbw mm1, mm7
		movq mm2, qword ptr [eax+ecx*2]
		lea eax, [eax+ecx*4]
		movq mm3, mm2
		movq qword ptr [edi+0x60], mm0
		punpcklbw mm2, mm7
		punpckhbw mm3, mm7
		movq mm4, qword ptr [eax+edx]
		movq qword ptr [edi+0x68], mm1
		movq mm5, mm4
		punpcklbw mm4, mm7
		movq qword ptr [edi+0x70], mm2
		movq qword ptr [edi+0x78], mm3
		movq mm0, qword ptr [eax]
		punpckhbw mm5, mm7
		movq mm1, mm0
		movq qword ptr [edi+0x80], mm4
		punpcklbw mm0, mm7
		punpckhbw mm1, mm7
		movq qword ptr [edi+0x88], mm5
		movq qword ptr [edi+0x90], mm0
		movq qword ptr [edi+0x98], mm1
		pcmpeqw mm3, mm3
		psllw mm3, 0xf
		psrlw mm3, 8
		movq mm2, qword ptr [edi+0x10]
		movq mm6, qword ptr [edi+0x50]
		psubw mm2, mm3
		psubw mm6, mm3
		movq mm0, mm2
		movq mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		movq mm1, mm2
		movq mm5, mm6
		movq mm2, qword ptr [edi+0x20]
		movq mm6, qword ptr [edi+0x60]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi+0x30]
		movq mm6, qword ptr [edi+0x70]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi+0x40]
		movq mm6, qword ptr [edi+0x80]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm7, mm3
		psrlw mm7, 7
		movq mm2, mm0
		movq mm6, mm4
		paddw mm0, mm7
		paddw mm4, mm7
		psraw mm2, 1
		psraw mm6, 1
		psraw mm0, 1
		psraw mm4, 1
		pmullw mm2, mm0
		pmullw mm6, mm4
		psubw mm1, mm2
		psubw mm5, mm6
		movq mm7, qword ptr smoothLimit
		movq mm2, mm1
		movq mm6, mm5
		movq qword ptr upperActivity, mm1
		movq qword ptr lowerActivity, mm5
		psubw mm1, mm7
		psubw mm5, mm7
		psraw mm2, 0xf
		psraw mm6, 0xf
		psraw mm1, 0xf
		psraw mm5, 0xf
		movq mm7, qword ptr [edi+0x40]
		pandn mm2, mm1
		pandn mm6, mm5
		movq mm4, qword ptr [edi+0x50]
		pand mm6, mm2
		movq mm2, mm7
		psubusw mm7, mm4
		psubusw mm4, mm2
		por mm7, mm4
		psubw mm7, qword ptr qv
		psraw mm7, 0xf
		pand mm7, mm6
		add edi, 8
		movq mm2, qword ptr [edi+0x10]
		movq mm6, qword ptr [edi+0x50]
		psubw mm2, mm3
		psubw mm6, mm3
		movq mm0, mm2
		movq mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		movq mm1, mm2
		movq mm5, mm6
		movq mm2, qword ptr [edi+0x20]
		movq mm6, qword ptr [edi+0x60]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi+0x30]
		movq mm6, qword ptr [edi+0x70]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi+0x40]
		movq mm6, qword ptr [edi+0x80]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		psrlw mm3, 7
		movq mm2, mm0
		movq mm6, mm4
		paddw mm0, mm3
		paddw mm4, mm3
		psraw mm2, 1
		psraw mm6, 1
		psraw mm0, 1
		psraw mm4, 1
		pmullw mm2, mm0
		pmullw mm6, mm4
		psubw mm1, mm2
		psubw mm5, mm6
		movq qword ptr upperActivity2, mm1
		movq qword ptr lowerActivity2, mm5
		movq mm3, qword ptr smoothLimit
		movq mm2, mm1
		movq mm6, mm5
		psubw mm1, mm3
		psubw mm5, mm3
		psraw mm2, 0xf
		psraw mm6, 0xf
		psraw mm1, 0xf
		psraw mm5, 0xf
		movq mm0, qword ptr [edi+0x40]
		pandn mm2, mm1
		pandn mm6, mm5
		movq mm4, qword ptr [edi+0x50]
		pand mm6, mm2
		movq mm2, mm0
		psubusw mm0, mm4
		psubusw mm4, mm2
		por mm0, mm4
		psubw mm0, qword ptr qv
		psraw mm0, 0xf
		pand mm0, mm6
		sub edi, 8
		movq mm5, qword ptr [edi]
		movq mm4, qword ptr [edi+0x10]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr qv
		psraw mm4, 0xf
		movq mm1, mm4
		pand mm4, mm6
		pandn mm1, mm3
		por mm1, mm4
		movq mm4, qword ptr [edi+0x80]
		movq mm5, qword ptr [edi+0x90]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr qv
		psraw mm4, 0xf
		movq mm2, mm4
		pand mm4, mm6
		pandn mm2, mm3
		por mm2, mm4
		movq mm3, mm1
		paddw mm3, mm3
		paddw mm3, mm1
		movq mm4, qword ptr [edi+0x10]
		paddw mm3, qword ptr [edi+0x20]
		paddw mm4, qword ptr [edi+0x30]
		paddw mm3, qword ptr [edi+0x40]
		paddw mm4, qword ptr Vp6WideAccumConst86D0
		paddw mm3, mm4
		movq mm4, mm3
		movq mm5, qword ptr [edi+0x10]
		paddw mm4, mm5
		psllw mm4, 1
		psubw mm4, qword ptr [edi+0x40]
		paddw mm4, qword ptr [edi+0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi], mm4
		movq mm5, qword ptr [edi+0x20]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi+0x50]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi+0x50]
		paddw mm4, qword ptr [edi+0x60]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi+0x10], mm4
		movq mm5, qword ptr [edi+0x30]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi+0x60]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi+0x60]
		paddw mm4, qword ptr [edi+0x70]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi+0x20], mm4
		movq mm5, qword ptr [edi+0x40]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi+0x70]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, mm1
		psubw mm4, qword ptr [edi+0x10]
		psubw mm4, qword ptr [edi+0x70]
		paddw mm4, qword ptr [edi+0x80]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi+0x30], mm4
		movq mm5, qword ptr [edi+0x50]
		psubw mm3, qword ptr [edi+0x10]
		paddw mm3, qword ptr [edi+0x80]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x10]
		psubw mm4, qword ptr [edi+0x20]
		psubw mm4, qword ptr [edi+0x80]
		paddw mm4, mm2
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi+0x40], mm4
		movq mm5, qword ptr [edi+0x60]
		psubw mm3, qword ptr [edi+0x20]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x20]
		psubw mm4, qword ptr [edi+0x30]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi+0x50], mm4
		movq mm5, qword ptr [edi+0x70]
		psubw mm3, qword ptr [edi+0x30]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x30]
		psubw mm4, qword ptr [edi+0x40]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi+0x60], mm4
		movq mm5, qword ptr [edi+0x80]
		psubw mm3, qword ptr [edi+0x40]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x40]
		psubw mm4, qword ptr [edi+0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi+0x70], mm4
		add edi, 8
		add esi, 8
		movq mm5, qword ptr [edi]
		movq mm4, qword ptr [edi+0x10]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr qv
		psraw mm4, 0xf
		movq mm1, mm4
		pand mm4, mm6
		pandn mm1, mm3
		por mm1, mm4
		movq mm4, qword ptr [edi+0x80]
		movq mm5, qword ptr [edi+0x90]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr qv
		psraw mm4, 0xf
		movq mm2, mm4
		pand mm4, mm6
		pandn mm2, mm3
		por mm2, mm4
		movq mm3, mm1
		paddw mm3, mm3
		paddw mm3, mm1
		movq mm4, qword ptr [edi+0x10]
		paddw mm3, qword ptr [edi+0x20]
		paddw mm4, qword ptr [edi+0x30]
		paddw mm3, qword ptr [edi+0x40]
		paddw mm4, qword ptr Vp6WideAccumConst86D0
		paddw mm3, mm4
		movq mm4, mm3
		movq mm5, qword ptr [edi+0x10]
		paddw mm4, mm5
		psllw mm4, 1
		psubw mm4, qword ptr [edi+0x40]
		paddw mm4, qword ptr [edi+0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi], mm4
		movq mm5, qword ptr [edi+0x20]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi+0x50]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi+0x50]
		paddw mm4, qword ptr [edi+0x60]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi+0x10], mm4
		movq mm5, qword ptr [edi+0x30]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi+0x60]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi+0x60]
		paddw mm4, qword ptr [edi+0x70]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi+0x20], mm4
		movq mm5, qword ptr [edi+0x40]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi+0x70]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, mm1
		psubw mm4, qword ptr [edi+0x10]
		psubw mm4, qword ptr [edi+0x70]
		paddw mm4, qword ptr [edi+0x80]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi+0x30], mm4
		movq mm5, qword ptr [edi+0x50]
		psubw mm3, qword ptr [edi+0x10]
		paddw mm3, qword ptr [edi+0x80]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x10]
		psubw mm4, qword ptr [edi+0x20]
		psubw mm4, qword ptr [edi+0x80]
		paddw mm4, mm2
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi+0x40], mm4
		movq mm5, qword ptr [edi+0x60]
		psubw mm3, qword ptr [edi+0x20]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x20]
		psubw mm4, qword ptr [edi+0x30]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi+0x50], mm4
		movq mm5, qword ptr [edi+0x70]
		psubw mm3, qword ptr [edi+0x30]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x30]
		psubw mm4, qword ptr [edi+0x40]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi+0x60], mm4
		movq mm5, qword ptr [edi+0x80]
		psubw mm3, qword ptr [edi+0x40]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x40]
		psubw mm4, qword ptr [edi+0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi+0x70], mm4
		add edi, 8
		sub esi, 8
		mov ebp, dword ptr dst
		lea ebp, [ebp+edx*4]
		movq mm0, qword ptr [esi]
		packuswb mm0, qword ptr [esi+8]
		movq qword ptr [ebp], mm0
		movq mm1, qword ptr [esi+0x10]
		packuswb mm1, qword ptr [esi+0x18]
		movq qword ptr [ebp+ecx], mm1
		movq mm2, qword ptr [esi+0x20]
		packuswb mm2, qword ptr [esi+0x28]
		movq qword ptr [ebp+ecx*2], mm2
		movq mm3, qword ptr [esi+0x30]
		packuswb mm3, qword ptr [esi+0x38]
		lea ebp, [ebp+ecx*4]
		movq qword ptr [ebp+edx], mm3
		movq mm0, qword ptr [esi+0x40]
		packuswb mm0, qword ptr [esi+0x48]
		movq qword ptr [ebp], mm0
		movq mm1, qword ptr [esi+0x50]
		packuswb mm1, qword ptr [esi+0x58]
		movq qword ptr [ebp+ecx], mm1
		movq mm2, qword ptr [esi+0x60]
		packuswb mm2, qword ptr [esi+0x68]
		movq qword ptr [ebp+ecx*2], mm2
		movq mm3, qword ptr [esi+0x70]
		packuswb mm3, qword ptr [esi+0x78]
		lea ebp, [ebp+ecx*2]
		movq qword ptr [ebp+ecx], mm3
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebp
		pop eax
			}
			ctx->m_variance[index] += upperActivity[0] + upperActivity[1] + upperActivity[2] + upperActivity[3] + upperActivity2[0] + upperActivity2[1] + upperActivity2[2] + upperActivity2[3];
			ctx->m_variance[index + count] += lowerActivity[0] + lowerActivity[1] + lowerActivity[2] + lowerActivity[3] + lowerActivity2[0] + lowerActivity2[1] + lowerActivity2[2] + lowerActivity2[3];
		} else {
			__asm {
		push esi
		push edi
		push ecx
		mov esi, dword ptr src
		mov edi, dword ptr dst
		push edx
		mov ecx, stride
		xor edx, edx
		sub edx, ecx
		lea esi, [esi+edx*4]
		movq mm0, qword ptr [esi]
		movq qword ptr [edi+edx*4], mm0
		lea edi, [edi+edx*4]
		movq mm1, qword ptr [esi+ecx]
		movq qword ptr [edi+ecx], mm1
		movq mm2, qword ptr [esi+ecx*2]
		lea esi, [esi+ecx*4]
		movq qword ptr [edi+ecx*2], mm2
		lea edi, [edi+ecx*4]
		movq mm3, qword ptr [esi+edx]
		movq qword ptr [edi+edx], mm3
		movq mm4, qword ptr [esi]
		movq mm5, qword ptr [esi+ecx]
		movq qword ptr [edi], mm4
		movq mm6, qword ptr [esi+ecx*2]
		lea esi, [esi+ecx*4]
		movq qword ptr [edi+ecx], mm5
		movq qword ptr [edi+ecx*2], mm6
		movq mm7, qword ptr [esi+edx]
		lea edi, [edi+ecx*4]
		movq qword ptr [edi+edx], mm7
		pop edx
		pop ecx
		pop edi
		pop esi
			}
		}
		src += 8;
		dst += 8;
	}
	dst += 8 - (stride << 3) - (count << 3);
	src = dst;
	for (index = first; index < end - 1; index++, src += 8, dst += 8) {
		q = limits[ctx->m_qIndex[index + 1]];
		if (q > 3) {
			qv[0] = (unsigned short)q;
			qv[1] = (unsigned short)q;
			qv[2] = (unsigned short)q;
			qv[3] = (unsigned short)q;
			rows[0] = src[-5];
			rows[72] = src[4];
			rows[1] = src[stride - 5];
			rows[73] = src[stride + 4];
			rows[2] = src[stride * 2 - 5];
			rows[74] = src[stride * 2 + 4];
			rows[3] = src[stride * 3 - 5];
			rows[75] = src[stride * 3 + 4];
			rows[4] = src[stride * 4 - 5];
			rows[76] = src[stride * 4 + 4];
			rows[5] = src[stride * 5 - 5];
			rows[77] = src[stride * 5 + 4];
			rows[6] = src[stride * 6 - 5];
			rows[78] = src[stride * 6 + 4];
			rows[7] = src[stride * 7 - 5];
			rows[79] = src[stride * 7 + 4];
			__asm {
		push eax
		push ebp
		push ecx
		push edx
		push esi
		push edi
		movq mm0, qword ptr qv
		movq mm1, qword ptr g_vp6MmxThrees
		pmullw mm1, mm0
		pmullw mm1, mm0
		psrlw mm1, 5
		movq qword ptr smoothLimit, mm1
		mov eax, dword ptr src
		xor edx, edx
		sub eax, 4
		lea esi, staging
		lea edi, rows
		mov ecx, stride
		sub edx, ecx
		movq mm0, qword ptr [eax]
		movq mm1, qword ptr [eax+ecx]
		movq mm2, qword ptr [eax+ecx*2]
		lea eax, [eax+ecx*4]
		movq mm3, qword ptr [eax+edx]
		movq mm4, mm0
		punpcklbw mm0, mm1
		punpckhbw mm4, mm1
		movq mm5, mm2
		punpcklbw mm2, mm3
		punpckhbw mm5, mm3
		movq mm1, mm0
		punpcklwd mm0, mm2
		punpckhwd mm1, mm2
		movq mm2, mm4
		punpckhwd mm4, mm5
		punpcklwd mm2, mm5
		pxor mm7, mm7
		movq mm5, mm0
		punpcklbw mm0, mm7
		movq qword ptr [edi+0x10], mm0
		punpckhbw mm5, mm7
		movq mm0, mm1
		movq qword ptr [edi+0x20], mm5
		punpcklbw mm1, mm7
		punpckhbw mm0, mm7
		movq qword ptr [edi+0x30], mm1
		movq mm3, mm2
		movq mm5, mm4
		movq qword ptr [edi+0x40], mm0
		punpcklbw mm2, mm7
		punpckhbw mm3, mm7
		movq qword ptr [edi+0x50], mm2
		punpcklbw mm4, mm7
		punpckhbw mm5, mm7
		movq qword ptr [edi+0x60], mm3
		movq mm0, qword ptr [eax]
		movq mm1, qword ptr [eax+ecx]
		movq qword ptr [edi+0x70], mm4
		movq mm2, qword ptr [eax+ecx*2]
		lea eax, [eax+ecx*4]
		movq qword ptr [edi+0x80], mm5
		movq mm4, mm0
		movq mm3, qword ptr [eax+edx]
		punpcklbw mm0, mm1
		punpckhbw mm4, mm1
		movq mm5, mm2
		punpcklbw mm2, mm3
		punpckhbw mm5, mm3
		movq mm1, mm0
		punpcklwd mm0, mm2
		punpckhwd mm1, mm2
		movq mm2, mm4
		punpckhwd mm4, mm5
		punpcklwd mm2, mm5
		movq mm5, mm0
		punpcklbw mm0, mm7
		movq qword ptr [edi+0x18], mm0
		punpckhbw mm5, mm7
		movq mm0, mm1
		movq qword ptr [edi+0x28], mm5
		punpcklbw mm1, mm7
		punpckhbw mm0, mm7
		movq qword ptr [edi+0x38], mm1
		movq mm3, mm2
		movq mm5, mm4
		movq qword ptr [edi+0x48], mm0
		punpcklbw mm2, mm7
		punpckhbw mm3, mm7
		movq qword ptr [edi+0x58], mm2
		punpcklbw mm4, mm7
		punpckhbw mm5, mm7
		movq qword ptr [edi+0x68], mm3
		movq qword ptr [edi+0x78], mm4
		movq qword ptr [edi+0x88], mm5
		pcmpeqw mm3, mm3
		psllw mm3, 0xf
		psrlw mm3, 8
		movq mm2, qword ptr [edi+0x10]
		movq mm6, qword ptr [edi+0x50]
		psubw mm2, mm3
		psubw mm6, mm3
		movq mm0, mm2
		movq mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		movq mm1, mm2
		movq mm5, mm6
		movq mm2, qword ptr [edi+0x20]
		movq mm6, qword ptr [edi+0x60]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi+0x30]
		movq mm6, qword ptr [edi+0x70]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi+0x40]
		movq mm6, qword ptr [edi+0x80]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm7, mm3
		psrlw mm7, 7
		movq mm2, mm0
		movq mm6, mm4
		paddw mm0, mm7
		paddw mm4, mm7
		psraw mm2, 1
		psraw mm6, 1
		psraw mm0, 1
		psraw mm4, 1
		pmullw mm2, mm0
		pmullw mm6, mm4
		psubw mm1, mm2
		psubw mm5, mm6
		movq qword ptr upperActivity, mm1
		movq qword ptr lowerActivity, mm5
		movq mm7, qword ptr smoothLimit
		movq mm2, mm1
		movq mm6, mm5
		psubw mm1, mm7
		psubw mm5, mm7
		psraw mm1, 0xf
		psraw mm5, 0xf
		psraw mm2, 0xf
		psraw mm6, 0xf
		movq mm7, qword ptr [edi+0x40]
		pandn mm2, mm1
		pandn mm6, mm5
		movq mm4, qword ptr [edi+0x50]
		pand mm6, mm2
		movq mm2, mm7
		psubusw mm7, mm4
		psubusw mm4, mm2
		por mm7, mm4
		psubw mm7, qword ptr qv
		psraw mm7, 0xf
		pand mm7, mm6
		add edi, 8
		movq mm2, qword ptr [edi+0x10]
		movq mm6, qword ptr [edi+0x50]
		psubw mm2, mm3
		psubw mm6, mm3
		movq mm0, mm2
		movq mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		movq mm1, mm2
		movq mm5, mm6
		movq mm2, qword ptr [edi+0x20]
		movq mm6, qword ptr [edi+0x60]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi+0x30]
		movq mm6, qword ptr [edi+0x70]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi+0x40]
		movq mm6, qword ptr [edi+0x80]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		psrlw mm3, 7
		movq mm2, mm0
		movq mm6, mm4
		paddw mm0, mm3
		paddw mm4, mm3
		psraw mm2, 1
		psraw mm6, 1
		psraw mm0, 1
		psraw mm4, 1
		pmullw mm2, mm0
		pmullw mm6, mm4
		psubw mm1, mm2
		psubw mm5, mm6
		movq qword ptr upperActivity2, mm1
		movq qword ptr lowerActivity2, mm5
		movq mm3, qword ptr smoothLimit
		movq mm2, mm1
		movq mm6, mm5
		psubw mm1, mm3
		psubw mm5, mm3
		psraw mm6, 0xf
		psraw mm2, 0xf
		psraw mm1, 0xf
		psraw mm5, 0xf
		movq mm0, qword ptr [edi+0x40]
		pandn mm2, mm1
		pandn mm6, mm5
		movq mm4, qword ptr [edi+0x50]
		pand mm6, mm2
		movq mm2, mm0
		psubusw mm0, mm4
		psubusw mm4, mm2
		por mm0, mm4
		psubw mm0, qword ptr qv
		psraw mm0, 0xf
		pand mm0, mm6
		sub edi, 8
		movq mm5, qword ptr [edi]
		movq mm4, qword ptr [edi+0x10]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr qv
		psraw mm4, 0xf
		movq mm1, mm4
		pand mm4, mm6
		pandn mm1, mm3
		por mm1, mm4
		movq mm4, qword ptr [edi+0x80]
		movq mm5, qword ptr [edi+0x90]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr qv
		psraw mm4, 0xf
		movq mm2, mm4
		pand mm4, mm6
		pandn mm2, mm3
		por mm2, mm4
		movq mm3, mm1
		paddw mm3, mm3
		paddw mm3, mm1
		movq mm4, qword ptr [edi+0x10]
		paddw mm3, qword ptr [edi+0x20]
		paddw mm4, qword ptr [edi+0x30]
		paddw mm3, qword ptr [edi+0x40]
		paddw mm4, qword ptr Vp6WideAccumConst86D0
		paddw mm3, mm4
		movq mm4, mm3
		movq mm5, qword ptr [edi+0x10]
		paddw mm4, mm5
		psllw mm4, 1
		psubw mm4, qword ptr [edi+0x40]
		paddw mm4, qword ptr [edi+0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi], mm4
		movq mm5, qword ptr [edi+0x20]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi+0x50]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi+0x50]
		paddw mm4, qword ptr [edi+0x60]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi+0x10], mm4
		movq mm5, qword ptr [edi+0x30]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi+0x60]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi+0x60]
		paddw mm4, qword ptr [edi+0x70]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi+0x20], mm4
		movq mm5, qword ptr [edi+0x40]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi+0x70]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, mm1
		psubw mm4, qword ptr [edi+0x10]
		psubw mm4, qword ptr [edi+0x70]
		paddw mm4, qword ptr [edi+0x80]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi+0x30], mm4
		movq mm5, qword ptr [edi+0x50]
		psubw mm3, qword ptr [edi+0x10]
		paddw mm3, qword ptr [edi+0x80]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x10]
		psubw mm4, qword ptr [edi+0x20]
		psubw mm4, qword ptr [edi+0x80]
		paddw mm4, mm2
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi+0x40], mm4
		movq mm5, qword ptr [edi+0x60]
		psubw mm3, qword ptr [edi+0x20]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x20]
		psubw mm4, qword ptr [edi+0x30]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi+0x50], mm4
		movq mm5, qword ptr [edi+0x70]
		psubw mm3, qword ptr [edi+0x30]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x30]
		psubw mm4, qword ptr [edi+0x40]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi+0x60], mm4
		movq mm5, qword ptr [edi+0x80]
		psubw mm3, qword ptr [edi+0x40]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x40]
		psubw mm4, qword ptr [edi+0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi+0x70], mm4
		add edi, 8
		add esi, 8
		movq mm5, qword ptr [edi]
		movq mm4, qword ptr [edi+0x10]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr qv
		psraw mm4, 0xf
		movq mm1, mm4
		pand mm4, mm6
		pandn mm1, mm3
		por mm1, mm4
		movq mm4, qword ptr [edi+0x80]
		movq mm5, qword ptr [edi+0x90]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr qv
		psraw mm4, 0xf
		movq mm2, mm4
		pand mm4, mm6
		pandn mm2, mm3
		por mm2, mm4
		movq mm3, mm1
		paddw mm3, mm3
		paddw mm3, mm1
		movq mm4, qword ptr [edi+0x10]
		paddw mm3, qword ptr [edi+0x20]
		paddw mm4, qword ptr [edi+0x30]
		paddw mm3, qword ptr [edi+0x40]
		paddw mm4, qword ptr Vp6WideAccumConst86D0
		paddw mm3, mm4
		movq mm4, mm3
		movq mm5, qword ptr [edi+0x10]
		paddw mm4, mm5
		psllw mm4, 1
		psubw mm4, qword ptr [edi+0x40]
		paddw mm4, qword ptr [edi+0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi], mm4
		movq mm5, qword ptr [edi+0x20]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi+0x50]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi+0x50]
		paddw mm4, qword ptr [edi+0x60]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi+0x10], mm4
		movq mm5, qword ptr [edi+0x30]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi+0x60]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi+0x60]
		paddw mm4, qword ptr [edi+0x70]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi+0x20], mm4
		movq mm5, qword ptr [edi+0x40]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi+0x70]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, mm1
		psubw mm4, qword ptr [edi+0x10]
		psubw mm4, qword ptr [edi+0x70]
		paddw mm4, qword ptr [edi+0x80]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi+0x30], mm4
		movq mm5, qword ptr [edi+0x50]
		psubw mm3, qword ptr [edi+0x10]
		paddw mm3, qword ptr [edi+0x80]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x10]
		psubw mm4, qword ptr [edi+0x20]
		psubw mm4, qword ptr [edi+0x80]
		paddw mm4, mm2
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi+0x40], mm4
		movq mm5, qword ptr [edi+0x60]
		psubw mm3, qword ptr [edi+0x20]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x20]
		psubw mm4, qword ptr [edi+0x30]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi+0x50], mm4
		movq mm5, qword ptr [edi+0x70]
		psubw mm3, qword ptr [edi+0x30]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x30]
		psubw mm4, qword ptr [edi+0x40]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi+0x60], mm4
		movq mm5, qword ptr [edi+0x80]
		psubw mm3, qword ptr [edi+0x40]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi+0x40]
		psubw mm4, qword ptr [edi+0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi+0x70], mm4
		mov eax, dword ptr dst
		add edi, 8
		sub esi, 8
		sub eax, 4
		movq mm0, qword ptr [esi]
		movq mm1, qword ptr [esi+0x10]
		movq mm4, mm0
		punpcklwd mm0, mm1
		punpckhwd mm4, mm1
		movq mm2, qword ptr [esi+0x20]
		movq mm3, qword ptr [esi+0x30]
		movq mm5, mm2
		punpcklwd mm2, mm3
		punpckhwd mm5, mm3
		movq mm1, mm0
		punpckldq mm0, mm2
		movq qword ptr [edi], mm0
		punpckhdq mm1, mm2
		movq mm0, mm4
		movq qword ptr [edi+0x10], mm1
		punpckldq mm0, mm5
		punpckhdq mm4, mm5
		movq mm1, qword ptr [esi+0x40]
		movq mm2, qword ptr [esi+0x50]
		movq mm5, qword ptr [esi+0x60]
		movq mm6, qword ptr [esi+0x70]
		movq mm3, mm1
		movq mm7, mm5
		punpcklwd mm1, mm2
		punpckhwd mm3, mm2
		punpcklwd mm5, mm6
		punpckhwd mm7, mm6
		movq mm2, mm1
		movq mm6, mm3
		punpckldq mm1, mm5
		punpckhdq mm2, mm5
		punpckldq mm3, mm7
		punpckhdq mm6, mm7
		movq mm5, qword ptr [edi]
		packuswb mm5, mm1
		movq qword ptr [eax], mm5
		movq mm7, qword ptr [edi+0x10]
		packuswb mm7, mm2
		movq qword ptr [eax+ecx], mm7
		packuswb mm0, mm3
		packuswb mm4, mm6
		movq qword ptr [eax+ecx*2], mm0
		lea eax, [eax+ecx*4]
		movq qword ptr [eax+edx], mm4
		add edi, 8
		add esi, 8
		movq mm0, qword ptr [esi]
		movq mm1, qword ptr [esi+0x10]
		movq mm4, mm0
		punpcklwd mm0, mm1
		punpckhwd mm4, mm1
		movq mm2, qword ptr [esi+0x20]
		movq mm3, qword ptr [esi+0x30]
		movq mm5, mm2
		punpcklwd mm2, mm3
		punpckhwd mm5, mm3
		movq mm1, mm0
		punpckldq mm0, mm2
		movq qword ptr [edi], mm0
		punpckhdq mm1, mm2
		movq mm0, mm4
		movq qword ptr [edi+0x10], mm1
		punpckldq mm0, mm5
		punpckhdq mm4, mm5
		movq mm1, qword ptr [esi+0x40]
		movq mm2, qword ptr [esi+0x50]
		movq mm5, qword ptr [esi+0x60]
		movq mm6, qword ptr [esi+0x70]
		movq mm3, mm1
		movq mm7, mm5
		punpcklwd mm1, mm2
		punpckhwd mm3, mm2
		punpcklwd mm5, mm6
		punpckhwd mm7, mm6
		movq mm2, mm1
		movq mm6, mm3
		punpckldq mm1, mm5
		punpckhdq mm2, mm5
		punpckldq mm3, mm7
		punpckhdq mm6, mm7
		movq mm5, qword ptr [edi]
		packuswb mm5, mm1
		movq qword ptr [eax], mm5
		movq mm7, qword ptr [edi+0x10]
		packuswb mm7, mm2
		movq qword ptr [eax+ecx], mm7
		packuswb mm0, mm3
		packuswb mm4, mm6
		movq qword ptr [eax+ecx*2], mm0
		lea eax, [eax+ecx*4]
		movq qword ptr [eax+edx], mm4
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebp
		pop eax
			}
			ctx->m_variance[index] += upperActivity[0] + upperActivity[1] + upperActivity[2] + upperActivity[3] + upperActivity2[0] + upperActivity2[1] + upperActivity2[2] + upperActivity2[3];
			ctx->m_variance[index + 1] += lowerActivity[0] + lowerActivity[1] + lowerActivity[2] + lowerActivity[3] + lowerActivity2[0] + lowerActivity2[1] + lowerActivity2[2] + lowerActivity2[3];
		}
	}
}
