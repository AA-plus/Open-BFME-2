// ?doEffectObject@ProjectileNugget@@UAEXPBUProjectileNuggetFireInfo@@PAVObject@@@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode /I.
// Native509814..509A3C,552B; ProjectileNugget vftableC646B0 slot5;
// WB10A4740 ProjectileNugget.cpp118-186 supplies identity and source scopes.
// Native Object getters establish transform8, position38, id74, modules244,
// projectile-source250; fire-info offsets are8/source, C/slot,38/barrel,5C/stream.
// Slot79 supplies a projectile; behavior interface+C slot18 supplies launch.
// Real inline fire-info accessors preserve parameter materialization. Visible
// read-only object-hash lookup preserves native CSE of the canonical GameLogic.
// Lookup storage follows existing GameLogicObjectLookupView and native2888D4;
// STLport _M_find supplies traversal, while exact native bytes prove the layout.
// ProjectileLookup* names describe private storage views, not recovered classes.
// Stream lookup occurs twice, then the same owner supplies its named module.
// No volatile barriers, extra lookup, pin, alternate global, or assembler.
#include <string.h>
#include "Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

// Local views of the WWMath types; only Matrix3D's name is load-bearing (the
// launch-position callee takes one). The helpers below expand retail's inline
// Matrix3D copy (member-wise) and Matrix3D::Transform_Vector.
struct ProjectileNuggetRow
{
	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	ProjectileNuggetRow Row[3];
};

class Team;
class ThingTemplate;
class WeaponTemplate;
struct CreateMask
{
	unsigned int m_bits[4];
};

class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }
private:
	unsigned char m_pad000[0x2EC];
	Team *m_defaultTeam; // +0x2EC
};

class ObjectFilter
{
public:
	Bool isValid() const;
private:
 int m_entryIndex; // native descriptor reads4B at0
};

class ProjectileUpdateInterface
{
public:
	virtual void projectileLaunch(const Object *victim, const Coord3D *victimPos,
		const Object *launcher, WeaponSlotType wslot, Int specificBarrelToUse,
		const void *fireInfo, const WeaponTemplate *detonationWeapon,
		const Matrix3D *launchTransform) = 0;
};

template <int N> class ProjectileNuggetSlots : public ProjectileNuggetSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class ProjectileNuggetSlots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

// The behavior-module interface each module carries at +0x0C.
class BehaviorModuleInterface : public ProjectileNuggetSlots<18>
{
public:
	virtual ProjectileUpdateInterface *getProjectileUpdateInterface() = 0; // slot 18
};

class BehaviorModule
{
public:
	// Calls slot 18 through the module's +0x0C interface.
	ProjectileUpdateInterface *projectileUpdateInterfaceView()
	{
		return ((BehaviorModuleInterface *)((char *)this + 0x0C))->getProjectileUpdateInterface();
	}
};

// The firer's +0x250 module: slot 79 hands out the projectile.
class ProjectileSourceModule : public ProjectileNuggetSlots<79>
{
public:
	virtual Object *getProjectileToLaunch(const ObjectFilter *filter) = 0; // slot 79
};

class Module;
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

class Rva0033EEC9
{
public:
	void rva0033EF86(const Coord3D *pos);	// the stream's position
};
class ProjectileStreamUpdate
{
public:
	void addProjectile(ObjectID sourceID, ObjectID projectileID, ObjectID victimID, const Coord3D *victimPos);
};

class Object
{
	friend class ProjectileNugget;
public:
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	ProjectileSourceModule *getProjectileSource() const { return m_250; }
	Player *getControllingPlayer() const;
	void setProducer(Object *producer);
protected:
	Module *findModule(NameKeyType key) const;
private:
	unsigned char m_pad000[0x08];
	Matrix3D m_transform; // +0x08
	Coord3D m_pos; // +0x38
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x244 - 0x78];
	BehaviorModule **m_behaviors; // +0x244
	unsigned char m_pad248[0x250 - 0x248];
	ProjectileSourceModule *m_250; // +0x250
};

class Weapon
{
public:
	static void calcProjectileLaunchPosition(const Object *launcher, WeaponSlotType wslot,
		Int specificBarrelToUse, Matrix3D &worldTransform, Coord3D &worldPos);
};

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, Bool b);
};

extern ThingFactory *TheThingFactory;
extern GameLogic *TheGameLogic;

// The fire info's template: its filter and launch-self byte.
struct ProjectileNuggetWeapon
{
	unsigned char m_pad000[0x120];
	ObjectFilter m_filter; // +0x120
	Bool m_launchSelf; // +0x124
};

struct ProjectileNuggetFireInfo
{
	unsigned char m_pad00[0x04];
	const ProjectileNuggetWeapon *m_weapon; // +0x04
	ObjectID m_sourceID; // +0x08
	WeaponSlotType m_wslot; // +0x0C
	unsigned char m_pad10[0x38 - 0x10];
	Int m_specificBarrel; // +0x38
	unsigned char m_pad3C[0x5C - 0x3C];
	ObjectID m_streamOwnerID; // +0x5C
 WeaponSlotType getWeaponSlot() const { return m_wslot; }
 int getSpecificBarrel() const { return m_specificBarrel; }
 const ProjectileNuggetWeapon *getWeapon() const { return m_weapon; }
 ObjectID getSourceID() const { return m_sourceID; }
 ObjectID getStreamOwnerID() const { return m_streamOwnerID; }
};

class ProjectileNugget
{
public:
	virtual void doEffectObject(const ProjectileNuggetFireInfo *info, Object *victim);
	
private:
	unsigned char m_pad004[0x128 - 0x04];
	const WeaponTemplate *m_detonationWeapon; // +0x128
	const ThingTemplate *m_projectileTemplate; // +0x12C
	unsigned char m_pad130[0x13C - 0x130];
	Int m_weaponSlotOverride; // +0x13C
	Coord3D m_launchOffset; // +0x140
	Bool m_useLaunchOffset; // +0x14C
};

// Storage and traversal from native _M_find2888D4 and pinned STLport reference.
struct ProjectileLookupNode { ProjectileLookupNode *next; ObjectID key; Object *object; };
struct ProjectileLookupBuckets {
 ProjectileLookupNode **begin,**end,**capacity;
 unsigned int size() const { return end-begin; }
 ProjectileLookupNode *const &operator[](unsigned int i) const { return begin[i]; }
};
struct ProjectileLookupMap { unsigned char hashEqual[4]; ProjectileLookupBuckets buckets; };
inline ObjectIdNode *ObjectIdMap::find(const ObjectID &id) {
 ProjectileLookupMap *map=(ProjectileLookupMap*)this;
 unsigned int bucket=(unsigned int)id % map->buckets.size();
 ProjectileLookupNode *node;
 for(node=map->buckets[bucket];node && node->key!=id;node=node->next) {}
 return (ObjectIdNode*)node;
}

inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectIdNode *node = m_map.find(id);
	if (node == 0)
		return 0;
	return node->object;
}


void ProjectileNugget::doEffectObject(const ProjectileNuggetFireInfo *info, Object *victim)
{
	Object *source = TheGameLogic->findObjectByID(info->getSourceID());
	if (source == 0)
		return;

	Matrix3D launchTransform;
	const Matrix3D *launchTransformPtr = &launchTransform;
	Coord3D worldPos;
	CreateMask mask;
	Object *projectile;
	const ProjectileNuggetWeapon *weapon = info->getWeapon();
	if (weapon->m_filter.isValid() && source->getProjectileSource())
	{
		Weapon::calcProjectileLaunchPosition(source, info->getWeaponSlot(), info->getSpecificBarrel(), launchTransform, worldPos);
		const ObjectFilter *filter = &info->getWeapon()->m_filter;
		projectile = source->getProjectileSource()->getProjectileToLaunch(filter);
	}
	else if (info->getWeapon()->m_launchSelf)
	{
		Weapon::calcProjectileLaunchPosition(source, info->getWeaponSlot(), info->getSpecificBarrel(), launchTransform, worldPos);
		projectile = source;
	}
	else
	{
		if (m_projectileTemplate == 0)
			return;
		launchTransformPtr = 0;
		memset(&mask, 0, sizeof(mask));
		projectile = TheThingFactory->newObject(m_projectileTemplate,
			source->getControllingPlayer()->getDefaultTeam(), &mask, false);
	}

	ProjectileUpdateInterface *pui = 0;
	for (BehaviorModule **u = projectile->getBehaviorModules(); *u; ++u)
	{
		if ((pui = (*u)->projectileUpdateInterfaceView()) != 0)
			break;
	}
	if (pui)
	{
		WeaponSlotType wslot = info->getWeaponSlot();
		if (m_weaponSlotOverride >= 0 && m_weaponSlotOverride < 6)
			wslot = (WeaponSlotType)m_weaponSlotOverride;
		projectile->setProducer(source);
		pui->projectileLaunch(victim, 0, source, wslot, info->getSpecificBarrel(), info,
			m_detonationWeapon, launchTransformPtr);
	}
	else
	{
		TheGameLogic->destroyObject(projectile);
	}

	

	Object *streamOwner = TheGameLogic->findObjectByID(info->getStreamOwnerID());
	if (streamOwner == 0)
		return;
	Object *launcher = TheGameLogic->findObjectByID(info->getSourceID());
	if (launcher == 0)
		return;
	static NameKeyType key_ProjectileStreamUpdate = NAMEKEY("ProjectileStreamUpdate");
	ProjectileStreamUpdate *update = (ProjectileStreamUpdate *)streamOwner->findModule(key_ProjectileStreamUpdate);
	if (update == 0)
		return;
	((Rva0033EEC9 *)update)->rva0033EF86(launcher->getPosition());
	update->addProjectile(launcher->getID(), projectile->getID(),
		victim ? victim->getID() : INVALID_OBJECT_ID, victim->getPosition());
}
