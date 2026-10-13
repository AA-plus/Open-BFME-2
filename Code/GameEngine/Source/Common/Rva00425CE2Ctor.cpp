// ??0Rva00425CE2@@QAE@XZ, retail 0x00421A84 (154B). The init/dtor TUs own
// this class: ?init@Rva00425CE2@@UAEXXZ (0x424DDE) is slot 1 and the ctor
// stores vtable 0x00C3BEE0. Base SubsystemInterface (rowed ctor 0x001B4E63),
// member at +0x20 (rowed ctor 0x003623E5, pinned applyFilter 0x00362120),
// memset +0x10 for 0x10, floats 40/50/40/0.3 at +0x24..+0x30, byte +0x34,
// temp from prototype 0x00DFEFA4 (rowed copy ctor 0x0004543D, 28-byte value
// proven by applyFilter's ret 0x1C and the sub esp,0x10 over the dead memset
// args). Layout from Rva00425CE2Dtor.cpp.
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 0x00421A84..0x00421B1D (154B). ctor of Rva00425CE2 (the init TU's
// subsystem; ctor stores vtable 0x00C3BEE0); base SubsystemInterface (rowed
// ctor 0x001B4E63), member at +0x20 (rowed ctor 0x003623E5, pinned
// applyFilter 0x00362120), memset +0x10 for 0x10, floats 40/50/40/0.3 at
// +0x24..+0x30, byte +0x34, temp from prototype 0x00DFEFA4 (rowed copy ctor
// 0x0004543D). Layout from the dtor TU Rva00425CE2Dtor.cpp.
#include <string.h>

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
private:
	char m_pad04[8];
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	char m_bytes[0x1c];
};

extern BfmeFixedStorage0004543D g_00DFEFA4;

class Rva003623E5Filter
{
public:
	void applyFilter(BfmeFixedStorage0004543D temp);
};

class Rva003623E5Member : public Rva003623E5Filter
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
private:
	unsigned m_unknown;
};

class Rva00425CE2 : public SubsystemInterface
{
public:
	Rva00425CE2();
	virtual ~Rva00425CE2();
	virtual void init();
private:
	int m_0C;
	char m_10[0x10];
	Rva003623E5Member m_20;
	float m_24, m_28, m_2C, m_30;
	bool m_34;
};

Rva00425CE2::Rva00425CE2()
	: m_0C(0), m_20()
{
	m_24 = 40.0f;
	m_28 = 50.0f;
	m_2C = 40.0f;
	m_30 = 0.3f;
	m_34 = false;
	memset(m_10, 0, 0x10);
	m_20.applyFilter(g_00DFEFA4);
}
