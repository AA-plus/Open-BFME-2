// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b65f0.md plus retail only.
// No decoder source was consulted.
// DeletePostProcBuffers retail 0x001B65F0 (182 bytes): frees (when non-null)
// the six raw allocations of the post-processor instance in the order 0xB8,
// 0xA0, 0xA4, 0xA8, 0xAC, 0xB0, clearing each raw pointer and its aligned
// twin right after the free.

void bfmeFreeOneJT(void *block);                 // 0x001B6410 duck_free

struct DeletePostProcBuffersInstance
{
	unsigned char pad00[0x24];
	void *fragmentQIndexAligned;     // 0x24
	void *fragmentVariancesAligned;  // 0x28
	void *fragmentFlagsAligned;      // 0x2C
	unsigned char pad30[0x34 - 0x30];
	void *boundingAligned;           // 0x34
	unsigned char pad38[0x3C - 0x38];
	void *deblockAligned;            // 0x3C
	unsigned char pad40[0xA0 - 0x40];
	void *boundingRaw;               // 0xA0
	void *deblockRaw;                // 0xA4
	void *fragmentQIndexRaw;         // 0xA8
	void *fragmentVariancesRaw;      // 0xAC
	void *fragmentFlagsRaw;          // 0xB0
	unsigned char padB4[0xB8 - 0xB4];
	void *intermediateRaw;           // 0xB8
	void *intermediateAligned;       // 0xBC
};

extern "C" void __cdecl DeletePostProcBuffers(DeletePostProcBuffersInstance *instance)
{
	if (instance->intermediateRaw)
		bfmeFreeOneJT(instance->intermediateRaw);
	instance->intermediateRaw = 0;
	instance->intermediateAligned = 0;

	if (instance->boundingRaw)
		bfmeFreeOneJT(instance->boundingRaw);
	instance->boundingRaw = 0;
	instance->boundingAligned = 0;

	if (instance->deblockRaw)
		bfmeFreeOneJT(instance->deblockRaw);
	instance->deblockRaw = 0;
	instance->deblockAligned = 0;

	if (instance->fragmentQIndexRaw)
		bfmeFreeOneJT(instance->fragmentQIndexRaw);
	instance->fragmentQIndexRaw = 0;
	instance->fragmentQIndexAligned = 0;

	if (instance->fragmentVariancesRaw)
		bfmeFreeOneJT(instance->fragmentVariancesRaw);
	instance->fragmentVariancesRaw = 0;
	instance->fragmentVariancesAligned = 0;

	if (instance->fragmentFlagsRaw)
		bfmeFreeOneJT(instance->fragmentFlagsRaw);
	instance->fragmentFlagsRaw = 0;
	instance->fragmentFlagsAligned = 0;
}
