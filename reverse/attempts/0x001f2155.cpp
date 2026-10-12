// ?_M_insert_overflow@?$vector@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@IAEXPAPAVObject@@ABQAV3@ABU__true_type@2@I_N@Z
// partial score=0.8 date=2026-10-12
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// STLport vector<Object*>::_M_insert_overflow (__true_type) at 0x001F2155,
// called from the rowed vector<Object*>::push_back 0x001F211B.
// Evidence: 147B body grows/copies 4B records; rowed byte allocator 0x307F0,
// out-of-line __copy_trivial 0x179B0, folded vector dtor 0x7FAB3 and the
// (pos, value-ref, tag, count, at-end) five-argument shape with ret 0x14.
// Uses the full bfmealloc shim (not alloconly) so allocation and the trivial
// copies resolve out of line as retail shows.
#include <vector>

class Object;

// This TU must not emit its own vector<Object*> teardown copy: the call
// binds the folded rowed copy at 0x7FAB3.
namespace _STL {
template <> vector<Object *, allocator<Object *> >::~vector();
}

// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row).
// This unit-local overload keeps the inlined code and offers the link no
// second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

template void _STL::vector<Object *, _STL::allocator<Object *> >::_M_insert_overflow(
    Object **, Object * const &, const _STL::__true_type &, unsigned, bool);
