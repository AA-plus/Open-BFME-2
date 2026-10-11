// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c5990.md plus retail only.
// No decoder source was consulted.
//
// Block coding mode (retail 0x001C5990): two equiprobable bools, first is
// the high bit, select inter (0), inter with vector (2), nearest (3) or
// near (4).

struct Rva009B4680State;
int __cdecl Rva009B4680Normalize(Rva009B4680State *coder); // 0x001C4F80 VP6_DecodeBool128

// RVA 0x001C5990
extern "C" int __cdecl VP6_DecodeBlockMode(unsigned char *pbi)
{
	Rva009B4680State *coder = (Rva009B4680State *)(pbi + 0x150);
	int value = Rva009B4680Normalize(coder) * 2;
	value += Rva009B4680Normalize(coder);

	switch (value) {
	case 0:
		return 0;
	case 1:
		return 2;
	case 2:
		return 3;
	case 3:
		return 4;
	}
	return 0;
}
