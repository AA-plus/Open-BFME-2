// ??0Rva0073F4F3@@QAE@PAX@Z, retail 0x0073F468 (139B RET4). Base ctor of
// Rva0073F4F3 whose dtor row is 0x0073F4F3 (Rva0073F4F3Dtor.cpp): stores the
// void* argument at +0, zero at +4, two 4-byte heap-sentinel list heads at
// +8/+0x1C (rowed _List_base<Coord3D> ctor 0x00280A8D), two 8-byte mutex
// members at +0xC/+0x20 (rowed ctor 0x00040F1E) and two 8-byte event members
// at +0x14/+0x28 (rowed ctor 0x00040F64); all four share the dtor at 0x40EDB.
// cl: /Ireference/shims/bfmelist /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// Native 0x0073F468..0x0073F4F2 (139B, RET4): base ctor of Rva0073F4F3
// (dtor 0x0073F4F3), stores the void* argument at +0, +4 zero, two 4-byte
// list heads at +8/+0x1C (rowed _List_base<Coord3D> ctor 0x00280A8D), two
// 8-byte mutexes at +0xC/+0x20 (rowed ctor 0x00040F1E) and two 8-byte events
// at +0x14/+0x28 (rowed ctor 0x00040F64). Layout from Rva0073F4F3Dtor.cpp.
#include <list>

#include "Coord3D.h"

// The mutex member call names the master's real class (row ??0Mutex@@QAE@HPBDPAX@Z
// at 0x00040F1E, Code/GameEngine/Source/Common/Rva00040F1EMutex.cpp). This TU
// only needs the ctor's name and the member's 8-byte size; it declares neither
// virtuals nor a local definition of the dtor.
class Mutex
{
public:
	Mutex(int a, const char *b, void *c);
	~Mutex();
private:
	char m_pad[8];
};

class Rva0040F9D
{
public:
	Rva0040F9D(int a, int b, const char *c, void *d);
	~Rva0040F9D();
private:
	char m_pad[8];
};

class Rva0073F4F3
{
public:
	Rva0073F4F3(void *arg);
private:
	void *m_arg;
	int m_4;
	_STL::list<Coord3D> m_8;
	Mutex m_0c;
	Rva0040F9D m_14;
	_STL::list<Coord3D> m_1c;
	Mutex m_20;
	Rva0040F9D m_28;
};

Rva0073F4F3::Rva0073F4F3(void *arg)
	: m_arg(arg), m_4(0), m_0c(1, 0, 0), m_14(1, 0, 0, 0), m_20(1, 0, 0), m_28(1, 0, 0, 0)
{
}
