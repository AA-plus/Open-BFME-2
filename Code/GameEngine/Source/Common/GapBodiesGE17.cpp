// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (seventeenth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees use the ledger's
// existing spellings.

// --- 0x00595020 (59B) / 0x0059505B (46B): weighted sums of flag bits.
class Rva00595020
{
public:
	int rva00595020(unsigned char flags);
	int rva0059505B(unsigned char flags);
};

int Rva00595020::rva00595020(unsigned char flags)
{
	int weight = 0;
	if (flags & 0x01)
		weight += 1;
	if (flags & 0x02)
		weight += 2;
	if (flags & 0x04)
		weight += 3;
	if (flags & 0x08)
		weight += 10;
	if (flags & 0x10)
		weight += 1;
	if (flags & 0x20)
		weight += 2;
	if (flags & 0x40)
		weight += 20;
	return weight;
}

int Rva00595020::rva0059505B(unsigned char flags)
{
	int weight = 2;
	if (flags & 0x01)
		weight = 3;
	if (flags & 0x02)
		weight += 1;
	if (flags & 0x04)
		weight += 1;
	if (flags & 0x20)
		weight += 5;
	if (flags & 0x40)
		weight += 5;
	return weight;
}

// --- vtable 0x00C4ED70 over a zero +0x08 and a cleared +0x0C; 0x002534B1 (17B): its field table (VA 0x00BF00A0) for the parser;
// 0x002534C2 (60B): the INI factory building one with that table.
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *table, unsigned int offset);	// 0x0002BC6E
};

class INI
{
public:
	void initFromINIMultiProc(void *what, void (*proc)(MultiIniFieldParse &p));	// 0x0002DEB5
};

extern const FieldParse s_Rva002534B1FieldParse[];			// VA 0x00BF00A0

class Rva0025349C
{
public:
	Rva0025349C() : m_08(0.0f), m_0C(0) {}
	virtual ~Rva0025349C() {}
	static void rva002534B1(MultiIniFieldParse &p);
	static Rva0025349C *rva002534C2(INI *ini);
private:
	int m_04;
	float m_08;
	int m_0C;
};

void Rva0025349C::rva002534B1(MultiIniFieldParse &p)
{
	p.add(s_Rva002534B1FieldParse, 0);
}

Rva0025349C *Rva0025349C::rva002534C2(INI *ini)
{
	Rva0025349C *data = new Rva0025349C;
	if (ini)
		ini->initFromINIMultiProc(data, rva002534B1);
	return data;
}
