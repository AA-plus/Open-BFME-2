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
