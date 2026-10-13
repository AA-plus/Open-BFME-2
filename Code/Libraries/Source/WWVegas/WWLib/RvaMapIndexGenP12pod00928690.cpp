// cl: /O2 /G7 /Ireference/shims/bfmealloc /D_CRTIMP= /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Retail 0x00928690 calls the Gen_p12pod lower-bound helper at 0x00927680,
// inserts through the tree helper at 0x009282C0, and returns the mapped field
// at node offset 0x1C.  Those calls identify map<Gen_p12pod, int>::operator[].
// The cached fields and negated less-than tests preserve the retail branch
// order when MSVC 7.1 inlines the three-field key comparison.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}

struct Gen_p12pod
{
	int a[3];
};

inline bool compare_tail(const Gen_p12pod &a, const Gen_p12pod &b)
{
	const int a1 = a.a[1];
	return b.a[1] > a1
		|| (!(b.a[1] < a1) && a.a[2] < b.a[2]);
}

inline bool operator<(const Gen_p12pod &a, const Gen_p12pod &b)
{
	const int a0 = a.a[0];
	return b.a[0] > a0 || (!(b.a[0] < a0) && compare_tail(a, b));
}

typedef _STL::map<Gen_p12pod, int, _STL::less<Gen_p12pod>,
	_STL::allocator<_STL::pair<const Gen_p12pod, int> > > Rva00928690Map;

template int &Rva00928690Map::operator[](const Gen_p12pod &);

// Native GetEdges0016E450 calls this same established three-int key map.
// Emit its real constructor and trivial tree teardown so fold admission can
// compare every whole body, relocation, recursive erase and associative EH
// graph against all existing owners at0016DE80/0016CB50/0016DAA0. These are
// genuine template instantiations, not newly named standalone wrappers.
// The already matched operator[]0016E330 remains byte-exact at /O2 /G7.
typedef _STL::pair<const Gen_p12pod, int> Rva00928690Pair;
typedef _STL::_Rb_tree<Gen_p12pod, Rva00928690Pair,
    _STL::_Select1st<Rva00928690Pair>, _STL::less<Gen_p12pod>,
    _STL::allocator<Rva00928690Pair> > Rva00928690Tree;
template Rva00928690Map::map();
template void Rva00928690Tree::_M_erase(Rva00928690Tree::_Link_type);
template Rva00928690Tree::~_Rb_tree();

#include <hash_map>
typedef _STL::pair<int, int> Rva00928590Key;
struct Rva00928590Hash { unsigned operator()(const Rva00928590Key &) const; };
struct Rva00928590Eq { bool operator()(const Rva00928590Key &, const Rva00928590Key &) const; };
typedef _STL::pair<const Rva00928590Key, int> Rva00928590Value;
typedef _STL::hashtable<Rva00928590Value, Rva00928590Key, Rva00928590Hash,
    _STL::_Select1st<Rva00928590Value>, Rva00928590Eq,
    _STL::allocator<Rva00928590Value> > Rva00928590Table;
template void Rva00928590Table::clear();
