// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001d55c0.md 001d5c60.md
// 001d5790.md and 001d5980.md plus retail only. No decoder source was consulted.
//
// Scalar (non-SIMD) 8x8 block reconstruction helpers (retail
// 0x001D55C0..0x001D5C5C): SatUnsigned8 clamps an int16 block to bytes and
// the three reconstruction routines build an int16 scratch block, then store
// it through SatUnsigned8. The 8-wide rows are written out so MSVC 7.1 emits
// the retail fully unrolled sequences.

extern "C" void __cdecl SatUnsigned8(unsigned char *dst, short *src, int dstStride, int srcStride);

// SatUnsigned8 retail 0x001D55C0 (301 bytes): eight rows of eight int16 samples
// clamped to 0..255 and stored as bytes.
extern "C" void __cdecl SatUnsigned8(unsigned char *dst, short *src, int dstStride, int srcStride)
{
	int row = 8;
	do {
		short s;
		int v;

		s = src[0];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[0] = (unsigned char)v;

		s = src[1];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[1] = (unsigned char)v;

		s = src[2];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[2] = (unsigned char)v;

		s = src[3];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[3] = (unsigned char)v;

		s = src[4];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[4] = (unsigned char)v;

		s = src[5];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[5] = (unsigned char)v;

		s = src[6];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[6] = (unsigned char)v;

		s = src[7];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[7] = (unsigned char)v;

		src += srcStride;
		dst += dstStride;
	} while (--row);
}

// ReconBlock_C retail 0x001D5C60 (308 bytes): add the prediction block to the
// block in place, then store it through SatUnsigned8.
extern "C" void __cdecl ReconBlock_C(short *work, short *addend,
	unsigned char *output, int dstStride)
{
	short *base = work;
	int passes = 2;
	do {
		work[0] += addend[0];
		work[1] += addend[1];
		work[2] += addend[2];
		work[3] += addend[3];
		work[4] += addend[4];
		work[5] += addend[5];
		work[6] += addend[6];
		work[7] += addend[7];
		work[8] += addend[8];
		work[9] += addend[9];
		work[10] += addend[10];
		work[11] += addend[11];
		work[12] += addend[12];
		work[13] += addend[13];
		work[14] += addend[14];
		work[15] += addend[15];
		work[16] += addend[16];
		work[17] += addend[17];
		work[18] += addend[18];
		work[19] += addend[19];
		work[20] += addend[20];
		work[21] += addend[21];
		work[22] += addend[22];
		work[23] += addend[23];
		work[24] += addend[24];
		work[25] += addend[25];
		work[26] += addend[26];
		work[27] += addend[27];
		work[28] += addend[28];
		work[29] += addend[29];
		work[30] += addend[30];
		work[31] += addend[31];
		work += 32;
		addend += 32;
	} while (--passes);

	SatUnsigned8(output, base, dstStride, 8);
}

// ScalarReconInter retail 0x001D5790 (485 bytes): reference byte plus residual
// into the scratch block, then store through SatUnsigned8.
extern "C" void __cdecl ScalarReconInter(short *work, unsigned char *output,
	const unsigned char *source, const short *residual, int stride)
{
	short *out = work + 2;
	int passes = 2;
	do {
		out[-2] = (short)(source[0] + residual[0]);
		out[-1] = (short)(source[1] + residual[1]);
		out[0] = (short)(source[2] + residual[2]);
		out[1] = (short)(source[3] + residual[3]);
		out[2] = (short)(source[4] + residual[4]);
		out[3] = (short)(source[5] + residual[5]);
		out[4] = (short)(source[6] + residual[6]);
		out[5] = (short)(source[7] + residual[7]);
		source += stride;

		out[6] = (short)(source[0] + residual[8]);
		out[7] = (short)(source[1] + residual[9]);
		out[8] = (short)(source[2] + residual[10]);
		out[9] = (short)(source[3] + residual[11]);
		out[10] = (short)(source[4] + residual[12]);
		out[11] = (short)(source[5] + residual[13]);
		out[12] = (short)(source[6] + residual[14]);
		out[13] = (short)(source[7] + residual[15]);
		source += stride;

		out[14] = (short)(source[0] + residual[16]);
		out[15] = (short)(source[1] + residual[17]);
		out[16] = (short)(source[2] + residual[18]);
		out[17] = (short)(source[3] + residual[19]);
		out[18] = (short)(source[4] + residual[20]);
		out[19] = (short)(source[5] + residual[21]);
		out[20] = (short)(source[6] + residual[22]);
		out[21] = (short)(source[7] + residual[23]);
		source += stride;

		out[22] = (short)(source[0] + residual[24]);
		out[23] = (short)(source[1] + residual[25]);
		out[24] = (short)(source[2] + residual[26]);
		out[25] = (short)(source[3] + residual[27]);
		out[26] = (short)(source[4] + residual[28]);
		out[27] = (short)(source[5] + residual[29]);
		out[28] = (short)(source[6] + residual[30]);
		out[29] = (short)(source[7] + residual[31]);
		source += stride;
		residual += 32;
		out += 32;
	} while (--passes);

	SatUnsigned8(output, work, stride, 8);
}

// ScalarReconInterHalfPixel2 retail 0x001D5980 (733 bytes): average of two
// reference rows plus residual into the scratch block, then store.
extern "C" void __cdecl ScalarReconInterHalfPixel2(short *work, unsigned char *output,
	const unsigned char *first, const unsigned char *second, const short *residual,
	int stride)
{
	short *out = work + 2;
	int passes = 2;
	do {
		out[-2] = (short)(((first[0] + second[0]) >> 1) + residual[0]);
		out[-1] = (short)(((first[1] + second[1]) >> 1) + residual[1]);
		out[0] = (short)(((first[2] + second[2]) >> 1) + residual[2]);
		out[1] = (short)(((first[3] + second[3]) >> 1) + residual[3]);
		out[2] = (short)(((first[4] + second[4]) >> 1) + residual[4]);
		out[3] = (short)(((first[5] + second[5]) >> 1) + residual[5]);
		out[4] = (short)(((first[6] + second[6]) >> 1) + residual[6]);
		out[5] = (short)(((first[7] + second[7]) >> 1) + residual[7]);
		first += stride;
		second += stride;

		out[6] = (short)(((first[0] + second[0]) >> 1) + residual[8]);
		out[7] = (short)(((first[1] + second[1]) >> 1) + residual[9]);
		out[8] = (short)(((first[2] + second[2]) >> 1) + residual[10]);
		out[9] = (short)(((first[3] + second[3]) >> 1) + residual[11]);
		out[10] = (short)(((first[4] + second[4]) >> 1) + residual[12]);
		out[11] = (short)(((first[5] + second[5]) >> 1) + residual[13]);
		out[12] = (short)(((first[6] + second[6]) >> 1) + residual[14]);
		out[13] = (short)(((first[7] + second[7]) >> 1) + residual[15]);
		first += stride;
		second += stride;

		out[14] = (short)(((first[0] + second[0]) >> 1) + residual[16]);
		out[15] = (short)(((first[1] + second[1]) >> 1) + residual[17]);
		out[16] = (short)(((first[2] + second[2]) >> 1) + residual[18]);
		out[17] = (short)(((first[3] + second[3]) >> 1) + residual[19]);
		out[18] = (short)(((first[4] + second[4]) >> 1) + residual[20]);
		out[19] = (short)(((first[5] + second[5]) >> 1) + residual[21]);
		out[20] = (short)(((first[6] + second[6]) >> 1) + residual[22]);
		out[21] = (short)(((first[7] + second[7]) >> 1) + residual[23]);
		first += stride;
		second += stride;

		out[22] = (short)(((first[0] + second[0]) >> 1) + residual[24]);
		out[23] = (short)(((first[1] + second[1]) >> 1) + residual[25]);
		out[24] = (short)(((first[2] + second[2]) >> 1) + residual[26]);
		out[25] = (short)(((first[3] + second[3]) >> 1) + residual[27]);
		out[26] = (short)(((first[4] + second[4]) >> 1) + residual[28]);
		out[27] = (short)(((first[5] + second[5]) >> 1) + residual[29]);
		out[28] = (short)(((first[6] + second[6]) >> 1) + residual[30]);
		out[29] = (short)(((first[7] + second[7]) >> 1) + residual[31]);
		first += stride;
		second += stride;
		residual += 32;
		out += 32;
	} while (--passes);

	SatUnsigned8(output, work, stride, 8);
}
