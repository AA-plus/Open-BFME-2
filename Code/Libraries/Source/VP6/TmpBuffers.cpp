// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b5530.md and 001b55e0.md plus
// retail only. No decoder source was consulted.
// Scratch buffers of the decoder instance: VP6_DeleteTmpBuffers (retail
// 0x001B5530) and VP6_AllocateTmpBuffers (retail 0x001B55E0). Every buffer is
// kept twice: the raw allocation and the pointer rounded up to 32 bytes.

void bfmeFreeOneJT(void *block);                 // 0x001B6410 duck_free

class Rva001B6400Allocation
{
public:
	enum AllocationTag { Bucket_GLUE_NOT_IMPLEMENTED = 0 };
	static void *__cdecl operator new(unsigned int bytes, AllocationTag tag); // 0x001B6400 duck_malloc
};

struct TmpBuffersInstance
{
	unsigned char pad000[0x264];
	void *scaleAligned;            // 0x264
	void *scaleRaw;                // 0x268
	int pad26C;
	void *coefficientAligned;      // 0x270
	void *coefficientRaw;          // 0x274
	int pad278;
	void *reconAligned;            // 0x27C
	void *reconRaw;                // 0x280
	void *dataAligned;             // 0x284
	void *dataRaw;                 // 0x288
	void *loopFilterRaw;           // 0x28C
	void *loopFilterAligned;       // 0x290
};

// RVA 0x001B5530
extern "C" void __cdecl VP6_DeleteTmpBuffers(TmpBuffersInstance *pbi)
{
	if (pbi->coefficientRaw != 0)
		bfmeFreeOneJT(pbi->coefficientRaw);

	if (pbi->loopFilterRaw != 0)
		bfmeFreeOneJT(pbi->loopFilterRaw);

	if (pbi->dataRaw != 0)
		bfmeFreeOneJT(pbi->dataRaw);

	if (pbi->reconRaw != 0)
		bfmeFreeOneJT(pbi->reconRaw);

	if (pbi->scaleRaw != 0)
		bfmeFreeOneJT(pbi->scaleRaw);

	pbi->coefficientRaw = 0;
	pbi->loopFilterRaw = 0;
	pbi->dataRaw = 0;
	pbi->reconRaw = 0;
	pbi->scaleRaw = 0;
	pbi->coefficientAligned = 0;
	pbi->loopFilterAligned = 0;
	pbi->dataAligned = 0;
	pbi->reconAligned = 0;
	pbi->scaleAligned = 0;
}

// RVA 0x001B55E0
extern "C" int __cdecl VP6_AllocateTmpBuffers(TmpBuffersInstance *pbi)
{
	VP6_DeleteTmpBuffers(pbi);

	void *a = Rva001B6400Allocation::operator new(0xa0, Rva001B6400Allocation::Bucket_GLUE_NOT_IMPLEMENTED);
	pbi->coefficientRaw = a;
	if (a == 0)
	{
		VP6_DeleteTmpBuffers(pbi);
		return 0;
	}
	pbi->coefficientAligned = (void *)(((unsigned int)a + 0x1f) & 0xffffffe0);

	void *b = Rva001B6400Allocation::operator new(0xa0, Rva001B6400Allocation::Bucket_GLUE_NOT_IMPLEMENTED);
	pbi->dataRaw = b;
	if (b == 0)
	{
		VP6_DeleteTmpBuffers(pbi);
		return 0;
	}
	pbi->dataAligned = (void *)(((unsigned int)b + 0x1f) & 0xffffffe0);

	void *c = Rva001B6400Allocation::operator new(0x120, Rva001B6400Allocation::Bucket_GLUE_NOT_IMPLEMENTED);
	pbi->loopFilterRaw = c;
	if (c == 0)
	{
		VP6_DeleteTmpBuffers(pbi);
		return 0;
	}
	pbi->loopFilterAligned = (void *)(((unsigned int)c + 0x1f) & 0xffffffe0);

	void *d = Rva001B6400Allocation::operator new(0xa0, Rva001B6400Allocation::Bucket_GLUE_NOT_IMPLEMENTED);
	pbi->reconRaw = d;
	if (d == 0)
	{
		VP6_DeleteTmpBuffers(pbi);
		return 0;
	}
	pbi->reconAligned = (void *)(((unsigned int)d + 0x1f) & 0xffffffe0);

	return 1;
}
