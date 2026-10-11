// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?parseConditionState@W3DScriptedModelDrawModuleData@@SAXPAVINI@@PAX1PBX@Z,
// retail 0x000C8914..0x000C8B83 (623 bytes, EH). WorldBuilder names it
// W3DScriptedModelDrawModuleData::parseConditionState; Zero Hour's
// W3DModelDrawModuleData::parseConditionState (W3DModelDraw.cpp) is the
// semantic donor, reduced in BFME 2 to its normal (0) and default (1)
// forms. Each form validates against the module data's 0xFC-byte state
// records (vector at +0x18) and default index (+0x4C) and throws Zero
// Hour's asset errors as INIException(3, ...); then the state's fields are
// read through the condition-state field table (retail 0x00BCAB20), its
// model list (+0x4C of the record) is required and dropped when it names
// "None", the condition bits (0x4C bytes, parsed by the rowed 0x000B937E
// and compared by 0x00045473) are copied in and the record is appended.
// The record's rowed constructor 0x000C47F4, assignment 0x000C27B0 and
// destructor 0x000C2980 carry address-derived names, so a stack view
// binds them. The table and record names are descriptive.
#include "ascii_string.h"
#include <string.h>
#include <vector>

struct FieldParse;

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);			// 0x0002DEED
	void initFromINI(void *what, const FieldParse *parseTable);	// 0x0002DE78
};

class INIException
{
public:
	char *mFailureMessage;
	int mErrorCode;
	INIException(int code, const char *format, ...);			// 0x0002F681
	INIException(const INIException &);
	~INIException();
};

// The condition-state field table (Model, Skeleton, ..., TurretArtPitch).
extern const FieldParse TheScriptedModelConditionStateFieldParse[];

// The 0x4C-byte condition bit set.
class Rva000B937E { public: void rva000B937E(INI *ini, void *description); };
bool Rva00045473Equal(const void *a, const void *b);
struct ScriptedModelConditionFlags
{
	unsigned int m_bits[19];

	void parse(INI *ini) { ((Rva000B937E *)this)->rva000B937E(ini, 0); }
	bool any() const
	{
		for (unsigned int i = 0; i < 19; ++i)
			if (m_bits[i])
				return true;
		return false;
	}
};

// The 252-byte state record: the condition bits, then the model names.
struct BfmePod252
{
	unsigned char m_bytes[252];
};
class Rva000C38F8 { public: Rva000C38F8(); };
class Rva000C27B0 { public: Rva000C27B0 &operator=(const Rva000C27B0 &that); };
class Rva000C2980 { public: ~Rva000C2980(); };
struct ScriptedModelConditionInfo
{
	__forceinline ScriptedModelConditionInfo() { ((Rva000C38F8 *)this)->Rva000C38F8::Rva000C38F8(); }
	__forceinline ~ScriptedModelConditionInfo() { ((Rva000C2980 *)this)->~Rva000C2980(); }
	ScriptedModelConditionInfo &operator=(const BfmePod252 &that)
	{
		*(Rva000C27B0 *)this = *(const Rva000C27B0 *)&that;
		return *this;
	}

	// The model names: a vector<AsciiString> the record's own constructor
	// and destructor manage.
	_STL::vector<AsciiString> &models() { return *(_STL::vector<AsciiString> *)m_models; }

	ScriptedModelConditionFlags m_flags;			// +0x00
	unsigned char m_models[sizeof(_STL::vector<AsciiString>)];	// +0x4C
	unsigned char m_tail[252 - 0x4c - sizeof(_STL::vector<AsciiString>)];
};

class W3DScriptedModelDrawModuleData
{
public:
	static void parseConditionState(INI *ini, void *instance, void *store, const void *userData);

	unsigned char m_pad00[0x18];
	_STL::vector<BfmePod252> m_conditionStates;		// +0x18
	unsigned char m_pad24[0x4c - 0x24];
	int m_defaultState;								// +0x4C
};

void W3DScriptedModelDrawModuleData::parseConditionState(INI *ini, void *instance, void *store, const void *userData)
{
	ScriptedModelConditionInfo info;
	ScriptedModelConditionFlags conditions;
	memset(&conditions, 0, sizeof(conditions));
	W3DScriptedModelDrawModuleData *self = (W3DScriptedModelDrawModuleData *)instance;
	switch ((unsigned int)userData)
	{
	case 0:
		if (self->m_defaultState >= 0)
			info = self->m_conditionStates[self->m_defaultState];
		conditions.parse(ini);
		if (self->m_defaultState < 0 && self->m_conditionStates.empty() && conditions.any())
			throw INIException(3, "*** ASSET ERROR: when not using DefaultConditionState, the first ConditionState must be for NONE (%s)", "");
		if (!conditions.any() && self->m_defaultState >= 0)
			throw INIException(3, "*** ASSET ERROR: you may not specify both a Default state and a Conditions=None state");
		for (_STL::vector<BfmePod252>::iterator it = self->m_conditionStates.begin(); it != self->m_conditionStates.end(); ++it)
		{
			if (Rva00045473Equal(&conditions, &*it))
				throw INIException(3, "*** ASSET ERROR: duplicate condition states are not currently allowed (%s)", "");
		}
		break;
	case 1:
		if (self->m_defaultState >= 0)
			throw INIException(3, "*** ASSET ERROR: you may have only one default state!");
		if (ini->getNextTokenOrNull(0))
			throw INIException(3, "*** ASSET ERROR: unknown keyword");
		if (!self->m_conditionStates.empty())
			throw INIException(3, "*** ASSET ERROR: when using DefaultConditionState, it must be the first state listed (%s)\n", "");
		self->m_defaultState = self->m_conditionStates.size();
		break;
	}
	ini->initFromINI(&info, TheScriptedModelConditionStateFieldParse);
	if (info.models().size() == 0)
		throw INIException(3, "*** ASSET ERROR: you must specify a model name");
	if (info.models()[0].isNone())
		info.models().erase(info.models().begin(), info.models().end());
	info.m_flags = conditions;
	self->m_conditionStates.push_back(*(const BfmePod252 *)&info);
}
