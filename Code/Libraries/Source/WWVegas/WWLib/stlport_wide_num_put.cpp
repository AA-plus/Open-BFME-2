// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport

#include <stl/_alloc.h>
// Public malloc release uses retail's unoptimized import entry; callers keep the header inline body.
namespace _STL {
#pragma optimize("", off)
template <> __forceinline void __malloc_alloc<0>::deallocate(void *p, size_t) { free((char *)p); }
#pragma optimize("", on)
}

#include <locale>

#include <cstddef>
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
template class _STL::num_put<wchar_t, _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
