// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b70a0.md plus retail only.
// No decoder source was consulted.
//
// VP6_init_dequantizer (retail 0x001B70A0, 277 bytes): for the frame Q index
// q, fills the Y and UV dequantiser tables (64 shorts each, pointers at
// quantizer offsets 0x180 and 0x184) at every position named by the quant
// index bytes (0x140) with the AC threshold entry for q shifted left 2, and
// position 0 with the DC quantizer entry for q shifted left 2.

struct DequantizerState
{
	int m_qIndex;                     // 0x0
	void *m_unused4;
	char m_pad08[0x30];
	void *m_pad38;
	void *m_pad3C[1];
	unsigned char m_pad40[0x101];
	unsigned char m_scanIndex[0x3f];  // 0x141..0x17F, read from 0x141
	unsigned short *m_dequantY;       // 0x180
	unsigned short *m_dequantUV;      // 0x184
};

// Retail tables: Y AC thresholds (image 0x00BD7860), UV AC thresholds
// (0x00BD7960), Y DC quantizers (0x00BD7E60) and UV DC quantizers (0x00BD7EE0).
extern const unsigned short g_bfmeApplyTableA[];
extern const unsigned short g_bfmeApplyTableB[];
extern const unsigned short g_bfmeApplyTableC[];
extern const unsigned short g_bfmeApplyTableD[];

// RVA 0x001B70A0 (the version argument is unused)
extern "C" void __cdecl VP6_init_dequantizer(DequantizerState *s, int)
{
	unsigned char *p = s->m_scanIndex + 1;
	int count = 0x15;

	do
	{
		s->m_dequantY[p[-1]] = g_bfmeApplyTableA[s->m_qIndex * 2] << 2;
		s->m_dequantY[p[0]] = g_bfmeApplyTableA[s->m_qIndex * 2] << 2;
		s->m_dequantY[p[1]] = g_bfmeApplyTableA[s->m_qIndex * 2] << 2;
		p += 3;
	}
	while (--count != 0);

	s->m_dequantY[0] = g_bfmeApplyTableC[s->m_qIndex] << 2;

	p = s->m_scanIndex + 1;
	count = 0x15;

	do
	{
		s->m_dequantUV[p[-1]] = g_bfmeApplyTableB[s->m_qIndex * 2] << 2;
		s->m_dequantUV[p[0]] = g_bfmeApplyTableB[s->m_qIndex * 2] << 2;
		s->m_dequantUV[p[1]] = g_bfmeApplyTableB[s->m_qIndex * 2] << 2;
		p += 3;
	}
	while (--count != 0);

	s->m_dequantUV[0] = g_bfmeApplyTableD[s->m_qIndex] << 2;
}
