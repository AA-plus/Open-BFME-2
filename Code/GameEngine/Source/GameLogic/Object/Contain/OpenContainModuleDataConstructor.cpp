// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii
// stlport
// ??0OpenContainModuleData@@QAE@XZ, retail 0x00465124..0x00465221 (253
// bytes, EH): the constructor whose table 0x00C43658 the rowed destructor
// 0x00257481 (Rva00465124BaseDtor.cpp) and scalar deleting destructor
// 0x00465221 belong to. Over Snapshot it builds the die-mux data at +8
// (rowed init 0x000CE534), two null release handles at +0x38/+0x3C, the
// +0x40/+0x44 members (rowed 0x003623E5), the +0x48 list (base constructor
// 0x000B92D2), the +0x4C set (0x00463D59), the cleared 128-bit set at +0x58
// (rowed reset 0x0024CA24) and the +0x88 string vector (base constructor
// 0x00211E58); then the body sets its fields (-1000 at +0x68, -1 at +0x70,
// the +0x7D..+0x84 flags) and empties the string vector before +0x94 = 100.
// The unwind map destroys them in reverse (list copy 0x00257464, set copy
// 0x00256641). Field identities beyond the cited callees are not recovered.
#include <bitset>
#include <list>
#include <set>
#include <vector>
#include "ascii_string.h"
#include "Common/Snapshot.h"

struct BfmePod32 { int m_data[8]; };
struct Rva00463D59Element { int m_a; int m_b; };
inline bool operator<(const Rva00463D59Element &a, const Rva00463D59Element &b) { return a.m_a < b.m_a; }

namespace _STL {
template<> _List_base<BfmePod32, allocator<BfmePod32> >::_List_base(const allocator<BfmePod32> &a);
template<> set<Rva00463D59Element, less<Rva00463D59Element>, allocator<Rva00463D59Element> >::set();
template<> __declspec(nothrow) bitset<128> &bitset<128>::reset();
template<> __declspec(nothrow) _Vector_base<AsciiString, allocator<AsciiString> >::_Vector_base(const allocator<AsciiString> &a);
template<> vector<AsciiString, allocator<AsciiString> >::~vector();
template<> vector<AsciiString, allocator<AsciiString> >::iterator vector<AsciiString, allocator<AsciiString> >::erase(iterator first, iterator last);
}

class DieMuxData
{
public:
	DieMuxData() { init(); }
	DieMuxData *init();
private:
	unsigned char m_data[0x30];
};

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct Rva0010F149Handle
{
	Rva0010F149Handle() : m_ptr(0) {}
	~Rva0010F149Handle() { if (m_ptr) m_ptr->Release_Ref(); }
	OpaqueRefCounted *m_ptr;
};

class Rva00360D26Member
{
public:
	Rva00360D26Member();
	~Rva00360D26Member();
private:
	int m_x;
};

struct Rva00257464
{
	__forceinline Rva00257464() {}
	~Rva00257464() {}
	_STL::list<BfmePod32> m_list;
};

struct Rva00256641
{
	~Rva00256641() {}
	_STL::set<Rva00463D59Element> m_set;
};

struct Rva0024CA24Bits
{
	Rva0024CA24Bits() { ((_STL::bitset<128> *)this)->reset(); }
	unsigned int m_words[4];
};

class OpenContainModuleData : public Snapshot
{
public:
	OpenContainModuleData();
	virtual ~OpenContainModuleData();
protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
private:
	int m_04;
	DieMuxData m_dieMuxData;			// +0x08
	Rva0010F149Handle m_ref38;			// +0x38
	Rva0010F149Handle m_ref3C;			// +0x3C
	Rva00360D26Member m_member40;			// +0x40
	Rva00360D26Member m_member44;			// +0x44
	Rva00257464 m_list48;				// +0x48
	Rva00256641 m_set4C;				// +0x4C
	Rva0024CA24Bits m_bits58;			// +0x58
	float m_68;
	float m_6C;
	int m_70;
	int m_74;
	int m_78;
	bool m_7C;
	bool m_7D;
	bool m_7E;
	bool m_7F;
	bool m_80;
	bool m_81;
	bool m_82;
	bool m_83;
	bool m_84;
	bool m_85;
	bool m_86;
	_STL::vector<AsciiString> m_vec88;		// +0x88
	int m_94;
};

OpenContainModuleData::OpenContainModuleData()
{
	m_70 = -1;
	m_68 = -1000.0f;
	m_85 = false;
	m_74 = 1;
	m_6C = 0.0f;
	m_78 = 1;
	m_7C = false;
	m_7D = true;
	m_7E = true;
	m_7F = true;
	m_80 = true;
	m_81 = true;
	m_82 = true;
	m_83 = false;
	m_84 = true;
	m_86 = false;
	m_vec88.clear();
	m_94 = 100;
}
