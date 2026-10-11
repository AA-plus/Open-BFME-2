// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c4f80.md plus retail only. No
// decoder source was consulted.
//
// Equiprobable bool-coder symbol decode (retail 0x001C4F80, stack-argument
// form): the boundary is half of (range + 1), the window and range are reduced
// when the symbol is 1, both are doubled exactly once, and one bit is consumed
// from the refill count with a byte refill from the buffer when it expires.

struct Vp6BoolCoder
{
	unsigned char m_pad0[4];
	unsigned m_range;
	unsigned m_code;
	int m_bitsRemaining;
	unsigned m_inputCursor;
	const unsigned char *m_inputBase;
};

// RVA 0x001C4F80
extern "C" int __cdecl VP6_DecodeBool128(Vp6BoolCoder *state)
{
	unsigned range = state->m_range;
	unsigned code = state->m_code;
	int bitsRemaining = state->m_bitsRemaining;
	unsigned half = (range + 1) >> 1;
	unsigned threshold = half << 24;
	int bit;

	if (code >= threshold) {
		range -= half;
		code -= threshold;
		range <<= 1;
		code <<= 1;
		bit = 1;
	} else {
		range = half << 1;
		code <<= 1;
		bit = 0;
	}

	if (--bitsRemaining == 0) {
		bitsRemaining = 8;
		code |= state->m_inputBase[state->m_inputCursor];
		++state->m_inputCursor;
	}

	state->m_range = range;
	state->m_bitsRemaining = bitsRemaining;
	state->m_code = code;
	return bit;
}
