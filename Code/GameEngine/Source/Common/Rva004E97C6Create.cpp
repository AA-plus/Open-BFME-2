// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x004E97C6 (93B, EH, RET 0x10): news a Rva00596B05 (0x3C bytes, the
// AIMoneyLender-labelled object whose rowed constructor 0x00596BF3 takes two
// pointers and two ints), appends it to the owner's pointer vector at +0x18
// through the rowed push_back 0x004DFCB0 (named for another pointer element;
// the storage is the same) and returns it. The push_back takes its element
// by reference, so retail spills the new pointer into the dead fourth
// argument slot. The owner and the element's role are unknown (address names).
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	void push_back(const T &);
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};
}

struct LivingWorldArmy;

class Rva00596B05
{
public:
	Rva00596B05(void *a1, void *a2, int a3, int a4);
	virtual ~Rva00596B05();
private:
	char m_pad[0x3C - 4];
};

class Rva004E97C6
{
public:
	Rva00596B05 *rva004E97C6(void *a1, void *a2, int a3, int a4);
private:
	char m_pad00[0x18];
	_STL::vector<LivingWorldArmy *, _STL::allocator<LivingWorldArmy *> > m_members;	// +0x18
};

Rva00596B05 *Rva004E97C6::rva004E97C6(void *a1, void *a2, int a3, int a4)
{
	Rva00596B05 *member = new Rva00596B05(a1, a2, a3, a4);
	m_members.push_back(reinterpret_cast<LivingWorldArmy *>(member));
	return member;
}
