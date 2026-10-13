// ??0WaterTransparencySetting@@QAE@XZ
// partial score=0.9 date=2026-10-13
// ??0WaterTransparencySetting@@QAE@XZ
// partial score=0.9 date=2026-09-29
// ??0WaterTransparencySetting@@QAE@XZ
// partial score=0.90 date=2026-09-29
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ??0WaterTransparencySetting@@QAE@XZ, retail 0x00200D80, 249 bytes.
// Water transparency defaults over rowed Rva00200D38 member at +0x10 via
// pinned StringBase char ctor 0x00037BA0 and rowed Rva ctor 0x00200D38.
// Evidence: strings WaterTransparency and TWWater01.tga, vtable overwrites
// 0x007DDC48 to 0x007E2BA4 and member 0x00BE2B78 to 0x007E2B98, floats
// 3.0 1.0 140.0 255.0 via movss, callers at 0x00200F2A and 0x00200F5C.
// Donor: ZH Water.h WaterTransparencySetting ctor.
template <typename T>
class StringBase
{
	friend class AsciiString;
	StringBase() : m_data(0) {}
	StringBase(const char *str);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();
public:
	void set(const char *str);
private:
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const char *str) : StringBase<char>(str) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() { releaseBuffer(); }
};

class Rva00200D38
{
public:
	Rva00200D38(const AsciiString &name);
private:
	const void *m_vtable;
	AsciiString m_name;
};

class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

struct RGBColor
{
	float red;
	float green;
	float blue;
};

class WaterTransparencySetting : public EmptyBase
{
public:
	WaterTransparencySetting();
private:
	const void *m_vtable;
	void *m_nextOverride;
	unsigned char m_isOverride;
	char m_pad09[3];
	int m_unk0C;
	Rva00200D38 m_rva10;
	float m_depth18;
	float m_opacity1C;
	RGBColor m_standing20;
	RGBColor m_radar2C;
	bool m_blend38;
	char m_pad39[3];
	AsciiString m_texture3C;
	float m_unk40;
	char m_pad44[8];
	float m_unk4C;
	bool m_unk50;
	char m_pad51[3];
	float m_unk54;
	float m_unk58;
};

WaterTransparencySetting::WaterTransparencySetting()
	: m_vtable(reinterpret_cast<const void *>(0x007DDC48)), m_nextOverride(0), m_isOverride(0), m_unk0C(-1), m_rva10(AsciiString("WaterTransparency"))
{
	m_vtable = reinterpret_cast<const void *>(0x007E2BA4);
	*(const void **)&m_rva10 = reinterpret_cast<const void *>(0x007E2B98);
	m_depth18 = 3.0f;
	m_opacity1C = 1.0f;
	m_standing20.red = 1.0f;
	m_standing20.green = 1.0f;
	m_standing20.blue = 1.0f;
	m_radar2C.red = 140.0f;
	m_radar2C.green = 140.0f;
	m_radar2C.blue = 255.0f;
	m_texture3C.set("TWWater01.tga");
	m_unk40 = 1.0f;
	m_unk4C = 20.0f;
	m_blend38 = false;
	m_unk50 = false;
	m_unk54 = 0.0f;
	m_unk58 = 0.0f;
}
