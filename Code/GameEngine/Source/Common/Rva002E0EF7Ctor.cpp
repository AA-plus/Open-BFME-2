// WotR player member ownership, 2026-10-12. Target table C04948 and its
// LWPlayerDef literal establish Snapshot identity independently of the bank.
// Default2E0EF7/copy2E0A0A/dtor2E0F1E and xfer52BA0A establish the 0x28-byte
// physical contract: wide handle04, narrow08/0C/10/14, ints18/1C/20, flag24.
// Legacy address-named views retain existing callers while emitting the same
// complete four-slot table. Every added fold has whole-body/relocation proof;
// no unique-byte credit for member aliases. See attempt_evidence/player-owners.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/moduledata
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
// Initialization-only physical view: the five string handles at04..14 are
// cleared directly by retail. Their real release/copy workers are owned by
// LWPlayerDef's complete teardown and copy-construction implementations.
class Rva002E0EF7:public Snapshot {
public: __declspec(nothrow) Rva002E0EF7();virtual ~Rva002E0EF7();
protected:virtual void loadPostProcess(){}virtual const char*GetSnapshotName()const{return "LWPlayerDef";}virtual void xfer(Xfer*);
private:int m_04,m_08,m_0c,m_10,m_14,m_18,m_1c,m_20;bool m_24;
};
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
Rva002E0EF7::Rva002E0EF7(){m_04=0;m_08=0;m_0c=0;m_10=0;m_14=0;_ReadWriteBarrier();m_1c=-1;m_18=0;m_20=0;m_24=false;}
typedef char LegacySize[sizeof(Rva002E0EF7)==40?1:-1];

class LWPlayerDef:public Snapshot {
public: __declspec(nothrow) LWPlayerDef();virtual ~LWPlayerDef();
protected:virtual void loadPostProcess(){}virtual const char*GetSnapshotName()const{return "LWPlayerDef";}virtual void xfer(Xfer*);
private:int m_04,m_08,m_0c,m_10,m_14,m_18,m_1c,m_20;bool m_24;
};
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
LWPlayerDef::LWPlayerDef(){m_04=0;m_08=0;m_0c=0;m_10=0;m_14=0;_ReadWriteBarrier();m_1c=-1;m_18=0;m_20=0;m_24=false;}
typedef char LWSize[sizeof(LWPlayerDef)==40?1:-1];
