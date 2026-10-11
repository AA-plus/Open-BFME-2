// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001bcfc0.md plus retail only. No
// decoder source was consulted.
//
// ReadHeaderBits (retail 0x001BCFC0): reads 1..31 bits MSB first from the
// frame header reader. The 32-bit window keeps its unread bits at the top;
// when the request exceeds the bits available the next four buffer bytes are
// loaded big-endian as a fresh window.

struct Vp6HeaderReader
{
	const unsigned char *m_data;
	unsigned int m_value;
	unsigned int m_bits;
	unsigned int m_bytes;
};

// RVA 0x001BCFC0
extern "C" unsigned int __cdecl ReadHeaderBits(Vp6HeaderReader *state, unsigned int count)
{
	unsigned int bytes = state->m_bytes;
	const unsigned char *input = state->m_data;
	unsigned int bits = state->m_bits;
	unsigned int value = state->m_value;
	input += bytes;
	unsigned int result = 0;

	if (bits < count)
	{
		result = value >> (32 - bits);
		count -= bits;
		result <<= count;
		value = input[0];
		value = (value << 8) + input[1];
		value = (value << 8) + input[2];
		value = (value << 8) + input[3];
		bytes += 4;
		bits = 32;
	}

	state->m_value = value << count;
	state->m_bits = bits - count;
	state->m_bytes = bytes;
	return (value >> (32 - count)) | result;
}
