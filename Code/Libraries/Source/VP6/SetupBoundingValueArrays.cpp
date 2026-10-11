// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001bd590.md and 001bfe80.md plus
// retail only. No decoder source was consulted.
// Bounding value tables of the post-processor instance. Both build a tent
// shaped table of 512 signed dwords addressed from its centre (entry 256)
// and return the centre: SetupDeblockValueArray_Generic (retail 0x001BD590,
// deblock table at +0x3C) and SetupBoundingValueArray_Generic (retail
// 0x001BFE80, filter table at +0x34).
extern "C" void * __cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

struct DeblockBoundingInstance
{
	unsigned char pad00[0x3C];
	int *deblockValues;   // 0x3C
};

struct FilterBoundingInstance
{
	unsigned char pad00[0x34];
	int *boundingValues;  // 0x34
};

// RVA 0x001BD590
extern "C" int *__cdecl SetupDeblockValueArray_Generic(DeblockBoundingInstance *instance, int limit)
{
	int *base = instance->deblockValues;
	int *bounding = base + 256;
	int i;

	memset(base, 0, 512 * sizeof(int));

	for (i = 0; i < limit; i++) {
		bounding[-limit - i] = i - limit;
		bounding[-i] = -i;
		bounding[i] = i;
		bounding[limit + i] = limit - i;
	}

	return bounding;
}

// RVA 0x001BFE80
extern "C" int *__cdecl SetupBoundingValueArray_Generic(FilterBoundingInstance *instance, int limit)
{
	int *base = instance->boundingValues;
	int *bounding = base + 256;
	int i;

	memset(base, 0, 512 * sizeof(int));

	for (i = 0; i < limit; i++) {
		bounding[-limit - i] = i - limit;
		bounding[-i] = -i;
		bounding[i] = i;
		bounding[limit + i] = limit - i;
	}

	return bounding;
}
