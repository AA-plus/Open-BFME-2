// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bcf40.md 001bcf80.md plus retail
// only. No decoder source was consulted.
struct BoolCoder;
struct Vp6BoolCoder;
extern "C" int __cdecl VP6_DecodeBool128(Vp6BoolCoder *state); // 0x001C4F80

// RVA 0x001BCF40: read equiprobable bools, most significant first.
extern "C" unsigned int __cdecl VP6_bitread(BoolCoder *coder, int bits)
{
	unsigned int r = 0;
	for (int i = bits - 1; i >= 0; --i)
		r |= VP6_DecodeBool128((Vp6BoolCoder *)coder) << i;
	return r;
}

struct HeaderReader
{
	const unsigned char *buffer;  // 0x00
	unsigned int value;           // 0x04
	int bitsAvailable;            // 0x08
	int position;                 // 0x0C
};

// RVA 0x001BCF80: load the first four bytes big-endian.
extern "C" void __cdecl InitHeaderBuffer(HeaderReader *reader, const unsigned char *data)
{
	reader->buffer = data;
	unsigned int value = data[0];
	value = (value << 8) + data[1];
	value = (value << 8) + data[2];
	value = (value << 8) + data[3];
	reader->value = value;
	reader->bitsAvailable = 0x20;
	reader->position = 4;
}
