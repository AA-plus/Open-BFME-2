// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <sstream>

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_ostringstream<char, char_traits<char>, allocator<char> >::basic_ostringstream(int); }
namespace _STL { template <> basic_stringbuf<char, char_traits<char>, allocator<char> >::basic_stringbuf(int); }
namespace _STL { template <> basic_ostringstream<char, char_traits<char>, allocator<char> >::~basic_ostringstream(); }
namespace _STL { template <> basic_stringbuf<char, char_traits<char>, allocator<char> >::~basic_stringbuf(); }
namespace _STL { template <> int basic_stringbuf<char, char_traits<char>, allocator<char> >::_M_xsputnc(char, int); }
namespace _STL { template <> int basic_stringbuf<char, char_traits<char>, allocator<char> >::overflow(int); }
namespace _STL { template <> int basic_stringbuf<char, char_traits<char>, allocator<char> >::pbackfail(int); }
namespace _STL { template <> fpos<int> basic_stringbuf<char, char_traits<char>, allocator<char> >::seekoff(long, int, int); }
namespace _STL { template <> fpos<int> basic_stringbuf<char, char_traits<char>, allocator<char> >::seekpos(fpos<int>, int); }
namespace _STL { template <> basic_streambuf<char, char_traits<char> > * basic_stringbuf<char, char_traits<char>, allocator<char> >::setbuf(char *, int); }
namespace _STL { template <> int basic_stringbuf<char, char_traits<char>, allocator<char> >::uflow(); }
namespace _STL { template <> int basic_stringbuf<char, char_traits<char>, allocator<char> >::underflow(); }
namespace _STL { template <> int basic_stringbuf<char, char_traits<char>, allocator<char> >::xsputn(char const *, int); }
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
template class _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> >;
