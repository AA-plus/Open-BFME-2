// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b92d0.md and 001b9360.md plus
// retail only. No decoder source was consulted.
// Reconstruction frame allocations of the decoder instance: VP6_DeleteFrameInfo
// (retail 0x001B92D0) and VP6_AllocateFrameInfo (retail 0x001B9360).

void bfmeFreeOneJT(void *block);                 // 0x001B6410 duck_free

class Rva001B6400Allocation
{
public:
	enum AllocationTag { Bucket_GLUE_NOT_IMPLEMENTED = 0 };
	static void *__cdecl operator new(unsigned int bytes, AllocationTag tag); // 0x001B6400 duck_malloc
};

struct FrameInfoInstance
{
	unsigned char pad000[0x1B8];
	unsigned int yStride;        // 0x1B8
	unsigned char pad1BC[0x244 - 0x1BC];
	void *thisFrameAligned;      // 0x244
	void *thisFrameRaw;          // 0x248
	void *goldenAligned;         // 0x24C
	void *goldenRaw;             // 0x250
	void *lastFrameAligned;      // 0x254
	void *lastFrameRaw;          // 0x258
	void *postProcAligned;       // 0x25C
	void *postProcRaw;           // 0x260
};

// RVA 0x001B92D0
extern "C" void __cdecl VP6_DeleteFrameInfo(FrameInfoInstance *pbi)
{
	if (pbi->thisFrameRaw != 0)
		bfmeFreeOneJT(pbi->thisFrameRaw);
	if (pbi->goldenRaw != 0)
		bfmeFreeOneJT(pbi->goldenRaw);
	if (pbi->lastFrameRaw != 0)
		bfmeFreeOneJT(pbi->lastFrameRaw);
	if (pbi->postProcRaw != 0)
		bfmeFreeOneJT(pbi->postProcRaw);

	pbi->thisFrameRaw = 0;
	pbi->goldenRaw = 0;
	pbi->lastFrameRaw = 0;
	pbi->thisFrameAligned = 0;
	pbi->goldenAligned = 0;
	pbi->lastFrameAligned = 0;
	pbi->postProcRaw = 0;
}

// RVA 0x001B9360
extern "C" int __cdecl VP6_AllocateFrameInfo(FrameInfoInstance *pbi, int frameSize)
{
	VP6_DeleteFrameInfo(pbi);

	void *first = Rva001B6400Allocation::operator new(
		(unsigned int)frameSize + pbi->yStride + 0x20,
		Rva001B6400Allocation::Bucket_GLUE_NOT_IMPLEMENTED);
	pbi->thisFrameRaw = first;
	if (first == 0)
	{
		VP6_DeleteFrameInfo(pbi);
		return 0;
	}
	pbi->thisFrameAligned = (void *)(((unsigned int)first + 0x1F) & ~0x1F);

	void *second = Rva001B6400Allocation::operator new(
		(unsigned int)frameSize + pbi->yStride + 0x20,
		Rva001B6400Allocation::Bucket_GLUE_NOT_IMPLEMENTED);
	pbi->goldenRaw = second;
	if (second == 0)
	{
		VP6_DeleteFrameInfo(pbi);
		return 0;
	}
	pbi->goldenAligned = (void *)(((unsigned int)second + 0x1F) & ~0x1F);

	void *third = Rva001B6400Allocation::operator new(
		(unsigned int)frameSize + pbi->yStride + 0x20,
		Rva001B6400Allocation::Bucket_GLUE_NOT_IMPLEMENTED);
	pbi->lastFrameRaw = third;
	if (third == 0)
	{
		VP6_DeleteFrameInfo(pbi);
		return 0;
	}
	pbi->lastFrameAligned = (void *)(((unsigned int)third + 0x1F) & ~0x1F);
	return 1;
}
