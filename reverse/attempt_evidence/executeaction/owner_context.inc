// Compile context for the single dispatcher bank. Contains the original owner
// members so visibility and inlining match the measured owner-unit trial.
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// 0x003CA418 (166B, WB 0x0101A240) sorts a living-world player's armies by
// their +0x20 id and sets an army reference to the n-th one that has a name.
// 0x003C6279 (123B, WB 0x0101A170) sets an int reference to the +0x14 id
// of the living-world player whose +0x40 name matches, or -1.
// Also two unnamed WorldBuilder members on the same region and army
// references: 0x003C3943 (117B, WB 0x0101A3A0) stores the name of the region
// an army is in, and 0x003C39B8 (135B, WB 0x0101A6F0) moves an army to a
// region (0x002B2702 with 1).
//
// ScriptActions::doLivingWorldSetRegionRefToAdjacentRegion, retail 0x003C6871
// (258B), from WorldBuilder's ScriptActions.cpp (debug build, name, statement
// order, the "ListAllAdjacentRegions" assertion at line 11840).
//
// Target facts: two script-engine region-reference lookups (0x00208DB8, by
// value), the region manager at g_009FEF10+0xB0 resolving the source region
// (0x002104B6), listing its adjacent region ids into a local vector<int>
// (0x0020FD42) and resolving each id (0x0020EAF6); +0x13C is compared between
// regions and 0x003F036E is the second filter.
//
// The search loop never advances its iterator, in WorldBuilder as in retail:
// once a candidate is found it spins, so cl drops the final reference
// assignment (it is reachable only with an empty list, where nothing is
// found). Retail is the result of compiling that loop as written.
//
// ScriptActions::doCreateUnitRevivalEntry, retail 0x003C62F4 (323B; ret 0xC),
// from WorldBuilder's ScriptActions.cpp twin (wb 0x0101B750; name, parameter
// and statement order; its unknown-type, no-player and no-tracker branches
// only log). Target facts: the template by name (pinned findTemplate
// 0x002D06CA), the player through the rowed mask lookups, the tracker at
// player+0x738 (WB +0x740), and a 0xD8-byte revival record (pinned ctor
// 0x0037E289, dtor 0x001EB63C) whose +0x08/+0x0C/+0x10 get the level's
// required experience and rank twice, or the template's own rank (pinned
// 0x0033B479) when no level is given or the store (TheExperienceLevelSystem) has none.
//
// ScriptActions::doCreateUnitRevivalEntryFromDelayedCarryoverHero, retail
// 0x003CA14C (347B; ret 8), from WorldBuilder's twin (wb 0x0101B0E0; name,
// statement order, ArmySummary::SpawnOneDelayedCarryoverUnitIntoUnitRevivalTracker):
// the action side of ScriptConditions_delayedCarryover.cpp's condition, with
// its views. A running linear campaign hands the types, tracker and player to
// the campaign manager (pinned 0x001EC9AC, result only logged in WB);
// otherwise the first army of the selected players that spawns one delayed
// carryover unit of the types ends the search.
//
// ScriptActions::doCreateDelayedCarryoverUnitAtWaypoint, retail 0x003C9F4B
// (513B; ret 0x10), from WorldBuilder's twin (wb 0x0101A8C0; name, statement
// order, ArmySummary::SpawnOneDelayedCarryoverUnit): the same type list and
// player selection, but the campaign manager (pinned 0x001EC99B) or the first
// army that spawns one (pinned 0x0040E589) yields an ObjectID; the object is
// placed at the waypoint (TerrainLogic slot 0x88, location +0x0C) and, when a
// unit name is given, named and cached as in createUnitOnTeamAt.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"
#include <vector>
#include <algorithm>
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

class Rva0020E89C;
struct Rva002B488EResult;
class Rva0040D701ArmySummary;

class Rva002104B6
{
public:
	void *rva002104B6(void *name);
};

class Rva0020FD42
{
public:
	void rva0020FD42(void *region, void *ids);
};

class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);
};

class LivingWorldRegionFilterView
{
public:
	bool rva003F036E();
};

struct LivingWorldRegionView
{
	unsigned char m_pad00[0x14];
	AsciiString m_name;
	unsigned char m_pad18[0x13C - 0x18];
	int m_13C;
};

class Rva002BA8F1Logic
{
public:
	Rva002B488EResult *rva002B488E(int armyID);
	class Rva002E2903Player *find(int id, unsigned int *outIndex);
	class Rva002E2903Player *rva002B52A8(int index);
	void rva002B323C(_STL::vector<Rva0040D701ArmySummary *> *armies, int armyID);
	int getPlayerCount() const { return m_players.size(); }
	void *getRegionManager() const { return m_regionManager; }

private:
	unsigned char m_pad00[0x8C];
	_STL::vector<class Rva002E2903Player *> m_players;
	unsigned char m_pad98[0xB0 - 0x98];
	void *m_regionManager;
};

class ThingTemplate
{
public:
	int rva0033B479() const;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

class Player;
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

// ExperienceLevelSystem.cpp's handle: list and iterator, passed by value.
class ExperienceLevelList;
class ExperienceLevelIterator
{
public:
	ExperienceLevelIterator() {}
	ExperienceLevelIterator(const ExperienceLevelIterator &that) : m_node(that.m_node) {}

private:
	void *m_node;
};

struct ExperienceLevelHandle
{
	ExperienceLevelHandle() {}
	ExperienceLevelHandle(const ExperienceLevelHandle &that) : m_list(that.m_list), m_iter(that.m_iter) {}
	bool isValid() const { return m_list != 0; }

	ExperienceLevelList *m_list;
	ExperienceLevelIterator m_iter;
};

class ExperienceLevelStore
{
public:
	int GetLevelRank(ExperienceLevelHandle levelHandle) const;
	int GetRequiredExperience(ExperienceLevelHandle levelHandle) const;
	ExperienceLevelHandle rva00288E21(const ThingTemplate *thingTemplate, int level) const;
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

// The 0xD8-byte revival record (WB UnitRevivalEntry) built from a template.
struct Rva002E2D10Record
{
	Rva002E2D10Record(const ThingTemplate *thingTemplate);
	~Rva002E2D10Record();

	unsigned char m_pad00[0x08];
	float m_requiredExperience;	// +0x08
	int m_rank;			// +0x0C
	int m_levelRank;		// +0x10
	unsigned char m_pad14[0xD8 - 0x14];
};

class UnitRevivalTracker
{
public:
	void addRevivableUnit(const Rva002E2D10Record &entry, Player *player);
};

class Player
{
public:
	UnitRevivalTracker *getUnitRevivalTracker() { return &m_unitRevivalTracker; }
	int getArmyID() const { return m_armyID; }

private:
	unsigned char m_pad00[0x3AC];
	int m_armyID;
	unsigned char m_pad3B0[0x738 - 0x3B0];
	UnitRevivalTracker m_unitRevivalTracker;
};

class ObjectTypes
{
public:
	ObjectTypes();
	virtual ~ObjectTypes();
	int getListSize() const { return m_objectTypes.size(); }
	void addObjectType(const AsciiString &objectType);

private:
	AsciiString m_listName;
	_STL::vector<AsciiString> m_objectTypes;
};

class LinearCampaignManager
{
public:
	bool hasCampaign() const { return m_campaign != 0; }
	bool rva001EC9AC(ObjectTypes *types, UnitRevivalTracker *tracker, Player *player);
	ObjectID rva001EC99B(ObjectTypes *types, Player *player);

private:
	unsigned char m_pad00[0x10];
	void *m_campaign;
};
extern LinearCampaignManager *TheLinearCampaignManager;

// WorldBuilder's ArmySummary (address-derived spelling as in
// ScriptConditions_delayedCarryover.cpp).
class Rva0040D701ArmySummary
{
public:
	bool SpawnOneDelayedCarryoverUnitIntoUnitRevivalTracker(ObjectTypes *types);
	ObjectID SpawnOneDelayedCarryoverUnit(ObjectTypes *types);
};

struct Coord3D;

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

class Object : public Thing
{
public:
	void setName(const AsciiString &name) { m_name = name; }

private:
	unsigned char m_pad00[0x88];
	AsciiString m_name;
};

extern GameLogic *TheGameLogic;

class Waypoint
{
public:
	const Coord3D *getLocation() const { return (const Coord3D *)m_location; }

private:
	unsigned char m_pad[0x0C];
	unsigned char m_location[0x0C];
};

class TerrainLogic
{
public:
#define TERRAIN_SLOT(n) virtual void slot##n();
	TERRAIN_SLOT(0) TERRAIN_SLOT(1) TERRAIN_SLOT(2) TERRAIN_SLOT(3) TERRAIN_SLOT(4)
	TERRAIN_SLOT(5) TERRAIN_SLOT(6) TERRAIN_SLOT(7) TERRAIN_SLOT(8) TERRAIN_SLOT(9)
	TERRAIN_SLOT(10) TERRAIN_SLOT(11) TERRAIN_SLOT(12) TERRAIN_SLOT(13) TERRAIN_SLOT(14)
	TERRAIN_SLOT(15) TERRAIN_SLOT(16) TERRAIN_SLOT(17) TERRAIN_SLOT(18) TERRAIN_SLOT(19)
	TERRAIN_SLOT(20) TERRAIN_SLOT(21) TERRAIN_SLOT(22) TERRAIN_SLOT(23) TERRAIN_SLOT(24)
	TERRAIN_SLOT(25) TERRAIN_SLOT(26) TERRAIN_SLOT(27) TERRAIN_SLOT(28) TERRAIN_SLOT(29)
	TERRAIN_SLOT(30) TERRAIN_SLOT(31) TERRAIN_SLOT(32) TERRAIN_SLOT(33)
#undef TERRAIN_SLOT
	virtual Waypoint *getWaypointByName(const AsciiString &name); // slot 0x88
};
extern TerrainLogic *TheTerrainLogic;

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &, bool);
	void doObjectTypeListMaintenance(const AsciiString &, const AsciiString &, bool);
	void rva0035818E(const AsciiString &, struct Coord3D *);
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
	ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);
	bool didUnitExist(const AsciiString &name);
	void rva00357960(const AsciiString &name, Object *obj); // ZH transferObjectName
	void addObjectToCache(Object *obj, const AsciiString &name);
	AsciiString *rva00208DB8(AsciiString name);
	int *rva00208E99(AsciiString name);
	int *rva00208CF0(AsciiString name);
};

struct Rva002B488EResult;
class Rva00318C32Ret;

class Rva00318C79Owner
{
public:
	Rva00318C32Ret *rva00318C32();
};

class Rva002B2702
{
public:
	void rva002B2702(void *army, void *region, int arg);
};

class Rva00329EE9StringValue
{
public:
	bool isEmpty() const;
};
extern ScriptEngine *TheScriptEngine;


// W7-G1 candidate: donor Scripts.h parameter accessors, retail offsets.
// The bank transcribes all switch labels; ABI/type reconciliation remains.
struct Coord3D { float x, y, z; };
struct RGBColor { float red, green, blue; };
enum EmotionType { EMOTION_INVALID = -1 };
enum ObjectStatusTypes { OBJECT_STATUS_INVALID = -1 };
class Parameter
{
public:
    int getInt() const { return m_int; }
    float getReal() const { return m_real; }
    const AsciiString &getString() const { return m_string; }
    void getCoord3D(Coord3D *) const;
private:
    int m_type;
    bool m_initialized;
    int m_int;
    float m_real;
    AsciiString m_string;
    Coord3D m_coord;
};
class ScriptAction
{
public:
    __forceinline Parameter *getParameterInline(int index) {
        if (index >= 0 && index < m_numParms)
            return m_parms[index];
        return 0;
    }
    int getActionType() const { return m_type; }
    bool isEnabled() const { return m_enabled; }
    __declspec(noinline) Parameter *getParameter(int index) {
        if (index >= 0 && index < m_numParms)
            return m_parms[index];
        return 0;
    }
private:
    void *m_vtable;
    int m_type;
    int m_numParms;
    Parameter *m_parms[12];
    unsigned char m_pad3c[5];
    bool m_enabled;
};

class Team;
extern int BfmeLogicFramesPerSecond; // canonical signed32 timing owner at target VA 0x00DBA4E4; reconciled in round2
double __cdecl Rva000422BBCeil(float);
class ScriptActionViewSlots { public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31(float, float, float);
    virtual void slot32(int);
    virtual void slot33(int);
    virtual void slot34(float, float, float);
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45(int);
    virtual void slot46();
    virtual void slot47(int);
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56(int);
};
class ScriptActionAudioSlots { public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16(int, int, int);
    virtual void slot17(int, int, int);
};
class ScriptActionWindowSlots { public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16(bool);
};
class ScriptActionGameEngineSlots { public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18(int);
};
class View; extern View *TheTacticalView;
class AudioManager; extern AudioManager *TheAudio;
class GlobalData; extern GlobalData *TheWritableGlobalData;
class Radar; extern Radar *TheRadar;
class GameEngine; extern GameEngine *TheGameEngine;
class GameClient; extern GameClient *TheGameClient;
struct ScriptActionGlobalData {
    unsigned char m_pad00[0x26]; bool m_flag26;
    unsigned char m_pad27; int m_value28;
    unsigned char m_pad2C[0x950-0x2C]; float m_value950;
    unsigned char m_pad954[0xD40-0x954]; float m_valueD40;
};
struct ScriptActionRadarFlags { unsigned char m_pad00[0x11]; bool m_flag11; };
class Rva00239A40 { public: void rva00239A40(AsciiString); };
void __cdecl HideControlBar(bool);
void __cdecl ShowControlBar(bool);
void __cdecl Rva004E400DEnable();

class Rva003BD598 { public: void rva003BD598(); };
class Rva003BE5C9 { public: void rva003BE5C9(); void rva003C3B4A(); };
class Rva003BE6CB { public: void rva003BE6CB(); };
class Rva003BE7ED { public: void rva003BE7ED(); };
class Rva003BBAD3 { public: void rva003BBAD3(); };
class Rva003C08CC { public: void rva003C08CC(class AsciiString const *, bool); };
class Rva003BC392Holder { public: void set(bool); };
class Rva003C1E69 { public: class Team * rva003C1E69(class AsciiString const &, class AsciiString const &); };
class Rva003C1FDE { public: void rva003C1FDE(class AsciiString const &, bool); };
class ScriptActions
{
protected:
	void doLivingWorldSetRegionRefToAdjacentRegion(const AsciiString &destRefName,
		const AsciiString &srcRefName, bool skipMatching13C, bool skipFiltered);
	void rva003CA418(const AsciiString &armyRefName, int n, const AsciiString &playerRefName);
	void rva003C6279(const AsciiString &refName, const AsciiString &playerName);
	void rva003C3943(const AsciiString &regionRefName, const AsciiString &armyRefName);
	void rva003C39B8(const AsciiString &armyRefName, const AsciiString &regionRefName);
	void doCreateUnitRevivalEntry(const AsciiString &objectTypeName, const AsciiString &playerName, int level);
	void doCreateUnitRevivalEntryFromDelayedCarryoverHero(const AsciiString &objectTypeName, const AsciiString &playerName);
	void doCreateDelayedCarryoverUnitAtWaypoint(const AsciiString &objectTypeName, const AsciiString &playerName,
		const AsciiString &waypointName, const AsciiString &unitName);
public:
	virtual void executeAction(ScriptAction *pAction);
public:
	void Rva003BA96F(float, float, float, float, float);
public:
	void Rva003BA9AF(int);
public:
	void Rva003BA9CA(int);
public:
	void Rva003BA9E5();
public:
	void Rva003BA9FA(float, float, float, float);
public:
	void Rva003BAA2D(float);
public:
	void Rva003BAA46(Parameter *, bool, float);
public:
	void Rva003BAAD6();
public:
	void Rva003BAAE4(AsciiString const &, float, float, float, float);
public:
	void Rva003BAB7A(float, float, float, float);
public:
	void Rva003BABCB(float, float, float, float);
public:
	void Rva003BAC1C(float, float, float, float);
public:
	void Rva003BAC6D(float, float, float, float);
public:
	void Rva003BACCA(Parameter *);
public:
	void Rva003BAD15(AsciiString const &, float, float, AsciiString const &);
public:
	void Rva003BAE04();
public:
	void Rva003BAECA(float, float, float, float);
public:
	void Rva003BAF1D(float, float, float, float);
public:
	void Rva003BAF95(float, float, float, float);
public:
	void Rva003BAFE8(Parameter *, float, float, float, float, float);
public:
	void Rva003BB05FSet(int, float, float, float, bool);
public:
	void Rva003BB0C7Set(int, float, float, float, float, float, int);
public:
	void Rva003BB141Notify(StringBase<char> const &);
public:
	void Rva003BB163Set(AsciiString const &, int);
public:
	void Rva003BB1A4Grant(AsciiString const &, AsciiString const &);
public:
	void Rva003BB1FFAttack(Parameter *, AsciiString const &);
public:
	void Rva003BB233Set(AsciiString const &, int);
public:
	void Rva003BB274Ai(Parameter *, int);
public:
	void Rva003BB29D(AsciiString const &);
public:
	void Rva003BB2DFClear(AsciiString const &);
public:
	void Rva003BB31DClear(AsciiString const &);
public:
	void Rva003BB35B(AsciiString const &, int);
public:
	void Rva003BB39EClear(AsciiString const &);
public:
	void Rva003BB3DCSet(AsciiString const &);
public:
	void Rva003BB41A(AsciiString const &, int);
public:
	void Rva003BB45DSet(AsciiString const &);
public:
	void Rva003BB49BDestroy(Parameter *);
public:
	void Rva003BB4BDApply(Parameter *, float, float, float, int);
public:
	void Rva003BB4F7Kill(Parameter *);
public:
	void Rva003BB518Clear(AsciiString const &);
public:
	void Rva003BB5B7Do(Parameter *, int, RGBColor *);
public:
	void Rva003BB61E(const AsciiString &);
public:
	void Rva003BB62C(int);
public:
	void Rva003BB641();
public:
	void Rva003BB654();
public:
	void Rva003BB6C0Clear(AsciiString const &);
public:
	void Rva003BB700(bool);
public:
	void Rva003BB713Set(AsciiString const &, Object *, AsciiString const &);
public:
	void Rva003BB76EDo(Coord3D *, void *);
public:
	void Rva003BB79DDo(Parameter *, void *);
public:
	void Rva003BB7E2();
public:
	void Rva003BB7F0();
public:
	void Rva003BB7FESet(int, bool);
public:
	void Rva003BB898(bool, bool);
public:
	void Rva003BB8EDReveal(AsciiString const &, float, AsciiString const &);
public:
	void Rva003BB94CReveal(AsciiString const &);
public:
	void Rva003BB9C6Reveal(bool, AsciiString const &);
public:
	void Rva003BBA59Reveal(AsciiString const &);
public:
	void Rva003BBB36Enable();
public:
	void Rva003BBC61Set(bool);
public:
	void Rva003BBC81Set(bool, bool, int);
public:
	void Rva003BBCB3Set(bool);
public:
	void Rva003BBCD2Set(bool, bool);
public:
	void Rva003BBE04(bool);
public:
	void Rva003BBE44Set(bool, int);
public:
	void Rva003BBE91Set(bool, int);
public:
	void Rva003BBEDE();
public:
	void Rva003BBEE9();
public:
	void Rva003BBEF4(int, float);
public:
	void Rva003BBF23Disable(Parameter *, bool);
public:
	void Rva003BBF51Set(Parameter *, float);
public:
	void Rva003BBF8F();
public:
	void Rva003BBFA0();
public:
	void Rva003BBFB1Select(Parameter *);
public:
	void Rva003BBFD6Select(Parameter *);
public:
	void Rva003BBFFBSet(int, float);
public:
	void Rva003BC048Set(AsciiString const &, int);
public:
	void Rva003BC0A7Set(AsciiString const &, int);
public:
	void Rva003BC107();
public:
	void Rva003BC115();
public:
	void Rva003BC1A0Forward();
public:
	void Rva003BC1B2Do(Parameter *, bool, float);
public:
	void Rva003BC22EDo(float, float, float);
public:
	void Rva003BC259Remove(Parameter *);
public:
	void Rva003BC2E4Do(Parameter *, bool);
public:
	void Rva003BC306Do(Parameter *, float);
public:
	void Rva003BC33DDo(Parameter *, float, float, float);
public:
	void Rva003BC421Do(Parameter *, int);
public:
	void Rva003BC47ADo(int);
public:
	void Rva003BC4ABSet(AsciiString const &, int);
public:
	void Rva003BC4D1Do(int);
public:
	void Rva003BC4E8Do(int);
public:
	void Rva003BC4FFForward();
public:
	void Rva003BC510Do(int);
public:
	void Rva003BC524Set(AsciiString const &, float);
public:
	void Rva003BC54FDo(int);
public:
	void Rva003BC566Forward();
public:
	void Rva003BC582Set(AsciiString const &, int);
public:
	void Rva003BC5CESet(AsciiString const &, int);
public:
	void Rva003BC626Set(AsciiString const &, int);
public:
	void Rva003BC67ASet(AsciiString const &, int);
public:
	void Rva003BC6C7Set(int);
public:
	void Rva003BC6D9Set(AsciiString const &, AsciiString const &);
public:
	void Rva003BC72FSet(AsciiString const &, AsciiString const &);
public:
	void Rva003BC785Set(AsciiString const &, AsciiString const &, AsciiString const &);
public:
	void Rva003BC7EFSet(AsciiString const &, int);
public:
	void Rva003BC830Clear(AsciiString const &);
public:
	void Rva003BC86ESet(AsciiString const &, AsciiString const &);
public:
	void Rva003BC8AFSet(AsciiString const &, int);
public:
	void Rva003BC8F0Set(bool);
public:
	void Rva003BC903Do(Parameter *, int);
public:
	void Rva003BC96FDo(Parameter *, int);
public:
	void Rva003BC996Do(Parameter *, StringBase<char> const &, float);
public:
	void Rva003BC9E0Do(AsciiString const &, float, AsciiString const &, AsciiString const &);
public:
	void Rva003BCA12Do(AsciiString const &, AsciiString const &, AsciiString const &);
public:
	void Rva003BCA43Do(AsciiString const &);
public:
	void Rva003BCA5DSet(bool);
public:
	void Rva003BCA68Set(bool);
public:
	void Rva003BCA7BSet(bool);
public:
	void Rva003BCA8ESet(bool);
public:
	void Rva003BCAA1Set(float);
public:
	void Rva003BCADAForward(const AsciiString &, const AsciiString &);
public:
	void Rva003BCAE8Forward();
public:
	void Rva003BCAF6Do(Parameter *, float, float, float);
public:
	void Rva003BCB37Set(AsciiString const &, int);
public:
	void Rva003BCB7A(AsciiString const &, AsciiString const &, int);
public:
	void Rva003BCBC7Set(AsciiString const &, float);
public:
	void Rva003BCC08Do(float, float);
public:
	void Rva003BCC6ESet(bool);
public:
	void Rva003BCC81Set(bool);
public:
	void Rva003BCC94Do();
public:
	void Rva003BCCA2Do();
public:
	void Rva003BCCC6Do(Parameter *, Parameter *);
public:
	void Rva003BCD1BDo(Parameter *);
public:
	void Rva003BCD45Do(Parameter *);
public:
	void Rva003BCDD7Do(Parameter *);
public:
	void Rva003BCFC9Set(bool);
public:
	void Rva003BCFD4Set(bool);
public:
	void Rva003BCFE7Forward(bool);
public:
	void Rva003BCFF5Forward(bool);
public:
	void Rva003BD003Forward(bool);
public:
	void Rva003BD011Forward(bool);
public:
	void Rva003BD01FSet(bool);
public:
	void Rva003BD032Set(Parameter *, void *);
public:
	void Rva003BD062Set(void *, AsciiString const *, bool);
public:
	void Rva003BD0C8Set(AsciiString const &, bool);
public:
	void Rva003BD108SetGamePaused();
public:
	void Rva003BD116Set(Parameter *, void *);
public:
	void Rva003BD153Set(void *, int, int);
public:
	void Rva003BD19CSet(void *, Parameter *);
public:
	void Rva003BD405Set(unsigned char);
public:
	void Rva003BD412Set(unsigned char);
public:
	void Rva003BD884Set(Parameter *, AsciiString const *);
public:
	void Rva003BE9DBSet(AsciiString const &, float);
public:
	void Rva003BEA10Do(AsciiString const *, void *);
public:
	void Rva003BEB01Do(AsciiString const *, void *);
public:
	void Rva003BEBD6Do(AsciiString const *);
public:
	void Rva003BECCDSet(AsciiString const &, AsciiString const &, bool);
public:
	void Rva003BF71EDo(AsciiString const &, AsciiString const &);
public:
	void Rva003BF7ACDo(AsciiString const &, Parameter *);
public:
	void Rva003BF813Do(AsciiString const &, AsciiString const &, AsciiString const &);
public:
	void Rva003BF8B4Hunt(AsciiString const &);
public:
	void Rva003BF903Do(AsciiString const &, int);
public:
	void Rva003BF96FDo(AsciiString const &, AsciiString const &);
public:
	void Rva003BF9C8Do(AsciiString const &);
public:
	void Rva003BF9FADo(AsciiString const &, float, AsciiString const &);
public:
	void Rva003BFA77Do(Parameter const &, int);
public:
	void Rva003BFAC3Set(AsciiString const &, int);
public:
	void Rva003BFAF4Do(AsciiString const &);
public:
	void Rva003BFB8CDo(AsciiString const &, int);
public:
	void Rva003BFC27Do(AsciiString const &);
public:
	void Rva003BFCBFDo(AsciiString const &, int);
public:
	void Rva003BFD5ASet(AsciiString const &);
public:
	void Rva003BFF50Do(AsciiString const *, int, RGBColor *);
public:
	void Rva003BFFECDo(AsciiString const &, bool);
public:
	void Rva003C00CEDo(AsciiString const *, void *);
public:
	void Rva003C0308Do(AsciiString const &, bool, bool, int, AsciiString const &, int);
public:
	void Rva003C0425Do(AsciiString const &, bool, bool, int, AsciiString const &, int);
public:
	void Rva003C075BDo(AsciiString const *, AsciiString const *);
public:
	void Rva003C07C1Do(AsciiString const &, AsciiString const &, AsciiString const &);
public:
	void Rva003C0849Do(AsciiString const &, AsciiString const &, AsciiString const &);
public:
	void Rva003C0C3ESet(AsciiString const &);
public:
	void Rva003C0DE1Do(AsciiString const &, bool);
public:
	void Rva003C0E87Do(AsciiString const &, int);
public:
	void Rva003C1020Do(AsciiString const &, AsciiString const &, Parameter *);
public:
	void Rva003C1E8CSet(AsciiString const &, int);
public:
	void Rva003C1EC2Set(AsciiString const &, int);
public:
	void Rva003C1F0A(AsciiString const &, StringBase<char> const &, float);
public:
	void Rva003C1F6CDo(AsciiString const *, int);
public:
	void Rva003C1FADDestroy();
public:
	void Rva003C2121Grant(AsciiString const &, AsciiString const &);
public:
	void Rva003C21E5Do(AsciiString const *, int, AsciiString const *, AsciiString const *);
public:
	void Rva003C2260Do(AsciiString const &, int);
public:
	void Rva003C239FDo(AsciiString const &, int, Parameter *);
public:
	void Rva003C2A29Do(AsciiString const &, AsciiString const &);
public:
	void Rva003C2A9FDo(AsciiString const &, int);
public:
	void Rva003C2BC0Do(Parameter *, Parameter *);
public:
	void Rva003C2C28Do(Parameter *, Parameter *);
public:
	void Rva003C2C8FDo(Parameter *, Parameter *);
public:
	void Rva003C2CD8Do(Parameter *, Parameter *);
public:
	void Rva003C2D34Do(Parameter *, Parameter *);
public:
	void Rva003C2D90Do(Parameter *, Parameter *);
public:
	void Rva003C2DEADo(Parameter *, Parameter *);
public:
	void Rva003C2E61Do(void const *, void const *, void const *);
public:
	void Rva003C2EC9Do(void const *, void const *, void const *);
public:
	void Rva003C301DDo(Parameter *, Parameter *);
public:
	void Rva003C30D9Do(AsciiString const &, bool);
public:
	void Rva003C3175Do(AsciiString const &, bool);
public:
	void Rva003C31F3Do(AsciiString const &, AsciiString const &, bool);
public:
	void Rva003C353BDo(Parameter *, void *);
public:
	void Rva003C35AADo(AsciiString const *, bool, bool);
public:
	void Rva003C36C0Do(Parameter *, bool);
public:
	void Rva003C36FEDo(Parameter *, bool);
public:
	void Rva003C388EDo(Parameter *, bool);
public:
	void Rva003C3A3FSet(AsciiString const &, int);
public:
	void Rva003C3E75Apply(Parameter *, AsciiString const &, void *);
public:
	void Rva003C3EC5Apply(Parameter *, AsciiString const &, int);
public:
	void Rva003C3F9EApply(Parameter *, AsciiString const &, int);
public:
	void Rva003C4003Apply(Parameter *, AsciiString const &, void *);
public:
	void Rva003C4245Do(Parameter *, AsciiString const &, AsciiString const &);
public:
	void Rva003C4350Do(AsciiString const &, AsciiString const &, Object *);
public:
	void Rva003C43A3Do(AsciiString const &, AsciiString const &);
public:
	void Rva003C43F3Do(AsciiString const &, AsciiString const &, Object *);
public:
	void Rva003C4449Do(AsciiString const &, AsciiString const &);
public:
	void Rva003C4570Do(AsciiString const &, AsciiString const &);
public:
	void Rva003C45D4Apply(Parameter *, AsciiString const &);
public:
	void Rva003C4D5CDo(AsciiString const *);
public:
	void Rva003C4DC2Do(AsciiString const &);
public:
	void Rva003C4E28Find(AsciiString const &, float, float, float);
public:
	void Rva003C5405Do(AsciiString, AsciiString const &);
public:
	void Rva003C549DDo(AsciiString, AsciiString const &);
public:
	void Rva003C5535Do(AsciiString);
public:
	void Rva003C57A9Do(Parameter *, AsciiString const &);
public:
	void Rva003C5825Do(Parameter *, AsciiString const &, AsciiString const &);
public:
	void Rva003C58C9Do(Parameter *, AsciiString const &, int);
public:
	void Rva003C5A00Do(AsciiString const &, AsciiString const &, float, float);
public:
	void Rva003C6A0EDo(Parameter *, Parameter *, Parameter *);
public:
	void Rva003C6B7BDo(Parameter *, Parameter *, Parameter *);
public:
	void Rva003C6D4FDo(Parameter *, Parameter *, Parameter *);
public:
	void Rva003C7A30Do(Parameter *, int);
public:
	void Rva003C7AF3Do(Parameter *, int);
public:
	void Rva003C82EADo(Parameter *, Parameter *);
public:
	void Rva003C89D1Guard(Parameter *, Parameter *);
public:
	void Rva003C8A15Do(Parameter *, AsciiString const &, AsciiString const &);
public:
	void Rva003C8A95Do(Parameter *);
public:
	void Rva003C8ABFDo(AsciiString const &, AsciiString const &);
public:
	void Rva003C8B62Do(AsciiString const &);
public:
	void Rva003C8BCBDo(AsciiString const &, AsciiString const &);
public:
	void Rva003C8C6EDo(AsciiString const &);
public:
	void Rva003C8E2BExit(AsciiString const &);
public:
	void Rva003C90B1Exit(Parameter *);
public:
	void Rva003C91D1Idle(Parameter *);
public:
	void Rva003C9C0AAttack(Parameter *, int);
public:
	void Rva0042F9DAEmit();
public:
	void bfmeGoFGE(void *, void *, bool);
public:
	void bfmeLinkObjectsA70(void *, void *);
protected:
	void createUnitOnTeamAt(AsciiString const &, AsciiString const &, AsciiString const &, AsciiString const &);
protected:
	void doAffectObjectPanelFlagsTeam(AsciiString const &, AsciiString const &, bool);
protected:
	void doAffectObjectPanelFlagsUnit(Parameter *, AsciiString const &, bool);
public:
	void doAttackMoveTeamTowardsNearest(AsciiString const &, AsciiString const &, AsciiString const &);
protected:
	void doBorderSwitch(int);
protected:
	void doBuildBaseBuilding(AsciiString const &, Parameter *, AsciiString const &);
protected:
	void doBuildBaseBuildingInSlot(AsciiString const &, Parameter *, Parameter *, AsciiString const &);
protected:
	void doBuildBuildingOnFoundation(AsciiString const &, AsciiString const &);
protected:
	void doCameoFlash(AsciiString const &, int);
protected:
	void doCounterMathCounter(Parameter *, Parameter *, Parameter *);
protected:
	void doCounterMathValue(Parameter *, Parameter *, Parameter *);
protected:
	void doCreateObject(AsciiString const &, AsciiString const &, AsciiString const &, Coord3D *, float);
protected:
	void doDisplayCinematicText(AsciiString const &, AsciiString const &, int);
protected:
	void doDisplayNotificationBox(AsciiString const &, AsciiString const &, int, AsciiString const &);
protected:
	void doDisplayText(AsciiString const &);
protected:
	void doEnablePlanningMode(unsigned char);
public:
	void doFireSpecialPowerAtWaypoint(AsciiString const &, AsciiString const &, AsciiString const &);
protected:
	void doFlashObjectivesButton(int);
protected:
	void doFlashPlanningModeButton(int);
protected:
	void doFlashSpellStoreButton(int);
protected:
	void doForceObjectSelection(AsciiString const &, AsciiString const &, bool, AsciiString const &);
protected:
	void doHeroSelectButtonFlash(int, int);
protected:
	void doIdleAllPlayerUnits(AsciiString const &);
protected:
	void doKillHordeMembers(Parameter *, float);
protected:
	void doMergeTeamIntoTeam(AsciiString const &, AsciiString const &);
protected:
	void doMoveTeamTowardsNearest(AsciiString const &, AsciiString const &, AsciiString);
protected:
	void doMoveUnitTowardsNearest(AsciiString const &, AsciiString const &, AsciiString);
protected:
	void doNamedAttackArea(AsciiString const &, AsciiString const &);
protected:
	void doNamedAttackAreaForSeconds(AsciiString const &, AsciiString const &, int);
protected:
	void doNamedAttackFollowWaypoints(Parameter *, AsciiString const &);
protected:
	void doNamedAttackTeam(AsciiString const &, AsciiString const &);
protected:
	void doNamedBuildStructureAtWaypoint(Parameter *, AsciiString const &, float, AsciiString const &);
protected:
	void doNamedCustomColor(Parameter *, int);
protected:
	void doNamedEnableCameraFading(Parameter *, bool);
protected:
	void doNamedEnableStealth(AsciiString const &, bool);
protected:
	void doNamedEnterNamed(AsciiString const &, AsciiString const &);
protected:
	void doNamedExitAll(AsciiString const &);
protected:
	void doNamedFaceNamed(AsciiString const &, AsciiString const &);
protected:
	void doNamedFaceWaypoint(AsciiString const &, AsciiString const &);
protected:
	void doNamedFireWeaponFollowingWaypointPath(AsciiString const &, AsciiString const &);
protected:
	void doNamedFollowWaypoints(AsciiString const &, AsciiString const &);
protected:
	void doNamedFollowWaypointsExact(AsciiString const &, AsciiString const &);
protected:
	void doNamedGuard(AsciiString const &);
protected:
	void doNamedSetRepulsor(AsciiString const &, bool);
protected:
	void doNamedSetTeam(Parameter *, AsciiString const &);
protected:
	void doPlaySoundEffect(AsciiString const &);
protected:
	void doPlaySoundEffectAt(AsciiString const &, AsciiString const &);
protected:
	void doPlaySoundEffectAtTeam(AsciiString const &, AsciiString const &);
protected:
	void doPlayerForceEmotion(Parameter *, int, float);
protected:
	void doPlayerSetSpecialPowerCountdown(AsciiString const &, AsciiString const &, int);
protected:
	void doRemoveCommandBarButton(AsciiString const &, AsciiString const &);
protected:
	void doResetMusicScripting(bool);
protected:
	void doResumeSupplyTruckingForIdleUnits(AsciiString const &);
protected:
	void doSelectBuilderButtonFlash(int);
protected:
	void doSellBuildingOnFoundation(Parameter *);
protected:
	void doSetCounterToPlayerOwnershipOfUnitsWithModelCondition(AsciiString const &, AsciiString const &, AsciiString const &);
protected:
	void doSetCounterToThreatFinderThreat(AsciiString const &, AsciiString const &, AsciiString const &, AsciiString const &);
protected:
	void doSetTeamState(AsciiString const &, AsciiString const &);
protected:
	void doSetUnitReference(AsciiString const &, Parameter *, bool);
protected:
	void doSetUnitReferenceToHomeBaseOfPlayer(AsciiString const &, AsciiString const &, bool);
protected:
	void doSkirmishAttackNearestGroupWithValue(AsciiString const &, int, int);
protected:
	void doSoundPlayFromNamed(AsciiString const &, AsciiString const &);
protected:
	void doSpeechPlay(AsciiString const &, bool);
protected:
	void doTeamAttackArea(AsciiString const &, AsciiString const &);
protected:
	void doTeamAttackMoveFollowWaypoints(AsciiString const &, AsciiString const &, bool, bool);
protected:
	void doTeamAttackNamed(AsciiString const &, AsciiString const &);
protected:
	void doTeamAttackTeam(AsciiString const &, AsciiString const &);
protected:
	void doTeamAvailableForRecruitment(AsciiString const &, bool);
protected:
	void doTeamCaptureNearestUnownedFactionUnit(AsciiString const &);
protected:
	void doTeamEnableStealth(AsciiString const &, bool);
protected:
	void doTeamEnterNamed(AsciiString const &, AsciiString const &);
protected:
	void doTeamExitAll(AsciiString const &);
protected:
	void doTeamFaceNamed(AsciiString const &, AsciiString const &);
protected:
	void doTeamFaceWaypoint(AsciiString const &, AsciiString const &);
protected:
	void doTeamFollowSkirmishApproachPath(AsciiString const &, AsciiString const &, bool);
protected:
	void doTeamFollowWaypoints(AsciiString const &, AsciiString const &, bool, bool);
protected:
	void doTeamFollowWaypointsExact(AsciiString const &, int, bool);
protected:
	void doTeamForceEmotion(Parameter *, int, float);
protected:
	void doTeamGarrisonNearestBuilding(AsciiString const &);
protected:
	void doTeamGarrisonSpecificBuilding(AsciiString const &, AsciiString const &, bool);
protected:
	void doTeamGuard(AsciiString const &);
protected:
	void doTeamHuntWithCommandButton(AsciiString const &, AsciiString const &);
protected:
	void doTeamIdleForFramecount(AsciiString const &, int, bool);
protected:
	void doTeamMoveToSkirmishApproachPath(AsciiString const &, AsciiString const &);
protected:
	void doTeamPartialUseCommandButton(float, AsciiString const &, AsciiString const &);
protected:
	void doTeamSetRepulsor(AsciiString const &, bool);
protected:
	void doTeamSpinForFramecount(AsciiString const &, int);
protected:
	void doTeamStandGround(Parameter *, Parameter *);
protected:
	void doTeamStartSequentialScript(AsciiString const &, AsciiString const &, int);
protected:
	void doTeamUseCommandButtonOnNearestBuilding(AsciiString const &, AsciiString const &);
protected:
	void doTeamUseCommandButtonOnNearestBuildingClass(AsciiString const &, AsciiString const &, int);
protected:
	void doTeamUseCommandButtonOnNearestEnemy(AsciiString const &, AsciiString const &);
protected:
	void doTeamUseCommandButtonOnNearestGarrisonedBuilding(AsciiString const &, AsciiString const &);
protected:
	void doTeamUseCommandButtonOnNearestKindof(AsciiString const &, AsciiString const &, int);
protected:
	void doUnitAssimilateWithFirstWalkOnArmy(Parameter *);
protected:
	void doUnitForceEmotion(Parameter *, int, float);
protected:
	void doUnitGarrisonNearestBuilding(AsciiString const &);
protected:
	void doUnitGarrisonSpecificBuilding(AsciiString const &, AsciiString const &, bool);
protected:
	void doUnitGuardForFramecount(AsciiString const &, int, bool);
protected:
	void doUnitGuardPosition(AsciiString const &, AsciiString const &);
protected:
	void doUnitIdleForFramecount(AsciiString const &, int, bool);
protected:
	void doUnitReceiveUpgrade(Parameter *, AsciiString const &);
protected:
	void doUnitStandGround(Parameter *, Parameter *);
protected:
	void doUnitStartSequentialScript(Parameter *, AsciiString const &, int);
protected:
	void doUnpackBase(Parameter *, AsciiString const *, int);
protected:
	void rva003BA943(Parameter *, bool);
public:
	void rva003BBB51(bool);
protected:
	void rva003BBD61(AsciiString const &, bool);
public:
	void rva003BBD84(AsciiString const &);
public:
	void rva003BBDC4(AsciiString const &);
protected:
	void rva003BC93C(Parameter *, int);
public:
	void rva003BD2A6(bool);
protected:
	void rva003BD306(Parameter *, bool);
public:
	void rva003BD32B(int);
public:
	void rva003BD34D(int);
public:
	void rva003BD36F(int);
public:
	void rva003BD391(int);
public:
	void rva003BD3CB(void *, float, int);
public:
	void rva003BD905(AsciiString const &, AsciiString const &);
public:
	void rva003BDB03(AsciiString const &, AsciiString const &);
public:
	void rva003BDC65(AsciiString const &, AsciiString const &, int);
public:
	void rva003BDE5D(AsciiString const &, AsciiString const &);
public:
	void rva003BDFA5(AsciiString const &, AsciiString const &, int);
protected:
	void rva003BEDD1(AsciiString const &, AsciiString const &);
protected:
	void rva003C004D(AsciiString const &, float);
protected:
	void rva003C0091(AsciiString const &);
protected:
	void rva003C013C(AsciiString const &, AsciiString const &);
protected:
	void rva003C05DE(AsciiString const &, bool);
protected:
	void rva003C062D(AsciiString const &, float);
protected:
	void rva003C0983(AsciiString const &, AsciiString const &, Object *);
protected:
	void rva003C09DA(AsciiString const &, AsciiString const &);
protected:
	void rva003C0A2E(AsciiString const &);
protected:
	void rva003C0D6A(AsciiString const &, int, bool);
protected:
	void rva003C0D90(AsciiString const &, int, bool);
protected:
	void rva003C0E32(AsciiString const &, int);
protected:
	void rva003C0F09(AsciiString const &, int);
protected:
	void rva003C207C(Parameter *, Parameter *, bool);
protected:
	void rva003C20CA(AsciiString const &, Parameter *, bool);
protected:
	void rva003C2166(AsciiString const &, int, AsciiString const &);
public:
	void rva003C2662(AsciiString const &, AsciiString const &);
public:
	void rva003C276A(AsciiString const &, AsciiString const &, Parameter *);
public:
	void rva003C32CC(const AsciiString &, const AsciiString &, bool);
public:
	void rva003C33C9(Parameter *, Parameter *, Parameter *, Parameter *, bool);
protected:
	void rva003C3609(Parameter *);
protected:
	void rva003C38EF(Parameter *, ObjectStatusTypes, bool);
public:
	void rva003C4070(AsciiString const &, AsciiString const &);
public:
	void rva003C4145(AsciiString const &, AsciiString const &, AsciiString const &);
public:
	void rva003C42B9(Parameter *, AsciiString const &, AsciiString const &);
public:
	void rva003C449C(const AsciiString &, const AsciiString &, const AsciiString &);
public:
	void rva003C4625(AsciiString const &, Parameter *, AsciiString const &);
public:
protected:
	void rva003C4751(Parameter *);
public:
protected:
	void rva003C49AE(Parameter *, Parameter *);
public:
	void rva003C55A6(void *, AsciiString const &, AsciiString const &, AsciiString const &, AsciiString const &);
public:
	void rva003C56D6(void *, AsciiString const &, AsciiString const &, AsciiString const &);
protected:
	void rva003C596A(AsciiString const &, AsciiString const &, float, float);
protected:
	void rva003C5F1B(ScriptAction *, Parameter *, Parameter *, Parameter *, bool);
protected:
	void rva003C606C(Parameter *, bool);
protected:
	void rva003C66F1(AsciiString const &, Parameter *, AsciiString const &, Parameter *, AsciiString const &);
protected:
	void rva003C6EFC(AsciiString const &, AsciiString const &, bool);
public:
	void rva003C7018(AsciiString const &, AsciiString const &, float, bool);
public:
	void rva003C739D(Parameter *, Parameter *, Parameter *, Parameter *, Parameter *);
public:
	void rva003C7914(AsciiString const &, Parameter *);
public:
	void rva003C7BBB(const AsciiString &, const AsciiString &, bool);
public:
	void rva003C8482(const AsciiString &);
public:
	void rva003C90DD(const AsciiString &, const AsciiString &);
public:
	void rva003C951B(AsciiString const &, AsciiString const &, AsciiString const &);
protected:
	void rva003C9BAD(AsciiString const &);
public:
	void rva003C9D0D(AsciiString const &, float);
protected:
	void rva003C9E4E(AsciiString const &, AsciiString const &);
protected:
	void rva003CA322(AsciiString const &, int, AsciiString const &, AsciiString const &);
protected:
	void updateTeamSetAttitude(AsciiString const &, int);
};

void ScriptActions::doLivingWorldSetRegionRefToAdjacentRegion(const AsciiString &destRefName,
	const AsciiString &srcRefName, bool skipMatching13C, bool skipFiltered)
{
	AsciiString *destRef = TheScriptEngine->rva00208DB8(destRefName);
	AsciiString *srcRef = TheScriptEngine->rva00208DB8(srcRefName);
	LivingWorldRegionView *srcRegion = (LivingWorldRegionView *)
		((Rva002104B6 *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->getRegionManager())->rva002104B6(srcRef);
	destRef->clear();
	if (!srcRegion)
		return;

	_STL::vector<int> ids;
	((Rva0020FD42 *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->getRegionManager())->rva0020FD42(srcRegion, &ids);
	LivingWorldRegionView *found = 0;
	_STL::vector<int>::iterator it = ids.begin();
	_STL::vector<int>::iterator end = ids.end();
	while (it != end) {
		if (!found) {
			LivingWorldRegionView *region = (LivingWorldRegionView *)
				((Rva0020EAF6View *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->getRegionManager())->rva0020EAF6(*it);
			if (region) {
				bool ok = true;
				if (skipMatching13C && region->m_13C == srcRegion->m_13C)
					ok = false;
				if (ok && skipFiltered && ((LivingWorldRegionFilterView *)region)->rva003F036E())
					ok = false;
				if (ok)
					found = region;
			}
		}
	}
	if (found)
		*destRef = found->m_name;
}

void ScriptActions::rva003C3943(const AsciiString &regionRefName, const AsciiString &armyRefName)
{
	AsciiString *regionRef = TheScriptEngine->rva00208DB8(regionRefName);
	int *armyRef = TheScriptEngine->rva00208E99(armyRefName);
	Rva002B488EResult *army = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B488E(*armyRef);
	if (!army) {
		regionRef->clear();
		return;
	}
	LivingWorldRegionView *region = (LivingWorldRegionView *)((Rva00318C79Owner *)army)->rva00318C32();
	const AsciiString &name = region ? region->m_name : AsciiString::TheEmptyString;
	*regionRef = name;
}

void ScriptActions::rva003C39B8(const AsciiString &armyRefName, const AsciiString &regionRefName)
{
	AsciiString *regionRef = TheScriptEngine->rva00208DB8(regionRefName);
	int armyID = *TheScriptEngine->rva00208E99(armyRefName);
	if (armyID == 0 || ((Rva00329EE9StringValue *)regionRef)->isEmpty())
		return;
	Rva002B488EResult *army = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B488E(armyID);
	if (!army)
		return;
	void *region = ((Rva002104B6 *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->getRegionManager())->rva002104B6(regionRef);
	if (region)
		((Rva002B2702 *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->rva002B2702(army, region, 1);
}

struct Rva003C3AB0Item
{
	unsigned char m_pad00[0x18];
	AsciiString m_name;
	unsigned char m_pad1C[0x20 - 0x1C];
	int m_20;
};

struct Rva003C3AB0Cmp
{
	bool operator()(const Rva003C3AB0Item *a, const Rva003C3AB0Item *b) const { return a->m_20 < b->m_20; }
};

class Rva002E2903Player
{
public:
	unsigned char m_pad00[0x14];
	int m_id;
	unsigned char m_pad18[0x40 - 0x18];
	const AsciiString *m_name;
	unsigned char m_pad44[0x1B8 - 0x44];
	_STL::vector<Rva003C3AB0Item *> m_armies;
};

void ScriptActions::rva003C6279(const AsciiString &refName, const AsciiString &playerName)
{
	int *ref = TheScriptEngine->rva00208CF0(refName);
	int count = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->getPlayerCount();
	for (int i = 0; i < count; ++i) {
		Rva002E2903Player *player = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B52A8(i);
		if (player && player->m_name->compare(playerName) == 0) {
			*ref = player->m_id;
			return;
		}
	}
	*ref = -1;
}

void ScriptActions::rva003CA418(const AsciiString &armyRefName, int n, const AsciiString &playerRefName)
{
	int *armyRef = TheScriptEngine->rva00208E99(armyRefName);
	*armyRef = 0;
	int *playerRef = TheScriptEngine->rva00208CF0(playerRefName);
	Rva002E2903Player *player = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(*playerRef, 0);
	if (!player)
		return;
	_STL::vector<Rva003C3AB0Item *> &armies = player->m_armies;
	_STL::sort(armies.begin(), armies.end(), Rva003C3AB0Cmp());
	_STL::vector<Rva003C3AB0Item *>::iterator it = armies.begin();
	_STL::vector<Rva003C3AB0Item *>::iterator end = armies.end();
	for (; it != end; ++it) {
		if (!((Rva00329EE9StringValue *)&(*it)->m_name)->isEmpty())
			--n;
		if (n <= 0)
			break;
	}
	if (it != end)
		*armyRef = (*it)->m_20;
}

void ScriptActions::doCreateUnitRevivalEntry(const AsciiString &objectTypeName, const AsciiString &playerName, int level)
{
	const ThingTemplate *objectType = TheThingFactory->findTemplate(objectTypeName);
	if (!objectType)
		return;
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	Player *player = ThePlayerList->getEachPlayerFromMask(mask);
	if (!player)
		return;
	UnitRevivalTracker *tracker = player->getUnitRevivalTracker();
	if (!tracker)
		return;
	Rva002E2D10Record entry(objectType);
	if (level == -1) {
		entry.m_rank = objectType->rva0033B479();
	} else {
		ExperienceLevelHandle levelHandle = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->rva00288E21(objectType, level);
		if (levelHandle.isValid()) {
			entry.m_requiredExperience = (float)reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetRequiredExperience(levelHandle);
			entry.m_rank = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetLevelRank(levelHandle);
			entry.m_levelRank = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetLevelRank(levelHandle);
		} else {
			entry.m_rank = objectType->rva0033B479();
		}
	}
	tracker->addRevivableUnit(entry, player);
}

void ScriptActions::doCreateUnitRevivalEntryFromDelayedCarryoverHero(const AsciiString &objectTypeName,
	const AsciiString &playerName)
{
	ObjectTypes tempTypes;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(objectTypeName);
	if (!types || types->getListSize() == 0) {
		tempTypes.addObjectType(objectTypeName);
		types = &tempTypes;
	}
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	if (TheLinearCampaignManager && TheLinearCampaignManager->hasCampaign()) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player) {
			UnitRevivalTracker *tracker = player->getUnitRevivalTracker();
			if (tracker)
				TheLinearCampaignManager->rva001EC9AC(types, tracker, player);
		}
	} else if (TheLivingWorldLogic) {
		while (mask) {
			Player *player = ThePlayerList->getEachPlayerFromMask(mask);
			if (!player)
				continue;
			int armyID = player->getArmyID();
			if (armyID == -1)
				continue;
			_STL::vector<Rva0040D701ArmySummary *> armies;
			(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B323C(&armies, armyID);
			_STL::vector<Rva0040D701ArmySummary *>::iterator it = armies.begin();
			_STL::vector<Rva0040D701ArmySummary *>::iterator end = armies.end();
			for (; it != end; ++it) {
				if ((*it)->SpawnOneDelayedCarryoverUnitIntoUnitRevivalTracker(types))
					return;
			}
		}
	}
}

void ScriptActions::doCreateDelayedCarryoverUnitAtWaypoint(const AsciiString &objectTypeName,
	const AsciiString &playerName, const AsciiString &waypointName, const AsciiString &unitName)
{
	ObjectTypes tempTypes;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(objectTypeName);
	if (!types || types->getListSize() == 0) {
		tempTypes.addObjectType(objectTypeName);
		types = &tempTypes;
	}
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	if (!way)
		return;
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	ObjectID result = INVALID_OBJECT_ID;
	if (TheLinearCampaignManager && TheLinearCampaignManager->hasCampaign()) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (!player)
			return;
		result = TheLinearCampaignManager->rva001EC99B(types, player);
	} else {
		if (!TheLivingWorldLogic)
			return;
		while (result == INVALID_OBJECT_ID && mask) {
			Player *player = ThePlayerList->getEachPlayerFromMask(mask);
			if (!player)
				continue;
			int armyID = player->getArmyID();
			if (armyID == -1)
				continue;
			_STL::vector<Rva0040D701ArmySummary *> armies;
			(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B323C(&armies, armyID);
			_STL::vector<Rva0040D701ArmySummary *>::iterator it = armies.begin();
			_STL::vector<Rva0040D701ArmySummary *>::iterator end = armies.end();
			for (; result == INVALID_OBJECT_ID && it != end; ++it)
				result = (*it)->SpawnOneDelayedCarryoverUnit(types);
		}
	}
	if (result == INVALID_OBJECT_ID)
		return;
	Object *obj = TheGameLogic->findObjectByID(result);
	if (!obj)
		return;
	obj->setPosition(way->getLocation());
	if (unitName != AsciiString::TheEmptyString) {
		obj->setName(unitName);
		if (TheScriptEngine->didUnitExist(unitName))
			TheScriptEngine->rva00357960(unitName, obj);
		else
			TheScriptEngine->addObjectToCache(obj, "");
	}
}

// BFME2 executeAction at RVA 0x003CA4BE, WB 0x0101C3C0.
// ZH ScriptActions.cpp guides parameter/call semantics; numeric case labels
// and argument ordering below come from retail, not donor enum values.
