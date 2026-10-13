// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
// STLport 4.5.3 bit-vector fill constructor used by retail 0x0043FE13.
// Out-of-line base plus _M_initialize with an inlined 0/-1 fill loop.
#include <vector>
template _STL::vector<bool>::vector(unsigned, bool, _STL::allocator<bool> const &);
