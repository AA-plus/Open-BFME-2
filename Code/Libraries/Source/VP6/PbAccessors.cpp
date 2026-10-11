// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b5830.md 001b6330.md 001b6340.md
// 001b6360.md 001b9680.md 001b58f0.md plus retail only. No
// decoder source was consulted. Small cdecl accessors of PB_INSTANCE.
struct PB_INSTANCE
{
	unsigned char pad0[0x1A0];
	int ppLevel;
	unsigned char pad1[0x1C0 - 0x1A4];
	int fragPixelsH;
	int fragPixelsV;
	unsigned char pad2[0x220 - 0x1C8];
	int reconUOffset;
	int reconVOffset;
	unsigned char pad3[0x244 - 0x228];
	unsigned char *thisFrameRecon;
};

// RVA 0x001B5830: the version string "6.1.0.5".
extern "C" const char *__cdecl VP60D_GetVersionNumber(void)
{
	return "6.1.0.5";
}

// RVA 0x001B6330
extern "C" unsigned char *__cdecl GetThisFrameReconPtr(const PB_INSTANCE *pbi)
{
	return pbi->thisFrameRecon;
}

// RVA 0x001B6340
extern "C" unsigned char *__cdecl GetThisFrameReconUPtr(const PB_INSTANCE *pbi)
{
	return pbi->thisFrameRecon + pbi->reconUOffset;
}

// RVA 0x001B6360
extern "C" unsigned char *__cdecl GetThisFrameReconVPtr(const PB_INSTANCE *pbi)
{
	return pbi->thisFrameRecon + pbi->reconVOffset;
}

// RVA 0x001B9680
extern "C" void __cdecl VP6_InitialiseConfiguration(PB_INSTANCE *pbi)
{
	pbi->fragPixelsH = 8;
	pbi->fragPixelsV = 8;
}

// RVA 0x001B58F0: command 0 reports the post-processing level.
extern "C" void __cdecl VP6_GetPbParam(const PB_INSTANCE *pbi, unsigned int command, unsigned int *out)
{
	if (command == 0)
		*out = pbi->ppLevel;
}
