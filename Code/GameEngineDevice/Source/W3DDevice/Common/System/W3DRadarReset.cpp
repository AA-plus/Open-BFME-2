// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?reset@W3DRadar@@UAEXXZ, retail 0x0004E2FA..0x0004E3A1 (167 bytes, EH). Zero Hour's
// W3DRadar::reset: the base Radar::reset, then under the DX8 thread lock the overlay and
// shroud textures' top surfaces are cleared to zero (rowed Get_Surface_Level 0x00132D70,
// clear 0x00116780, surface handle dtor 0x00176CB0) and the terrain texture reference is
// cleared (0x0004D75B); two primary-table steps (+0x20, +0x28) follow and the +0x1460 flag is
// set. The override is entered through the Radar sub-object at +4 of the W3DRadar object,
// so the view models W3DRadar with Radar as its second base (offsets are Radar-relative).
typedef unsigned int UnsignedInt;

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
struct BFMEDX8DeviceLock
{
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();
	void clear(UnsignedInt color);
private:
	void *m_surface;
};

class CursorTextureSlot
{
public:
	W3DRadarResetSurface Get_Surface_Level();
	void *texture;
};

class BfmeResetTextureRef
{
public:
	void clear();
	void *m_texture;
};

class W3DRadarPrimary
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
};

class Radar
{
public:
	virtual void reset();
};

class W3DRadar : public W3DRadarPrimary, public Radar
{
public:
	virtual void reset();
private:
	unsigned char m_pad08[0x1464 - 8];
	bool m_1464;					// +0x1460 from Radar
	unsigned char m_pad1465[0x1470 - 0x1465];
	CursorTextureSlot m_overlayTexture;		// +0x146C from Radar
	BfmeResetTextureRef m_terrainTexture;		// +0x1470 from Radar
	unsigned char m_pad1478[0x1480 - 0x1478];
	CursorTextureSlot m_shroudTexture;		// +0x147C from Radar
};

void W3DRadar::reset()
{
	Radar::reset();
	BFMEDX8DeviceLock lock;
	m_overlayTexture.Get_Surface_Level().clear(0);
	m_shroudTexture.Get_Surface_Level().clear(0);
	m_terrainTexture.clear();
	s08();
	s10();
	m_1464 = true;
}
