// cl: /O2 /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport

#include <hash_map>
// bfme link decl-only begin
namespace _STL { template <> void ** __uninitialized_fill_n<void **, unsigned int, void *>(void **, unsigned int, void *const &, __true_type const &); }
namespace _STL { template <> hash_map<int, int, hash<int>, equal_to<int>, allocator<pair<int const, int> > >::hash_map(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> hashtable<pair<int const, int>, int, hash<int>, _Select1st<pair<int const, int> >, equal_to<int>, allocator<pair<int const, int> > >::~hashtable(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
// bfme link decl-only end

namespace _STL
{
template <>
void swap<_STLP_alloc_proxy<void**, void*, allocator<void*> > >(
        _STLP_alloc_proxy<void**, void*, allocator<void*> >& a,
        _STLP_alloc_proxy<void**, void*, allocator<void*> >& b);

template <>
__declspec(dllimport) __forceinline
vector<void*, allocator<void*> >::iterator
vector<void*, allocator<void*> >::begin()
{
    return this->_M_start;
}

template <>
__declspec(dllimport) __forceinline
vector<void*, allocator<void*> >::iterator
vector<void*, allocator<void*> >::end()
{
    return this->_M_finish;
}

template <>
__declspec(dllimport) __forceinline
vector<void*, allocator<void*> >::size_type
vector<void*, allocator<void*> >::size() const
{
    return vector<void*, allocator<void*> >::size_type(
            this->_M_finish - this->_M_start);
}

template <>
__declspec(dllimport) __forceinline
vector<void*, allocator<void*> >::reference
vector<void*, allocator<void*> >::operator[](
        vector<void*, allocator<void*> >::size_type n)
{
    return *(begin() + n);
}

template <>
vector<void*, allocator<void*> >::allocator_type
vector<void*, allocator<void*> >::get_allocator() const;

template <>
__declspec(dllimport) __forceinline
vector<void*, allocator<void*> >::size_type
vector<void*, allocator<void*> >::capacity() const
{
    return vector<void*, allocator<void*> >::size_type(
            this->_M_end_of_storage._M_data - this->_M_start);
}

template <>
__declspec(dllimport) __forceinline
void vector<void*, allocator<void*> >::swap(
        vector<void*, allocator<void*> >& x)
{
    _STLP_STD::swap(this->_M_start, x._M_start);
    _STLP_STD::swap(this->_M_finish, x._M_finish);
    _STLP_STD::swap(this->_M_end_of_storage, x._M_end_of_storage);
}

template <>
__declspec(dllimport) __forceinline
void vector<void*, allocator<void*> >::insert(
        vector<void*, allocator<void*> >::iterator pos,
        vector<void*, allocator<void*> >::size_type n,
        const vector<void*, allocator<void*> >::value_type& x)
{
    _M_fill_insert(pos, n, x);
}

template <>
void** fill_n<void**, unsigned int, void*>(
        void** first, unsigned int n, void* const& value);

template <>
void _STLP_CALL advance<const unsigned int*, int>(
        const unsigned int*& i, int n);

template <>
const unsigned int* __lower_bound<const unsigned int*, unsigned int,
        less<unsigned int>, int>(const unsigned int* first,
        const unsigned int* last, const unsigned int& value,
        less<unsigned int> comp, int*);
}

template class _STL::less<unsigned int>;
template class _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??$_Construct@Uvalue_type@KeyToBucketMap@NameKeyGenerator@@@_STL@@YAXPAUvalue_type@KeyToBucketMap@NameKeyGenerator@@ABU123@@Z=??$_Construct@U?$pair@$$CBHH@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBHH@0@ABU10@@Z")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??$_Construct@UGen_t_008fb570_p8pod@@U1@@_STL@@YAXPAUGen_t_008fb570_p8pod@@ABU1@@Z=??$_Construct@U?$pair@$$CBHH@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBHH@0@ABU10@@Z")
#pragma comment(linker, "/alternatename:?Rva00142E20@@YAXXZ=??0?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@ABV?$allocator@PAX@1@@Z")
