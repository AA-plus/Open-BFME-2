// ?translateGameMessage@CommandTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z
// partial score=0.821261372492925 date=2026-10-13
// cl: /I. -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/shims/stringbaseunicode /O1 /G7 /arch:SSE /ICode/Libraries/Include -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/MessageStream
// stlport
// Ported from GeneralsMD/Code/GameEngine/Source/GameClient/MessageStream/CommandXlat.cpp.
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later, as in the vendored source.
// BFME layout/call witnesses: build/gap_005ade0d/LAYOUTS.md and region_{a,b}.asm.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include "ascii_string.h"
#include "Common/UnicodeString.h"
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t>*)this)->releaseBuffer(); }
#include "Lib/Coord3D.h"
#include "Code/Libraries/Include/Lib/ICoord2D.h"
#include "Code/Libraries/Include/Lib/IRegion2D.h"
class Drawable; class Object; class Player; class ThingTemplate; class CommandButton;
class PickAndPlayInfo;
class Rva004D92FE { public:
 Rva004D92FE();
 bool field00; char pad01[3]; Drawable* m_drawTarget; void* m_weaponSlot;
 void* field0c; int m_specialPowerType; Coord3D m_position; void* field1c;
};
typedef _STL::list<Drawable*> SelectedDrawableList;
union GameMessageArgumentType { int integer; unsigned drawableID; ICoord2D pixel; IRegion2D pixelRegion; Coord3D location; };
enum ObjectID { OBJECTID_NONE=0 };
class GameMessage { public:
 enum Type { MSG_INVALID=0, MSG_CREATE_SELECTED_GROUP=0x3e9 };
 char pad00[0x10]; Type m_type;
 Type getType() const { return m_type; }
 const GameMessageArgumentType* getArgument(int) const;
 void appendIntegerArgument(int);
 void appendBooleanArgument(bool); void appendObjectIDArgument(ObjectID);
 void appendLocationArgument(const struct Coord3D&);
};
enum GameMessageDisposition { KEEP_MESSAGE, DESTROY_MESSAGE };
enum CommandEvaluateType { DO_COMMAND, DO_HINT, DO_EVALUATE };
class AudioEventRTS { public: AudioEventRTS(const AsciiString&,int); ~AudioEventRTS(); void* m_vftable; char opaque04[0x6c]; };
class CommandButton { public: char pad00[0x10]; int m_command; bool isContextCommand() const; int getCommandType() const { return m_command; } };
enum KindOfType { KINDOF_PLACEHOLDER };
template<int N> class BitFlags { public: int words[7]; };
class Thing { public: Drawable* getDrawable() const; bool isAnyKindOf(const BitFlags<69>&) const; bool isKindOf(KindOfType) const; };

class SpawnBehaviorInterface {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual Object* getClosestSlave(const Coord3D*); // vtable +0x8

};

enum CanAttackResult { ATTACKRESULT_NONE,ATTACKRESULT_INVALID_SHOT,ATTACKRESULT_VALID2,ATTACKRESULT_VALID3 };
enum AbleToAttackType { ATTACK_TYPE_ZERO,ATTACK_TYPE_ONE };
enum CommandSourceType { SOURCE_ZERO };
struct ForceAttackTemplate { char pad[0x108]; unsigned char kind108; char pad109[9]; unsigned char kind112; };
class Object {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual Drawable* getDrawable() const; // vtable +0x28

 ForceAttackTemplate* m_template; char pad08[0x30]; Coord3D m_position; char pad44[0x30]; ObjectID m_id;
 char pad78[0x1fc]; Object* m_containedBy;
 ObjectID getID() const { return m_id; }
 const Coord3D* getPosition() const { return &m_position; }
 bool isKindOf(int k) const { return ((const Thing*)this)->isKindOf((KindOfType)k); }
 const AsciiString* rva00290E67() const;
 bool isLocallyControlled() const;
 bool isAbleToAttack() const;
 CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType,const Object*,CommandSourceType) const;
 CanAttackResult getAbleToUseWeaponAgainstTarget(AbleToAttackType,const Object*,const Coord3D*,CommandSourceType) const;
 SpawnBehaviorInterface* getSpawnBehaviorInterface() const;

};

class Drawable { public: char pad00[0xfc]; Object* m_object; Object* getObject() const { return m_object; } const Coord3D* getPosition() const; };
class PlayerTemplate { public: char pad00[0xe4]; AsciiString m_beaconTemplate; const AsciiString& getBeaconTemplate() const { return m_beaconTemplate; } };
class Team; enum Relationship { CONTEXT_ALLY,CONTEXT_ENEMY,CONTEXT_NEUTRAL };
class Player { public: char pad00[4]; PlayerTemplate* m_playerTemplate;
 const PlayerTemplate* getPlayerTemplate() const { return m_playerTemplate; }
 Relationship getRelationship(const Team*) const; Object* findNaturalCommandCenter(); Object* rva002AC629();
 bool isPlayerActive() const;
 Object* rva000D4660(bool,Object**) const;
 int rva002ABCF0(unsigned char,int*);
 int iterateObjects(int (*)(Object*,void*),void*) const;
 void countObjectsByThingTemplate(int,const ThingTemplate* const*,bool,int*,bool) const;
};
class PlayerList { public: char pad00[0xc]; Player* m_localPlayer; Player* getLocalPlayer() const { return m_localPlayer; } };
class ControlBar { public: void rva0031AD94(); const CommandButton* findCommandButton(const AsciiString&); void togglePurchaseScience(); };
class GameLogic { public: char pad00[0x91]; bool m_showBehindBuildingMarkers; char pad92[0x7a]; int m_mode;
 bool rva0042219();char rva0023C6FD();
 bool isInMultiplayerGame(); bool rva000652A0() const; bool isInReplayGame() const { return m_mode==3; }
};
// TU-local field view of retail's GlobalData; the one writable global at
// 0x012ED5C8 is declared with EA's own class below and cast at each use.
class RvaGlobalDataView { public:
 char pad00[0x38]; bool m_useCloudMap; char pad39[0xb]; bool m_useLightMap; char pad45[0x1b]; bool m_useAlternateMouse;
 char pad61[3]; bool m_useShadowVolumes; char pad65[0xaa7]; int m_netMinPlayers; char padb10[0x7c]; int m_maxParticleCount;
 char padb90[0xc9]; bool m_TiVOFastMode;
};
struct Rva001EDD80Pair;
class Mouse { public: bool rva001EDD80(const Rva001EDD80Pair*,const Rva001EDD80Pair*); int getCursorIndex(const AsciiString&); char pad00[0x10ec]; unsigned m_dragTolerance; char pad10f0[4]; unsigned m_clickTime;
 bool rva005A49E0(const ICoord2D*,const ICoord2D*) const;
};
class Radar { public: bool rva00107140(Coord3D*); };
class Rva004891C0 { public: char pad00[0x4d]; bool field4d; bool test() const; };
class Rva003968A0 { public: bool test(); };
enum RecorderModeType { RECORDER_NONE };
class RecorderClass { public: RecorderModeType getMode(); };
enum NameKeyType { NAMEKEY_NONE };
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString&); };
class GameWindow { public: bool winIsHidden(); };
class ThingFactory { public: const ThingTemplate* findTemplate(const AsciiString&); };
class MultiplayerSettings { public: char pad00[0x14]; int m_maxBeaconsPerPlayer; int getMaxBeaconsPerPlayer() { return m_maxBeaconsPerPlayer; } };

struct Rva0029AEF9Item;
enum SpecialPowerType { CONTEXT_POWER_NONE };
class InGameUI {
public:
 bool areSelectedObjectsControllable() const;
 bool rva0029AEF9(Rva0029AEF9Item*,int,int,int,int,int) const;
 enum ActionType { CONTEXT_ACTION_ZERO }; enum SelectionRules { CONTEXT_ANY,CONTEXT_ALL };
 bool canSelectedObjectsDoSpecialPower(const CommandButton*,const Object*,const Coord3D*,SelectionRules,unsigned,Object*) const;
 bool canSelectedObjectsDoAction(ActionType,const Object*,SelectionRules,bool) const;
 CanAttackResult getCanSelectedObjectsAttack(ActionType,const Object*,SelectionRules,bool) const;
 bool canSelectedObjectsEffectivelyUseWeapon(const CommandButton*,const Object*,const Coord3D*,SelectionRules) const;
 bool canSelectedObjectsOverrideSpecialPowerDestination(const Coord3D*,SelectionRules,SpecialPowerType) const;
 bool rva0029CC19(const Object*);
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual void slot0B(); // vtable +0x2C
    virtual void __cdecl message(UnicodeString,...); // MSVC overloaded slot +0x34
    virtual void __cdecl message(AsciiString,...); // MSVC overloaded slot +0x30
    virtual void slot0E(); // vtable +0x38
    virtual void slot0F(); // vtable +0x3C
    virtual void slot10(); // vtable +0x40
    virtual void slot11(); // vtable +0x44
    virtual void slot12(); // vtable +0x48
    virtual void slot13(); // vtable +0x4C
    virtual void slot14(); // vtable +0x50
    virtual void slot15(); // vtable +0x54
    virtual void slot16(); // vtable +0x58
    virtual void slot17(); // vtable +0x5C
    virtual void slot18(); // vtable +0x60
    virtual void slot19(); // vtable +0x64
    virtual void slot1A(); // vtable +0x68
    virtual void slot1B(); // vtable +0x6C
    virtual void slot1C(); // vtable +0x70
    virtual void slot1D(); // vtable +0x74
    virtual void slot1E(); // vtable +0x78
    virtual void slot1F(); // vtable +0x7C
    virtual void slot20(); // vtable +0x80
    virtual void slot21(); // vtable +0x84
    virtual void slot22(); // vtable +0x88
    virtual void slot23(); // vtable +0x8C
    virtual void slot24(); // vtable +0x90
    virtual void slot25(); // vtable +0x94
    virtual void slot26(); // vtable +0x98
    virtual void slot27(); // vtable +0x9C
    virtual void slot28(); // vtable +0xA0
    virtual void slot29(); // vtable +0xA4
    virtual void slot2A(); // vtable +0xA8
    virtual void slot2B(); // vtable +0xAC
    virtual void slot2C(); // vtable +0xB0
    virtual void slot2D(); // vtable +0xB4
    virtual void setGUICommand(const CommandButton*); // vtable +0xB8
    virtual const CommandButton* getGUICommand(); // vtable +0xBC
    virtual void slot30(); // vtable +0xC0
    virtual void slot31(); // vtable +0xC4
    virtual void slot32(); // vtable +0xC8
    virtual void slot33(); // vtable +0xCC
    virtual void slot34(); // vtable +0xD0
    virtual void slot35(); // vtable +0xD4
    virtual void slot36(); // vtable +0xD8
    virtual void slot37(); // vtable +0xDC
    virtual void selectDrawable(Drawable*); // vtable +0xE0
    virtual void slot39(); // vtable +0xE4
    virtual void deselectAllDrawables(); // vtable +0xE8
    virtual void selectAllUnitsByType(int,Player*); // vtable +0xEC
    virtual int getSelectCount(); // vtable +0xF0
    virtual void slot3D(); // vtable +0xF4
    virtual void slot3E(); // vtable +0xF8
    virtual void slot3F(); // vtable +0xFC
    virtual void slot40(); // vtable +0x100
    virtual Drawable* getFirstSelectedDrawable(); // vtable +0x104
    virtual void slot42(); // vtable +0x108
    virtual void slot43(); // vtable +0x10C
    virtual void slot44(); // vtable +0x110
    virtual void slot45(); // vtable +0x114
    virtual void slot46(); // vtable +0x118
    virtual void slot47(); // vtable +0x11C
    virtual void slot48(); // vtable +0x120
    virtual const SelectedDrawableList* getAllSelectedDrawables() const; // vtable +0x124
    virtual void slot4A(); // vtable +0x128
    virtual void slot4B(); // vtable +0x12C
    virtual void slot4C(); // vtable +0x130
    virtual void slot4D(); // vtable +0x134
    virtual void slot4E(); // vtable +0x138
    virtual void slot4F(); // vtable +0x13C
    virtual void slot50(); // vtable +0x140
    virtual void slot51(); // vtable +0x144
    virtual void slot52(); // vtable +0x148
    virtual void slot53(); // vtable +0x14C
    virtual void slot54(); // vtable +0x150
    virtual void slot55(); // vtable +0x154
    virtual void slot56(); // vtable +0x158
    virtual void selectUnitsMatchingCurrentSelection(); // vtable +0x15C

 char pad04[0x12ac]; bool m_waypointMode; bool m_forceAttackMode; bool m_forceMoveMode; bool m_preferSelectionMode;
 bool m_cameraRotateLeft; bool m_cameraRotateRight; bool m_cameraZoomIn; bool m_cameraZoomOut;
 bool field12b8; bool field12b9; bool field12ba; bool field12bb;
 bool isInForceAttackMode() const { return m_forceAttackMode; }
 bool getInputEnabled() const;
 bool rva0043EC00() const;
 void rva0043CEC0();

};

class MessageStream {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual void slot0B(); // vtable +0x2C
    virtual void slot0C(); // vtable +0x30
    virtual void slot0D(); virtual void slot0E(); virtual void slot0F(); virtual void slot10(); virtual void slot11();
    virtual GameMessage* appendMessage(GameMessage::Type); // vtable +0x48

};

class GameClient {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual Drawable* findDrawableByID(unsigned); // vtable +0x2C
    virtual Drawable* firstDrawable(); // vtable +0x30

};

class View {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual Drawable* pickDrawable(const ICoord2D*,bool,int); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual void slot0B(); // vtable +0x2C
    virtual void slot0C(); // vtable +0x30
    virtual void slot0D(); // vtable +0x34
    virtual void slot0E(); // vtable +0x38
    virtual void slot0F(); // vtable +0x3C
    virtual void slot10(); // vtable +0x40
    virtual void slot11(); // vtable +0x44
    virtual void slot12(); // vtable +0x48
    virtual void slot13(); // vtable +0x4C
    virtual void slot14(); // vtable +0x50
    virtual void lookAt(const Coord3D*); // vtable +0x54
    virtual void slot16(); // vtable +0x58
    virtual void slot17(); // vtable +0x5C
    virtual void slot18(); // vtable +0x60
    virtual void slot19(); // vtable +0x64
    virtual void slot1A(); // vtable +0x68
    virtual void slot1B(); // vtable +0x6C
    virtual void slot1C(); // vtable +0x70
    virtual void slot1D(); // vtable +0x74
    virtual void slot1E(); // vtable +0x78
    virtual void slot1F(); // vtable +0x7C
    virtual void slot20(); // vtable +0x80
    virtual void slot21(); // vtable +0x84
    virtual void slot22(); // vtable +0x88
    virtual void slot23(); // vtable +0x8C
    virtual void slot24(); // vtable +0x90
    virtual void slot25(); // vtable +0x94
    virtual void slot26(); // vtable +0x98
    virtual void slot27(); // vtable +0x9C
    virtual void slot28(); // vtable +0xA0
    virtual void slot29(); // vtable +0xA4
    virtual void slot2A(); // vtable +0xA8
    virtual void slot2B(); // vtable +0xAC
    virtual void slot2C(); // vtable +0xB0
    virtual void slot2D(); // vtable +0xB4
    virtual void slot2E(); // vtable +0xB8
    virtual void slot2F(); // vtable +0xBC
    virtual void slot30(); // vtable +0xC0
    virtual void slot31(); // vtable +0xC4
    virtual void slot32(); // vtable +0xC8
    virtual void slot33(); // vtable +0xCC
    virtual void slot34(); // vtable +0xD0
    virtual void slot35(); // vtable +0xD4
    virtual void slot36(); // vtable +0xD8
    virtual void slot37(); // vtable +0xDC
    virtual void slot38(); // vtable +0xE0
    virtual void slot39(); // vtable +0xE4
    virtual void slot3A(); // vtable +0xE8
    virtual void slot3B(); // vtable +0xEC
    virtual void slot3C(); // vtable +0xF0
    virtual void slot3D(); // vtable +0xF4
    virtual void slot3E(); // vtable +0xF8
    virtual void slot3F(); // vtable +0xFC
    virtual void slot40(); // vtable +0x100
    virtual void slot41(); // vtable +0x104
    virtual void slot42(); // vtable +0x108
    virtual void slot43(); // vtable +0x10C
    virtual void slot44(); // vtable +0x110
    virtual void slot45(); // vtable +0x114
    virtual void slot46(); // vtable +0x118
    virtual void slot47(); // vtable +0x11C
    virtual void slot48(); // vtable +0x120
    virtual const SelectedDrawableList* getAllSelectedDrawables() const; // vtable +0x124
    virtual void slot4A(); // vtable +0x128
    virtual void slot4B(); // vtable +0x12C
    virtual void slot4C(); // vtable +0x130
    virtual void slot4D(); // vtable +0x134
    virtual void slot4E(); // vtable +0x138
    virtual void slot4F(); // vtable +0x13C
    virtual void slot50(); // vtable +0x140
    virtual void slot51(); // vtable +0x144
    virtual void slot52(); // vtable +0x148
    virtual void slot53(); // vtable +0x14C
    virtual void slot54(); // vtable +0x150
    virtual void slot55(); // vtable +0x154
    virtual void slot56(); // vtable +0x158
    virtual void slot57(); // vtable +0x15C
    virtual void slot58(); // vtable +0x160
    virtual void screenToTerrain(const ICoord2D*,Coord3D*,bool); // vtable +0x164

};

class WindowLayout {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void hide(bool); // vtable +0x10
 char pad04[0x10]; bool m_hidden;
};

class Shell { public: char pad00[0x58]; bool m_active; WindowLayout* top(); };
class GameWindowManager {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual void slot0B(); // vtable +0x2C
    virtual void slot0C(); // vtable +0x30
    virtual void slot0D(); // vtable +0x34
    virtual void slot0E(); // vtable +0x38
    virtual void slot0F(); // vtable +0x3C
    virtual void slot10(); // vtable +0x40
    virtual void slot11(); // vtable +0x44
    virtual void slot12(); // vtable +0x48
    virtual void slot13(); // vtable +0x4C
    virtual void slot14(); // vtable +0x50
    virtual void slot15(); // vtable +0x54
    virtual void slot16(); // vtable +0x58
    virtual void slot17(); // vtable +0x5C
    virtual void slot18(); // vtable +0x60
    virtual void slot19(); // vtable +0x64
    virtual void slot1A(); // vtable +0x68
    virtual void slot1B(); // vtable +0x6C
    virtual void slot1C(); // vtable +0x70
    virtual void slot1D(); // vtable +0x74
    virtual void slot1E(); // vtable +0x78
    virtual void slot1F(); // vtable +0x7C
    virtual void slot20(); // vtable +0x80
    virtual void slot21(); // vtable +0x84
    virtual void slot22(); // vtable +0x88
    virtual void slot23(); // vtable +0x8C
    virtual void slot24(); // vtable +0x90
    virtual void slot25(); // vtable +0x94
    virtual void slot26(); // vtable +0x98
    virtual void slot27(); // vtable +0x9C
    virtual void slot28(); // vtable +0xA0
    virtual void slot29(); // vtable +0xA4
    virtual void slot2A(); // vtable +0xA8
    virtual void slot2B(); // vtable +0xAC
    virtual void slot2C(); // vtable +0xB0
    virtual void slot2D(); // vtable +0xB4
    virtual void slot2E(); // vtable +0xB8
    virtual void slot2F(); // vtable +0xBC
    virtual void slot30(); // vtable +0xC0
    virtual void slot31(); // vtable +0xC4
    virtual void slot32(); // vtable +0xC8
    virtual void slot33(); // vtable +0xCC
    virtual void slot34(); // vtable +0xD0
    virtual void slot35(); // vtable +0xD4
    virtual void slot36(); // vtable +0xD8
    virtual GameWindow* winGetWindowFromId(GameWindow*,int); // vtable +0xDC

};

class GameInfo {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual bool isMultiPlayer() const; // vtable +0x2C

};

class AudioManager {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual void slot0B(); // vtable +0x2C
    virtual void slot0C(); // vtable +0x30
    virtual void slot0D(); // vtable +0x34
    virtual void slot0E(); // vtable +0x38
    virtual void slot0F(); // vtable +0x3C
    virtual void slot10(); // vtable +0x40
    virtual unsigned addAudioEvent(const AudioEventRTS*); // vtable +0x44
    virtual void slot12(); // vtable +0x48
    virtual void slot13(); // vtable +0x4C
    virtual void slot14(); // vtable +0x50
    virtual void slot15(); // vtable +0x54
    virtual void slot16(); // vtable +0x58
    virtual void slot17(); // vtable +0x5C
    virtual void slot18(); // vtable +0x60
    virtual void slot19(); // vtable +0x64
    virtual void slot1A(); // vtable +0x68
    virtual void slot1B(); // vtable +0x6C
    virtual void slot1C(); // vtable +0x70
    virtual void slot1D(); // vtable +0x74
    virtual void slot1E(); // vtable +0x78
    virtual void slot1F(); // vtable +0x7C
    virtual void slot20(); // vtable +0x80
    virtual void slot21(); // vtable +0x84
    virtual void slot22(); // vtable +0x88
    virtual void slot23(); // vtable +0x8C
    virtual void slot24(); // vtable +0x90
    virtual void slot25(); // vtable +0x94
    virtual void slot26(); // vtable +0x98
    virtual void slot27(); // vtable +0x9C
    virtual void slot28(); // vtable +0xA0
    virtual void slot29(); // vtable +0xA4
    virtual void slot2A(); // vtable +0xA8
    virtual void slot2B(); // vtable +0xAC
    virtual void slot2C(); // vtable +0xB0
    virtual void slot2D(); // vtable +0xB4
    virtual void slot2E(); // vtable +0xB8
    virtual void slot2F(); // vtable +0xBC
    virtual void slot30(); // vtable +0xC0
    virtual void slot31(); // vtable +0xC4
    virtual void slot32(); // vtable +0xC8
    virtual void slot33(); // vtable +0xCC
    virtual void slot34(); // vtable +0xD0
    virtual void slot35(); // vtable +0xD4
    virtual void slot36(); // vtable +0xD8
    virtual void slot37(); // vtable +0xDC
    virtual void slot38(); // vtable +0xE0
    virtual void slot39(); // vtable +0xE4
    virtual void slot3A(); // vtable +0xE8
    virtual void slot3B(); // vtable +0xEC
    virtual void slot3C(); // vtable +0xF0
    virtual void slot3D(); // vtable +0xF4
    virtual void slot3E(); // vtable +0xF8
    virtual void slot3F(); // vtable +0xFC
    virtual void slot40(); // vtable +0x100
    virtual void slot41(); // vtable +0x104
    virtual void slot42(); // vtable +0x108
    virtual void slot43(); // vtable +0x10C
    virtual void slot44(); // vtable +0x110
    virtual void slot45(); // vtable +0x114
    virtual void slot46(); // vtable +0x118
    virtual void slot47(); // vtable +0x11C
    virtual void slot48(); // vtable +0x120
    virtual const char* getMiscAudio() const; // vtable +0x124

};

class Display {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual void slot0B(); // vtable +0x2C
    virtual void slot0C(); // vtable +0x30
    virtual void slot0D(); // vtable +0x34
    virtual void slot0E(); // vtable +0x38
    virtual void slot0F(); // vtable +0x3C
    virtual void slot10(); // vtable +0x40
    virtual void slot11(); // vtable +0x44
    virtual void slot12(); // vtable +0x48
    virtual void slot13(); // vtable +0x4C
    virtual void slot14(); // vtable +0x50
    virtual void slot15(); // vtable +0x54
    virtual void slot16(); // vtable +0x58
    virtual void slot17(); // vtable +0x5C
    virtual void slot18(); // vtable +0x60
    virtual void slot19(); // vtable +0x64
    virtual void slot1A(); // vtable +0x68
    virtual void slot1B(); // vtable +0x6C
    virtual void slot1C(); // vtable +0x70
    virtual void slot1D(); // vtable +0x74
    virtual void slot1E(); // vtable +0x78
    virtual void slot1F(); // vtable +0x7C
    virtual void slot20(); // vtable +0x80
    virtual void slot21(); // vtable +0x84
    virtual void slot22(); // vtable +0x88
    virtual void slot23(); // vtable +0x8C
    virtual void slot24(); // vtable +0x90
    virtual void slot25(); // vtable +0x94
    virtual void slot26(); // vtable +0x98
    virtual void slot27(); // vtable +0x9C
    virtual void slot28(); // vtable +0xA0
    virtual void slot29(); // vtable +0xA4
    virtual void slot2A(); // vtable +0xA8
    virtual void slot2B(); // vtable +0xAC
    virtual void slot2C(); // vtable +0xB0
    virtual void slot2D(); // vtable +0xB4
    virtual void slot2E(); // vtable +0xB8
    virtual void slot2F(); // vtable +0xBC
    virtual void slot30(); // vtable +0xC0
    virtual void slot31(); // vtable +0xC4
    virtual void slot32(); // vtable +0xC8
    virtual void slot33(); // vtable +0xCC
    virtual void slot34(); // vtable +0xD0
    virtual void slot35(); // vtable +0xD4
    virtual void slot36(); // vtable +0xD8
    virtual void slot37(); // vtable +0xDC
    virtual void slot38(); // vtable +0xE0
    virtual void slot39(); // vtable +0xE4
    virtual void slot3A(); // vtable +0xE8
    virtual void slot3B(); // vtable +0xEC
    virtual void slot3C(); // vtable +0xF0
    virtual void slot3D(); // vtable +0xF4
    virtual void slot3E(); // vtable +0xF8
    virtual void slot3F(); // vtable +0xFC
    virtual void slot40(); // vtable +0x100
    virtual void slot41(); // vtable +0x104
    virtual void slot42(); // vtable +0x108
    virtual void slot43(); // vtable +0x10C
    virtual void slot44(); // vtable +0x110
    virtual void slot45(); // vtable +0x114
    virtual void slot46(); // vtable +0x118
    virtual void slot47(); // vtable +0x11C
    virtual void slot48(); // vtable +0x120
    virtual void takeScreenShot(); // vtable +0x124

};

extern InGameUI* TheInGameUI;
extern GameClient* TheGameClient;
extern MessageStream* TheMessageStream; // ledger alias of MessageStreamSubsystem at 0x00A00950
extern PlayerList* ThePlayerList;
extern View* TheTacticalView;
extern GameLogic* TheGameLogic;
class GlobalData;
extern GlobalData* TheWritableGlobalData;
static inline RvaGlobalDataView* localGlobalData() { return (RvaGlobalDataView*)TheWritableGlobalData; }
extern Mouse* TheMouse;
extern Radar* TheRadar;
extern ControlBar* TheControlBar;
extern Shell* TheShell;
extern RecorderClass* TheRecorder;
extern GameWindowManager* TheWindowManager;
extern NameKeyGenerator* TheNameKeyGenerator;
extern ThingFactory* TheThingFactory;
extern MultiplayerSettings* TheMultiplayerSettings;
extern GameInfo* TheGameInfo;
extern AudioManager* TheAudio;
extern Display* TheDisplay;
// Retail 0x012F3330 is EA's GameWindowTransitionsHandler *TheTransitionHandler;
// Rva004891C0 is this TU's view of the object, so every use casts.
class GameWindowTransitionsHandler;
extern GameWindowTransitionsHandler* TheTransitionHandler;
// 0x012F1028 is the one Glo012F1028 global.  Rva003968A0 above is this TU's
// view of that object (its test() is a pinned callee), so the use casts.
class Glo012F1028Type;

extern void* g_va012F71B4;
extern void* g_va012F4988;
void rva00511CC0(int);
void HideInGameChat();
void rva0052B2A0();
void rva00569D80();
void Rva004C1040(int);
int Rva00459060(bool);
int rva005A9B00(Object*,void*);
class DrawableList;
void pickAndPlayUnitVoiceResponse(const DrawableList*,GameMessage::Type,PickAndPlayInfo* = 0);

class CommandTranslator { public:
 virtual GameMessageDisposition translateGameMessage(const GameMessage*);
 virtual ~CommandTranslator();
private:
 int opaque04; bool m_teamExists; char pad09[3];
 ICoord2D m_mouseRightDragAnchor, m_mouseRightDragLift;
 unsigned m_mouseRightDown, m_mouseRightUp, field24, field28; bool field2c;
 public:
 enum CommandEvaluateType { CONTEXT_COMMAND, CONTEXT_HINT, CONTEXT_EVALUATE };
 GameMessage::Type evaluateContextCommand(Drawable*,const Coord3D*,CommandEvaluateType);
 const CommandButton* rva0042970A(int);
private:
 int rva00428EEB(const CommandButton*,int,Drawable*,const Coord3D*);
 int issueMoveToLocationCommand(const Coord3D*,Drawable*,int);
 int issueSpecialPowerCommand(const CommandButton*,int,Drawable*,const Coord3D*,Object*);
 int issueAttackCommand(Drawable*,const Coord3D*,int,int);
 int issueFireWeaponCommand(const CommandButton*,int,Drawable*,const Coord3D*);
 int issueCombatDropCommand(const CommandButton*,int,Drawable*,const Coord3D*);
 int evaluateForceAttack(Drawable*,const Coord3D*,::CommandEvaluateType);
 void rva005A9C90(const GameMessage*);
};

struct HeroHolder { Object* hero; Object* previous; };

static Object* iNeedAHero(Object* previous)
{
 Player* localPlayer=ThePlayerList->getLocalPlayer();
 if(!localPlayer) return 0;
 HeroHolder holder; holder.hero=0; holder.previous=previous;
 localPlayer->iterateObjects(rva005A9B00,&holder);
 if(!holder.hero && previous) { holder.previous=0; localPlayer->iterateObjects(rva005A9B00,&holder); }
 return holder.hero;
}

// ZH canObjectForceAttack, reference34f59164f6; native4291C8..429276
// and WB00E79D50 preserve the three argument meanings. Native uses EDI/ESI
// for the first two arguments; keeping the static noinline definition with
// its actual callers lets MSVC reproduce that internal calling convention.
// Target kind bits108:04 and112:10 replace the donor queries; all object
// attack calls bind existing native providers. Coord3D uses its canonical tag.
static __declspec(noinline) int canObjectForceAttack(Object* obj,const Object* victim,const Coord3D* pos)
{
 if(!obj->isAbleToAttack()) return 0;
 if(victim) {
  int result=obj->getAbleToAttackSpecificObject(ATTACK_TYPE_ONE,victim,SOURCE_ZERO);
  if(result!=3 && result!=2 && (obj->m_template->kind112&0x10)) {
   SpawnBehaviorInterface* spawn=obj->getSpawnBehaviorInterface();
   if(spawn) { Object* slave=spawn->getClosestSlave(victim->getPosition()); if(slave) result=slave->getAbleToAttackSpecificObject(ATTACK_TYPE_ONE,victim,SOURCE_ZERO); }
  }
  return result;
 }
 if(pos) {
  if((obj->m_template->kind108&4) || (obj->m_template->kind112&0x10)) {
   SpawnBehaviorInterface* spawn=obj->getSpawnBehaviorInterface();
   if(spawn) spawn->getClosestSlave(pos);
  }
  return obj->getAbleToUseWeaponAgainstTarget(ATTACK_TYPE_ZERO,0,pos,SOURCE_ZERO);
 }
 return 0;
}
static __declspec(noinline) int canAnyForceAttack(const SelectedDrawableList* allSelected,const Object* victim,const Coord3D* pos)
{
 for(SelectedDrawableList::const_iterator it=allSelected->begin();it!=allSelected->end();++it) {
  Drawable* draw=*it; if(!draw) continue;
  Object* obj=draw->getObject(); if(!obj) continue;
  return canObjectForceAttack(obj,victim,pos);
 }
 return 0;
}

// ZH/BFME1 evaluateForceAttack adapted to native429CBB..429E11 (342B),
// WB00E79A40: target message IDs426/427 and hintsA8/A9/AA,36B voice info,
// selected-list slot124 and message-create slot48. Both visible static
// helpers above retain the native compiler-selected internal register ABI.
int CommandTranslator::evaluateForceAttack(Drawable* draw,const Coord3D* pos,::CommandEvaluateType type)
{
 int retVal=0;
 if(!draw && !pos) return retVal;
 const SelectedDrawableList* allSelected=TheInGameUI->getAllSelectedDrawables();
 if(draw) {
  Object* obj=draw->getObject();
  if(!obj) return retVal;
  int result=canAnyForceAttack(allSelected,obj,pos);
  if(result==3 || result==2) {
   retVal=0x426;
   if(type==DO_COMMAND) {
    Rva004D92FE info;
    info.m_drawTarget=draw;
    pickAndPlayUnitVoiceResponse((const DrawableList*)allSelected,(GameMessage::Type)0x426,(PickAndPlayInfo*)&info);
    GameMessage* newMsg=TheMessageStream->appendMessage((GameMessage::Type)0x426);
    newMsg->appendObjectIDArgument(obj->getID());
    newMsg->appendLocationArgument(*pos);
   } else if(type==DO_HINT) {
    retVal=0xa9;
    TheMessageStream->appendMessage((GameMessage::Type)0xa9);
   }
  } else if(result==1 && type==DO_HINT) {
   retVal=0xa8;
   TheMessageStream->appendMessage((GameMessage::Type)0xa8);
  }
 } else if(pos) {
  int result=canAnyForceAttack(allSelected,0,pos);
  if(result==3 || result==2) {
   retVal=0x427;
   if(type==DO_COMMAND) {
    Rva004D92FE info;
    info.m_position=*pos;
    pickAndPlayUnitVoiceResponse((const DrawableList*)allSelected,(GameMessage::Type)0x427,(PickAndPlayInfo*)&info);
    GameMessage* newMsg=TheMessageStream->appendMessage((GameMessage::Type)0x427);
    newMsg->appendLocationArgument(*pos);
   } else if(type==DO_HINT) {
    retVal=0xaa;
    TheMessageStream->appendMessage((GameMessage::Type)0xaa);
   }
  } else if(result==1 && type==DO_HINT) {
   retVal=0xa8;
   TheMessageStream->appendMessage((GameMessage::Type)0xa8);
  }
 }
 return retVal;
}


// Native/WB context-command views. ZH CommandXlat.cpp1425..2331 provides
// command ordering; BFME2-only selection, deploy, chaining and dock paths
// below come from WB E79EC0 and retail829E11..82AF97, RET12.
template<int N> class ContextSlots : public ContextSlots<N-1> { public: virtual void slot(ContextSlots<N>*); };
template<> class ContextSlots<0> {};
struct ContextPlayers { char pad[0x10];Player*local;Player*getLocalPlayer() const {return local;} };
class ContextMouse : public ContextSlots<18> { public: virtual void getPosition(int*,int*); };
class ContextView : public ContextSlots<90> { public: virtual bool screenToTerrain(const ICoord2D*,Coord3D*,int); };
class ContextUI : public ContextSlots<47> { public:
 virtual void setCommand(const CommandButton*); virtual const CommandButton* command();
 virtual void pad49(); virtual void pad50(); virtual void pad51(); virtual void pad52();
 virtual void pad53(); virtual void pad54(); virtual void pad55(); virtual void pad56();
 virtual void pad57(); virtual void pad58(); virtual void pad59(); virtual void pad60();
 virtual void pad61(); virtual void pad62(); virtual void pad63(); virtual void pad64();
 virtual void pad65(); virtual void selectDrawable(Drawable*); virtual void pad67(); virtual void deselect();
 virtual void selectAll(int,Player*); virtual int selectedCount(); virtual void pad71(); virtual void pad72();
 virtual const SelectedDrawableList* selected() const; virtual void pad74(); virtual Drawable* first();
 virtual void slotT76(); virtual void slotT77(); virtual void slotT78(); virtual void slotT79(); virtual void slotT80(); virtual void slotT81(); virtual void slotT82(); virtual void slotT83(); virtual void slotT84(); virtual void slotT85(); virtual void slotT86(); virtual void slotT87(); virtual void slotT88(); virtual void slotT89(); virtual void slotT90(); virtual void slotT91(); virtual void slotT92(); virtual void slotT93(); virtual void slotT94(); virtual void slotT95(); virtual void slotT96();
 virtual void selectMatching();
 char pad04[0x8b0-4];bool waypoint;char pad8b1[7];bool forceAttack,forceMove,preferSelection;bool rotateLeft,rotateRight,zoomIn,zoomOut,extra8bf,extra8c0,extra8c1,extra8c2;bool forceAttackMode()const{return forceAttack;}
};
static __forceinline ContextUI* contextUI() { return (ContextUI*)TheInGameUI; }
struct ContextButton { char pad[0x14];int type;int word18;unsigned options;char pad20[0x24];class Overridable* special; };
static __forceinline const ContextButton* contextButton(const CommandButton*c) { return (const ContextButton*)c; }
class Overridable { public: const Overridable* friend_getFinalOverride() const; };
struct ContextPower { char pad[0x14];int id;int word18;int type; };
struct ContextObject { char pad0[0x250];void* container;int word254;void* ai;char pad25c[0xa8];Team* team;Team*getTeam() const {return team;} char pad308[0x131];bool masked; };
static __forceinline ContextObject* contextObject(Object*o) { return (ContextObject*)o; }
static __forceinline bool contextKind(const Object*o,int bit) { return (((const unsigned char*)o->m_template)[0x108+(bit>>3)]&(1<<(bit&7)))!=0; }
class Rva0055A88BDwordField { public: int get() const; };
class Rva0006EE7A : public BitFlags<69> { public: Rva0006EE7A(int,int,int); };
struct Rva0029AEF9Item;
bool __cdecl Rva0029C752Check();
bool __stdcall Rva0029AEF9Check(Rva0029AEF9Item*,int,int,int,int,int);
unsigned char Rva0027DC65Check(float*);
struct Arg;
class Rva00429007 { public: int rva00429007(Arg*,int); };
class Rva00429093 { public: int rva00429093(Arg*,int); };
class Rva00429112 { public: int rva00429112(Arg*,int); };
int __stdcall Rva00428EEBIssueFireWeapon(const CommandButton*,int,Drawable*,const Coord3D*);
class Rva0031D5F8 { public: void* rva0031D5F8(const AsciiString*); };
class CommandSet { public: const CommandButton* getCommandButton(int) const; };
class Rva0026F0F0 { public: void* rva0026F0F0(const void*); };
class Rva0029DE76 { public: bool rva0029DE76(const Coord3D*); };
class ActionManager { public: GameMessage::Type rva0041CE06(const Object*); };
extern ActionManager* TheActionManager;
class Keyboard { public: bool isShift(); };extern Keyboard* TheKeyboard;
class Pathfinder { public: bool QuickDoesPathExist(Object*,const Coord3D*,const Coord3D*,int); bool IsWaterCell(int,int); };
class AI;extern AI* TheAI;struct ContextAI {char pad[0x10];Pathfinder*path;};
class TerrainLogic;extern TerrainLogic* TheTerrainLogic;
class UpgradeCenter;extern UpgradeCenter* TheUpgradeCenter;
enum CellShroudStatus { CONTEXT_SHROUD_NONE };
class PartitionManager { public: CellShroudStatus getShroudStatusForPlayer(int,const Coord3D*) const; };extern PartitionManager*ThePartitionManager;
class ContextAIUpdate : public ContextSlots<90> { public: virtual bool active(); };
class ContextContain : public ContextSlots<69> { public: virtual int unload(int); };
const CommandButton* __stdcall Rva0042970AGet(int);
struct ContextPoint : public Coord3D { ContextPoint(const Coord3D&c) {x=c.x;y=c.y;z=c.z;} };
bool __fastcall canSelectionSalvage(const Object*);


#include "Code/GameEngine/Include/Common/BfmeAudioEventPrefix136.h"
static __forceinline int translateHeight(const IRegion2D&r){return r.hi.y-r.lo.y;}
static __forceinline int translateWidth(const IRegion2D&r){return r.hi.x-r.lo.x;}
struct TranslateUIInput { char pad[0x15];bool enabled,active;bool getInputEnabled() const {return enabled&&active;} };
struct TranslateMouseFields {char pad[0x12e8];unsigned dragTolerance;int pad12ec;unsigned clickTime;};
struct TranslateGlobalFields {char pad[0x5c];bool alternate;char pad5d[0xa44-0x5d];int netMinPlayers;char pada48[0xbbd-0xa48];bool fastMode;char padbbe[0x11c9-0xbbe];bool timeControls;};
static __forceinline TranslateGlobalFields* translateGlobals(){return (TranslateGlobalFields*)TheWritableGlobalData;}
struct TranslateLogicFields { char pad[0x110];int mode;bool isReplay()const{return mode==3;} };
struct TranslateTransition {char pad[0x24];int first,second;char pad2c[0x25];bool flag;};
class TranslateGameClient : public ContextSlots<16> { public: virtual Drawable*find(unsigned);virtual Drawable*first(); };
class TranslateGameInfo : public ContextSlots<19> { public: virtual bool multiplayer(); };
class TranslateWindowManager : public ContextSlots<60> {public:virtual GameWindow*window(GameWindow*,int);};
class TranslateDisplay : public ContextSlots<83> {public:virtual void screenshot(int);};
class TranslateAudio : public ContextSlots<25> {public: virtual unsigned add(const BfmeAudioEventPrefix136*);
virtual void slotAudio26();virtual void slotAudio27();virtual void slotAudio28();virtual void slotAudio29();virtual void slotAudio30();virtual void slotAudio31();virtual void slotAudio32();virtual void slotAudio33();virtual void slotAudio34();virtual void slotAudio35();virtual void slotAudio36();virtual void slotAudio37();virtual void slotAudio38();virtual void slotAudio39();virtual void slotAudio40();virtual void slotAudio41();virtual void slotAudio42();virtual void slotAudio43();virtual void slotAudio44();virtual void slotAudio45();virtual void slotAudio46();virtual void slotAudio47();virtual void slotAudio48();virtual void slotAudio49();virtual void slotAudio50();virtual void slotAudio51();virtual void slotAudio52();virtual void slotAudio53();virtual void slotAudio54();virtual void slotAudio55();virtual void slotAudio56();virtual void slotAudio57();virtual void slotAudio58();virtual void slotAudio59();virtual void slotAudio60();virtual void slotAudio61();virtual void slotAudio62();virtual void slotAudio63();virtual void slotAudio64();virtual void slotAudio65();virtual void slotAudio66();virtual void slotAudio67();virtual void slotAudio68();virtual void slotAudio69();virtual void slotAudio70();virtual void slotAudio71();virtual void slotAudio72();virtual void slotAudio73();virtual void slotAudio74();virtual void slotAudio75();virtual void slotAudio76();virtual void slotAudio77();
 virtual const char*misc() const;};
class TranslateMessages : public ContextSlots<16> {public:virtual void __cdecl message(UnicodeString,...);};
class TranslateGameEngine : public ContextSlots<16> {public:virtual void increase();virtual void decrease();};
class GameEngine;extern GameEngine*TheGameEngine;
class Eva;extern Eva*TheEva;class Rva001DD3DD {public:void update();};
class BfmeMemberRV {public:bool bfmeAskRV();};
class Bfme939Helper {public:int get()const;};
class BfmeSelectionState {public:bool isSelectionLocked() const;};
class Rva002D3861 {public:void rva002D3861();};
class RadarWindowOverrideSource;extern RadarWindowOverrideSource*theRadarWindowOverrideSource;
class GameSpyBuddyMessageQueueInterface;extern GameSpyBuddyMessageQueueInterface*TheGameSpyBuddyMessageQueue;
// Draft data identity: native E046B8 is owned under an address-derived name;
// reconcile its owner before landing this parent. No alias is defined here.
extern void* ContextMessengerWindow;
class AptMessenger {public:static void OpenScreen();};class AptInGameChat {public:static void OpenScreen(int);};
void Rva00511730(int);void Rva004E41AB();void Rva0050EC24();void Rva0051B8EA();void ToggleControlBar(bool);void Rva0029B4F9Init();
unsigned Rva0030F099(bool);void __stdcall Rva0042AF97Handle(GameMessage*);
struct Rva00429276Entry;
struct Rva00429276Holder {Rva00429276Entry*first;Rva00429276Entry*second;};
int Rva00429276(Rva00429276Entry*,Rva00429276Holder*);
static __declspec(noinline) Rva00429276Entry* Rva004292A6(Rva00429276Entry*second) {
 Player*player=((ContextPlayers*)ThePlayerList)->getLocalPlayer();if(!player)return 0;
 Rva00429276Holder holder;holder.first=0;holder.second=second;
 player->iterateObjects((int(*)(Object*,void*))Rva00429276,&holder);
 if(!holder.first&&second){holder.second=0;player->iterateObjects((int(*)(Object*,void*))Rva00429276,&holder);}return holder.first;
}
namespace _STL {
template<> list<Drawable*,allocator<Drawable*> >::list(const list<Drawable*,allocator<Drawable*> >&);
template<> _List_base<Drawable*,allocator<Drawable*> >::~_List_base();
}

// ZH/BF1 CommandXlat::translateGameMessage is the semantic guide.
// Complete native42B0DE..42BF7F code3745B plus63 switch entries252B,
// extent3997 through42C07B. WB E7CBE0 supplies original statement scopes.
GameMessageDisposition CommandTranslator::translateGameMessage(const GameMessage*msg)
{
 InGameUI*initialUI=TheInGameUI;
 GameMessage::Type t=msg->getType();
 GameMessageDisposition disp=KEEP_MESSAGE;
 if(t!=0x70&&t!=0x1d&&t!=0x6a5&&t!=0x7d9&&t!=0x7ed&&t!=0x45f&&t!=0x6a6&&t!=0x6b8&&t!=0x448&&t!=0x469&&!((TranslateUIInput*)initialUI)->getInputEnabled()) {
  bool system=false;switch(t){case 0x3ec:case 0x447:case 0x44a:case 0x6ba:case 0x6bb:system=true;break;}if(!system)return DESTROY_MESSAGE;
 }
 switch(t) {
 case 0x5c:((ContextUI*)initialUI)->selectMatching();disp=DESTROY_MESSAGE;break;
 case 0x63: {
  if(!((TranslateGameClient*)TheGameClient)->first())break;
  Object*previous=0;
  if(contextUI()->selectedCount()>0){Drawable*selected=contextUI()->first();if(selected){Object*object=selected->getObject();if(object&&contextKind(object,90))previous=object;}}
  Object*hero=(Object*)Rva004292A6((Rva00429276Entry*)previous);if(!hero)break;
  if(hero->m_containedBy)hero=hero->m_containedBy;
  Drawable*heroDraw=((Thing*)hero)->getDrawable();if(!heroDraw)break;
  contextUI()->deselect();GameMessage*team=TheMessageStream->appendMessage(GameMessage::MSG_CREATE_SELECTED_GROUP);team->appendBooleanArgument(true);team->appendObjectIDArgument(hero->getID());contextUI()->selectDrawable(heroDraw);TheTacticalView->lookAt(heroDraw->getPosition());disp=DESTROY_MESSAGE;break;
 }
 case 0x61:{Player*local=((ContextPlayers*)ThePlayerList)->getLocalPlayer();if(local){Object*o=(Object*)local->rva002ABCF0(1,0);if(o)TheTacticalView->lookAt(o->getPosition());}disp=DESTROY_MESSAGE;break;}
 case 0x62:if(TheEva)((Rva001DD3DD*)TheEva)->update();disp=DESTROY_MESSAGE;break;
 case 0x64:((ContextUI*)initialUI)->selectAll(0,((ContextPlayers*)ThePlayerList)->getLocalPlayer());disp=DESTROY_MESSAGE;break;
 case 0x65:TheMessageStream->appendMessage((GameMessage::Type)0x436);disp=DESTROY_MESSAGE;break;
 case 0x66:TheMessageStream->appendMessage((GameMessage::Type)0x435);disp=DESTROY_MESSAGE;break;
 case 0x68:TheMessageStream->appendMessage((GameMessage::Type)0x449);disp=DESTROY_MESSAGE;break;
 case 0x67:disp=DESTROY_MESSAGE;break;
 case 0x69:disp=DESTROY_MESSAGE;break;
 case 0x6a:disp=DESTROY_MESSAGE;break;
 case 0x6d:{GameLogic*logic=TheGameLogic;if(logic->isInMultiplayerGame()&&!((TranslateLogicFields*)logic)->isReplay()){Player*local=((ContextPlayers*)ThePlayerList)->getLocalPlayer();if(local&&((BfmeMemberRV*)local)->bfmeAskRV()||!translateGlobals()->netMinPlayers)AptInGameChat::OpenScreen(0);}disp=DESTROY_MESSAGE;break;}
 case 0x6e:{GameLogic*logic=TheGameLogic;if(logic->isInMultiplayerGame()&&!((TranslateLogicFields*)logic)->isReplay()){Player*local=((ContextPlayers*)ThePlayerList)->getLocalPlayer();if(local||!translateGlobals()->netMinPlayers){if(((BfmeMemberRV*)local)->bfmeAskRV())AptInGameChat::OpenScreen(1);else AptInGameChat::OpenScreen(4);}}disp=DESTROY_MESSAGE;break;}
 case 0x6c:if(TheGameSpyBuddyMessageQueue){if(!ContextMessengerWindow)AptMessenger::OpenScreen();else Rva00511730(0);}disp=DESTROY_MESSAGE;break;
 case 0x6f:{GameLogic*logic=TheGameLogic;if(logic->rva0042219()&&!((TranslateTransition*)TheTransitionHandler)->first&&!((TranslateTransition*)TheTransitionHandler)->second){if(logic->rva0023C6FD())Rva0050EC24();else Rva004E41AB();}disp=DESTROY_MESSAGE;break;}
 case 0x93:{GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)0x468);m->appendIntegerArgument(2);disp=DESTROY_MESSAGE;break;}
 case 0x95:{GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)0x468);m->appendIntegerArgument(1);disp=DESTROY_MESSAGE;break;}
 case 0x94:{GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)0x468);m->appendIntegerArgument(3);disp=DESTROY_MESSAGE;break;}
 case 0x97:{GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)0x469);m->appendIntegerArgument(1);m->appendIntegerArgument(0);disp=DESTROY_MESSAGE;break;}
 case 0x96:{GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)0x469);m->appendIntegerArgument(0);m->appendIntegerArgument(1);disp=DESTROY_MESSAGE;break;}
 case 0x98:TheMessageStream->appendMessage((GameMessage::Type)0x470);disp=DESTROY_MESSAGE;break;
 case 0x90:{GameLogic*logic=TheGameLogic;if(logic->isInMultiplayerGame()&&!((TranslateLogicFields*)logic)->isReplay()&&((BfmeMemberRV*)((ContextPlayers*)ThePlayerList)->getLocalPlayer())->bfmeAskRV()&&(!translateGlobals()->netMinPlayers||((TranslateGameInfo*)TheGameInfo)->multiplayer())){int count;Player*local=((ContextPlayers*)ThePlayerList)->getLocalPlayer();const ThingTemplate*thing=TheThingFactory->findTemplate(*(AsciiString*)((char*)(*(PlayerTemplate**)((char*)local+0x34))+0x17c));((ContextPlayers*)ThePlayerList)->getLocalPlayer()->countObjectsByThingTemplate(1,&thing,false,&count,true);if(count<*(int*)((char*)TheMultiplayerSettings+0x18)){const CommandButton*c=TheControlBar->findCommandButton(AsciiString("Command_PlaceBeacon"));contextUI()->setCommand(c);}}disp=DESTROY_MESSAGE;break;}
 case 0x91:disp=DESTROY_MESSAGE;break;
 case 0x70:{TranslateTransition*c=(TranslateTransition*)TheTransitionHandler;if(c&&(c->first||c->second))c->flag=true;else Rva0051B8EA();disp=DESTROY_MESSAGE;break;}
 case 0x71: {
  if(*(bool*)((char*)TheShell+0x5c)){WindowLayout*w=TheShell->top();if(w)w->hide(!w->m_hidden);}
  else if(!(TheRecorder&&((Bfme939Helper*)TheRecorder)->get()==1)) {
   bool hide=false;if(TheWindowManager){int id=TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:ControlBarParent"));GameWindow*w=((TranslateWindowManager*)TheWindowManager)->window(0,id);if(w)hide=!w->winIsHidden();}ToggleControlBar(true);
  }disp=DESTROY_MESSAGE;break;
 }
 case 118:((ContextUI*)initialUI)->forceMove=true;break;
 case 119:((ContextUI*)initialUI)->forceMove=false;break;
 case 120:((ContextUI*)initialUI)->waypoint=true;break;
 case 122:((ContextUI*)initialUI)->preferSelection=true;break;
 case 123:((ContextUI*)initialUI)->preferSelection=false;break;
 case 121:((ContextUI*)initialUI)->waypoint=false;break;
 case 127:((ContextUI*)initialUI)->rotateLeft=true;break;
 case 128:((ContextUI*)initialUI)->rotateLeft=false;break;
 case 129:((ContextUI*)initialUI)->rotateRight=true;break;
 case 130:((ContextUI*)initialUI)->rotateRight=false;break;
 case 131:((ContextUI*)initialUI)->zoomIn=true;break;
 case 132:((ContextUI*)initialUI)->zoomIn=false;break;
 case 133:((ContextUI*)initialUI)->zoomOut=true;break;
 case 134:((ContextUI*)initialUI)->zoomOut=false;break;
 case 0x87:Rva0029B4F9Init();break;
 case 136:((ContextUI*)initialUI)->extra8bf=true;break;
 case 137:((ContextUI*)initialUI)->extra8bf=false;break;
 case 138:((ContextUI*)initialUI)->extra8c0=true;break;
 case 139:((ContextUI*)initialUI)->extra8c0=false;break;
 case 140:((ContextUI*)initialUI)->extra8c1=true;break;
 case 141:((ContextUI*)initialUI)->extra8c1=false;break;
 case 142:((ContextUI*)initialUI)->extra8c2=true;break;
 case 143:((ContextUI*)initialUI)->extra8c2=false;break;
 case 0x7d:if(TheGameLogic->isInMultiplayerGame()){BfmeAudioEventPrefix136 event(*(const OpaqueRefElement4*)(((TranslateAudio*)TheAudio)->misc()+0x28),0);((TranslateAudio*)TheAudio)->add(&event);disp=DESTROY_MESSAGE;TheMessageStream->appendMessage((GameMessage::Type)0x438);}break;
 case 0x7c:if(TheDisplay)((TranslateDisplay*)TheDisplay)->screenshot(0);disp=DESTROY_MESSAGE;break;
 case 0x3e9:case 0x3eb:case 0x3f8:case 0x3f9:case 0x3fa:case 0x3fb:case 0x3fc:case 0x3fd:case 0x3fe:case 0x3ff:case 0x400:case 0x401:case 0x461:{
  SelectedDrawableList list=*contextUI()->selected();
  for(SelectedDrawableList::iterator it=list.begin();it!=list.end();) {Drawable*d=*it;if(d->getObject()&&d->getObject()->isLocallyControlled()){++it;continue;}else it=list.erase(it);}
  if(!list.empty())pickAndPlayUnitVoiceResponse((const DrawableList*)&list,t,0);m_teamExists=true;break;
 }
 case 0x3ea:case 0x402:case 0x403:case 0x404:case 0x405:case 0x406:case 0x407:case 0x408:case 0x409:case 0x40a:case 0x40b:m_teamExists=true;break;
 case 0x3ec:m_teamExists=false;break;
 case 0xa2:{bool selected=contextUI()->selectedCount()>0;if(!selected){const CommandButton*c=contextUI()->command();if(c){int commandType=contextButton(c)->type;if(commandType==32||commandType==38)selected=true;}}if(selected){Drawable*d=((TranslateGameClient*)TheGameClient)->find(msg->getArgument(0)->drawableID);if(d){if(contextUI()->forceAttackMode())evaluateForceAttack(d,d->getPosition(),DO_HINT);else evaluateContextCommand(d,d->getPosition(),CONTEXT_HINT);}}break;}
 case 0xa3:{ContextPoint position(msg->getArgument(0)->location);if(contextUI()->forceAttackMode())evaluateForceAttack(0,&position,DO_HINT);else evaluateContextCommand(0,&position,CONTEXT_HINT);break;}
 case 0xe:m_mouseRightDragAnchor=msg->getArgument(0)->pixel;m_mouseRightDown=msg->getArgument(2)->integer;field2c=false;break;
 case 3:{ICoord2D current=msg->getArgument(0)->pixel;if(TheMouse->rva001EDD80((const Rva001EDD80Pair*)&m_mouseRightDragAnchor,(const Rva001EDD80Pair*)&current))field2c=true;break;}
 case 0x10:m_mouseRightDragLift=msg->getArgument(0)->pixel;m_mouseRightUp=msg->getArgument(2)->integer;break;
 case 6:field28=msg->getArgument(2)->integer;break;
 case 4:field24=msg->getArgument(2)->integer;break;
 case 0x1b:case 0x1c:{
  bool isPoint=!field2c;if(m_mouseRightUp-m_mouseRightDown<((TranslateMouseFields*)TheMouse)->clickTime)isPoint=true;
  const CommandButton*command=contextUI()->command();int commandType=command?contextButton(command)->type:0;
  if(command&&commandType!=10)break;
  if(translateGlobals()->alternate&&isPoint){if(!TheTacticalView)break;Coord3D pos;((ContextView*)TheTacticalView)->screenToTerrain(&msg->getArgument(0)->pixel,&pos,0);bool controllable=TheInGameUI->areSelectedObjectsControllable();if(!controllable&&command&&(commandType==32||commandType==38))controllable=true;
   if(controllable){int pickType=Rva0030F099(contextUI()->forceAttackMode());Drawable*d=TheTacticalView->pickDrawable(&msg->getArgument(0)->pixelRegion.lo,contextUI()->forceAttackMode(),pickType);if(contextUI()->forceAttackMode())evaluateForceAttack(d,&pos,DO_COMMAND);else {int result=evaluateContextCommand(d,&pos,CONTEXT_COMMAND);if(commandType==24&&result==0xa5)contextUI()->setCommand(0);}disp=DESTROY_MESSAGE;}
  }break;
 }
 case 0x17:{
  bool isPoint=((unsigned)translateHeight(msg->getArgument(0)->pixelRegion)<=((TranslateMouseFields*)TheMouse)->dragTolerance&&(unsigned)translateWidth(msg->getArgument(0)->pixelRegion)<=((TranslateMouseFields*)TheMouse)->dragTolerance);
  if(field28-field24<((TranslateMouseFields*)TheMouse)->clickTime)isPoint=true;
  if(!TheTacticalView)break;
  const CommandButton*command=contextUI()->command();int commandType=command?contextButton(command)->type:0;
  if((!command||commandType==10)&&translateGlobals()->alternate)break;
  Coord3D pos;((ContextView*)TheTacticalView)->screenToTerrain(&msg->getArgument(0)->pixel,&pos,0);
  bool controllable=TheInGameUI->areSelectedObjectsControllable();if(!controllable&&command&&(commandType==32||commandType==38))controllable=true;
  if(isPoint&&controllable){int pickType=Rva0030F099(contextUI()->forceAttackMode());Drawable*d=TheTacticalView->pickDrawable(&msg->getArgument(0)->pixelRegion.lo,contextUI()->forceAttackMode(),pickType);if(contextUI()->forceAttackMode())evaluateForceAttack(d,&pos,DO_COMMAND);else{int result=evaluateContextCommand(d,&pos,CONTEXT_COMMAND);if(commandType==24&&result==0xa5)contextUI()->setCommand(0);}disp=DESTROY_MESSAGE;}
  break;
 }
 case 0x18:Rva0042AF97Handle((GameMessage*)msg);break;
 case 0x9c:if(((TranslateLogicFields*)TheGameLogic)->isReplay()){
  if(TheWritableGlobalData){translateGlobals()->fastMode=1-translateGlobals()->fastMode;((TranslateMessages*)TheInGameUI)->message(UnicodeString(L">> %s"),translateGlobals()->fastMode?L"ON":L"OFF");
   if(translateGlobals()->fastMode){BfmeAudioEventPrefix136 event(*(const OpaqueRefElement4*)(((TranslateAudio*)TheAudio)->misc()+0xd0),0);((TranslateAudio*)TheAudio)->add(&event);}
   else {BfmeAudioEventPrefix136 event(*(const OpaqueRefElement4*)(((TranslateAudio*)TheAudio)->misc()+0xd4),0);((TranslateAudio*)TheAudio)->add(&event);}
  }disp=DESTROY_MESSAGE;
 }break;
 case 0x92:if(!TheLivingWorldLogic||!((BfmeSelectionState*)TheLivingWorldLogic)->isSelectionLocked())if(TheControlBar)TheControlBar->rva0031AD94();disp=DESTROY_MESSAGE;break;
 case 0x99:if(theRadarWindowOverrideSource&&((BfmeMemberRV*)((ContextPlayers*)ThePlayerList)->getLocalPlayer())->bfmeAskRV())((Rva002D3861*)theRadarWindowOverrideSource)->rva002D3861();disp=DESTROY_MESSAGE;break;
 case 0x9a:TheMessageStream->appendMessage((GameMessage::Type)0x41c);break;
 case 0x9d:if(TheWritableGlobalData&&translateGlobals()->timeControls)((TranslateGameEngine*)TheGameEngine)->increase();break;
 case 0x9e:if(TheWritableGlobalData&&translateGlobals()->timeControls)((TranslateGameEngine*)TheGameEngine)->decrease();break;
 }
 return disp;
}
