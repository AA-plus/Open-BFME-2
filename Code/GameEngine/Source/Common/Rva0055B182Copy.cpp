// cl: /Ireference/shims/bfmelist /Ireference/shims/bfme2_ascii /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0055B0CC@@QAE@ABV0@@Z @0x0055B182 166B: user-written copy constructor
// of the opaque owner whose ctor/dtor are the rowed 0x0055B048/0x0055B0CC
// (layout from Rva0055B048Ctor.cpp; vtable 0x00C6B900). It copies the scalars
// and the AsciiString at +0x0C, default-constructs both int lists (EH states
// 0/1), resets m_20 to true, copies the trailing fields, then assigns both
// lists through the rowed list<int>::operator= 0x002C54EE. Caller: the rowed
// Rva00573B23 copy 0x00573AC8. Identity is address-derived.
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

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::erase(list<int, allocator<int> >::iterator);
}

// Declaration-only: retail has one list<int>::insert (rowed in stlport_list_int_insert.cpp, node creation out of line);
// this unit calls it rather than emitting a copy with the node creation inlined.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::insert(list<int, allocator<int> >::iterator, const int &);
}

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

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

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include "ascii_string.h"

class Rva0055B0CC
{
public:
	Rva0055B0CC(const Rva0055B0CC &other);
	virtual ~Rva0055B0CC();

private:
	float m_04;
	int m_08;
	AsciiString m_0C;
	unsigned int m_10;
	_STL::list<int, _STL::allocator<int> > m_14;
	float m_18;
	_STL::list<int, _STL::allocator<int> > m_1C;
	bool m_20;
	bool m_21;
	int m_24;
	bool m_28;
};

Rva0055B0CC::Rva0055B0CC(const Rva0055B0CC &other) :
	m_04(other.m_04),
	m_08(other.m_08),
	m_0C(other.m_0C),
	m_10(other.m_10),
	m_18(other.m_18),
	m_20(true),
	m_21(other.m_21),
	m_24(other.m_24),
	m_28(other.m_28)
{
	m_14 = other.m_14;
	m_1C = other.m_1C;
}
