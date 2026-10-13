// cl: /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_fill_insert@?$vector@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAEXPAUBfmeE16@@IABU3@@Z @0x000B0395 227B. vector<BfmeE16> fill-insert POD false_type path.
// Evidence: rowed BfmeE16 helpers 0x000ADE67 0x005B2B1E 0x004218D5 0x000ADE8D plus overflow 0x005B3970; /Ob0 keeps copy-backward wrapper and /G7 fixes registers vs o1 sibling.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "../../../Include/Lib/BfmeE16.h"
// Suppress this TU's non-retail BfmeE16 proxy deallocate copy (family2-LK3 row 34):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<BfmeE16*, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16*, size_t);
}
template void _STL::vector<BfmeE16>::_M_fill_insert(
	BfmeE16 *, unsigned int, const BfmeE16 &);
