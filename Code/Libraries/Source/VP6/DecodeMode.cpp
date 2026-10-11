// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c59f0.md plus retail only.
// No decoder source was consulted.
//
// VP6_DecodeMode (retail 0x001C59F0, 270 bytes): reads one coding mode with the
// primary bool coder (instance offset 0x150). A bool with the same-mode
// probability (0x77C, 10 bytes per context type) returns the previous mode;
// otherwise the nine tree probabilities of the (type, previous mode) pair
// (0x7A4, 9 bytes per pair) steer the binary mode tree.

extern "C" int __cdecl VP6_DecodeBool(void *state, int probability);

// RVA 0x001C59F0
extern "C" int __cdecl VP6_DecodeMode(unsigned char *pbi, int previousMode, int contextType)
{
	void *state = pbi + 0x150;
	int result;

	if (VP6_DecodeBool(state, pbi[0x77C + 10 * contextType + previousMode])) {
		result = previousMode;
		goto done;
	}

	unsigned char *node = pbi + 0x7A4 + 9 * (10 * contextType + previousMode);
	if (VP6_DecodeBool(state, node[0])) {
		if (VP6_DecodeBool(state, node[2])) {
			if (VP6_DecodeBool(state, node[6]))
				result = VP6_DecodeBool(state, node[8]) + 8;
			else
				result = VP6_DecodeBool(state, node[7]) + 5;
			goto done;
		}

		result = 1;
		if (VP6_DecodeBool(state, node[5]))
			result = 7;
		goto done;
	}

	if (VP6_DecodeBool(state, node[1]))
		result = VP6_DecodeBool(state, node[4]) + 3;
	else
		result = VP6_DecodeBool(state, node[3]) * 2;

done:
	return result;
}
