// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Vp6BoolCoder;

int Rva009B4600DecodeBool(void *state, int probability);
extern "C" int __cdecl VP6_DecodeBool128(Vp6BoolCoder *state);
extern "C" int __cdecl VP6_bitread(void *, int);

// ?Rva009B6950DecodeScale@@YAHPAE@Z
int Rva009B6950DecodeScale(unsigned char *ctx)
{
	void *state = ctx + 0x150;
	int sign;

	if (!Rva009B4600DecodeBool(state, 0xCD))
		return 0;

	sign = 1 - (VP6_DecodeBool128((Vp6BoolCoder *)state) << 1);

	if (!Rva009B4600DecodeBool(state, 0xAB))
		return sign << (3 - Rva009B4600DecodeBool(state, 0x53));

	if (!Rva009B4600DecodeBool(state, 0xC7)) {
		if (Rva009B4600DecodeBool(state, 0x8C))
			return (sign * 3) << 2;
		if (Rva009B4600DecodeBool(state, 0x7D))
			return sign << 4;
		if (Rva009B4600DecodeBool(state, 0x68))
			return (sign * 5) << 2;
		return (sign * 3) << 3;
	}

	return (VP6_bitread(state, 7) * sign) << 2;
}
