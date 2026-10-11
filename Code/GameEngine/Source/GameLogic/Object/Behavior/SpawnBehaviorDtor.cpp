// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc  /D_CRTIMP=
// stlport
//
// ??1SpawnBehavior@@UAE@XZ, retail 0x0045F6D3, 138 bytes. Virtual dtor.
// Restores the eight MI vptrs (+0 0xC426AC +0x0C 0xC425F0 +0x10 0xC425E0
// +0x20 0xC425AC +0x24 0xC425A8 +0x28 0xC4259C +0x2C 0xC42598 +0x30 0xC42550
// DIR32) then clears m_replacementTimes at +0x48 through the rowed
// 0x23DAA5 List_base clear, destroys m_spawnIDs at +0x4C and
// m_replacementTimes at +0x48 through the rowed 0x4EC395 List_base dtor,
// then calls the UpdateModule base dtor (pinned ??1UpdateModule@@UAE@XZ
// at 0x0024A797 rowed as ??1Rva0024A797@@UAE@XZ). Layout follows the ctor
// at 0x0045F581 (UpdateModule base size 0x20 plus four empty interfaces
// at +0x20..+0x2C plus UpgradeMux at +0x30 size 8 plus ptr+3 ints at
// +0x38..+0x44 plus two lists at +0x48/+0x4C, factory 0x0024B405 news
// 0x64) and the ZH donor SpawnBehavior.h (SpawnBehaviorInterface plus
// DieModuleInterface plus DamageModuleInterface plus UpgradeMux from
// UpgradeModule.h). BFME1 donor SpawnBehaviorDestructors.cpp proves the
// clear-then-destroy shape. Identity is the own vtable 0xC426AC plus slot
// 0 deleting dtor 0x004602D8 calling this body plus poolkey 0x0045F688
// with the SpawnBehavior literal.

#include <list>

class Thing;
class ModuleData;
class Object;

class BehaviorModuleBase
{
	virtual void unused();
	int a;
	int b;
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *obj, unsigned int frame);
};

class SpawnBehaviorInterface
{
public:
	virtual void spawnBehaviorAnchor();
};

class DieModuleInterface
{
public:
	virtual void dieAnchor();
};

class DamageModuleInterface
{
public:
	virtual void damageAnchor();
};

class SpawnExtraBase
{
public:
	virtual void spawnExtraAnchor();
};

class UpgradeMux
{
public:
	virtual void upgradeMuxAnchor();

private:
	bool m_upgradeExecuted;
};

class ThingTemplate;

class SpawnBehavior : public UpdateModule,
	public SpawnBehaviorInterface,
	public DieModuleInterface,
	public DamageModuleInterface,
	public SpawnExtraBase,
	public UpgradeMux
{
public:
	virtual ~SpawnBehavior();

private:
	const ThingTemplate *m_spawnTemplate; // +0x38
	int m_oneShotCountdown; // +0x3C
	int m_framesToWait; // +0x40
	int m_firstBatchCount; // +0x44
	_STL::list<int> m_replacementTimes; // +0x48
	_STL::list<int> m_spawnIDs; // +0x4C
	unsigned char m_pad50[0x14]; // +0x50..+0x63 trivial tail to news 0x64
};

inline SpawnBehavior::~SpawnBehavior()
{
	m_replacementTimes.clear();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleOther@@EAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// ??1SpawnBehavior@@UAE@XZ is a header inline elsewhere: another unit emits a
// select-any copy, so a strong definition here was a duplicate symbol in the
// linked build. This anchor only makes this unit emit its copy for the ledger
// row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitSpawnBehaviorDtor@@YAXPAVSpawnBehavior@@@Z present-unmatched
void bfmeEmitSpawnBehaviorDtor(SpawnBehavior *p)
{
	p->SpawnBehavior::~SpawnBehavior();
}
#pragma inline_depth()
