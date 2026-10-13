// ?rva00244D56@GameLogic@@QAEXPAV?$vector@URva0024622FEntry@@V?$allocator@URva0024622FEntry@@@_STL@@@_STL@@PBW4KindOfType@@1_N@Z
// partial score=0.85618 date=2026-10-13
// Native244D56..24555A 2052B; WorldBuilder D00E20 names loadAllObjects.
// Scoped draft from GameLogicInit.cpp: 2045B/frame108; remaining scalar homes,
// final x87 sine lifetime, and unresolved tree-clear calls are in re_attempts.log.
// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /ICode/GameEngine/Source/GameLogic/System
// stlport
// Scoped loadAllObjects bank from the verified current owner; other GameLogic bodies omitted.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
return a < b ? b : a;
}
}
#include <list>
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
#include <map>
#include <set>
#include <string>
#include <vector>
#include <math.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Libraries/Source/profile/profile.h"
#include <new>
#include <cstddef>
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}
namespace _STL { void *__copy_trivial(const void *__first, const void *__last, void *__result) throw(); }
typedef _STL::list<int, _STL::allocator<int> > IntList;
struct ObjectTOCEntry
{
AsciiString name;
unsigned short id;
};
template <class T> class Rva00245F79Allocator : public _STL::allocator<T>
{
};
typedef _STL::list<ObjectTOCEntry, Rva00245F79Allocator<ObjectTOCEntry> > ObjectTOCList;
namespace _STL
{
template<> void _List_base<ObjectTOCEntry, Rva00245F79Allocator<ObjectTOCEntry> >::clear();
}
struct Region3D
{
Coord3D lo;
Coord3D hi;
};
void setFPMode(void);
class SubsystemInterface
{
public:
virtual ~SubsystemInterface(void);
virtual void init(void) = 0;
virtual void s02(void); virtual void s03(void); virtual void s04(void);
virtual void s05(void); virtual void s06(void); virtual void s07(void);
virtual void s08(void);
virtual void reset(void);
virtual void update(void);
void setName(AsciiString name);
private:
int m_04;
AsciiString m_name;
};
class PartitionManager : public SubsystemInterface
{
public:
virtual void update(void);
void setRegion(const Region3D *extent, float cellSize);
void rva00625310(int value);
void rva00625300(const Region3D *extent);
void revealMapForPlayerPermanently(int playerIndex);
private:
int m_impl[2];
};
class Rva006253F0 : public PartitionManager
{
public:
Rva006253F0(void);
virtual void init(void);
};
class Open2Store8F75D0 : public PartitionManager
{
public:
Open2Store8F75D0(void);
virtual void init(void);
};
class Rva00739720
{
public:
void rva00739720(int value);
};
class CollisionManager : public SubsystemInterface
{
public:
CollisionManager(void);
virtual void init(void);
private:
int m_impl[2];
};
class Rva00758210
{
public:
void rva00758210(void);
};
class Rva006C0810
{
public:
void rva006C0810(const Region3D *extent, float cellSize);
};
class Object;
class ThingTemplate;
class Matrix3D;
enum PathfindLayerEnum
{
LAYER_INVALID = 0,
LAYER_GROUND = 1
};
class Rva00240000;
class TerrainLogic : public Snapshot, public SubsystemInterface
{
public:
virtual bool loadMap(const AsciiString &filename, Rva00240000 *stream, bool query,
bool newGame);
virtual void newMap(bool loadingSaveGame);
virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const;
virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer,
Coord3D *normal = 0, bool clip = true) const;
virtual void getExtent(Region3D *extent) const;
void rva002817F2(const AsciiString &filename);
PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
void rva00283642(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
void rva00280176(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
void rva0027D3D9(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
};
class BuffLogic : public Snapshot, public SubsystemInterface
{
};
class GhostObjectManager
{
public:
virtual ~GhostObjectManager(void);
virtual void g01(void); virtual void g02(void); virtual void g03(void);
virtual void reset(void);
virtual void setLocalPlayerIndex(int playerIndex);
};
class Pathfinder
{
public:
void rva002E8DAA(void);
void rva002F0F07(void);
void AddObjectToPathfindMap(Object *obj);
};
class AIData
{
char m_pad00[0xd8];
public:
bool m_d8;
AsciiString m_treeName[3];
float m_treeScale;
bool m_ec;
};
class AI : public SubsystemInterface
{
public:
Pathfinder *pathfinder(void) { return m_pathfinder; }
const AIData *getAiData(void) const { return m_aiData; }
private:
int m_0c;
Pathfinder *m_pathfinder;
char m_pad14[0x18 - 0x14];
AIData *m_aiData;
};
class AssetList;
struct AssetLoadMode;
void Rva00203BB1ForceAppContinue(void);
class ScriptEngine : public SubsystemInterface
{
public:
void rva00205358(AssetList *assets, AssetLoadMode *mode);
void rva00207C02(void);
void rva002047CF(void);
void forceAppContinue(void)
{
union
{
void (*entry)(void);
void (ScriptEngine::*method)(void);
} fn;
fn.entry = &Rva00203BB1ForceAppContinue;
(this->*fn.method)();
}
};
class Rva00203B08
{
public:
bool rva00203AE5(void);
};
class Overridable
{
public:
Overridable *deleteOverrides(void);
};
struct Rva00200BD9Holder;
class StatsCollector;
class Rva0048BA39StatsCollector
{
public:
~Rva0048BA39StatsCollector(void);
};
class Rva000427195
{
public:
void rva003A2A41(void);
};
class Rva00240CAB
{
public:
void rva0024191A(void);
};
class Rva001DBCDCTarget
{
public:
void rva001DBCDC(void);
};
class Rva0053F1ECSub
{
public:
void note(int buckets);
};
class Rva0023E7D9
{
public:
void rva0023E7D9(void);
void rva0023F88C(bool loadingSaveGame);
};
class Rva0035A1D8
{
public:
void rva0035A1D8(void);
};
class DOTManager
{
public:
void rva0043B725(void);
void update(void);
};
class Rva00439920
{
public:
void rva00439920(void);
};
class LargeGroupAudio : public SubsystemInterface
{
public:
LargeGroupAudio(void);
virtual void init(void);
private:
int m_body[13];
};
class Rva0035A2DC
{
public:
void rva0035A2DC(Region3D *extent, float cellSize);
};
class Rva00359E13
{
public:
Rva00359E13(void);
void rva0035AA3E(void);
private:
int m_body[17];
};
class Rva0043B660
{
public:
Rva0043B660(void);
void rva000B3FD0(void);
private:
int m_body[4];
};
class Rva0043821C
{
public:
void rva0043821C(void);
};
class Rva00243177
{
public:
Rva00243177(void);
void rva00439965(void);
private:
int m_body[6];
};
class Dict;
struct TeamsInfoNode
{
short m_previous;
short m_next;
short m_chainNext;
short m_chainPrevious;
int m_entry;
int m_extra;
};
class TeamsInfoRec
{
public:
void removeTeam(int index);
TeamsInfoNode *getNode(int index) { return &m_nodes[index]; }
int addTeam(const Dict *d);
private:
_STL::map<_STL::pair<AsciiString,AsciiString>,int> m_tree;
_STL::vector<TeamsInfoNode> m_nodes;
short m_count;short m_freeHead;
};
class Dict
{
public:
Dict(int numPairs = 0);
~Dict() { releaseData(); }
bool getBool(int key, bool *exists = 0) const;
float getReal(int key, bool *exists = 0) const;
AsciiString getAsciiString(int key, bool *exists = 0) const;
void setInt(int key, int value);
void setBool(int key, bool value);
void setAsciiString(int key, const AsciiString &value);
void setUnicodeString(int key, const UnicodeString &value);
void clear(void);
private:
void releaseData(void);
void *m_data;
};
class SidesInfo
{
public:
Dict *getDict(void) { return &m_dict; }
void *m_pBuildList;
Dict m_dict;
char m_pad08[0x60 - 8];
};
class SidesList
{
public:
void rva0032D554(void);
void rva0032F84F(void);
void rva0032C991(void);
void rva0032FF91(void);
void rva0032FD8E(void);
TeamsInfoRec *getTeamInfo(void) { return &m_teams; }
int addSide(const Dict *d);
SidesInfo *findSideInfo(AsciiString name, int *index = 0);
void addTeam(const Dict *d) { m_teams.addTeam(d); }
void rva0032E02B(void);
int getNumSides(void) const { return m_numSides; }
__declspec(noinline) SidesInfo *getSideInfo(int side)
{
if (side >= 0 && side < m_numSides)
return &m_sides[side];
return 0;
}
char m_pad000[0x3c];
int m_numSides;
SidesInfo m_sides[(0xf44 - 0x40) / 0x60];
char m_padSides[(0xf44 - 0x40) % 0x60];
TeamsInfoRec m_teams;
char m_padF60[0xf7c - 0xf60];
bool m_f7c;
};
class GlobalData
{
public:
char m_pad000[0xc];
AsciiString m_mapName;
char m_pad010[0x26 - 0x10];
bool m_26;
char m_pad027[0xd4 - 0x27];
float m_d4;
float m_d8;
char m_pad0DC[0x9c1 - 0xdc];
bool m_9c1;
char m_pad9C2[0xaf5 - 0x9c2];
bool m_af5;
char m_padAF6[0xbd0 - 0xaf6];
int m_bd0;
char m_padBD4[0xc18 - 0xbd4];
unsigned int m_c18;
char m_padC1C[0xc30 - 0xc1c];
int m_c30;
char m_padC34[0xd45 - 0xc34];
bool m_d45;
char m_padD46[0xd48 - 0xd46];
int m_d48;
char m_padD4C[0xddc - 0xd4c];
bool m_ddc;
char m_padDDD[0xe94 - 0xddd];
int m_e94;
char m_padE98[0x1110 - 0xe98];
bool m_1110;
char m_pad1111[0x123d - 0x1111];
bool m_123d;
};
class GameInfo;
class LoadScreen;
class Object;
class MapObject;
struct Rva0024622FEntry
{
Object *obj;
MapObject *mapObj;
};
class GameMessage;
class BfmeThingEC;
struct Rva00241529Record;
struct PlayerLeaveStatus;
class PlayerTemplate;
enum KindOfType
{
KINDOF_INVALID = -1
};
class UpdateModule;
typedef _STL::vector<UpdateModule *> UpdateModuleList;
class Rva0040CA98
{
public:
void rva0040CA98(void);
private:
char m_body[0x2c];
};
enum ObjectID
{
INVALID_ID = 0
};
class GameLogic : public SubsystemInterface
{
public:
virtual void init(void);
virtual void v11(void); virtual void v12(void);
virtual void update(int phase);
virtual TerrainLogic *createTerrainLogic(void);
virtual GhostObjectManager *createGhostObjectManager(void);
virtual BuffLogic *createBuffLogic(void);
virtual void reset(void);
void rva00240E18(bool loadingSaveGame);
void rva0023D17D(void);
void destroyAllObjectsImmediate(void);
void rva00376D49(void);
void rva00246422(bool dontCreate);
void rva00248558(bool loadingSaveGame);
void startNewGame_Init(bool loadingSaveGame);
void rva002469A5(bool loadingSaveGame, int *progress);
void startNewGame_PlaceMPBuildings(bool loadingSaveGame, int *progress);
void rva00248278(bool loadingSaveGame);
void rva0023F52C(bool loadingSaveGame);
void rva0024004D(bool loadingSaveGame);
void loadMapINI(AsciiString mapName);
void rva0023E628(AsciiString mapName);
void CreateMPPlayers(bool isSkirmish, int progress);
void CreateWOTRMPPlayers();
void SetUpCampaignPlayers(void);
void rva0023E0C7(void);
void lastHeardFrom(int playerIndex);
bool rva001DCD1C(void);
void rva0024622F(bool loadingSaveGame);
void setWidth(float width) { m_width = width; }
void setHeight(float height) { m_height = height; }
bool rva0023C8DA(unsigned char loadingSaveGame);
Object *findObjectByID(ObjectID id);
void rva00244D56(_STL::vector<Rva0024622FEntry> *created, const KindOfType *excludeKind,
const KindOfType *requireKind, bool dontCreate);
void startNewGame_OpenLoadScreen(bool loadingSaveGame, GameInfo *game);
bool isInMultiplayerGame(void);
bool rva00085124(void);
void formatPlayerStartWaypointName(AsciiString *name);
void ProcessCRC(unsigned int crc, int player, unsigned int frame, GameMessage *message,
bool forced, BfmeThingEC *stream);
void rva0023F8DA(void);
const AsciiString &rva0023FB58(int index);
PlayerLeaveStatus *getPlayerLeaveStatus(int playerIndex);
void rva002401DD(BfmeThingEC *stream, unsigned int frame, int player);
bool rva002259F3(void);
bool rva0042219(void);
void processCommandList(void);
void processDestroyList(void);
void logicMessageDispatcher(GameMessage *msg, void *userData);
unsigned int getCRC(int mode);
void rva00240EBC(void);
Object *getFirstObject(void) const { return m_objList; }
ObjectTOCEntry *findTOCEntryByName(AsciiString name);
void addTOCEntry(AsciiString name, unsigned short id);
void xferObjectTOC(Xfer *xfer);
private:
LoadScreen *getLoadScreen(bool saveGame);
public:
char m_pad00C[0x10 - 0x0c];
char m_10[0x24 - 0x10];
char m_24[0x30 - 0x24];
float m_width;
float m_height;
unsigned int m_38;
char m_pad03C[0x40 - 0x3c];
unsigned int m_40;
unsigned int getFrame(void) const { return m_40; }
bool m_44;
char m_pad045[0x48 - 0x45];
Rva00241529Record *m_48;
IntList::iterator m_4c;
IntList m_50;
AsciiString m_54;
_STL::vector<AsciiString> m_58;
AsciiString m_64;
AsciiString m_68;
bool m_6c;
bool m_6d;
char m_pad06E[0x70 - 0x6e];
bool m_70;
bool m_71;
bool m_72;
char m_pad073[0x94 - 0x73];
int m_94;
bool m_98;
bool m_99;
bool m_9a;
bool m_9b;
bool m_9c;
bool m_9d;
bool m_9e;
bool m_9f;
int m_a0;
int m_a4;
bool m_a8;
char m_pad0A9[0xac - 0xa9];
Object *m_objList;
char m_pad0B0[0xb4 - 0xb0];
char m_b4[0xc8 - 0xb4];
UpdateModuleList m_updates[4];
UpdateModuleList m_sleeping;
UpdateModule *m_104;
char m_pad108[0x10c - 0x108];
int m_10c;
int m_110;
int m_114;
int m_118;
bool m_11c;
bool m_11d;
char m_pad11E[0x120 - 0x11e];
LoadScreen *m_120;
bool m_124;
bool m_125;
bool m_126;
bool m_127;
bool m_128[8];
int m_130[8];
bool m_150;
char m_pad151[0x154 - 0x151];
Object *m_154;
Object *m_158;
Object *m_15c;
Object *m_160;
_STL::vector<void *> m_164;
Rva00359E13 *m_170;
Rva0043B660 *m_174;
Rva00243177 *m_178;
int m_17c;
int m_180;
Rva0040CA98 m_184;
int m_1b0;
int m_1b4;
int m_1b8;
bool m_1bc;
char m_pad1BD[0x1c0 - 0x1bd];
ObjectTOCList m_objectTOC;
char m_pad1C4[0x2a4 - 0x1c4];
int m_2a4;
};
extern PartitionManager *ThePartitionManager;
extern PartitionManager *TheShroudManager;
class BfmeTaintManager;
extern BfmeTaintManager *TheTaintManager;
extern CollisionManager *TheCollisionManager;
extern GlobalData *TheWritableGlobalData;
extern GhostObjectManager *TheGhostObjectManager;
extern TerrainLogic *TheTerrainLogic;
LargeGroupAudio *TheLargeGroupAudio = 0;
BuffLogic *TheBuffLogic = 0;
extern SidesList *TheSidesList;
extern GameLogic *TheGameLogic;
extern AI *TheAI;
extern ScriptEngine *TheScriptEngine;
extern StatsCollector *g_00E032F8;
extern Rva00200BD9Holder *g_rva00200BD9Holder;
class Rva000421FD
{
public:
void rva000421FD(void);
};
class Rva0004224C
{
public:
Rva0004224C(void)
{
if (TheGameLogic)
((Rva000421FD *)TheGameLogic)->rva000421FD();
}
~Rva0004224C(void)
{
if (TheGameLogic)
TheGameLogic->m_1b4--;
}
};
#define GAMELOGIC_SOURCE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\GameLogic.cpp"
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
template <class T> class Rva0024485CAllocator : public _STL::allocator<T>
{
};
class WaypointMap : public _STL::map<AsciiString, Coord3D, _STL::less<AsciiString>, Rva0024485CAllocator<_STL::pair<const AsciiString, Coord3D> > >
{
public:
int m_numStartSpots;
};
struct MapStartPosition
{
char m_pad00[2];
bool m_2;
char m_pad03[8 - 3];
_STL::set<AsciiString> m_factions;
};
typedef char MapStartPositionSizeCheck[sizeof(MapStartPosition) == 0x14 ? 1 : -1];
class MapMetaData
{
public:
char m_pad00[0x20];
int m_numPlayers;
char m_pad24[0x38 - 0x24];
WaypointMap m_waypoints;
char m_padWaypoints[0x54 - 0x38 - sizeof(WaypointMap)];
MapStartPosition m_startPositions[8];
};
class MapCache
{
public:
const MapMetaData *findMap(AsciiString mapName);
};
struct GameSlotHeroInfo
{
char m_pad00[0x0c];
unsigned int m_classIndex;
unsigned int m_subClassIndex;
};
class GameSlot
{
public:
bool isOccupied() const;
bool isAI() const;
void saveOffOriginalInfo();
int getStartPos() const { return m_10; }
void setStartPos(int startPos) { m_10 = startPos; }
int getPlayerTemplate() const { return m_18; }
int getTeamNumber() const { return m_1c; }
int getColor() const { return m_c; }
void setColor(int color) { m_c = color; }
void setPlayerTemplate(int playerTemplate);
bool isHuman() const;
const unsigned short *getNameStr() const { return m_name.str(); }
const GameSlotHeroInfo *getHero() const { return m_hasHero ? &m_hero : 0; }
char m_pad00[0x4];
int m_state;
char m_pad08[0xc - 0x8];
int m_c;
int m_10;
int m_14;
int m_18;
int m_1c;
int m_bfme20;
char m_pad24[0x30 - 0x24];
UnicodeString m_name;
AsciiString m_34;
char m_pad38[0x4c - 0x38];
int m_livingWorldPlayerID;
char m_pad50[0x60 - 0x50];
bool m_hasHero;
GameSlotHeroInfo m_hero;
};
class GameInfo
{
public:
virtual ~GameInfo(void);
virtual void gi04(void); virtual void gi08(void); virtual void gi0C(void);
virtual void gi10(void); virtual void gi14(void); virtual void gi18(void);
virtual void gi1C(void); virtual void gi20(void); virtual void gi24(void);
virtual void gi28(void); virtual void gi2C(void); virtual void gi30(void);
virtual int getLocalSlotNum(void) const;
GameSlot *getSlot(int index);
bool isPlayerPreorder(int index);
const GameSlot *getConstSlot(int index) const;
AsciiString getMap() const;
bool isStartPositionTaken(int positionIdx, int slotToIgnore = -1) const;
bool isColorTaken(int colorIdx, int slotToIgnore = -1) const;
char m_pad04[0x0c - 4];
int m_0c;
char m_pad10[0x54 - 0x10];
int m_54;
};
extern MapCache *TheMapCache;
extern GameInfo *TheGameInfo;
static inline float sqr(float x)
{
return x * x;
}
class LoadScreen
{
public:
virtual ~LoadScreen(void);
virtual void v01(void);
virtual void init(GameInfo *game);
};
class Rva009EB960
{
public:
virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
virtual void v08(); virtual void v09();
virtual void slot28();
};
class GameWindowTransitionsHandler
{
public:
virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
virtual void v08();
virtual void slot24();
virtual void slot28();
void rva001DC5EC(void);
void reverse(AsciiString groupName);
};
class Rva0023C7D2
{
public:
void rva0023C7D2(void);
void rva0023C7BB(int value);
};
extern Rva009EB960 *Rva0134FAA0;
extern GameWindowTransitionsHandler *TheTransitionHandler;
void bfmeReleaseQueuedDeviceInterfaces(void);
void populateRandomSideAndColor(GameInfo *game);
class Xfer;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Xfer
{
public:
class Version;
Xfer();
virtual ~Xfer();
void Version1();
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
class ThingTemplate
{
public:
const AsciiString &getName(void) const { return m_name; }
void GetAssetList(int a, int b);
int rva000456AC(int bit) const;
__forceinline bool isKindOf(KindOfType t) const
{
unsigned int mask = 1u << (t & 31);
return (m_kindof[t >> 5] & mask) != 0;
}
private:
char m_pad00[0x64];
AsciiString m_name;
char m_pad68[0x108 - 0x68];
public:
unsigned int m_108;
unsigned int m_kindof[4];
unsigned int m_11c;
unsigned int m_120;
char m_pad124[0x4a0 - 0x124];
float m_fenceWidth;
char m_pad4A4[0x4e0 - 0x4a4];
float m_4e0;
char m_pad4E4[0x5e5 - 0x4e4];
bool m_5e5;
char m_pad5E6[0x5eb - 0x5e6];
bool m_5eb;
bool m_5ec;
};
class Dict;
class Drawable;
class Thing
{
public:
Drawable *getDrawable(void) const;
void setTransformMatrix(const Matrix3D *mtx);
void setOrientation(float angle);
void setPosition(const Coord3D *pos);
};
template <int NUM_BITS>
class BitFlags
{
public:
BitFlags(const BitFlags &src);
bool any(void) const;
bool test(const void *other) const;
__declspec(dllimport) __forceinline bool anyIntersectionWith(const BitFlags &that) const { return that.test(this); }
private:
unsigned int m_bits[(NUM_BITS + 31) / 32];
};
typedef BitFlags<11> DisabledMaskType;
enum ObjectStatusTypes
{
OBJECT_STATUS_NONE
};
class AIUpdateInterface
{
public:
bool isMoving(void) const;
void destroyPath(void);
};
class Object : public Thing
{
public:
const ThingTemplate *getTemplate(void) const { return m_template; }
Object *getNextObject(void) const { return m_next; }
void updateObjValuesFromMapProperties(Dict *properties);
void rva0028B4CE(PathfindLayerEnum layer);
void rva00293E64(Dict *properties);
bool testStatus(ObjectStatusTypes bit) const;
bool isDisabled(void) const { return m_disabledMask.any(); }
const DisabledMaskType &getDisabledFlags(void) const { return m_disabledMask; }
AIUpdateInterface *getAIUpdateInterface(void) const { return m_ai; }
void rva0023D3AF(void *frame);
void rva00290357(void);
void rva002903C3(void);
void rva002903EF(void);
void rva00297612(void);
private:
void *m_vtbl;
const ThingTemplate *m_template;
char m_pad08[0x8c - 0x08];
Object *m_next;
char m_pad090[0x94 - 0x90];
public:
unsigned int m_94;
char m_pad098[0x188 - 0x98];
unsigned int m_188;
char m_pad18C[0x1c8 - 0x18c];
private:
DisabledMaskType m_disabledMask;
char m_pad1CC[0x258 - 0x1cc];
AIUpdateInterface *m_ai;
};
struct Rva001408C0Target;
typedef _STL::set<Rva001408C0Target *, _STL::less<Rva001408C0Target *>,
_STL::allocator<Rva001408C0Target *> > Rva001408C0Set;
class AssetList
{
public:
AssetList() : m_treeLayoutPad(0), m_changed(true) {}
void clear(void) { m_prototypes.clear(); m_changed = true; }
private:
Rva001408C0Set m_prototypes;
unsigned int m_treeLayoutPad;
bool m_changed;
};
struct AssetLoadMode
{
bool m_alternate;
AssetLoadMode() : m_alternate(false) {}
};
void bfmeMergeReceiverKeys(int value);
class MapObject
{
public:
MapObject *getNext(void) const { return m_next; }
const Coord3D *getLocation(void);
float getAngle(void) const { return m_angle; }
int getFlags(void) const { return m_flags; }
Dict *getProperties(void) { return &m_properties; }
const ThingTemplate *getThingTemplate(void) const;
private:
void *m_vtbl;
MapObject *m_next;
Coord3D m_location;
AsciiString m_objectName;
const ThingTemplate *m_thingTemplate;
float m_angle;
int m_flags;
Dict m_properties;
};
class BfmeMapObjectListHolder
{
public:
MapObject *m_head;
};
extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;
BfmeMapObjectListHolder *BfmeTheMapObjectListHolder = 0;
struct CreateMask
{
CreateMask() { memset(m_bits, 0, sizeof(m_bits)); }
unsigned int m_bits[4];
};
class Team;
class Rva003805BB
{
public:
bool rva003805BB(float value, bool flag);
void rva002E6A93(int value);
char m_pad00[0x14];
int m_14;
int m_18;
};
enum PlayerType
{
PLAYER_HUMAN
};
class Player
{
public:
Team *getDefaultTeam(void) const { return m_defaultTeam; }
PlayerType getPlayerType(void) const { return m_playerType; }
int getPlayerIndex(void) const { return m_playerIndex; }
int iterateObjects(int (*func)(Object *obj, void *userData), void *userData) const;
char m_pad00[0x8];
Rva003805BB m_skillPoints;
char m_pad24[0x34 - 0x24];
PlayerTemplate *m_34;
char m_pad38[0x4c - 0x38];
AsciiString m_4c;
char m_pad50[0x54 - 0x50];
int m_playerIndex;
char m_pad58[0x5c - 0x58];
PlayerType m_playerType;
char m_pad60[0x2ec - 0x60];
Team *m_defaultTeam;
char m_pad2F0[0x3bc - 0x2f0];
int m_3bc;
char m_pad3C0[0x4ac - 0x3c0];
int m_4ac;
};
enum NameKeyType
{
NAMEKEY_INVALID
};
class PlayerList : public SubsystemInterface
{
public:
virtual void p0b(void); virtual void p0c(void);
virtual void p0d(void); virtual void p0e(void);
virtual void newMap(void);
Player *getNeutralPlayer(void) const { return m_neutralPlayer; }
Player *getLocalPlayer(void) const { return m_local; }
Player *getNthPlayer(int index);
Player *findPlayerWithNameKey(NameKeyType key);
void setLocalPlayer(Player *player);
Team *validateTeam(AsciiString owner, MapObject *mapObj);
private:
char m_pad0C[0x10 - 0x0c];
Player *m_local;
char m_pad14[0x18 - 0x14];
Player *m_neutralPlayer;
};
class ThingFactory
{
public:
Object *rva002D0A23(const ThingTemplate *tt, Team *team, const CreateMask &mask, ObjectID id);
const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;
extern PlayerList *ThePlayerList;
static __forceinline void rotatePair(float &x, float &y, float s, float c)
{
float x0 = x, y0 = y;
x = c*x0 + s*y0;
y = c*y0 - s*x0;
}
class Matrix3D
{
public:
__forceinline Matrix3D(void) {}
__declspec(dllimport) __forceinline explicit Matrix3D(bool init)
{
if (init) {
m_row[0][0] = 1.0f; m_row[0][1] = 0.0f; m_row[0][2] = 0.0f; m_row[0][3] = 0.0f;
m_row[1][0] = 0.0f; m_row[1][1] = 1.0f; m_row[1][2] = 0.0f; m_row[1][3] = 0.0f;
m_row[2][0] = 0.0f; m_row[2][1] = 0.0f; m_row[2][2] = 1.0f; m_row[2][3] = 0.0f;
}
}
__forceinline void Rotate_Z(float theta)
{
float tmp1, tmp2;
float c;float sine[1];float&s=sine[0];
c = (float)cos(theta);
s = (float)sin(theta);
rotatePair(m_row[0][0],m_row[0][1],s,c);
rotatePair(m_row[1][0],m_row[1][1],s,c);
rotatePair(m_row[2][0],m_row[2][1],s,c);
}
private:
float m_row[3][4];
};
class Rva00271058
{
public:
void rva00271058(void *p);
};
static __forceinline const KindOfType *kindRef(const KindOfType &kind) { return &kind; }
extern void *ApplicationHWnd;
extern "C" __declspec(dllimport) void *__stdcall GetSystemMenu(void *wnd, int revert);
extern "C" __declspec(dllimport) int __stdcall EnableMenuItem(void *menu, unsigned id, unsigned flags);
extern "C" char *(__cdecl * const _imp__strrchr)(const char *text, int ch);
class Rva0023C83B
{
public:
Rva0023C83B(void)
{
EnableMenuItem(GetSystemMenu(ApplicationHWnd, 0), 0xF060, 1);
}
~Rva0023C83B(void) throw()
{
EnableMenuItem(GetSystemMenu(ApplicationHWnd, 0), 0xF060, 0);
}
};
class AudioManager
{
public:
virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
virtual void v38(); virtual void v39(); virtual void v3a(); virtual void v3b();
virtual void v3c(); virtual void v3d(); virtual void v3e(); virtual void v3f();
virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
virtual void v48(); virtual void v49(); virtual void v4a(); virtual void v4b();
virtual void v4c(); virtual void v4d(); virtual void v4e(); virtual void v4f();
virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57();
virtual void v58(); virtual void v59(); virtual void v5a(); virtual void v5b();
virtual void v5c(); virtual void v5d(); virtual void v5e(); virtual void v5f();
virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
virtual void slot190(void);
};
class BfmeDfe6e4
{
public:
void _M_rva00625699(void);
};
class Rva0023D46F
{
public:
Rva0023D46F(BfmeDfe6e4 *counter);
~Rva0023D46F(void)
{
if (m_counter)
m_counter->_M_rva00625699();
}
private:
BfmeDfe6e4 *m_counter;
};
class Rva00248558Scope
{
public:
Rva00248558Scope(void);
~Rva00248558Scope(void);
};
class Rva0023D6D5
{
public:
void rva0023D6D5(bool loadingSaveGame);
};
class Rva0021A54A;
class Rva0021B3FA
{
public:
void rva0021B3FA(void);
};
class GameLODManager
{
public:
int getStaticLODLevel(void) const { return m_staticLODLevel; }
int get1774(void) const { return m_1774; }
private:
char m_pad0000[0x1768];
int m_staticLODLevel;
char m_pad176C[0x1774 - 0x176c];
int m_1774;
};
void bfmeClearReceiverFlag(int value);
extern AudioManager *TheAudio;
extern BfmeDfe6e4 *theBfmeDfe6e4;
extern class CreateAHeroManager *TheCreateAHeroManager;
#define TheHeroManager (*(Rva0021A54A * *)&TheCreateAHeroManager)
extern GameLODManager *TheGameLODManager;
extern int SavedClientFrame;
extern unsigned char g_00DFF004;
extern char g_00E09B08[];
extern int g_00E09A00;
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);
class ParticleSystemManager
{
public:
virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
virtual void v10(); virtual void v11(); virtual void v12();
virtual void preloadAssets(void);
};
class ControlBar
{
public:
void rva0031D64F(void);
void rva0031AD48(bool flag);
void setControlBarSchemeByPlayer(Player *player);
void rva0031BAC3(Player *player);
char m_pad000[0x210];
Player *m_210;
};
class G00DFF080Obj
{
public:
virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
virtual void v04();
virtual void slot14(void);
};
class View
{
public:
virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
virtual void v14(); virtual void v15();
virtual void initHeightForMap(void);
virtual void v17(); virtual void v18(); virtual void v19(); virtual void v1a();
virtual void v1b(); virtual void v1c(); virtual void v1d();
virtual bool slot78(void);
virtual void v1f(); virtual void v20(); virtual void v21(); virtual void v22();
virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
virtual void v27(); virtual void v28(); virtual void v29(); virtual void v2a();
virtual void v2b(); virtual void v2c(); virtual void v2d(); virtual void v2e();
virtual void v2f(); virtual void v30(); virtual void v31();
virtual void lookAtPosition(const Coord3D *pos, int frames, float easeIn, float easeOut);
virtual void v33(); virtual void v34(); virtual void v35();
virtual bool slotD8(void);
virtual void v37(); virtual void v38(); virtual void v39(); virtual void v3a();
virtual void v3b(); virtual void v3c(); virtual void v3d(); virtual void v3e();
virtual void v3f(); virtual void v40(); virtual void v41(); virtual void v42();
virtual void v43(); virtual void v44();
virtual void setAngleAndPitchToDefault(void);
virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
virtual void v4a(); virtual void v4b(); virtual void v4c(); virtual void v4d();
virtual void v4e();
virtual void setZoomToDefault(void);
virtual void v50();
virtual void setOkToAdjustHeight(bool ok);
virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
virtual void v5a(); virtual void v5b(); virtual void v5c(); virtual void v5d();
virtual void v5e(); virtual void v5f(); virtual void v60(); virtual void v61();
virtual void v62(); virtual void v63(); virtual void v64(); virtual void v65();
virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69();
virtual void v6a(); virtual void v6b(); virtual void v6c(); virtual void v6d();
virtual void v6e(); virtual void v6f(); virtual void v70(); virtual void v71();
virtual void v72();
virtual bool v73(void);
virtual void v74(void *a, int b, int c, bool d);
};
class File;
enum RecorderModeType
{
RECORDERMODETYPE_RECORD,
RECORDERMODETYPE_PLAYBACK,
RECORDERMODETYPE_NONE
};
class RecorderClass : public SubsystemInterface
{
public:
bool isMultiplayer(void);
RecorderModeType getMode(void);
void logCRCMismatch(void);
void rva0037BE15(File *output, unsigned int frame);
void initControls(void);
char m_pad00C[0xe68 - 0xc];
int m_e68;
int m_e6c;
};
class InGameUI
{
friend class GameLogic;
public:
void setClientQuiet(bool quiet) { m_clientQuiet = quiet; }
private:
char m_pad000[0x8c5];
bool m_clientQuiet;
};
class StaticNameKey
{
public:
mutable int m_key;
const char *m_name;
};
class Rva00148F5ECache
{
public:
NameKeyType get(void);
};
static __forceinline NameKeyType staticKey(const StaticNameKey &key)
{
return ((Rva00148F5ECache *)&key)->get();
}
class NameKeyGenerator
{
public:
const AsciiString &keyToName(NameKeyType key);
NameKeyType nameToKey(const AsciiString &name);
NameKeyType nameToKey(const char *name);
};
class Waypoint
{
public:
const Coord3D *getLocation(void) const { return &m_location; }
private:
char m_pad00[0xc];
Coord3D m_location;
};
Waypoint *Rva00506CC3FindWaypoint(const AsciiString &name);
class Rva00E02F3CObj
{
public:
virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
virtual void v0c(); virtual void v0d();
virtual void slot38(void);
};
class Rva002A8F24 : public SubsystemInterface
{
public:
void rva002A95F9(void);
};
class TeamFactory : public SubsystemInterface
{
public:
virtual void tf0b(); virtual void tf0c(); virtual void tf0d(); virtual void tf0e(); virtual void tf0f(); virtual void tf10(); virtual void tf11();
void rva003A262C(void);
};
class Rva0023C666
{
public:
bool rva0023C666(void);
};
class BfmeGlob939D
{
public:
char bfmeCall939D(void);
};
class NetworkInterface
{
public:
virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
virtual void v0c(); virtual void v0d(); virtual void v0e();
virtual void slot3C(int arg);
virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
virtual void slot90(void);
virtual void slot94(void);
virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
virtual void v2a();
virtual bool slotAC(void);
virtual void v2c();
virtual int slotB4(void);
};
extern ParticleSystemManager *TheParticleSystemManager;
extern ControlBar *TheControlBar;
extern G00DFF080Obj *g_00DFF080;
extern View *TheTacticalView;
extern RecorderClass *TheRecorder;
extern NameKeyGenerator *TheNameKeyGenerator;
extern const StaticNameKey TheKey_InitialCameraPosition;
class VictorySystem;
extern VictorySystem *TheVictorySystem;
extern Rva002A8F24 *g_00DFEEF8;
extern TeamFactory *TheTeamFactory;
extern NetworkInterface *TheNetwork;
void rva0043D467(void);
class GameWindowManager : public SubsystemInterface
{
};
class Mouse
{
public:
void _bfme_setEngineVisibility(bool visible);
};
class GameState;
class Rva001EB298
{
public:
void rva001EB298(AsciiString mapName);
};
class Rva002DC7C1
{
public:
bool rva002DC7C1(const UnicodeString &path) const;
};
class MultiplayerSettings
{
public:
int getNumColors()
{
if (m_numColors == 0)
m_numColors = m_colorCount;
return m_numColors;
}
bool isShroudInMultiplayer() const { return m_shroudInMultiplayer; }
class MultiplayerColorDefinition *getColor(int which);
private:
char m_pad00[0x1c];
bool m_shroudInMultiplayer;
char m_pad1D[0x38 - 0x1d];
int m_colorCount;
int m_3c;
int m_numColors;
};
extern GameWindowManager *TheWindowManager;
extern Mouse *TheMouse;
extern GameState *TheGameState;
extern MultiplayerSettings *TheMultiplayerSettings;
class PlayerTemplate;
class PlayerTemplateBody
{
char m_bytes[0x1dc];
};
class PlayerTemplateStore
{
public:
int getPlayerTemplateCount() { return m_finish - m_start; }
const PlayerTemplate *getNthPlayerTemplate(int index) const;
const PlayerTemplate *findPlayerTemplate(NameKeyType key) const;
private:
char m_pad00[0x0c];
PlayerTemplateBody *m_start;
PlayerTemplateBody *m_finish;
};
extern PlayerTemplateStore *ThePlayerTemplateStore;
void rva00241C75(int slotNum, const GameSlot *slot, Player *player, const PlayerTemplate *pt);
static inline void zeroCoord(Coord3D *c)
{
c->x = 0.0f;
c->y = 0.0f;
c->z = 0.0f;
}
static inline void addCoord(Coord3D *dst, const Coord3D *src)
{
dst->x += src->x;
dst->y += src->y;
dst->z += src->z;
}
class WindowLayout
{
public:
virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
virtual void hide(bool hide);
virtual void bringForward(void);
};
class Shell
{
public:
void push(AsciiString filename, bool shutdownImmediate = false);
WindowLayout *top(void);
int getScreenCount(void) const { return m_screenCount; }
private:
char m_pad00[0x4c];
int m_screenCount;
};
class StatsCollector
{
public:
StatsCollector(void);
void rva00437DF8(void);
private:
char m_pad00[0x68];
};
class File
{
public:
enum seekMode
{
START,
CURRENT,
END
};
virtual ~File(void);
virtual bool open(const char *filename, int access);
virtual void close(void);
virtual int read(void *buffer, int bytes);
virtual int write(const void *buffer, int bytes);
virtual int seek(int bytes, seekMode mode);
};
class Radar
{
public:
virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03();
virtual void refreshTerrain(TerrainLogic *terrain);
virtual void r05();
virtual void newMap(TerrainLogic *terrain);
void forceOn(bool force) { m_11 = force; }
private:
char m_pad04[0x11 - 4];
bool m_11;
};
class Rva007397D0
{
public:
void rva007397D0(void);
};
class Rva006C0820
{
public:
void rva006C0820(void);
};
class Rva0023D494
{
public:
void rva0023D494(void);
};
class BfmeMemberRV
{
public:
bool bfmeAskRV(void);
};
class RadarWindowOverrideSource
{
public:
void rva002D55EF(void);
};
class Rva0022C4DF
{
public:
UnicodeString rva0022C4DF(void) const;
};
class GameSpyStagingRoom;
class Drawable
{
public:
void rva00278C6B(void);
Drawable *getNextDrawable(void) const { return m_next; }
void setDrawableStatus(unsigned int bits) { m_status |= bits; }
private:
char m_pad000[0x104];
Drawable *m_next;
char m_pad108[0x114 - 0x108];
unsigned int m_status;
};
class ClientFrameSubsystem
{
public:
virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
virtual void v20(); virtual void v21(); virtual void v22();
virtual Drawable *getDrawableList(void);
char m_pad004[0xc8 - 4];
bool m_c8;
void rva0023B383(Dict *properties, const ThingTemplate *tt, const Coord3D *pos);
};
enum GameSpyBuddyStatus
{
GAMESPY_BUDDY_STATUS_5 = 5
};
extern Shell *TheShell;
extern Radar *TheRadar;
extern unsigned int g_Va00DFE7A8;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
extern GameSpyStagingRoom *TheGameSpyGame;
extern class GameClient *TheGameClient;
#define TheGameClient (*(ClientFrameSubsystem * *)&TheGameClient)
void HideControlBar(bool immediate);
void ShowControlBar(bool immediate);
int rva0023D6FA(Object *obj);
int rva0061F090(void);
_STL::string WideCharStringToMultiByte(const unsigned short *orig);
void updateBuddyStatus(GameSpyBuddyStatus status, int sleepTime, _STL::string mapName);
extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(void *module, const char *name);
typedef void (*NewMapProc)(void);
class LuaScriptEngine : public SubsystemInterface
{
public:
void rva003387DC(const AsciiString &mapName);
};
extern const void *const g_00C4EF80[];
class Rva0084EF80Base
{
public:
virtual void rva0084EF80_slot0() {}
virtual void rva0084EF80_slot1() {}
virtual void rva0084EF80_slot2() {}
virtual void rva0084EF80_slot3() {}
~Rva0084EF80Base()
{
*(const void **)this = g_00C4EF80;
}
};
struct Rva00240000Vector
{
void *m_start;
void *m_finish;
void *m_end;
~Rva00240000Vector()
{
if (m_start)
free(m_start);
}
};
class __declspec(novtable) Rva00240000 : public Rva0084EF80Base
{
public:
Rva00240000(void);
~Rva00240000(void);
bool rva00308050(AsciiString path);
private:
Rva00240000Vector m_04;
Rva0084EF80Base m_10;
int m_14;
int m_18;
int m_1c;
};
class Rva00355CD8
{
public:
Rva00355CD8(int lo, int hi);
virtual ~Rva00355CD8(void);
private:
int m_body[3];
};
class GameEngine
{
public:
virtual void e00(); virtual void e01(); virtual void e02(); virtual void e03();
virtual void e04(); virtual void e05(); virtual void e06(); virtual void e07();
virtual void e08(); virtual void e09(); virtual void e0a(); virtual void e0b();
virtual void e0c(); virtual void e0d(); virtual void e0e(); virtual void e0f();
virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13();
virtual void setQuitting(bool quitting);
virtual void e15();
virtual bool isMultiplayerSession(void);
};
class Rva00E03138 : public SubsystemInterface
{
public:
virtual void c0b(); virtual void c0c(); virtual void c0d();
virtual void c0e(); virtual void c0f(); virtual void c10();
virtual void slot44(void);
};
class Display
{
public:
virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
virtual void d08(); virtual void d09(); virtual void d0a(); virtual void d0b();
virtual void d0c(); virtual void d0d(); virtual void d0e(); virtual void d0f();
virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13();
virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
virtual void d18(); virtual void d19(); virtual void d1a(); virtual void d1b();
virtual void d1c(); virtual void d1d(); virtual void d1e(); virtual void d1f();
virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
virtual void d28(); virtual void d29(); virtual void d2a(); virtual void d2b();
virtual void d2c(); virtual void d2d(); virtual void d2e(); virtual void d2f();
virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33();
virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37();
virtual void d38(); virtual void d39(); virtual void d3a(); virtual void d3b();
virtual void d3c(); virtual void d3d(); virtual void d3e(); virtual void d3f();
virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
virtual void d48(); virtual void d49(); virtual void d4a(); virtual void d4b();
virtual void d4c(); virtual void d4d(); virtual void d4e(); virtual void d4f();
virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53();
virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57();
virtual void d58(); virtual void d59(); virtual void d5a(); virtual void d5b();
virtual void d5c(); virtual void d5d(); virtual void d5e(); virtual void d5f();
virtual void slot180(const Region3D *extent);
};
class Rva0023C6A4
{
public:
bool rva00200084(void);
};
class Rva0020DXXX
{
public:
void rva0020D7F9(void);
};
class Rva002872BA : public SubsystemInterface
{
public:
void rva00287015(void);
};
class Rva00739780
{
public:
void rva00739780(int playerIndex);
};
extern int g_00DFE158;
extern GameInfo *TheSkirmishGameInfo;
extern LuaScriptEngine *TheLuaScriptEngine;
extern GameEngine *TheGameEngine;
extern struct UnknownE03138 *g_00E03138;
#define g_00E03138 (*(Rva00E03138 * *)&g_00E03138)
extern InGameUI *TheInGameUI;
extern Display *TheDisplay;
extern Rva002872BA *TheTriggerManager;
void bfmeStepReceiverRecord(int source);
class Rva001DBB87ZeroSetter
{
public:
void disable(void);
};
class Rva001DBAA4
{
public:
void unlock(void);
};
class Rva0023C565
{
public:
Rva0023C565();
~Rva0023C565()
{
if (TheTransitionHandler)
((Rva001DBAA4 *)TheTransitionHandler)->unlock();
}
};
class Rva0023E323
{
public:
int rva0023E323(float, int);
private:
AsciiString m_groupName;
unsigned int m_frame;
};
class GameState
{
char m_pad00[0x2c];
public:
AsciiString m_pristineMapName;
};
class FileSystem
{
public:
File *openFile(const char *filename, int access, int bufferSize);
bool doesFileExist(const char *filename) const;
};
extern FileSystem *TheFileSystem;
class GameTextInterface
{
public:
virtual void g00(void) = 0;
virtual void g01(void) = 0;
virtual void g02(void) = 0;
virtual void g03(void) = 0;
virtual void g04(void) = 0;
virtual void g05(void) = 0;
virtual void g06(void) = 0;
virtual void g07(void) = 0;
virtual void g08(void) = 0;
virtual void g09(void) = 0;
virtual void g10(void) = 0;
virtual void g11(void) = 0;
virtual void g12(void) = 0;
virtual void g13(void) = 0;
virtual void g14(void) = 0;
virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
virtual void g16(void) = 0;
virtual void g17(void) = 0;
virtual void g18(void) = 0;
virtual void initMapStringFile(const AsciiString &filename) = 0;
};
extern GameTextInterface *TheGameText;
enum INILoadType
{
INI_LOAD_INVALID,
INI_LOAD_OVERWRITE,
INI_LOAD_CREATE_OVERRIDES,
INI_LOAD_MULTIFILE
};
class INI
{
public:
INI();
~INI();
unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *pXfer);
private:
char m_body[0x87c];
};
extern "C" int (__cdecl * const _imp__sprintf)(char *buffer, const char *format, ...);
class Rva0062AF7
{
public:
void Rva0027DA58(void);
};
class LinearCampaignManager
{
public:
bool hasCampaign(void) const { return m_campaign != 0; }
private:
char m_pad00[0x10];
void *m_campaign;
};
extern LinearCampaignManager *TheLinearCampaignManager;
struct Rva0023FED9Entry
{
AsciiString m_playerName;
AsciiString m_sideName;
};
struct Rva0023FED9List
{
char m_pad00[0x1c];
Rva0023FED9Entry **m_begin;
Rva0023FED9Entry **m_end;
};
class Rva003F468D
{
public:
char m_pad00[0x24];
Rva0023FED9List *m_entries;
};
class Rva0020E6B7RegionManager
{
public:
Rva003F468D *rva0020E6B7(void);
};
class Rva002E2903Player
{
public:
char m_pad00[0x14];
int m_id;
};
class Rva002BA8F1Logic
{
public:
Rva002E2903Player *find(const AsciiString &name, unsigned int *outIndex);
Rva002E2903Player *find(int id, unsigned int *outIndex);
struct Rva002B3740Item *rva002B2B2D(void);
Rva0020E6B7RegionManager *getRegionManager(void) const { return m_regionManager; }
private:
char m_pad00[0xb0];
Rva0020E6B7RegionManager *m_regionManager;
};
extern const StaticNameKey TheKey_playerName;
extern const StaticNameKey TheKey_livingWorldPlayerID;
class PlayerTemplate
{
public:
NameKeyType getNameKey(void) const { return m_nameKey; }
int rva001FD234() const;
AsciiString getName() const;
bool isPlayableSide() const { return m_playableSide; }
private:
char m_pad00[0x10];
NameKeyType m_nameKey;
char m_pad14[0x151 - 0x14];
bool m_playableSide;
};
class MultiplayerColorDefinition
{
public:
int getColor(void) const { return m_color; }
int getNightColor(void) const { return m_colorNight; }
private:
char m_pad00[0x10];
int m_color;
char m_pad14[0x20 - 0x14];
int m_colorNight;
};
extern Rva00148F5ECache TheKey_playerIsHuman;
extern Rva00148F5ECache TheKey_playerDisplayName;
extern Rva00148F5ECache TheKey_playerFaction;
extern Rva00148F5ECache TheKey_playerAllies;
extern Rva00148F5ECache TheKey_playerEnemies;
extern Rva00148F5ECache TheKey_playerColor;
extern Rva00148F5ECache TheKey_playerNightColor;
extern Rva00148F5ECache TheKey_multiplayerStartIndex;
extern Rva00148F5ECache TheKey_multiplayerIsLocal;
extern Rva00148F5ECache TheKey_teamName;
extern Rva00148F5ECache TheKey_teamOwner;
extern Rva00148F5ECache TheKey_teamIsSingleton;
static __forceinline NameKeyType cacheKey(Rva00148F5ECache &key)
{
return key.get();
}
struct Rva002B3740Item
{
char m_pad000[0x13c];
int m_13c;
};
extern Rva00148F5ECache TheKey_playerIsSkirmish;
extern Rva00148F5ECache TheKey_playerSlot20;
extern Rva00148F5ECache TheKey_playerStartMoney;
extern Rva00148F5ECache TheKey_skirmishDifficulty;
extern Rva00148F5ECache TheKey_playerIsPreorder;
extern Rva00148F5ECache TheKey_playerAIType;
template <class T> class Rva002444BEAllocator : public _STL::allocator<T>
{
};
typedef _STL::vector<int, Rva002444BEAllocator<int> > Rva002444BEIndexVector;
enum Rva002444BEFaction
{
RVA002444BE_FACTION_NONE = 7
};
unsigned int GetGameLogicRandomSeed(void);
class CreateAHeroManager
{
public:
void *GetFactionMaskType(unsigned int classIndex, unsigned int subClassIndex);
};
class GameMessage
{
public:
void appendIntegerArgument(int arg);
void appendTimestampArgument(unsigned int arg);
void appendBooleanArgument(bool arg);
GameMessage *next(void) const { return m_next; }
private:
void *m_vtbl;
GameMessage *m_next;
};
class MessageStream
{
public:
virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
virtual void m16(); virtual void m17();
virtual GameMessage *appendMessage(int type);
void propagateMessages(void);
};
extern MessageStream *MessageStreamSubsystem;
class BfmeThingEC
{
public:
virtual void e00(void);
int bfmeTakeEC(int *size);
AsciiString m_04;
};
struct Rva00241529Record
{
unsigned int frame;
unsigned int crc;
int count;
unsigned int mask;
BfmeThingEC *stream;
Rva00241529Record *next;
};
extern int g_value12A6F38;
extern bool ignoreCRCMismatches;
struct PlayerLeaveStatus
{
int m_status;
int m_quitFrame;
int m_defeatFrame;
int m_victoryFrame;
bool m_notPresent;
unsigned char m_unknown11[3];
int m_isHuman;
AsciiString m_playerName;
};
extern char g_Va00DFE840[];
extern "C" __declspec(dllimport) __declspec(nothrow) int __cdecl sprintf(char *buffer, const char *format, ...);
enum UpdateSleepTime
{
UPDATE_SLEEP_NONE = 1,
UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class UpdateModuleInterface
{
public:
virtual UpdateSleepTime update(void) = 0;
virtual DisabledMaskType getDisabledTypesToProcess(void) const = 0;
};
class BehaviorModule
{
public:
virtual ~BehaviorModule(void);
Object *getObject(void) const { return m_object; }
private:
const void *m_moduleData;
Object *m_object;
void *m_vtbl0C;
};
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
unsigned int getWakeFrame(void) const { return m_nextCallFrame; }
void setWakeFrame(unsigned int frame)
{
if (frame > UPDATE_SLEEP_FOREVER)
frame = UPDATE_SLEEP_FOREVER;
m_nextCallFrame = frame;
}
void setIndexInLogic(int index, int phase)
{
m_phase = phase;
m_indexInLogic = index;
}
void setIndexInLogic(int index)
{
m_phase = -1;
m_indexInLogic = index;
}
private:
unsigned int m_nextCallFrame;
int m_indexInLogic;
int m_phase;
};
template <class T>
class LatchRestore
{
public:
LatchRestore(T &dest, const T &src) : m_whereToRestore(dest)
{
m_valueToRestore = dest;
dest = src;
}
virtual ~LatchRestore(void) { m_whereToRestore = m_valueToRestore; }
protected:
T m_valueToRestore;
T &m_whereToRestore;
};
class CommandList : public SubsystemInterface
{
public:
virtual void c0b(); virtual void c0c(); virtual void c0d();
virtual void c0e(); virtual void c0f(); virtual void c10();
virtual bool containsMessageOfType(int type);
GameMessage *getFirstMessage(void) const { return m_firstMessage; }
private:
GameMessage *m_firstMessage;
};
class Rva00DFE1C8Host
{
public:
bool rva00210DC9(void);
};
class Rva002431CB
{
public:
void rva002431CB(void);
};
class Rva002CEC0A
{
public:
void rva002CEC34(void);
};
class Rva002747F9
{
public:
void rva002747F9(int mode);
};
class Rva00238FF3Arg;
class Rva00238E1B
{
public:
void rva00238FF3(Rva00238FF3Arg *xfer);
};
class XferSave
{
public:
XferSave(void);
virtual ~XferSave(void);
unsigned char Open(Xfer *file, int mode, bool flag);
void close(void);
private:
char m_body[0x3c];
};
class CopyProtect
{
public:
static bool rva00232D38(void);
};
class StatsCollectorUpdate
{
public:
void rva00437BB6(void);
};
class GlobalWeatherSystem : public SubsystemInterface
{
};
class WeaponStore : public SubsystemInterface
{
};
class LocomotorStore : public SubsystemInterface
{
};
class Rva00A027B8 : public SubsystemInterface
{
};
class DelayedExperienceLevelGrantSystem : public SubsystemInterface
{
};
class BfmeMade_009CB5F0;
BfmeMade_009CB5F0 *bfmeMake_009CB5F0(void *text);
void Rva00225A0C(int msec);
extern CommandList *TheCommandList;
extern class LivingWorldManager *TheLivingWorldManager;
#define g_00DFE1C8 (*(Rva00DFE1C8Host * *)&TheLivingWorldManager)
extern bool TheDeepCRC;
extern bool TheLiteCRC;
bool TheLiteCRC = false;
extern void *g_00DFEFF0;
extern GlobalWeatherSystem *TheGlobalWeatherSystem;
extern Rva00A027B8 *g_00A027B8;
extern WeaponStore *TheWeaponStore;
extern LocomotorStore *TheLocomotorStore;
extern DelayedExperienceLevelGrantSystem *TheDelayedExperienceLevelGrantSystem;
extern void *g_Va00E01EDC;
extern "C" int (__cdecl * const _imp___unlink)(const char *path);
struct Rva0023E99ASlotFlag { char prefix[0x1a4]; bool flag; };
struct BfmeE8 { int a, b; };
class GameClient { public: void rva0023B383(Dict *, ThingTemplate *, const Coord3D *); };
extern "C" int (__cdecl * const _imp__strncmp)(const char *s1, const char *s2, unsigned int count);
class Rva0028CBFD
{
public:
void rva0028CBFD(void);
};
class Rva0033A68A
{
public:
Overridable *rva0033A68A(void);
};
static __forceinline const ThingTemplate *finalOverride(const ThingTemplate *tt)
{
return (const ThingTemplate *)((Rva0033A68A *)tt)->rva0033A68A();
}
class Team
{
public:
void setActive(void)
{
if (!m_active) {
m_created = true;
m_active = true;
}
}
private:
char m_pad00[0x5d];
bool m_active;
bool m_created;
};
extern Rva00148F5ECache TheKey_objectName;
extern Rva00148F5ECache TheKey_objectPrototypeScale;
extern Rva00148F5ECache TheKey_alignToTerrain;
extern Rva00148F5ECache TheKey_originalOwner;
float normalizeAngle(float angle);
void alignToTerrain(float angle, const Coord3D &pos, const Coord3D &normal, Matrix3D &mtx);
void GameLogic::rva00244D56(_STL::vector<Rva0024622FEntry> *created, const KindOfType *excludeKind,
const KindOfType *requireKind, bool dontCreate)
{
bool useTrees = true;
const ThingTemplate *treeA = TheThingFactory->findTemplate(TheAI->getAiData()->m_treeName[0]);
const ThingTemplate *treeB = TheThingFactory->findTemplate(TheAI->getAiData()->m_treeName[1]);
if (treeB == 0)
treeA = 0;
const ThingTemplate *treeC = TheThingFactory->findTemplate(TheAI->getAiData()->m_treeName[2]);
if (treeC == 0)
treeA = 0;
bool useOverrides = false;
bool multiplayer = TheRecorder->isMultiplayer();
if (TheGameLogic->m_110 == 2)
multiplayer = false;
if (!multiplayer) {
if (TheAI->getAiData()->m_d8 && TheGameLODManager->get1774() <= 0 && treeA) {
useOverrides = true;
treeA = finalOverride(treeA);
treeB = finalOverride(treeB);
treeC = finalOverride(treeC);
}
useTrees = !TheAI->getAiData()->m_ec;
}
AssetList assets;
int count = 0;
for (MapObject *pMapObj = BfmeTheMapObjectListHolder->m_head; pMapObj; pMapObj = pMapObj->getNext()) {
Rva0134FAA0->slot28();
bfmeReleaseQueuedDeviceInterfaces();
if (pMapObj->getFlags() & 0x36)
continue;
const ThingTemplate *thingTemplate = pMapObj->getThingTemplate();
if (thingTemplate == 0)
continue;
if (thingTemplate->m_5e5)
continue;
if (excludeKind && (char)thingTemplate->rva000456AC(*excludeKind))
continue;
if (requireKind && !(char)thingTemplate->rva000456AC(*requireKind))
continue;
if ((thingTemplate->m_108 & 0x40) && !useTrees)
continue;
const Coord3D *loc = pMapObj->getLocation();
Coord3D pos;
pos.x = loc->x;
pos.y = loc->y;
pos.z = loc->z;
pos.z += TheTerrainLogic->getGroundHeight(pos.x, pos.y);
float angle = normalizeAngle(pMapObj->getAngle());
bool isProp = (thingTemplate->m_kindof[2] >> 4) & 1;
if ((thingTemplate->m_kindof[0] & 0x80000) && thingTemplate->m_fenceWidth == 0.0f)
isProp = true;
bool unnamed = false;
if (thingTemplate->m_120 & 1) {
bool exists;
AsciiString name = pMapObj->getProperties()->getAsciiString(TheKey_objectName.get(), &exists);
if (!exists || name.isEmpty())
unnamed = true;
}
if (isProp || unnamed || (thingTemplate->m_kindof[1] & 0xc0000000)) {
Dict *props = pMapObj->getProperties();
bool hasScale;
float scale = props->getReal(TheKey_objectPrototypeScale.get(), &hasScale);
Matrix3D mtx(true);
bool align;
if (props->getBool(TheKey_alignToTerrain.get(), &align) && align) {
Coord3D normal;
TheTerrainLogic->getLayerHeight(pos.x, pos.y, LAYER_GROUND, &normal, true);
Coord3D zero;
zero.x = 0.0f;
zero.y = 0.0f;
zero.z = 0.0f;
alignToTerrain(angle, zero, normal, mtx);
} else {
mtx.Rotate_Z(pMapObj->getAngle());
}
float propScale = thingTemplate->m_4e0;
if (hasScale)
propScale *= scale;
AssetLoadMode mode;
((ThingTemplate *)thingTemplate)->GetAssetList((int)&assets, (int)&mode);
if (++count == 20) {
count = 0;
bfmeMergeReceiverKeys((int)&assets);
assets.clear();
}
if (dontCreate)
continue;
if (thingTemplate->m_kindof[1] & 0x40000000) {
if (treeA && useOverrides) {
if (thingTemplate->m_5eb && thingTemplate->m_5ec)
thingTemplate = treeA;
else if (!thingTemplate->m_5eb && thingTemplate->m_5ec)
thingTemplate = treeB;
else
thingTemplate = treeC;
propScale = TheAI->getAiData()->m_treeScale;
}
if (useTrees)
TheTerrainLogic->rva00283642(thingTemplate, &pos, &mtx, propScale);
} else if (thingTemplate->m_kindof[1] & 0x80000000) {
TheTerrainLogic->rva00280176(thingTemplate, &pos, &mtx, propScale);
} else if (unnamed) {
((GameClient *)TheGameClient)->rva0023B383(props, (ThingTemplate *)thingTemplate, &pos);
} else {
TheTerrainLogic->rva0027D3D9(thingTemplate, &pos, &mtx, propScale);
}
} else {
Dict *props = pMapObj->getProperties();
AsciiString originalOwner = props->getAsciiString(TheKey_originalOwner.get());
Team *team = ThePlayerList->validateTeam(originalOwner, pMapObj);
if (ThePlayerList->getNeutralPlayer()->getDefaultTeam() == team
&& _imp__strncmp("Player_", originalOwner.str(), 7) == 0
&& !(thingTemplate->m_120 & 0x20000))
continue;
AssetLoadMode mode;
((ThingTemplate *)thingTemplate)->GetAssetList((int)&assets, (int)&mode);
if (++count == 20) {
count = 0;
bfmeMergeReceiverKeys((int)&assets);
assets.clear();
}
if (dontCreate)
continue;
CreateMask mask;
Object *obj = TheThingFactory->rva002D0A23(thingTemplate, team, mask, (ObjectID)0);
if (obj == 0)
continue;
if ((pMapObj->getFlags() & 1) || (obj->getTemplate()->m_108 & 0x20)) {
Drawable *draw = obj->getDrawable();
if (draw)
draw->setDrawableStatus(1);
}
bool align;
if (props->getBool(TheKey_alignToTerrain.get(), &align) && align) {
Coord3D zero;
zero.x = 0.0f;
zero.y = 0.0f;
zero.z = 0.0f;
Coord3D normal;
TheTerrainLogic->getLayerHeight(pos.x, pos.y, LAYER_GROUND, &normal, true);
Matrix3D mtx;
alignToTerrain(angle, zero, normal, mtx);
obj->setTransformMatrix(&mtx);
} else {
obj->setOrientation(angle);
}
obj->setPosition(&pos);
obj->updateObjValuesFromMapProperties(props);
obj->rva0028B4CE(TheTerrainLogic->getLayerForDestination(obj, &pos));
Rva0134FAA0->slot28();
bfmeReleaseQueuedDeviceInterfaces();
((Rva0028CBFD *)obj)->rva0028CBFD();
team->setActive();
TheAI->pathfinder()->AddObjectToPathfindMap(obj);
Rva0024622FEntry entry;
entry.obj = obj;
entry.mapObj = *(MapObject*volatile*)&pMapObj;
((_STL::vector<BfmeE8> *)created)->push_back(*(const BfmeE8 *)&entry);
}
}
bfmeMergeReceiverKeys((int)&assets);
}
