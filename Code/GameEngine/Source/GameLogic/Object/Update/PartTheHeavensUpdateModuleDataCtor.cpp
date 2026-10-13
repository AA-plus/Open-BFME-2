// ??0PartTheHeavensUpdateModuleData@@QAE@XZ, retail 0x004ACBF8 (185B).
// The pinned factory ?friend_newModuleData@PartTheHeavensUpdateModuleData@@
// SAPAVModuleData@@PAVINI@@@Z (0x0024F4FD, matched) news 0x94 bytes and calls
// this ctor, proving the class size; vtable 0x00854E38 (deleting dtor
// 0x004ACCB1 -> rowed dtor 0x004ACCCD). Layout from the dtor TU: unused +4,
// AsciiString +8, int +0xC, three 44-byte curve members at +0x10/+0x3C/+0x68
// (rowed ctor 0x002BF807, pinned Rva00504EADCurve::set 0x00504EAD). The
// m_str08()/m_0c(0) member-init list is the retail-measured zero-register
// shape; body: curve set(0,0,0,0), set(0,1,0,0), set(0,0,0,0).
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /O1
// stlport
// Native 0x004ACBF8..0x004ACCB0 (185B). Factory
// ?friend_newModuleData@PartTheHeavensUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
// (0x0024F4FD) news 0x94 bytes and calls this ctor. Vtable 0x00854E38
// (deleting dtor 0x004ACCB1 -> rowed dtor 0x004ACCCD). Layout from the dtor
// TU: unused +4, AsciiString +8, unused +0xC, three 44-byte curve members at
// +0x10/+0x3C/+0x68 (rowed ctor 0x002BF807, pinned set 0x00504EAD).
#include <vector>
#include "Common/Snapshot.h"

#include "BfmeE16.h"

#include "ascii_string.h"

class Rva00504EADCurve
{
public:
	void set(float a, float b, float c, float d);
};

class Rva002BF807 : public Rva00504EADCurve
{
public:
	__declspec(nothrow) Rva002BF807();
private:
	int m_pad0;
	int m_pad4;
	_STL::vector<BfmeE16> m_vec;
	int m_rest[6];
};

class PartTheHeavensUpdateModuleData : public Snapshot
{
public:
	PartTheHeavensUpdateModuleData();
	virtual ~PartTheHeavensUpdateModuleData();

private:
	int m_unused04;
	AsciiString m_str08;
	int m_0c;
	Rva002BF807 m_10;
	Rva002BF807 m_3c;
	Rva002BF807 m_68;
};

PartTheHeavensUpdateModuleData::PartTheHeavensUpdateModuleData()
	: m_str08(), m_0c(0)
{
	m_10.set(0.0f, 0.0f, 0.0f, 0.0f);
	m_3c.set(0.0f, 1.0f, 0.0f, 0.0f);
	m_68.set(0.0f, 0.0f, 0.0f, 0.0f);
}
