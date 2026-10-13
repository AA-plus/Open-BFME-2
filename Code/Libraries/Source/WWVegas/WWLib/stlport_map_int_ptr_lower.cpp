// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
//
// Dedicated TU for map<unsigned,void*>::_M_lower_bound. Reloc named this
// address as the signed-int tree but retail uses jb not jl.

#include <map>
// bfme link decl-only begin
namespace _STL { template <> pair<_Rb_tree_iterator<pair<unsigned int const, void *>, _Nonconst_traits<pair<unsigned int const, void *> > >, bool> _Rb_tree<unsigned int, pair<unsigned int const, void *>, _Select1st<pair<unsigned int const, void *> >, less<unsigned int>, allocator<pair<unsigned int const, void *> > >::insert_unique(pair<unsigned int const, void *> const &); }
// bfme link decl-only end

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

typedef _STL::pair<const unsigned, void *> PairIntPtrLower;
typedef _STL::_Rb_tree<unsigned, PairIntPtrLower, _STL::_Select1st<PairIntPtrLower>, _STL::less<unsigned>, _STL::allocator<PairIntPtrLower> > TreeIntPtrLower;
typedef _STL::map<unsigned, void *, _STL::less<unsigned>, _STL::allocator<PairIntPtrLower> > MapIntPtrLower;

// Explicit single-member instantiations for the 7 rows this TU owns.
// Replaces the former whole-class instantiation, which emitted 140 COMDAT
// copies including 7 that differ from retail (link lane). Each line emits
// exactly one owned body; calls to shared helpers reach the retail copy
// another TU provides.
template TreeIntPtrLower::_Link_type TreeIntPtrLower::_M_lower_bound(const unsigned &) const;
template TreeIntPtrLower::_Link_type TreeIntPtrLower::_M_upper_bound(const unsigned &) const;
template TreeIntPtrLower::_Link_type TreeIntPtrLower::_M_find<unsigned>(const unsigned &) const;
template TreeIntPtrLower::_Link_type TreeIntPtrLower::_M_copy(TreeIntPtrLower::_Link_type, TreeIntPtrLower::_Link_type);
template TreeIntPtrLower::iterator TreeIntPtrLower::insert_unique(TreeIntPtrLower::iterator, const TreeIntPtrLower::value_type &);
template TreeIntPtrLower::_Rb_tree(const TreeIntPtrLower &);
template bool MapIntPtrLower::value_compare::operator()(const MapIntPtrLower::value_type &, const MapIntPtrLower::value_type &) const;

