// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <vector>
#include <cstddef>
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

struct Rva002CFBAEElement { _STL::vector<char> values[3]; bool operator==(const Rva002CFBAEElement&) const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy_aux<Rva002CFBAEElement *>(Rva002CFBAEElement *, Rva002CFBAEElement *, _STL::__false_type const &);
