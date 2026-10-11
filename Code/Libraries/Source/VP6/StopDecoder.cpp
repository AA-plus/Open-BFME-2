// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b62e0.md plus retail only. No
// decoder source was consulted.
//
// Decoder shutdown (retail 0x001B62E0). Its own unit, so VP6_DeletePBInstance
// stays a call as in retail.

struct PB_INSTANCE
{
	unsigned char pad000[0x13C];
	void *quantizer;              // 0x13C
	unsigned char pad140[0x158];
	void *postProc;               // 0x298
};

void Rva009A6EC0Release(void **quantizer);             // 0x001B7930 VP6_DeleteQuantizer
void bfmeStepJW(void *instance);                       // 0x001B9040 VP6_DeleteFragmentInfo
void Rva009A8880Release(void *instance);               // 0x001B92D0 VP6_DeleteFrameInfo
extern "C" void __cdecl DeletePostProcInstance(void **postProc); // 0x001B68D0
extern "C" void __cdecl VP6_DeletePBInstance(PB_INSTANCE **instance); // 0x001B56A0

// RVA 0x001B62E0
extern "C" int __cdecl VP6_StopDecoder(PB_INSTANCE **instance)
{
	if (*instance)
	{
		Rva009A6EC0Release(&(*instance)->quantizer);
		DeletePostProcInstance(&(*instance)->postProc);
		bfmeStepJW(*instance);
		Rva009A8880Release(*instance);
		VP6_DeletePBInstance(instance);
	}
	return 1;
}
