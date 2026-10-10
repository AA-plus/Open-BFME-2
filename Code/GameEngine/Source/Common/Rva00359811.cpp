// cl: /O1 /arch:SSE /G7 /MD
// stlport
// ?rva00359811@Rva00359811@@QAEIABURva003597C3Element@@_N@Z 0x00359811 27B; branch and set erase call are retail evidence
#include <set>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

struct Rva003597C3Element
{
	char bytes[8];
};

bool operator<(const Rva003597C3Element &left, const Rva003597C3Element &right);

class Rva00359811
{
public:
	unsigned int rva00359811(const Rva003597C3Element &key, bool useSecond);
private:
	char m_pad00[0x0c];
	_STL::set<Rva003597C3Element> m_first;
	_STL::set<Rva003597C3Element> m_second;
};

unsigned int Rva00359811::rva00359811(const Rva003597C3Element &key, bool useSecond)
{
	return (useSecond ? m_second : m_first).erase(key);
}
