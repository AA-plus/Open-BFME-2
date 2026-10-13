// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Drawable element identity is proven by CommandTranslator::translateGameMessage
// selected-drawable list copy and AIUpdateInterface voice-response list operations.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// TU-local overload avoids exporting an unrelated max instantiation.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <list>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}



class Drawable;


// Instantiate the recovered member; retain only its required template dependencies.
template void _STL::list<Drawable *, _STL::allocator<Drawable *> >::_M_insert_dispatch<_STL::_List_iterator<Drawable *, _STL::_Const_traits<Drawable *> > >(_STL::_List_iterator<Drawable *, _STL::_Nonconst_traits<Drawable *> >, _STL::_List_iterator<Drawable *, _STL::_Const_traits<Drawable *> >, _STL::_List_iterator<Drawable *, _STL::_Const_traits<Drawable *> >, _STL::__false_type const &);
