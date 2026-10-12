// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// PlayerTemplateStore::rva001FD4A2, retail 0x001FD4A2 (63 B; WB 0x00A78370,
// unnamed, reached through a vtable): drops the INI overrides of every
// player template (Overridable::deleteOverrides 0x001E35ED) in the store's
// template vector at +0x0C (stride 0x1DC, as the rowed lookups in
// PlayerTemplate.cpp read it). Zero Hour's reset() keeps the list; this is
// BFME's override-aware counterpart. The method name is address-derived.
#include <vector>

class Overridable
{
public:
	Overridable *deleteOverrides();		// 0x001E35ED
};

struct PlayerTemplateOverrideView : public Overridable
{
	char m_bytes[0x1DC];
};

class PlayerTemplateStore
{
public:
	void rva001FD4A2();
private:
	char m_pad00[0x0C];
	_STL::vector<PlayerTemplateOverrideView> m_playerTemplates;	// +0x0C
};

void PlayerTemplateStore::rva001FD4A2()
{
	for (unsigned int i = 0; i < m_playerTemplates.size(); ++i)
		m_playerTemplates[i].deleteOverrides();
}
