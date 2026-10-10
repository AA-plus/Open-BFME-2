// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?insert@?$list@PAX...@QAE?AU?$_List_iterator@PAX...@2@U32@ABQAX@Z, retail 0x00525A87, 37 bytes.
// Evidence: frameless body that calls the rowed list<void*>::_M_create_node
// at 0x005258C0, links the node before the given position and returns the
// iterator through the hidden pointer (ret 0xc). The snapped-boundary queue
// measured it inside MilesAudioManagerInit3DSamplePools.cpp, whose /Oy- keeps
// a frame pointer retail does not have here, so it lives in its own TU. The
// masked body occurs 46 times in .text but once with this callee.
#include <list>

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

template _STL::list<void *, _STL::allocator<void *> >::iterator
	_STL::list<void *, _STL::allocator<void *> >::insert(iterator, void *const &);
