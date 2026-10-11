// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001d56f0.md plus retail only.
// No decoder source was consulted.
// ScalarReconIntra retail 0x001D56F0 (153 bytes): intra reconstruction without
// SIMD. Each of the 64 residual values plus 128 goes into the scratch block,
// which is then written to the output through the unsigned 8-bit saturating
// block store (retail 0x001D55C0).
extern "C" void __cdecl SatUnsigned8(unsigned char *dst, short *src, int dstStride, int srcStride);

extern "C" void __cdecl ScalarReconIntra(short *scratch, unsigned char *output,
	const short *residual, int lineStep)
{
	int rows = 8;
	short *out = scratch + 2;
	do {
		out[-2] = (short)(residual[0] + 128);
		out[-1] = (short)(residual[1] + 128);
		out[0] = (short)(residual[2] + 128);
		out[1] = (short)(residual[3] + 128);
		out[2] = (short)(residual[4] + 128);
		out[3] = (short)(residual[5] + 128);
		out[4] = (short)(residual[6] + 128);
		out[5] = (short)(residual[7] + 128);
		out += 8;
		residual += 8;
	} while (--rows);

	SatUnsigned8(output, scratch, lineStep, 8);
}
