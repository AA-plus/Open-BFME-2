// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport

#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <map>
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Const_traits<pair<int const, int> > > _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::upper_bound(int const &) const; }
namespace _STL { template <> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_Rb_tree(_Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > > const &); }
namespace _STL { template <> map<int, int, less<int>, allocator<pair<int const, int> > >::map(map<int, int, less<int>, allocator<pair<int const, int> > > const &); }
namespace _STL { template <> _Rb_tree_node<pair<int const, int> > * _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_M_copy(_Rb_tree_node<pair<int const, int> > *, _Rb_tree_node<pair<int const, int> > *); }
namespace _STL { template <> void map<int, int, less<int>, allocator<pair<int const, int> > >::clear(); }
namespace _STL { template <> unsigned int map<int, int, less<int>, allocator<pair<int const, int> > >::count(int const &) const; }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > > _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::equal_range(int const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > > map<int, int, less<int>, allocator<pair<int const, int> > >::equal_range(int const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Const_traits<pair<int const, int> > >, _Rb_tree_iterator<pair<int const, int>, _Const_traits<pair<int const, int> > > > map<int, int, less<int>, allocator<pair<int const, int> > >::equal_range(int const &) const; }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > map<int, int, less<int>, allocator<pair<int const, int> > >::insert(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, pair<int const, int> const &); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::swap(_Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > > &); }
// bfme link decl-only end

// Preserve retail's inlined buffer release while using the canonical public allocator.
namespace _STL {
#pragma optimize("gsy", on)
template <> __forceinline void allocator<_Rb_tree_node<pair<const int, int> > >::deallocate(_Rb_tree_node<pair<const int, int> > *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

class GameWindow;
typedef _STL::_Rb_tree<GameWindow *, GameWindow *, _STL::_Identity<GameWindow *>, _STL::less<GameWindow *>, _STL::allocator<GameWindow *> > RetailRangeTree;
typedef _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > IntMapTree;

// Use the separately compiled size-optimized subtree erase at retail 0x692F5.
// Suppress this speed-profile copy so callers select the verified provider.
namespace _STL {
template <> void IntMapTree::_M_erase(_Rb_tree_node<pair<const int, int> > *);
// Native clone owner is the verified 30B body at 0x0053444F.
// This speed-profile unit emits a different allocation/cleanup shape.
template <> IntMapTree::_Link_type IntMapTree::_M_clone_node(IntMapTree::_Link_type);
// This unit inlines the tree walk into map::lower_bound; retail calls the
// worker (rows 59 family2-LK3). Suppress both overloads so the link keeps
// the retail copy another unit provides.
template <> _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::iterator _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::lower_bound(const int &);
template <> _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::const_iterator _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::lower_bound(const int &) const;
// Same for map::find (row 38): suppress so the link keeps the retail copy.
template <> _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::iterator _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::find(const int &);
template <> _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::const_iterator _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::find(const int &) const;
// Same for operator[] (row 39 S): suppress so the link keeps the retail copy.
template <> int &_STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::operator[](const int &);
// Member-template suppression attempt (row 37 _Rb_tree::find).
template <> template <> IntMapTree::iterator IntMapTree::find<int>(const int &);
// Plain-member suppression for _Rb_tree::lower_bound (row 40).
template <> IntMapTree::iterator IntMapTree::lower_bound(const int &);
template <> IntMapTree::const_iterator IntMapTree::lower_bound(const int &) const;
}

// The historical int-map spelling of erase at 0x61F8A0 reaches the existing
// pointer-tree range owner at 0x61F840. Preserve that call explicitly: its
// unsigned pointer comparison is not the signed int-map range at 0x2F1C89.
// The int-map row name is a legacy structural view, not an application identity.
template <> inline IntMapTree::size_type IntMapTree::erase(const int &key)
{
	_STL::pair<RetailRangeTree::iterator, RetailRangeTree::iterator> range =
		reinterpret_cast<RetailRangeTree *>(this)->equal_range(reinterpret_cast<GameWindow *const &>(key));
	size_type count = _STL::distance(reinterpret_cast<iterator &>(range.first), reinterpret_cast<iterator &>(range.second));
	erase(reinterpret_cast<iterator &>(range.first), reinterpret_cast<iterator &>(range.second));
	return count;
}

template class _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >;

// Unsigned four-byte key view used by the asset-manager set operations at
// 0x61F910/0x61FAA0. The range release is the complete 144-byte ICF twin of
// this unit's int-map owner at 0x61F7B0, including its allocation release and
// 0x692F5 subtree callee. No original key or application class name is claimed.
extern void __cdecl Rva00030830FreeAllocation(void *);
struct Rva0061F910Key { unsigned int a; };
inline bool operator<(const Rva0061F910Key &left, const Rva0061F910Key &right)
{
    return left.a < right.a;
}
typedef _STL::_Rb_tree<Rva0061F910Key, Rva0061F910Key,
    _STL::_Identity<Rva0061F910Key>, _STL::less<Rva0061F910Key>,
    _STL::allocator<Rva0061F910Key> > NativeTree;
namespace _STL {
template <> __forceinline void allocator<_Rb_tree_node<Rva0061F910Key> >::deallocate(
    _Rb_tree_node<Rva0061F910Key> *p, size_t) const
{
    if (p != 0) Rva00030830FreeAllocation(p);
}
template <> void NativeTree::_M_erase(_Rb_tree_node<Rva0061F910Key> *);
}
template void NativeTree::erase(NativeTree::iterator, NativeTree::iterator);
