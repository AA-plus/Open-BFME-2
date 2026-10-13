// ??0Rva00421A84@@QAE@XZ
// partial score=0.9 date=2026-10-13
// cl: /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// Retail 0x00421A84 (154B, RET0 thiscall): constructor over the rowed
// SubsystemInterface base (0x001B4E63) with vtable VA 0x00C3BEE0: the int at
// +0xC and a 16-byte BfmeFixedStorage0004543D at +0x10 are zeroed (retail's
// memset import 0x006291AE), the Rva003623E5Member at +0x20 is constructed
// through the rowed 0x003623E5, four floats come from the data globals and the
// +0x34 byte is cleared; finally the by-value fixed storage global is copied to
// the stack (rowed copy ctor 0x0004543D) and handed to the rowed
// Rva003623E5Filter::applyFilter 0x00362120 through the same +0x20 object.
// The owning class identity is unknown; the row keeps an address-derived name.
extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);

class BfmeFixedStorage0004543D
{
public:
	__forceinline BfmeFixedStorage0004543D() {}
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &o);

private:
	unsigned char m_data[16];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
};

class Rva003623E5Filter
{
public:
	void applyFilter(BfmeFixedStorage0004543D storage);
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	char m_pad04[8];
};

extern BfmeFixedStorage0004543D g_Rva00421A84Storage;
extern float g_Rva00421A84FloatA;
extern float g_Rva00421A84FloatB;
extern float g_Rva00421A84FloatC;

class Rva00421A84 : public SubsystemInterface
{
public:
	Rva00421A84();

private:
	int m_0C;
	BfmeFixedStorage0004543D m_10;
	Rva003623E5Member m_20;
	float m_24;
	float m_28;
	float m_2C;
	float m_30;
	bool m_34;
};

Rva00421A84::Rva00421A84() :
	m_0C(0),
	m_10(),
	m_24(g_Rva00421A84FloatA),
	m_28(g_Rva00421A84FloatB),
	m_2C(g_Rva00421A84FloatA),
	m_30(g_Rva00421A84FloatC),
	m_34(0)
{
	memset(&m_10, 0, 16);
	((Rva003623E5Filter *)&m_20)->applyFilter(g_Rva00421A84Storage);
}
