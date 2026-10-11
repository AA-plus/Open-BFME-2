// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

struct Rva00054EBEElement { char bytes[1]; bool operator<(const Rva00054EBEElement&)const; bool operator==(const Rva00054EBEElement&)const; };
namespace _STL {template<> struct hash<Rva00054EBEElement> { unsigned operator()(const Rva00054EBEElement&) const; };}

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Ht_iterator<_STL::pair<int const, Rva00054EBEElement>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00054EBEElement> >, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva00054EBEElement> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva00054EBEElement> > > _STL::hashtable<_STL::pair<int const, Rva00054EBEElement>, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva00054EBEElement> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva00054EBEElement> > >::find<int>(int const &);
