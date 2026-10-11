// cl: /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// Skirmish-AI tactic base ctors taking the tactic name:
//   ??0Rva005DC73C@@QAE@ABVAsciiString@@@Z @0x005DC722 26B, vtable 0x00C767DC
//   ??0Rva005DCB27@@QAE@ABVAsciiString@@@Z @0x005DCB0D 26B, vtable 0x00C76834
//   ??0Rva005DCC24@@QAE@ABVAsciiString@@@Z @0x005DCC0A 26B, vtable 0x00C7690C
//     (the RoamingDefense/StartWoTRBattle/RingHero/... base; dtor 0x005DCC24)
// Each forwards (name, true) to the rowed AITactic base ctor 0x004ED3D1
// (AITactic.cpp, bool flag) and installs its own vtable. Same
// base + vtable shape as the landed SimpleAttack ctor
// (??0AISimpleAttackTactic@@QAE@XZ @0x005AA6B4, which calls 0x005DC722 with the
// SimpleAttack name). Class views are minimal: vtable width beyond the
// dtor/deleting-dtor slots is unproven and not declared.
#include "ascii_string.h"

class AITactic
{
public:
	AITactic(const AsciiString &name, bool flag);
	virtual ~AITactic();
};

class AITacticOffensive : public AITactic
{
public:
	AITacticOffensive(const AsciiString &name);
	virtual ~AITacticOffensive();
};

AITacticOffensive::AITacticOffensive(const AsciiString &name)
	: AITactic(name, true)
{
}

class AITacticDefensive : public AITactic
{
public:
	AITacticDefensive(const AsciiString &name);
	virtual ~AITacticDefensive();
};

AITacticDefensive::AITacticDefensive(const AsciiString &name)
	: AITactic(name, true)
{
}

class Rva005DCC24 : public AITactic
{
public:
	Rva005DCC24(const AsciiString &name);
	virtual ~Rva005DCC24();
};

Rva005DCC24::Rva005DCC24(const AsciiString &name)
	: AITactic(name, true)
{
}
