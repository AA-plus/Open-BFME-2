// ??0Rva000F9C3C@@QAE@XZ
// partial score=0.96 date=2026-10-13
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /arch:SSE
// stlport
// ??0Rva000F9C3C@@QAE@XZ @0x000F9C3C 97B trial r3: vtable + zero members +
// two BfmeE16 vectors via the _Vector_base allocator-forwarding idiom
// (SaveGameInfoConstructorBFME2 precedent: forceinline member ctor keeps the
// byte-sized allocator temporary and the 0x611E58 base call in place).
// vtable as raw immediate for the trial only (needs data row + g_ name).
#include <memory>
#include <vector>

struct BfmeE16 { float x, y, z, w; };
struct BfmeE16Vec : _STL::_Vector_base<BfmeE16, std::allocator<BfmeE16> > {
	__forceinline BfmeE16Vec() : _STL::_Vector_base<BfmeE16, std::allocator<BfmeE16> >(std::allocator<BfmeE16>()) {}
	~BfmeE16Vec();
};

class Rva000F9C3C {
public:
	virtual ~Rva000F9C3C();
	Rva000F9C3C();
	int m04, m08, m0C, m10, m14, m18, m1C;
	float f20, f24, f28;
	BfmeE16Vec v2C;
	BfmeE16Vec v38;
	int m44, m48, m4C, m50;
};

// ??0Rva000F9C3C@@QAE@XZ @0x000F9C3C 97B.
Rva000F9C3C::Rva000F9C3C() : m04(0), m08(0), m0C(0), m10(0), m14(0), m18(0), m1C(0), f20(0.0f), f24(0.0f), f28(0.0f), v2C(), v38(), m44(0), m48(0), m4C(0), m50(0) {}
