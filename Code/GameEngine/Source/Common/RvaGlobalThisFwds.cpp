// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../Include/GameLogic/ScriptActionsBFME2.h"
// Two global-this forwards (11B each): mov ecx, [global], jmp <run>.
// Each loads a singleton pointer into this and tail-jumps its parameterless
// run method.
// 0x003BBEDE (global 0x00DFE16C -> 0x00203AD5),
// 0x003BBEE9 (global 0x00DFE16C -> 0x00203ADD).
// (0x003BD424 is ScriptActions::doEnablePlanningMode, in ScriptActions.cpp.)
// Global/callee identities unproven (opaque pins); the wrapper names are
// address-derived. One ledger row per forward.

class Rva00203AD5Run
{
public:
	void run();
};

class Rva00203ADDRun
{
public:
	void run();
};

extern class ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003BBEDE()
{
	(*(Rva00203AD5Run **)&TheScriptEngine)->run();
}

void ScriptActions::Rva003BBEE9()
{
	((Rva00203ADDRun *)(*(Rva00203AD5Run **)&TheScriptEngine))->run();
}
