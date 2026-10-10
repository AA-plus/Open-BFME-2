// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport

// CameraMarker range copy for the FlammableUpdate file cluster.
// Explicit vector instantiation pulls the STLport __copy<CameraMarker*>
// core, which retail calls at 0x0048C897 (47 bytes) from the assign wrapper
// at 0x00288A5C. /O1 is load-bearing: without it the loop enregisters
// pointers (61 bytes); with it the frame keeps the EBP shape and the
// stack-slot updates exactly as retail. The element is a size-faithful
// 8-byte view (next link plus name word); only its address and the
// declared-only copy assignment feed codegen here, and that assignment
// resolves through the rowed ??4CameraMarker at 0x28876F. Unclaimed
// sibling emissions ride along (explicit-instantiation TUs are exempt
// from the unmatched check, stlport_vector_pair precedent).

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

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

struct CameraMarker
{
	~CameraMarker();
	CameraMarker &operator=(const CameraMarker &src);

	CameraMarker *m_next;
	void *m_name;
};

template class _STL::vector<CameraMarker, _STL::allocator<CameraMarker> >;
