// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??1Rva002A8D49@@QAE@XZ @ 0x002A8E64 (18B). Frees vector start at +0x854 via
// rowed _free 0x00030830 if non-null. Same +0x854 as the ctor at 0x002A8D49
// (CombatChain[16] + scalars + vector<BfmeE16> + floats + Tuning[4]); other
// members need no cleanup (no dtors) so the dtor is only the vector teardown.
// Evidence: callers at 0x002A92BE plus unwinds; Free TU sole-caller note.
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

#include "../../../../Libraries/Include/Lib/BfmeE16.h"

class Rva002A8D49
{
public:
	~Rva002A8D49();
private:
	char m_pad[0x854];
	_STL::vector<BfmeE16> m_vec;
};

Rva002A8D49::~Rva002A8D49()
{
}
