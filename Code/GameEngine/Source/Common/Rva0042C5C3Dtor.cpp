// cl: /O1 /MD /EHsc
// ??1Rva0042C5C3@@UAE@XZ, retail 0x0042C5C3..0x0042C677 (180 bytes, EH):
// the destructor of the 0x3C-byte impl built by ??0Rva0042C5C3 (0x0042C693;
// opaque pin of its scalar deleting destructor). Own tables 0x00C3C6E4,
// 0x00C3C6DC (+4), 0x00C3C6D4 (+8) and 0x00C3C6D0 (+0xC). With
// TheLivingWorldLogic present it takes its +8 and +4 subobjects off the
// logic's lists at +0x1C and +0x4C (rowed erase 0x002B7250), unregisters this
// from its +0x20 owner (rowed 0x0042CAEB), then its parts die as retail's
// unwind map lists them: the +0x38 owned-pointer cell (rowed clear
// 0x0042C1DF), the +0x34 cell (rowed 0x000AD6F4), the base at +0xC (rowed
// 0x00574A8A), the StrategicHUD cell base at +0x14 (rowed 0x0042E00F) and
// the three interface bases whose inline destructors restore 0x00C62A20,
// 0x00BED658 and 0x00BDBA74 (out-of-line copies 0x004EDFFF, 0x00238D97 and
// 0x00429191). Identities are not established.
class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *who);
};

class LivingWorldLogic
{
public:
	unsigned char m_pad00[0x1C];
	Rva002B7250 m_list1C;
	unsigned char m_pad1D[0x4C - 0x1D];
	Rva002B7250 m_list4C;
};

extern LivingWorldLogic *TheLivingWorldLogic;

class Rva0042CBB6
{
public:
	void rva0042CAEB(int who);
};

class Rva000AD6F4
{
public:
	~Rva000AD6F4();
private:
	void *m_ptr;
};

class Rva0042C1DF
{
public:
	~Rva0042C1DF() { clear(); }
	void clear();
private:
	void *m_ptr;
};

class Rva0042DFF5
{
public:
	~Rva0042DFF5();
private:
	void *m_ptr;
};

class Rva00574A8A
{
public:
	virtual ~Rva00574A8A();
private:
	int m_04;
};

class Gen_uwm_00429191
{
public:
	virtual void s0();
	~Gen_uwm_00429191() {}
};

class Gen_uwm_00238d97
{
public:
	virtual void s0();
	~Gen_uwm_00238d97() {}
};

class Gen_uwm_004edfff
{
public:
	virtual void s0();
	~Gen_uwm_004edfff() {}
};

class Rva0042C5C3 : public Gen_uwm_00429191, public Gen_uwm_00238d97, public Gen_uwm_004edfff,
	public Rva0042DFF5, public Rva00574A8A
{
public:
	virtual ~Rva0042C5C3();
private:
	int m_18;
	int m_1C;
	Rva0042CBB6 *m_owner;			// +0x20
	unsigned char m_pad24[0x34 - 0x24];
	Rva000AD6F4 m_34;
	Rva0042C1DF m_38;
};

Rva0042C5C3::~Rva0042C5C3()
{
	if (TheLivingWorldLogic)
	{
		TheLivingWorldLogic->m_list1C.rva002B7250((CreateAHeroData *)static_cast<Gen_uwm_004edfff *>(this));
		TheLivingWorldLogic->m_list4C.rva002B7250((CreateAHeroData *)static_cast<Gen_uwm_00238d97 *>(this));
	}
	m_owner->rva0042CAEB((int)this);
}
