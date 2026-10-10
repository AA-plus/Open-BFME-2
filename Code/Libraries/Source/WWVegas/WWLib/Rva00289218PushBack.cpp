// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva00289218@Rva00289218@@QAEXPBVModuleData@@@Z, retail 0x00289218, 16 bytes.
//
// Forwards a ModuleData pointer to the vector<const ModuleData*> at +0x14
// through the rowed ModuleFactory push_back at 0x004DFCB0. Same 16-byte
// lea-push-add-call shape as the rowed list/vector push_back twins. Identity:
// unlock lane, thiscall (reads ecx), callers at 0x002892CF and 0x0052D0F8;
// owner class unproven so honest Rva address name.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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
class ModuleData;
typedef _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > ModuleDataVec;
class Rva00289218 {
    char m_pad[20];
    ModuleDataVec m_vec;
public:
    void rva00289218(const ModuleData *p);
};
void Rva00289218::rva00289218(const ModuleData *p)
{
    m_vec.push_back(p);
}
