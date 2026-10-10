// cl: /Ireference/shims/ini_bfme2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Include /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ??0Rva003200EB@@QAE@XZ @0x003200EB 81B.
// Ctor: int@+0 zeroed, floats@+4/+8 default 1.0f via shared literal at
// 0x00BBB8D8, list<int>@+0xC default-constructed then cleared. Caller
// 0x0031C87C in unclaimed 0x0031C83D region. Prev 0x003200BC shares class
// flags and list<int> usage in ControlBarList003200A2.cpp. Honest address
// ctor name (owner unproven).
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

class Rva003200EB
{
public:
	Rva003200EB();
private:
	int m_unk00;
	float m_unk04;
	float m_unk08;
	std::list<int> m_list0C;
};

Rva003200EB::Rva003200EB()
{
	m_unk00 = 0;
	m_list0C.clear();
	m_unk04 = m_unk08 = 1.0f;
}
