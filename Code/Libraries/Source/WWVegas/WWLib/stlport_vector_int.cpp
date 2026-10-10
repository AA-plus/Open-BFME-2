// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
}

// Only the rowed members are instantiated: instantiating the whole class
// also emitted this unit's copies of the constructor, _Vector_base
// constructor and operator=, which differ from retail's (0x00211E58,
// 0x0021C21B, from the game's /O1 units) and, being first in link order,
// captured every other unit's calls to them.
template _STL::vector<int, _STL::allocator<int> >::iterator _STL::vector<int, _STL::allocator<int> >::erase(iterator, iterator);
template void _STL::vector<int, _STL::allocator<int> >::clear();
template void _STL::vector<int, _STL::allocator<int> >::push_back(const int &);
template void _STL::vector<int, _STL::allocator<int> >::pop_back();
template void _STL::vector<int, _STL::allocator<int> >::_M_fill_insert(iterator, size_type, const int &);
