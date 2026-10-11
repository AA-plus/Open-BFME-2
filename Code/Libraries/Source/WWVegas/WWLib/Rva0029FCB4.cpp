// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva0029FCB4@Rva0029FCB4@@QAE?AV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@XZ retail 0x0029FCB4 32B
// By-value Science vector getter via final override +0x24. Evidence: rowed
// friend_getFinalOverride 0x00288609 plus rowed vector<ScienceType> copy ctor
// 0x0054878E; ret 4 with hidden pointer; 7 callers.
#include <vector>

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

enum ScienceType
{
	SCIENCE_NONE = 0
};
// Native scalar-vector cleanup uses the rowed game-memory free wrapper.
// Keep the first compatible ScienceType destructor's allocator identity.
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template <> inline _Vector_base<ScienceType, allocator<ScienceType> >::~_Vector_base()
{ if (_M_start) Rva00030830GameFree(_M_start); }
}


class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
};

class Rva0029FCB4
{
public:
	_STL::vector<ScienceType> rva0029FCB4();

private:
	char _pad[0x24];
	_STL::vector<ScienceType> m_24;
};

_STL::vector<ScienceType> Rva0029FCB4::rva0029FCB4()
{
	const Overridable *f = ((const Overridable *)this)->friend_getFinalOverride();
	return *(const _STL::vector<ScienceType> *)((const char *)f + 0x24);
}
