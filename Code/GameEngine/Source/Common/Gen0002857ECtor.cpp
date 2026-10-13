// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??0Gen0002857E@@QAE@PAVRva000A7E9E@@ABVAsciiString@@@Z at 0x0010ED4C (118B).
// Constructor of the Miles wave-info entry whose handle/release methods are
// rowed in Rva0010ECBDFinish.cpp: copies the name at +0, stores the owner at
// +4, zeroes the counters/flags at +0x2C..+0x40 and builds the two events at
// +0x44/+0x4C. Native 10ED4C..10EDC2 RET8; the destructor view of the same
// object is Rva0010EDC2 in Rva0010ED3DMax.cpp.
// Evidence: BFME1 donor game/GameEngine/Source/Common/Gen0002857EHandle.cpp
// field map; retail pushes (1,0,0,0) into the event constructor 0x00040F64 for
// both events and memsets the 0x24-byte wave info at +8.
// Codegen: the retail scheduler stores the +0x34 counter early (before the
// first event constructor's pushes) and the remaining zero stores later; that
// order appears when the +0x3C priority word is a volatile member as well, the
// same way the volatile +0x34 counter keeps the handle() add-immediate.
#include "ascii_string.h"
#include "../../Include/Common/Rva00041004Lock.h"
#include <string.h>

class __declspec(novtable) Rva0040F9D : public Rva0040EDB {
public:
	Rva0040F9D(int,int,const char*,void*);
	virtual ~Rva0040F9D() {}
};

class Rva000A7E9E;

class Gen0002857E
{
public:
	Gen0002857E(Rva000A7E9E *owner, const AsciiString &name);
private:
	AsciiString m_name;
	Rva000A7E9E *m_owner;
	unsigned int m_waveInfo[9];
	void *m_data;
	unsigned int m_size;
	volatile int m_count;
	unsigned int m_lastReleaseTime;
	volatile int m_priority;
	bool m_allocated;
	Rva0040F9D m_ready;
	Rva0040F9D m_failed;
};

Gen0002857E::Gen0002857E(Rva000A7E9E *owner, const AsciiString &name)
	: m_name(name), m_owner(owner), m_data(0), m_size(0), m_count(0), m_lastReleaseTime(0),
	m_priority(0), m_allocated(false), m_ready(1, 0, 0, 0), m_failed(1, 0, 0, 0)
{
	memset(m_waveInfo, 0, sizeof(m_waveInfo));
}
