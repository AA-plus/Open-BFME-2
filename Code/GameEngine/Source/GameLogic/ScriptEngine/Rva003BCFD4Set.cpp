// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCFD4Set@ScriptActions@@QAEX_N@Z @0x003BCFD4 19B: script sets ClientFrameSubsystem +0xc0 byte from bool arg.
// Evidence: mov al,[esp+4] mov ecx,[0xDFE77C]=TheGameClient mov [ecx+0xc0],al ret 4; caller 0x003CE62F; siblings Rva003BCA7BSet same shape.
class ClientFrameSubsystem
{
public:
	unsigned char m_pad[0xc0];
	unsigned char m_c0;
};
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

void ScriptActions::Rva003BCFD4Set(bool b)
{
	((ClientFrameSubsystem *)TheGameClient)->m_c0 = b;
}
