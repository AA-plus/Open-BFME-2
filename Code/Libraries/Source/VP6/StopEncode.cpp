// cl: /DNDEBUG /MD /EHsc
// Clean room: reverse/vp6_cleanroom/specs/001bcc70.md plus retail only. No
// decoder source was consulted.
//
// VP6_StopEncode (retail 0x001BCC70): flushes the bool encoder. The low value
// is shifted up by 24, 16 or 8 minus (count & 7) depending on the count, its
// four bytes are written to the buffer most significant first and the byte
// position advances by four.

struct Vp6EncoderState
{
	int m_words[5];
	void *m_pointer;
};

// RVA 0x001BCC70
extern "C" void __cdecl VP6_StopEncode(Vp6EncoderState *state)
{
	int bit = state->m_words[3];
	int shift;
	if (bit < -16)
		shift = 24;
	else
	{
		shift = 16;
		if (bit >= -8)
			shift = 8;
	}
	shift -= bit & 7;
	state->m_words[0] = (unsigned int)state->m_words[0] << shift;
	((unsigned char *)state->m_pointer)[state->m_words[4]++] = ((unsigned char *)&state->m_words[0])[3];
	((unsigned char *)state->m_pointer)[state->m_words[4]++] = ((unsigned char *)&state->m_words[0])[2];
	((unsigned char *)state->m_pointer)[state->m_words[4]++] = ((unsigned char *)&state->m_words[0])[1];
	((unsigned char *)state->m_pointer)[state->m_words[4]++] = ((unsigned char *)&state->m_words[0])[0];
}
