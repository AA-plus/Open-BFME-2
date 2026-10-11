// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHsc /MD /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
}

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}



struct Rva002A3FAFRecord { Rva002A3FAFRecord(); Rva002A3FAFRecord(const Rva002A3FAFRecord&); ~Rva002A3FAFRecord(); Rva002A3FAFRecord&operator=(const Rva002A3FAFRecord&); char bytes[52]; bool operator==(const Rva002A3FAFRecord&)const; bool operator<(const Rva002A3FAFRecord&)const; };


// This caller's native REL32 already names the kept provider at 0x00330E5D.
// Compatible calling convention and argument/return ABI; binding is address-proven.
#pragma comment(linker, "/alternatename:??0Rva002A3FAFRecord@@QAE@XZ=??0RadiusDecalTemplate@@QAE@XZ")

// This caller's native REL32 already names the kept provider at 0x000B6CF1.
// Compatible calling convention and argument/return ABI; binding is address-proven.
#pragma comment(linker, "/alternatename:??1Rva002A3FAFRecord@@QAE@XZ=??1BfmeStringRecord000B94D2@@QAE@XZ")

// Instantiate the recovered member; retain only its required template dependencies.
template Rva002A3FAFRecord & _STL::hash_map<int, Rva002A3FAFRecord, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva002A3FAFRecord> > >::operator[](int const &);
