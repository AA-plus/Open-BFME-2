// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x00486623, 100B: FXListDie::onDie, entered through the
// DieModuleInterface subobject at +0x10 (isDieApplicable on this-0x10,
// module data this-0x0C, object this-0x08).
// Body: Zero Hour's FXListDie::onDie (GeneralsMD GameEngine/Source/
// GameLogic/Object/Die/FXListDie.cpp) without the ambient-sound stop: the
// default death FX (module data +0x38) is played on the object toward the
// damage dealer when orientToObject (+0x3C) is set, else at the object
// position (FXList::doFXObj 0x000B2235 / doFXPos 0x00094C29).

#include "../../../Common/GameLogicObjectLookupView.h"

typedef bool Bool;

struct Coord3D;
class Matrix3D;

class DamageInfo
{
public:
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID;
};

class DieMuxData
{
public:
	Bool isDieApplicable(const Object *object, const DamageInfo *damageInfo) const;
};

class FXList
{
public:
	static void doFXObj( const FXList *fx, const Object *primary, const Object *secondary = 0 );
	static void doFXPos( const FXList *fx, const Coord3D *primary,
		const Matrix3D *primaryMtx = 0, const float primarySpeed = 0.0f,
		const Coord3D *secondary = 0 );
};

class Object
{
public:
	const Coord3D *getPosition() const { return (const Coord3D *)m_pos; }
	unsigned char m_pad00[0x38];
	unsigned char m_pos[12];
};

extern GameLogic *TheGameLogic;

struct FXListDieModuleData
{
	unsigned char m_pad00[0x38];
	const FXList *m_defaultDeathFX;
	Bool m_orientToObject;
	Bool isDieApplicable(const Object *object, const DamageInfo *damageInfo) const
	{
		return ((const DieMuxData *)((const unsigned char *)this + 8))
			->isDieApplicable(object, damageInfo);
	}
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	Object *getObject() const { return m_object; }
	const FXListDieModuleData *getFXListDieModuleData() const { return m_moduleData; }
private:
	const FXListDieModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x10 - 0x0C];
};

class DieModuleInterface
{
public:
	virtual void onDie( const DamageInfo *damageInfo ) = 0;
};

class DieModule : public BehaviorModule, public DieModuleInterface
{
protected:
	// The ZH DieModule helper uses the module-data DieMuxData at +8.
	// Retail 0x0045CEA7 confirms that offset and the owner Object at +8.
	// Keep its SELECT_ANY body here with the retail onDie consumer.
	__declspec(noinline) Bool isDieApplicable( const DamageInfo *damageInfo ) const
	{
		return getFXListDieModuleData()->isDieApplicable(getObject(), damageInfo);
	}
};

class FXListDie : public DieModule
{
public:
	virtual void onDie( const DamageInfo *damageInfo );
};

//-------------------------------------------------------------------------------------------------
/** The die callback. */
//-------------------------------------------------------------------------------------------------
void FXListDie::onDie( const DamageInfo *damageInfo )
{
	if (!isDieApplicable(damageInfo))
		return;
	const FXListDieModuleData* d = getFXListDieModuleData();
	if (getFXListDieModuleData()->m_defaultDeathFX)
	{
		if (d->m_orientToObject)
		{
			Object *damageDealer = TheGameLogic->findObjectByID( damageInfo->m_sourceID );
			FXList::doFXObj(d->m_defaultDeathFX, getObject(), damageDealer);
		}
		else
		{
			FXList::doFXPos(d->m_defaultDeathFX, getObject()->getPosition());
		}
	}
}
