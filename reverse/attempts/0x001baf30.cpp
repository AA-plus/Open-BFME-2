// AnyRatioFrameScale
// partial score=0.85 date=2026-10-13
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001baf30.md plus retail only.
// No decoder source was consulted.
// AnyRatioFrameScale retail 0x001BAF30..0x001BB18D (606 bytes), cdecl:
// scales a whole frame with AnyRatio_2D_Scale at the post-processor's
// horizontal and vertical ratios, zeroes the padding to the right of and
// below the scaled luma, then scales the chroma planes at half size.
// Returns the luma result (0 when the ratio is unsupported).
struct Rva009AF200Context
{
	int m_mode;
	unsigned char m_pad04[0x40 - 0x04];
	unsigned int m_frameWidth;
	unsigned char m_pad44[0x58 - 0x44];
	int m_hScale;
	int m_hRatio;
	int m_vScale;
	int m_vRatio;
	unsigned char m_pad68[0x70 - 0x68];
	unsigned int m_expandedWidth;
	unsigned int m_expandedHeight;
	unsigned char *m_planeY;
	unsigned char *m_planeU;
	unsigned char *m_planeV;
	unsigned char m_pad84[0xB4 - 0x84];
	int m_border;
};

struct ScaleFramePlanes
{
	int width, height, pitch, chromaWidth, chromaHeight, chromaPitch;
	char *y, *u, *v;
};

extern "C" void *__cdecl memset(void *block, int value, unsigned int bytes);

extern "C" int __cdecl AnyRatio_2D_Scale(
	Rva009AF200Context *context,
	const unsigned char *source,
	int source_pitch,
	unsigned int source_width,
	unsigned int source_height,
	unsigned char *dest,
	unsigned int dest_pitch,
	unsigned int dest_width,
	unsigned int dest_height);

extern "C" int __cdecl AnyRatioFrameScale(Rva009AF200Context *pbi, unsigned char *frame,
	ScaleFramePlanes *dst, int yOffset, int uvOffset)
{
	int dstWidth = pbi->m_expandedWidth;
	int srcWidth = (pbi->m_expandedWidth * pbi->m_hRatio + pbi->m_hScale - 1) / pbi->m_hScale;
	int dstHeight = pbi->m_expandedHeight;
	int srcHeight = (pbi->m_expandedHeight * pbi->m_vRatio + pbi->m_vScale - 1) / pbi->m_vScale;
	int paddedWidth;
	int paddedHeight;
	int row;
	int luma;

	if (pbi->m_hRatio == 3)
		paddedWidth = (srcWidth + 2) / 3 * pbi->m_hScale * 3 / pbi->m_hRatio;
	else
		paddedWidth = (srcWidth + 7) / 8 * pbi->m_hScale * 8 / pbi->m_hRatio;
	if (pbi->m_vRatio == 3)
		paddedHeight = (srcHeight + 2) / 3 * pbi->m_vScale * 3 / pbi->m_vRatio;
	else
		paddedHeight = (srcHeight + 7) / 8 * pbi->m_vScale * 8 / pbi->m_vRatio;

	luma = AnyRatio_2D_Scale(pbi, frame + (int)pbi->m_planeY + yOffset,
		pbi->m_frameWidth + pbi->m_border * 2, srcWidth, srcHeight,
		(unsigned char *)dst->y + yOffset, dst->pitch, dstWidth, dstHeight);
	for (row = 0; row < paddedHeight; row++)
		memset((unsigned char *)dst->y + dst->pitch * row + yOffset + dstWidth, 0, paddedWidth - dstWidth);
	for (row = dstHeight; row < paddedHeight; row++)
		memset((unsigned char *)dst->y + dst->pitch * row + yOffset, 0, paddedWidth);
	if (luma == 0)
		return 0;
	AnyRatio_2D_Scale(pbi, frame + (int)pbi->m_planeU,
		pbi->m_frameWidth / 2 + pbi->m_border, (srcWidth + 1) / 2, (srcHeight + 1) / 2,
		(unsigned char *)dst->u + uvOffset, dst->chromaPitch, (dstWidth + 1) / 2, (dstHeight + 1) / 2);
	AnyRatio_2D_Scale(pbi, frame + (int)pbi->m_planeV,
		pbi->m_frameWidth / 2 + pbi->m_border, (srcWidth + 1) / 2, (srcHeight + 1) / 2,
		(unsigned char *)dst->v + uvOffset, dst->chromaPitch, (dstWidth + 1) / 2, (dstHeight + 1) / 2);
	return luma;
}
