// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Table-reached INI block parsers from .text gaps no ledger row covers
// (seat-3 batch E; see GapBodiesS3A.cpp). Retail bytes establish every shape;
// field names are retail's string literals. Unrowed parse callbacks are
// pinned under address-derived names.

class INI;

typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);	// 0x0002DE78
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);	// 0x0002EFC0
	static void Rva0033940F_Parse(INI *ini, void *instance, void *store, const void *userData);	// 0x0033940F
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);	// 0x0002F11E
	static void parseColorInt(INI *ini, void *instance, void *store, const void *userData);		// 0x0002F3FE
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);			// 0x0002EF56
};

void rva00423FD8(INI *ini, void *instance, void *store, const void *userData);	// 0x00423FD8
void rva00425842(INI *ini, void *instance, void *store, const void *userData);	// 0x00425842
void parseFormationSelectionCriteriaRva00424185(INI *ini, void *instance, void *store, const void *userData);	// 0x00424185
void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);	// 0x00361CA5

class Rva0022AD10Subsystem;
extern Rva0022AD10Subsystem *TheFormationAssistant;

// --- 0x00425B90 (302B): the formation assistant's INI block, parsed through
// a table built on the stack into TheFormationAssistant.
void rva00425B90(INI *ini)
{
	FieldParse dataFieldParse[] =
	{
		{ "DefaultPreviewObject", INI::Rva0033940F_Parse, 0, 0x0C },
		{ "RowPadding", INI::parseReal, 0, 0x24 },
		{ "ColumnPadding", INI::parseReal, 0, 0x28 },
		{ "FacingArrowHeadTemplate", INI::Rva0033940F_Parse, 0, 0x10 },
		{ "FacingArrowBodyTemplate", INI::Rva0033940F_Parse, 0, 0x14 },
		{ "FacingArrowBaseTemplate", INI::Rva0033940F_Parse, 0, 0x18 },
		{ "ActivationDragDistance", INI::parseReal, 0, 0x2C },
		{ "ActivationTime", INI::parseReal, 0, 0x30 },
		{ "UnitDefinition", rva00423FD8, 0, 0 },
		{ "FormationTemplate", rva00425842, 0, 0 },
		{ "FormationSelection", parseFormationSelectionCriteriaRva00424185, 0, 0 },
		{ "ValidObjectFilter", iniParseObjectFilter, 0, 0x20 },
		{ 0, 0, 0, 0 }
	};
	ini->initFromINI(TheFormationAssistant, dataFieldParse);
}

// --- 0x005742A1 / 0x0057A260 (18B each): table slots parsing an INI block
// into this object through a static field table (retail 0x00C6E36C and
// 0x00C6EE98; the field names are retail's).
class GlobalLanguage
{
public:
	static void parseFontDesc(INI *ini, void *instance, void *store, const void *userData);	// 0x0037691C
};

class Rva005742A1
{
public:
	virtual void rva005742A1(INI *ini);
private:
	static const FieldParse s_fieldParseTable[];
};

const FieldParse Rva005742A1::s_fieldParseTable[] =
{
	{ "Title", INI::parseAsciiString, 0, 0x08 },
	{ "Help", INI::parseAsciiString, 0, 0x0C },
	{ 0, 0, 0, 0 }
};

void Rva005742A1::rva005742A1(INI *ini)
{
	ini->initFromINI(this, s_fieldParseTable);
}

class Rva0057A260
{
public:
	virtual void rva0057A260(INI *ini);
private:
	static const FieldParse s_fieldParseTable[];
};

const FieldParse Rva0057A260::s_fieldParseTable[] =
{
	{ "ItemFont", GlobalLanguage::parseFontDesc, 0, 0x08 },
	{ "ItemNormalColor", INI::parseColorInt, 0, 0x14 },
	{ "ItemImportantColor", INI::parseColorInt, 0, 0x18 },
	{ "ItemNewColor", INI::parseColorInt, 0, 0x1C },
	{ "ItemVerticalSpacing", INI::parseReal, 0, 0x20 },
	{ 0, 0, 0, 0 }
};

void Rva0057A260::rva0057A260(INI *ini)
{
	ini->initFromINI(this, s_fieldParseTable);
}

// --- 0x004E12C4 / 0x004E12EF / 0x004E1342 (19B each): field-parse callbacks
// parsing a nested block into their store through the rowed tables 0x00C616C0
// (LivingWorldCampaignObjects' SpawnArmy table), 0x00C61830 and 0x00C61884.
class SpawnArmy
{
public:
	static const FieldParse m_fieldParseTable[];			// 0x00C616C0
};

extern const FieldParse g_00C61830;
extern const FieldParse g_00C61884;

void rva004E12C4(INI *ini, void *instance, void *store, const void *userData)
{
	ini->initFromINI(store, SpawnArmy::m_fieldParseTable);
}

void rva004E12EF(INI *ini, void *instance, void *store, const void *userData)
{
	ini->initFromINI(store, &g_00C61830);
}

void rva004E1342(INI *ini, void *instance, void *store, const void *userData)
{
	ini->initFromINI(store, &g_00C61884);
}

// --- 0x005CB288 / 0x005E3955 / 0x005E9F80 (18B each): more table slots
// parsing an INI block into this object through static field tables (retail
// 0x00C74D20, 0x00C77C10 and 0x00C780D4; the field names are retail's).
class Rva005CB288
{
public:
	virtual void rva005CB288(INI *ini);
private:
	static const FieldParse s_fieldParseTable[];
};

const FieldParse Rva005CB288::s_fieldParseTable[] =
{
	{ "BuildPlotsTitle", INI::parseAsciiString, 0, 0x08 },
	{ "BuildPlotsHelp", INI::parseAsciiString, 0, 0x0C },
	{ "ArmoryPointsTitle", INI::parseAsciiString, 0, 0x10 },
	{ "ArmoryPointsHelp", INI::parseAsciiString, 0, 0x14 },
	{ "CommandPointsTitle", INI::parseAsciiString, 0, 0x18 },
	{ "CommandPointsHelp", INI::parseAsciiString, 0, 0x1C },
	{ 0, 0, 0, 0 }
};

void Rva005CB288::rva005CB288(INI *ini)
{
	ini->initFromINI(this, s_fieldParseTable);
}

class Rva005E3955
{
public:
	virtual void rva005E3955(INI *ini);
private:
	static const FieldParse s_fieldParseTable[];
};

const FieldParse Rva005E3955::s_fieldParseTable[] =
{
	{ "BackButtonTooltip", INI::parseAsciiString, 0, 0x08 },
	{ 0, 0, 0, 0 }
};

void Rva005E3955::rva005E3955(INI *ini)
{
	ini->initFromINI(this, s_fieldParseTable);
}

class Rva005E9F80
{
public:
	virtual void rva005E9F80(INI *ini);
private:
	static const FieldParse s_fieldParseTable[];
};

const FieldParse Rva005E9F80::s_fieldParseTable[] =
{
	{ "BattleRoundsPerStep", INI::parseInt, 0, 0x08 },
	{ 0, 0, 0, 0 }
};

void Rva005E9F80::rva005E9F80(INI *ini)
{
	ini->initFromINI(this, s_fieldParseTable);
}

// --- 0x003F9CD2 (54B): the pupil / eye-decal anim-object block: build a
// fresh 0x74-byte 0x003F9C11 record, parse it through the static table
// 0x00C37668 (retail's field names) and hand it to TheLivingWorldManager
// (+0x2C4).
class Rva003F9C11
{
public:
	Rva003F9C11() throw();									// 0x003F9C11
	static const FieldParse s_fieldParseTable[];
private:
	char m_pad[0x74];
};

const FieldParse Rva003F9C11::s_fieldParseTable[] =
{
	{ "PupilAnimObject", INI::parseAsciiString, 0, 0x04 },
	{ "PupilBeamAnimObject", INI::parseAsciiString, 0, 0x08 },
	{ "EyeDecalAnimObject", INI::parseAsciiString, 0, 0x0C },
	{ "EyeDecalBeamAnimObject", INI::parseAsciiString, 0, 0x10 },
	{ 0, 0, 0, 0 }
};

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

struct Rva003F9CD2ManagerView
{
	char m_pad[0x2C4];
	Rva003F9C11 *m_2C4;										// +0x2C4
};

void rva003F9CD2(INI *ini)
{
	Rva003F9C11 *record = new Rva003F9C11;
	ini->initFromINI(record, Rva003F9C11::s_fieldParseTable);
	((Rva003F9CD2ManagerView *)TheLivingWorldManager)->m_2C4 = record;
}
