// _AnyRatioFrameScale
// partial score=0.6 date=2026-10-11
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001baf30.md plus retail only.
// No decoder source was consulted.
//
// AnyRatioFrameScale (retail 0x001BAF30, 606 bytes): scales the luma and
// both chroma planes of the reconstructed frame into a YUV buffer with
// AnyRatio_2D_Scale and zero fills the padding beyond the destination size.
extern "C" void * __cdecl memset(void *destination, int value, unsigned int bytes);
#pragma intrinsic(memset)

struct PostProcAnyRatio
{
	unsigned char m_pad00[0x40];
	int m_frameWidth;      // 0x40
	unsigned char m_pad44[0x58 - 0x44];
	int m_hscale; // 0x58
	int m_hratio;          // 0x5C
	int m_vscale; // 0x60
	int m_vratio;          // 0x64
	unsigned char m_pad68[0x70 - 0x68];
	int m_width;           // 0x70
	int m_height;          // 0x74
	int m_yOffset;         // 0x78
	int m_uOffset;         // 0x7C
	int m_vOffset;         // 0x80
	unsigned char m_pad84[0xB4 - 0x84];
	int m_border;          // 0xB4
};

struct YuvConfigAnyRatio
{
	unsigned char m_pad00[8];
	int m_yStride;         // 0x08
	unsigned char m_pad0C[0x14 - 0x0C];
	int m_uvStride;        // 0x14
	unsigned char *m_y;    // 0x18
	unsigned char *m_u;    // 0x1C
	unsigned char *m_v;    // 0x20
};

extern "C" int __cdecl AnyRatio_2D_Scale(PostProcAnyRatio *pbi, unsigned char *source, int sourcePitch,
	int sourceWidth, int sourceHeight, unsigned char *destination, int destinationPitch,
	int destinationWidth, int destinationHeight);

extern "C" int __cdecl AnyRatioFrameScale(PostProcAnyRatio *pbi, unsigned char *frame,
	YuvConfigAnyRatio *config, int yOffset, int uvOffset)
{
	int width = pbi->m_width;
	int hratio = pbi->m_hratio;
	int hscale = pbi->m_hscale;
	int sourceWidth = ((unsigned int)width * hratio + hscale - 1) / (unsigned int)hscale;
	int vscale = pbi->m_vscale;
	int height = pbi->m_height;
	int sourceHeight = (unsigned int)(height * pbi->m_vratio + vscale - 1) / (unsigned int)vscale;
	int paddedWidth;
	int paddedHeight;
	int result;
	int row;

	if (hratio == 3)
		paddedWidth = ((sourceWidth + 2) / 3 * hscale * 3) / hratio;
	else
		paddedWidth = ((sourceWidth + 7) / 8 * hscale * 8) / hratio;
	if (pbi->m_vratio == 3)
		paddedHeight = ((sourceHeight + 2) / 3 * vscale * 3) / pbi->m_vratio;
	else
		paddedHeight = ((sourceHeight + 7) / 8 * vscale * 8) / pbi->m_vratio;

	result = AnyRatio_2D_Scale(pbi, frame + pbi->m_yOffset, pbi->m_frameWidth + pbi->m_border * 2,
		sourceWidth, sourceHeight, config->m_y + yOffset, config->m_yStride, width, height);
	for (row = 0; row < paddedHeight; row++)
		memset(config->m_y + config->m_yStride * row + yOffset + width, 0, paddedWidth - width);
	for (row = height; row < paddedHeight; row++)
		memset(config->m_y + config->m_yStride * row + yOffset, 0, paddedWidth);
	if (result == 0)
		return 0;

	width = (width + 1) >> 1;
	height = (height + 1) >> 1;
	sourceWidth = (sourceWidth + 1) >> 1;
	sourceHeight = (sourceHeight + 1) >> 1;
	AnyRatio_2D_Scale(pbi, frame + pbi->m_uOffset, (pbi->m_frameWidth >> 1) + pbi->m_border,
		sourceWidth, sourceHeight, config->m_u + uvOffset, config->m_uvStride, width, height);
	AnyRatio_2D_Scale(pbi, frame + pbi->m_vOffset, (pbi->m_frameWidth >> 1) + pbi->m_border,
		sourceWidth, sourceHeight, config->m_v + uvOffset, config->m_uvStride, width, height);
	return result;
}
