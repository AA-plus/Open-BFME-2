// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// The remaining opaque pair-keyed record tree: _M_insert 2073D7/148B and
// insert_unique 207A9B/151B. Its 12-byte value extent is carried from the
// separately matched _M_create_node. Application identity remains unknown.
// The counter and flag trees formerly guessed as sets here are now owned
// by ScriptEngineRva0020881A.cpp as native map instantiations.
#define _STLP_NO_EXCEPTIONS 1
#include <set>
class AsciiString { void *m_data; public: AsciiString(const AsciiString &); ~AsciiString(); };
bool operator<(const _STL::pair<AsciiString, AsciiString> &, const _STL::pair<AsciiString, AsciiString> &);
struct BfmeStringRecord002049D6 { _STL::pair<AsciiString, AsciiString> key; char rest[4]; BfmeStringRecord002049D6(const BfmeStringRecord002049D6 &); ~BfmeStringRecord002049D6(); };
inline bool operator<(const BfmeStringRecord002049D6 &a, const BfmeStringRecord002049D6 &b) { return a.key < b.key; }
#define SET_TREE(T) _STL::_Rb_tree<T, T, _STL::_Identity<T>, _STL::less<T>, _STL::allocator<T> >
typedef SET_TREE(BfmeStringRecord002049D6) TreeC;
template <> TreeC::_Link_type TreeC::_M_create_node(const BfmeStringRecord002049D6 &);
template TreeC::iterator TreeC::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const BfmeStringRecord002049D6 &, _STL::_Rb_tree_node_base *);

// /D_BFME_RETAIL_TREE_INSERT_LAYOUT selects the verified 151B layout.
template _STL::pair<TreeC::iterator, bool> TreeC::insert_unique(const BfmeStringRecord002049D6 &);
