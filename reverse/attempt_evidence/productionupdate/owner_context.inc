// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /ICode/Libraries/Include /Ireference/shims/bfme2_ascii  /D_CRTIMP=
// stlport
//
// ProductionUpdate queue members (BFME 2), from the Generals Zero Hour
// ProductionUpdate.cpp and ProductionUpdate.h.
//
// Target facts. The ProductionUpdateInterface vftable 0x00C51478 sits at
// +0x20 (after UpdateModule), so these members get `this` at +0x20: the
// object is at [this-0x18] and the module data at [this-0x1C]. Slots 0-22
// are rowed here, except:
// - slot 8 (queueCreateUnit), slot 16 and slot 17 (getProductionCount);
// - slot 10 cancelUnitCreate (0x0049DC50) and slot 12 (0x0049CCF0);
// - slot 15 cancelAndRefundAllProduction (ProductionUpdate.cpp);
// - slot 21 firstProduction, folded into a shared getter.
// Slots without a ZH counterpart keep placeholder names.
// The queue head and tail are at +0x28/+0x2C, the unique id at +0x30 and the
// entry count at +0x34. +0x130 holds a vector of type names (slot 13) and
// +0x13C a flag that disables unit queueing (slot 0).
// addToProductionQueue and removeFromProductionQueue are the rowed 0x0049D526
// and 0x0049D57F, spelled through their Rva view here. The module data keeps
// MaxQueueEntries at +0x28.
// Each entry is a 0x54-byte Rva0049D1B1 (rowed ctor 0x0049D162) with:
// - type +4, object template +8, upgrade +0xC, production id +0x10;
// - percent complete +0x14, cost +0x28, a door/slot index +0x30 (-1 for
//   none), the upgrade's +0x70 copy at +0x38 and +0x3C (set by slot 14);
// - next/prev links at +0x48/+0x4C.
// The unit test (type 1 or 3) is the rowed out-of-line copy 0x00327C1B.
// BFME 2 differences from ZH:
// - queueUpgrade has no canProduceUpgrade check.
// - canAffordUpgrade and calcCostToBuild also take the object.
// - the withdrawal and refund are recorded against the player's +0x3BC
//   tracker, and the refund is the cost stored on the entry.
// - when the object's castle-member module (0x00395708) has its data flag
//   +0x18 set, the cost is also stored as a float at object +0x324.
// - addUpgrade and removeUpgrade take a trailing 0.
// - unit matches go through ThingTemplate::isEquivalentTo.
// - xfer is at version 7. Each entry also carries +0x18, +0x1C, quantities
//   +0x20/+0x24, the cost, the +0x34 flag and the slot; versions 4 and 5 add
//   a dummy Real, list<int> and Bool per entry. The tail keeps an unused
//   uint, the +0x118..+0x120 fields, the doors, both flag sets (0x000BB710)
//   and the version 2/3/6/7 fields.
// The STL containers come from STLport with the bfmelist/bfmealloc shims; a
// hand-written list view puts the dummy list's allocator temporary in a new
// frame slot, where retail reuses the dead parameter slot.

#include "ascii_string.h"
#include "unicode_string.h"
#include "Lib/Coord3D.h"
#include <string.h>
#include <bitset>
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1 };
enum ModelConditionFlagType { MODEL_NONE=0 };
enum DisabledType { DISABLED_NONE=0 };
enum KindOfType { KINDOF_NONE=0 };
enum CellShroudStatus { SHROUD_NONE=0 };
class Drawable; class Team; struct CreateMask; class Rva0049CD4FArg;

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define TRUE 1
#define FALSE 0
#define NULL 0

class Thing;
class ModuleData;
class Object;
class Player;
class Upgrade;


// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}
#include <vector>

class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

Xfer *Rva00460216XferList(Xfer *xfer, _STL::list<int> *list);
Xfer *xferAsciiStringVector(Xfer *xfer, _STL::vector<AsciiString> *vec);

typedef unsigned int AudioHandle;

class AudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
	virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
	virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
	virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69();
	virtual void v70(); virtual void v71(); virtual void v72(); virtual void v73(); virtual void v74();
	virtual void v75(); virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83(); virtual void v84();
	virtual void v85(); virtual void v86(); virtual void v87();
	virtual void xferAudioHandle(Xfer *xfer, AudioHandle *handle) = 0; // slot 88
};

extern AudioManager *TheAudio;

// ModelConditionFlags-sized bit set (0x4C bytes) with the rowed member xfer.
class Rva000BB710
{
public:
	void xfer(Xfer *xfer);
 unsigned int test(unsigned bit) const { return m_words[bit>>5] & (1u << (bit&31)); }
 void clear() { memset(m_words,0,sizeof(m_words)); }
 void set(unsigned bit,bool value=true) { if(value) m_words[bit>>5] |= 1u << (bit&31); else m_words[bit>>5] &= ~(1u << (bit&31)); }
private:
	unsigned int m_words[19];
};

enum CanMakeType
{
	CANMAKE_OK = 0,
	CANMAKE_NO_PREREQ,
	CANMAKE_NO_MONEY,
	CANMAKE_FACTORY_IS_DISABLED,
	CANMAKE_QUEUE_FULL
};

enum ProductionID
{
	PRODUCTIONID_INVALID = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_3E = 0x3E
};

struct Rva0049D0DEMask
{
	UnsignedInt m_bits[1];
};

// ZH Overridable: the next override is at +4 (rowed chain walk 0x001E35DF).
class Rva001E35DFView
{
public:
	const Rva001E35DFView *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Rva001E35DFView *m_nextOverride;
	Bool m_isOverride;
};

class ThingTemplate : public Rva001E35DFView
{
public:
	Int rva0033A69A(const Player *,int,int) const;
	Bool isEquivalentTo(const ThingTemplate *tt) const;
	const AsciiString &getName() const { return m_name; }
	UnsignedInt getProductionPriorityKind() const { return m_kindFlags[0] & (1 << 14); }

private:
	char m_unknown0C[0x64 - 0xC];
	AsciiString m_name; // +0x64
	char m_unknown68[0x7c-0x68];
	AsciiString m_upgradeCameos[5];
	char m_unknown90[0x108-0x90];
	UnsignedInt m_kindFlags[7]; // +0x108, 218 KindOfType bits
public:
	unsigned int productionSkipsDoor() const { return m_kindFlags[6]&0x8000; }
	const AsciiString *upgradeCameos() const { return m_upgradeCameos; }
	char m_unknown124[0x348-0x124];
	_STL::vector<AsciiString> m_auxiliaryTemplates;
	Real m_buildVariationDuration; // +354
};

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *,Team *,const CreateMask *,bool);
	const ThingTemplate *findTemplate(const AsciiString &key); // findTemplate
};

extern ThingFactory *TheThingFactory;

enum UpgradeType
{
	UPGRADE_TYPE_PLAYER = 0,
	UPGRADE_TYPE_OBJECT = 1
};

enum UpgradeStatusType
{
	UPGRADE_STATUS_INVALID = 0,
	UPGRADE_STATUS_IN_PRODUCTION = 1
};

enum ProductionType
{
	PRODUCTION_INVALID = 0,
	PRODUCTION_UNIT,
	PRODUCTION_UPGRADE,
	PRODUCTION_HORDE_UNIT
};

class UpgradeTemplate
{
public:
	UpgradeType getUpgradeType() const { return m_type; }
	UnsignedInt rva0026EF50(Player *player, Object *obj) const; // calcCostToBuild

	const AsciiString &getUpgradeName() const { return m_name; }

	char m_unknown00[4];
	UpgradeType m_type; // +4
	AsciiString m_name; // +8
	char m_unknown0C[0x28-0xC];
	AsciiString m_displayName;
	char m_unknown2C[0x40-0x2C];
	void *m_researchSound;
	int m_evaEvent;
	void *m_unitSound;
	char m_unknown4C[0x70-0x4C];
	Int m_bfme70; // +0x70
};

class UpgradeCenter
{
public:
	Bool rva0026F11A(Player *player, const UpgradeTemplate *upgrade, Object *obj, Bool displayReason); // canAffordUpgrade
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class Rva0039B795
{
	char m_unknown00[4];
};

class Rva0039B7AD;

// Money.
class Rva003B0D7C
{
public:
	UnsignedInt rva003B0CB3(UnsignedInt amount, Rva0039B795 *tracker, bool flag); // withdraw
	void rva003B0D7C(Int amount, Rva0039B7AD *tracker, bool flag); // deposit

private:
	char m_unknown00[0xC];
};

// The lookup's existing address-derived owner is retained: neither WB helper
// carries an original name. Native GetEntryToProcess passes Player+0x738 to
// both this RET12 lookup and the RET8, float-returning progress query.
class Rva0037EE4C
{
public:
	Int rva0037EE4C(const ThingTemplate *, Int, Int);
	Real rva0037E815(Int, Object *);
	char m_unknown00[0x14];
};

class Rva002A7461;
class Player
{
public:
 Rva002A7461 *revivalGate() { return reinterpret_cast<Rva002A7461 *>(reinterpret_cast<char *>(this)+0x60); }
	Bool allowedToBuild(const ThingTemplate *) const;
	void onUnitCreated(Object *,Object *);
	Rva003B0D7C *getMoney() { return &m_money; }
	Bool rva002AB87D(const UpgradeTemplate *upgrade) const; // hasUpgradeComplete
	Bool rva002AA8EF(const UpgradeTemplate *upgrade) const; // hasUpgradeInProduction
	Upgrade *rva002AE329(const UpgradeTemplate *upgrade, UpgradeStatusType status, Int flag); // addUpgrade
	void rva002ADAC3(const UpgradeTemplate *upgrade, Int flag); // removeUpgrade

	char m_unknown00[0x54];
	Int m_playerIndex;
	char m_unknown58[0x90-0x58];
	Rva003B0D7C m_money; // +0x90
	char m_unknown9C[0x2ec-0x9c];
	Team *m_defaultTeam;
	char m_unknown2F0[0x3bc-0x2f0];
	Rva0039B795 m_tracker; // +0x3BC
	char m_unknown3C0[0x738 - 0x3C0];
	Rva0037EE4C m_revivalTracker; // +0x738 (WB uses +0x740)
};

enum ObjectID
{
	INVALID_ID = 0
};

enum ExitDoorType
{
	DOOR_1 = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

#define _GAME_TYPE_H_
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Module;

// ZH ExitInterface slots 0..10 (BFME 1 UpdateModule.h); BFME 2 adds slot 11.
class ExitInterface
{
public:
	virtual Bool isExitBusy() const = 0;
	virtual ExitDoorType reserveDoorForExit(const ThingTemplate *objType, Object *specificObject) = 0;
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor) = 0;
	virtual void exitObjectByBudding(Object *newObj, Object *budHost) = 0;
	virtual void unreserveDoorForExit(ExitDoorType exitDoor) = 0;
	virtual void exitObjectInAHurry(Object *newObj) = 0;
	virtual void setRallyPoint(const void *pos) = 0;
	virtual const void *getRallyPoint() const = 0;
	virtual Bool useSpawnRallyPoint() const = 0;
	virtual Bool getNaturalRallyPoint(void *rallyPoint, Bool offset) const = 0;
	virtual Bool getExitPosition(void *exitPosition, float *orientation) const = 0;
	virtual void exitSlot11() = 0;
};

class BehaviorModule;
class ProductionUpdateInterface;

class ProductionContainView; class ProductionAIUpdateView;
class Object
{
public:
 const ThingTemplate *getTemplate() const { return m_template; }
	Player *getControllingPlayer() const;
 void rva0028AE6D();
 __forceinline void setProductionCondition() { if(m_modelConditionFlags.test(332)) return; m_modelConditionFlags.set(332); rva0028AE6D(); }
 __forceinline void clearProductionCondition() { if(!m_modelConditionFlags.test(332)) return; m_modelConditionFlags.set(332,false); rva0028AE6D(); } void rva0028CFB2(const int *,const int *);
 void setProducer(Object *); CellShroudStatus getShroudStatusForPlayer(int) const;
 void setSpecialModelConditionState(ModelConditionFlagType,unsigned int);
 void teleportTo(const Coord3D *,bool); void setStatus(ObjectStatusTypes,bool);
 void updateUpgradeModules(); void setDisabledUntil(DisabledType,unsigned int);
 bool clearDisabled(DisabledType); bool isKindOf(KindOfType) const;
 bool isLocallyControlled() const; void rva00293077(const void *);
 void rva002900FA(int);
	ExitInterface *getObjectExitInterface() const;
	Module *findUpdateModule(NameKeyType key) const { return findModule(key); }
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool rva00290D2B(const UpgradeTemplate *upgrade) const; // hasUpgrade
	Bool rva002940B9(const UpgradeTemplate *upgrade); // affectedByUpgrade
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }

	char m_unknown00[4]; const ThingTemplate *m_template;
 char m_unknown08[0x38-8]; Coord3D m_position;
 char m_unknown44[0x74-0x44]; ObjectID m_id; ObjectID m_containerID;
 char m_unknown7C[0x88-0x7c]; AsciiString m_name;
 char m_unknown8C[0x10c-0x8c]; Rva000BB710 m_modelConditionFlags;
 char m_unknown158[0x244-0x158];
 BehaviorModule **m_behaviors; // +0x244, null-terminated
	char m_unknown248[8]; ProductionContainView *m_contain;
 char m_unknown254[4]; ProductionAIUpdateView *m_ai;
 char m_unknown25C[8]; void *m_experience;
 char m_unknown268[0x324-0x268];
	Real m_bfme324; // +0x324
 char m_unknown328[0x438-0x328]; unsigned char m_flag438;
 char m_unknown439[0x45c-0x439]; int m_handle45C;

protected:
	Module *findModule(NameKeyType key) const;
};

struct Rva00395708Data
{
	char m_unknown00[0x18];
	Bool m_flag; // +0x18
};

class Module
{
public:
	char m_unknown00[4];
	const Rva00395708Data *m_moduleData; // +4
};

class CastleBehavior
{
public:
	static Module *rva000395708(Object *obj);
};

class ProductionEntry
{
public:
	Bool getProductionObject() const;
};

// ProductionEntry.
class Rva0049D1B1
{
public:
	Rva0049D1B1() throw();
	virtual ~Rva0049D1B1();

	// type 1 or 3, the rowed out-of-line copy 0x00327C1B
	Bool isUnit() const { return ((const ProductionEntry *)this)->getProductionObject(); }
	ProductionType getProductionType() const { return m_type; }
 Int getProductionID() const { return m_productionID; }
	const ThingTemplate *getProductionObject() const { return m_objectToProduce; }
	const UpgradeTemplate *getProductionUpgrade() const { return m_upgradeToResearch; }

	ProductionType m_type; // +4
	const ThingTemplate *m_objectToProduce; // +8
	const UpgradeTemplate *m_upgradeToResearch; // +0xC
	Int m_productionID; // +0x10
	Real m_percentComplete; // +0x14
	Real m_bfme18; // +0x18
	Int m_bfme1C; // +0x1C
	Int m_productionQuantityTotal; // +0x20
	Int m_productionQuantityProduced; // +0x24
	Int m_cost; // +0x28
	ExitDoorType m_exitDoor; // +0x2C
	Int m_bfme30; // +0x30
	Bool m_bfme34; // +0x34
	Int m_bfme38; // +0x38
	Int m_bfme3C; // +0x3C
	AsciiString m_name; // +40
	Bool m_slave; // +44
	char m_unknown45[3];
	Rva0049D1B1 *m_next; // +0x48
	Rva0049D1B1 *m_prev; // +0x4C
	char m_unknown50[0x54 - 0x50];
};

class ProductionUpdateModuleData
{
public:
	char m_unknown00[8];
	Int m_numDoorAnimations;
	char m_unknown0C[0x18-0xc];
	UnsignedInt m_constructionCompleteDuration;
	char m_unknown1C[0x28-0x1c];
	UnsignedInt m_maxQueueEntries; // +0x28
	char m_unknown2C[4]; bool m_noExperience; char m_unknown31[3];
	unsigned m_specialDuration; unsigned m_completeDuration; char m_unknown3C[4];
	bool m_inheritVeterancy; bool m_economyCondition; char m_unknown42[2];
	AsciiString m_economyKey; void *m_economySound;
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

// BehaviorModuleInterface: the per-module interface queries; retail reads
// getProductionUpdateInterface from slot 28 (+0x70).
class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
	virtual void bmi01();
	virtual void bmi02();
	virtual void bmi03();
	virtual void bmi04();
	virtual void bmi05();
	virtual void bmi06();
	virtual void bmi07();
	virtual void bmi08();
	virtual void bmi09();
	virtual void bmi10();
	virtual void bmi11();
	virtual void bmi12();
	virtual void bmi13();
	virtual void bmi14();
	virtual void bmi15();
	virtual void bmi16();
	virtual void bmi17();
	virtual void bmi18();
	virtual void bmi19();
	virtual void bmi20();
	virtual void bmi21();
	virtual void bmi22();
	virtual void bmi23();
	virtual void bmi24();
	virtual void bmi25();
	virtual void bmi26();
	virtual void bmi27();
	virtual ProductionUpdateInterface *getProductionUpdateInterface();	// +0x70
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	void xfer(Xfer *xfer);

protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class ProductionUpdateInterface
{
public:
	virtual CanMakeType rva0049CFCD() const;
	virtual CanMakeType canQueueUpgrade(const UpgradeTemplate *upgrade) const;
	virtual ProductionID requestUniqueUnitID();
	virtual Bool queueUpgrade(const UpgradeTemplate *upgrade);
	virtual void cancelUpgrade(const UpgradeTemplate *upgrade);
	virtual void rva0049CC9D(const ThingTemplate *unitType, Bool five);
	virtual Bool isUpgradeInQueue(const UpgradeTemplate *upgrade) const;
	virtual UnsignedInt countUnitTypeInQueue(const ThingTemplate *unitType) const;
	virtual void i08();
	virtual Bool rva0049CC36(ProductionID productionID) const;
	virtual void cancelUnitCreate(ProductionID productionID);
	virtual void rva0049CC61(const ThingTemplate *unitType);
	virtual void i12();
	virtual void rva0049F8A9(const ThingTemplate *unitType, Bool cancel);
	virtual void rva0049CC15(ProductionID productionID, Int value);
	virtual void cancelAndRefundAllProduction();
	virtual void rva0049DEC8();
	virtual void i17();
	virtual UnsignedInt rva0049CEAE(const ThingTemplate *unitType) const;
	virtual UnsignedInt rva0049CEE1(Int value) const;
	virtual UnsignedInt rva0049D0DE(const Rva0049D0DEMask *mask) const;
	virtual const Rva0049D1B1 *firstProduction() const;
	virtual const Rva0049D1B1 *nextProduction(const Rva0049D1B1 *p) const;
};

class DieModuleInterface
{
public:
	virtual void onDie();
};

class Rva0049D526
{
public:
	void rva0049D526(void *entry); // addToProductionQueue
	void rva0049D57F(void *entry); // removeFromProductionQueue
};

enum
{
	DOOR_COUNT_MAX = 4
};

struct DoorInfo
{
	UnsignedInt m_doorOpenedFrame;
	UnsignedInt m_doorWaitOpenFrame;
	UnsignedInt m_doorClosedFrame;
	Bool m_holdOpen;
};

// Native-only supplemental views for the update bank. No inferred full class ABI.
class OpaqueRefCounted { public: void Release_Ref(); };
struct OpaqueRefElement4 { OpaqueRefCounted *referent; };
struct BfmeAudioEventPrefix136 {
 BfmeAudioEventPrefix136(const OpaqueRefElement4 &,int);
 BfmeAudioEventPrefix136(const OpaqueRefElement4 &,ObjectID);
 virtual ~BfmeAudioEventPrefix136();
 unsigned char opaque[132];
};
class Rva002D9531 { public: void rva002D9531(int); };
class Rva0033F15DDwordSlot { public: void set(int); };
class Rva002AE98B { public: float rva002AE98B(const AsciiString *); };
class Rva0049D3BC { public: void rva0049D3BC(); };
struct Rva002A7557In;
class Rva002A7461 { public: bool rva002A7557(Rva002A7557In *,int); };
class Rva0037E6E8 { public: float rva0037E815(int,Object *); };
class Rva0037E421 { public: void *rva0037E451(int); void *rva0037E421(int); };
struct ProductionRevivalCount { char m_pad[0x98]; int m_98; };
class UnitRevivalTracker { public: Object *productionSystemNewObject(unsigned int,const Coord3D *); };
class Rva0039ADF3 { public: bool rva0039AE04() const; };
class ExperienceTracker { public: void rva0039B315(float,bool,bool,bool,bool); };
struct ProductionExperienceView { char pad[0x24]; int level; int next; };
class Rva003BD306Target { public: void rva0039B2C7(int,int); };
class Rva004DC8E7AsciiField { public: AsciiString get() const; };
class ScriptEngine { public:
 void rva00357F11(int,const AsciiString &,int);
 bool didUnitExist(const AsciiString &);
 void addObjectToCache(Object *,const AsciiString &);
 void rva00357960(const AsciiString &,Object *);
};
extern ScriptEngine *TheScriptEngine;
class Rva00358752Opaque { public: Object *lookupUnitByValue(AsciiString); };
class Thing { public: Drawable *getDrawable() const; void setPosition(const Coord3D *); void setOrientation(float); };
class Rva002390CB { public: int opaque00; OpaqueRefElement4 ref; ~Rva002390CB() { if(ref.referent) ref.referent->Release_Ref(); } };
class Drawable { public:
 void setFullyObscuredByShroud(bool); void rva002723C0(int); void rva00274176(bool);
 void setDrawableHidden(bool); void fadeIn(unsigned int);
 Rva002390CB rva0049D114();
 // Native shared empty RET hook; owner/identity still needs fold proof.
 void rva000B3FD0();
};
class Rva002707FA { public: void rva002707FA(unsigned char); };
class Rva0028CBFD { public: void rva0028CBFD(); };
class SlaveWatcherBehavior { public: void rva00484869(int); };
class Rva0049CD24 { public: void rva0049CD24(Object *); };
struct CreateMask { unsigned int bits[4]; CreateMask() { memset(bits,0,sizeof(bits)); } };
struct ProductionPlayerListView { char pad[0x10]; Player *localPlayer; };
class PlayerList; extern PlayerList *ThePlayerList;
struct ProductionAIDataView { char pad[0xbb]; bool createdFlag; };
class Pathfinder { public: int MoveAlliesAwayFromDestination(Object *,const Coord3D *,const Coord3D *); };
struct ProductionAIView { char pad[0x10]; Pathfinder *pathfinder; Pathfinder *getPathfinder() const { return pathfinder; } char pad14[4]; ProductionAIDataView *data; };
class AI; extern AI *TheAI;
// Pending data ownership: these draft names have no definitions. Exact code bytes
// do not prove their bindings because DIR32 operands are masked by the byte gate.
// The existing rate owners are shared across194 files; two are live-claimed.
// See productionupdate/data-bindings.tsv before landing; do not create aliases.
extern int BfmeLogicFramesPerSecond;
extern int BfmeClientFramesPerSecond;
extern const unsigned int ProductionDoorOpeningFlags[4];
extern const unsigned int ProductionDoorClosingFlags[4];
extern const unsigned int ProductionDoorWaitingOpenFlags[4];
enum EvaEventID { EVA_NONE=0 };
class Eva { public: bool reportEvaEvent(EvaEventID,const Coord3D *,const Coord3D *); };
extern Eva *TheEva;
enum RadarEventType { RADAR_NONE=0 };
class Radar { public: void createEvent(const Coord3D *,RadarEventType,float); };
extern Radar *TheRadar;
class FXList { public: static void doFXObj(const FXList *,const Object *,const Object *); };
class FXListStore { public: const FXList *findFXList(const char *) const; };
extern FXListStore *TheFXListStore;
class GameTextInterface { public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0c();
 virtual void s10();virtual void s14();virtual void s18();virtual void s1c();
 virtual void s20();virtual void s24();virtual void s28();virtual void s2c();
 virtual void s30();virtual void s34();virtual void s38();
 virtual UnicodeString fetch(const char *,bool * =0);
};
extern GameTextInterface *TheGameText;
class InGameUI; extern InGameUI *TheInGameUI;
class ControlBar; extern ControlBar *TheControlBar;
struct ProductionControlBarView { char pad[0x28]; bool dirty; };
struct ProductionDrawableView { char pad[0xfc]; Object *object; };
class TerrainLogic; extern TerrainLogic *TheTerrainLogic;
class RespawnUpdate { public: void triggerRevival(Object *); };
struct Rva0028F633 { Rva0028F633(int,int); unsigned int bits[32]; };
namespace _STL {
}
class DrawableList: public _STL::list<Drawable *> {public: ~DrawableList() throw();};
class PickAndPlayInfo;
class Rva004D92FE { public: Rva004D92FE(); char pad[8]; Drawable *drawTarget; char tail[24]; };
class GameMessage { public: enum Type { MSG_NONE=0 }; };
void pickAndPlayUnitVoiceResponse(const DrawableList *,GameMessage::Type,PickAndPlayInfo *);
// WB1207EF0 and native caller prove this member ABI; provider corrected and byte-verified.
struct Rva0049DF81Input;

class ProductionAudioView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual unsigned int addEvent(const BfmeAudioEventPrefix136 *);
virtual void s68();
virtual void stopEvent(unsigned int);
virtual void s70();
virtual void s74();
virtual void s78();
virtual void s7c();
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sa0();
virtual void sa4();
virtual void sa8();
virtual void sac();
virtual void sb0();
virtual void sb4();
virtual void sb8();
virtual void sbc();
virtual void sc0();
virtual void sc4();
virtual void sc8();
virtual void scc();
virtual bool isPlaying(unsigned int);
};

class ProductionInGameUIView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void message(UnicodeString,...);
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual void s78();
virtual void s7c();
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sa0();
virtual void sa4();
virtual void sa8();
virtual void sac();
virtual void sb0();
virtual void sb4();
virtual void sb8();
virtual void sbc();
virtual void sc0();
virtual void sc4();
virtual void sc8();
virtual void scc();
virtual void sd0();
virtual void sd4();
virtual void sd8();
virtual void sdc();
virtual void se0();
virtual void se4();
virtual void se8();
virtual void sec();
virtual void sf0();
virtual void sf4();
virtual void sf8();
virtual void sfc();
virtual void s100();
virtual void s104();
virtual void s108();
virtual void s10c();
virtual void s110();
virtual void s114();
virtual void s118();
virtual void s11c();
virtual void s120();
virtual void s124();
virtual void s128();
virtual Drawable *getSelectedDrawable();
};

class ProductionAIUpdateView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual void s78();
virtual void s7c();
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sa0();
virtual void sa4();
virtual void sa8();
virtual void sac();
virtual void sb0();
virtual void sb4();
virtual void sb8();
virtual void sbc();
virtual void sc0();
virtual void sc4();
virtual void sc8();
virtual void scc();
virtual void sd0();
virtual void sd4();
virtual void sd8();
virtual void sdc();
virtual void se0();
virtual void se4();
virtual void se8();
virtual void sec();
virtual void sf0();
virtual void sf4();
virtual void sf8();
virtual void sfc();
virtual void s100();
virtual void s104();
virtual void s108();
virtual void s10c();
virtual void s110();
virtual void s114();
virtual void s118();
virtual void s11c();
virtual void s120();
virtual void s124();
virtual void s128();
virtual void s12c();
virtual void s130();
virtual void s134();
virtual void s138();
virtual void s13c();
virtual void s140();
virtual void s144();
virtual void s148();
virtual void s14c();
virtual void s150();
virtual void s154();
virtual void s158();
virtual void s15c();
virtual void s160();
virtual void s164();
virtual bool s168();
virtual void s16c();
virtual void s170();
virtual void s174();
virtual void s178();
virtual void s17c();
virtual void s180();
virtual void s184();
virtual void s188();
virtual void s18c();
virtual void s190();
virtual void s194();
virtual void s198();
virtual void s19c();
virtual void s1a0();
virtual void s1a4();
virtual void s1a8();
virtual void s1ac();
virtual void s1b0();
virtual void s1b4();
virtual void s1b8();
virtual void s1bc();
virtual void s1c0();
virtual void s1c4();
virtual void s1c8();
virtual void s1cc();
virtual void s1d0();
virtual void s1d4();
virtual void s1d8();
virtual void s1dc();
virtual void s1e0();
virtual void s1e4();
virtual void s1e8();
virtual void s1ec();
virtual void s1f0();
virtual void s1f4();
virtual void s1f8();
virtual void s1fc();
virtual void s200();
virtual void s204();
virtual void s208();
virtual void s20c();
virtual void s210();
virtual void s214();
virtual void s218();
virtual void s21c();
virtual void s220();
virtual void s224();
virtual void s228();
virtual void s22c();
virtual void s230();
virtual void s234(Object *);
};

class ProductionSlaveInterface { public:
virtual void s00();
virtual void setMaster(Object *);
};

class ProductionBehaviorView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual ProductionSlaveInterface *getSlave();
};

class ProductionHordeInterface { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual AsciiString getTemplateName();
virtual int getExtraCount();
};

class ProductionContainView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual ProductionAIUpdateView *getAI();
virtual ProductionHordeInterface *getHorde();
};

class ProductionTerrainView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void terrainHeight(float,float,float *,int,int);
};

class ProductionUpdate : public UpdateModule, public ProductionUpdateInterface, public DieModuleInterface
{
public:
 virtual UpdateSleepTime update();
 void rva0049E368(); void rva0049CF25();
 void rva0049DF81(Rva0049DF81Input *,Object *);
 Int calcTotalProductionFrames(Rva0049CD4FArg *);

	virtual CanMakeType rva0049CFCD() const;
	virtual CanMakeType canQueueUpgrade(const UpgradeTemplate *upgrade) const;
	virtual ProductionID requestUniqueUnitID();
	virtual Bool queueUpgrade(const UpgradeTemplate *upgrade);
	virtual void cancelUpgrade(const UpgradeTemplate *upgrade);
	virtual void rva0049CC9D(const ThingTemplate *unitType, Bool five);
	virtual Bool isUpgradeInQueue(const UpgradeTemplate *upgrade) const;
	virtual UnsignedInt countUnitTypeInQueue(const ThingTemplate *unitType) const;
	virtual Bool rva0049CC36(ProductionID productionID) const;
	virtual void rva0049CC61(const ThingTemplate *unitType);
	virtual void rva0049F8A9(const ThingTemplate *unitType, Bool cancel);
	virtual void rva0049CC15(ProductionID productionID, Int value);
	virtual void cancelAndRefundAllProduction();
	virtual void rva0049DEC8();
	virtual UnsignedInt rva0049CEAE(const ThingTemplate *unitType) const;
	virtual UnsignedInt rva0049CEE1(Int value) const;
	virtual UnsignedInt rva0049D0DE(const Rva0049D0DEMask *mask) const;
	virtual const Rva0049D1B1 *nextProduction(const Rva0049D1B1 *p) const;

	static ProductionUpdateInterface *getProductionUpdateInterfaceFromObject(Object *obj);
	const Rva0049D1B1 *GetEntryToProcess();

protected:
	virtual void xfer(Xfer *xfer);

	const ProductionUpdateModuleData *getProductionUpdateModuleData() const
	{
		return (const ProductionUpdateModuleData *)m_moduleData;
	}
	void addToProductionQueue(Rva0049D1B1 *production)
	{
		((Rva0049D526 *)this)->rva0049D526(production);
	}
	void removeFromProductionQueue(Rva0049D1B1 *production)
	{
		((Rva0049D526 *)this)->rva0049D57F(production);
	}

	Rva0049D1B1 *m_productionQueue; // +0x28
	Rva0049D1B1 *m_productionQueueTail; // +0x2C
	ProductionID m_uniqueID; // +0x30
	UnsignedInt m_productionCount; // +0x34
	UnsignedInt m_constructionCompleteFrame; // +0x38
	DoorInfo m_doors[DOOR_COUNT_MAX]; // +0x3C
	Rva000BB710 m_clearFlags; // +0x7C
	Rva000BB710 m_setFlags; // +0xC8
	Bool m_flagsDirty; // +0x114
	UnsignedInt m_bfme118; // +0x118
	Bool m_bfme11C; // +0x11C
	ObjectID m_bfme120; // +0x120
	_STL::list<ObjectID> m_createdAuxiliary; // +124
	UnsignedInt m_bfme128; // +0x128
	AudioHandle m_bfme12C; // +0x12C
	_STL::vector<AsciiString> m_bfme130; // +0x130
	Bool m_bfme13C; // +0x13C
};

// WB 0x1203E30 names this routine. Native 49CFEB..49D07A first prefers
// unit entries with KindOfType bit14, then horde entries whose revival
// progress is at least one, otherwise the head. Both walks use the native
// interface's slot22 (+0x58); WB's corresponding slot is +0x54.
const Rva0049D1B1 *ProductionUpdate::GetEntryToProcess()
{
	const Rva0049D1B1 *entry;
	for (entry = m_productionQueue; entry; entry = nextProduction(entry))
	{
		if (entry->isUnit() && entry->getProductionObject()->getProductionPriorityKind())
			return entry;
	}
	for (entry = m_productionQueue; entry; entry = nextProduction(entry))
	{
		if (entry->getProductionType() == PRODUCTION_HORDE_UNIT)
		{
			Rva0037EE4C *tracker = &getObject()->getControllingPlayer()->m_revivalTracker;
			Int productionID = entry->m_productionID;
			Int index = tracker->rva0037EE4C(entry->getProductionObject(), productionID, 0);
			if (tracker->rva0037E815(index, getObject()) >= 1.0f)
				return entry;
		}
	}
	return m_productionQueue;
}

// ?queueUpgrade@ProductionUpdate@@UAE_NPBVUpgradeTemplate@@@Z @0x0049D867 315B
Bool ProductionUpdate::queueUpgrade( const UpgradeTemplate *upgrade )
{

	// sanity
	if( upgrade == NULL )
		return FALSE;

	// get the player
	Player *player = getObject()->getControllingPlayer();

	// sanity check to make sure we can build this upgrade
	if( upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER &&
			TheUpgradeCenter->rva0026F11A( player, upgrade, getObject(), FALSE ) == FALSE )
		return FALSE;
	else if( upgrade->getUpgradeType() == UPGRADE_TYPE_OBJECT &&
					 (getObject()->rva00290D2B( upgrade ) == TRUE ||
					  getObject()->rva002940B9( upgrade ) == FALSE) )
		return FALSE;

	// you cannot queue the production of an upgrade twice in this queue
	if( isUpgradeInQueue( upgrade ) == TRUE )
		return FALSE;

	//
	// you cannot queue a player upgrade production if you are producing one already somewhere else
	// (or that somewhere else could even possibly be here)
	//
	if( upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER &&
      (player->rva002AB87D( upgrade ) || player->rva002AA8EF( upgrade )) )
		return FALSE;

	if (m_productionCount >= getProductionUpdateModuleData()->m_maxQueueEntries)
		return FALSE;

	// allocate a new production entry
	Rva0049D1B1 *production = new Rva0049D1B1;

	// assing production entry data
	production->m_productionID = 0;
	production->m_type = PRODUCTION_UPGRADE;
	production->m_upgradeToResearch = upgrade;
	production->m_bfme38 = upgrade->m_bfme70;

	// take the cost for the build away from the player
	production->m_cost = upgrade->rva0026EF50( player, getObject() );
	player->getMoney()->rva003B0CB3( production->m_cost, &player->m_tracker, true );

	Object *obj = getObject();
	Module *castle = CastleBehavior::rva000395708( obj );
	if( castle && castle->m_moduleData->m_flag )
		obj->m_bfme324 = (Real)production->m_cost;

	// tie to the end of the production queue
	addToProductionQueue( production );

	// add this upgrade as in progress in the player
	player->rva002AE329( upgrade, UPGRADE_STATUS_IN_PRODUCTION, 0 );

	return TRUE;  // queued

}  // end queueUpgrade

// ?cancelUpgrade@ProductionUpdate@@UAEXPBVUpgradeTemplate@@@Z @0x0049D9A2 146B
void ProductionUpdate::cancelUpgrade( const UpgradeTemplate *upgrade )
{

	// sanity
	if( upgrade == NULL )
		return;

	// get the player
	Player *player = getObject()->getControllingPlayer();

	// sanity, you can't cancel it if the player isn't actually building one
	if( upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER && player->rva002AA8EF( upgrade ) == FALSE )
		return;

	//
	// find the production entry for this upgrade in the queue here, there can only be one
	// of this type in the queue
	//
	Rva0049D1B1 *production;
	for( production = m_productionQueue; production; production = production->m_next )
	{

		if( production->m_type == PRODUCTION_UPGRADE &&
				production->m_upgradeToResearch == upgrade )
			break;

	}  // end for

	// sanity, entry not found
	if( production == NULL )
		return;

	// refund the cost paid back to the player
	player->getMoney()->rva003B0D7C( production->m_cost, (Rva0039B7AD *)&player->m_tracker, true );

	// remove this production from the queue
	removeFromProductionQueue( production );

	// delete production instance
	::delete production;

	//
	// remove the IN_PRODUCTION status of this upgrade from the player, object upgrades don't
	// have any other IN_PRODUCTION status other than their existence in the build queue
	//
	if( upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER )
		player->rva002ADAC3( upgrade, 0 );

}  // end cancelUpgrade

// ?rva0049CFCD@ProductionUpdate@@UBE?AW4CanMakeType@@XZ @0x0049CFCD 30B
// Slot 0, where ZH has canQueueCreateUnit; BFME 2's takes no argument and
// refuses while the +0x13C flag is set.
CanMakeType ProductionUpdate::rva0049CFCD() const
{
	if( m_bfme13C )
		return CANMAKE_FACTORY_IS_DISABLED;

	if (m_productionCount >= getProductionUpdateModuleData()->m_maxQueueEntries)
		return CANMAKE_QUEUE_FULL;

	return CANMAKE_OK;
}

// ?canQueueUpgrade@ProductionUpdate@@UBE?AW4CanMakeType@@PBVUpgradeTemplate@@@Z @0x0049CFA9 36B
CanMakeType ProductionUpdate::canQueueUpgrade( const UpgradeTemplate *upgrade ) const
{
	if (m_productionCount >= getProductionUpdateModuleData()->m_maxQueueEntries)
		return CANMAKE_QUEUE_FULL;

	return getObject()->testStatus( OBJECT_STATUS_BFME_3E ) ? CANMAKE_FACTORY_IS_DISABLED : CANMAKE_OK;
}

// ?requestUniqueUnitID@ProductionUpdate@@UAE?AW4ProductionID@@XZ @0x0049E142 10B
ProductionID ProductionUpdate::requestUniqueUnitID( void )
{
	ProductionID tmp = m_uniqueID;
	m_uniqueID = (ProductionID)(m_uniqueID+1);
	return tmp;
}

// ?rva0049CC9D@ProductionUpdate@@UAEXPBVThingTemplate@@_N@Z @0x0049CC9D 83B
// Cancels the last one (or five) queued units of the type, newest first.
void ProductionUpdate::rva0049CC9D( const ThingTemplate *unitType, Bool five )
{
	Int count = five ? 5 : 1;
	Rva0049D1B1 *production = m_productionQueueTail;
	while( count )
	{
		if( production == NULL )
			break;
		if( production->isUnit() && unitType->isEquivalentTo( production->m_objectToProduce ) )
		{
			cancelUnitCreate( (ProductionID)production->m_productionID );
			--count;
			production = m_productionQueueTail;
		}
		else
			production = production->m_prev;
	}
}

// ?isUpgradeInQueue@ProductionUpdate@@UBE_NPBVUpgradeTemplate@@@Z @0x0049CDF9 47B
Bool ProductionUpdate::isUpgradeInQueue( const UpgradeTemplate *upgrade ) const
{
	const Rva0049D1B1 *production;

	for( production = firstProduction(); production; production = nextProduction( production ) )
		if( production->getProductionType() == PRODUCTION_UPGRADE &&
				production->getProductionUpgrade() == upgrade )
			return TRUE;

	return FALSE;  // not in queue

}  // end isUpgradeInQueue

// ?countUnitTypeInQueue@ProductionUpdate@@UBEIPBVThingTemplate@@@Z @0x0049CE28 59B
UnsignedInt ProductionUpdate::countUnitTypeInQueue( const ThingTemplate *unitType ) const
{
	UnsignedInt count = 0;
	const Rva0049D1B1 *production;

	for( production = firstProduction(); production; production = nextProduction( production ) )
		if( production->getProductionType() == PRODUCTION_UNIT &&
				unitType->isEquivalentTo( production->getProductionObject() ) )
			count++;

	return count;

}  // end countUnitTypeInQueue

// ?rva0049CC36@ProductionUpdate@@UBE_NW4ProductionID@@@Z @0x0049CC36 43B
// Is a unit with this production id in the queue.
Bool ProductionUpdate::rva0049CC36( ProductionID productionID ) const
{
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
		if( production->isUnit() && production->m_productionID == productionID )
			return TRUE;

	return FALSE;
}

// ?rva0049CC61@ProductionUpdate@@UAEXPBVThingTemplate@@@Z @0x0049CC61 60B
// Cancels the oldest queued unit of the type.
void ProductionUpdate::rva0049CC61( const ThingTemplate *unitType )
{
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
	{
		if( production->isUnit() && unitType->isEquivalentTo( production->m_objectToProduce ) )
		{
			cancelUnitCreate( (ProductionID)production->m_productionID );
			return;
		}
	}
}

// ?rva0049F8A9@ProductionUpdate@@UAEXPBVThingTemplate@@_N@Z @0x0049F8A9 113B
// Without the flag, records the type's name in the +0x130 list; with it,
// cancels every unfinished queued unit of the type.
void ProductionUpdate::rva0049F8A9( const ThingTemplate *unitType, Bool cancel )
{
	if( !cancel )
	{
		m_bfme130.push_back( unitType->getName() );
		return;
	}

	Rva0049D1B1 *production = m_productionQueue;
	while( production )
	{
		ProductionType type = production->m_type;
		if( production->m_percentComplete < 100.0f &&
				(type == PRODUCTION_UNIT || type == PRODUCTION_HORDE_UNIT) &&
				unitType->isEquivalentTo( production->m_objectToProduce ) )
		{
			Rva0049D1B1 *next = production->m_next;
			cancelUnitCreate( (ProductionID)production->m_productionID );
			production = next;
		}
		else
			production = production->m_next;
	}
}

// ?rva0049CC15@ProductionUpdate@@UAEXW4ProductionID@@H@Z @0x0049CC15 33B
// Sets the +0x3C field of the entry with this production id.
void ProductionUpdate::rva0049CC15( ProductionID productionID, Int value )
{
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
	{
		if( production->m_productionID == productionID )
		{
			production->m_bfme3C = value;
			return;
		}
	}
}

// ?rva0049CEAE@ProductionUpdate@@UBEIPBVThingTemplate@@@Z @0x0049CEAE 51B
// Counts the queued units (and hordes) of the type.
UnsignedInt ProductionUpdate::rva0049CEAE( const ThingTemplate *unitType ) const
{
	UnsignedInt count = 0;
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
		if( production->isUnit() && unitType->isEquivalentTo( production->m_objectToProduce ) )
			count++;
	return count;
}

// ?rva0049CEE1@ProductionUpdate@@UBEIH@Z @0x0049CEE1 27B
// Counts the entries whose +0x30 field equals the value.
UnsignedInt ProductionUpdate::rva0049CEE1( Int value ) const
{
	UnsignedInt count = 0;
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
		if( value == production->m_bfme30 )
			count++;
	return count;
}

// ?getProductionUpdateInterfaceFromObject@ProductionUpdate@@SAPAVProductionUpdateInterface@@PAVObject@@@Z @0x0049CEFC 41B
// ZH's static lookup: the first behavior module that answers
// getProductionUpdateInterface.
ProductionUpdateInterface *ProductionUpdate::getProductionUpdateInterfaceFromObject( Object *obj )
{
	if( obj == NULL )
		return NULL;

	for( BehaviorModule **u = obj->getBehaviorModules(); *u; ++u )
	{
		ProductionUpdateInterface *pui = (*u)->getProductionUpdateInterface();
		if( pui )
			return pui;
	}

	return NULL;
}

// ?rva0049D0DE@ProductionUpdate@@UBEIPBURva0049D0DEMask@@@Z @0x0049D0DE 54B
// Counts the entries whose +0x30 index (-1 for none) is set in the mask.
UnsignedInt ProductionUpdate::rva0049D0DE( const Rva0049D0DEMask *mask ) const
{
	UnsignedInt count = 0;
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
	{
		UnsignedInt index = production->m_bfme30;
		if( index != (UnsignedInt)-1 && (mask->m_bits[index >> 5] & (1 << (index & 31))) )
			count++;
	}
	return count;
}

// ?nextProduction@ProductionUpdate@@UBEPBVRva0049D1B1@@PBV2@@Z @0x0049E14C 18B
const Rva0049D1B1 *ProductionUpdate::nextProduction( const Rva0049D1B1 *p ) const
{
	return p ? p->m_next : NULL;
}

// ?rva0049DEC8@ProductionUpdate@@UAEXXZ @0x0049DEC8 154B
// Slot 16: cancels and refunds the queue, then sends the object held at
// +0x120 out through door 1 unless it has a RespawnUpdate, and finally
// calls the exit interface's slot 11.
void ProductionUpdate::rva0049DEC8()
{
	cancelAndRefundAllProduction();
	ExitInterface *exitInterface = getObject()->getObjectExitInterface();
	ObjectID id = m_bfme120;
	if( id != INVALID_ID )
	{
		Object *obj = TheGameLogic->findObjectByID( id );
		if( obj )
		{
			static NameKeyType key_RespawnUpdate = NAMEKEY( "RespawnUpdate" );
			if( obj->findUpdateModule( key_RespawnUpdate ) == NULL )
				exitInterface->exitObjectViaDoor( obj, DOOR_1 );
		}
	}
	if( exitInterface )
		exitInterface->exitSlot11();
}

// ?xfer@ProductionUpdate@@MAEXPAVXfer@@@Z @0x0049F91A 1192B
// The ZH xfer at version 7. Over ZH it adds the entry's +0x18/+0x1C, cost,
// +0x34 flag and slot, the object's +0x118/+0x11C/+0x120 and four gated
// tails; version 4 and 5 entries carry a dead float, int list and flag.
void ProductionUpdate::xfer( Xfer *xfer )
{
	// extend base class
	UpdateModule::xfer( xfer );
	if( xfer->IsLightCRC() )
		return;

	// version
	Xfer::Version version( 1, 7 );
	*xfer == version;

	// production queue count
	Rva0049D1B1 *production;
	unsigned short productionCount = 0;
	for( production = m_productionQueue; production; production = production->m_next )
		productionCount++;
	*xfer == productionCount;

	// production queue data
	if( xfer->IsStoring() )
	{
		AsciiString name;

		// write all queue data
		for( production = m_productionQueue; production; production = production->m_next )
		{

			// type
			xfer->XferRawBytes( &production->m_type, sizeof( ProductionType ) );

			// thing/upgrade template name
			switch( production->m_type )
			{
				case PRODUCTION_UNIT:
				case PRODUCTION_HORDE_UNIT:
					name = production->m_objectToProduce->getName();
					break;
				case PRODUCTION_UPGRADE:
					name = production->m_upgradeToResearch->getUpgradeName();
					break;
				default:
					XferException error;
					bfmeFormatText( &error, 5, 0 );
					_CxxThrowException( &error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo ); __assume(0);
			}
			*xfer == name;

			xfer->XferRawBytes( &production->m_productionID, sizeof( ProductionID ) );
			*xfer == production->m_percentComplete;
			*xfer == production->m_bfme18;
			*xfer == production->m_bfme1C;
			*xfer == production->m_productionQuantityTotal;
			*xfer == production->m_productionQuantityProduced;
			*xfer == production->m_cost;
			*xfer == production->m_bfme34;
			xfer->XferRawBytes( &production->m_exitDoor, sizeof( ExitDoorType ) );
			Int slot = production->m_bfme30;
			*xfer == slot;
			if( version.m_minimum >= 4 )
			{
				Real unusedReal = 0.0f;
				*xfer == unusedReal;
				_STL::list<Int> unusedList;
				Rva00460216XferList( xfer, &unusedList );
			}
			if( version.m_minimum >= 5 )
			{
				Bool unusedBool = FALSE;
				*xfer == unusedBool;
			}

		}  // end for

	}  // end if, save
	else
	{
		AsciiString name;

		// the queue should be emtpy now
		if( m_productionQueue != NULL )
		{
			XferException error;
			bfmeFormatText( &error, 5, 0 );
			_CxxThrowException( &error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo ); __assume(0);
		}

		// read each element
		for( unsigned short i = 0; i < productionCount; ++i )
		{

			// allocate new production entry
			production = new Rva0049D1B1;

			// tie to list at end
			if( m_productionQueue == NULL )
				m_productionQueue = production;

			// make any existing tail pointer now point to us, and we point back to them
			if( m_productionQueueTail )
			{
				m_productionQueueTail->m_next = production;
				production->m_prev = m_productionQueueTail;
			}

			// this production entry is now the new tail at the end of the list
			m_productionQueueTail = production;

			// type
			xfer->XferRawBytes( &production->m_type, sizeof( ProductionType ) );

			// thing/upgrade template name
			*xfer == name;
			switch( production->m_type )
			{
				case PRODUCTION_UNIT:
				case PRODUCTION_HORDE_UNIT:
					production->m_objectToProduce = TheThingFactory->findTemplate(name);
					production->m_objectToProduce = production->m_objectToProduce ?
						(const ThingTemplate *)production->m_objectToProduce->getFinalOverride() : NULL;
					break;
				case PRODUCTION_UPGRADE:
					production->m_upgradeToResearch = TheUpgradeCenter->findUpgrade( name );
					break;
			}

			xfer->XferRawBytes( &production->m_productionID, sizeof( ProductionID ) );
			*xfer == production->m_percentComplete;
			*xfer == production->m_bfme18;
			*xfer == production->m_bfme1C;
			*xfer == production->m_productionQuantityTotal;
			*xfer == production->m_productionQuantityProduced;
			*xfer == production->m_cost;
			*xfer == production->m_bfme34;
			xfer->XferRawBytes( &production->m_exitDoor, sizeof( ExitDoorType ) );
			Int slot;
			*xfer == slot;
			production->m_bfme30 = slot;
			if( version.m_minimum >= 4 )
			{
				Real unusedReal = 0.0f;
				*xfer == unusedReal;
				_STL::list<Int> unusedList;
				Rva00460216XferList( xfer, &unusedList );
			}
			if( version.m_minimum >= 5 )
			{
				Bool unusedBool = FALSE;
				*xfer == unusedBool;
			}

		}  // end for, i

	}  // end else, load

	// unique id
	xfer->XferRawBytes( &m_uniqueID, sizeof( ProductionID ) );

	// production count
	*xfer == m_productionCount;

	// construction complete frame
	*xfer == m_constructionCompleteFrame;

	UnsignedInt unused = 0;
	*xfer == unused;
	XferObjectID( xfer, &m_bfme120 );
	*xfer == m_bfme118;
	*xfer == m_bfme11C;

	// door info
	for( Int i = 0; i < DOOR_COUNT_MAX; ++i )
	{
		*xfer == m_doors[ i ].m_doorOpenedFrame;
		*xfer == m_doors[ i ].m_doorWaitOpenFrame;
		*xfer == m_doors[ i ].m_doorClosedFrame;
		*xfer == m_doors[ i ].m_holdOpen;
	}

	// clear flags
	m_clearFlags.xfer( xfer );

	// set flags
	m_setFlags.xfer( xfer );

	// flags dirty
	*xfer == m_flagsDirty;

	if( version.m_minimum >= 2 )
		*xfer == m_bfme128;
	if( version.m_minimum >= 3 && TheAudio )
		TheAudio->xferAudioHandle( xfer, &m_bfme12C );
	if( version.m_minimum >= 6 )
		xferAsciiStringVector( xfer, &m_bfme130 );
	if( version.m_minimum >= 7 )
		*xfer == m_bfme13C;

}  // end xfer


void ProductionUpdate::rva0049CF25()
{
 for (const Rva0049D1B1 *entry=m_productionQueue;entry;entry=(m_productionQueue ? nextProduction(entry) : nextProduction(entry))) {
  if (entry->m_type!=PRODUCTION_HORDE_UNIT) continue;
  Object *obj=getObject();
  if (!obj) continue;
  Player *player=obj->getControllingPlayer();
  if (!player) continue;
  if (player->revivalGate()->rva002A7557(reinterpret_cast<Rva002A7557In *>(const_cast<ThingTemplate *>(entry->getProductionObject())),1)) continue;
  Rva0037EE4C *tracker=&player->m_revivalTracker;
  if (!tracker) continue;
  int index=tracker->rva0037EE4C(entry->getProductionObject(),entry->getProductionID(),0);
  ProductionRevivalCount *item=reinterpret_cast<ProductionRevivalCount *>(reinterpret_cast<Rva0037E421 *>(tracker)->rva0037E421(index));
  if (item) ++item->m_98;
 }
}
