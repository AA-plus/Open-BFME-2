// ?addObject@ElvenWoodSpecialPower@@QAEPAVObject@@PBUCoord3D@@PBVAsciiString@@@Z
// partial score=0.972 date=2026-10-13
// R5 WB EVIDENCE (wb_show 0x4C397F --gd): true ElvenWoodSpecialPower::addObject,
// file GameLogic/Object/SpecialPower/ElvenWoodSpecialPower.cpp. Outer KINDOF gate
// is BitFlags<218,KindOfType>::test chain via BfmeWideResult::next(tmpl+0x108,ch)
// with 'd'(0x64)/'^'(0x5e)/'_'(0x5f): next(d)||next(^)||next(_) == our inlined
// (kinds[12]&0x10)||(kinds[11]&0xC0) since bit100=byte12.10, bits94-95=byte11.C0.
// Inner dispatch next(0x5e)->addTree / next(0x5f)->rva00280176 / else rva0027D3D9
// == our (kind@0x110&0x40000000(bit94)) / (kind<0:bit95) / else. Matrix zeros are a
// SOURCE LOOP in debug (ptr-walk) + if(1)-identity; retail unrolls to our 9+3 stores.
// DEBUG() string on !templ @:302 (dropped in retail). setTeam arg: this+8->+0x310.
// R5 TRIAL: volatile-zero stores (9x) NEUTRAL (24 diffs unchanged): MSVC hoists the
// kind int-load+test above volatile stores freely; zeros-vol does not pin. Untried:
// source-loop zeros (unroll scheduling), TinTin-style split of kind test.
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"

class Thing;
class ModuleData;
struct Coord3D;
class Object;
class Team;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const ModuleData *m_data;
	Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleInterface
{
public:
	virtual void specialPowerModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModule : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public ModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );

protected:
	virtual ~SpecialPowerModule();
};

class ElvenWoodSpecialPower : public SpecialPowerModule
{
public:
	ElvenWoodSpecialPower( Thing *thing, const ModuleData *moduleData );
	Object *addObject(const Coord3D *position, const AsciiString *name);

protected:
	virtual ~ElvenWoodSpecialPower();
};

ElvenWoodSpecialPower::ElvenWoodSpecialPower( Thing *thing, const ModuleData *moduleData )
	: SpecialPowerModule( thing, moduleData )
{
}

// ??1ElvenWoodSpecialPower@@MAE@XZ present-unmatched
ElvenWoodSpecialPower::~ElvenWoodSpecialPower()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?specialPowerModuleInterfaceAnchor@SpecialPowerModuleInterface@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// ?addObject@ElvenWoodSpecialPower@@QAEPAVObject@@PBUCoord3D@@PBVAsciiString@@@Z
// @0x004C397F 288B (WB125EB20 addObject): template lookup, KINDOF-gated
// terrain stamp through a retail-ordered identity Matrix3D, else masked
// object creation. The matrix is built with explicit stores (zeros,
// scale load, diagonals) so the compiler keeps retail's schedule.
#pragma function(memset)
extern "C" void *memset(void *dst, int value, unsigned int size);

class ThingTemplate
{
public:
	unsigned char prefix[0x108];
	unsigned char kinds[28];
	unsigned char gap[0x4E0 - 0x124];
	float scale;
};

class Matrix3D
{
public:
	float row[3][4];
};

class TerrainLogic
{
public:
	void rva00283642(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
	void rva00280176(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
	void rva0027D3D9(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
};
extern TerrainLogic *TheTerrainLogic;

struct CreateMask
{
	unsigned words[4];
};

class Thing
{
public:
	void setPosition(const Coord3D *);
};

class Object : public Thing
{
public:
	void setTeam(Team *);
	char pad[0x304];
	Team *team;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, bool flag);
};
extern ThingFactory *TheThingFactory;

Object *ElvenWoodSpecialPower::addObject(const Coord3D *position, const AsciiString *name)
{
	const ThingTemplate *templ = TheThingFactory->findTemplate(*name);
	if (templ) {
		if ((templ->kinds[12] & 0x10) || (templ->kinds[11] & 0xC0)) {
			Matrix3D matrix;
			matrix.row[0][0] = 1.0f;
			matrix.row[1][1] = 1.0f;
			matrix.row[2][2] = 1.0f;
			*(volatile float *)&matrix.row[0][1] = 0.0f;
			*(volatile float *)&matrix.row[0][2] = 0.0f;
			*(volatile float *)&matrix.row[0][3] = 0.0f;
			*(volatile float *)&matrix.row[1][0] = 0.0f;
			*(volatile float *)&matrix.row[1][2] = 0.0f;
			*(volatile float *)&matrix.row[1][3] = 0.0f;
			*(volatile float *)&matrix.row[2][0] = 0.0f;
			*(volatile float *)&matrix.row[2][1] = 0.0f;
			*(volatile float *)&matrix.row[2][3] = 0.0f;
			float scale = templ->scale;
			int kind;
			if ((kind = *(volatile int *)(templ->kinds + 8)) & 0x40000000)
				TheTerrainLogic->rva00283642(templ, position, &matrix, scale);
			else if (kind < 0)
				TheTerrainLogic->rva00280176(templ, position, &matrix, scale);
			else
				TheTerrainLogic->rva0027D3D9(templ, position, &matrix, scale);
		}
		else {
			CreateMask mask;
			memset(&mask, 0, sizeof(mask));
			Object *object = TheThingFactory->newObject(templ, 0, &mask, false);
			if (object) {
				object->setTeam(m_object->team);
				object->setPosition(position);
				return object;
			}
		}
	}
	return 0;
}
