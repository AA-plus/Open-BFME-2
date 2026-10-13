// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva003BC6C7Set@ScriptActions@@QAEXH@Z @0x003BC6C7 18B: free wrapper forwarding to GameLogic::rva003BA5DD.
// Evidence: mov ecx,[0x00DFE78C] test ecx je ret jmp 0x003BA5DD ret 4; chain
// from just-landed 0x003BA5DD; sole caller 0x003CD546 in ScriptActions dispatch.

class GameLogic
{
public:
	void rva003BA5DD(int value);
};
extern GameLogic *TheGameLogic;


void ScriptActions::Rva003BC6C7Set(int value)
{
	if (TheGameLogic)
		TheGameLogic->rva003BA5DD(value);
}
