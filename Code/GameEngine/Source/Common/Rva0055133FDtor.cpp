// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// ??1Rva0055133F@@UAE@XZ, retail 0x0055133F..0x005513E9 (170 bytes, EH):
// the destructor of the class whose scalar deleting destructor is 0x00551323
// (vtable 0x00C6AC0C). Retail stores no own table here (reproduced with a
// novtable view; the implicit destructor is the other candidate); only the
// parts die, in retail's unwind-map order: the lock holder at +0xA8
// (inline destructor running the rowed clearLock 0x00550995), the
// CriticalSectionClass at +0xA0, five buffers at +0x90/+0x84/+0x78/+0x6C/
// +0x60 whose storage goes to GameFree (unwind copies at 0x00142D70) and the
// base (rowed out-of-line destructor 0x00610480 restoring 0x00C7B6AC).
// Identities are not established.
#include "mutex.h"

void __cdecl Rva00030830GameFree(void *);

class Gen_uwm_00610480
{
public:
	virtual void s0();
	~Gen_uwm_00610480();
};

struct Gen_uwm_00142d70
{
	~Gen_uwm_00142d70() { if (m_start) Rva00030830GameFree(m_start); }
	void *m_start;
	void *m_finish;
	void *m_end;
};

class Rva00550995Owner
{
public:
	~Rva00550995Owner() { clearLock(); }
	void clearLock();
private:
	CriticalSectionClass::LockClass *m_lock;
};

class __declspec(novtable) Rva0055133F : public Gen_uwm_00610480
{
public:
	virtual ~Rva0055133F();
private:
	unsigned char m_pad04[0x60 - 4];
	Gen_uwm_00142d70 m_60;
	Gen_uwm_00142d70 m_6C;
	Gen_uwm_00142d70 m_78;
	Gen_uwm_00142d70 m_84;
	Gen_uwm_00142d70 m_90;
	int m_9C;
	CriticalSectionClass m_section;		// +0xA0
	Rva00550995Owner m_lockHolder;		// +0xA8
};

Rva0055133F::~Rva0055133F()
{
}
