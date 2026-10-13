// cl: -GR- -EHsc-
// ??0AptOnlineOpenPlay@@QAE@H@Z @0x005BA1FD 55B: composing constructor. Builds
// the base with (0, arg) through the pinned base ctor, installs the three
// polymorphic tables (all DIR32, copied from retail by the gate), publishes
// this to the 0xE06544 global when clear, and returns this. Targets from
// retail REL32/DIR32; table symbols declared never defined.
class Rva005BA1FDBase
{
public:
	Rva005BA1FDBase(int x, int y);
	virtual void BaseVirt();
};

struct Rva005BA1FDM60
{
	virtual void M60Virt();
	char pad[8];
};

struct Rva005BA1FDM6C
{
	virtual void M6CVirt();
};

class AptOnlineOpenPlay;
// g_rva005BA1FDInst is only an alias of the owned global g_Va00E06544 (ledger names column); this unit reads the owner through its own view type.
extern int g_Va00E06544;
#define g_rva005BA1FDInst (*(AptOnlineOpenPlay * *)&g_Va00E06544)

class AptOnlineOpenPlay : public Rva005BA1FDBase
{
	char pad[0x60 - 4];
	Rva005BA1FDM60 m_60;
	Rva005BA1FDM6C m_6c;

public:
	AptOnlineOpenPlay(int arg);
	virtual void BoxVirt();
};

AptOnlineOpenPlay::AptOnlineOpenPlay(int arg)
	: Rva005BA1FDBase(arg, 0)
{
	if (g_rva005BA1FDInst == 0)
		g_rva005BA1FDInst = this;
}
