// _LoopDeringBlock
// partial score=0.6 date=2026-10-13
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d8b40.md plus retail disassembly
// only. No decoder source was consulted.
//
// LoopDeringBlock retail 0x001D8B40..0x001D8DCE (655 bytes, cdecl, caller
// cleans). In-place adaptive smoothing, unreferenced in retail. The dering
// threshold table (256 unsigned ints) sits at instance + 0x453C.

typedef unsigned int uint;

struct VP6DeringInstance
{
	char pad[0x453C];
	uint m_thresholds[256];
};

extern "C" void *__cdecl memcpy(void *destination, const void *source, unsigned int count);
#pragma intrinsic(memcpy)

static inline int BfmeAbsInt(int value)
{
	return value < 0 ? -value : value;
}

extern "C" void __cdecl LoopDeringBlock(VP6DeringInstance *instance, unsigned char *block, uint stride, uint width, uint height)
{
	unsigned char smallest = 255;
	unsigned char largest = 0;
	unsigned char *scan = block;
	for (uint y = 0; y < height; ++y)
	{
		for (uint x = 0; x < width; ++x)
		{
			unsigned char value = *scan++;
			if (value < smallest)
				smallest = value;
			if (value > largest)
				largest = value;
		}
		scan += stride - width;
	}

	uint threshold = instance->m_thresholds[largest];
	uint fromSmallest = instance->m_thresholds[255 - smallest];
	if (fromSmallest > threshold)
		threshold = fromSmallest;
	threshold += (int)(largest - smallest) >> 5;

	for (uint y = 0; y < height; ++y)
	{
		unsigned char *row = block + y * stride;
		if (width)
		{
			unsigned char buffer[16];
			for (uint x = 0; x < width; ++x)
			{
				uint value = row[x];
				int leftDelta = BfmeAbsInt((int)value - (int)row[x - 1]);
				int rightDelta = BfmeAbsInt((int)value - (int)row[x + 1]);
				uint sum = value * 2;
				sum += ((uint)leftDelta <= threshold) ? row[x - 1] : value;
				sum += ((uint)rightDelta <= threshold) ? row[x + 1] : value;
				buffer[x] = (unsigned char)((sum + 2) >> 2);
			}
			memcpy(row, buffer, width);
		}
	}

	for (uint x = 0; x < width; ++x)
	{
		if (height)
		{
			unsigned char buffer[16];
			unsigned char *above = block - stride + x;
			unsigned char *middle = block + x;
			unsigned char *below = block + stride + x;
			for (uint y = 0; y < height; ++y)
			{
				uint value = middle[0];
				int aboveDelta = BfmeAbsInt((int)value - (int)above[0]);
				int belowDelta = BfmeAbsInt((int)value - (int)below[0]);
				uint sum = value * 2;
				sum += ((uint)aboveDelta <= threshold) ? above[0] : value;
				sum += ((uint)belowDelta <= threshold) ? below[0] : value;
				buffer[y] = (unsigned char)((sum + 2) >> 2);
				above += stride;
				middle += stride;
				below += stride;
			}
			for (uint y = 0; y < height; ++y)
				block[x + y * stride] = buffer[y];
		}
	}
}
