// cl: /O2 /G7 /DNDEBUG /MD
//
// Three unreferenced (no direct caller or table slot found) channel getters
// placed between StreakRendererClass and LightEnvironmentClass bodies: each
// picks one of three packed 32-bit words at +4/+8/+0x0C by index (1 and 2
// select +8 and +0x0C, anything else +4) and scales a part of it by 1/255.
// ?rva0014A150@Rva0014A150@@QBEMH@Z, retail 0x0014A150 (91 bytes): the
// word's high 16 bits.
// ?rva0014A1B0@Rva0014A150@@QBEMH@Z, retail 0x0014A1B0 (64 bytes): the word
// shifted right by 8, as unsigned.
// ?rva0014A1F0@Rva0014A150@@QBEMH@Z, retail 0x0014A1F0 (61 bytes): the
// whole word, as unsigned.
// x87 conversions (no /arch:SSE); /O2 /G7 gives the sub-based case chain.
// Address-derived names.
struct Rva0014A150Word
{
	unsigned short m_lo;
	unsigned short m_hi;
};

class Rva0014A150
{
public:
	float rva0014A150(int index) const;
	float rva0014A1B0(int index) const;
	float rva0014A1F0(int index) const;
private:
	unsigned char m_pad00[4];
	unsigned int m_words[3];	// +0x04
};

float Rva0014A150::rva0014A150(int index) const
{
	const unsigned int *word;
	switch (index)
	{
	case 0:
		word = &m_words[0];
		break;
	case 1:
		word = &m_words[1];
		break;
	case 2:
		word = &m_words[2];
		break;
	default:
		word = &m_words[0];
		break;
	}
	return (float)((const Rva0014A150Word *)word)->m_hi * (1.0f / 255.0f);
}

float Rva0014A150::rva0014A1B0(int index) const
{
	const unsigned int *word;
	switch (index)
	{
	case 0:
		word = &m_words[0];
		break;
	case 1:
		word = &m_words[1];
		break;
	case 2:
		word = &m_words[2];
		break;
	default:
		word = &m_words[0];
		break;
	}
	return (float)(*word >> 8) * (1.0f / 255.0f);
}

float Rva0014A150::rva0014A1F0(int index) const
{
	const unsigned int *word;
	switch (index)
	{
	case 0:
		word = &m_words[0];
		break;
	case 1:
		word = &m_words[1];
		break;
	case 2:
		word = &m_words[2];
		break;
	default:
		word = &m_words[0];
		break;
	}
	return (float)*word * (1.0f / 255.0f);
}
