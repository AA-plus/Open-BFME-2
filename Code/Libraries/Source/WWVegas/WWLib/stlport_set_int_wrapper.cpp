// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva000BCA55@Rva000BCA55@@QAEXH@Z retail 0x000BCA55 28B
// Set-insert discard wrapper: set<int> at +0x9c via rowed insert 0x000BC15D,
// pair return discarded via stack temp. No callers; leaf.
// Evidence: callee 0x000BC15D plus prev row 0x000BC834 in same page.
#include <set>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

struct Rva000BCA55
{
	void rva000BCA55(int x);

	char m_pad[0x9c];
	_STL::set<int> m_set;
};

void Rva000BCA55::rva000BCA55(int x)
{
	m_set.insert(x);
}
