// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#define _STLP_BFME_TREE_NODE_BASE_O2  // emit retail's _Rb_tree_node_base::_S_minimum/_S_maximum (vendor/stlport/stl/_tree.h)
#include <algorithm>
#include <map>

struct Rva002D07F4Element { short words[1]; bool operator<(const Rva002D07F4Element&b)const { return words[0]<b.words[0]; } bool operator==(const Rva002D07F4Element&b)const {return words[0]==b.words[0];} };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree<Rva002D07F4Element, _STL::pair<Rva002D07F4Element const, int>, _STL::_Select1st<_STL::pair<Rva002D07F4Element const, int> >, _STL::less<Rva002D07F4Element>, _STL::allocator<_STL::pair<Rva002D07F4Element const, int> > > & _STL::_Rb_tree<Rva002D07F4Element, _STL::pair<Rva002D07F4Element const, int>, _STL::_Select1st<_STL::pair<Rva002D07F4Element const, int> >, _STL::less<Rva002D07F4Element>, _STL::allocator<_STL::pair<Rva002D07F4Element const, int> > >::operator=(_STL::_Rb_tree<Rva002D07F4Element, _STL::pair<Rva002D07F4Element const, int>, _STL::_Select1st<_STL::pair<Rva002D07F4Element const, int> >, _STL::less<Rva002D07F4Element>, _STL::allocator<_STL::pair<Rva002D07F4Element const, int> > > const &);

// The outer map operator= at retail 0x002D0B36 (18 bytes): forwards to the tree
// member instantiated above and returns this.
template _STL::map<Rva002D07F4Element, int, _STL::less<Rva002D07F4Element >, _STL::allocator<_STL::pair<const Rva002D07F4Element, int> > > &_STL::map<Rva002D07F4Element, int, _STL::less<Rva002D07F4Element >, _STL::allocator<_STL::pair<const Rva002D07F4Element, int> > >::operator=(const _STL::map<Rva002D07F4Element, int, _STL::less<Rva002D07F4Element >, _STL::allocator<_STL::pair<const Rva002D07F4Element, int> > > &);
