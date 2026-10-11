// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00598B2A@@UAE@XZ @0x00598CFD 125B via clear plus members plus virtual base
// Evidence: virtual dtor vtable 0x00870D2C; rowed clear 0x00598B2A; vector dtor 0x0002CC70 at +0x4C; holder free at +0x3C via rowed _free 0x00030830; rowed hashtable dtor 0x005982AC at +0x18; rowed List_base dtor 0x004EC395 at +0x14; rowed tree dtor 0x005981CA at +8; base dtor pinned at 0x00506B28
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
#include <vector>
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
extern "C" void __cdecl free(void *p);
class Rva005980F3
{
public:
	~Rva005980F3();
private:
	void *m_head;
	int m_flag;
};
class Rva005982AC
{
public:
	~Rva005982AC();
private:
	char m_pad[4];
	void *_s;
	void *_f;
	void *_e;
};
struct Holder004
{
	void *m_ptr;
	~Holder004() { if (m_ptr) free(m_ptr); }
};
class Rva00598CFDBase
{
public:
	virtual ~Rva00598CFDBase();
};
class Rva00598B2A : public Rva00598CFDBase
{
public:
	void rva00598B2A();
	virtual ~Rva00598B2A();
private:
	char m_pad04[4];
	Rva005980F3 m_tree;
	char m_pad10[4];
	_STL::list<int> m_list;
	Rva005982AC m_hasht;
	char m_pad28[0x3C - 0x28];
	Holder004 m_hold;
	char m_pad40[0x4C - 0x40];
	_STL::vector<AsciiString> m_vec;
};
Rva00598B2A::~Rva00598B2A()
{
	rva00598B2A();
}
