// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b7050.md plus retail only. No
// decoder source was consulted.
// RVA 0x001B7050..0x001B7067: copy the 256-byte table at 0x00BD7860 (ledger
// name g_bfmeApplyTableA) into the quantizer at +0x3C.
extern "C" void *__cdecl memcpy(void *destination, const void *source, unsigned int bytes);
#pragma intrinsic(memcpy)

extern const unsigned short g_bfmeApplyTableA[128];

extern "C" void __cdecl VP6_InitQTables(unsigned char *quantizer)
{
	memcpy(quantizer + 0x3C, g_bfmeApplyTableA, sizeof(g_bfmeApplyTableA));
}
