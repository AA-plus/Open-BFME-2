// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ?rva0041E971@Rva0041E971@@QAEPAVGameWindow@@PAVWindowVideo@@@Z @0x0041E971 51B.
// Reverse lookup over the WindowVideoManager playing map (+0xC): begin(),
// compare second (WindowVideo*) to arg, return first (GameWindow*), else null.
// Uses the real WindowVideoManager::WindowVideoMap type (private made public
// TU-locally) so begin/++ mangle to the rowed 0x00427195/0x0041E832 bodies.
// Layout pad 0xC reproduces retail add ecx,0xC. Evidence: callees rowed in
// window_video_manager.cpp, caller at 0x005AE117.

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

class Rva0041E971
{
public:
	GameWindow *rva0041E971(WindowVideo *vid);
private:
	char m_pad[12];
	WindowVideoManager::WindowVideoMap m_map;
};

GameWindow *Rva0041E971::rva0041E971(WindowVideo *vid)
{
	WindowVideoManager::WindowVideoMap::iterator it = m_map.begin();
	for (; it != m_map.end(); ++it)
	{
		if (it->second == vid)
			return (GameWindow *)it->first;
	}
	return NULL;
}
