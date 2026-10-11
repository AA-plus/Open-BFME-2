// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b7930.md plus retail only. No
// decoder source was consulted.
//
// Quantizer teardown (retail 0x001B7930): frees the raw Y and UV dequantiser
// allocations, zeroes the four pointer fields, frees the quantizer block and
// stores null through the caller's pointer.

void bfmeFreeOneJT(void *what); // 0x001B6410 duck_free

struct QUANTIZER
{
	unsigned char m_pad0[0x180];
	void *m_at180;
	void *m_at184;
	void *m_at188;
	void *m_at18C;
};

// RVA 0x001B7930
extern "C" void __cdecl VP6_DeleteQuantizer(void **what)
{
	QUANTIZER *self = (QUANTIZER *)*what;
	if (self != 0) {
		if (self->m_at188 != 0)
			bfmeFreeOneJT(self->m_at188);
		self->m_at188 = 0;
		self->m_at180 = 0;

		if (self->m_at18C != 0)
			bfmeFreeOneJT(self->m_at18C);
		self->m_at18C = 0;
		self->m_at184 = 0;

		bfmeFreeOneJT(*what);
		*what = 0;
	}
}
