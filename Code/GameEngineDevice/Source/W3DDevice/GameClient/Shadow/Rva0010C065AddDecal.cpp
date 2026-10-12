// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /GX- /MD
// ?rva0010C065@Rva0010C065@@UAEPAVW3DProjectedShadow@@PAURva0010C065Info@@@Z,
// retail 0x0010C065..0x0010C145 (224B): a Ghidra-unlisted table slot of the
// projected-shadow manager (Zero Hour's W3DProjectedShadowManager::addDecal
// role). It looks up the info's texture by name through the pinned
// 0x0010BC90 and builds the decal through the rowed factory 0x0010BB11
// (whose signature names every argument): type 0x1000 entries go on the +0x1C
// list with a second texture taken from the info's second name and the last
// flag set; all others go on the +0x08 list. Fields are named by offset.
#include "ascii_string.h"

class W3DShadowTexture;
class RenderObjClass;
class W3DProjectedShadow;

class Rva0010BC90ShadowManager
{
public:
	W3DShadowTexture *getTexture(const char *name);			// 0x0010BC90
};

class Rva0010BB11ShadowFactory
{
public:
	W3DProjectedShadow *create(W3DShadowTexture *texture, RenderObjClass *robj, int type,
		unsigned char flag, float sizeX, float sizeY, float value, float offsetU, float offsetV,
		void *list, unsigned char flag84, int secondTexture, unsigned char flag85);	// 0x0010BB11
};

struct Rva0010C065Info
{
	AsciiString m_textureName;								// +0x00
	AsciiString m_secondTextureName;						// +0x04
	int m_type;												// +0x08
	float m_sizeX;											// +0x0C
	float m_sizeY;											// +0x10
	char m_pad14[0x20 - 0x14];
	float m_value;											// +0x20
	char m_pad24[2];
	unsigned char m_flag;									// +0x26
};

class Rva0010C065
{
public:
	virtual W3DProjectedShadow *rva0010C065(Rva0010C065Info *info);
private:
	Rva0010BC90ShadowManager *textures() { return (Rva0010BC90ShadowManager *)this; }
	Rva0010BB11ShadowFactory *factory() { return (Rva0010BB11ShadowFactory *)this; }
	int m_04;
	char m_list08[0x1C - 0x08];								// +0x08
	char m_list1C[4];										// +0x1C
};

W3DProjectedShadow *Rva0010C065::rva0010C065(Rva0010C065Info *info)
{
	if (info == 0)
		return 0;
	if (info->m_type == 0x1000)
	{
		const char *secondName = info->m_secondTextureName.str();
		const char *name = info->m_textureName.str();
		return factory()->create(textures()->getTexture(name), 0, info->m_type, info->m_flag,
			info->m_sizeX, info->m_sizeY, info->m_value, 0.0f, 0.0f, m_list1C, 0,
			(int)textures()->getTexture(secondName), 1);
	}
	return factory()->create(textures()->getTexture(info->m_textureName.str()), 0, info->m_type, info->m_flag,
		info->m_sizeX, info->m_sizeY, info->m_value, 0.0f, 0.0f, m_list08, 0, 0, 0);
}
