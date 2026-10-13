// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BB79DDo@ScriptActions@@QAEXPAVParameter@@PAX@Z @0x003BB79D 69B: ScriptActions member mapping Parameter to Object then Radar+Eva on Object+0x38.
// Target evidence: push [esp+4] ScriptEngine::getUnitNamed 0x003588E7 test je then lea esi [eax+0x38] test je then fld g_00BC2918 Radar 0x009FF070 via pin 0x002D88A4 with extra+float then g_00DFDC30 via pin 0x001DDAE1 ret 8; caller 0x003CBD09.
class Parameter;
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad[0x38];
	Coord3D m_pos;
};
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *);
};
extern class ScriptEngine *TheScriptEngine;
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
void ScriptActions::Rva003BB79DDo(Parameter *p, void *extra)
{
	Object *o = TheScriptEngine->getUnitNamed(p);
	if (!o)
		return;
	const Coord3D *pos = o->getPosition();
	if (!pos)
		return;
	((Rva002D88A4 *)TheRadar)->rva002D88A4((Coord3D *)pos, extra, 4.0f);
	(*(Rva001DDAE1 **)&TheEva)->rva001DDAE1((Coord3D *)pos);
}
