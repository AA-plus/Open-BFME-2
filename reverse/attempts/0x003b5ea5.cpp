// ?ParseAction@ScriptAction@@KAPAV1@AAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// partial score=0.96 date=2026-10-11
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// BANK (partial 0.96, 2026-10-11, claude-opus-5-5): ParseAction in its Scripts.cpp
// proxy home Code/GameEngine/Source/GameLogic/ScriptEngine/TemplateGetParameterType.cpp.
// Deltas vs the old .93 bank, each measured: (1) Template::getParameterType defined
// earlier in the TU (cl then keeps the parameter in EDX across the call and the
// template in EBX): first 0x190 bytes exact; (2) TU converted from its private
// StringBase view to reference/shims/bfme2_ascii with /O1 -- the three existing rows
// (0x3B27A3, 0x3B4343, 0x3B4A94) stay exact and the alternatename hatch goes away;
// (3) ParseAction needs an EBP frame retail has without EH: /Oy- for the TU breaks
// getParameterType (27B), so only ParseAction sits under #pragma optimize("y", off);
// (4) case 0xfe deletes through Parameter::deleteInstance (test/releaseBuffer/free);
// (5) cross-jump survivors give source-order constraints 0x1b2<0x24<0x12-group,
// 0x5d<0x1a<0x7a, 0x0e<0xd2, 0x2d<0x55<0x52, 0xb9<0x11 (null-store blocks keep the
// first copy, ctor tails the last); every order obeying them scores the same.
// Remaining: the 0x1a/0x1b body is laid out right after case 0x24 (retail: between
// 0x55 and 0x52) and the body is 1817 vs 1818 B. Case order, label order, split
// bodies, EH/nothrow variants did not move it.
//
// ?getParameterType@Template@@QBE?AW4ParameterType@Parameter@@H@Z, retail 0x003B27A3 (24 bytes).
// Template::getParameterType shared by ActionTemplate and ConditionTemplate
// (both derive from Template in ZH Scripts.h; BFME2 callers pass both types:
// 0x003B4343 via getActionTemplate, 0x003B4A94/0x003B6D92 via getConditionTemplate).
// Layout from ScriptEngine_initTemplateNameKeys.cpp (m_numParameters +0x48,
// m_parameters +0x4C, sizeof 0x80). Donor ZH Scripts.cpp Template::getParameterType
// with DEBUG_CRASH compiled out (/DNDEBUG) returns Parameter::INT (0) out of range,
// matching retail xor eax,eax.
//
// ?setActionType@ScriptAction@@QAEXW4ScriptActionType@1@@Z, retail 0x003B4343
// (137 bytes), and ?setConditionType@Condition@@QAEXW4ConditionType@1@@Z,
// retail 0x003B4A94 (137 bytes). BFME1 donor Scripts.cpp
// ScriptAction::setActionType / Condition::setConditionType: free the old
// parameters, store the type, look the template up through the pinned
// ScriptEngine::getActionTemplate 0x00203926 / getConditionTemplate
// 0x00203941 and new one Parameter per template slot. Retail deltas: the
// delete inlines to the rowed releaseBuffer 0x00036410 plus ::operator delete
// (not a pooled deleteInstance), Parameter is 0x28 bytes with its AsciiString
// at +0x10. Retail keeps the new parameter pointer in edx across the
// getParameterType call, which cl only does when that callee was compiled
// earlier in the same TU, so all three bodies share this file as they shared
// retail's Scripts.cpp. ScriptAction caller 0x003B5413 is its ctor (vtable
// 0x0081F3FC).

#include "ascii_string.h"

// Retail registers no unwind state for the copied key name: its literal
// compares cannot throw.
template<> int StringBase<char>::compare(const char *) const throw();
static inline int compareLiteral(const AsciiString &s, const char *literal)
{
	return ((const StringBase<char> *)&s)->compare(literal);
}

typedef int Int;
typedef bool Bool;
typedef unsigned short DataChunkVersionType;
enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

struct DataChunkInfo
{
	AsciiString label;
	AsciiString parentLabel;
	DataChunkVersionType version;
	Int dataSize;
};

class DataChunkInput
{
public:
	Int readInt();
	NameKeyType readNameKey();
};

void __cdecl operator delete(void *ptr);

// Parameter's by-value string setter (ZH friend_setString); the ledger names
// the body by address only, so Parameter reaches it through this base.
class Rva00333B02
{
public:
	void rva00333B02(AsciiString value);
};

// 0x003B27F8: the OBJECT_TYPE -> object-type-list retype, called on the
// parameter (the ledger spells its class by the address of its template).
class Rva0034FF50
{
public:
	void checkAndSet();
};

class Parameter : public Rva00333B02
{
public:
	enum ParameterType
	{
		INT = 0,
		REAL = 1,
		BOOLEAN = 8,
		SIDE = 11,
		OBJECT_TYPE = 15,
		AI_MOOD = 20
	};
	Parameter(ParameterType type, int val = 0) throw();
	__forceinline ~Parameter() {}
	void deleteInstance() { this->~Parameter(); ::operator delete(this); }

	static Parameter *ReadParameter(DataChunkInput &file);

	ParameterType getParameterType() const { return m_paramType; }
	Int getInt() const { return m_int; }
	Rva0034FF50 *retyper() { return (Rva0034FF50 *)this; }

private:
	ParameterType m_paramType; // +0x00
	Bool m_initialized; // +0x04
	Int m_int; // +0x08
	float m_real; // +0x0C
	AsciiString m_string; // +0x10
	char m_tail[0x28 - 0x14];
};

class Template
{
public:
	int getNumParameters() const throw() { return m_numParameters; }
	Parameter::ParameterType getParameterType(int ndx) const;

	char m_head[0x08];
	AsciiString m_name; // +0x08
	AsciiString m_internalName; // +0x0C
	NameKeyType m_internalNameKey; // +0x10
	char m_middle[0x48 - 0x14];
	int m_numParameters; // +0x48
	Parameter::ParameterType m_parameters[12]; // +0x4C
};

Parameter::ParameterType Template::getParameterType(int ndx) const
{
	if (ndx >= 0 && ndx < m_numParameters) {
		return m_parameters[ndx];
	}
	return Parameter::INT;
}

class ActionTemplate : public Template
{
};

class ConditionTemplate : public Template
{
};

class ScriptEngine
{
public:
	const ActionTemplate *getActionTemplate(int type) throw();
	const ConditionTemplate *getConditionTemplate(int type) throw();
};
extern ScriptEngine *TheScriptEngine;

enum { MAX_PARMS = 12 };

class ScriptAction
{
public:
	enum ScriptActionType
	{
		NO_OP = 5,
		NUM_ITEMS = 0x257
	};
	ScriptAction() throw();
	void setActionType(ScriptActionType type);

	Int getActionType() const { return m_actionType; }
	Int getNumParameters() const { return m_numParms; }

protected:
	static ScriptAction *ParseAction(DataChunkInput &file, DataChunkInfo *info, void *userData);

private:
	void *m_vtable; // +0x00
	int m_actionType; // +0x04
	int m_numParms; // +0x08
	Parameter *m_parms[MAX_PARMS]; // +0x0C
	ScriptAction *m_nextAction; // +0x3C
	Bool m_hasWarnings; // +0x40
	Bool m_active; // +0x41
	Int m_bfmeActionTail; // +0x44
};

void ScriptAction::setActionType(ScriptActionType type)
{
	int i;
	for (i = 0; i < m_numParms; i++) {
		if (m_parms[i])
			m_parms[i]->deleteInstance();
		m_parms[i] = 0;
	}
	m_actionType = type;
	const ActionTemplate *pTemplate = TheScriptEngine->getActionTemplate(m_actionType);
	m_numParms = pTemplate->getNumParameters();
	for (i = 0; i < m_numParms; i++) {
		m_parms[i] = new Parameter(pTemplate->getParameterType(i));
	}
}

class Condition
{
public:
	enum ConditionType
	{
		CONDITION_FALSE = 0
	};
	virtual ~Condition();
	void setConditionType(ConditionType type);
private:
	int m_conditionType; // +0x04
	int m_numParms; // +0x08
	Parameter *m_parms[MAX_PARMS]; // +0x0C
};

void Condition::setConditionType(ConditionType type)
{
	int i;
	for (i = 0; i < m_numParms; i++) {
		if (m_parms[i])
			m_parms[i]->deleteInstance();
		m_parms[i] = 0;
	}
	m_conditionType = type;
	const ConditionTemplate *pTemplate = TheScriptEngine->getConditionTemplate(m_conditionType);
	m_numParms = pTemplate->getNumParameters();
	for (i = 0; i < m_numParms; i++) {
		m_parms[i] = new Parameter(pTemplate->getParameterType(i));
	}
}

#pragma optimize("y", off)
ScriptAction *ScriptAction::ParseAction(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	ScriptAction *pScriptAction = new ScriptAction;

	pScriptAction->m_actionType = file.readInt();

	const ActionTemplate *at = TheScriptEngine->getActionTemplate(pScriptAction->m_actionType);
	if (info->version >= 2) {
		NameKeyType key = file.readNameKey();
		Bool match = false;
		if (at) {
			if (at->m_internalNameKey == key) {
				match = true;
			} else if (pScriptAction->m_actionType == 0x181 &&
				(at->m_internalName.compare("BUILD_BASE_BUILDING_PER_TACTICAL_MARKER") == 0 ||
				 at->m_internalName.compare("BUILD_BASE_BUILDING_PER_TACTIC") == 0)) {
				match = true;
			}
		}
		if (!match && pScriptAction->m_actionType == 0x181) {
			AsciiString name = TheNameKeyGenerator->keyToName(key);
			if (compareLiteral(name, "BUILD_BASE_BUILDING_PER_TACTICAL_MARKER") == 0 ||
				compareLiteral(name, "BUILD_BASE_BUILDING_WITH_TACTIC") == 0) {
				match = true;
			}
		}
		if (!match) {
			Int i;
			for (i = 0; i < ScriptAction::NUM_ITEMS; i++) {
				at = TheScriptEngine->getActionTemplate(i);
				if (key == at->m_internalNameKey) {
					match = true;
					pScriptAction->m_actionType = i;
					break;
				}
			}
			if (!match) {
				pScriptAction->m_actionType = ScriptAction::NO_OP;
				pScriptAction->m_numParms = 0;
			}
		}
	}

	pScriptAction->m_numParms = file.readInt();
	Int i;
	for (i = 0; i < pScriptAction->m_numParms; i++) {
		Parameter *parameter = Parameter::ReadParameter(file);
		pScriptAction->m_parms[i] = parameter;
		if (parameter->getParameterType() == Parameter::OBJECT_TYPE && at->getNumParameters() > i &&
			at->getParameterType(i) == 0x3d)
			parameter->retyper()->checkAndSet();
	}

	if (info->version >= 3)
		pScriptAction->m_active = file.readInt() != 0;
	else
		pScriptAction->m_active = true;

	// heal old files.
	switch (pScriptAction->getActionType()) {
		case 0x1b2:
		case 0x1b3:
			if (pScriptAction->getNumParameters() == 3) {
				pScriptAction->m_numParms = 4;
				pScriptAction->m_parms[3] = new Parameter((Parameter::ParameterType)0x34, 1);
			}
			break;
		case 0xff:
			if (pScriptAction->m_numParms == 1) {
				pScriptAction->m_numParms = 2;
				pScriptAction->m_parms[1] = pScriptAction->m_parms[0];
				pScriptAction->m_parms[0] = new Parameter(Parameter::SIDE);
				pScriptAction->m_parms[0]->rva00333B02("<This Player>");
			}
			break;
		case 0x24:
			if (pScriptAction->m_numParms == 3) {
				pScriptAction->m_numParms = 4;
				pScriptAction->m_parms[3] = new Parameter(Parameter::BOOLEAN, 0);
			}
			break;
		case 0xfe:
			if (pScriptAction->m_numParms == 1) {
				Bool flank = pScriptAction->m_parms[0]->getInt() != 0;
				if (pScriptAction->m_parms[0])
					pScriptAction->m_parms[0]->deleteInstance();
				pScriptAction->m_numParms = 0;
				if (flank)
					pScriptAction->m_actionType = 0x102;
			}
			break;
		case 0x2d:
		case 0x2e:
			if (pScriptAction->m_numParms >= 2 && pScriptAction->m_parms[1]->getParameterType() == Parameter::INT) {
				pScriptAction->m_parms[1] = new Parameter(Parameter::AI_MOOD, pScriptAction->m_parms[1]->getInt());
			}
			break;
		case 0x5d:
		case 0x94:
			if (pScriptAction->getNumParameters() == 2) {
				pScriptAction->m_numParms = 3;
				pScriptAction->m_parms[2] = new Parameter(Parameter::SIDE);
			}
			break;
		case 0x69:
		case 0x95:
		case 0xe9:
		case 0xea:
			if (pScriptAction->getNumParameters() == 0) {
				pScriptAction->m_numParms = 1;
				pScriptAction->m_parms[0] = new Parameter(Parameter::SIDE);
			}
			break;
		case 0x55:
			if (pScriptAction->m_numParms == 1) {
				pScriptAction->m_numParms = 2;
				pScriptAction->m_parms[1] = new Parameter(Parameter::BOOLEAN, 1);
			}
			break;
		case 0x1a:
		case 0x1b:
			if (pScriptAction->getNumParameters() == 1) {
				pScriptAction->m_numParms = 3;
				pScriptAction->m_parms[1] = new Parameter((Parameter::ParameterType)0x34, 0);
				pScriptAction->m_parms[2] = new Parameter((Parameter::ParameterType)0x34, 0);
			}
			break;
		case 0x0e:
			if (pScriptAction->getNumParameters() == 3) {
				pScriptAction->m_numParms = 5;
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL, 0);
				pScriptAction->m_parms[4] = new Parameter(Parameter::REAL, 0);
			}
			break;
		case 0x12:
		case 0x13:
		case 0x78:
		case 0x79:
		case 0x154:
		case 0x15a:
			if (pScriptAction->getNumParameters() == 2) {
				pScriptAction->m_numParms = 4;
				pScriptAction->m_parms[2] = new Parameter(Parameter::REAL);
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL);
			}
			break;
		case 0xd2:
			if (pScriptAction->getNumParameters() == 2) {
				pScriptAction->m_numParms = 5;
				pScriptAction->m_parms[2] = new Parameter(Parameter::REAL, 0);
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL, 0);
				pScriptAction->m_parms[4] = new Parameter(Parameter::BOOLEAN, 0);
			} else if (pScriptAction->getNumParameters() == 4) {
				pScriptAction->m_numParms = 5;
				pScriptAction->m_parms[4] = new Parameter(Parameter::BOOLEAN, 0);
			}
			break;
		case 0x52:
			if (pScriptAction->getNumParameters() == 1) {
				pScriptAction->m_numParms = 2;
				pScriptAction->m_parms[1] = new Parameter(Parameter::BOOLEAN, 0);
			}
			break;
		case 0x7a:
			if (pScriptAction->getNumParameters() == 2) {
				pScriptAction->m_numParms = 3;
				pScriptAction->m_parms[2] = new Parameter(Parameter::REAL);
			}
			break;
		case 0xb9:
			if (pScriptAction->getNumParameters() == 3) {
				pScriptAction->m_numParms = 5;
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL, 0);
				pScriptAction->m_parms[4] = new Parameter(Parameter::REAL, 0);
			}
			if (pScriptAction->getNumParameters() == 5) {
				pScriptAction->m_numParms = 6;
				pScriptAction->m_parms[5] = new Parameter(Parameter::REAL, 0);
			}
			break;
		case 0x11:
		case 0x186:
			if (pScriptAction->getNumParameters() == 3) {
				pScriptAction->m_numParms = 6;
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL);
				pScriptAction->m_parms[4] = new Parameter(Parameter::REAL);
				pScriptAction->m_parms[5] = new Parameter(Parameter::REAL);
			} else if (pScriptAction->getNumParameters() == 5) {
				pScriptAction->m_numParms = 6;
				pScriptAction->m_parms[5] = new Parameter(Parameter::REAL, 0);
			}
			break;
	}

	if (at->getNumParameters() != pScriptAction->getNumParameters()) {
		pScriptAction->m_actionType = ScriptAction::NO_OP;
		pScriptAction->m_numParms = 0;
	}
	return pScriptAction;
}
#pragma optimize("", on)
