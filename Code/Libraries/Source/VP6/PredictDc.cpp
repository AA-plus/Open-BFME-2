// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c5180.md plus retail only. No
// decoder source was consulted.
//
// VP6_PredictDC (retail 0x001C5180): the predicted DC is taken from the left
// and above block contexts whose frame matches the macroblock mode's frame
// (averaged, rounding toward zero, when both match), else from the last-DC
// entry for that frame. The block's first coefficient gains the prediction
// and the last-DC entry becomes the resulting coefficient.

struct Vp6PredictMacroblock
{
	unsigned char pad0[4];
	short *values;
	int selector;
};

struct Vp6PredictNeighbor
{
	unsigned char pad0[8];
	short selector;
	short value;
};

// Retail 0x00BD8D00: ten 32-bit mode-to-frame entries. The consumers
// read the low byte or word of each entry through this shared byte array.
unsigned char g_bfmeVp6SelectorMap[40] = {
    1, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  1, 0, 0, 0,  1, 0, 0, 0,
    2, 0, 0, 0,  2, 0, 0, 0,  1, 0, 0, 0,  2, 0, 0, 0,  2, 0, 0, 0
};

// RVA 0x001C5180
extern "C" void __cdecl VP6_PredictDC(Vp6PredictMacroblock *state, int block,
	short *output, const Vp6PredictNeighbor *left,
	const Vp6PredictNeighbor *above)
{
	unsigned char selector = g_bfmeVp6SelectorMap[state->selector * 4];
	unsigned char count = 0;
	int sum = 0;

	if ((unsigned short)selector == (unsigned short)above->selector) {
		sum = above->value;
		count = 1;
	}
	if ((unsigned short)selector == (unsigned short)left->selector) {
		sum += left->value;
		++count;
	}

	if (count == 0)
		sum = output[selector];
	else if (count == 2)
		sum = (sum + ((unsigned short)sum >> 15)) >> 1;

	state->values[block << 6] += (short)sum;
	output[selector] = state->values[block << 6];
}
