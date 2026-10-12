// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?doFireSpecialPowerAtWaypoint@ScriptActions@@QAEXABVAsciiString@@00@Z
// @0x003C41BA 80B. WorldBuilder's ScriptActions::doFireSpecialPowerAtWaypoint
// (ScriptActions.cpp, asserts "Invalid waypoint/power in
// FireSpecialPowerAtWaypoint") looks the waypoint up through TheTerrainLogic
// (+0x88), the power through findSpecialPowerTemplate 0x0029B6EB, and fires
// at the waypoint's location (+0xC) with FireSpecialPowerAtPosition
// 0x003C069B; retail is that body with the asserts compiled out. StringBase
// copy 0x000365F0 for the by-value AsciiString; caller 0x003CC74F.
#include "ascii_string.h"

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void *v34(const AsciiString &name);
};

extern TerrainLogic *TheTerrainLogic;

class SpecialPowerTemplate;
class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

extern SpecialPowerStore *TheSpecialPowerStore;

struct Coord3D;

class ScriptActions
{
public:
	void doFireSpecialPowerAtWaypoint(const AsciiString &playerName,
		const AsciiString &powerName, const AsciiString &waypointName);
	bool FireSpecialPowerAtPosition(const AsciiString &playerName,
		const SpecialPowerTemplate *power, const Coord3D *position) throw();
};

void ScriptActions::doFireSpecialPowerAtWaypoint(const AsciiString &playerName,
	const AsciiString &powerName, const AsciiString &waypointName)
{
	void *waypoint = TheTerrainLogic->v34(waypointName);
	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate(powerName);
	if (waypoint != 0 && power != 0)
		FireSpecialPowerAtPosition(playerName, power, (const Coord3D *)((char *)waypoint + 0xc));
}
