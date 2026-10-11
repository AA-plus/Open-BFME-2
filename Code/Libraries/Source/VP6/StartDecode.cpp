// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bcee0.md plus retail only.
// No decoder source was consulted.
//
// Bool decoder start (retail 0x001BCEE0).

struct BOOL_CODER
{
	volatile int lowValue;                  // 0x00
	volatile int range;                     // 0x04
	volatile int value;                     // 0x08
	volatile int count;                     // 0x0C
	volatile int position;                  // 0x10
	unsigned char *volatile buffer;         // 0x14
};

// RVA 0x001BCEE0
extern "C" void __cdecl VP6_StartDecode(BOOL_CODER *coder, unsigned char *source)
{
	coder->position = 0;
	coder->lowValue = 0;
	coder->range = 0xff;
	coder->count = 8;
	coder->buffer = source;
	coder->value = ((((source[0] << 8) + source[1]) << 8) + source[2]) * 256 + source[3];
	coder->position = 4;
}
