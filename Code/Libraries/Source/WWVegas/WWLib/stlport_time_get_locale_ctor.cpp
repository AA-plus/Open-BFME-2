// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Instantiate the protected locale-time overload directly from STLport 4.5.3
// stl/_time_facets.h. Vtables BBBBC0 (narrow) and BBBBEC (wide) are independently
// established by the matched default constructors and destructors;
// _Time_Info starts at +0xC in both facets.
#include <locale>

// Suppress this TU's non-retail _String_base<char> dtor copy (family2-LK3 rows
// 22/26): the rowed 63B copy in stlport_narrow_string_base_dtor.cpp serves the link.
template <> _STL::_String_base<char, _STL::allocator<char> >::~_String_base();
template _STL::time_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >::time_get(_Locale_time *, size_t);
template _STL::time_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >::time_get(_Locale_time *, size_t);
