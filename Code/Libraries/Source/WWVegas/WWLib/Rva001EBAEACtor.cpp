// cl: /O1 /Oy- /arch:SSE /MD /GX- /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ??0Rva001EBAEA@@QAE@HH@Z, retail 0x001EBAEA, 137 bytes.
// Honest-address ctor: base holds the two int args at +4/+8 so their stores
// precede the derived vptr install at +0 (vtable 0x00BDF168, gate DIR32),
// then zeroes at +0x0C/+0x10, three 16-byte element vectors at
// +0x14/+0xA4/+0xB4 via the rowed _Vector_base 0x00211E58, an 0x80-byte member
// at +0x20 via the shared clear80 helper 0x001EAE6F, float zero at +0xA0,
// int zero at +0xB0 and four zero bytes at +0xC0. Callers at 0x001EBC32 and
// 0x001ECF48. Element size only (BfmeE16 stand-in); class/param identity
// unproven so the name is address-derived.
#include "../../../Include/Lib/BfmeE16.h"

namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};

template <class T, class Allocator> class _Vector_base
{
public:
	_Vector_base(const Allocator &);

protected:
	T *m_begin;
	T *m_end;
	T *m_endOfStorage;
};

template <class T> class vector : public _Vector_base<T, allocator<T> >
{
public:
	__forceinline vector() : _Vector_base<T, allocator<T> >(allocator<T>()) {}
};
}

class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper();
	Rva001EAE6FHelper *clear80();

private:
	char m_pad[0x80];
};

// ??0Rva001EAE6FHelper@@QAE@XZ present-unmatched
inline Rva001EAE6FHelper::Rva001EAE6FHelper()
{
	clear80();
}

class Rva001EBAEABase
{
public:
	Rva001EBAEABase(int a, int b) : m_a(a), m_b(b) {}

protected:
	int m_a;
	int m_b;
};

class Rva001EBAEA : public Rva001EBAEABase
{
public:
	Rva001EBAEA(int a, int b);
	virtual ~Rva001EBAEA();

private:
	int m_c;
	float m_f;
	_STL::vector<BfmeE16> m_vec0;
	Rva001EAE6FHelper m_helper;
	float m_f2;
	_STL::vector<BfmeE16> m_vec1;
	int m_c2;
	_STL::vector<BfmeE16> m_vec2;
	unsigned char m_b0;
	unsigned char m_b1;
	unsigned char m_b2;
	unsigned char m_b3;
};

Rva001EBAEA::Rva001EBAEA(int a, int b)
	: Rva001EBAEABase(a, b)
	, m_c(0)
	, m_f(0.0f)
	, m_vec0()
	, m_helper()
	, m_f2(0.0f)
	, m_vec1()
	, m_c2(0)
	, m_vec2()
	, m_b0(0)
	, m_b1(0)
	, m_b2(0)
	, m_b3(0)
{
}
