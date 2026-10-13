// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// The five virtuals behind numpunct<char>'s vftable at 0x007BBB78 and
// numpunct<wchar_t>'s at 0x007BBB94. No search was needed to identify these -
// the vftable slot IS the identity, and the ledger already holds slot 0 of
// both, so slots 1..5 are do_decimal_point, do_thousands_sep, do_grouping,
// do_truename and do_falsename in declaration order.

#include <locale>
#include <cstddef>
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

namespace _STL
{

char numpunct<char>::do_decimal_point() const
{
	return '.';
}

char numpunct<char>::do_thousands_sep() const
{
	return ',';
}

string numpunct<char>::do_grouping() const
{
	return string();
}

string numpunct<char>::do_truename() const
{
	return _M_truename;
}

string numpunct<char>::do_falsename() const
{
	return _M_falsename;
}

wchar_t numpunct<wchar_t>::do_decimal_point() const
{
	return L'.';
}

wchar_t numpunct<wchar_t>::do_thousands_sep() const
{
	return L',';
}

string numpunct<wchar_t>::do_grouping() const
{
	return string();
}

wstring numpunct<wchar_t>::do_truename() const
{
	return _M_truename;
}

wstring numpunct<wchar_t>::do_falsename() const
{
	return _M_falsename;
}

}
