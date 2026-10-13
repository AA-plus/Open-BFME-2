// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -ICode/GameEngine/Include -DNDEBUG -MD /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include "Code/GameEngine/Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003C35AADo@@YGXPBVAsciiString@@PAX_N@Z @0x003C35AA 77B (dump range 18).
// Trigger-area wiring: team-name copy, rowed ScriptEngine
// getQualifiedTriggerAreaByName, pinned 0x0052E3E6 member on the
// 0x00DFF0F8+0x10 object, flag gate, then the pinned ScriptEngine
// 0x00209811 member. All callees rowed/pinned; identities unproven.
#include "ascii_string.h"

class PolygonTrigger;

class ScriptEngine
{
public:
	PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
	void rva00209811(const AsciiString &name, unsigned char x);
};
extern ScriptEngine *TheScriptEngine;

class Pathfinder
{
public:
	void rva0052E3E6(PolygonTrigger *a, bool b);
};

struct Rva00DFF0F8Obj
{
	char m_pad[0x10];
	Pathfinder *m_p10;
};
extern class AI *TheAI;

void ScriptActions::Rva003C35AADo(const AsciiString *teamName, bool x, bool flag)
{
	PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(*teamName);
	if (trigger == 0)
		return;
	((Rva00DFF0F8Obj *)TheAI)->m_p10->rva0052E3E6(trigger, x);
	if (flag != 0)
		return;
	TheScriptEngine->rva00209811(*teamName, x);
}
