// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b8430.md 001b8a40.md plus retail
// only. No decoder source was consulted.
//
// Separable bilinear 8x8 two-pass filters (retail 0x001B8430 FilterBlock2dBil
// with 16-bit output, 0x001B8A40 FilterBlock2dBil_8 with byte output, 295
// bytes each). The horizontal pass is inlined: nine source rows (advancing by
// the pixels per line), each of eight positions is first weight times the
// pixel plus second weight times its right neighbour, plus 64, shifted right
// 7, stored as a dword in the shared scratch buffer (image 0x00DFDA58, eight
// dwords per row). The matching second pass then runs on the scratch buffer
// with (scratch, output, 8, 8, 8, 8, vertical weights).

extern int g_bfmeTableC7E0;

extern "C" void __cdecl FilterBlock2dBil_SecondPass(
	int *, unsigned short *, int, int, int, int, const int *);
extern "C" void __cdecl FilterBlock2dBil_SecondPass_8(
	int *, unsigned char *, int, int, int, int, const int *);

// RVA 0x001B8430
extern "C" void __cdecl FilterBlock2dBil(
    const unsigned char *source,
	unsigned short *destination,
	int sourcePitch,
	const int *horizontalWeights,
	const int *verticalWeights)
{
    int sourceDelta = sourcePitch;
    sourceDelta -= 8;
    int *table = &g_bfmeTableC7E0;
    table += 2;
    int rows = 9;
    const unsigned char *sourcePointer = source;

    do
    {
        for (int column = -2; column <= 5; column++)
        {
            table[column] = (sourcePointer[0] * horizontalWeights[0] +
                              sourcePointer[1] * horizontalWeights[1] + 0x40) >> 7;
            sourcePointer++;
        }

        sourcePointer += sourceDelta;
		table += 8;
		--rows;
	}
	while (rows != 0);

	FilterBlock2dBil_SecondPass(&g_bfmeTableC7E0, destination, 8, 8, 8, 8, verticalWeights);
}

// RVA 0x001B8A40
extern "C" void __cdecl FilterBlock2dBil_8(
    const unsigned char *source,
	unsigned short *destination,
	int sourcePitch,
	const int *horizontalWeights,
	const int *verticalWeights)
{
    int sourceDelta = sourcePitch;
    sourceDelta -= 8;
    int *table = &g_bfmeTableC7E0;
    table += 2;
    int rows = 9;
    const unsigned char *sourcePointer = source;

    do
    {
        for (int column = -2; column <= 5; column++)
        {
            table[column] = (sourcePointer[0] * horizontalWeights[0] +
                              sourcePointer[1] * horizontalWeights[1] + 0x40) >> 7;
            sourcePointer++;
        }

        sourcePointer += sourceDelta;
		table += 8;
		--rows;
	}
	while (rows != 0);

	FilterBlock2dBil_SecondPass_8(&g_bfmeTableC7E0, (unsigned char *)destination, 8, 8, 8, 8, verticalWeights);
}
