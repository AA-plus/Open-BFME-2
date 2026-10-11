// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c7330.md plus retail only. No
// decoder source was consulted.
//
// VP6_DecodeModeProbs retail 0x001C7330 (373 bytes): reads the per-frame mode
// probability update for the three mode-context groups, loading a codebook
// vector and/or adding clamped differences, then rebuilds the mode trees.

extern "C" int __cdecl VP6_DecodeBool(void *state, int probability);   // 0x001C4F00 VP6_DecodeBool
extern "C" int __cdecl VP6_bitread(void *, int);           // 0x001BCF40
extern "C" int __cdecl VP6_decodeModeDiff(unsigned char *ctx);            // 0x001C7250 VP6_decodeModeDiff
extern "C" void __cdecl VP6_BuildModeTree(unsigned char *ctx);            // 0x001C7040

// g_bfmeQuantRow: the mode-probability codebook at retail VA 0x00BD94F8
// (3 groups x 16 vectors x 20 bytes, 960 bytes).
unsigned char g_bfmeQuantRow[960] = {
	9, 15, 32, 25, 7, 19, 9, 21,
	1, 12, 14, 12, 3, 18, 14, 23,
	3, 10, 0, 4, 48, 39, 1, 2,
	11, 27, 29, 44, 7, 27, 1, 4,
	0, 3, 1, 6, 1, 2, 0, 0,
	21, 32, 1, 2, 4, 10, 32, 43,
	6, 23, 2, 3, 1, 19, 1, 6,
	12, 21, 0, 7, 69, 83, 0, 0,
	0, 2, 10, 29, 3, 12, 0, 1,
	0, 3, 0, 3, 2, 2, 0, 0,
	11, 20, 1, 4, 18, 36, 43, 48,
	13, 35, 0, 2, 0, 5, 3, 12,
	1, 2, 0, 0, 70, 44, 0, 1,
	2, 10, 37, 46, 8, 26, 0, 2,
	0, 2, 0, 2, 0, 1, 0, 0,
	8, 15, 0, 1, 8, 21, 74, 53,
	22, 42, 0, 1, 0, 2, 0, 3,
	1, 2, 0, 0, 141, 42, 0, 0,
	1, 4, 11, 24, 1, 11, 0, 1,
	0, 1, 0, 2, 0, 0, 0, 0,
	8, 19, 4, 10, 24, 45, 21, 37,
	9, 29, 0, 3, 1, 7, 11, 25,
	0, 2, 0, 1, 46, 42, 0, 1,
	2, 10, 54, 51, 10, 30, 0, 2,
	0, 2, 0, 1, 0, 1, 0, 0,
	28, 32, 0, 0, 3, 10, 75, 51,
	14, 33, 0, 1, 0, 2, 0, 1,
	1, 2, 0, 0, 100, 46, 0, 1,
	3, 9, 21, 37, 5, 20, 0, 1,
	0, 2, 1, 2, 0, 1, 0, 0,
	27, 29, 0, 1, 9, 25, 53, 51,
	12, 34, 0, 1, 0, 3, 1, 5,
	0, 2, 0, 0, 80, 38, 0, 0,
	1, 4, 69, 33, 5, 16, 0, 1,
	0, 1, 0, 0, 0, 1, 0, 0,
	16, 20, 0, 0, 2, 8, 104, 49,
	15, 33, 0, 1, 0, 1, 0, 1,
	1, 1, 0, 0, 194, 16, 0, 0,
	1, 1, 1, 9, 1, 3, 0, 0,
	0, 1, 0, 1, 0, 0, 0, 0,
	41, 22, 1, 0, 1, 31, 0, 0,
	0, 0, 0, 1, 1, 7, 0, 1,
	98, 25, 4, 10, 123, 37, 6, 4,
	1, 27, 0, 0, 0, 0, 5, 8,
	1, 7, 0, 1, 12, 10, 0, 2,
	26, 14, 14, 12, 0, 24, 0, 0,
	0, 0, 55, 17, 1, 9, 0, 36,
	5, 7, 1, 3, 209, 5, 0, 0,
	0, 27, 0, 0, 0, 0, 0, 1,
	0, 1, 0, 1, 0, 0, 0, 0,
	2, 5, 4, 5, 0, 121, 0, 0,
	0, 0, 0, 3, 2, 4, 1, 4,
	2, 2, 0, 1, 175, 5, 0, 1,
	0, 48, 0, 0, 0, 0, 0, 2,
	0, 1, 0, 2, 0, 1, 0, 0,
	83, 5, 2, 3, 0, 102, 0, 0,
	0, 0, 1, 3, 0, 2, 0, 1,
	0, 0, 0, 0, 233, 6, 0, 0,
	0, 8, 0, 0, 0, 0, 0, 1,
	0, 1, 0, 0, 0, 1, 0, 0,
	34, 16, 112, 21, 1, 28, 0, 0,
	0, 0, 6, 8, 1, 7, 0, 3,
	2, 5, 0, 2, 159, 35, 2, 2,
	0, 25, 0, 0, 0, 0, 3, 6,
	0, 5, 0, 1, 4, 4, 0, 1,
	75, 39, 5, 7, 2, 48, 0, 0,
	0, 0, 3, 11, 2, 16, 1, 4,
	7, 10, 0, 2, 212, 21, 0, 1,
	0, 9, 0, 0, 0, 0, 1, 2,
	0, 2, 0, 0, 2, 2, 0, 0,
	4, 2, 0, 0, 0, 172, 0, 0,
	0, 0, 0, 1, 0, 2, 0, 0,
	2, 0, 0, 0, 187, 22, 1, 1,
	0, 17, 0, 0, 0, 0, 3, 6,
	0, 4, 0, 1, 4, 4, 0, 1,
	133, 6, 1, 2, 1, 70, 0, 0,
	0, 0, 0, 2, 0, 4, 0, 3,
	1, 1, 0, 0, 251, 1, 0, 0,
	0, 2, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	2, 3, 2, 3, 0, 2, 0, 2,
	0, 0, 11, 4, 1, 4, 0, 2,
	3, 2, 0, 4, 49, 46, 3, 4,
	7, 31, 42, 41, 0, 0, 2, 6,
	1, 7, 1, 4, 2, 4, 0, 1,
	26, 25, 1, 1, 2, 10, 67, 39,
	0, 0, 1, 1, 0, 14, 0, 2,
	31, 26, 1, 6, 103, 46, 1, 2,
	2, 10, 33, 42, 0, 0, 1, 4,
	0, 3, 0, 1, 1, 3, 0, 0,
	14, 31, 9, 13, 14, 54, 22, 29,
	0, 0, 2, 6, 4, 18, 6, 13,
	1, 5, 0, 1, 85, 39, 0, 0,
	1, 9, 69, 40, 0, 0, 0, 1,
	0, 3, 0, 1, 2, 3, 0, 0,
	31, 28, 0, 0, 3, 14, 130, 34,
	0, 0, 0, 1, 0, 3, 0, 1,
	3, 3, 0, 1, 171, 25, 0, 0,
	1, 5, 25, 21, 0, 0, 0, 1,
	0, 1, 0, 0, 0, 0, 0, 0,
	17, 21, 68, 29, 6, 15, 13, 22,
	0, 0, 6, 12, 3, 14, 4, 10,
	1, 7, 0, 3, 51, 39, 0, 1,
	2, 12, 91, 44, 0, 0, 0, 2,
	0, 3, 0, 1, 2, 3, 0, 1,
	81, 25, 0, 0, 2, 9, 106, 26,
	0, 0, 0, 1, 0, 1, 0, 1,
	1, 1, 0, 0, 140, 37, 0, 1,
	1, 8, 24, 33, 0, 0, 1, 2,
	0, 2, 0, 1, 1, 2, 0, 0,
	14, 23, 1, 3, 11, 53, 90, 31,
	0, 0, 0, 3, 1, 5, 2, 6,
	1, 2, 0, 0, 123, 29, 0, 0,
	1, 7, 57, 30, 0, 0, 0, 1,
	0, 1, 0, 1, 0, 1, 0, 0,
	13, 14, 0, 0, 4, 20, 175, 20,
	0, 0, 0, 1, 0, 1, 0, 1,
	1, 1, 0, 0, 202, 23, 0, 0,
	1, 3, 2, 9, 0, 0, 0, 1,
	0, 1, 0, 1, 0, 0, 0, 0,
};

extern "C" void __cdecl VP6_DecodeModeProbs(unsigned char *ctx)
{
    void *state = ctx + 0x150;
    int plane = 0;
    struct Rows {
        unsigned char a[10];
        unsigned char b[10];
    };
    Rows *rows = (Rows *)(ctx + 0x737);

    do {
        if (VP6_DecodeBool(state, 0xAE)) {
            int index = VP6_bitread(state, 4) + plane;
            ((unsigned char *)rows)[-1] = g_bfmeQuantRow[((index + index * 4) << 2) + 0];
            ((unsigned char *)rows)[-11] = g_bfmeQuantRow[((index + index * 4) << 2) + 1];
            ((unsigned char *)rows)[0] = g_bfmeQuantRow[((index + index * 4) << 2) + 2];
            ((unsigned char *)rows)[-10] = g_bfmeQuantRow[((index + index * 4) << 2) + 3];
            ((unsigned char *)rows)[1] = g_bfmeQuantRow[((index + index * 4) << 2) + 4];
            ((unsigned char *)rows)[-9] = g_bfmeQuantRow[((index + index * 4) << 2) + 5];
            ((unsigned char *)rows)[2] = g_bfmeQuantRow[((index + index * 4) << 2) + 6];
            ((unsigned char *)rows)[-8] = g_bfmeQuantRow[((index + index * 4) << 2) + 7];
            ((unsigned char *)rows)[3] = g_bfmeQuantRow[((index + index * 4) << 2) + 8];
            ((unsigned char *)rows)[-7] = g_bfmeQuantRow[((index + index * 4) << 2) + 9];
            ((unsigned char *)rows)[4] = g_bfmeQuantRow[((index + index * 4) << 2) + 10];
            ((unsigned char *)rows)[-6] = g_bfmeQuantRow[((index + index * 4) << 2) + 11];
            ((unsigned char *)rows)[5] = g_bfmeQuantRow[((index + index * 4) << 2) + 12];
            ((unsigned char *)rows)[-5] = g_bfmeQuantRow[((index + index * 4) << 2) + 13];
            ((unsigned char *)rows)[6] = g_bfmeQuantRow[((index + index * 4) << 2) + 14];
            ((unsigned char *)rows)[-4] = g_bfmeQuantRow[((index + index * 4) << 2) + 15];
            ((unsigned char *)rows)[7] = g_bfmeQuantRow[((index + index * 4) << 2) + 16];
            ((unsigned char *)rows)[-3] = g_bfmeQuantRow[((index + index * 4) << 2) + 17];
            ((unsigned char *)rows)[8] = g_bfmeQuantRow[((index + index * 4) << 2) + 18];
            ((unsigned char *)rows)[-2] = g_bfmeQuantRow[((index + index * 4) << 2) + 19];
        }
        if (VP6_DecodeBool(state, 0xFE)) {
            for (int i = 0; i < 10; ++i) {
                unsigned char *dst = (unsigned char *)rows + 11;
                int v = VP6_decodeModeDiff(ctx) + dst[i - 12];
                if (v < 0)
                    v = 0;
                else if (v > 255)
                    v = 255;
                dst[i - 12] = (unsigned char)v;

                v = VP6_decodeModeDiff(ctx) + dst[i - 22];
                if (v < 0)
                    v = 0;
                else if (v > 255)
                    v = 255;
                dst[i - 22] = (unsigned char)v;
            }
        }
        plane += 16;
        ++rows;
    } while (plane < 48);

    VP6_BuildModeTree(ctx);
}
