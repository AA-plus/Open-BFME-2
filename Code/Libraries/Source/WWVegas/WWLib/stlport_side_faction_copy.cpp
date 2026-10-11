// cl: /Ireference/shims/bfme2_ascii /Oy- /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// STLport 4.5.3 source instantiations for PC AllowedFactions (table C68DB8).
// PC callback 534FFB copies an AsciiString vector into an ordered set with
// inserter(set, set.begin()). Its complete call chain is 534FD8 -> 534FB3 ->
// 534E99 -> 534DE6; the final assignment calls the already established
// AsciiString set hinted insertion and tree increment, not an inferred pin.
// Four-byte source stride, string copy/destroy callees and the previously
// verified AsciiString set node/value layout independently constrain the type.
// Xbox correspondence identified the parser family; it supplies no PC bytes.
#include <set>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}
#include <algorithm>
#include <iterator>

#include "ascii_string.h"

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
template <> pair<Lk6AsciiSetTree::iterator, bool> Lk6AsciiSetTree::insert_unique(const AsciiString&);
template <> Lk6AsciiSetTree::iterator Lk6AsciiSetTree::insert_unique(Lk6AsciiSetTree::iterator, const AsciiString&);
template <> _Rb_tree_node<AsciiString> *Lk6AsciiSetTree::_M_create_node(const AsciiString&);
}
bool operator<(const AsciiString &, const AsciiString &);

typedef _STL::set<AsciiString> FactionSet;
typedef _STL::insert_iterator<FactionSet> FactionInserter;
template FactionInserter _STL::copy(AsciiString *, AsciiString *, FactionInserter);
