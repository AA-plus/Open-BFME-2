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

extern "C" void __cdecl VP6_DeleteQuantizer(void **quantizer); // 0x001B7930
extern "C" void __cdecl VP6_DeleteFragmentInfo(void *instance); // 0x001B9040
extern "C" void __cdecl VP6_DeleteFrameInfo(void *instance); // 0x001B92D0
extern "C" void __cdecl DeletePostProcInstance(void **postProc); // 0x001B68D0
extern "C" void __cdecl VP6_DeletePBInstance(PB_INSTANCE **instance); // 0x001B56A0

// RVA 0x001B62E0
extern "C" int __cdecl VP6_StopDecoder(PB_INSTANCE **instance)
{
	if (*instance)
	{
		VP6_DeleteQuantizer(&(*instance)->quantizer);
		DeletePostProcInstance(&(*instance)->postProc);
		VP6_DeleteFragmentInfo(*instance);
		VP6_DeleteFrameInfo(*instance);
		VP6_DeletePBInstance(instance);
	}
	return 1;
}
