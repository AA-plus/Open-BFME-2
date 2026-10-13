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
	void Release_Ref();
};

class TextureClass
{
public:
	void Release_Ref();
};

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
			m_prototype->Release_Ref();
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
