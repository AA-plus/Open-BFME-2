// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??0Rva0060426C@@QAE@ABV0@@Z @0x0060426C 29B: copy ctor copies dword +0 then map<unsigned void*> at +4 via rowed Rb_tree copy 0x00603EEB. Evidence: callers 0x00604289 0x006045A2; callee rowed.
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

class Rva0060426C
{
public:
	unsigned int m_first;
	_STL::map<unsigned int, void *> m_map;
	Rva0060426C(const Rva0060426C &other);
};

Rva0060426C::Rva0060426C(const Rva0060426C &other) : m_first(other.m_first), m_map(other.m_map)
{
}

// ?Rva00604289Construct@@YAXPAVRva0060426C@@ABV1@@Z @0x00604289 45B placement-new copy via rowed 0x0060426C. Evidence: caller 0x00604374 and implicit null check.
void Rva00604289Construct(Rva0060426C *dest, const Rva0060426C &src)
{
	new(dest) Rva0060426C(src);
}
