// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?rva000C199D@Rva000C199DInterface@@..., retail 0x000C199D (38 bytes, RET 4), slot 33 of the
// model-draw table 0x007CC588 reached through the +0x0C interface (complete object this-0x0C,
// as for rva000BBFD6): copies the given list into the interface's vector at +0x2C (rowed
// operator= 0x000C091B) and re-runs the complete object's slot 64 with the +0x08 value, 1 and
// the +0x0C value. Names stay address-derived.
#include <vector>

struct Rva00B6CF1;

namespace _STL {
template <> vector<Rva00B6CF1> &vector<Rva00B6CF1>::operator=(const vector<Rva00B6CF1> &other);
}

class Rva000C199DComplete
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual void s44();
	virtual void s45();
	virtual void s46();
	virtual void s47();
	virtual void s48();
	virtual void s49();
	virtual void s50();
	virtual void s51();
	virtual void s52();
	virtual void s53();
	virtual void s54();
	virtual void s55();
	virtual void s56();
	virtual void s57();
	virtual void s58();
	virtual void s59();
	virtual void s60();
	virtual void s61();
	virtual void s62();
	virtual void s63();
	virtual void slot64(int first, int second, int third);	// +0x100
};

class Rva000C199DInterface
{
public:
	void rva000C199D(const _STL::vector<Rva00B6CF1> &values);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	unsigned char m_pad10[0x2C - 0x10];
	_STL::vector<Rva00B6CF1> m_values;		// +0x2C
};

void Rva000C199DInterface::rva000C199D(const _STL::vector<Rva00B6CF1> &values)
{
	m_values = values;
	reinterpret_cast<Rva000C199DComplete *>(reinterpret_cast<char *>(this) - 0xC)->slot64(m_08, 1, m_0C);
}
