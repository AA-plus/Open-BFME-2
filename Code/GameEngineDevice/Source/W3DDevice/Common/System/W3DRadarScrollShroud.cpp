// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?rva0004F580@W3DRadar@@UAEXXZ, retail 0x0004F580..0x0004F7D8 (600 bytes, EH).
// W3DRadar primary vftable 0x00BC4E34 slot 8 (the step W3DRadar::reset calls
// first): clears the texture held at +0x148C, then copies the "ScrollShroud"
// mapped image into it. The image's texture holder (+0x2C) is used when present,
// else the image file is loaded (0x00132D89, cached handle) and flagged
// (0x00132FE9). Under the DX8 device lock both top surfaces are locked
// (source read-only), equal-sized A8R8G8B8/A4R4G4B4 rows are copied (a size
// mismatch clears the destination), both are unlocked and +0x14D6 is set.
// Purpose and every offset/slot are read from the retail bytes; names of the
// method and of the +0x148C/+0x14D6 members are not recovered.
#include "ascii_string.h"

typedef unsigned int UnsignedInt;

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
void __cdecl Log_DX8_ErrorCode(unsigned int res);

struct BFMEDX8DeviceLock
{
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

static inline void DX8_ErrorCode(unsigned int res)
{
	if (res)
		Log_DX8_ErrorCode(res);
}

struct RECT;
struct D3DLOCKED_RECT
{
	int Pitch;
	void *pBits;
};

struct IDirect3DSurface8
{
	virtual long __stdcall QueryInterface(void);
	virtual unsigned long __stdcall AddRef(void);
	virtual unsigned long __stdcall Release(void);
	virtual long __stdcall GetDevice(void);
	virtual long __stdcall SetPrivateData(void);
	virtual long __stdcall GetPrivateData(void);
	virtual long __stdcall FreePrivateData(void);
	virtual long __stdcall GetContainer(void);
	virtual long __stdcall GetDesc(void);
	virtual long __stdcall unused09(void);
	virtual long __stdcall unused10(void);
	virtual long __stdcall unused11(void);
	virtual long __stdcall unused12(void);
	virtual long __stdcall LockRect(D3DLOCKED_RECT *locked, const RECT *rect, unsigned long flags);	// +0x34
	virtual long __stdcall UnlockRect(void);								// +0x38
};

class SurfaceClass
{
public:
	struct SurfaceDescription
	{
		unsigned int Format;
		unsigned int Width;
		unsigned int Height;
	};
	void Get_Description(SurfaceDescription &desc);
};

// The surface holder Get_Surface_Level returns: the D3D surface first.
class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();
	void clear(UnsignedInt color);
	IDirect3DSurface8 *m_surface;
};

class CursorTextureSlot
{
public:
	W3DRadarResetSurface Get_Surface_Level();
	void *texture;
};

class TextureClass
{
public:
	void Release_Ref();
};

class BFME2ParticleTextureHandle
{
public:
	~BFME2ParticleTextureHandle() { if (m_ptr) m_ptr->Release_Ref(); }
	TextureClass *m_ptr;
};


class TextureAsset
{
public:
	static BFME2ParticleTextureHandle Get(const char *filename, int a, int b);
	void rva00132FE9(bool flag);
};

class Image
{
public:
	char m_unreconstructed_00[8];
	AsciiString m_filename;			// +0x08
	char m_unreconstructed_0c[0x2C - 0x0C];
	CursorTextureSlot *m_textureSlot;	// +0x2C
};

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;

enum
{
	BFME_D3DFMT_A8R8G8B8 = 21,
	BFME_D3DFMT_A4R4G4B4 = 26,
	BFME_D3DLOCK_READONLY = 0x10
};

class W3DRadar
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void rva0004F580();
private:
	unsigned char m_unreconstructed_004[0x148C - 4];
	CursorTextureSlot m_148c;			// +0x148C
	unsigned char m_unreconstructed_1490[0x14D6 - 0x1490];
	bool m_14d6;					// +0x14D6
};

void W3DRadar::rva0004F580()
{
	m_14d6 = false;
	m_148c.Get_Surface_Level().clear(0);

	const Image *image = TheMappedImageCollection->findImageByName(AsciiString("ScrollShroud"));
	if (!image)
		return;

	BFME2ParticleTextureHandle texture = TextureAsset::Get(image->m_filename.str(), 1, 0);
	((TextureAsset *)&texture)->rva00132FE9(true);

	CursorTextureSlot *slot = image->m_textureSlot ? image->m_textureSlot : (CursorTextureSlot *)&texture;
	if (slot)
	{
		W3DRadarResetSurface srcSurface = slot->Get_Surface_Level();
		W3DRadarResetSurface dstSurface = m_148c.Get_Surface_Level();
		SurfaceClass::SurfaceDescription srcDesc;
		SurfaceClass::SurfaceDescription dstDesc;
		((SurfaceClass *)&srcSurface)->Get_Description(srcDesc);
		((SurfaceClass *)&dstSurface)->Get_Description(dstDesc);
		if (srcDesc.Format == dstDesc.Format)
		{
			BFMEDX8DeviceLock lock;
			IDirect3DSurface8 *src = srcSurface.m_surface;
			IDirect3DSurface8 *dst = dstSurface.m_surface;
			if (src && dst)
			{
				D3DLOCKED_RECT srcRect;
				D3DLOCKED_RECT dstRect;
				memset(&srcRect, 0, sizeof(srcRect));
				memset(&dstRect, 0, sizeof(dstRect));
				DX8_ErrorCode(src->LockRect(&srcRect, 0, BFME_D3DLOCK_READONLY));
				DX8_ErrorCode(dst->LockRect(&dstRect, 0, 0));
				if (srcDesc.Width == dstDesc.Width && srcDesc.Height == dstDesc.Height)
				{
					int bytesPerPixel;
					if (srcDesc.Format == BFME_D3DFMT_A8R8G8B8)
						bytesPerPixel = 4;
					else if (srcDesc.Format == BFME_D3DFMT_A4R4G4B4)
						bytesPerPixel = 2;
					else
						goto unlock;
					unsigned char *srcBits = (unsigned char *)srcRect.pBits;
					unsigned char *dstBits = (unsigned char *)dstRect.pBits;
					for (int y = dstDesc.Height - 1; y >= 0; --y)
					{
						memcpy(dstBits, srcBits, bytesPerPixel * dstDesc.Width);
						srcBits += srcRect.Pitch;
						dstBits += dstRect.Pitch;
					}
				}
				else if (dstDesc.Format == BFME_D3DFMT_A8R8G8B8 || dstDesc.Format == BFME_D3DFMT_A4R4G4B4)
				{
					memset(dstRect.pBits, 0, dstRect.Pitch * dstDesc.Height);
				}
unlock:
				DX8_ErrorCode(dst->UnlockRect());
				DX8_ErrorCode(src->UnlockRect());
				m_14d6 = true;
			}
		}
	}
}
