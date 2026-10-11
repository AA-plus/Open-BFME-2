// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <locale>

// Suppress this TU's non-retail _String_base<char> dtor copy (family2-LK3 rows
// 22/26): the rowed 63B copy in stlport_narrow_string_base_dtor.cpp serves the link.
template <> _STL::_String_base<char, _STL::allocator<char> >::~_String_base();
template class _STL::time_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > >;
