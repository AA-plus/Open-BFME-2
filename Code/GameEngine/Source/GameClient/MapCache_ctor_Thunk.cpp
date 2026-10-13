// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameClient/MapCache_ctor_Thunk.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// MapCache::MapCache 0x0022E28B (61B). Callee addresses are read off retail's
// call sites (reverse/symbols.csv). Only the placed bodies are carried; the
// donor's other definitions are omitted.
// Open-BFME5: clean C++ lift of the retail MapCache constructor.

#include <map>
#include <set>

typedef int Bool;

#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_base<_STL::pair<AsciiString const,int>,_STL::allocator<_STL::pair<AsciiString const,int> > >::_Rb_tree_base(_STL::allocator<_STL::pair<AsciiString const,int> > const &); }
namespace _STL { template <> _Rb_tree<AsciiString,_STL::pair<AsciiString const,int>,_STL::_Select1st<_STL::pair<AsciiString const,int> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<AsciiString const,int> > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree_base<_STL::pair<AsciiString const,int>,_STL::allocator<_STL::pair<AsciiString const,int> > >::~_Rb_tree_base(); }
namespace _STL { template <> void _Rb_tree<AsciiString,_STL::pair<AsciiString const,int>,_STL::_Select1st<_STL::pair<AsciiString const,int> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<AsciiString const,int> > >::_M_erase(_STL::_Rb_tree_node<_STL::pair<AsciiString const,int> > *); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<AsciiString const,int> > * _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<AsciiString const,int> > *,_STL::_Rb_tree_node<_STL::pair<AsciiString const,int> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<AsciiString const,int> > > >::allocate(unsigned int); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<AsciiString const,int> > * allocator<_STL::_Rb_tree_node<_STL::pair<AsciiString const,int> > >::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<AsciiString const,int> > *,_STL::_Rb_tree_node<_STL::pair<AsciiString const,int> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<AsciiString const,int> > > >::deallocate(_STL::_Rb_tree_node<_STL::pair<AsciiString const,int> > *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_Rb_tree_node<_STL::pair<AsciiString const,int> > >::deallocate(_STL::_Rb_tree_node<_STL::pair<AsciiString const,int> > *,unsigned int) const; }
// bfme link decl-only end

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
struct MapMetaData
{
	unsigned char m_data[252];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache : public std::map<AsciiString, MapMetaData>
{
public:
	MapCache();

private:
	std::map<AsciiString, Bool> m_seen;
	std::set<AsciiString> m_allowedMaps;
};

MapCache::MapCache()
{
}
