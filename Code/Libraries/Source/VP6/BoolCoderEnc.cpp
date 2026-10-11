// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bcc40.md
// plus retail only. No decoder source was consulted.
struct BoolCoder
{
	int low;
	int range;
	int value;
	int count;
	int pos;
	void *buffer;
	int measure;
	int bits;
};

// RVA 0x001BCC40
extern "C" void __cdecl VP6_StartEncode(BoolCoder *coder, void *buffer)
{
	coder->low = 0;
	coder->range = 255;
	coder->value = 0;
	coder->count = -24;
	coder->buffer = buffer;
	coder->pos = 0;
}
