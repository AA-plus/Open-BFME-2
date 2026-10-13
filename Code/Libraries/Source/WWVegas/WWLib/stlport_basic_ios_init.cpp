// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Dedicated TU for basic_ios<char>::init. The retail body uses the generic
// ctype<char>::widen virtual rather than STLport's char widening
// specialization. Do not edit stlport_narrow_fstream.cpp.

#define _STLP_NO_METHOD_SPECIALIZATION
#include <istream>
#include <ostream>

// Suppress this TU's non-retail _String_base<char> dtor copy (family2-LK3 rows
// 22/26): the rowed 63B copy in stlport_narrow_string_base_dtor.cpp serves the link.
template <> _STL::_String_base<char, _STL::allocator<char> >::~_String_base();
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> bool _M_init<char, char_traits<char> >(basic_ostream<char, char_traits<char> > &); }
namespace _STL { template <> basic_ostream<char, char_traits<char> > & _M_put_num<char, char_traits<char>, long>(basic_ostream<char, char_traits<char> > &, long); }
namespace _STL { template <> basic_ostream<char, char_traits<char> > & _M_put_num<char, char_traits<char>, unsigned long>(basic_ostream<char, char_traits<char> > &, unsigned long); }
namespace _STL { template <> basic_ostream<char, char_traits<char> > & _M_put_num<char, char_traits<char>, double>(basic_ostream<char, char_traits<char> > &, double); }
namespace _STL { template <> void basic_ostream<char, char_traits<char> >::_M_put_char(char); }
namespace _STL { template <> void basic_ostream<char, char_traits<char> >::_M_put_nowiden(char const *); }
namespace _STL { template <> basic_ostream<char, char_traits<char> > & basic_ostream<char, char_traits<char> >::flush(); }
namespace _STL { template <> basic_ostream<char, char_traits<char> > & basic_ostream<char, char_traits<char> >::put(char); }
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
template class _STL::basic_istream<char, _STL::char_traits<char> >;
template class _STL::basic_istream<wchar_t, _STL::char_traits<wchar_t> >;
template class _STL::basic_ostream<char, _STL::char_traits<char> >;
template class _STL::basic_ostream<wchar_t, _STL::char_traits<wchar_t> >;
