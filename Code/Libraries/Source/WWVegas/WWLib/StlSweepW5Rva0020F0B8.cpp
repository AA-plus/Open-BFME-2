// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <hash_map>
#include <cstddef>

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

struct Rva0020F0B8Element { char bytes[1]; Rva0020F0B8Element();Rva0020F0B8Element(const Rva0020F0B8Element&);~Rva0020F0B8Element();Rva0020F0B8Element&operator=(const Rva0020F0B8Element&); struct Hash { unsigned state[1]; unsigned operator()(const Rva0020F0B8Element&) const; }; struct Equal { unsigned state[1]; bool operator()(const Rva0020F0B8Element&,const Rva0020F0B8Element&)const; }; struct Compare {unsigned state[1]; bool operator()(const Rva0020F0B8Element&,const Rva0020F0B8Element&)const; }; bool operator==(const Rva0020F0B8Element&) const; };
template class _STL::hash_map<Rva0020F0B8Element,int,Rva0020F0B8Element::Hash,Rva0020F0B8Element::Equal>;
