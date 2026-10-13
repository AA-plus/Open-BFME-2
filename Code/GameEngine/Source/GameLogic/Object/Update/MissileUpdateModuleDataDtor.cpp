// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1MissileUpdateModuleData@@UAE@XZ, retail 0x004A7869, 51 bytes.
// MissileUpdateModuleData destructor: destroys the exhaust AsciiString at
// +0x11C through the pinned StringBase dtor 0x00036410 (state 0) then
// restores the Snapshot base vtable 0x00BBB554. Layout from the rowed ctor
// 0x004A77B8 (size 0x120 via factory 0x0024EFA0, exhaust string at +0x11C,
// table 0x00C53470) and the rowed FriendNew TU (vptr plus 0x11C pad).
// Own vtable 0x00853668 installed by the ctor. Caller is the slot-0 ??_G at
// 0x004A784D. Shape follows CreateObjectDieModuleDataDtor (TU-local Snapshot
// with inline BBB554-restoring dtor plus novtable derived suppressing the
// entry store retail lacks plus single string member).


class Xfer;

#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"


#include "ascii_string.h"

class __declspec(novtable) MissileUpdateModuleData : public Snapshot
{
public:
	virtual ~MissileUpdateModuleData();

private:
	unsigned char m_pad04[0x11C - 4];
	AsciiString m_exhaust;
};

MissileUpdateModuleData::~MissileUpdateModuleData()
{
}
