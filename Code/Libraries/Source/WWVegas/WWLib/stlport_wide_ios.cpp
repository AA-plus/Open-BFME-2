// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <ios>

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_ios<unsigned short, char_traits<unsigned short> > & basic_ios<unsigned short, char_traits<unsigned short> >::copyfmt(basic_ios<unsigned short, char_traits<unsigned short> > const &); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
template class _STL::basic_ios<wchar_t, _STL::char_traits<wchar_t> >;
