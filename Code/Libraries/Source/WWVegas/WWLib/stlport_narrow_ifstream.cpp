// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <fstream>

// Native allocation owner 0x00013F10 (189 bytes) supplies this helper.
// BFME 1 FilebufInstantiations at f98983a7d3 likewise defers allocation.
// The generic emitted copy differs from the complete retail body.
namespace _STL {
template <> bool basic_filebuf<char, char_traits<char> >::_M_allocate_buffers(char *, streamsize);
}


// The exact default constructor is owned by the verified dedicated unit.
// This whole-class instantiation emitted a non-retail copy; defer to that owner.
template <>
_STL::basic_ifstream<char, _STL::char_traits<char> >::basic_ifstream();

// Filename and descriptor constructors likewise defer to their exact owners.
template <>
_STL::basic_ifstream<char, _STL::char_traits<char> >::basic_ifstream(int, _STL::ios_base::openmode);
template <>
_STL::basic_ifstream<char, _STL::char_traits<char> >::basic_ifstream(const char *, _STL::ios_base::openmode, long);

#include <cstddef>
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
template class _STL::basic_ifstream<char, _STL::char_traits<char> >;
