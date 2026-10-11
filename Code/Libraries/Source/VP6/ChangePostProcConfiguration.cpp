// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b67e0.md plus retail only. No
// decoder source was consulted.
//
// ChangePostProcConfiguration (retail 0x001B67E0): copies the 14-dword frame
// configuration into the post-processor instance at +0x40 and derives the
// fragment counts (width and height shifted right 3), plane and unit fragment
// totals, the motion-vector border and the reconstruction Y, U and V data
// offsets. All divisions are unsigned shifts.
extern "C" void *__cdecl memcpy(void *destination, const void *source,
	unsigned int bytes);

struct PostProcPlaneRecord
{
	unsigned char m_pad00[0x40];
	unsigned int m_width;
	unsigned int m_rawHeight;
	unsigned int m_plane;
	unsigned int m_stride;
	unsigned int m_copied[10];
	unsigned int m_at78;
	unsigned int m_at7C;
	unsigned int m_at80;
	unsigned int m_at84;
	unsigned int m_at88;
	unsigned int m_at8C;
	unsigned int m_at90;
	unsigned int m_at94;
	unsigned int m_at98;
	unsigned int m_at9C;
	unsigned char m_padA0[0x14];
	unsigned int m_atB4;
};

// RVA 0x001B67E0
extern "C" void __cdecl ChangePostProcConfiguration(void *selfRaw, void *sourceRaw)
{
	PostProcPlaneRecord *self = (PostProcPlaneRecord *)selfRaw;
	unsigned int *source = (unsigned int *)sourceRaw;

	memcpy(&self->m_width, source, 14 * 4);

	unsigned int plane = self->m_plane;
	unsigned int rawHeight = self->m_rawHeight;
	unsigned int width = self->m_width;
	width >>= 3;
	unsigned int height = rawHeight >> 3;
	self->m_at94 = height;
	unsigned int pixels = height * width;
	self->m_at84 = pixels;
	const unsigned int *strideField = &self->m_stride;
	register unsigned int stride = *strideField;
	unsigned int quarterPixels = pixels >> 2;
	self->m_at8C = pixels + quarterPixels * 2;
	self->m_at90 = width;

	unsigned int chromaSpan = (plane - width * 8) >> 1;
	self->m_at78 = (plane + 1) * chromaSpan;

	unsigned int planeBytes = (rawHeight + chromaSpan * 2) * plane;
	self->m_at98 = plane;
	self->m_atB4 = chromaSpan;
	self->m_at88 = quarterPixels;
	self->m_at7C = (stride + 1) * (chromaSpan >> 1) + planeBytes;
	self->m_at9C = stride;
	self->m_at80 = (chromaSpan >> 1) * stride
		+ ((rawHeight >> 1) + chromaSpan) * stride
		+ (chromaSpan >> 1) + planeBytes;
}
