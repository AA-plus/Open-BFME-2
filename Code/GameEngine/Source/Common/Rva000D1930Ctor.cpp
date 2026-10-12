// RegionBonusInfo: retail ctor20E42C writes six zeros after the Snapshot
// vptr. Native BE4324 has four slots: scalar4A10FD, emptyB3FD0,
// literal-name3EFD37 and serializer3EFCD1. This replaces the old single-dword
// address-named table with its complete owner; size0x1C is independently
// witnessed by the two player member offsets258/274 and other constructors.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/moduledata
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class RegionBonusInfo:public Snapshot {
public:
 __declspec(nothrow) RegionBonusInfo(); virtual ~RegionBonusInfo(){}
protected:
 virtual void loadPostProcess(){}
 virtual const char *GetSnapshotName()const{return "RegionBonusInfo";}
 virtual void xfer(Xfer*);
private:int m_04,m_08,m_0C,m_10,m_14,m_18;
};
RegionBonusInfo::RegionBonusInfo(){m_04=0;m_08=0;m_0C=0;m_10=0;m_14=0;m_18=0;}
typedef char BonusSize[sizeof(RegionBonusInfo)==28?1:-1];
