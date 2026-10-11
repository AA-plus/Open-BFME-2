// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d26e0.md plus retail only.
// No decoder source was consulted.
//
// LastVerticalBand_1_2_Scale_MMX retail 0x001D26E0..0x001D26FE (31 bytes),
// cdecl. Last band of the 1-to-2 vertical scale: row 1 (pitch bytes below)
// becomes a copy of row 0, eight bytes per step until the width is used up
// (so the width is in effect rounded up to a multiple of 8). The MMX copy is
// inline assembly inside an ordinary C function that names its own
// arguments; cl 13.10 has no C form for the MMX move.
extern "C" void __cdecl LastVerticalBand_1_2_Scale_MMX(unsigned char *band,
	unsigned int pitch, unsigned int width)
{
	__asm
	{
		mov esi, band
		mov ecx, pitch
		mov edx, width
	nextStep:
		movq mm0, [esi]
		movq [esi + ecx], mm0
		add esi, 8
		sub edx, 8
		jg nextStep
	}
}
