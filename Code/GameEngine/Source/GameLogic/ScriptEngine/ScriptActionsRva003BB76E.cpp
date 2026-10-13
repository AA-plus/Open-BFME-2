// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BB76EDo@ScriptActions@@QAEXPAUCoord3D@@PAX@Z @0x003BB76E 47B: ScriptActions member Coord+extra to Radar+Eva.
// Target evidence: fld g_00BC2918 Radar 0x009FF070 via pin 0x002D88A4 with extra+float then g_00DFDC30 via pin 0x001DDAE1 ret 8; caller 0x003CBCE8.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Radar;
extern Radar *TheRadar;
class Rva002D88A4
{
public:
	void rva002D88A4(Coord3D *pos, void *extra, float scale);
};
class Rva001DDAE1
{
public:
	void rva001DDAE1(Coord3D *pos);
};
extern class Eva *TheEva;
// g_00BC2918 was the retail address alias (RVA 0x007C2918) of the constant 4.0f; the literal is the source.
void ScriptActions::Rva003BB76EDo(Coord3D *pos, void *extra)
{
	((Rva002D88A4 *)TheRadar)->rva002D88A4(pos, extra, 4.0f);
	(*(Rva001DDAE1 **)&TheEva)->rva001DDAE1(pos);
}
