// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b9d10.md 001b9db0.md
// 001ba0a0.md and 001ba160.md plus retail only. No decoder source was
// consulted.
//
// Scalar in-place vertical 4-to-5 and 3-to-5 band interpolators (retail
// 0x001B9D10, 0x001B9DB0, 0x001BA0A0, 0x001BA160): rows 1..4 of a band are
// rebuilt per column from the source rows with weights 51/205, 102/154,
// 154/102 (4-to-5) or 102/154, 205/51, 51/205, 154/102 (3-to-5), each sum
// plus 128 shifted right 8. The Last variants serve the final band of a
// plane, where no following source row exists and row 4 repeats the last
// source row.

// RVA 0x001B9D10
extern "C" void __cdecl VerticalBand_4_5_Scale_C(unsigned char *source, int stride, unsigned int bytes)
{
    unsigned char *cursor = source;
    while (bytes > 0)
    {
        unsigned int second = cursor[stride];
        unsigned int first = cursor[0];
        unsigned int firstWeight = first * 51;
        unsigned int secondWeight = second * 205;
        cursor[stride] = (unsigned char)((firstWeight + secondWeight + 128) >> 8);
        unsigned int fourth;
        unsigned int third;
        third = cursor[stride * 2];
        unsigned int thirdWeight = third * 154;
        fourth = cursor[stride * 3];
        cursor[stride * 2] = (unsigned char)((second * 102 + thirdWeight + 128) >> 8);
        cursor[stride * 3] = (unsigned char)((fourth * 102 + thirdWeight + 128) >> 8);
        cursor[stride * 4] = (unsigned char)((cursor[stride * 5] * 51 + fourth * 205 + 128) >> 8);
        ++cursor;
        --bytes;
    }
}

// RVA 0x001B9DB0
extern "C" void __cdecl LastVerticalBand_4_5_Scale_C(unsigned char *source, int stride, unsigned int bytes)
{
	unsigned char *cursor = source;
	while (bytes > 0)
	{
		unsigned int second = cursor[stride];
		unsigned int first = cursor[0];
		unsigned int firstWeight = first * 51;
		unsigned int secondWeight = second * 205;
		cursor[stride] = (unsigned char)((firstWeight + secondWeight + 128) >> 8);

		unsigned int fourth;
		unsigned int third;
		fourth = cursor[stride * 3];
		third = cursor[stride * 2];
		cursor[stride * 2] = (unsigned char)((second * 102 + third * 154 + 128) >> 8);
		cursor[stride * 3] = (unsigned char)((third * 154 + fourth * 102 + 128) >> 8);
		cursor[stride * 4] = (unsigned char)fourth;
		++cursor;
		--bytes;
	}
}

// RVA 0x001BA0A0
extern "C" void __cdecl VerticalBand_3_5_Scale_C(unsigned char *source, int stride, unsigned int bytes)
{
	unsigned char *cursor = source;

	for (; bytes > 0; --bytes)
	{
		unsigned char *row2 = cursor + stride * 2;
		unsigned char *row4 = cursor + stride * 4;
		unsigned int row1Value = cursor[stride];
		unsigned int row0Value = cursor[0];
		cursor[stride] = (unsigned char)((row0Value * 102 + row1Value * 154 + 128) >> 8);

		unsigned int row2Value = row2[0];
		row2[0] = (unsigned char)((row1Value * 205 + row2Value * 51 + 128) >> 8);
		row2[stride] = (unsigned char)((row1Value * 51 + row2Value * 205 + 128) >> 8);

		unsigned int row5Value = row4[stride];
		row4[0] = (unsigned char)((row2Value * 154 + row5Value * 102 + 128) >> 8);

		++cursor;
		++row2;
		++row4;
	}
}

// RVA 0x001BA160
extern "C" void __cdecl LastVerticalBand_3_5_Scale_C(unsigned char *source, int stride, unsigned int bytes)
{
	unsigned char *cursor = source;

	while (bytes > 0)
	{
		unsigned int first = cursor[0];
		unsigned int second = cursor[stride];
		cursor[stride] = (unsigned char)((first * 102 + second * 154 + 128) >> 8);

		unsigned int third = cursor[stride * 2];
		cursor[stride * 2] = (unsigned char)((second * 205 + third * 51 + 128) >> 8);
		cursor[stride * 3] = (unsigned char)((second * 51 + third * 205 + 128) >> 8);
		cursor[stride * 4] = (unsigned char)third;

		++cursor;
		--bytes;
	}
}
