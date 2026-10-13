// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BB31DClear@@YGXABVAsciiString@@@Z @0x003BB31D 62B: free stdcall clearing Player byte +0x339 for each player in a name mask.
// Target evidence: calls ScriptEngine::rva00357475 (0x00357475) once then getEachPlayerFromMask (0x002A7BC9) loop writing byte [eax+0x339]=0; globals g_Va009FE16C (0x009FE16C) and ThePlayerList (0x009FEEE8); ret 4; caller 0x003CB7C7.
class AsciiString;
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };
class Player
{
public:
	void setObjectsEnabled(const AsciiString &templateTypeToAffect, bool enable);
	void setUnitsShouldHunt(bool unitsShouldHunt, CommandSourceType source);

	char m_pad00[0x339];
	unsigned char m_flag339; // +0x339
};
class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
};
extern class ScriptEngine *TheScriptEngine;
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;
void __stdcall Rva003BB31DClear(const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *p;
	do {
		p = ThePlayerList->getEachPlayerFromMask(mask);
		if (p)
			p->m_flag339 = 0;
	} while (mask != 0);
}

// Three same-shape player-mask actions from adjacent Ghidra starts. Their
// action identities are unresolved, so the recovered entries use RVA names.
// The only semantic anchors used here are the rowed player-mask resolver and
// PlayerList iterator shared with the neighboring target-proven set/clear
// actions above. The Player callees are called by their rows' names:
// setUnitsShouldHunt (0x002AE9B8) from a script and setObjectsEnabled
// (0x002ABD93) on the action's second argument.

void __stdcall Rva003BB29D(const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *p;
	do {
		p = ThePlayerList->getEachPlayerFromMask(mask);
		if (p)
			p->setUnitsShouldHunt(true, CMD_FROM_SCRIPT);
	} while (mask != 0);
}

void __stdcall Rva003BB35B(const AsciiString &name, int arg)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *p;
	do {
		p = ThePlayerList->getEachPlayerFromMask(mask);
		if (p)
			p->setObjectsEnabled(*(const AsciiString *)arg, false);
	} while (mask != 0);
}

void __stdcall Rva003BB41A(const AsciiString &name, int arg)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *p;
	do {
		p = ThePlayerList->getEachPlayerFromMask(mask);
		if (p)
			p->setObjectsEnabled(*(const AsciiString *)arg, true);
	} while (mask != 0);
}
