// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0?$_Rb_tree@HU?$pair@$$CBHPAX@_STL@@U?$_Select1st@U?$pair@$$CBHPAX@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@QAE@ABV01@@Z,
// retail 0x001FDA0B, 165 bytes. Chain lane: calls the just-landed
// Rva001FD751 copy via the HPAX _M_copy fold pin, the rowed HPAX
// _Rb_tree_base ctor at 0x001F0534, and the rowed vector get_allocator
// fold at 0x0021983A. Same flags as the sibling map<int,void*> o1 unit.
#define _STLP_BFME_TREE_NODE_BASE_O2  // emit retail's _Rb_tree_node_base::_S_minimum/_S_maximum (vendor/stlport/stl/_tree.h)
#include <map>

typedef _STL::_Rb_tree<int, _STL::pair<const int, void *>, _STL::_Select1st<_STL::pair<const int, void *> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > IntPtrCopyTree;
template IntPtrCopyTree::_Rb_tree(const IntPtrCopyTree &);
