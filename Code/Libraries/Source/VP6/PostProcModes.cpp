// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b6900.md 001b6910.md 001b6920.md
// plus retail only. No decoder source was consulted.
// cdecl setters of POSTPROC_INSTANCE fields 0x6C, 0xC0 and 0xC4.
struct POSTPROC_INSTANCE
{
	unsigned char pad0[0x6C];
	int interlaced;
	unsigned char pad1[0xC0 - 0x70];
	int deInterlaceMode;
	int addNoiseMode;
};

// RVA 0x001B6900..0x001B690B
extern "C" void __cdecl SetPPInterlacedMode(POSTPROC_INSTANCE *pp, int flag)
{
	pp->interlaced = flag;
}

// RVA 0x001B6910..0x001B691E
extern "C" void __cdecl SetDeInterlaceMode(POSTPROC_INSTANCE *pp, int mode)
{
	pp->deInterlaceMode = mode;
}

// RVA 0x001B6920..0x001B692E
extern "C" void __cdecl SetAddNoiseMode(POSTPROC_INSTANCE *pp, int mode)
{
	pp->addNoiseMode = mode;
}
