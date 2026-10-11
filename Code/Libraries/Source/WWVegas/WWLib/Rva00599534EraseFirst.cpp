// cl: /GX-
// stlport
// ?rva00599534@Rva00599534@@QAEXH@Z @0x00599534 48B: list<int> at +4 erase first match via rowed erase 0x00438539; callers 0x004EC911 and 0x004EC055
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::erase(list<int, allocator<int> >::iterator);
}

// list<int> destruction otherwise instantiates the allocator<_List_node<int>>
// deallocate COMDAT (one byte shape per TU flags); an explicit
// dllimport+forceinline specialization takes those calls inline so this
// TU emits no external copy. Body is verbatim primary (assert included).
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


class Rva00599534
{
public:
	void rva00599534(int val);
private:
	char m_pad[4];
	_STL::list<int, _STL::allocator<int> > m_list;
};

void Rva00599534::rva00599534(int val)
{
	for (_STL::list<int, _STL::allocator<int> >::iterator it = m_list.begin(); it != m_list.end(); ++it) {
		if (*it == val) {
			m_list.erase(it);
			break;
		}
	}
}
