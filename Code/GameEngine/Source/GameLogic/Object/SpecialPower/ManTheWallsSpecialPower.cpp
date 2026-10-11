// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc

class Object;
class AIGroup
{
public:
	void add(Object *member);
};

// Two-pointer range view; the caller passes the vector member at entry +4.
// The capacity word is not read by this helper.
class BfmeVecAV
{
public:
	Object **m_begin;
	Object **m_end;
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
