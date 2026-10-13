// stlport
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BC8F0Set@ScriptActions@@QAEX_N@Z @0x003BC8F0 19B: script sets GameLogic +0x9f byte from bool arg.
// Evidence: mov al,[esp+4] mov ecx,[0xDFE78C]=TheGameLogic mov [ecx+0x9f],al ret 4; caller 0x003CD4C3.
class GameLogic
{
public:
	unsigned char m_pad[0x9f];
	unsigned char m_9f;
};
extern GameLogic *TheGameLogic;

void ScriptActions::Rva003BC8F0Set(bool b)
{
	TheGameLogic->m_9f = b;
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
