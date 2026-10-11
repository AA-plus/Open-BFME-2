// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bc1a0.md plus retail only.
// No decoder source was consulted.
// VP6_ResetLeftContext retail 0x001BC1A0 (135 bytes): zeroes the four 16-byte
// left block contexts (left Y row 0, left Y row 1, left U, left V), then sets
// the mode of each to -1 and the frame of each to 4.
extern "C" void *__cdecl memset(void *block, int value, unsigned int bytes);
#pragma intrinsic(memset)

struct LeftBlockContext
{
	int token;             // 0x0 (token byte)
	int mode;              // 0x4
	unsigned short frame;  // 0x8
	unsigned short dc;     // 0xA
	int tailPadding;       // 0xC
};

struct ResetLeftContextInstance
{
	unsigned char pad000[0xCC];
	LeftBlockContext left[4];  // 0xCC, 0xDC, 0xEC, 0xFC
};

extern "C" void __cdecl VP6_ResetLeftContext(ResetLeftContextInstance *pbi)
{
	int zero = 0;
	memset(&pbi->left[0], zero, sizeof(LeftBlockContext));
	memset(&pbi->left[1], zero, sizeof(LeftBlockContext));
	memset(&pbi->left[2], zero, sizeof(LeftBlockContext));
	memset(&pbi->left[3], zero, sizeof(LeftBlockContext));

	zero |= 0xFFFFFFFF;
	pbi->left[0].mode = zero;
	pbi->left[1].mode = zero;
	pbi->left[2].mode = zero;
	pbi->left[3].mode = zero;

	unsigned short four = 4;
	pbi->left[0].frame = four;
	pbi->left[1].frame = four;
	pbi->left[2].frame = four;
	pbi->left[3].frame = four;
}
