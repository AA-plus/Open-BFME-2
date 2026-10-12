// ??0Rva001DA19EBase@@QAE@XZ
// partial score=0.85 date=2026-10-12
// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva001DA19EBase@@QAE@XZ, retail 0x001DA19E..0x001DA2D5 (311 bytes, no EH
// frame, ret 0): the default constructor of the 0xC4-byte base the rowed
// Rva00433390 constructor (and 0x0005AD2A) builds first (pinned under this
// address name). It installs table 0x00BDA270 and initializes, in offset
// order: three cleared words, a 100.0f limit and seven cleared floats, 1.0f,
// two cleared words, 25, -1, 2, two cleared words, four zero-initialized
// vectors each followed by a cleared count word (+0x50..+0x8C), a float block
// (0, 100, 1000, 1, 1, 0, 1, 1), 2, -1 and a last vector at +0xB8. Retail
// builds this unit without exception handling (no frame for the vector
// members). Field meanings are not established.
#include <vector>

class Rva001DA19EBase
{
public:
	Rva001DA19EBase();
	virtual ~Rva001DA19EBase();

private:
	int m_04;
	int m_08;
	int m_0C;
	float m_10;
	float m_14, m_18, m_1C, m_20, m_24, m_28, m_2C;
	float m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;
	_STL::vector<int> m_50;
	int m_5C;
	_STL::vector<int> m_60;
	int m_6C;
	_STL::vector<int> m_70;
	int m_7C;
	_STL::vector<int> m_80;
	int m_8C;
	float m_90, m_94, m_98, m_9C, m_A0, m_A4, m_A8, m_AC;
	int m_B0;
	int m_B4;
	_STL::vector<int> m_B8;
};

Rva001DA19EBase::Rva001DA19EBase()
	: m_04(0), m_08(0), m_0C(0),
	  m_10(100.0f),
	  m_14(0.0f), m_18(0.0f), m_1C(0.0f), m_20(0.0f), m_24(0.0f), m_28(0.0f), m_2C(0.0f),
	  m_30(1.0f),
	  m_34(0), m_38(0), m_3C(25), m_40(-1), m_44(2), m_48(0), m_4C(0),
	  m_50(), m_5C(0), m_60(), m_6C(0), m_70(), m_7C(0), m_80(), m_8C(0),
	  m_90(0.0f), m_94(100.0f), m_98(1000.0f), m_9C(1.0f), m_A0(1.0f), m_A4(0.0f), m_A8(1.0f), m_AC(1.0f),
	  m_B0(2), m_B4(-1)
{
}
