// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b8040.md plus retail only.
// No decoder source was consulted.
// InitVPUtil retail 0x001B8040..0x001B8049 (10 bytes): cdecl and argument
// free. Calls the IDCT constant filler at 0x001C4300 then tail-jumps to the
// utility dispatch-table installer at 0x001C4440. Both callees are rowed
// today under the names declared below.
extern "C" void __cdecl fillidctconstants();
extern "C" void __cdecl UtilMachineSpecificConfig();

extern "C" void __cdecl InitVPUtil()
{
	fillidctconstants();
	UtilMachineSpecificConfig();
}
