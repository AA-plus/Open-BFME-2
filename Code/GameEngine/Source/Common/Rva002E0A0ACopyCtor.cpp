// WotR player member ownership, 2026-10-12. Target table C04948 and its
// LWPlayerDef literal establish Snapshot identity independently of the bank.
// Default2E0EF7/copy2E0A0A/dtor2E0F1E and xfer52BA0A establish the 0x28-byte
// physical contract: wide handle04, narrow08/0C/10/14, ints18/1C/20, flag24.
// Legacy address-named views retain existing callers while emitting the same
// complete four-slot table. Every added fold has whole-body/relocation proof;
// no unique-byte credit for member aliases. See attempt_evidence/player-owners.
// cl: /O1 /G7 /arch:SSE /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /EHsc /MD
// ??0Rva002E0A0A@@QAE@ABV0@@Z @0x002E0A0A 149B copy ctor with vptr then 1 wide and 4 narrow StringBase copies then ints and byte
// Evidence: callees rowed 0x00037050 wide plus 0x000365F0 narrow x4; callers 0x002E2943 0x0052C1F2; vtable VA 0x00804948 via virtual dtor filled by gate
// Link note: TU-local StringBase kept because shared header's copy ctor is private to AsciiString/UnicodeString friends, so direct member copies need a friend grant here
#include "ascii_string.h"


#include "unicode_string.h"

#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class Rva002E0A0A : public Snapshot
{
public:
	Rva002E0A0A(const Rva002E0A0A &src);
	virtual ~Rva002E0A0A();
protected:virtual void loadPostProcess(){}virtual const char*GetSnapshotName()const{return "LWPlayerDef";}virtual void xfer(Xfer*);
private:
	UnicodeString m_04;
	AsciiString m_08;
	AsciiString m_0c;
	AsciiString m_10;
	AsciiString m_14;
	int m_18;
	int m_1c;
	int m_20;
	unsigned char m_24;
};

Rva002E0A0A::Rva002E0A0A(const Rva002E0A0A &src)
	: m_04(src.m_04)
	, m_08(src.m_08)
	, m_0c(src.m_0c)
	, m_10(src.m_10)
	, m_14(src.m_14)
{
	m_18 = src.m_18;
	m_1c = src.m_1c;
	m_20 = src.m_20;
	m_24 = src.m_24;
}
