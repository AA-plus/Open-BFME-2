// _DeblockNonFilteredBandNewFilter_C
// partial score=0.85 date=2026-10-12
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bf090.md plus retail only.
// No decoder source was consulted.

struct Vp6DeblockBandNewInstance
{
	unsigned char m_pad00[0x0C];
	int m_frameQIndex;
	unsigned char m_pad10[0x28 - 0x10];
	int *m_variance;
	unsigned char m_pad2c[0x38 - 0x2c];
	int *m_bounding;
};

extern const unsigned char g_bfmeClampTable[];

extern "C" void __cdecl DeblockNonFilteredBandNewFilter_C(Vp6DeblockBandNewInstance *ctx,
	unsigned char *source, unsigned char *destination, unsigned int stride,
	unsigned int count, unsigned int first, const unsigned int *limits)
{
	unsigned int index;
	int x0, x1, x2, x3, x4, x5, x6, x7, x8, x9;
	int upper, lower, sum, filter;
	int qStep, limit;
	unsigned int row;
	unsigned char *rowInput, *rowOutput;
	qStep = limits[ctx->m_frameQIndex];
	index = first;
	int p2 = 2 * stride;
	int p3 = 3 * stride;
	int p4 = 4 * stride;
	int p5;
	while (index < first + count) {
		rowInput = source + 8 * (index - first);
		limit = (qStep * 3) >> 2;
		p5 = 5 * stride;
		rowOutput = destination + 8 * (index - first);
		for (row = 0; row < 8; ++row) {
			x0 = rowInput[-p5];
			x1 = rowInput[-p4];
			x2 = rowInput[-p3];
			x3 = rowInput[-p2];
			x4 = rowInput[-(int)stride];
			x5 = rowInput[0];
			x6 = rowInput[stride];
			x7 = rowInput[p2];
			x8 = rowInput[p3];
			x9 = rowInput[p4];
			upper = (x1 - x0) > 0 ? (x1 - x0) : (x0 - x1);
			upper += (x2 - x1) > 0 ? (x2 - x1) : (x1 - x2);
			upper += (x3 - x2) > 0 ? (x3 - x2) : (x2 - x3);
			upper += (x4 - x3) > 0 ? (x4 - x3) : (x3 - x4);
			lower = (x5 - x6) > 0 ? (x5 - x6) : (x6 - x5);
			lower += (x6 - x7) > 0 ? (x6 - x7) : (x7 - x6);
			lower += (x7 - x8) > 0 ? (x7 - x8) : (x8 - x7);
			lower += (x8 - x9) > 0 ? (x8 - x9) : (x9 - x8);
			ctx->m_variance[index] += upper > 255 ? 255 : upper;
			ctx->m_variance[index + count] += lower > 255 ? 255 : lower;
			if (upper < limit && lower < limit && x5 - x4 < qStep && x4 - x5 < qStep) {
				sum = x4 + 3 * x0 + x3 + x2 + 4 + x1;
				rowOutput[-p4] = (unsigned char)((sum + x1) >> 3);
				sum += x5 - x0;
				rowOutput[-p3] = (unsigned char)((sum + x2) >> 3);
				sum += x6 - x0;
				rowOutput[-p2] = (unsigned char)((sum + x3) >> 3);
				sum += x7 - x0;
				rowOutput[-(int)stride] = (unsigned char)((sum + x4) >> 3);
				sum += x8 - x1;
				rowOutput[0] = (unsigned char)((sum + x5) >> 3);
				sum += x9 - x2;
				rowOutput[stride] = (unsigned char)((sum + x6) >> 3);
				sum += x9 - x3;
				rowOutput[p2] = (unsigned char)((sum + x7) >> 3);
				sum += x9 - x4;
				rowOutput[p3] = (unsigned char)((sum + x8) >> 3);
			} else {
				filter = ctx->m_bounding[(x3 - x6 + 3 * (x5 - x4) + 4) >> 3];
				rowOutput[-(int)stride] = g_bfmeClampTable[x4 + filter];
				rowOutput[0] = g_bfmeClampTable[x5 - filter];
				rowOutput[-p4] = rowInput[-p4];
				rowOutput[-p3] = rowInput[-p3];
				rowOutput[-p2] = rowInput[-p2];
				rowOutput[stride] = rowInput[stride];
				rowOutput[p2] = rowInput[p2];
				rowOutput[p3] = rowInput[p3];
			}
			rowInput++;
			rowOutput++;
		}
		if (index == first) {
			index++;
			continue;
		}
		rowInput = rowOutput = destination - 8 * stride + 8 * (index - first);
		for (row = 0; row < 8; ++row) {
			x0 = rowInput[-5];
			x1 = rowInput[-4];
			x2 = rowInput[-3];
			x3 = rowInput[-2];
			x4 = rowInput[-1];
			x5 = rowInput[0];
			x6 = rowInput[1];
			x7 = rowInput[2];
			x8 = rowInput[3];
			x9 = rowInput[4];
			upper = (x1 - x0) > 0 ? (x1 - x0) : (x0 - x1);
			upper += (x2 - x1) > 0 ? (x2 - x1) : (x1 - x2);
			upper += (x3 - x2) > 0 ? (x3 - x2) : (x2 - x3);
			upper += (x4 - x3) > 0 ? (x4 - x3) : (x3 - x4);
			lower = (x5 - x6) > 0 ? (x5 - x6) : (x6 - x5);
			lower += (x6 - x7) > 0 ? (x6 - x7) : (x7 - x6);
			lower += (x7 - x8) > 0 ? (x7 - x8) : (x8 - x7);
			lower += (x8 - x9) > 0 ? (x8 - x9) : (x9 - x8);
			ctx->m_variance[index - 1] += upper > 255 ? 255 : upper;
			ctx->m_variance[index] += lower > 255 ? 255 : lower;
			if (upper < limit && lower < limit && x5 - x4 < qStep && x4 - x5 < qStep) {
				sum = x4 + 3 * x0 + x3 + x2 + 4 + x1;
				rowOutput[-4] = (unsigned char)((sum + x1) >> 3);
				sum += x5 - x0;
				rowOutput[-3] = (unsigned char)((sum + x2) >> 3);
				sum += x6 - x0;
				rowOutput[-2] = (unsigned char)((sum + x3) >> 3);
				sum += x7 - x0;
				rowOutput[-1] = (unsigned char)((sum + x4) >> 3);
				sum += x8 - x1;
				rowOutput[0] = (unsigned char)((sum + x5) >> 3);
				sum += x9 - x2;
				rowOutput[1] = (unsigned char)((sum + x6) >> 3);
				sum += x9 - x3;
				rowOutput[2] = (unsigned char)((sum + x7) >> 3);
				sum += x9 - x4;
				rowOutput[3] = (unsigned char)((sum + x8) >> 3);
			} else {
				filter = ctx->m_bounding[(x3 - x6 + 3 * (x5 - x4) + 4) >> 3];
				rowOutput[-1] = g_bfmeClampTable[x4 + filter];
				rowOutput[0] = g_bfmeClampTable[x5 - filter];
			}
			rowInput += stride;
			rowOutput += stride;
		}
		index++;
	}
}
