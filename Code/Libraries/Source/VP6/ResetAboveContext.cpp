// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bc230.md plus retail only.
// No decoder source was consulted.
//
// VP6_ResetAboveContext (retail 0x001BC230, 338 bytes): resets the above-row
// block contexts (Y, U, V; 16 bytes each) of the decoder instance: mode -1,
// frame 4, DC 0, token 0, then seeds the last-DC arrays (Y 0, U and V 128).
// The table pointers are read through volatile fields to keep retail's
// repeated loads.

struct AboveBlockContext
{
	unsigned char token;          // 0x0
	unsigned char pad01[3];
	int mode;                     // 0x4
	unsigned short frame;         // 0x8
	unsigned short dc;            // 0xA
	unsigned char pad0c[4];
};

struct ResetAboveContextInstance
{
	unsigned char pad0[0x10c];
	AboveBlockContext * volatile aboveY;   // 0x10C
	AboveBlockContext * volatile aboveU;   // 0x110
	AboveBlockContext * volatile aboveV;   // 0x114
	unsigned char pad118[0x19c - 0x118];
	unsigned char version;                 // 0x19C
	unsigned char pad19d[0x1f8 - 0x19d];
	unsigned int volatile horizontalFragments; // 0x1F8
	unsigned char pad1fc[0x20];
};

// RVA 0x001BC230
extern "C" void __cdecl VP6_ResetAboveContext(ResetAboveContextInstance *pbi)
{
	int minusOne = -1;
	unsigned short four = 4;
	int zero = 0;
	int i = 0;
	i = 0;
	if (pbi->horizontalFragments + 8 != 0)
	{
		do
		{
			pbi->aboveY[i].mode = minusOne;
			pbi->aboveY[i].frame = four;
			pbi->aboveY[i].dc = zero;
			pbi->aboveY[i].token = zero;
		}
		while (++i < pbi->horizontalFragments + 8);
	}

	i = 0;
	if ((pbi->horizontalFragments >> 1) + 8 != 0)
	{
		do
		{
			pbi->aboveU[i].mode = minusOne;
			pbi->aboveU[i].frame = four;
			pbi->aboveU[i].token = zero;
			pbi->aboveU[i].dc = zero;
			pbi->aboveV[i].mode = minusOne;
			pbi->aboveV[i].frame = four;
			pbi->aboveV[i].token = zero;
			pbi->aboveV[i].dc = zero;
		}
		while (++i < (pbi->horizontalFragments >> 1) + 8);
	}

	if (pbi->version < 6)
	{
		pbi->aboveU[1].mode = zero;
		pbi->aboveU[1].frame = zero;
		pbi->aboveV[1].mode = zero;
		pbi->aboveV[1].frame = zero;
	}

	*(unsigned short *)((unsigned char *)pbi + 0x12c) = 0x80;
	*(unsigned short *)((unsigned char *)pbi + 0x134) = 0x80;
	*(unsigned short *)((unsigned char *)pbi + 0x124) = zero;

	unsigned short *tail = (unsigned short *)((unsigned char *)pbi + 0x12e);
	i = 2;
	do
	{
		tail[-4] = zero;
		tail[0] = zero;
		tail[4] = zero;
		++tail;
		--i;
	}
	while (i != 0);
}
