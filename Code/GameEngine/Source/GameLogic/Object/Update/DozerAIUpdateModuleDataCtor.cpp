// cl: /DNDEBUG /MD
//
// ??0DozerAIUpdateModuleData@@QAE@XZ, retail 0x00488A81, 36 bytes.
// ModuleData ctor over the pinned TransportAIUpdateModuleData base
// (0x26E5D7, 0x64 bytes per the SiegeAI row): installs vtable 0x00C4B6C8
// explicitly (novtable) and zeroes three floats at +0x64/+0x68/+0x6C via an
// xmm0-homed fzero local (/arch:SSE emits retail xorps+movss). Class size
// 0x70 proven by the DozerAIUpdate data factory (news 0x70, sole caller at
// 0x24CDD9). Row supersedes the ctor pin.

extern "C" const void *const vtbl_00C4B6C8[];  // folded, 3 classes; via ??_7AnimalAIUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4B6C8=??_7AnimalAIUpdateModuleData@@6B@")

class INI
{
public:
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

struct FieldParse
{
	const char *token;
	void (__cdecl *parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};

// Retail VA 0x00C4B748 (.rdata, file offset 0x0084B348): the dozer's three module
// data fields - RepairHealthPercentPerSecond through the rowed
// INI::parsePercentToReal (0x0002F1BA) at +0x64, BoredTime through the rowed
// INI::parseDurationReal (0x00338B0A) at +0x68 and BoredRange through the rowed
// INI::parseReal (0x0002EFC0) at +0x6C - then the zero sentinel. The three
// offsets are the same words the ctor above zeroes, and the 64-byte extent is the
// ledger's own bound.
// Symbol ?g_00C4B748@@3QBUFieldParse@@B, transcribed below.
extern const struct FieldParse g_00C4B748[] =
{
	{ "RepairHealthPercentPerSecond", &INI::parsePercentToReal, 0, 0x64 },
	{ "BoredTime",                    &INI::parseDurationReal,  0, 0x68 },
	{ "BoredRange",                   &INI::parseReal,          0, 0x6C },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class __declspec(novtable) TransportAIUpdateModuleData
{
public:
	TransportAIUpdateModuleData();
	virtual ~TransportAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x00 vptr (novtable: no compiler install here).
	// Remainder is opaque (0x60 bytes); only the 0x64 size matters.
	unsigned char m_opaque[0x60];
};

class __declspec(novtable) DozerAIUpdateModuleData : public TransportAIUpdateModuleData
{
public:
	DozerAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x64/+0x68/+0x6C float zeros (end at the rowed 0x70 instance size).
	float m_64;
	float m_68;
	float m_6C;
};

// ??0DozerAIUpdateModuleData@@QAE@XZ @0x00488A81
DozerAIUpdateModuleData::DozerAIUpdateModuleData()
	: TransportAIUpdateModuleData()
{
	float fzero = 0.0f;
	*(unsigned int *)this = ((unsigned int)vtbl_00C4B6C8);
	m_64 = fzero;
	m_68 = fzero;
	m_6C = fzero;
}

// ?buildFieldParse@DozerAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00488AA5
void DozerAIUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	TransportAIUpdateModuleData::buildFieldParse(parse);
	parse.add(g_00C4B748, 0);
}
