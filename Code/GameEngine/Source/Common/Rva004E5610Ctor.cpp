// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva004E5610@@QAE@XZ, retail 0x004E5610, 68 bytes.
//
// Evidence: the pin names the ctor; the rowed vtable 0x00C623C4 slot 0 is
// Rva004E5610::rva004E55B9 (0x004E55B9), the rowed
// _List_base<BfmePod60> ctor 0x004E4F59 builds the four-byte list at +4 with
// an allocator temporary, and the float at +8 loads the shared 1.0f constant
// 0x00BBB8D8. BfmePod60 is the ledger's 0x60-byte placeholder element, as in
// stlport_pod_list_bodies.cpp.

#include <list>

struct BfmePod60
{
	int a[15];
};

inline bool operator==(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] < y.a[0]; }

class Rva004E5610Base
{
public:
	Rva004E5610Base() {}
	virtual ~Rva004E5610Base();
	virtual void sb();
};

class Rva004E5610 : public Rva004E5610Base
{
public:
	Rva004E5610();
	virtual ~Rva004E5610();
	virtual void rva004E55B9(int objectID, float value, bool flag);

private:
	std::list<BfmePod60> m_list4; // +0x04
	float m_8; // +0x08
};

Rva004E5610::Rva004E5610()
	: m_8(1.0f)
{
}
