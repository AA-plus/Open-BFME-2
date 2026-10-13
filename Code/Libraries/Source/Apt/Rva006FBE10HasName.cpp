// cl: /O2 /DNDEBUG /MD /EHsc
// Retail 0x006FBE10 (65 B, ret 4), right before AptScriptFunctionBase's
// rowed rva006FBED0: an AptScriptFunctionBase query that reports whether a
// name resolves in its scope. With no active script frame (the static
// spFrameStack, 0xE1835C) it looks the name up in the native hash (+8) of the
// function's creator scope (mpCreatorScope, +0x28 as checked below), false
// when there is none; otherwise in the active frame's own native hash. Both
// go through AptNativeHash::Lookup (0x0070B380). Retail tests the no-frame
// case first. The method name is address-derived; the derived class only
// gives this TU the base's protected members without editing the header.
#include "AptObject/AptScriptFunction.h"

struct Rva006FBE10HashOwner
{
	char m_pad0[8];
	AptNativeHash m_hash;
};

class Rva006FBE10Scope : public AptScriptFunctionBase
{
public:
	bool hasName(const EAStringC *name);
};

typedef char Rva006FBE10CreatorScopeAt28[(sizeof(AptObject) + 8 == 0x28) ? 1 : -1];

bool Rva006FBE10Scope::hasName(const EAStringC *name)
{
	if (!spFrameStack)
	{
		if (mpCreatorScope)
			return ((Rva006FBE10HashOwner *)mpCreatorScope)->m_hash.Lookup(name) != 0;
		return false;
	}
	return ((Rva006FBE10HashOwner *)spFrameStack)->m_hash.Lookup(name) != 0;
}
