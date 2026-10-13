// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0HordeMeleeAmoeba@@QAE@PAX0@Z, retail 0x00587D9C 49B.
// Derived ctor: base Rva005D6FCC (vptr + held void* at +4, rowed 0x005D6FCC)
// then vector<BfmeE16> at +8 via rowed Vector_base 0x00211E58, bool at +0x14
// set, void* at +0x18 stored. Caller 0x00587F39; vtable 0x00C6FF38.
// Same recipe as rowed ??0HordeMeleeFormation 0x00586D8E with flag true.
#include <vector>

#include "../../../Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

class Rva005D6FCC
{
public:
	Rva005D6FCC(void *held);
	virtual ~Rva005D6FCC();
	void *m_held;
};

class HordeMeleeAmoeba : public Rva005D6FCC
{
public:
	HordeMeleeAmoeba(void *held, void *other);
	virtual ~HordeMeleeAmoeba();
private:
	_STL::vector<BfmeE16> m_vec; // +8
	bool m_flag; // +0x14
	void *m_other; // +0x18
};

HordeMeleeAmoeba::HordeMeleeAmoeba(void *held, void *other)
	: Rva005D6FCC(held), m_vec(_STL::allocator<BfmeE16>())
{
	m_other = other;
	m_flag = true;
}

// ?rva00587F11@Rva00587F11Factory@@QAEPAVRva005D6FCC@@PAX@Z, retail
// 0x00587F11 60B: slot 1 of the HordeMeleeAmoeba factory table (deleting
// destructor ICF-shared at 0x00587752 in slot 0); creates the amoeba around
// the given pointer with the factory itself as its second argument.
class Rva00587F11Factory
{
public:
	Rva005D6FCC *rva00587F11(void *held);
};

Rva005D6FCC *Rva00587F11Factory::rva00587F11(void *held)
{
	return new HordeMeleeAmoeba(held, this);
}
