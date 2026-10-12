// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?ParseLivingWorldCampaignBlock@LivingWorldCampaign@@SAXPAVINI@@@Z
// @0x0052D04E 200B: the "LivingWorldCampaign" INI block parser.
// Target evidence: the block-parse registration at VA 0x00DD19A0
// (Rva007ABBF6BlockParseInits.cpp) binds token "LivingWorldCampaign" to
// 0x0052D04E; retail literal 0x00C68998 "ParseLivingWorldCampaignBlock::
// Campaign name expected" thrown as INIException(3) through
// __TI1?AVINIException@@ 0x008FE2FC. Body: skip when TheCampaignManager
// (0x00A02D6C) is null, read the name with getNextToken(0), new a 0x50-byte
// campaign through its constructor 0x0052CF0F (pushes the name), fill it from
// field table 0x008688A8 via INI::initFromINI, run 0x0052C0C8 on it, then hand
// it to the manager through the 16-byte forwarder 0x00289218 (rowed under an
// address name; its other caller is 0x002892CF).
// Name and file from the WorldBuilder build (LivingWorldCampaign.cpp,
// assert line 523, the null-manager DEBUG compiled out of retail); the
// constructor's class follows from this allocation and is a structural
// inference, the 0x0052C0C8 step keeps an address name.
#include "ascii_string.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *what, const FieldParse *parseTable);
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};

class ModuleData;

class Rva00289218
{
public:
	void rva00289218(const ModuleData *data);
};

class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;

extern const FieldParse LivingWorldCampaignFields[];

// A campaign's 184-byte mission records (+0x0C begin, +0x10 end); the
// byte at +0xB4 marks a record the step below selects.
struct LivingWorldCampaignRecord
{
	char m_pad00[0xB4];
	bool m_selected;						// +0xB4
	char m_padB5[0xB8 - 0xB5];
};

struct LivingWorldCampaignRecords
{
	LivingWorldCampaignRecord *m_start;
	LivingWorldCampaignRecord *m_finish;
	LivingWorldCampaignRecord *m_endOfStorage;

	unsigned int size() const { return m_finish - m_start; }
	LivingWorldCampaignRecord &operator[](unsigned int i) { return m_start[i]; }
};

class LivingWorldCampaign
{
public:
	LivingWorldCampaign(const AsciiString &name);
	void rva0052C0C8();

	static void ParseLivingWorldCampaignBlock(INI *ini);

private:
	char m_pad00[0x0C];
	LivingWorldCampaignRecords m_records;	// +0x0C
	int m_currentIndex;						// +0x18
	char m_pad1C[0x50 - 0x1C];
};

void LivingWorldCampaign::ParseLivingWorldCampaignBlock(INI *ini)
{
	if (TheCampaignManager == 0)
		return;

	AsciiString name(ini->getNextToken(0));
	if (name.getLength() == 0)
		throw INIException(3, "ParseLivingWorldCampaignBlock::Campaign name expected");

	LivingWorldCampaign *campaign = new LivingWorldCampaign(name);
	ini->initFromINI(campaign, LivingWorldCampaignFields);
	campaign->rva0052C0C8();
	((Rva00289218 *)TheCampaignManager)->rva00289218((const ModuleData *)campaign);
}

// LivingWorldCampaign::rva0052C0C8, retail 0x0052C0C8 (81 B; WB 0x0133BFA0,
// unnamed, LivingWorldCampaign.cpp): the current index (+0x18) becomes the
// first record whose +0xB4 byte is set, else the last record. Record stride
// 0xB8 and both offsets are retail's; the names are structural.
void LivingWorldCampaign::rva0052C0C8()
{
	m_currentIndex = m_records.size() - 1;
	for (unsigned int i = 0; i < m_records.size(); ++i)
	{
		if (m_records[i].m_selected)
		{
			m_currentIndex = i;
			break;
		}
	}
}
