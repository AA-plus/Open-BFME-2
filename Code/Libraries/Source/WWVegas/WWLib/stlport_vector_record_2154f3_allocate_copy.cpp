// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 16-byte BfmeVectorRecord0002154F3 vector allocation/copy helper at RVA 0x215614.
// Uses the shared ascii_string.h so the emitted ??_GAsciiString copy calls
// releaseBuffer like the kept WOLBuddyOverlay copy. operator= is declared only
// so this TU does not emit the shallow implicit copy (kept deep copy lives in
// StringVectorRecordCopyBFME2.cpp).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "ascii_string.h"
#include <vector>
struct BfmeVectorRecord0002154F3 {
    AsciiString text;
    _STL::vector<AsciiString> names;
    BfmeVectorRecord0002154F3();
    BfmeVectorRecord0002154F3(const BfmeVectorRecord0002154F3 &);
    BfmeVectorRecord0002154F3 &operator=(const BfmeVectorRecord0002154F3 &);
};
namespace _STL {
template <> void _Construct<BfmeVectorRecord0002154F3, BfmeVectorRecord0002154F3>(BfmeVectorRecord0002154F3 *, const BfmeVectorRecord0002154F3 &);
}
template class _STL::vector<BfmeVectorRecord0002154F3, _STL::allocator<BfmeVectorRecord0002154F3> >;
