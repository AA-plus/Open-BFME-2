// cl: /Ireference/shims/bfmelist /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ??1Rva00414520@@UAE@XZ @ 0x00414520 78B
// Evidence: chain via 0x0055A91A Clear; vptr 0x00C3A08C own then 0x00BBB554 base; members +0x08 pool release via rowed 0x00360D26 and +0x18 list<int> via rowed List_base dtor 0x004EC395; callers 0x00414571 deleting dtor 0x00414D94 0x00414E13; layout like BfmeAssignRecord44 in Rva0055A91AClear.cpp.
#include <list>

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

struct Rva0039BCF8;

#include "ScoredKillTrackerView.h"

class Xfer;

#include "Common/Snapshot.h"

class Rva00414520 : public Snapshot
{
public:
	virtual ~Rva00414520();
private:
	int m_04; // +0x04
	Rva00360D26Member m_08; // +0x08
	int m_0C; // +0x0C
	Rva0039BCF8 *m_10; // +0x10
	int m_14; // +0x14
	_STL::list<int, _STL::allocator<int> > m_18; // +0x18
	int m_1C; // +0x1C
};

Rva00414520::~Rva00414520()
{
	((ScoredKillTracker *)this)->rva0055A91A();
}
