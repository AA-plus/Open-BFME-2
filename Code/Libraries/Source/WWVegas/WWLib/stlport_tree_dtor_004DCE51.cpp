// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??1?$_Rb_tree@GU?$pair@$$CBGH@_STL@@U?$_Select1st@U?$pair@$$CBGH@_STL@@@2@U?$less@G@2@V?$allocator@U?$pair@$$CBGH@_STL@@@2@@_STL@@QAE@XZ @0x004DCE51, 56B.
// GH map tree dtor: calls clear 0x004DCC39 then frees header via 0x00030830.
// Same 56B EH shape as 0x001DDB8E. Chain from clear. Callers 0x004DCEA6.
#include <map>

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

typedef _STL::_Rb_tree<unsigned short, _STL::pair<const unsigned short, int>, _STL::_Select1st<_STL::pair<const unsigned short, int> >, _STL::less<unsigned short>, _STL::allocator<_STL::pair<const unsigned short, int> > > GHMapTree004DCE51;

template GHMapTree004DCE51::~_Rb_tree();
