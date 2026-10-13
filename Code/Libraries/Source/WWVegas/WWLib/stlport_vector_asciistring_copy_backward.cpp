// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// _STL::__copy_backward worker for AsciiString at 0x000B4460, 47 bytes.
// Backward twin of the rowed forward __copy at 0x000B4431 (dup_000b4431):
// count = (last-first)>>2, then decrement last/result and copy via
// ?set@?$StringBase@D@@QAEXABV1@@Z. Caller wrapper at 0x000B6631.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
// The exact assignment specialization is provided by StlportAsciiStringVectorAssign.cpp.
// Keep this consumer on that verified body rather than instantiate the stock copy.
#include <vector>
#include "ascii_string.h"
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> > &
vector<AsciiString, allocator<AsciiString> >::operator=(const vector<AsciiString, allocator<AsciiString> > &);
}

#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void vector<AsciiString,_STL::allocator<AsciiString> >::_M_clear(); }
// bfme link decl-only end

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> COMDAT copies, so the calls bind the kept rowed copies.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> void vector<AsciiString, allocator<AsciiString> >::reserve(size_t);
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString*, AsciiString*);
template <> void vector<AsciiString, allocator<AsciiString> >::_M_fill_insert(AsciiString*, size_t, const AsciiString&);
}

template class _STL::vector<AsciiString, _STL::allocator<AsciiString> >;
