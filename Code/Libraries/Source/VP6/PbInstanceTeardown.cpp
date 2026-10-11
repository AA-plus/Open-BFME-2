// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b56a0.md plus
// retail only. No decoder source was consulted.
//
// Decoder instance teardown (retail 0x001B56A0). The instance
// is the 0x4954 byte PB_INSTANCE; only the quantizer pointer (0x13C) and the
// post-processor pointer (0x298) are named here.

struct PB_INSTANCE
{
	unsigned char pad000[0x13C];
	void *quantizer;              // 0x13C
	unsigned char pad140[0x158];
	void *postProc;               // 0x298
};

class BfmeThingJT;
void bfmeFreeJT(BfmeThingJT *instance);                // 0x001B5530 VP6_DeleteTmpBuffers
void Rva009A6EC0Release(void **quantizer);             // 0x001B7930 VP6_DeleteQuantizer
void bfmeStepJW(void *instance);                       // 0x001B9040 VP6_DeleteFragmentInfo
void Rva009A8880Release(void *instance);               // 0x001B92D0 VP6_DeleteFrameInfo
void bfmeFreeOneJT(void *block);                       // 0x001B6410 duck_free
extern "C" void __cdecl DeletePostProcInstance(void **postProc); // 0x001B68D0

// RVA 0x001B56A0
extern "C" void __cdecl VP6_DeletePBInstance(PB_INSTANCE **instance)
{
	if (*instance)
	{
		bfmeFreeJT((BfmeThingJT *)*instance);
		Rva009A6EC0Release(&(*instance)->quantizer);
		DeletePostProcInstance(&(*instance)->postProc);
	}
	bfmeFreeOneJT(*instance);
	*instance = 0;
}
