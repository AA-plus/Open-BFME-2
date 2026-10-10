// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>
#include <string>
#include <utility>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

struct Rva002CEFAAElement { char bytes[1]; Rva002CEFAAElement();Rva002CEFAAElement(const Rva002CEFAAElement&);~Rva002CEFAAElement();Rva002CEFAAElement& operator=(const Rva002CEFAAElement&); };
template class _STL::map<_STL::pair<int,int>,Rva002CEFAAElement>;
