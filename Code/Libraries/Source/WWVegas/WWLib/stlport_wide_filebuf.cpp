// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <fstream>
// bfme link decl-only begin
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_allocate_buffers(unsigned short *, int); }
// bfme link decl-only end

template class _STL::basic_filebuf<wchar_t, _STL::char_traits<wchar_t> >;
