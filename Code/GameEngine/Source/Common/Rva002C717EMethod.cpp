// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva002C717E@Rva002A8AB1Record@@QAEXABVAsciiString@@H@Z 0x002C717E 24B
// Store an int under an AsciiString key in the +0x17C map via rowed map operator[].
#include <map>
#include "ascii_string.h"

struct TreeHintPayload001F8ACB
{
	int m_val;
	TreeHintPayload001F8ACB() : m_val(0) {}
	TreeHintPayload001F8ACB(const TreeHintPayload001F8ACB &o) : m_val(o.m_val) {}
};

typedef _STL::pair<const AsciiString, TreeHintPayload001F8ACB> TreeHintPair001F8ACB;
typedef _STL::map<AsciiString, TreeHintPayload001F8ACB, _STL::less<AsciiString>, _STL::allocator<TreeHintPair001F8ACB> > Map001F8ACB;

class Rva002A8AB1Record
{
public:
	void rva002C717E(const AsciiString &key, int value);
private:
	char m_pad[0x17C];
	Map001F8ACB m_map;
};

// bfme link decl-only begin
namespace _STL { template <> void _Construct<_STL::pair<AsciiString const,TreeHintPayload001F8ACB>,_STL::pair<AsciiString const,TreeHintPayload001F8ACB> >(_STL::pair<AsciiString const,TreeHintPayload001F8ACB> *,_STL::pair<AsciiString const,TreeHintPayload001F8ACB> const &); }
namespace _STL { template <> TreeHintPayload001F8ACB & map<AsciiString,TreeHintPayload001F8ACB,_STL::less<AsciiString>,_STL::allocator<_STL::pair<AsciiString const,TreeHintPayload001F8ACB> > >::operator[](AsciiString const &); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<AsciiString const,TreeHintPayload001F8ACB> > * _Rb_tree<AsciiString,_STL::pair<AsciiString const,TreeHintPayload001F8ACB>,_STL::_Select1st<_STL::pair<AsciiString const,TreeHintPayload001F8ACB> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<AsciiString const,TreeHintPayload001F8ACB> > >::_M_create_node(_STL::pair<AsciiString const,TreeHintPayload001F8ACB> const &); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<AsciiString const,TreeHintPayload001F8ACB> > * _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<AsciiString const,TreeHintPayload001F8ACB> > *,_STL::_Rb_tree_node<_STL::pair<AsciiString const,TreeHintPayload001F8ACB> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<AsciiString const,TreeHintPayload001F8ACB> > > >::allocate(unsigned int); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<AsciiString const,TreeHintPayload001F8ACB> > * allocator<_STL::_Rb_tree_node<_STL::pair<AsciiString const,TreeHintPayload001F8ACB> > >::allocate(unsigned int,void const *) const; }
namespace _STL { template <> _STL::pair<_STL::_Rb_tree_iterator<_STL::pair<AsciiString const,TreeHintPayload001F8ACB>,_STL::_Nonconst_traits<_STL::pair<AsciiString const,TreeHintPayload001F8ACB> > >,bool> _Rb_tree<AsciiString,_STL::pair<AsciiString const,TreeHintPayload001F8ACB>,_STL::_Select1st<_STL::pair<AsciiString const,TreeHintPayload001F8ACB> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<AsciiString const,TreeHintPayload001F8ACB> > >::insert_unique(_STL::pair<AsciiString const,TreeHintPayload001F8ACB> const &); }
// bfme link decl-only end
void Rva002A8AB1Record::rva002C717E(const AsciiString &key, int value)
{
	m_map[key].m_val = value;
}
