// cl: -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/shims/stringbaseunicode /O1 /G7 /arch:SSE /ICode/Libraries/Include -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/MessageStream
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
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/IRegion2D.h"
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
 char pad78[0x19c]; Object* m_containedBy;
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
 int iterateObjects(int (*)(Object*,void*),void*) const;
 void countObjectsByThingTemplate(int,const ThingTemplate* const*,bool,int*,bool) const;
};
class PlayerList { public: char pad00[0xc]; Player* m_localPlayer; Player* getLocalPlayer() const { return m_localPlayer; } };
class ControlBar { public: const CommandButton* findCommandButton(const AsciiString&); void togglePurchaseScience(); };
class GameLogic { public: char pad00[0x91]; bool m_showBehindBuildingMarkers; char pad92[0x7a]; int m_mode;
 bool isInMultiplayerGame(); bool rva000652A0() const; bool isInReplayGame() const { return m_mode==3; }
};
// TU-local field view of retail's GlobalData; the one writable global at
// 0x012ED5C8 is declared with EA's own class below and cast at each use.
class RvaGlobalDataView { public:
 char pad00[0x38]; bool m_useCloudMap; char pad39[0xb]; bool m_useLightMap; char pad45[0x1b]; bool m_useAlternateMouse;
 char pad61[3]; bool m_useShadowVolumes; char pad65[0xaa7]; int m_netMinPlayers; char padb10[0x7c]; int m_maxParticleCount;
 char padb90[0xc9]; bool m_TiVOFastMode;
};
class Mouse { public: int getCursorIndex(const AsciiString&); char pad00[0x10ec]; unsigned m_dragTolerance; char pad10f0[4]; unsigned m_clickTime;
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
struct ContextPlayerIndex {char pad[0x54];int index;int getIndex() const {return index;}};
struct ContextPlayers { char pad[0x10];Player*local;Player*getLocalPlayer() const {return local;} };
class ContextMouse : public ContextSlots<18> { public: virtual void getPosition(int*,int*); };
class ContextView : public ContextSlots<90> { public: virtual bool screenToTerrain(const ICoord2D*,Coord3D*,int); };
class ContextUI : public ContextSlots<47> { public:
 virtual void setCommand(const CommandButton*); virtual const CommandButton* command();
 virtual void pad49(); virtual void pad50(); virtual void pad51(); virtual void pad52();
 virtual void pad53(); virtual void pad54(); virtual void pad55(); virtual void pad56();
 virtual void pad57(); virtual void pad58(); virtual void pad59(); virtual void pad60();
 virtual void pad61(); virtual void pad62(); virtual void pad63(); virtual void pad64();
 virtual void pad65(); virtual void pad66(); virtual void pad67(); virtual void pad68();
 virtual void pad69(); virtual int selectedCount(); virtual void pad71(); virtual void pad72();
 virtual const SelectedDrawableList* selected() const; virtual void pad74(); virtual Drawable* first();
 char pad04[0x8b0-4];bool waypoint;char pad8b1[7];bool forceAttack,forceMove,preferSelection; bool getForceAttack() const {return forceAttack;}
};
static __forceinline ContextUI* contextUI() { return (ContextUI*)TheInGameUI; }
struct ContextButton { char pad[0x14];int type;int word18;unsigned options; unsigned getOptions() const {return options;}char pad20[0x24];class Overridable* special; };
static __forceinline const ContextButton* contextButton(const CommandButton*c) { return (const ContextButton*)c; }
class Overridable { public: const Overridable* friend_getFinalOverride() const; };
struct ContextPower { char pad[0x14];int id;int word18;int type; };
struct ContextObject { char pad0[0x250];void* container;int word254;void* ai;char pad25c[0xa8];Team* team;Team*getTeam() const {return team;} char pad308[0x131];bool masked; };
static __forceinline ContextObject* contextObject(Object*o) { return (ContextObject*)o; }
static __forceinline bool contextKind(const Object*o,int bit) { return (((const unsigned char*)o->m_template)[0x108+(bit>>3)]&(1<<(bit&7)))!=0; }
class Rva0055A88BDwordField { public: int get() const; };
class Rva0006EE7A : public BitFlags<69> { public: Rva0006EE7A(int,int,int); };
struct Rva0029AEF9Item;
bool Rva0027DC65Check(float*);
struct Arg;
class Rva00429007 { public: int rva00429007(Arg*,int); };
class Rva00429093 { public: int rva00429093(Arg*,int); };
class Rva00429112 { public: int rva00429112(Arg*,int); };
class Rva0031D5F8 { public: void* rva0031D5F8(const AsciiString*); };
class CommandSet { public: const CommandButton* getCommandButton(int) const; };
class Rva0026F0F0 { public: void* rva0026F0F0(const void*); };
class Rva0029DE76 { public: bool rva0029DE76(const Coord3D*); };
class ActionManager { public: GameMessage::Type rva0041CE06(const Object*); };
extern ActionManager* TheActionManager;
class Keyboard { public: bool isShift(); };extern Keyboard* TheKeyboard;
class Pathfinder { public: bool QuickDoesPathExist(Object*,const Coord3D*,const Coord3D*,int); bool IsWaterCell(int,int); };
class AI;extern AI* TheAI;struct ContextAI {char pad[0x10];Pathfinder*path; Pathfinder*getPathfinder() const {return path;}};
class TerrainLogic;extern TerrainLogic* TheTerrainLogic;
class UpgradeCenter;extern UpgradeCenter* TheUpgradeCenter;
enum CellShroudStatus { CONTEXT_SHROUD_NONE };
#include "../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager*ThePartitionManager;
class ContextAIUpdate : public ContextSlots<90> { public: virtual bool active(); };
class ContextContain : public ContextSlots<69> { public: virtual int unload(int); };
struct ContextPoint : public Coord3D { ContextPoint(const Coord3D&c) {x=c.x;y=c.y;z=c.z;} };
bool __fastcall canSelectionSalvage(const Object*);

// Native429E11..42AF97,4486B,RET12; WB E79EC0. Complete ZH-guided context
// evaluator with BFME2 branches and measured enum/layout/callee adaptations.
// ZH CommandXlat.cpp1425..2331 is the semantic guide; BFME1 donor cee35b7d8.
// Native option/force-attack getters and shared invalid-hint tail are preserved.
// The volatile read in command24 preserves the target stack-home access; it is
// a reconstruction constraint, not a claim about the original qualifier.
GameMessage::Type CommandTranslator::evaluateContextCommand(Drawable*draw,const Coord3D*pos,CommandEvaluateType type)
{
 Object*obj=draw?draw->getObject():0;
 Drawable*drawableInWay=draw;
 Coord3D terrainPosition;
 if(draw) {
  int id=((Rva0055A88BDwordField*)draw)->get();
  if(id==99999999 || id==99999996 || id==99999997 || id==99999998) {
   ICoord2D pixel;((ContextMouse*)TheMouse)->getPosition(&pixel.x,&pixel.y);
   if(((ContextView*)TheTacticalView)->screenToTerrain(&pixel,&terrainPosition,0))pos=&terrainPosition;
  }
 }
 if(!obj || (contextObject(obj)->masked && !contextKind(obj,6) && !contextKind(obj,97) && !contextKind(obj,136) && !contextKind(obj,68))) {draw=0;obj=0;}
 Object*selectedObject=0;
 if(contextUI()->selectedCount()==1) {Drawable*only=*contextUI()->selected()->begin();selectedObject=only?only->getObject():0;}
 bool allSpecial=false,allOther=false,hasSpecial=false,hasOther=false,hasGround=false,hasNonGround=false;
 const SelectedDrawableList*selection=contextUI()->selected();
 for(SelectedDrawableList::const_iterator it=selection->begin();it!=selection->end();++it) {
  Drawable*d=*it;Object*o=d?d->getObject():0;
  if(o) {
   if(contextKind(o,134))hasSpecial=true;else hasOther=true;
   if(((Thing*)o)->isAnyKindOf(Rva0006EE7A(0,55,147)))hasGround=true;else hasNonGround=true;
  }
 }
 if(hasSpecial&&!hasOther)allSpecial=true;
 if(hasGround&&!hasNonGround)allOther=true;
 if(allSpecial){draw=0;obj=0;}
 Object*originalObject=obj;Drawable*originalDraw=draw;
 if(contextUI()->forceMove){draw=0;originalDraw=0;obj=0;originalObject=0;}
 else if(contextUI()->getForceAttack())drawableInWay=draw;
 int msgType=0;
 if(obj && obj->isLocallyControlled() && contextUI()->preferSelection)return (GameMessage::Type)msgType;
 const CommandButton*command=contextUI()->command();
 if(TheInGameUI->areSelectedObjectsControllable() || (command&&(contextButton(command)->type==32||contextButton(command)->type==38||contextButton(command)->type==31))) {
  GameMessage*hintMessage;
  if(contextUI()->waypoint) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE) {if(TheTerrainLogic)msgType=issueMoveToLocationCommand(pos,draw,type);}
   else {msgType=0xb5;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendLocationArgument(*pos);}
   return (GameMessage::Type)msgType;
  }
  CanAttackResult result;
  if(command&&(command->isContextCommand()||contextButton(command)->type==24||contextButton(command)->type==32||contextButton(command)->type==38||contextButton(command)->type==11||contextButton(command)->type==31)) {
   if(originalObject&&contextKind(originalObject,6)&&!(contextButton(command)->getOptions()&0x10)){draw=originalDraw=0;obj=originalObject=0;}
   if(originalObject&&(contextKind(originalObject,97)||contextKind(originalObject,136))&&!(contextButton(command)->getOptions()&0x200000)){draw=originalDraw=0;obj=originalObject=0;}
   if(originalObject&&(contextButton(command)->getOptions()&7)) {
    switch(((ContextPlayers*)ThePlayerList)->getLocalPlayer()->getRelationship(contextObject(originalObject)->getTeam())) {
    case CONTEXT_ALLY:if(!(contextButton(command)->getOptions()&1)){draw=originalDraw=0;obj=originalObject=0;}break;
    case CONTEXT_ENEMY:if(!(contextButton(command)->getOptions()&2)){draw=originalDraw=0;obj=originalObject=0;}break;
    case CONTEXT_NEUTRAL:if(!(contextButton(command)->getOptions()&4)){draw=originalDraw=0;obj=originalObject=0;}break;
    }
   }
   bool currentlyValid=false;ObjectID objectID=obj?obj->getID():OBJECTID_NONE;
   switch(contextButton(command)->type) {
   case 11:currentlyValid=TheInGameUI->rva0029AEF9((Rva0029AEF9Item*)command,(int)obj,(int)pos,0,contextButton(command)->getOptions(),0);break;
   case 23:currentlyValid=TheInGameUI->canSelectedObjectsEffectivelyUseWeapon(command,obj,pos,InGameUI::CONTEXT_ANY);break;
   case 24:currentlyValid=TheInGameUI->canSelectedObjectsDoSpecialPower(command,*(Object*const volatile*)&originalObject,pos,InGameUI::CONTEXT_ANY,contextButton(command)->getOptions(),0);if(currentlyValid){objectID=originalObject?originalObject->getID():OBJECTID_NONE;obj=originalObject;draw=originalDraw;}break;
   case 26:currentlyValid=!obj?true:TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)15,obj,InGameUI::CONTEXT_ANY,false);break;
   case 29:currentlyValid=TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)10,obj,InGameUI::CONTEXT_ANY,false);break;
   case 30:currentlyValid=TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)11,obj,InGameUI::CONTEXT_ANY,false);break;
   case 31:{ContextPoint position(*pos);currentlyValid=Rva0027DC65Check(&position.x);break;}
   case 32: {Object*unit=((ContextPlayers*)ThePlayerList)->getLocalPlayer()->findNaturalCommandCenter();if(unit)currentlyValid=TheInGameUI->canSelectedObjectsDoSpecialPower(command,obj,pos,InGameUI::CONTEXT_ANY,contextButton(command)->getOptions(),unit);else currentlyValid=false;break;}
   case 38: {Object*unit=((ContextPlayers*)ThePlayerList)->getLocalPlayer()->rva002AC629();if(unit)currentlyValid=TheInGameUI->canSelectedObjectsDoSpecialPower(command,obj,pos,InGameUI::CONTEXT_ANY,contextButton(command)->getOptions(),unit);else currentlyValid=false;break;}
   case 41:currentlyValid=TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)19,obj,InGameUI::CONTEXT_ANY,false);break;
   case 47:currentlyValid=TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)20,obj,InGameUI::CONTEXT_ANY,false);break;
   }
   if(currentlyValid) {
    if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE) {
     switch(contextButton(command)->type) {
     case 29:case 30:msgType=((Rva00429007*)this)->rva00429007((Arg*)draw,type);break;
     case 41:msgType=((Rva00429093*)this)->rva00429093((Arg*)draw,type);break;
     case 47:msgType=((Rva00429112*)this)->rva00429112((Arg*)draw,type);break;
     case 24:msgType=issueSpecialPowerCommand(command,type,originalDraw,pos,0);break;
     case 32:{Object*unit=((ContextPlayers*)ThePlayerList)->getLocalPlayer()->findNaturalCommandCenter();if(unit)msgType=issueSpecialPowerCommand(command,type,draw,pos,unit);break;}
     case 38:{Object*unit=((ContextPlayers*)ThePlayerList)->getLocalPlayer()->rva002AC629();if(unit)msgType=issueSpecialPowerCommand(command,type,draw,pos,unit);break;}
     case 11:msgType=rva00428EEB(command,type,draw,pos);break;
     case 23:msgType=issueFireWeaponCommand(command,type,draw,pos);break;
     case 26:msgType=issueCombatDropCommand(command,type,draw,pos);break;
     }
     if(type==CONTEXT_COMMAND)contextUI()->setCommand(0);
    } else {msgType=0xa4;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(objectID);}
   } else {msgType=0xa5;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(objectID);}
  }
  else if(TheInGameUI->rva0029CC19(originalObject)) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE) {
    msgType=0x412;
    if(type==CONTEXT_COMMAND) {
     const CommandButton*c=TheControlBar->findCommandButton(AsciiString("Command_SpecialAbilitySiegeDeploy"));
     if(c) {
      GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)msgType);
      m->appendIntegerArgument(((const ContextPower*)contextButton(c)->special->friend_getFinalOverride())->id);
      m->appendObjectIDArgument(originalObject->getID());m->appendIntegerArgument(contextButton(c)->options);m->appendObjectIDArgument(OBJECTID_NONE);m->appendLocationArgument(*originalObject->getPosition());
      Rva004D92FE info;info.m_drawTarget=((Thing*)originalObject)->getDrawable();info.m_specialPowerType=(int)contextButton(c)->special;info.m_position=*pos;
      pickAndPlayUnitVoiceResponse((const DrawableList*)contextUI()->selected(),(GameMessage::Type)msgType,(PickAndPlayInfo*)&info);
     }
    }
   } else {msgType=0xa7;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(originalObject->getID());}
  }
  else if(TheInGameUI->canSelectedObjectsOverrideSpecialPowerDestination(pos,InGameUI::CONTEXT_ANY,CONTEXT_POWER_NONE)) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE) {msgType=0x441;if(type==CONTEXT_COMMAND){GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)msgType);m->appendLocationArgument(*pos);m->appendIntegerArgument(0);m->appendObjectIDArgument(OBJECTID_NONE);}}
   else {msgType=0xbd;TheMessageStream->appendMessage((GameMessage::Type)msgType);}
  }
  else if(draw&&!contextUI()->getForceAttack()&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)7,obj,(InGameUI::SelectionRules)0,false)) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE) {msgType=1067;if(type==CONTEXT_COMMAND){GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)msgType);m->appendObjectIDArgument(obj->getID());Rva004D92FE info;info.m_drawTarget=draw;pickAndPlayUnitVoiceResponse((const DrawableList*)contextUI()->selected(),(GameMessage::Type)msgType,(PickAndPlayInfo*)&info);}}
   else {msgType=174;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID());}
  }
  else if(draw&&!contextUI()->getForceAttack()&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)3,obj,(InGameUI::SelectionRules)0,false)) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE) {msgType=1069;if(type==CONTEXT_COMMAND){GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)msgType);m->appendObjectIDArgument(obj->getID());Rva004D92FE info;info.m_drawTarget=draw;pickAndPlayUnitVoiceResponse((const DrawableList*)contextUI()->selected(),(GameMessage::Type)msgType,(PickAndPlayInfo*)&info);}}
   else {msgType=177;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID());}
  }
  else if(draw&&!contextUI()->getForceAttack()&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)4,obj,(InGameUI::SelectionRules)1,false)) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE) {msgType=1070;if(type==CONTEXT_COMMAND){GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)msgType);m->appendLocationArgument(*pos);Rva004D92FE info;info.m_position=*pos;pickAndPlayUnitVoiceResponse((const DrawableList*)contextUI()->selected(),(GameMessage::Type)msgType,(PickAndPlayInfo*)&info);}}
   else {msgType=178;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID());}
  }
  else if((draw||originalDraw)&&!contextUI()->getForceAttack()&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)8,originalObject?originalObject:obj,InGameUI::CONTEXT_ANY,true)) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE)msgType=((Rva00429007*)this)->rva00429007((Arg*)(originalDraw?originalDraw:draw),type);
   else {Object*target=originalObject?originalObject:obj;msgType=TheActionManager->rva0041CE06(target);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(target->getID());}
  }
  else if(originalDraw&&!contextUI()->getForceAttack()&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)6,originalObject,InGameUI::CONTEXT_ANY,false)) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE) {msgType=1066;if(type==CONTEXT_COMMAND){GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)msgType);m->appendObjectIDArgument(originalObject->getID());Rva004D92FE info;info.m_drawTarget=originalDraw;pickAndPlayUnitVoiceResponse((const DrawableList*)contextUI()->selected(),(GameMessage::Type)msgType,(PickAndPlayInfo*)&info);}}
   else {msgType=173;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(originalObject->getID());}
  }
  else if(draw&&!contextUI()->getForceAttack()&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)2,obj,InGameUI::CONTEXT_ANY,false)) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE) {msgType=1064;if(type==CONTEXT_COMMAND){GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)msgType);m->appendObjectIDArgument(obj->getID());Rva004D92FE info;info.m_drawTarget=draw;pickAndPlayUnitVoiceResponse((const DrawableList*)contextUI()->selected(),(GameMessage::Type)msgType,(PickAndPlayInfo*)&info);}}
   else {msgType=171;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID());}
  }
  else if(draw&&!contextUI()->getForceAttack()&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)5,obj,InGameUI::CONTEXT_ANY,false)) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE) {msgType=1065;if(type==CONTEXT_COMMAND){GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)msgType);m->appendObjectIDArgument(obj->getID());Rva004D92FE info;info.m_drawTarget=draw;pickAndPlayUnitVoiceResponse((const DrawableList*)contextUI()->selected(),(GameMessage::Type)msgType,(PickAndPlayInfo*)&info);}}
   else {msgType=172;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID());}
  }
  else if(draw&&draw->getObject()&&!contextUI()->getForceAttack()&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)10,draw->getObject(),InGameUI::CONTEXT_ANY,false)) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE)msgType=((Rva00429007*)this)->rva00429007((Arg*)draw,type);
   else {msgType=182;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(draw->getObject()->getID());}
  }
  else if(draw&&!contextUI()->getForceAttack()&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)11,obj,InGameUI::CONTEXT_ANY,false)) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE)msgType=((Rva00429007*)this)->rva00429007((Arg*)draw,type);
   else {msgType=184;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID());}
  }
  else if(draw&&!contextUI()->getForceAttack()&&canSelectionSalvage(obj)) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE){msgType=0x442;if(type==CONTEXT_COMMAND){GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)msgType);m->appendLocationArgument(*obj->getPosition());Rva004D92FE info;info.m_drawTarget=draw;pickAndPlayUnitVoiceResponse((const DrawableList*)contextUI()->selected(),(GameMessage::Type)msgType,(PickAndPlayInfo*)&info);}}
   else {msgType=0xbe;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendLocationArgument(*obj->getPosition());}
  }
  else if(draw&&!contextUI()->getForceAttack()&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)9,obj,InGameUI::CONTEXT_ANY,true)) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE)msgType=((Rva00429007*)this)->rva00429007((Arg*)draw,type);
   else {msgType=0xb0;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID());}
  }
  else if(draw&&(result=TheInGameUI->getCanSelectedObjectsAttack((InGameUI::ActionType)1,obj,InGameUI::CONTEXT_ANY,contextUI()->getForceAttack()))==3) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE)msgType=issueAttackCommand(draw,pos,type,0);
   else {msgType=0xa7;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID());}
  }
  else if(draw&&result==2) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE)msgType=issueAttackCommand(draw,pos,type,0);
   else {msgType=0xc0;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID());}
  }
  else if(draw&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)12,obj,InGameUI::CONTEXT_ANY,false)) {
   Object*selected=contextUI()->first()->getObject();
   CommandSet*set=(CommandSet*)((Rva0031D5F8*)TheControlBar)->rva0031D5F8(selected->rva00290E67());
   if(set)for(int i=0;i<32;++i) {
    const CommandButton*c=set->getCommandButton(i);
    if(c&&contextButton(c)->type==24) {
     int power=((const ContextPower*)contextButton(c)->special->friend_getFinalOverride())->type;
     if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE) {if(power==26||power==29){msgType=issueSpecialPowerCommand(c,type,draw,pos,0);break;}}
     else if(power==29){msgType=0xb9;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID());}
    }
   }
  }
  else if(draw&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)18,obj,InGameUI::CONTEXT_ANY,false)) {
   if(type==CONTEXT_COMMAND){const CommandButton*c=rva0042970A(51);if(c)msgType=issueSpecialPowerCommand(c,type,draw,pos,0);}
   else {
    msgType=0x7d6;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID());
    Object*selected=contextUI()->first()->getObject();void*power=((Rva0026F0F0*)TheUpgradeCenter)->rva0026F0F0((char*)selected+0x284);
    if(power)hintMessage->appendIntegerArgument(TheMouse->getCursorIndex(*(AsciiString*)((char*)power+0x74)));
    else hintMessage->appendIntegerArgument(1);
   }
  }
  else if(draw&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)17,obj,InGameUI::CONTEXT_ALL,false)) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE) {
    Object*selected=contextUI()->first()->getObject();CommandSet*set=(CommandSet*)((Rva0031D5F8*)TheControlBar)->rva0031D5F8(selected->rva00290E67());
    if(set)for(int i=0;i<32;++i){const CommandButton*c=set->getCommandButton(i);if(c&&contextButton(c)->type==24){int power=((const ContextPower*)contextButton(c)->special->friend_getFinalOverride())->type;if(power==39){msgType=issueSpecialPowerCommand(c,type,draw,pos,0);break;}}}
   } else {
    bool reachable=true;
    if(obj&&pos&&contextKind(obj,94)){Object*selected=contextUI()->first()->getObject();if(selected&&!((ContextAI*)TheAI)->getPathfinder()->QuickDoesPathExist(selected,selected->getPosition(),pos,0))reachable=false;}
    if(reachable){msgType=0x7d8;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);}else{msgType=0xbf;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);}
    hintMessage->appendObjectIDArgument(obj->getID());
   }
  }
  else if(draw&&contextUI()->selectedCount()==1&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)16,draw->getObject(),InGameUI::CONTEXT_ALL,false)) {
   if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE) {
    msgType=0x423;if(type==CONTEXT_COMMAND){GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)msgType);Object*target=!draw?0:draw->getObject();ObjectID id=!target?OBJECTID_NONE:target->getID();m->appendObjectIDArgument(id);Rva004D92FE info;if(target){info.m_drawTarget=((Thing*)target)->getDrawable();info.m_position=*target->getPosition();}pickAndPlayUnitVoiceResponse((const DrawableList*)contextUI()->selected(),(GameMessage::Type)msgType,(PickAndPlayInfo*)&info);}
   }else {msgType=0x7d7;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID());}
  }
  else if((pos&&!draw&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)14,0,InGameUI::CONTEXT_ALL,false))||(draw&&obj&&TheInGameUI->canSelectedObjectsDoAction((InGameUI::ActionType)14,obj,InGameUI::CONTEXT_ANY,false))) {
   msgType=0x413;
   if(type==CONTEXT_COMMAND) {
    const SelectedDrawableList*selected=contextUI()->selected();
    for(SelectedDrawableList::const_iterator it=selected->begin();it!=selected->end();++it){Drawable*d=*it;if(d&&d->getObject()){GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)msgType);m->appendObjectIDArgument(d->getObject()->getID());m->appendLocationArgument(*pos);bool queue=TheKeyboard->isShift()&&!draw;m->appendBooleanArgument(queue);m->appendObjectIDArgument(obj?obj->getID():OBJECTID_NONE);}}
   }else if(type==CONTEXT_HINT){msgType=0xbc;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendLocationArgument(*pos);}
  }
  else if(draw&&result==1&&(!originalObject||!contextKind(obj,60)||contextKind(obj,150))) {
   msgType=0xa8;hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendLocationArgument(*pos);
  }
  else if(type==CONTEXT_COMMAND||type==CONTEXT_EVALUATE) {
   if(obj&&contextKind(obj,104))msgType=issueMoveToLocationCommand(pos,0,type);else msgType=issueMoveToLocationCommand(pos,drawableInWay,type);
  }
  else {
   bool reachable=((Rva0029DE76*)TheInGameUI)->rva0029DE76(pos);
   bool active=selectedObject&&contextObject(selectedObject)->ai&&((ContextAIUpdate*)contextObject(selectedObject)->ai)->active();
   if(!(reachable||(selectedObject&&contextKind(selectedObject,134))||active))goto invalidHint; {
    if(contextUI()->waypoint)msgType=0xb5;
    else if(selectedObject&&contextKind(selectedObject,191)&&contextKind(selectedObject,217)&&contextObject(selectedObject)->container) {
     if(pos&&(((ContextAI*)TheAI)->getPathfinder()->IsWaterCell((int)pos,1)||ThePartitionManager->getShroudStatusForPlayer(((ContextPlayerIndex*)((ContextPlayers*)ThePlayerList)->getLocalPlayer())->getIndex(),pos)==2))msgType=0xb3;
     else if(pos&&((ContextContain*)contextObject(selectedObject)->container)->unload(0))msgType=0xb1;
     else goto invalidHint;
    }else msgType=0xb3;
   }goto appendHint; invalidHint: msgType=0xbf; appendHint:;
   hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendLocationArgument(*pos);
  }
 } else if(type==CONTEXT_HINT&&contextUI()->selectedCount()>0&&!TheInGameUI->areSelectedObjectsControllable()) {
  msgType=0xbf;GameMessage*m=TheMessageStream->appendMessage((GameMessage::Type)msgType);m->appendLocationArgument(*pos);
 }
 return (GameMessage::Type)msgType;
}
