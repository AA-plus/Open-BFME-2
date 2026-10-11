// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?DoXfer@Rva0055DB41@@UAEXAAVXfer@@@Z, retail 0x0055DB41 (146 bytes): the
// Snapshot DoXfer slot shared by three FX particle module tables (0x0081C6E8,
// 0x0081D0C8, 0x0081D798 minus the slot), placed after the lightning emission
// template parsers. Version 1 (rowed 0x000053EE), two Coord3D fields (+0x24,
// +0x30, Xfer slot 0x60 as in ParticleSystemInfo::DoXfer) and nine
// GameClientRandomVariables (+0x3C..+0x9C, rowed xferRandomVariable). The
// Xfer view is ParticleSystemInfoDoXfer.cpp's; owner name address-derived.
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
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
class Rva0055DB41SnapshotView;

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

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

	virtual void SkipBadBlock(Rva0055DB41SnapshotView &snapshot, unsigned int size);
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
	virtual Xfer &operator==(Rva0055DB41SnapshotView &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


class GameClientRandomVariable
{
public:
	int m_type;
	float m_low;
	float m_high;
};

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &v);

class Rva0055DB41SnapshotView
{
public:
	virtual ~Rva0055DB41SnapshotView() {}
	virtual const char *GetSnapshotName() = 0;
	virtual void LoadPostProcess() = 0;
	virtual void DoXfer(Xfer &xfer) = 0;
};

class Rva0055DB41 : public Rva0055DB41SnapshotView
{
public:
	virtual void DoXfer(Xfer &xfer);
private:
	unsigned char m_pad04[0x24 - 0x04];
	Coord3DBase m_24;
	Coord3DBase m_30;
	GameClientRandomVariable m_3C;
	GameClientRandomVariable m_48;
	GameClientRandomVariable m_54;
	GameClientRandomVariable m_60;
	GameClientRandomVariable m_6C;
	GameClientRandomVariable m_78;
	GameClientRandomVariable m_84;
	GameClientRandomVariable m_90;
	GameClientRandomVariable m_9C;
};

void Rva0055DB41::DoXfer(Xfer &xfer)
{
	xfer.Version1();
	xfer == m_24;
	xfer == m_30;
	xferRandomVariable(xfer, m_3C);
	xferRandomVariable(xfer, m_48);
	xferRandomVariable(xfer, m_54);
	xferRandomVariable(xfer, m_60);
	xferRandomVariable(xfer, m_6C);
	xferRandomVariable(xfer, m_78);
	xferRandomVariable(xfer, m_84);
	xferRandomVariable(xfer, m_90);
	xferRandomVariable(xfer, m_9C);
}
