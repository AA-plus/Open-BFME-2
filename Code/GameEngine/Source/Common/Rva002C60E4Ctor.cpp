// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva002C60E4@@QAE@PAX_N@Z @0x002C60E4 203B
// Evidence: unlock lane prev Rva002C5FE8Search next DispDword setter caller
// 0x002C6EE0 callees Rva00506B1B ctor plus Vector_base BfmeE16 plus operator
// new plus AITargetChooser/AITacticsGenerator/Rva00506A34 ctors vtable g_00C004E4
// offsets 0x08/0x0c/0x10/0x14/0x18/0x1c/0x20 ret 8 two args voidptr plus bool.
// Identity: honest-address thiscall ctor with two args.
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

class Rva00506B1B
{
public:
	Rva00506B1B();
	// Declared only: retail's unwind call lands on the rowed body at 0x00506B28.
	virtual ~Rva00506B1B();
	virtual void v1();
	bool m_04;
};

class AITargetChooser
{
public:
	AITargetChooser(void *p);
	~AITargetChooser();
	char m_pad[0x20];
};

class AITacticsGenerator
{
public:
	AITacticsGenerator(void *p);
	char m_pad[0x64];
};

class Rva00506A34
{
public:
	Rva00506A34(void *p);
	char m_pad[0x10];
};

// Rowed non-virtual destructors reached through views: 0x00505BBA (the generator
// member at +0x10) and the ICF-folded 15-byte pair destructor 0x000796BC (+0x1C).
class Rva00506909
{
public:
	~Rva00506909();
};

class Rva000C24EA
{
public:
	~Rva000C24EA();
};

class Rva002C60E4 : public Rva00506B1B
{
public:
	Rva002C60E4(void *arg0, bool arg1);
	void rva002C61AF();
	virtual ~Rva002C60E4() {}

private:
	void *m_08;
	AITargetChooser *m_0C;
	AITacticsGenerator *m_10;
	int m_14;
	int m_18;
	Rva00506A34 *m_1C;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec;
};

Rva002C60E4::Rva002C60E4(void *arg0, bool arg1)
	: m_08(arg0), m_0C(0), m_14(0), m_18(0), m_1C(0)
{
	if (arg1)
		m_0C = new AITargetChooser(arg0);
	m_10 = new AITacticsGenerator(arg0);
	m_1C = new Rva00506A34(arg0);
}

// ?rva002C61AF@Rva002C60E4@@QAEXXZ @0x002C61AF 133B: releases the three owned
// members (each guarded, the pointer cleared only when it was set) and then
// the pointer vector at +0x20: delete every non-null element, erase the range.
// Evidence: 0x002C60E4 ctor layout (+0x0C chooser, +0x10 generator, +0x1C
// third member, vector at +0x20) and the rowed dtors 0x0050549A, 0x00505BBA,
// 0x000796BC; the vector erase is the ICF'd void* erase 0x0031BD55.
void Rva002C60E4::rva002C61AF()
{
	if (m_10) { delete (Rva00506909 *)m_10; m_10 = 0; }
	if (m_0C) { delete m_0C; m_0C = 0; }
	if (m_1C != 0) { delete (Rva000C24EA *)m_1C; m_1C = 0; }
	void ***vec = (void ***)&m_vec;
	if (vec[0] != vec[1]) {
		void **finish = *(void ***)((char *)this + 0x24);
		for (void **cur = *(void ***)((char *)this + 0x20); cur != finish; ++cur) {
			if (*cur)
				::operator delete(*cur);
		}
		((_STL::vector<void *, _STL::allocator<void *> > *)vec)->erase(vec[0], vec[1]);
	}
}
