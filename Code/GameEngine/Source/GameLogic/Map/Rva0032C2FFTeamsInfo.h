// TU-local STL view for Rva0032C2FFTeamsInfo.cpp: the receiver's list member
// must call the rowed out-of-line push_back
// (?push_back@?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@
// QAEXABVAsciiString@@@Z at 0x001FD868), so the member stays a declaration.
namespace _STL
{
template <class T> class allocator;

template <class T, class A> class list
{
public:
	struct node
	{
		node *next;
		node *previous;
		T value;
	};

	void push_back(const T &value);
	node *m_head;
};
}
