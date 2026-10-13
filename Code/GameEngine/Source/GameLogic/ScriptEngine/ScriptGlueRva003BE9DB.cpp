// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva003BE9DBSet@@YGXABVAsciiString@@M@Z @0x003BE9DB 53B (dump range 18).
// Team float setter through the doSetTeamState argument idiom: copies the
// name through the rowed StringBase copy ctor, resolves the team through
// rowed ScriptEngine 0x003584E9 getTeamNamed, and calls the rowed
// Team::damageTeamMembers (0x0039E76C, stack-float shape) when non-null.
#include "ascii_string.h"

typedef bool Bool;

class Team
{
public:
	bool damageTeamMembers(float amount);	// rowed bool return (TeamApplyDamage.cpp); result unused here
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString team, Bool exact);
};
extern ScriptEngine *TheScriptEngine;

void __stdcall Rva003BE9DBSet(const AsciiString &team, float f)
{
	Team *t = TheScriptEngine->getTeamNamed(team, false);
	if (t != 0)
		t->damageTeamMembers(f);
}
