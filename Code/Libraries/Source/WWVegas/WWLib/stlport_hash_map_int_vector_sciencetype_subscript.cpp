// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// hash_map<int, vector<ScienceType>>::operator[] @0x0041EB1A 179B.
// Retail finds the key via hashtable find (rowed dup 0x00148B27), inserts a
// default pair on miss via _M_insert 0x0041EAD1 and returns the mapped vector.
// Caller 0x0041EC73 pushes key+value and reuses the value push for the
// following vector assign 0x0021C21B; callee itself takes one arg (ret 4).
// Evidence: STLport _hash_map.h operator[] shape, prev/next rows in this
// family, callers at 0x0041ECEF/0x0041ED6A.

#include <hash_map>
#include <vector>
// Suppress this TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
}

#include <cstddef>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}

enum ScienceType
{
	SCIENCE_NONE = 0
};

template _STL::vector<ScienceType> &_STL::hash_map<int, _STL::vector<ScienceType>, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, _STL::vector<ScienceType> > > >::operator[](const int &);
