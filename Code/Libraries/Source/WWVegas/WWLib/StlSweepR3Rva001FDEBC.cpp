// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}



struct Rva001FDEBCRecord {Rva001FDEBCRecord();Rva001FDEBCRecord(const Rva001FDEBCRecord&);~Rva001FDEBCRecord();Rva001FDEBCRecord&operator=(const Rva001FDEBCRecord&);char bytes[1];bool operator<(const Rva001FDEBCRecord&)const;bool operator==(const Rva001FDEBCRecord&)const;};
namespace _STL {template class hashtable<pair<const int,Rva001FDEBCRecord>,int,hash<int>,_Select1st<pair<const int,Rva001FDEBCRecord> >,equal_to<int>,allocator<pair<const int,Rva001FDEBCRecord> > >;}
