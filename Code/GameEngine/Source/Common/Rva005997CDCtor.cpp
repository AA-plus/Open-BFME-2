// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0Rva005997CD@@QAE@H@Z @0x00599784 73B
// Ctor of Rva005997CD (dtor at 0x005997CD): two list<int> at +0/+4 via rowed
// List_base ctor 0x004EC36C, AsciiString at +8 zeroed, int at +0xC from arg,
// bool at +0x10 false, returns this. Evidence: abuts dtor, same members,
// EH_prolog plus List_base twice, ret-4 single int arg, 1 caller.
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}
#include "ascii_string.h"

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

class Rva005997CD
{
public:
	Rva005997CD(int x);
	~Rva005997CD();
private:
	_STL::list<int> m_list0;
	_STL::list<int> m_list1;
	AsciiString m_str;
	int m_val;
	bool m_flag;
};

Rva005997CD::Rva005997CD(int x) : m_val(x), m_flag(false)
{
}
