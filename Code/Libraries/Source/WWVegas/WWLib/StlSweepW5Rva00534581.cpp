// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#define _STLP_BFME_TREE_NODE_BASE_O2  // emit retail's _Rb_tree_node_base::_S_minimum/_S_maximum (vendor/stlport/stl/_tree.h)
#include <algorithm>
#include <map>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

struct Rva00534581Element { short words[1]; bool operator<(const Rva00534581Element&b)const { return words[0]<b.words[0]; } bool operator==(const Rva00534581Element&b)const {return words[0]==b.words[0];} };
template class _STL::map<Rva00534581Element,int>;
