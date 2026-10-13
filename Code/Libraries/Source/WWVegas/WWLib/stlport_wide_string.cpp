// cl: /Ireference/shims/bfmealloc /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 wide-string instantiations.

#include <string>
// bfme link decl-only begin
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::reserve(unsigned int); }
// bfme link decl-only end

template class _STL::basic_string<wchar_t, _STL::char_traits<wchar_t>, _STL::allocator<wchar_t> >;
