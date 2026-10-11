// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c4f00.md and 001c5100.md plus
// retail only. No decoder source was consulted.
//
// Bool-coder symbol decode (retail 0x001C4F00 VP6_DecodeBool, 0x001C5100
// nDecodeBool): boundary = 1 + ((range - 1) * probability >> 8), compared
// against the window's top byte, then renormalised by doubling with a byte
// refill whenever the bit count expires. The two bodies behave identically
// but retail schedules them differently, so each keeps its own shape.

struct Vp6BoolCoderState
{
	unsigned char m_pad0[4];
	unsigned m_range;
	unsigned m_code;
	int m_bitsRemaining;
	unsigned m_inputCursor;
	const unsigned char *m_inputBase;
};

// RVA 0x001C4F00
// This copy updates the bit count only after renormalization.
extern "C" int __cdecl VP6_DecodeBool(void *rawState, int probability)
{
	Vp6BoolCoderState *state = (Vp6BoolCoderState *)rawState;
	unsigned oldRange = state->m_range;
	unsigned range = ((oldRange - 1) * probability) >> 8;
	int bitsRemaining = state->m_bitsRemaining;
	unsigned code = state->m_code;
	int bit = 0;
	++range;
	unsigned threshold = range << 24;
	if (code >= threshold) {
		range = oldRange - range;
		code -= threshold;
		bit = 1;
	}
	if (range < 0x80) {
		do {
			range += range;
			code += code;
			if (--bitsRemaining == 0) {
				code |= state->m_inputBase[state->m_inputCursor];
				bitsRemaining = 8;
				++state->m_inputCursor;
			}
		} while (range < 0x80);
		state->m_bitsRemaining = bitsRemaining;
	}
	state->m_code = code;
	state->m_range = range;
	return bit;
}

// RVA 0x001C5100
extern "C" int __cdecl nDecodeBool(Vp6BoolCoderState *state, int probability)
{
	int bitsRemaining = state->m_bitsRemaining;
	unsigned code = state->m_code;
	unsigned range = state->m_range;
	int bit = 0;
	unsigned split = (((range - 1) * probability) >> 8) + 1;
	unsigned threshold = split << 24;

	if (code >= threshold) {
		range -= split;
		code -= threshold;
		bit = 1;
	} else {
		range = split;
	}

	while (range < 0x80) {
		range += range;
		code += code;
		if (--bitsRemaining == 0) {
			code |= state->m_inputBase[state->m_inputCursor];
			bitsRemaining = 8;
			++state->m_inputCursor;
		}
	}

	state->m_range = range;
	state->m_code = code;
	state->m_bitsRemaining = bitsRemaining;
	return bit;
}
