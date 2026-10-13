// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003BC1A0Forward@ScriptActions@@QAEXXZ @0x003BC1A0 18B: script forwards TheTerrainLogic to TheRadar slot 0x10.
// Evidence: mov ecx,[0xDFF070]=TheRadar push [0xDFEC50]=TheTerrainLogic mov eax,[ecx] call [eax+0x10] ret; caller 0x003CC86C.
class TerrainLogic;
class Radar
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04(TerrainLogic *t);
};
extern Radar *TheRadar;
extern TerrainLogic *TheTerrainLogic;

void ScriptActions::Rva003BC1A0Forward()
{
	TheRadar->s04(TheTerrainLogic);
}
