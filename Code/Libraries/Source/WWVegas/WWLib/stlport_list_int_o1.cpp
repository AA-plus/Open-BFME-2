// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// A vendored instantiation unit. It exists so the linker-selected bodies of
// this container appear as COMDATs that build/objplace.py can place against
// unlanded functions; the suffix says which optimisation level, because for
// these containers different bodies survive the link from different units.
#include <list>

// Declaration-only: retail has one list<int>::insert (rowed in stlport_list_int_insert.cpp, node creation out of line);
// this unit calls it rather than emitting a copy with the node creation inlined.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::insert(list<int, allocator<int> >::iterator, const int &);
}

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
// (Do NOT use where a rowed body inlines less<int>: _M_find/_M_insert and
// map/set bodies fail. Those TUs need the dllimport+body form instead.)
namespace _STL {
template <> bool less<int>::operator()(const int &a, const int &b) const;
}
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

template class _STL::list<int, _STL::allocator<int> >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva004EC395Member@@QAE@XZ=??1?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva0023DAA5List@@QAE@XZ=??1?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?clear@Rva0023DAA5List@@QAEXXZ=?clear@?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAEXXZ")
#pragma comment(linker, "/alternatename:??0?$_List_base@MV?$allocator@M@_STL@@@_STL@@QAE@ABV?$allocator@M@1@@Z=??0?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@ABV?$allocator@H@1@@Z")
#pragma comment(linker, "/alternatename:??0?$_List_base@UFloodMember@@V?$allocator@UFloodMember@@@_STL@@@_STL@@QAE@ABV?$allocator@UFloodMember@@@1@@Z=??0?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@ABV?$allocator@H@1@@Z")
