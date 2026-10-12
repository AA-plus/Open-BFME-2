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
