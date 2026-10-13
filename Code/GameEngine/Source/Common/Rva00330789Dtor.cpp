// Rva003306B0 destructor, retail 0x00330789 (105B EH), the WB unnamed slot
// after the rowed clear 0x0033073C. It removes every CreateAHeroData in the
// vector at +0x10 through the rowed remove 0x003306B0, notifies the listener
// list at +0 through the rowed forEach 0x0033066D with the virtual listener
// callback (vcall thunk 0x005CB265), then lets the two member destructors free
// the vector storage and the list's pointer array. The compiler's
// member-destruction states (vector alive = 1, list only = 0) come out of the
// member declarations, so the body itself carries no explicit state handling.
// The method name is address-derived.
//
// The loop condition reads the vector's first word through a volatile pointer
// into a named local: _ReadWriteBarrier() also forces the reload but leaves the
// this-setup mov ecx,esi in the loop body, and a bare reload is CSE'd across the
// remove call. The named volatile local yields retail's begin load into eax,
// compare against end, and the shared ecx=esi in the latch for the forEach call.
// stlport
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <vector>
#undef free

class Rva0053FA0A {
public:
	void rva0053FA32();
};

class CreateAHeroData : public Rva0053FA0A {
};

class Rva0033066DListener
{
public:
	virtual void notify(void *);
};

class Rva0033066DList
{
public:
	void forEach(void (Rva0033066DListener::*notify)(void *), void *arg);
	~Rva0033066DList()
	{
		if (m_begin)
			_STL::free(m_begin);
	}

private:
	Rva0033066DListener **m_begin;		// +0x00
	Rva0033066DListener **m_end;		// +0x04
	Rva0033066DListener **m_capacity;	// +0x08
	unsigned int m_index;			// +0x0C
};

class Rva003306B0
{
public:
	void rva003306B0(CreateAHeroData *key);	// 0x003306B0
	~Rva003306B0();				// 0x00330789

private:
	Rva0033066DList m_list;			// +0x00
	_STL::vector<void *> m_vec;		// +0x10
};

Rva003306B0::~Rva003306B0()
{
	for (;;) {
		void **begin = *(void **volatile *)&m_vec;
		if (begin == (void **)m_vec.end())
			break;
		rva003306B0((CreateAHeroData *)*m_vec.begin());
	}
	m_list.forEach(&Rva0033066DListener::notify, this);
}
