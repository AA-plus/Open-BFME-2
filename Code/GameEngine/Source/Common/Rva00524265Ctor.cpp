// cl: /O1 /G7 /arch:SSE /MD /EHsc /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// Native checklist constructor688 initializes the custom-render name list at18.
// This default vector<AsciiString> lifetime is a complete19-byte constructor
// and allocator-base relocation twin of ObjectCreationList; no unique-byte gain.
#include "ascii_string.h"
#include <vector>

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}
class Rva00524265 { public: Rva00524265(); ~Rva00524265(); private: _STL::vector<AsciiString> names; };
Rva00524265::Rva00524265() {}
