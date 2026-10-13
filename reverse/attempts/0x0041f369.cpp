// ?rva0041F369@ArmyDefinition@@QAEXXZ
// partial score=0.93 date=2026-10-13
// ?rva0041F369@Rva0041F760@@QAEXXZ
// partial score=0.93 date=2026-09-29
// ?rva0041F369@Rva0041F760@@QAEXXZ
// partial score=0.93 date=2026-09-29
// cl: /O1 /MD /arch:SSE

// ?rva0041F369@Rva0041F760@@QAEXXZ, retail 0x0041F369, 200 bytes. Normalizes
// the +4 pointer array's element floats at +4/+8/+0xC by 100.0f over their
// sums when positive. Target evidence: xorps-plus-movaps sums plus comiss
// guards plus divss-mulss rescales plus shared 100.0f at 0x00BC292C;
// caller at 0x0041F8D7 plus same +4/+8 array as Rva0041F760Dtor.

struct Rva0041F369Elem
{
	char m_pad00[4];
	float m_04;
	float m_08;
	float m_0C;
};

class Rva0041F760
{
public:
	void rva0041F369();
private:
	char m_pad00[4];
	Rva0041F369Elem **m_begin04;
	Rva0041F369Elem **m_end08;
};

// ?rva0041F369@Rva0041F760@@QAEXXZ present-unmatched
void Rva0041F760::rva0041F369()
{
	float sum04 = 0.0f;
	float sum08 = 0.0f;
	float sum0C = 0.0f;
	for (Rva0041F369Elem **p = m_begin04; p != m_end08; ++p)
	{
		Rva0041F369Elem *e = *p;
		sum08 += e->m_08;
		sum04 += e->m_04;
		sum0C += e->m_0C;
	}
	float k = 100.0f;
	if (sum04 > 0.0f)
	{
		float s = k / sum04;
		for (Rva0041F369Elem **p = m_begin04; p != m_end08; ++p)
			(*p)->m_04 *= s;
	}
	if (sum08 > 0.0f)
	{
		float s = k / sum08;
		for (Rva0041F369Elem **p = m_begin04; p != m_end08; ++p)
			(*p)->m_08 *= s;
	}
	if (sum0C > 0.0f)
	{
		k /= sum0C;
		for (Rva0041F369Elem **p = m_begin04; p != m_end08; ++p)
			(*p)->m_0C *= k;
	}
}
