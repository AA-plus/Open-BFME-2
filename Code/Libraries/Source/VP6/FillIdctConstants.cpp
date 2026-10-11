// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c4300.md plus retail only.
// No decoder source was consulted.
// fillidctconstants retail 0x001C4300 (140 bytes): fills the 48-word IDCT
// constant block at retail 0x00E22980 from the seven cosine constants at
// retail 0x00DB8188.

// Retail 0x00E22980: the zero-filled 48-word constant block.
unsigned short Rva009B3A00Table[48] = { 0 };
// Retail 0x00DB8188: the seven IDCT cosine constants (retail .data contents).
unsigned short Rva009B3A00Source[7] = {
	0xfb15u, 0xec83u, 0xd4dbu, 0xb505u, 0x8e3au, 0x61f8u, 0x31f1u
};

struct FourWords { unsigned short a, b, c, d; };

extern "C" void __cdecl fillidctconstants(void)
{
	unsigned short *table = Rva009B3A00Table;
	unsigned short *clear = table + 16;
	while (clear != table)
	{
		--clear;
		*clear = 0;
	}

	unsigned short allBits = 0xffff;
	table[15] = allBits;
	table[10] = allBits;
	table[5] = allBits;
	table[0] = allBits;

	int stride = 8;
	FourWords *destination = (FourWords *)(table + 16);
	int sourceIndex = 0;
	do
	{
		unsigned short value = Rva009B3A00Source[sourceIndex];
		destination->d = value;
		destination->c = value;
		destination->b = value;
		destination->a = value;
		destination = (FourWords *)((int)destination + stride);
		++sourceIndex;
	} while ((int)&destination->c <= (int)(table + 42));

	table[47] = stride;
	table[46] = stride;
	table[45] = stride;
	table[44] = stride;
}
