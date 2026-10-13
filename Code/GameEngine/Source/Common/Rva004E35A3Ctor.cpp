// cl: /MD
// stlport
//
// ??0Rva004E35A3@@QAE@XZ @0x004E35A3 12B: opaque map-holder ctor.
// Calls the rowed map<int,void*> default ctor at 0x0033C432 (row in
// stlport_map_int_ptr_o1.cpp). No vtable store, no EH prologue, returns
// this (mov eax,esi). Callers at 0x003EEB1E and 0x004FB476. Owner
// identity unproven, honest Rva name. Prev 0x004E32F2 (Rva004E32F2Dtor.cpp
// /O1 /MD) and next 0x004E3733 (stlport pod vector bodies) share no TU,
// so new file beside them copying prev flags.
#include <map>
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_base<_STL::pair<int const,void *>,_STL::allocator<_STL::pair<int const,void *> > >::_Rb_tree_base(_STL::allocator<_STL::pair<int const,void *> > const &); }
namespace _STL { template <> _Rb_tree<int,_STL::pair<int const,void *>,_STL::_Select1st<_STL::pair<int const,void *> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,void *> > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree_base<_STL::pair<int const,void *>,_STL::allocator<_STL::pair<int const,void *> > >::~_Rb_tree_base(); }
namespace _STL { template <> void _Rb_tree<int,_STL::pair<int const,void *>,_STL::_Select1st<_STL::pair<int const,void *> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,void *> > >::_M_erase(_STL::_Rb_tree_node<_STL::pair<int const,void *> > *); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,void *> > * allocator<_STL::_Rb_tree_node<_STL::pair<int const,void *> > >::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<int const,void *> > *,_STL::_Rb_tree_node<_STL::pair<int const,void *> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<int const,void *> > > >::deallocate(_STL::_Rb_tree_node<_STL::pair<int const,void *> > *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_Rb_tree_node<_STL::pair<int const,void *> > >::deallocate(_STL::_Rb_tree_node<_STL::pair<int const,void *> > *,unsigned int) const; }
// bfme link decl-only end

class Rva004E35A3
{
public:
	Rva004E35A3();

private:
	_STL::map<int, void *> m_map;
};

Rva004E35A3::Rva004E35A3()
{
}
