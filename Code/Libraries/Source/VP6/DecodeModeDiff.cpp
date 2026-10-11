// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c7250.md plus retail only. No decoder source was consulted.
// VP6_decodeModeDiff, retail RVA 0x001C7250 (211 bytes).
struct Vp6BoolCoder;

extern "C" int __cdecl VP6_DecodeBool(void *state, int probability);
extern "C" int __cdecl VP6_DecodeBool128(Vp6BoolCoder *state);
extern "C" int __cdecl VP6_bitread(void *, int);

extern "C" int __cdecl VP6_decodeModeDiff(unsigned char *ctx)
{
	void *state = ctx + 0x150;
	int sign;

	if (!VP6_DecodeBool(state, 0xCD))
		return 0;

	sign = 1 - (VP6_DecodeBool128((Vp6BoolCoder *)state) << 1);

	if (!VP6_DecodeBool(state, 0xAB))
		return sign << (3 - VP6_DecodeBool(state, 0x53));

	if (!VP6_DecodeBool(state, 0xC7)) {
		if (VP6_DecodeBool(state, 0x8C))
			return (sign * 3) << 2;
		if (VP6_DecodeBool(state, 0x7D))
			return sign << 4;
		if (VP6_DecodeBool(state, 0x68))
			return (sign * 5) << 2;
		return (sign * 3) << 3;
	}

	return (VP6_bitread(state, 7) * sign) << 2;
}
