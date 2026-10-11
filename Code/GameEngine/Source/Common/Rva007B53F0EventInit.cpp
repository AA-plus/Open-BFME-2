// cl: /O2 /MD
//
// Static-initializer strip: the startup event BFMEPoolYield.cpp waits on is
// created by this translation unit's dynamic initializer through the
// CreateEventA IAT slot 0x00BBA2C8. Retail pushes each zero argument as an
// immediate (push 0) rather than the xor/push eax that /O1 emits, so the
// owning unit was built for speed. The owning TU is unrecovered, so the
// initializer keeps an honest address name; the handle is WWLib thread.cpp
// test_event, the one definition at VA 0x00E07C00.

extern "C" __declspec(dllimport) void * __stdcall CreateEventA(void *attributes, int manualReset, int initialState, const char *name);

// Read by the rowed BFMEPoolYield (0x006105C1).
extern void *test_event;

struct Rva007B53F0EventInit
{
	static void rva007B53F0();
};

// 0x007B53F0 (23B): VA 0x00E07C00 = CreateEventA(0, 0, 0, "").
void Rva007B53F0EventInit::rva007B53F0()
{
	test_event = CreateEventA(0, 0, 0, "");
}
