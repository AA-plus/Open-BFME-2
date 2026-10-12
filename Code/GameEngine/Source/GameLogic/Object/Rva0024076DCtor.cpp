// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0024076D@@QAE@XZ, retail 0x0024076D..0x0024080F (162 bytes, EH,
// ret 0): the default constructor of the 0x50-byte local an Object method
// builds at [ebp-0x70] (call at 0x00248869). Layout from the bytes and the
// unwind funclet 0x0077126A (an AsciiString at +0): an AsciiString, a
// WWMath-style Matrix3D at +4 whose three 16-byte rows go through the vector
// constructor iterator over the folded empty row ctor 0x0047A6A9 and are set
// to identity in the body, four cleared words, an observer list (list base
// 0x004EC36C) at +0x44 and two cleared words. Identity is not established.
#include <list>
#include "ascii_string.h"

struct Rva0047A6A9Row16
{
	Rva0047A6A9Row16();										// 0x0047A6A9
	float x, y, z, w;
};

struct Rva0024076DMatrix3D
{
	Rva0047A6A9Row16 Row[3];
	__forceinline Rva0024076DMatrix3D() {}
	__forceinline void Make_Identity()
	{
		Row[0].x = 1.0f; Row[0].y = 0.0f; Row[0].z = 0.0f; Row[0].w = 0.0f;
		Row[1].x = 0.0f; Row[1].y = 1.0f; Row[1].z = 0.0f; Row[1].w = 0.0f;
		Row[2].x = 0.0f; Row[2].y = 0.0f; Row[2].z = 1.0f; Row[2].w = 0.0f;
	}
};

struct Rva004FA1FObserver;

class Rva0024076D
{
public:
	Rva0024076D();

private:
	AsciiString m_name;										// +0x00
	Rva0024076DMatrix3D m_transform;						// +0x04
	int m_34;												// +0x34
	int m_38;												// +0x38
	int m_3C;												// +0x3C
	int m_40;												// +0x40
	_STL::list<Rva004FA1FObserver *> m_observers;			// +0x44
	int m_48;												// +0x48
	int m_4C;												// +0x4C
};

Rva0024076D::Rva0024076D()
{
	m_transform.Make_Identity();
	m_34 = 0;
	m_38 = 0;
	m_3C = 0;
	m_40 = 0;
	m_48 = 0;
	m_4C = 0;
}
