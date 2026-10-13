// cl: -O1 -arch:SSE -G7 -MD -EHsc -DNDEBUG -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003BD108SetGamePaused@ScriptActions@@QAEXXZ, retail 0x003BD108 14B. Identity is address-named; packet shows TheGameLogic followed by GameLogic::SetGamePaused(true).
class GameLogic
{
public:
	void rva0023D0E3(bool paused);
};
extern GameLogic *TheGameLogic;

void ScriptActions::Rva003BD108SetGamePaused()
{
	TheGameLogic->rva0023D0E3(true);
}
