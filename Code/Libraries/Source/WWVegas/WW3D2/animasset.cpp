// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?HasAnim@AnimationAsset@@SA_NPBD@Z @ 0x0014CE16 (81 bytes).
// WB9C3BF0 animasset.cpp identifies AnimationAsset::HasAnim. Native a*
// prefix, lowercasing and registry membership independently confirm its role.
// Animation-asset existence check: builds the "a*"+name key lowercased in
// a 512-byte buffer and returns the registry contains-check. No SEH (no
// object lifetimes); the checker address is pinned.

#include "AnimationAssetBFME2.h"

extern "C" char *_mbscpy(char *destination, const char *source);
extern "C" __declspec(dllimport) char *__cdecl _strlwr(char *string);

// Registry contains-check (retail 0x0061F0D0, 28B): null name or null
// registry answers false, else tail-calls the registry lookup 0xA21170.
extern bool __cdecl Render_Obj_Exists(const char *name);

// ?HasAnim@AnimationAsset@@SA_NPBD@Z
bool AnimationAsset::HasAnim(const char *name)
{
	if (name == 0)
		return false;

	char lookup[512];
	_mbscpy(lookup, "a*");
	_mbscpy(lookup + 2, name);
	_strlwr(lookup);
	return Render_Obj_Exists(lookup);
}

//
// ?Get@AnimationAsset@@SA?AVHAnimPrototypeOwner@@PBD@Z @ 0x0014CF01
// (94 bytes). WB9C3B30 animasset.cpp names AnimationAsset::Get; native
// hidden result and owner lifetimes independently confirm its role. The
// existing HAnimPrototypeOwner ABI name remains a view, not a target fact.
// Registry-owner factory for animation prototypes: null name
// returns a default owner, otherwise a converting temporary. Mixed
// named-return plus temporary-return sources the single construction flag
// with direct hidden-slot construction (same recipe as the landed HTree
// factory 0x0017FC1E, whose re_log partial first mapped this family).

class HierarchyPrototype
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual int slot10();
	virtual void slot11();
	char m_pad[0x10]; // +0x04
	HAnimClass *m_animation; // +0x14
};

#include "../../../../GameEngineDevice/Source/W3DDevice/GameClient/BFME2ParticleTextureHandles.h"

class HierarchyPrototypeRef
{
public:
	~HierarchyPrototypeRef()
	{
		if (m_object != 0)
			((TextureClass *)m_object)->Release_Ref();
	}

private:
	HierarchyPrototype *m_object;
};

class HAnimPrototypeOwner
{
public:
	HAnimPrototypeOwner() : m_prototype(0) {}
	HAnimPrototypeOwner(const HierarchyPrototypeRef &source);
	~HAnimPrototypeOwner()
	{
		if (m_prototype != 0)
			((TextureClass *)m_prototype)->Release_Ref();
	}

	HierarchyPrototype *m_prototype; // +0x00
};

extern HierarchyPrototypeRef __cdecl Rva0061F230_GetPrototype(const char *name);

// ?Get@AnimationAsset@@SA?AVHAnimPrototypeOwner@@PBD@Z
HAnimPrototypeOwner AnimationAsset::Get(const char *name)
{
	if (name == 0)
	{
		HAnimPrototypeOwner empty;
		return empty;
	}
	return HAnimPrototypeOwner(Rva0061F230_GetPrototype(name));
}


// Native returned animation has a reference count at+4; no additional layout
// is inferred here. WB9C3CB0 names GetAnim and independently shows its asset
// ownership. Cursor and particle callers pass this object to Set_Animation.
class HAnimClass { public: char unknown00[4]; int m_refCount; };
// Existing registry ABI alias retained from the previous GetAnim unit.
#pragma comment(linker, "/alternatename:?Rva0061F230_GetPrototype@@YA?AVHierarchyPrototypeRef@@PBD@Z=?Rva009EBCE0_GetPrototype@@YA?AVRva009EBCE0AssetReference@@PBD@Z")
HAnimClass *AnimationAsset::GetAnim(const char *name)
{
	if (name == 0)
		return 0;

	char lookup[512];
	_mbscpy(lookup, "a*");
	_mbscpy(lookup + 2, name);
	_strlwr(lookup);

	HAnimPrototypeOwner owner(Rva0061F230_GetPrototype(lookup));
	if (owner.m_prototype == 0)
		return 0;

	HierarchyPrototype *object = owner.m_prototype;
	if ((unsigned char)object->slot10() == 0)
		object->slot11();
	HAnimClass *animation = object->m_animation;
	if (animation != 0)
		++animation->m_refCount;
	return object->m_animation;
}


// Existing Get_HAnim callers share this same verified animation body.
#pragma comment(linker, "/alternatename:?Get_HAnim@@YAPAVHAnimClass@@PBD@Z=?GetAnim@AnimationAsset@@SAPAVHAnimClass@@PBD@Z")
