// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Constructor layout inferred from complete retail copy constructors and callers.
#include <vector>
#include "ascii_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}

struct BfmeVectorRecord001B4A39 {
    AsciiString text0;
    _STL::vector<AsciiString> names0, names1, names2, names3, names4;
    unsigned int word40;
    AsciiString text1;
    BfmeVectorRecord001B4A39();
};

BfmeVectorRecord001B4A39::BfmeVectorRecord001B4A39()
    : text0(), names0(), names1(), names2(), names3(), names4(), text1()
{
    text0.clear();
    _STL::vector<AsciiString> *names = &names0;
    names->erase(names->begin(), names->end());
    names = &names1;
    names->erase(names->begin(), names->end());
    names = &names2;
    names->erase(names->begin(), names->end());
    names = &names3;
    names->erase(names->begin(), names->end());
    names = &names4;
    names->erase(names->begin(), names->end());
    word40 = 0;
    text1.clear();
}
