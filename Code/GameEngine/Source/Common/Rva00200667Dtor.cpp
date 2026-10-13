// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// stlport
// ??1Rva00200667@@QAE@XZ, retail 0x00200667, 5 bytes. Thunk jmp to List_base dtor 0x004EC395.
// Evidence: retail 5B jmp to 0x004EC395; vector-dtor at 0x00320058 pushes 0x00200667 as array element dtor; Rva00283002Clear calls it; deleting-dtor wrapper at 0x002821B3.
namespace _STL
{
	template <class T> class allocator;
	template <class T, class A> class _List_base
	{
	public:
		~_List_base();
	private:
		void *m_header;
	};
}

class Rva00200667 : public _STL::_List_base<int, _STL::allocator<int> >
{
public:
	~Rva00200667();
};

// Select-any like the OpenContainModuleDataConstructor.cpp copy (this retail
// body comes first in link order, so it is the copy the link keeps); the anchor
// keeps the body emitted.
inline Rva00200667::~Rva00200667()
{
}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitRva00200667Dtor@@YAXPAVRva00200667@@@Z absent-from-retail
void bfmeEmitRva00200667Dtor(Rva00200667 *p)
{
	p->Rva00200667::~Rva00200667();
}
