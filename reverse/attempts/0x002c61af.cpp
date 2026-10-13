// ?rva002C61AF@Rva002C61AF@@QAEXXZ
// partial score=0.99 date=2026-10-13
// ?rva002C61AF@Rva002C61AF@@QAEXXZ
// partial score=0.97 date=2026-10-04
// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva002C61AF@Rva002C61AF@@QAEXXZ @0x002C61AF 133B
// Evidence: unlock lane prev Rva002C5FE8Search next DispDword setter caller
// 0x002C6354 callees Rva00506909 dtor plus Rva0050542B dtor plus pair dtor
// plus operator delete plus vector voidptr erase globals none offsets
// 0x10/0x0c/0x1c/0x20/0x24. Identity: honest-address thiscall method no args
// returning void.
#include <vector>

class Rva00506909
{
public:
	~Rva00506909();
};

class Rva0050542B
{
public:
	~Rva0050542B();
};

class Rva002C61AFThird
{
public:
	~Rva002C61AFThird();
};

class Rva002C61AF
{
public:
	void rva002C61AF();

private:
	char m_pad0[0x0C];
	Rva0050542B *m_0C;
	Rva00506909 *m_10;
	char m_pad14[0x08];
	Rva002C61AFThird *m_1C;
	void **m_vecBegin;
	void **m_vecEnd;
	void **m_vecEndStorage;
};

// ?rva002C61AF@Rva002C61AF@@QAEXXZ present-unmatched
void Rva002C61AF::rva002C61AF()
{
	if (m_10) { delete m_10; m_10 = 0; }
	if (m_0C) { delete m_0C; m_0C = 0; }
	if (m_1C != 0) { delete m_1C; m_1C = 0; }
	void ***vec = (void ***)&m_vecBegin;
	if (vec[0] != vec[1]) {
		void **finish = m_vecEnd;
		for (void **cur = m_vecBegin; cur != finish; ++cur) {
			if (*cur)
				::operator delete(*cur);
		}
		((_STL::vector<void *, _STL::allocator<void *> > *)vec)->erase(vec[0], vec[1]);
	}
}
