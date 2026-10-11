// cl: /O1 /MD /EHsc
// ??1Rva001505CD@@UAE@XZ, retail 0x001505CD..0x00150659 (140 bytes, EH):
// the destructor of the class whose scalar deleting destructor is
// 0x00150A5B (table 0x00BD3A34). It erases its "Sas" registration (rowed
// 0x001532E1), then its parts die as retail's unwind map lists them: the
// four-interface member at +0xB8 (out-of-line copy 0x0014DC76), the +0x5C
// member (rowed 0x0015058E), the three +0x44/+0x2C/+0x14 members (rowed
// 0x00150558), the lone interface at +0x10, the three-interface member at
// +4 (rowed 0x0014DC9E) and the interface base. Every interface restores
// table 0x00BC6F24 (unwind copy 0x000E14BD); the two compound members store
// no table of their own (novtable views). Identities are not established.
void Rva001532E1Erase(const char *name);

class Gen_uw_000e14bd
{
public:
	virtual void s0();
	~Gen_uw_000e14bd() {}
};

class __declspec(novtable) Rva0014DC9E : public Gen_uw_000e14bd
{
public:
	virtual ~Rva0014DC9E() {}
private:
	Gen_uw_000e14bd m_4;
	Gen_uw_000e14bd m_8;
};

class __declspec(novtable) Rva0014DC76 : public Gen_uw_000e14bd
{
public:
	virtual ~Rva0014DC76() {}
private:
	Gen_uw_000e14bd m_4;
	Gen_uw_000e14bd m_8;
	Gen_uw_000e14bd m_C;
};

class Rva00150558
{
public:
	virtual ~Rva00150558();
private:
	unsigned char m_pad04[0x18 - 4];
};

class Rva0015058E
{
public:
	virtual ~Rva0015058E();
private:
	unsigned char m_pad04[0x5C - 4];
};

class Rva001505CD : public Gen_uw_000e14bd
{
public:
	virtual ~Rva001505CD();
private:
	Rva0014DC9E m_04;
	Gen_uw_000e14bd m_10;
	Rva00150558 m_14;
	Rva00150558 m_2C;
	Rva00150558 m_44;
	Rva0015058E m_5C;
	Rva0014DC76 m_B8;
};

Rva001505CD::~Rva001505CD()
{
	Rva001532E1Erase("Sas");
}
