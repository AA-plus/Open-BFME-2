// cl: /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005A083C@AptOnlineCustomMatch@@QAEXXZ, retail 0x005A083C 140B. Unlock: builds 2-int list from +0x498/+0x49C when both non-null then WindowManager 0xB4/0xB0.
// Evidence: callees list base/push_front/push_back/dup/dtor rowed in stlport_list_int_o1; TheWindowManager global; caller 0x005A0D56.
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


class GameWindowManager
{
public:
	virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
	virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7();
	virtual void _v8(); virtual void _v9(); virtual void _v10(); virtual void _v11();
	virtual void _v12(); virtual void _v13(); virtual void _v14(); virtual void _v15();
	virtual void _v16(); virtual void _v17(); virtual void _v18(); virtual void _v19();
	virtual void _v20(); virtual void _v21(); virtual void _v22(); virtual void _v23();
	virtual void _v24(); virtual void _v25(); virtual void _v26(); virtual void _v27();
	virtual void _v28(); virtual void _v29(); virtual void _v30(); virtual void _v31();
	virtual void _v32(); virtual void _v33(); virtual void _v34(); virtual void _v35();
	virtual void _v36(); virtual void _v37(); virtual void _v38(); virtual void _v39();
	virtual void _v40(); virtual void _v41(); virtual void _v42(); virtual void _v43();
	virtual void slotB0(_STL::list<int> lst);
	virtual void slotB4();
};
extern GameWindowManager *TheWindowManager;

class AptOnlineCustomMatch
{
public:
	void rva005A083C();
private:
	char m_pad[0x498];
	int m_498;
	int m_49C;
};

void AptOnlineCustomMatch::rva005A083C()
{
	if (m_498 == 0)
		return;
	if (m_49C == 0)
		return;
	_STL::list<int> lst;
	lst.push_front(m_498);
	lst.push_back(m_49C);
	TheWindowManager->slotB4();
	TheWindowManager->slotB0(lst);
}
