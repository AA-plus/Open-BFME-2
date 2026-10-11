// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
//
// ?insert@?$map@IPAXU?$less@I@_STL@@V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBIPAX@_STL@@U?$_Nonconst_traits@U?$pair@$$CBIPAX@_STL@@@2@@2@U32@ABU?$pair@$$CBIPAX@2@@Z
// retail 0x00534A0D 29B: map<unsigned void*>::insert(iterator position const value_type&)
// hint-forwarding wrapper over the rowed _Rb_tree hint insert_unique at 0x005348E7.
// Called once by the unclaimed operator[]-style worker at 0x00534A2A via 0x00534A7B.
// Flags copy the sibling map<unsigned void*> TU stlport_map_int_ptr_lower.cpp.
#include <map>

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

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

typedef _STL::map<unsigned, void *, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, void *> > > MapIntPtr;

template MapIntPtr::iterator MapIntPtr::insert(MapIntPtr::iterator, const MapIntPtr::value_type &);
