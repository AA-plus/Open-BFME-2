// WotR player member ownership, 2026-10-12. Target table C04948 and its
// LWPlayerDef literal establish Snapshot identity independently of the bank.
// Default2E0EF7/copy2E0A0A/dtor2E0F1E and xfer52BA0A establish the 0x28-byte
// physical contract: wide handle04, narrow08/0C/10/14, ints18/1C/20, flag24.
// Legacy address-named views retain existing callers while emitting the same
// complete four-slot table. Every added fold has whole-body/relocation proof;
// no unique-byte credit for member aliases. See attempt_evidence/player-owners.
// cl: /O1 /Ob2 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "ascii_string.h"
#include "unicode_string.h"
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
class Xfer
{
public:
	class Version;
	Xfer();
	virtual ~Xfer();
	void Version1();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;
	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);
	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);
protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};
class Xfer::Version
{
public:
	unsigned char m_major;
	unsigned char m_minor;
	Version(unsigned char a, unsigned char b) : m_major(a), m_minor(b) {}
};

// Native table C04948: scalar2E18A7, emptyB3FD0, name52BA04, xfer52BA0A.
// Target string C686E8 independently names LWPlayerDef. Physical member
// contract: five string handles +4..14, integers18/1C/20 and flag24, size28.
class LWPlayerDef:public Snapshot {
public:
 __declspec(nothrow) LWPlayerDef(); LWPlayerDef(const LWPlayerDef&);
 virtual ~LWPlayerDef();
protected:
 virtual void loadPostProcess();
 virtual const char *GetSnapshotName()const;
 virtual void xfer(Xfer*);
private:
 UnicodeString m_04;AsciiString m_08,m_0c,m_10,m_14;
 int m_18,m_1c,m_20;bool m_24;
};
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

LWPlayerDef::LWPlayerDef(const LWPlayerDef&s):m_04(s.m_04),m_08(s.m_08),m_0c(s.m_0c),m_10(s.m_10),m_14(s.m_14){m_18=s.m_18;m_1c=s.m_1c;m_20=s.m_20;m_24=s.m_24;}

typedef char LWDefSize[sizeof(LWPlayerDef)==40?1:-1];
void LWPlayerDef::xfer(Xfer *xfer)
{
	Xfer::Version v(1, 2);
	*xfer == v;
	if (!xfer->IsCRC())
		*xfer == m_04;
	*xfer == m_08;
	*xfer == m_0c;
	*xfer == m_14;
	*xfer == m_1c;
	*xfer == m_10;
	*xfer == m_18;
	*xfer == m_24;
	if (v.m_minor >= 2)
		*xfer == m_20;
	else
		m_20 = 0;
}

class Rva002E0EF7:public Snapshot {
public:
 __declspec(nothrow) Rva002E0EF7(); Rva002E0EF7(const Rva002E0EF7&);
 virtual ~Rva002E0EF7();
protected:
 virtual void loadPostProcess();
 virtual const char *GetSnapshotName()const;
 virtual void xfer(Xfer*);
private:
 UnicodeString m_04;AsciiString m_08,m_0c,m_10,m_14;
 int m_18,m_1c,m_20;bool m_24;
};

void Rva002E0EF7::xfer(Xfer *xfer)
{
	Xfer::Version v(1, 2);
	*xfer == v;
	if (!xfer->IsCRC())
		*xfer == m_04;
	*xfer == m_08;
	*xfer == m_0c;
	*xfer == m_14;
	*xfer == m_1c;
	*xfer == m_10;
	*xfer == m_18;
	*xfer == m_24;
	if (v.m_minor >= 2)
		*xfer == m_20;
	else
		m_20 = 0;
}
