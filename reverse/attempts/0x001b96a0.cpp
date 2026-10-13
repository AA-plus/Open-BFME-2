// UpdateUMVBorder
// partial score=0.75 date=2026-10-13
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b96a0.md plus retail only.
// No decoder source was consulted.
// UpdateUMVBorder retail 0x001B96A0..0x001B9AB6 (1047 bytes), cdecl
// (post-processor instance, frame buffer base): replicates the edge pixels of
// the Y, U and V planes into the surrounding border so motion vectors may
// point outside the picture. Each plane runs the same two static helpers: the
// side borders fill and the top/bottom row copies, both of which the compiler
// inlines (byte fills to rep stos, row copies to rep movs).
struct Rva009AF200Context
{
	int m_mode;
	unsigned char m_pad04[0x78 - 0x04];
	unsigned char *m_planeY;
	unsigned char *m_planeU;
	unsigned char *m_planeV;
	unsigned int m_fragmentsY;
	unsigned int m_fragmentsUV;
	unsigned int m_scratchCount;
	int m_width;
	int m_height;
	int m_strideY;
	int m_strideUV;
	unsigned char m_padA0[0xB4 - 0xA0];
	int m_border;
};

static __forceinline void FillBytes(unsigned char *destination, unsigned char value, int count)
{
	int k;
	for (k = 0; k < count; k++)
		destination[k] = value;
}

static __forceinline void CopyBytes(unsigned char *destination, const unsigned char *source, int count)
{
	int k;
	for (k = 0; k < count; k++)
		destination[k] = source[k];
}

static __forceinline void PlaneSides(unsigned char *row, int width, int rows, int border, int stride)
{
	unsigned char *last = row + width - 1;
	unsigned char *left = row - border;
	unsigned char *right = last + 1;
	int i;

	for (i = 0; i < rows; i++)
	{
		FillBytes(left, row[0], border);
		FillBytes(right, *last, border);
		row += stride;
		left += stride;
		right += stride;
		last += stride;
	}
}

static __forceinline void PlaneRows(unsigned char *source, int rows, int border, int stride)
{
	unsigned char *lastRow = source + (rows - 1) * stride;
	unsigned char *top = source - border * stride;
	unsigned char *bottom = lastRow + stride;
	int i;

	for (i = 0; i < border; i++)
	{
		CopyBytes(top, source, stride);
		CopyBytes(bottom, lastRow, stride);
		top += stride;
		bottom += stride;
	}
}

extern "C" void __cdecl UpdateUMVBorder(Rva009AF200Context *pbi, unsigned char *buffer)
{
	int border = pbi->m_border;

	PlaneSides(buffer + (int)pbi->m_planeY, pbi->m_width << 3, pbi->m_height << 3,
		pbi->m_border, pbi->m_strideY);
	PlaneRows(buffer + pbi->m_border * pbi->m_strideY, pbi->m_height << 3,
		pbi->m_border, pbi->m_strideY);
	PlaneSides(buffer + (int)pbi->m_planeU, pbi->m_width << 2, pbi->m_height << 2,
		pbi->m_border >> 1, pbi->m_strideUV);
	PlaneRows(buffer + (int)pbi->m_planeU - (pbi->m_border >> 1), pbi->m_height << 2,
		pbi->m_border >> 1, pbi->m_strideUV);
	PlaneSides(buffer + (int)pbi->m_planeV, pbi->m_width << 2, pbi->m_height << 2,
		pbi->m_border >> 1, pbi->m_strideUV);
	PlaneRows(buffer + (int)pbi->m_planeV - (pbi->m_border >> 1), pbi->m_height << 2,
		pbi->m_border >> 1, pbi->m_strideUV);
	(void)border;
}
