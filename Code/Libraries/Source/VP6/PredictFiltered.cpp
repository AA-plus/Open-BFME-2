// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001d8dd0.md plus retail only.
// No decoder source was consulted.
// VP6_PredictFiltered retail 0x001D8DD0 (170 bytes): builds the loop filtered
// 12x12 prediction neighbourhood of a block. The motion vector is reduced to
// whole pixels (rounding toward zero), the 12x12 region around the displaced
// reference is copied into the pitch-16 scratch block through the function
// pointer at retail 0x00E22D08, and the two edge loop filters (function
// pointers at retail 0x00E22FA8 and 0x00E22FB4) run over the fractional
// boundary offsets.

typedef void (__cdecl *PredictFilteredCopy)(void *, void *, int, int);
typedef void (__cdecl *PredictFilteredEdge)(void *, int, int);

extern void *g_bfmeSlotB40;                 // retail 0x00E22D08, 12x12 copy function pointer
// Matched DIR32 witness (w=1) places this callback slot at VA 0x00E22FA8
// in the zero-filled .data tail: the vertical-edge loop filter.
PredictFilteredEdge g_rva01356E8C;
// Matched DIR32 witness (w=1) places this callback slot at VA 0x00E22FB4
// in the zero-filled .data tail: the horizontal-edge loop filter.
PredictFilteredEdge g_rva01356E98;

struct PredictFilteredInstance
{
	unsigned char pad00[0x74];
	int currentStride;              // 0x74
	unsigned char pad78[4];
	int motionShift;                // 0x7C
	unsigned char pad80[8];
	int frameStride;                // 0x88
	unsigned char pad8C[0x13C - 0x8C];
	void *quantizer;                // 0x13C (its first dword is the frame q index)
	unsigned char pad140[0x290 - 0x140];
	void *scratch;                  // 0x290
};

extern "C" void __cdecl VP6_PredictFiltered(
	PredictFilteredInstance *pbi, void *reference, int motionX, int motionY)
{
	void *scratch = pbi->scratch;
	int scaledX = motionX;
	int scaledY = motionY;
	if (scaledX > 0) {
		scaledX >>= pbi->motionShift;
	} else {
		scaledX = -scaledX;
		scaledX >>= pbi->motionShift;
		scaledX = -scaledX;
	}
	if (scaledY > 0) {
		scaledY >>= pbi->motionShift;
	} else {
		scaledY = -scaledY;
		scaledY >>= pbi->motionShift;
		scaledY = -scaledY;
	}

	int source = pbi->frameStride * scaledY;
	source -= pbi->currentStride * 2 + 2;
	source += scaledX;
	source += (int)reference;
	((PredictFilteredCopy)g_bfmeSlotB40)((void *)source, scratch,
		pbi->currentStride, 0x10);

	scaledX = -scaledX;
	scaledY = -scaledY;
	scaledX &= 7;
	scaledY &= 7;
	if (scaledX != 0) {
		void *quantizer = *(void **)pbi->quantizer;
		g_rva01356E8C(quantizer, scaledX + (int)scratch + 2, 0x10);
	}
	if (scaledY != 0) {
		void *quantizer = *(void **)pbi->quantizer;
		scaledY += 2;
		scaledY <<= 4;
		scaledY += (int)scratch;
		g_rva01356E98(quantizer, scaledY, 0x10);
	}
}
