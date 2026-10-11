// cl: /Ireference/shims/bfmelist /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// _STL::hash_map<int, _STL::list<BfmePod264> >::operator[] @0x0028A104 166B.
// Retail finds the key via hashtable find (rowed dup 0x00148B27), inserts a
// default pair on miss via _M_insert 0x0028A0BB and returns the mapped list.
// Caller 0x0028A237 pushes key and reuses it; callee itself takes one arg
// (ret 4). Evidence: STLport _hash_map.h operator[] shape, prev/next rows in
// this family (stlport_hash_map_int_list_pod264.cpp flags), callees rowed,
// unlock lane unblocks 0x0028A1AA.

#include <hash_map>
#include <list>
#include <cstddef>
// Suppress this TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
}
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


struct BfmePod264 { int a[66]; };

template _STL::list<BfmePod264> &_STL::hash_map<int, _STL::list<BfmePod264>, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, _STL::list<BfmePod264> > > >::operator[](const int &);
