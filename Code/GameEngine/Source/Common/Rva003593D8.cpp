// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// stlport
// ?rva003593D8@Rva003593D8@@QAEII@Z 0x003593D8 16B; tree erase call and +0x24 this adjustment are retail evidence
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

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

struct Rva00358E26Record
{
	char word;
	bool operator<(const Rva00358E26Record &other) const { return word < other.word; }
	bool operator==(const Rva00358E26Record &other) const { return word == other.word; }
};

class Rva003593D8
{
public:
	unsigned int rva003593D8(int key);
private:
	char m_pad00[0x24];
	_STL::map<int, Rva00358E26Record> m_records;
};

unsigned int Rva003593D8::rva003593D8(int key)
{
	return m_records.erase(key);
}
