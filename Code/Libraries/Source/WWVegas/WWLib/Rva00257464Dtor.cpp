// cl: /MD
// ??1Rva00257464@@QAE@XZ @0x00257464 5B
// Novtable empty dtor tail-jumping to the pinned base dtor at 0x002572D7.
// Evidence: 5B jmp; callers are Unwind funclets; neighbours are record/blog.
struct Rva002572D7Member
{
public:
	~Rva002572D7Member();
};
struct __declspec(novtable) Rva00257464 : public Rva002572D7Member
{
	~Rva00257464();
};
// Select-any like the OpenContainModuleDataConstructor.cpp copy (this retail
// body comes first in link order, so it is the copy the link keeps); the anchor
// keeps the body emitted.
inline Rva00257464::~Rva00257464()
{
}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitRva00257464Dtor@@YAXPAVRva00257464@@@Z absent-from-retail
void bfmeEmitRva00257464Dtor(Rva00257464 *p)
{
	p->Rva00257464::~Rva00257464();
}
