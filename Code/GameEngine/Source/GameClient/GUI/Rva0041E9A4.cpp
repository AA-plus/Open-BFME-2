// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ?rva0041E9A4@Rva0041F042@@UAEXXZ @0x0041E9A4 46B
// Evidence: ref lane VTABLE slot 9 of 0x0083AF78 (Rva0041F042 vtable); iterates WindowVideoMap at +0xC
// via rowed begin 0x00427195 and ++ 0x0041E832 calling rowed notifyAll 0x0041E717 on each second.
// Uses real WindowVideoMap type like sibling Rva0041E971Find; class proven by vtable.
#include <map>
#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
#include "prerts.h"
#include "ascii_string.h"
#include "subsystem_interface.h"
#define private public
#include "window_video_manager.h"
#undef private
#include "game_window.h"
#include "video_player.h"
#include "display.h"
// bfme link decl-only begin
namespace _STL { template <> _STL::_Hashtable_node<_STL::pair<GameWindow const * const,WindowVideo *> > * _Hashtable_iterator<_STL::pair<GameWindow const * const,WindowVideo *>,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > >::_M_skip_to_next(); }
namespace _STL { template <> _STL::_Ht_iterator<_STL::pair<GameWindow const * const,WindowVideo *>,_STL::_Nonconst_traits<_STL::pair<GameWindow const * const,WindowVideo *> >,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > > hashtable<_STL::pair<GameWindow const * const,WindowVideo *>,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > >::begin(); }
// bfme link decl-only end

class Rva0041E717Broadcast
{
public:
	void notifyAll();
};

class Rva0041F042
{
public:
	virtual void rva0041E9A4();
private:
	char m_pad04[12 - 4];
	WindowVideoManager::WindowVideoMap m_map0C;
};

void Rva0041F042::rva0041E9A4()
{
	WindowVideoManager::WindowVideoMap::iterator it = m_map0C.begin();
	for (; it != m_map0C.end(); ++it)
	{
		WindowVideo *v = it->second;
		((Rva0041E717Broadcast *)v)->notifyAll();
	}
}
