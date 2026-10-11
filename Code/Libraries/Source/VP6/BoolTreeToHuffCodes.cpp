// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bbaf0.md plus retail only.
// No decoder source was consulted.
//
// BoolTreeToHuffCodes (retail 0x001BBAF0, 336 bytes): converts the eleven
// branch probabilities of the token tree into twelve token weights (dword
// index equals the token number, 11 being end-of-block). Each weight is the
// product of the branch values from the root down, shifted right by 8 after
// every multiplication.

// RVA 0x001BBAF0
extern "C" void __cdecl BoolTreeToHuffCodes(const unsigned char *probabilities, unsigned int *weights)
{
	unsigned int factor01 = ((unsigned int)probabilities[0] * probabilities[1]) >> 8;
	weights[11] = factor01;

	unsigned int factor0 = ((unsigned int)probabilities[0] * (0xff - probabilities[1])) >> 8;
	weights[0] = factor0;

	unsigned int inverse0 = 0xff - probabilities[0];
	weights[1] = ((unsigned int)probabilities[2] * inverse0) >> 8;

	unsigned int factor3 = ((0xff - probabilities[2]) * inverse0) >> 8;
	unsigned int value3 = ((unsigned int)probabilities[3] * factor3) >> 8;
	unsigned int value4 = ((unsigned int)probabilities[4] * value3) >> 8;
	weights[2] = value4;

	unsigned int factor5 = ((0xff - probabilities[4]) * value3) >> 8;
	unsigned int value5 = ((unsigned int)probabilities[5] * factor5) >> 8;
	weights[3] = value5;
	unsigned int value6 = ((0xff - probabilities[5]) * factor5) >> 8;
	weights[4] = value6;

	unsigned int factor6 = ((0xff - probabilities[3]) * factor3) >> 8;
	unsigned int value7 = ((unsigned int)probabilities[6] * factor6) >> 8;
	unsigned int value8 = ((unsigned int)probabilities[7] * value7) >> 8;
	weights[5] = value8;
	unsigned int value9 = ((0xff - probabilities[7]) * value7) >> 8;
	weights[6] = value9;

	unsigned int factor8 = ((0xff - probabilities[6]) * factor6) >> 8;
	unsigned int value10 = ((unsigned int)probabilities[8] * factor8) >> 8;
	unsigned int value11 = ((unsigned int)probabilities[9] * value10) >> 8;
	weights[7] = value11;
	unsigned int value12 = ((0xff - probabilities[9]) * value10) >> 8;
	weights[8] = value12;

	unsigned int factor10 = ((0xff - probabilities[8]) * factor8) >> 8;
	unsigned int value13 = ((unsigned int)probabilities[10] * factor10) >> 8;
	weights[9] = value13;
	unsigned int value14 = ((0xff - probabilities[10]) * factor10) >> 8;
	weights[10] = value14;
}
