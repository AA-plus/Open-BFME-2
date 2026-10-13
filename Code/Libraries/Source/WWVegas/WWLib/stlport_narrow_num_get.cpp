// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <string>
// Canonical default construction is supplied by retail7850.
namespace _STL { template <> basic_string<char>::basic_string(); }
#include <locale>
// The complete native float scanners are owned by the read_float units
// (F850 narrow;10420 wide). Keep this unit's generic copies out of the link.
namespace _STL {
template <> bool _M_read_float<istreambuf_iterator<char, char_traits<char> >, char>(
    string &, istreambuf_iterator<char, char_traits<char> > &,
    istreambuf_iterator<char, char_traits<char> > &, ios_base &, char *);
}
// basic_string<char>::reserve is retail's 116-byte body at 0x0000C390, owned by
// stlport_narrow_string_reserve.cpp; this unit's header copy is not retail's and
// came before it in link order, so only declare its instantiation here.
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int); }
// Use the complete retail scanner at 0x00007C90 rather than a competing
// generic header implementation.
namespace _STL {
template <> int _M_get_base_or_zero<istreambuf_iterator<char, char_traits<char> >, char>(
    istreambuf_iterator<char, char_traits<char> > &,
    istreambuf_iterator<char, char_traits<char> > &, ios_base &, char *);
}

// Suppress this TU's non-retail _String_base<char> dtor copy (family2-LK3 rows
// 22/26): the rowed 63B copy in stlport_narrow_string_base_dtor.cpp serves the link.
template <> _STL::_String_base<char, _STL::allocator<char> >::~_String_base();
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> istreambuf_iterator<char, char_traits<char> > num_get<char, istreambuf_iterator<char, char_traits<char> > >::do_get(istreambuf_iterator<char, char_traits<char> >, istreambuf_iterator<char, char_traits<char> >, ios_base &, int &, long double &) const; }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
template class _STL::num_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;

// Keep the two independently rowed string-termination helpers emitted.
template void _STL::basic_string<char>::_M_terminate_string();
template void _STL::basic_string<char>::_M_terminate_string_aux(const _STL::__true_type &);

// Taking these addresses preserves the three independently rowed header helpers
// formerly emitted only by the removed generic scanner. These constants are
// emission anchors, not claimed retail data.
void (*const bfmeNarrowFloatInitAnchor)(const _STL::ctype<char> &, char &, char &, char &, char &, char *) = &_STL::_Initialize_get_float;
bool (*const bfmeNarrowFloatDigitSeparatorAnchor)(char &, char, const char *) = &_STL::__get_fdigit_or_sep;
bool (*const bfmeNarrowFloatDigitAnchor)(char &, const char *) = &_STL::__get_fdigit;
