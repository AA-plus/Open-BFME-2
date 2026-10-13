// stlport
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCA68Set@ScriptActions@@QAEX_N@Z @0x003BCA68 19B evidence: mov al [esp+4] mov ecx [TheGameLogic] mov [ecx+0x99] al ret 4; caller at 0x003CD731; sibling Rva003BCA7BSet +0x9A same stdcall bool shape
class GameLogic {
public:
	unsigned char m_pad[0x99];
	unsigned char m_99;
};
extern GameLogic *TheGameLogic;
void ScriptActions::Rva003BCA68Set(bool b)
{
	TheGameLogic->m_99 = b;
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
