// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c7640.md plus retail only.
// No decoder source was consulted.
//
// SetupDeblockValueArray_ForMMX retail 0x001C7640..0x001C7674 (53 bytes),
// cdecl. Prepares the constant block of the MMX edge filters inside the
// postprocessor's 512-entry int32 scratch array (+0x3C): its midpoint (1024
// bytes in) rounded down to 32 bytes receives two words of the limit in both
// 16-bit halves, two words of 16-bit ones and two words of 16-bit fours,
// each pair stored high word first. Returns the block. Twin of
// SetupBoundingValueArray_ForMMX (0x001D3230), which reads +0x34.
struct POSTPROC_INSTANCE
{
	unsigned char pad0[0x3C];
	int *deblockValues;
};

extern "C" int *__cdecl SetupDeblockValueArray_ForMMX(POSTPROC_INSTANCE *ppi, int limit)
{
	int *block = (int *)((unsigned int)(ppi->deblockValues + 256) & ~31u);
	block[1] = limit * 0x10001;
	block[0] = limit * 0x10001;
	block[3] = 0x10001;
	block[2] = 0x10001;
	block[5] = 0x40004;
	block[4] = 0x40004;
	return block;
}
