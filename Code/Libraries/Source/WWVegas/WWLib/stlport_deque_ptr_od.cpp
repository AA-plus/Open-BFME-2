// cl: /Od /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// A vendored instantiation unit. It exists so the linker-selected bodies of
// this container appear as COMDATs that build/objplace.py can place against
// unlanded functions; the suffix says which optimisation level, because for
// these containers different bodies survive the link from different units.
#include <deque>
// bfme link decl-only begin
namespace _STL { template <> void _Construct<void *, void *>(void **, void *const &); }
namespace _STL { template <> void _Deque_iterator_base<void *>::_M_advance(int); }
namespace _STL { template <> void _Deque_iterator_base<void *>::_M_increment(); }
namespace _STL { template <> void deque<void *, allocator<void *> >::_M_pop_front_aux(); }
namespace _STL { template <> int _Deque_iterator_base<void *>::_M_subtract(_Deque_iterator_base<void *> const &) const; }
namespace _STL { template <> void deque<void *, allocator<void *> >::clear(); }
namespace _STL { template <> void deque<void *, allocator<void *> >::pop_back(); }
namespace _STL { template <> void deque<void *, allocator<void *> >::pop_front(); }
// bfme link decl-only end
template class _STL::deque<void *, _STL::allocator<void *> >;
