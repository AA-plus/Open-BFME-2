// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// GameLogic::setControlBarOverride, retail 0x0024792F (79 B; WB 0x00D08DA0).
// Zero Hour's body, m_controlBarOverrides[make_pair(name, slot)] = button,
// with BFME 2's key order (slot, name): the make_pair<int, AsciiString> call
// 0x0023FC23 and the map subscript 0x00246FF6 on this+0x24 (the map the rowed
// lookup 0x00246F8E searches). The name is the one the rowed caller
// doRemoveCommandBarButton binds (0x003C5D5E). The map keeps the ledger's
// structural key and mapped-value names.
#include "ascii_string.h"
#include <map>
#include "../../Common/GameLogicObjectLookupView.h"

struct TreeKey00242F5E { int m_id; AsciiString m_name; };
struct TreeOpaqueMapped242F5E { unsigned int m_bits; };
bool operator<(const TreeKey00242F5E &a, const TreeKey00242F5E &b);

typedef _STL::map<TreeKey00242F5E, TreeOpaqueMapped242F5E, _STL::less<TreeKey00242F5E>, _STL::allocator<_STL::pair<const TreeKey00242F5E, TreeOpaqueMapped242F5E> > > ControlBarOverrideMap;

// The shared GameLogic view leaves +0x24 unmodelled; the override map lives there.
struct GameLogicControlBarOverrides
{
	unsigned char m_pad00[0x24];
	ControlBarOverrideMap m_controlBarOverrides;	// +0x24
};

void GameLogic::setControlBarOverride(const AsciiString &commandSetName, int slot, const CommandButton *commandButton)
{
	((GameLogicControlBarOverrides *)this)->m_controlBarOverrides[(const TreeKey00242F5E &)_STL::make_pair(slot, commandSetName)].m_bits = (unsigned int)commandButton;
}
