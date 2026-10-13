// cl: /MD /EHsc
//
// ?Rva0035D6F9Parse@@YAXPAVINI@@PAVRva0035D6F9Holder@@@Z @0x0035D6F9 81B: factory news 0x34,
// calls ctor ??0ScoreScaleUpTransition at 0x0035D6B8, parses SlaveAttack table 0x0086BB18 via rowed
// INI::initFromINI 0x0002DE78, stores via holder+0x10 setter pinned at 0x005F69CE.
// Same 81B shape as 0x0035E327/0x0035EEA7; vtable 0x00816510 via ctor; chain from 0x0035D6B8.
// Opaque address-derived names; base layout from Rva001DBAA4Ctor.cpp.
struct FieldParse;
extern const struct FieldParse SlaveAttackFieldTable;

// Retail 0x00C6BB18 (RVA 0x0086BB18) is the all-zero 16-byte empty
// FieldParse entry already defined there as g_emptyFieldParseTable. Keep one
// storage definition and resolve this consumer's distinct decoration to it.
#pragma comment(linker, "/alternatename:?SlaveAttackFieldTable@@3UFieldParse@@B=?g_emptyFieldParseTable@@3QBHB")

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	int m_4;
	bool m_8;
	bool m_9;
	bool m_A;
	int m_C;
};

class ScoreScaleUpTransition : public Rva001DBAA4
{
public:
	virtual ~ScoreScaleUpTransition();
	ScoreScaleUpTransition();
	char m_pad10[0x10];
	int m_20;
	char m_pad24[0x34 - 0x24];
};

typedef char ScoreScaleUpTransitionSizeMatchesRetail[(sizeof(ScoreScaleUpTransition) == 0x34) ? 1 : -1];

class Rva0035D6F9Holder
{
public:
	// Pinned as ?set@Rva0035D6F9Holder@@QAEXPAVRva0035D53C@@@Z (the class's
	// former placeholder name), which Player.cpp's alternatename binds.
	void set(class Rva0035D53C *obj);
};

void __cdecl Rva0035D6F9Parse(INI *ini, Rva0035D6F9Holder *holder)
{
	ScoreScaleUpTransition *obj = new ScoreScaleUpTransition;
	ini->initFromINI(obj, &SlaveAttackFieldTable);
	holder->set((Rva0035D53C *)obj);
}
