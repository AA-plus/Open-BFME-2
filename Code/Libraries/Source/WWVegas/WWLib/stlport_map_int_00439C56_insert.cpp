// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?insert@?$map@HURva00439AAAMapped@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHURva00439AAAMapped@@@_STL@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHURva00439AAAMapped@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHURva00439AAAMapped@@@_STL@@@2@@2@U32@ABU?$pair@$$CBHURva00439AAAMapped@@@2@@Z @0x00439C56 29B map hint-insert forwards to tree insert_unique 0x00439B30.
// Evidence: rowed insert_unique 0x00439B30 in StlportIntMapInsertFamily.cpp; caller 0x00439C73 passes hidden+pos+pair with this=map; same 29B shape as 0x005592FB and 0x0021DB74.
#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

struct Rva00439AAAMapped { int a; };

typedef _STL::map<int, Rva00439AAAMapped, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00439AAAMapped> > > Map00439C56;

template Map00439C56::iterator Map00439C56::insert(Map00439C56::iterator, const Map00439C56::value_type &);
// bfme link decl-only begin
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,Rva00439AAAMapped> > * _Rb_tree<int,_STL::pair<int const,Rva00439AAAMapped>,_STL::_Select1st<_STL::pair<int const,Rva00439AAAMapped> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,Rva00439AAAMapped> > >::_M_create_node(_STL::pair<int const,Rva00439AAAMapped> const &); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,Rva00439AAAMapped> > * allocator<_STL::_Rb_tree_node<_STL::pair<int const,Rva00439AAAMapped> > >::allocate(unsigned int,void const *) const; }
// bfme link decl-only end
