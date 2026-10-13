// cl: /O1 /DNDEBUG /MD /EHsc
//
// 0x004FF997 (31B): the rowed map<int,int> _M_find<int> 0x00388F63 on the
// +0x1C tree with the int arg by address; when the result equals the +0x1C
// header return 0 else the +0x14 field. Identities unproven.

class Rva004FF997Owner;

namespace _STL {
template <class T1, class T2> struct pair { T1 first; T2 second; };
template <class P> struct _Select1st {};
template <class T> struct less {};
template <class T> class allocator {};
template <class V> struct _Rb_tree_node;
template <class K, class V, class KOV, class Cmp, class Alloc> class _Rb_tree
{
	friend class ::Rva004FF997Owner;
	typedef _Rb_tree_node<V> *_Link_type;
private:
	template <class KT> _Link_type _M_find(const KT &) const;
};
}

typedef _STL::pair<const int, int> IntIntPair;
typedef _STL::_Rb_tree<int, IntIntPair, _STL::_Select1st<IntIntPair>, _STL::less<int>, _STL::allocator<IntIntPair> > MapIntIntTree;

class Rva004FF997Owner
{
public:
	int rva004FF997(int key);

private:
	char m_pad[0x1C];	// +0x00..0x1B
	void *m_1C_head;	// +0x1C header/end for the find compare
};

int Rva004FF997Owner::rva004FF997(int key)
{
	void *node = ((MapIntIntTree *)&m_1C_head)->_M_find(key);
	if (node == m_1C_head)
		return 0;
	return *(int *)((char *)node + 0x14);
}
