// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b75b0.md plus retail only.
// No decoder source was consulted.
//
// VP6_UpdateQC (retail 0x001B75B0): refresh the quantizer when the selected
// quantizer index differs from the one last built. The two retail calls push
// the quantizer plus a forwarded word and clean 16 bytes together; the
// typed call adapter keeps the extra word on the first call.

#include <string.h>

struct Rva009A6780State;
struct BfmeS1040;
extern "C" void __cdecl VP6_init_quantizer(Rva009A6780State *, int); // 0x001B71F0
extern "C" void __cdecl VP6_init_dequantizer(BfmeS1040 *, int);  // 0x001B70A0

extern unsigned int vp6DequantIndex[64]; // retail 0x00BD8460 zig-zag order
extern int g_rva01142408[]; // retail 0x00BD8560 identity index

static __forceinline unsigned codecWord(const char *p)
{
	unsigned value;
	memcpy(&value, p, 4);
	return value;
}

static __forceinline void resetInverseMap(char *bytes)
{
	int *table = g_rva01142408;
	memcpy(bytes + 0x13c, &table, 4);
	for (int i = 0; i < 64; ++i)
		bytes[0x140 + vp6DequantIndex[i]] = (char)i;
}

// RVA 0x001B75B0
extern "C" void __cdecl VP6_UpdateQC(void *quantizer, int version)
{
	char *bytes = static_cast<char *>(quantizer);
	unsigned index = codecWord(bytes);
	int selected = codecWord(bytes + 0x3c + index * 4);
	int current = codecWord(bytes + 0x38);
	if (selected == current)
		return;
	memcpy(bytes + 0x38, bytes + 4, 4);
	resetInverseMap(bytes);

	VP6_init_quantizer(static_cast<Rva009A6780State *>(quantizer), version);
	VP6_init_dequantizer(static_cast<BfmeS1040 *>(quantizer), version);
}
