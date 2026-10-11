// cl: /Ob0

// LINK: the middle member's assignment is rowed as the STLport vector's
// operator= over Rva00332217Record (0x002E9E70); only that call is used here.
struct Rva00332217Record;
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	vector &operator=(const vector &other);

private:
	void *m_item;
};
}
typedef _STL::vector<Rva00332217Record, _STL::allocator<Rva00332217Record> > Rva002E9E70Mid;

class Rva002E17F0
{
	virtual void handle();
	char m_04;
	Rva002E9E70Mid m_08;

public:
	void operator=(const Rva002E17F0 &other);
};

void Rva002E17F0::operator=(const Rva002E17F0 &other)
{
	m_08 = other.m_08;
	m_04 = other.m_04;
}
