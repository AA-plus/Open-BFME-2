// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
#include "Coord3D.h"

class Object;
class Player;
struct Rva00372571Params
{
	const Coord3D *m_pos;
	bool m_addWaypoint;
	Object *m_ignoreObstacle;
	Object *m_target;
	const float *m_facing;
	int m_formationType;
	Player *m_player;
	bool m_attackMove;
};
class AIGroup
{
public:
	void add(Object *member);
	void rva00372571(Rva00372571Params *params, int commandSource);
};
class AI
{
public:
	AIGroup *createGroup();
	void destroyGroup(AIGroup *group);
};
extern AI *TheAI;

// Two-pointer range view; the caller passes the vector member at entry +4.
// The capacity word is not read by this helper.
class BfmeVecAV
{
public:
	Object **m_begin;
	Object **m_end;
};

// Native 16-byte record: one Object* followed by a three-word vector.
// Only the first two vector words are used by the group-copy helper.
struct Rva004C734DElement
{
	Object *owner;
	BfmeVecAV members;
	void *storageEnd;
};
struct ManTheWallsObjectPositionView
{
	unsigned char m_beforePosition[0x38];
	Coord3D m_position;
};

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
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
};

class ManTheWallsSpecialPower : public SpecialPowerModule
{
public:
	ManTheWallsSpecialPower( Thing *thing, const ModuleData *moduleData );
	void rva004C70AD(BfmeVecAV *range, AIGroup *group);
	void rva004C7167(Rva004C734DElement *entry);
};

ManTheWallsSpecialPower::ManTheWallsSpecialPower( Thing *thing, const ModuleData *moduleData )
	: SpecialPowerModule( thing, moduleData )
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?specialPowerModuleInterfaceAnchor@SpecialPowerModuleInterface@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Native 4C70AD..4C70CF, RET8. The ManTheWalls helper 4C7167 restores
// its receiver into ECX before this call; WB 1268D00 does the same, and
// WB 1268D90 saves ECX as this. Thus the earlier free __stdcall claim
// reproduced bytes but omitted a real receiver. The receiver is unused here.
// Loop semantics were carried by BFME1 9e3be919b10ae956e3c8a13995e0d62f2be1d016
// game/GameEngine/Source/Common/BfmeConv1746.cpp; target calls AIGroup::add
// and independently establishes the two pointer fields and Object* elements.
// The original method and range-type names remain unknown.
void ManTheWallsSpecialPower::rva004C70AD(BfmeVecAV *range, AIGroup *group)
{
	for (Object **it = range->m_begin; it != range->m_end; ++it)
		group->add(*it);
}

// Native 4C7167..4C71D3 (108B, RET4); WB 1268D00. Creates an AI group,
// adds the entry's Object* range and issues the existing group command
// using its owner's +38 position, then destroys the group. All eight
// command-block fields, their write order and the zero source are native
// observations. Command semantics and the method's original name are open.
// The member helper ABI above accounts for the formerly unexplained ECX
// save/restore; the old free-function declaration omitted six native bytes.
void ManTheWallsSpecialPower::rva004C7167(Rva004C734DElement *entry)
{
	AIGroup *group = TheAI->createGroup();
	if (group)
	{
		rva004C70AD(&entry->members, group);
		Rva00372571Params params;
		params.m_formationType = -1;
		params.m_pos = &((ManTheWallsObjectPositionView *)entry->owner)->m_position;
		params.m_addWaypoint = false;
		params.m_ignoreObstacle = 0;
		params.m_target = 0;
		params.m_facing = 0;
		params.m_player = 0;
		params.m_attackMove = false;
		group->rva00372571(&params, 0);
		TheAI->destroyGroup(group);
	}
}
