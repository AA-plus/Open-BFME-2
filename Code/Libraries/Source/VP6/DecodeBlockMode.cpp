// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c5990.md plus retail only.
// No decoder source was consulted.
//
// Block coding mode (retail 0x001C5990): two equiprobable bools, first is
// the high bit, select inter (0), inter with vector (2), nearest (3) or
// near (4).

struct Vp6BoolCoder;
extern "C" int __cdecl VP6_DecodeBool128(Vp6BoolCoder *coder); // 0x001C4F80

// RVA 0x001C5990
extern "C" int __cdecl VP6_DecodeBlockMode(unsigned char *pbi)
{
	Vp6BoolCoder *coder = (Vp6BoolCoder *)(pbi + 0x150);
	int value = VP6_DecodeBool128(coder) * 2;
	value += VP6_DecodeBool128(coder);

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
