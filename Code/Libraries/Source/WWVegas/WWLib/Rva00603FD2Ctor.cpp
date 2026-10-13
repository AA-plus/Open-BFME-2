// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// ??0Rva00603FD2@@QAE@PBIABV?$_Rb_tree@IU?$pair@$$CBIPAX@_STL@@U?$_Select1st@U?$pair@$$CBIPAX@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@@Z @0x00603FD2 29B: copy int from ptr plus tree copy at plus4. Evidence: caller 0x00604251 passes ptr plus tree; callee rowed Rb_tree copy 0x00603EEB; ret 8 two args.
#define _STLP_BFME_TREE_NODE_BASE_O2  // emit retail's _Rb_tree_node_base::_S_minimum/_S_maximum (vendor/stlport/stl/_tree.h)
#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

typedef _STL::pair<const unsigned, void *> PairIntPtr00603FD2;
typedef _STL::_Rb_tree<unsigned, PairIntPtr00603FD2, _STL::_Select1st<PairIntPtr00603FD2>, _STL::less<unsigned>, _STL::allocator<PairIntPtr00603FD2> > TreeIntPtr00603FD2;

class Rva00603FD2
{
public:
	Rva00603FD2(unsigned const *a, TreeIntPtr00603FD2 const &b);
private:
	unsigned m_00;
	TreeIntPtr00603FD2 m_04;
};

Rva00603FD2::Rva00603FD2(unsigned const *a, TreeIntPtr00603FD2 const &b) : m_00(*a), m_04(b)
{
}
