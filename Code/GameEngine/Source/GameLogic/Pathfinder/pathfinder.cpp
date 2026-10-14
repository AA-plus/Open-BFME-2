// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// wb-lead 2.000 callgraph: Pathfinder::SetBridgeStateRepaired at 0x002E7205.
// Identity evidence: the GeneralsMD AIPathfind.cpp implementation
// Pathfinder::changeBridgeState checks the selected layer, sets its destroyed
// state to the inverse of repaired, then dirties zones with the repaired flag.
// GeneralsMD BridgeBehavior calls that method on bridge damage and repair.
// Target call sites resolve to rowed Rva0036666B at 0x0036666B, unrowed callee
// 0x0036736E and rowed PathfindZoneManager::rva00531481 at 0x00531481. The unrowed
// callee pin is supported by its selected-layer callsite and the GeneralsMD
// PathfindLayer::setDestroyed(Bool) donor. Target arithmetic gives 64-byte
// layers at +0x60 and the final manager-like subobject at +0x460.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <new>
#include "../../Common/GameLogicObjectLookupView.h"
typedef bool Bool;
typedef int Int;
enum PathfindLayerEnum
{
	PATHFIND_LAYER_UNKNOWN = 0,
	PATHFIND_LAYER_GROUND = 1
};
typedef int LocomotorSurfaceTypeMask;

class LocomotorSet
{
public:
	LocomotorSurfaceTypeMask getValidSurfaces() const
	{
		return m_validLocomotorSurfaces;
	}
private:
	char m_pad[0x10];
	LocomotorSurfaceTypeMask m_validLocomotorSurfaces;
	Bool m_downhillOnly;
	Bool m_scalesWalls;
};

class Player
{
public:
	char m_pad00[0x5c];
	Int m_playerType;		// +0x5C (1: computer)
};
// Relationship order is established by the rowed Object::getRelationship.
class AIUpdateInterface;
struct PathfinderTemplateView {
    char pad[0x64];
    char *nameBuffer;
    char pad68[0x108-0x68];
    unsigned char kinds[24];
    char pad120[0x56c-0x120];Int priority;char pad570[0x634-0x570];Bool flag;
    __forceinline bool hasKind(int bit) const { return (kinds[bit/8] & (1<<(bit%8)))!=0; }
    // The same KindOf bit read as BitFlags words (dword tests in retail).
    __forceinline unsigned int testKindWord(unsigned int bit) const { return ((const unsigned int *)kinds)[bit>>5] & (1u<<(bit&31)); }
    __forceinline const char *name() const { return nameBuffer ? nameBuffer+8 : ""; }
};
enum Relationship { ENEMIES=0, NEUTRAL=1, ALLIES=2 };
enum ObjectStatusTypes { QuickStatus49=49 };
class Object
{
public:
	Player *getControllingPlayer() const;
 Bool testStatus(ObjectStatusTypes) const;
	Relationship getRelationship(const Object *) const;
    int rva0028B511() const;
    bool rva002E6B89();
	bool IsAtGoalPosition() const;
	Bool canCrushOrSquishNoAlly(Object *other, Int test);
	bool rva0028AFBB() const;
	float GetGoalAngle() const;
    __forceinline int getID() const { return *(const int *)((const char *)this+0x74); }
	AIUpdateInterface *getAI() const { return reinterpret_cast<AIUpdateInterface *>(m_258); }
	void *m_vtable;
	PathfinderTemplateView *m_template;
	char m_pad08[0x38-8];
	float position[3];
	float m_orientation;				// +0x44
	char m_pad48[0x258 - 0x48];
	char *m_258;						// +0x258 (WorldBuilder +0x260: CanApproachToTarget's gate)
	char m_pad25C[0x274-0x25C];
	Object *container;
};
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
};
struct Rva002E7ED6Info;
class Pathfinder;
// Native aircraft-path node ABI agrees with the rowed ctor and prepend provider.
class PathNode {
public:
    PathNode(const Coord3D *,PathfindLayerEnum) throw();
    PathNode *next,*previous,*nextOptimized;
    Coord3D position;
    PathfindLayerEnum layer;
    Bool canOptimize;
    Int portalID;
};
struct Rva002EDEABArg;
struct Rva002E93A7Info
{
	Pathfinder *m_00;
	Int m_04;
};
class Waypoint { public: Int word0,id;void *name;Coord3D location;char pad18[0x44-0x18];Waypoint *chainNext;Int word48,linkCount; };
class PathfindCell;
class Path
{
 friend class Pathfinder;
public:
 void rva00265596(const Coord3D *,PathfindLayerEnum,Int);
	Path();										///< matched 0x00363DC8
	// 0x00364551 / 0x00365E98 (unrowed): Zero Hour's optimize step with a
	// BFME facing hint, and a final pass toward a direction (unnamed).
	void rva00364551(Object *obj, LocomotorSurfaceTypeMask surfaces, Bool blocked, const float *facing);
	void rva00365E98(Object *obj, const Coord3D *dir, LocomotorSurfaceTypeMask surfaces, Bool blocked);
	void rva002655E3(const Coord3D *pos, PathfindLayerEnum layer, Int portal);
	void SetLastNodePortal(Int portal);
private:
	void *word0;PathNode *firstNode;PathNode *lastNode;char wordC;Bool blockedByAlly;char padE[0x28-0xe];
};

struct Rva002E8C23Pair { Int x,y; };
void rva002E79A8(int,unsigned char,int,int,int);
// ?Rva002E8C4DCall@@YAHHEPAURva002E8C23Pair@@H@Z, retail 0x002E8C4D (33 bytes):
// cdecl cell-centre wrapper forwarding the cell's x/y to 0x002E79A8. Defined
// here, ahead of its Pathfinder callers, because cl 7.1 reads the body: knowing
// it keeps no reference to the cell is what fixes AdjustDestination's schedule.
int __cdecl Rva002E8C4DCall(int a1, unsigned char a2, Rva002E8C23Pair *a3, int a4)
{
	rva002E79A8(a1, a2, a3->x, a3->y, a4);
	return a1;
}
bool Rva002EBBFBIsOdd(void *);
struct ICoord2D;
ICoord2D *Rva002E7875WorldToCell(ICoord2D *,bool,const Coord3D *);
extern "C" double __cdecl fabs(double);
struct PathfinderCostCellInfo { Int x,y; };
struct PathfinderGroundInfo { PathfinderCostCellInfo position;Int parent;Waypoint *parentWaypoint;unsigned short totalCost,costSoFar;char pad14[0x28-0x14];ObjectID obstacleID;unsigned int flags; };
struct In002E6BA1 { Int x,y; };
class MixFileInfoBuffer;
extern Int TheMixFileInfoPool;
void Rva0052DBCDInit();
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **,Int,In002E6BA1 *);
class Rva002E6AF3 { public: Int get() const; };
class Rva002E6B06 { public: Int rva002E6B06(); };
class Rva002E6C79;
struct Rva002E8BCFSrc;
class Rva002E8BCF { public: Rva002E8BCF(const Rva002E8BCFSrc *,Bool,Int,Bool); Int surfaces;Bool field4,field5;Int maxLayer;Bool fieldC; };
class Rva002E6DC4
{
public:
	bool rva002E6DC4(void *a_raw, void *b_raw);
private:
	char m_pad[0x48];
	void *m_48;
};

void ji_00629952();
struct Rva002F35AFCell;
class Rva002E6C79
{
public:
	Int rva002E6C79();
	Rva002F35AFCell *m_00;
	Rva002E6C79 *next() { return (Rva002E6C79 *)rva002E6C79(); }
};
class PathfindCell
{
 friend class Pathfinder;
public:
	// The packed cell word at +0x0C: type in bits 0-3, layer in bits 4-9.
	enum CellType
	{
		CELL_CLEAR = 0,
		CELL_OBSTACLE = 4,
		CELL_IMPASSABLE = 5
	};
	enum { LAYER_GROUND = 1 };

 Bool IsObstaclePresent(ObjectID) const;
 Bool StartPathfind(Int);void ReleaseInfo();void SetParentCell(Int *);void PutOnClosedList(MixFileInfoBuffer **);Int CalcCostSoFar(const Rva002E6C79 *);
 __forceinline void allocateInfo(In002E6BA1 *pos) {
  if(!m_pathInfo) { if(!TheMixFileInfoPool)Rva0052DBCDInit();m_pathInfo=(PathfinderGroundInfo *)Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool,(Int)this,pos); }
  else m_pathInfo->parentWaypoint=0;
 }
	void rva0052DAE9(Bool open);
	unsigned short quickZone()const {return (unsigned short)word8;}
 Int getXIndex() const { return m_pathInfo->position.x; }
	Int getYIndex() const { return m_pathInfo->position.y; }
	// 0x0052DD75 (unrowed): an angle for the cell from a facing, a count and
	// a weight (unnamed).
	float rva0052DD75(float facing, Int count, float weight);
	__declspec(dllimport) __forceinline CellType getType() const { return (CellType)(m_info & 0xf); }
	Int getLayer() const { return (m_info & 0x3f0) >> 4; }
	Int getConnectLayer() const { return (m_info >> 10) & 0x3f; }
	Bool rvaBit16() const { return (Bool)((m_info >> 16) & 1); }
 PathfindCell *getParentCell(){return (PathfindCell *)((Rva002E6C79 *)this)->rva002E6C79();}
 Waypoint *getParentWaypoint()const {return m_pathInfo?m_pathInfo->parentWaypoint:0;}

private:
	PathfinderGroundInfo *m_pathInfo;
	Waypoint *waypoint;Int word8;
	unsigned int m_info;			// +0x0C
};

// A locomotor's legal surfaces live in its template (+0x04) at +0x14.
struct LocomotorTemplate
{
	char m_pad00[0x14];
	LocomotorSurfaceTypeMask m_surfaces;	// +0x14
};

class Locomotor
{
public:
	__declspec(dllimport) __forceinline LocomotorSurfaceTypeMask getLegalSurfaces() const { return m_template->m_surfaces; }

private:
	void *m_vtbl;
	const LocomotorTemplate *m_template;	// +0x04
};

// The surfaces each cell type allows, indexed by type (VA 0x00DBD33C,
// defined in Rva002E6DC4Check.cpp).
// g_00DBD33C: VA 0x00DBD33C (.data), the cell-type surface table; exact retail initial dwords.
unsigned int g_00DBD33C[16] = {
	0x00000009, 0x0000000A, 0x0000000C, 0x00000018,
	0x00000028, 0x00000048, 0x00000048, 0x00000088,
	0x00000000, 0x3E490FDB, 0x41A00000, 0x41A00000,
	0x00000000, 0x00000001, 0x00000000, 0xFFFFFFFF
};

extern "C" __declspec(dllimport) double __cdecl floor(double);
float Sin(float x);
float Cos(float x);

// REAL_TO_INT_FLOOR: the IAT floor then an x87 round-to-integer store.
static __forceinline Int realToIntFloor(float f)
{
	float floored = (float)floor((double)f);
	long i;
	__asm {
		fld [floored]
		fistp [i]
	}
	return i;
}

class Rva002F3738
{
public:
	void rva002F3738(void **entry);
};

struct _Rva002E7B02Cell
{
	Int x;
	Int y;
	Int z;
};

class Rva002E7B02
{
public:
	Rva002E7B02(Int a, Int b, const _Rva002E7B02Cell &cell);
private:
	Int m_00;
	Int m_04;
	Int m_08;
	Int m_0C;
	Int m_10;
};

struct Rva002E7B29Info;

template<int N> class PathfinderNativeSlots : public PathfinderNativeSlots<N-1> { public: virtual void unusedSlot(PathfinderNativeSlots<N> *); };
template<> class PathfinderNativeSlots<0> {};
class TerrainLogicCheckDestination : public PathfinderNativeSlots<50> { public: virtual bool slotC8(const Coord3D *); };
class PathfinderContain28 : public PathfinderNativeSlots<28> { public: virtual int slot70(); };
class PathfinderContain31 : public PathfinderNativeSlots<31> { public: virtual void *slot7C(); };
class PathfinderContain69 : public PathfinderNativeSlots<69> { public: virtual unsigned int slot114(int); };
class TerrainLogicWaterQuery : public PathfinderNativeSlots<19> { public: virtual bool slot4C(float,float,float *,void *,void *); };
class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual float getGroundHeight(float x, float y, Coord3D *normal);
	virtual float getLayerHeight(float,float,PathfindLayerEnum,Coord3D *,Bool);
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

// The per-object radius/centre split (rowed 0x002EBCA7).
void Rva002EBCA7Split(void *obj, Int *radius, unsigned char *center);
struct Rva002F600CInfo;

// Coord3D::set(const Coord3D *) as Zero Hour's header defines it inline.
static __forceinline void zeroCoord3D(Coord3D *dst)
{
	dst->x = 0.0f;
	dst->y = 0.0f;
	dst->z = 0.0f;
}
static __forceinline void copyCoord3D(Coord3D *dst, const Coord3D *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

// Pathfinder_FuncTightenPath (0x34 bytes): WorldBuilder's functor for
// TightenPath's line walk, Zero Hour's TightenPathStruct plus the goal.
class Pathfinder_FuncTightenPath
{
public:
	Pathfinder_FuncTightenPath(Pathfinder *pathfinder, Object *obj,
		const LocomotorSet &locomotorSet, PathfindLayerEnum layer,
		const Coord3D &goal);

	Pathfinder *m_pathfinder;				// +0x00
	Object *m_obj;							// +0x04
	const LocomotorSet *m_locomotorSet;		// +0x08
	Int m_radius;							// +0x0C
	unsigned char m_center;					// +0x10
	PathfindLayerEnum m_layer;				// +0x14
	Bool m_foundDest;						// +0x18
	Coord3D m_goal;							// +0x1C
	Coord3D m_destPos;						// +0x28
};

// Pathfinder_IsCheckForAdjust (0x3C bytes): WorldBuilder's functor for the
// destination-adjust check; Zero Hour's checkForAdjust info plus the goal,
// an optional second position whose layer wins, a float and a word.
class Pathfinder_IsCheckForAdjust
{
public:
	Pathfinder_IsCheckForAdjust(Pathfinder *pathfinder, Object *obj,
		void *arg, const Coord3D &goal, const Coord3D *layerPos, float range,
		Int arg6);

	Pathfinder *m_pathfinder;				// +0x00
	Object *m_obj;							// +0x04
	void *m_08;								// +0x08
	Bool m_isHuman;							// +0x0C
	unsigned char m_center;					// +0x0D
	Int m_radius;							// +0x10
	const Coord3D *m_layerPos;				// +0x14
	PathfindLayerEnum m_layer;				// +0x18
	float m_range;							// +0x1C
	Rva002E8C23Pair fallback;
	Int m_28;								// +0x28
	Int m_2C;								// +0x2C
	Coord3D m_goal;							// +0x30
};

// Pathfinder_IsCheckForMeleeHordeAdjust (0x34 bytes): WorldBuilder's functor
// for the melee/horde destination check; Zero Hour's checkForAdjust info
// (isHuman, radius/centre, layer) plus a float and the goal.
class Pathfinder_IsCheckForMeleeHordeAdjust
{
public:
	Pathfinder_IsCheckForMeleeHordeAdjust(Pathfinder *pathfinder, Object *obj,
		void *arg, const Coord3D &goal, float range);

	Pathfinder *m_pathfinder;				// +0x00
	Object *m_obj;							// +0x04
	void *m_08;								// +0x08
	Bool m_isHuman;							// +0x0C
	unsigned char m_center;					// +0x0D
	Int m_radius;							// +0x10
	PathfindLayerEnum m_layer;				// +0x14
	float m_range;							// +0x18
	Rva002E8C23Pair m_1C;
	Int m_24;								// +0x24
	Coord3D m_goal;							// +0x28
};

// The rowed cell-centre helper 0x002EBC59 (returns its out Coord3D) and the
// pinned 0x002CB35C range probe (WorldBuilder: Weapon::isWithinAttackRange).
void *rva002EBC59(void *out, void *obj, Int a2, Int a3, Int a4);
class Rva002CB35CObj
{
public:
	Bool rva002CB35C(Int a1, void *pos, void *a3, void *a4, float range, Int a6);
};

// CanApproachToTarget's helpers. The rowed 0x002C9B80 range query returns a
// float; its +0x04 member answers the rowed byte getter 0x002C9400.
class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};
class Rva002C9B80Owner
{
public:
	float rva002C9B80(void *a, float b);
	void *m_00;
	Rva002C9400ByteField *m_04;				// +0x04
};
// The 0x24-byte cell-query functor (rowed constructor 0x002E9ACC); the line
// walk 0x002F6C22 calls its 0x002F4D8B callback, which sets +0x1C on a hit.
struct Rva002E8BCFSrc;
struct Rva002F4D8BInfo;
class Rva002E9ACC
{
public:
	Rva002E9ACC(void *a1, Object *obj, Rva002E8BCFSrc const *src,
		unsigned char a4, unsigned char a5);
	char m_pad00[0x1C];
	Bool m_found;							// +0x1C
	unsigned char m_1D;						// +0x1D
	unsigned char m_1E;						// +0x1E
	unsigned char m_1F;						// +0x1F
	unsigned char m_20;						// +0x20
};

// A hierarchical path node list (rowed 0x002E6C79 gives the next node) whose
// +0 points at a cell record: x, y, and at +0x0C a zone record whose +0x04
// is kept.
struct Rva002F35AFZone
{
	Int m_00;
	Int m_04;
};
struct Rva002F35AFCell
{
	Int x;
	Int y;
	Int m_08;
	Rva002F35AFZone *m_0C;
};

// The 12-byte record +0x1C1CC collects per hop (zone, next cell x/y).
struct Rva002F35AFHop
{
	Int m_zone;
	PathfinderCostCellInfo m_position;
};
// The 0x14-byte hierarchical path (rowed constructor 0x005348AD); 0x00534557
// adds a cell and 0x00534AAE finishes it (WorldBuilder: computeOrderMap).
class Rva005348AD
{
public:
	Rva005348AD();
	void rva00534557(Rva002F35AFCell *cell);
	void rva00534AAE();
private:
	char m_pad[0x14];
};

class Rva0036666B
{
public:
	bool rva0036666B();
};

class PathfindLayer
{
public:
	bool setDestroyed(bool destroyed);
    __declspec(noinline) void rva000B3FD0();
private:
	char m_pad[0x40];
};

class PathfindZoneManager
{
public:
	void rva00531300();
	void rva00531481();
	void rva005314C6(Int x, Int y, unsigned char flag);
};


struct Rva002EBC7FPair { int x,y; };
void *rva002EBC7F(void *,void *,Rva002EBC7FPair *,int);
#include <math.h>
class Rva001E46E1 { public: float rva001E46E1(Object *); };
class AIUpdateInterface {
public:
    bool isAircraftThatAdjustsDestination() const;
    int rva0026417F(bool);
    Object *getCurrentVictim() const;
    char gap[0x1f0];
    Rva001E46E1 *locomotor;
};
// Native 0x002EC0A2 reads Object nodes at cell-info +0x14, +0x20 and +0x24.
// The list-role labels below describe the three observed conflict passes;
// their original member spellings are not established. Nodes link at +0 and
// carry Object* at +8; native Object position/AI/container are +0x38/+0x258/+0x274.
struct PathCollisionNode { PathCollisionNode *next; void *word4; Object *object; };
struct PathCollisionInfo {
    int x,y;
    char gap08[0x14-8];
    PathCollisionNode *occupants;
    PathCollisionNode *hordeGoalNodes; // Native/WB horde query list at+18.
    char gap1C[4];
    PathCollisionNode *goals;
    PathCollisionNode *reservations;
    ObjectID fallbackID; // Native/WB fallback lookup when +20 list is empty.
};
struct PathCollisionCell { PathCollisionInfo *info; };
// Native bridge list links at +4; height and containment use existing
// independently admitted Bridge providers from the terrain-logic family.
class Bridge {
public:
    bool isPointOnBridge(const Coord3D *pos);
    float getBridgeHeight(const Coord3D *pos, Coord3D *normal);
    void *m_00;
    Bridge *m_next;
};
struct Rva002ED236Pos {
    float x, y, z;
    Rva002ED236Pos(const Coord3D &c) { x = c.x; y = c.y; z = c.z; }
    ~Rva002ED236Pos() {}
};
int Rva002E6E8AGet(int layer);
class Rva002E7482 { public: float rva002E7482(int layer); };

#include "ascii_string.h"
struct GeometryShape {
    int type; float height,major,minor;
    float offsetX,offsetY,offsetZ;
    AsciiString name;
    bool enabled,opaque21;
    __forceinline GeometryShape() : type(0),height(1),major(1),minor(1),offsetX(0),offsetY(0),offsetZ(0),enabled(true),opaque21(true) {}
};
class GeometryInfo { public: void rva006BD9C0(GeometryShape &) const; };
struct ICoord2DBase { int x,y; };
class Rva002E9D09 { public: int rva002E9D09(Object *,int,int); };
class Rva002E7C99 {
public:
    void *rva002E7C99(int,int,int,unsigned char,int,unsigned char,int);
    char fields[28];
};
class Rva0006E009DwordField { public: int get() const; };
class Rva0052DB4D { public: bool rva0052DB4D(int); };
void rva002E79A8(int,unsigned char,int,int,int);
// Native 0x002F01B6 addresses this 12-byte floating scratch first. Later
// 0x002F0369 stores integer position at scratch+4 and diameter at scratch+12.
// The two phases do not overlap; this local union preserves that 20-byte reuse.
union PathfinderCheckCoordinates {
    Coord3D point;
    struct IntegerLayout { int reserved; ICoord2DBase position,size; } cells;
};
struct PathfinderLogFile;
extern "C" int __cdecl fprintf(PathfinderLogFile *,const char *,...);
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;

#include "../../../../Libraries/Include/Lib/ICoord2D.h"
// A cell index returned by value (hidden pointer): ICoord2D with a field-wise
// copy constructor, like PathfinderCellPoint below.
struct PathfinderCellIndex : ICoord2D {
	__forceinline PathfinderCellIndex() {}
	__forceinline PathfinderCellIndex(const PathfinderCellIndex &o) { x = o.x; y = o.y; }
};
class Rva002F6F90Context { public: Bool rva002F6F90(unsigned int,Int); };
class Rva002F70E5Context { public: Bool rva002F70E5(unsigned int,Int); };
class Rva002E7440 { public: Bool rva002E7440(Int,Int); };
class Rva002E7414 { public: Int rva002E7414(Int,Int); };
class Rva002F336AOwner { public: Bool rva002F336A(Int,Int); };
struct PathfinderOpenQueue {PathfindCell **first,**last;Bool empty()const{return first==last;}PathfindCell *front()const{return *first;}};
struct ICoord2D;
struct Rva002E7261Info;
struct PathfinderMineshaft { Int m_00; Int m_portal; Int m_08; Coord3D m_position; };
struct TCheckMovementInfo;
class HierarchicalPath;
class Pathfinder
{
public:
 Bool adjustToMeleeDestination(Object*,const LocomotorSet&,Coord3D*);
 Bool CheckForAdjust(Object *,const LocomotorSet &,Bool,Int,Int,PathfindLayerEnum,Int,Bool,Coord3D *,const Coord3D *,float,Int *,Int);
 Bool QuickDoesPathExist(Object *,const Coord3D *,const Coord3D *,Int);
 Bool IsValidMovementPositionForObject(const Coord3D *,Int,Int,const Object *);
 Bool rva002F4115(Object *,Int,Int,LocomotorSet *);
 Bool rva002F4AC1(const ICoord2D *,Int,Int,Object *,PathfindLayerEnum,Int,Rva002E7261Info *,void *,void *);
 PathfindCell *rva002F068F();
 Path *FindSafePath(Object *,const LocomotorSet &,const Coord3D *,const Coord3D *,const Coord3D *,float);
 Path *PatchPath(Object *,const LocomotorSet &,Path *,Bool);
 Path *GetHordeUnitPath(Object *,const Coord3D *);
    Path *GetAircraftPath(const Object *,const Coord3D *);
    int _GetOverlapUnits(Object *,const Coord3D *,int *);
    int GetOverlapGoalUnits(Object *,const Coord3D *,int *);
    int CountOverlapHordeGoalUnits(Object *,const Coord3D *);
    int _GetAdjacentUnits(Object *,const Coord3D *,int *);
    Bool rva002E9BE5(const Coord3D *,const Coord3D *,float,unsigned,Coord3D *);
    Bool rva002F3392(PathNode *,PathNode *,unsigned,Coord3D *,Coord3D *,Coord3D *);
    void SetDebugPath(Rva002EDEABArg *);
	Bool rva002EAE5F(const ICoord2D *,Int,ICoord2D *,void *);
	Bool rva002EB11B(const ICoord2D *,Int,ICoord2D *,void *);
	Bool rva002F379E(ICoord2D *,Int,void *);
	Bool AdjustDestination(Object *,const LocomotorSet &,Coord3D *,const Coord3D *);
	Bool AdjustHordeMeleeDestination(Object *,void *,Coord3D *);
	Int CheckPathCost(Object *,const LocomotorSet &,const Coord3D *,const Coord3D *);
	Bool rva002F8E2D(const ICoord2D *,Int,ICoord2D *,void *);
	Bool rva002F90E9(ICoord2D *,Int,void *);
	Bool rva002F92BC(const ICoord2D *,Int,ICoord2D *,void *);
 PathfindCell *rva002E8BF8(PathfindLayerEnum,const Coord3D *);
 PathfindCell *rva002F36E5();Int rva002F40E7();void CheckChangeLayers(PathfindCell *,Object *);
	Path *InternalFindPath(Object *,const LocomotorSet &,const Coord3D *,const Coord3D *,HierarchicalPath *,Bool *);
	Int rva002F83F5(PathfindCell *,PathfindCell *,const LocomotorSet &,Bool,Bool,Int,ICoord2D *,Object *,Int);
	Int ExamineNeighboringCellsForSidewaysAttack(PathfindCell *,const ICoord2D *,Int,const LocomotorSet &,Bool,Bool,Int,ICoord2D *,Object *,Int);
	Bool checkForMovement(Object *,TCheckMovementInfo &);
	Bool rva002EDFF9(Object *,Coord3D *);
	void rva002E75A3(Coord3D *,Coord3D *);
	Int rva002F0A72(PathfindCell *,PathfindCell *);
	float GetWallHeight(PathfindLayerEnum layer, const Coord3D *pos, Coord3D *normal);
	void *rva001E3647Pos(int layer, const Coord3D *pos);
	bool IsPointOnRamp(const Coord3D *pos);
	PathfindLayerEnum rva002ED236(Object *obj, Rva002ED236Pos pos);
	Bool CheckDestination(Object *,Int,Int,PathfindLayerEnum,Int,Bool,Int *,Bool);
    Int rva002EED80(const ICoord2DBase *,const ICoord2DBase *,float,int,Rva002E9D09 *);
	void SetBridgeStateRepaired(PathfindLayerEnum layer, Bool repaired);
	void ForceMapRecalculation();
	void Rva0052F2EC();
	int rva002EADE1(const Coord3D *a, const Coord3D *b,
		PathfindLayerEnum layer, Rva002E7ED6Info *info);
	int rva002EED41(const Coord3D *startWorld, const Coord3D *endWorld,
		PathfindLayerEnum layer, Rva002E93A7Info *info);
	int rva002EB3D7(const Coord3D *startWorld, const Coord3D *endWorld,
		PathfindLayerEnum layer, Rva002E7B29Info *info);
	Bool IsGroundLineOnly(const Coord3D *startWorld,
		const Coord3D *endWorld);
	Bool IsGroundPathPassable(const Coord3D *startWorld,
		PathfindLayerEnum layer, const Coord3D *endWorld, Int pathDiameter);
	void AddToOpenList(PathfindCell *cell);
	int CalcExtraCosts(Object *,PathfindCell *,Rva002EBC7FPair *,int,int,bool);
	int CalcCollisionFreeExtraCosts(Object *,PathfindCell *,Rva002EBC7FPair *,PathfindLayerEnum,int,int,bool);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);	// 0x002E6D62
	PathfinderCellIndex Rva002E7917(bool center, const Coord3D *pos);	// 0x002E7917 clamp wrapper
	Bool IsValidMovementTerrain(PathfindLayerEnum layer, const Locomotor *locomotor, const Coord3D *pos);
	Int AdjustGroundPathPosition(const Coord3D &source, Coord3D &destination);
	unsigned char bfmeWrapE6E90(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);
	Bool CheckForTarget(void *obj, void *a2, void *a3, Rva002CB35CObj *weapon,
		void *a5, void *a6, void *a7, void *a8, Coord3D *out);
	Path *BuildActualPath(Object *obj, LocomotorSurfaceTypeMask surfaces,
		const Coord3D *fromPos, PathfindCell *goalCell, Bool center,
		Bool blocked, Bool faceDirection);
	// WorldBuilder's Pathfinder::PrependCells (0x002EE1C7, unrowed).
	void PrependCells(Path *path, const Coord3D *fromPos, PathfindCell *goalCell, Bool center);
	Rva005348AD *MakeHierarchicalPathPassable(void *unused, Rva002E6C79 *path, Bool expand);
	void TightenPath(Object *obj, const LocomotorSet &locomotorSet, Coord3D *from, const Coord3D *to);
	int rva002F95B7(const Coord3D *from, const Coord3D *to, PathfindLayerEnum layer, Rva002F600CInfo *info);
	Int iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002F4D8BInfo *callbackInfo);
	Bool CanApproachToTarget(Object *obj, const Coord3D *targetPos, Rva002C9B80Owner *weapon, Bool flag);
protected:
	Path *FindHierarchicalPath(Bool isHuman,
		const LocomotorSet &locomotorSet, Object *obj, const Coord3D *from,
		const Coord3D *to, Bool crusher);
	Path *FindClosestHierarchicalPath(Bool isHuman,
		const LocomotorSet &locomotorSet, Object *obj, const Coord3D *from,
		const Coord3D *to, Bool crusher, Coord3D *adjustedTo);
	Path *internal_findHierarchicalPath(Bool isHuman,
		LocomotorSurfaceTypeMask locomotorSurface, Object *obj,
		const Coord3D *from, const Coord3D *to, Bool crusher, Bool closestOK,
		Coord3D *adjustedTo);
private:
	Int iterateCellsAlongLine(const ICoord2D *,const ICoord2D *,PathfindLayerEnum,Rva002E7261Info *);
	char m_pad000[8];Bool m_isMapReady;char m_pad009[7];
	int m_unknown10;
	ICoord2D m_clampLo, m_clampHi;	// +0x14 cell extent the 0x002E7917 clamp uses
    Int m_extentLowX,m_extentLowY,m_extentHighX,m_extentHighY;
    MixFileInfoBuffer *m_closedList;Bool m_isTunneling;char m_pad039[0x48-0x39];
	ObjectID m_ignoreObstacleID;	// +0x48
	char m_pad04C[0x5c-0x4c];
	Bridge *m_bridges;
	PathfindLayer m_layers[16];
	PathfindZoneManager m_zoneManager;
	char m_pad461[0x1BEB6 - 0x461];
	Bool m_1BEB6;		// +0x1BEB6: paths get a facing hint from the goal cell
	char m_pad1BEB7[5];
	float m_wallLayerHeights[48];
	char m_pad1BF7C[0x1C1CC - 0x1BF7C];
	_STL::vector<Rva002F35AFHop> m_1C1CC;	// +0x1C1CC
 // +0x1C1D8/+0x1C1DC: mine-shaft portals; WorldBuilder asserts m_destMineshaft
 // on the second. Each carries a zone/portal ID at +4 and its position at +0xC.
 PathfinderMineshaft *m_srcMineshaft,*m_destMineshaft;
 char pad1c1e0[0x1d1f0-0x1c1e0];PathfinderOpenQueue m_openCells;
};

class Rva002E99F9Sub460
{
public:
	unsigned short rva0053241F(void *, unsigned short);
	unsigned short rva00531FD4(void *, unsigned short);
};

// The 0x002E8045 walk calls this ABI view. The callback at 0x002E7261
// writes its result key at +8 and cell coordinates at +0xC/+0x10.
struct Rva002E7261Info
{
	Pathfinder *m_pathfinder;
	Int m_arg;
	Int m_key;
	ICoord2D m_position;
	Int cellCallback(PathfindCell *, PathfindCell *, Int, Int);
};

// Native 0x002F4AC1..0x002F4B33 (114 bytes, RET36). WB's four calls pass
// this argument order; retail confirms the changed-cell key at info+8.
Bool Pathfinder::rva002F4AC1(const ICoord2D *start, Int dx, Int dy,
	Object *object, PathfindLayerEnum layer, Int expected,
	Rva002E7261Info *info, void *lookup, void *context)
{
	ICoord2D endpoint = *start;
	endpoint.x += dx;
	endpoint.y += dy;
	iterateCellsAlongLine(start, &endpoint, layer, info);
	if (info->m_key != -1)
	{
		Int actual = ((Rva002E99F9Sub460 *)((char *)this + 0x460))
			->rva0053241F(lookup, (unsigned short)info->m_key);
		if (expected == actual || rva002F4115(object, expected, actual,
			(LocomotorSet *)context))
			return true;
	}
	return false;
}

// ?Pathfinder::SetBridgeStateRepaired present-unmatched
void Pathfinder::SetBridgeStateRepaired(PathfindLayerEnum layer, Bool repaired)
{
	if (((Rva0036666B *)&m_layers[layer])->rva0036666B()) {
		if (m_layers[layer].setDestroyed(!repaired)) {
			m_zoneManager.rva00531481();
		}
	}
}

void Pathfinder::ForceMapRecalculation()
{
	if (m_unknown10 != 0) {
		Rva0052F2EC();
	}
}

// WB 0xD3EA20 dispatches the ground-layer line test to the rowed helper.
// The retail ABI reuses endWorld's dead parameter slot for callback context.
#pragma optimize("y", off)
// ?Pathfinder::IsGroundLineOnly present-unmatched
Bool Pathfinder::IsGroundLineOnly(const Coord3D *startWorld,
	const Coord3D *endWorld)
{
	return !rva002EADE1(startWorld, endWorld, PATHFIND_LAYER_GROUND,
		(Rva002E7ED6Info *)&endWorld);
}
#pragma optimize("y", on)

// WB 0xD60940 identifies AddToOpenList; retail marks the cell open, then
// appends its pointer through the thiscall helper at 0x002F3738. The queue
// receiver is Pathfinder+0x1D1F0 in the target body.
void Pathfinder::AddToOpenList(PathfindCell *cell)
{
	((PathfindCell *)cell)->rva0052DAE9(true);
	((Rva002F3738 *)((char *)this + 0x1d1f0))->rva002F3738((void **)&cell);
}

// WB 0xD3E820 identifies IsGroundPathPassable. Retail builds callback context
// from this and pathDiameter, then delegates the cell walk to 0x002EED41.
Bool Pathfinder::IsGroundPathPassable(const Coord3D *startWorld,
	PathfindLayerEnum layer, const Coord3D *endWorld, Int pathDiameter)
{
	Rva002E93A7Info info;
	info.m_04 = pathDiameter;
	info.m_00 = this;
	return !rva002EED41(startWorld, endWorld, layer, &info);
}

// WB 0xD4F090 builds the 0x002E7B02 callback context from source and copies
// its adjusted Coord3D back only when the rowed 0x002EB3D7 walk succeeds.
// ?Pathfinder::AdjustGroundPathPosition present-unmatched
Int Pathfinder::AdjustGroundPathPosition(const Coord3D &source,
	Coord3D &destination)
{
	Rva002E7B02 context((Int)this, 4,
		*(const _Rva002E7B02Cell *)&source);
	Int adjusted = rva002EB3D7(&source, &destination, PATHFIND_LAYER_GROUND,
		(Rva002E7B29Info *)&context);
	if (adjusted != 0) {
		destination = *(Coord3D *)((char *)&context + 8);
	}
	return adjusted;
}

// WB 0xD58AF0: after its two debug-only initialization assertions, the wrapper
// forwards isHuman, the LocomotorSet surface mask, obj, from, to, crusher,
// closestOK=true, and adjustedTo to internal_findHierarchicalPath.
Path *Pathfinder::FindClosestHierarchicalPath(Bool isHuman,
	const LocomotorSet &locomotorSet, Object *obj, const Coord3D *from,
	const Coord3D *to, Bool crusher, Coord3D *adjustedTo)
{
	return internal_findHierarchicalPath(isHuman, locomotorSet.getValidSurfaces(),
		obj, from, to, crusher, true, adjustedTo);
}

// WB 0xD588A0 maps this six-argument wrapper to internal_findHierarchicalPath;
// its local Coord3D receives the optional adjusted destination.
Path *Pathfinder::FindHierarchicalPath(Bool isHuman,
	const LocomotorSet &locomotorSet, Object *obj, const Coord3D *from,
	const Coord3D *to, Bool crusher)
{
	Coord3D adjustedTo;
	return internal_findHierarchicalPath(isHuman, locomotorSet.getValidSurfaces(),
		obj, from, to, crusher, false, &adjustedTo);
}

// Pathfinder::IsValidMovementTerrain, retail 0x002E7296 (158 bytes): WB's
// name for Zero Hour's Pathfinder::validMovementTerrain (AIPathfind.cpp),
// whose body this is; the per-type surfaces come from the table instead of
// validLocomotorSurfacesForCellType.
Bool Pathfinder::IsValidMovementTerrain(PathfindLayerEnum layer, const Locomotor *locomotor, const Coord3D *pos)
{
	Int x = realToIntFloor(pos->x * 0.1f);
	Int y = realToIntFloor(pos->y * 0.1f);

	PathfindCell *toCell = getCell(layer, x, y);
	if (toCell == 0)
		return false;
	if (toCell->getType() == PathfindCell::CELL_OBSTACLE) return true;
	if (toCell->getType() == PathfindCell::CELL_IMPASSABLE) return true;
	if (toCell->getLayer() != PathfindCell::LAYER_GROUND && toCell->getType() == PathfindCell::CELL_CLEAR)
		return true;
	// check validity of destination cell
	LocomotorSurfaceTypeMask acceptableSurfaces = g_00DBD33C[toCell->getType()];
	if ((locomotor->getLegalSurfaces() & acceptableSurfaces) == 0)
		return false;
	return true;
}

// Pathfinder_FuncTightenPath::Pathfinder_FuncTightenPath, retail 0x002EE43A
// (97 bytes). Name from WorldBuilder (pathfinder.cpp line 11307,
// wb-name-unverified); fields follow Zero Hour's TightenPathStruct.
Pathfinder_FuncTightenPath::Pathfinder_FuncTightenPath(Pathfinder *pathfinder,
	Object *obj, const LocomotorSet &locomotorSet, PathfindLayerEnum layer,
	const Coord3D &goal)
{
	m_pathfinder = pathfinder;
	m_obj = obj;
	m_locomotorSet = &locomotorSet;
	m_layer = layer;
	copyCoord3D(&m_goal, &goal);
	zeroCoord3D(&m_destPos);
	Rva002EBCA7Split(m_obj, &m_radius, &m_center);
	m_foundDest = false;
}

// Pathfinder::TightenPath, retail 0x002FC95E (83 bytes). Name from
// WorldBuilder (pathfinder.cpp line 11334, wb-name-unverified); Zero Hour's
// Pathfinder::tightenPath with the struct turned into a functor: walks the
// cells from `from` to `to` and moves `from` to the last good position found.
void Pathfinder::TightenPath(Object *obj, const LocomotorSet &locomotorSet,
	Coord3D *from, const Coord3D *to)
{
	Pathfinder_FuncTightenPath info(this, obj, locomotorSet,
		TheTerrainLogic->getLayerForDestination(obj, from), *to);
	rva002F95B7(from, to, info.m_layer, (Rva002F600CInfo *)&info);
	if (info.m_foundDest)
		*from = info.m_destPos;
}

// Pathfinder_IsCheckForMeleeHordeAdjust::Pathfinder_IsCheckForMeleeHordeAdjust,
// retail 0x002ED72B (139 bytes). Name from WorldBuilder (pathfinder.cpp line
// 4570, wb-name-unverified); isHuman/radius/layer follow Zero Hour's
// checkForAdjust setup.
Pathfinder_IsCheckForMeleeHordeAdjust::Pathfinder_IsCheckForMeleeHordeAdjust(
	Pathfinder *pathfinder, Object *obj, void *arg, const Coord3D &goal,
	float range)
{
	m_pathfinder = pathfinder;
	m_obj = obj;
	m_08 = arg;
	m_range = range;
	m_24 = 0;
	copyCoord3D(&m_goal, &goal);
	m_isHuman = (m_obj->getControllingPlayer() && m_obj->getControllingPlayer()->m_playerType == 1) ? 0 : 1;
	Rva002EBCA7Split(m_obj, &m_radius, &m_center);
	m_layer = TheTerrainLogic->getLayerForDestination(obj, &goal);
}

// Pathfinder_IsCheckForAdjust::Pathfinder_IsCheckForAdjust, retail 0x002ED484
// (177 bytes). Name from WorldBuilder (pathfinder.cpp, wb-name-unverified);
// the sibling of Pathfinder_IsCheckForMeleeHordeAdjust, taking its layer
// from the optional second position when one is given.
Pathfinder_IsCheckForAdjust::Pathfinder_IsCheckForAdjust(Pathfinder *pathfinder,
	Object *obj, void *arg, const Coord3D &goal, const Coord3D *layerPos,
	float range, Int arg6)
{
	m_pathfinder = pathfinder;
	m_obj = obj;
	m_08 = arg;
	m_layerPos = layerPos;
	m_range = range;
	m_28 = 0;
	m_2C = arg6;
	copyCoord3D(&m_goal, &goal);
	m_isHuman = (m_obj->getControllingPlayer() && m_obj->getControllingPlayer()->m_playerType == 1) ? 0 : 1;
	Rva002EBCA7Split(m_obj, &m_radius, &m_center);
	m_layer = TheTerrainLogic->getLayerForDestination(obj, &m_goal);
	if (m_layerPos)
		m_layer = TheTerrainLogic->getLayerForDestination(0, m_layerPos);
}

// Pathfinder::CheckForTarget, retail 0x002F2FA4 (123 bytes). Name from
// WorldBuilder (pathfinder.cpp line 9429, wb-name-unverified). When the
// rowed 0x002F1C25 test passes, takes the 0x002EBC59 cell position and keeps
// it in `out` if the weapon probe (range 10) accepts it.
Bool Pathfinder::CheckForTarget(void *obj, void *a2, void *a3,
	Rva002CB35CObj *weapon, void *a5, void *a6, void *a7, void *a8,
	Coord3D *out)
{
	if (bfmeWrapE6E90(obj, a2, a3, (void *)1, a7, a8))
	{
		Coord3D cell;
		Coord3D pos = *(Coord3D *)rva002EBC59(&cell, obj, (Int)a2, (Int)a3, 1);
		if (weapon->rva002CB35C((Int)obj, &pos, a5, a6, 10.0f, 1))
		{
			*out = pos;
			return true;
		}
	}
	return false;
}

// Pathfinder::BuildActualPath, retail 0x002F0596 (249 bytes). Name from
// WorldBuilder (pathfinder.cpp lines 10785..10786, wb-name-unverified); Zero
// Hour's buildActualPath (new Path, prependCells, optimize) with BFME's
// facing hint and final direction pass.
Path *Pathfinder::BuildActualPath(Object *obj, LocomotorSurfaceTypeMask surfaces,
	const Coord3D *fromPos, PathfindCell *goalCell, Bool center, Bool blocked,
	Bool faceDirection)
{
	Path *path = new Path;
	PrependCells(path, fromPos, goalCell, center);
	float facing[2];
	facing[0] = 0.0f;
	facing[1] = 0.0f;
	if (m_1BEB6)
	{
		float orientation = obj->m_orientation;
		float angle = goalCell->rva0052DD75(orientation, 10, 0.5f);
		facing[0] = Cos(angle);
		facing[1] = Sin(angle);
	}
	path->rva00364551(obj, surfaces, blocked, m_1BEB6 ? facing : 0);
	if (faceDirection)
	{
		Coord3D dir = *((const Thing *)obj)->getUnitDirectionVector2D();
		path->rva00365E98(obj, &dir, surfaces, blocked);
	}
	return path;
}

// Pathfinder::MakeHierarchicalPathPassable, retail 0x002F35AF (308 bytes).
// Name from WorldBuilder (pathfinder.cpp lines 10858..10859,
// wb-name-unverified). Records each hop of the node list at +0x1C1CC, then
// builds a hierarchical path over its cells, marking each cell (or, when
// expanding, the 3x3 block of 16-cell zones around it) in the zone manager.
Rva005348AD *Pathfinder::MakeHierarchicalPathPassable(void *, Rva002E6C79 *path, Bool expand)
{
	Rva002E6C79 *node;
	for (node = path; node->next(); node = node->next())
	{
		Rva002F35AFCell *cell = node->m_00;
		if ((cell ? cell->m_0C : 0) && node->next())
		{
			Rva002F35AFHop hop;
			hop.m_zone = (cell ? cell->m_0C : 0)->m_04;
			hop.m_position.x = node->next()->m_00->x;
			hop.m_position.y = node->next()->m_00->y;
			m_1C1CC.push_back(hop);
		}
	}
	Rva005348AD *result = new Rva005348AD;
	for (node = path; node; node = node->next())
	{
		if (expand)
		{
			for (Int dx = -16; dx <= 16; dx += 16)
				for (Int dy = -16; dy <= 16; dy += 16)
					m_zoneManager.rva005314C6(node->m_00->x + dx, node->m_00->y + dy, 1);
		}
		else
		{
			m_zoneManager.rva005314C6(node->m_00->x, node->m_00->y, 1);
		}
		result->rva00534557(node->m_00);
	}
	result->rva00534AAE();
	return result;
}

// Pathfinder::CanApproachToTarget, retail 0x002FA2DC (277 bytes). Name from
// WorldBuilder (pathfinder.cpp lines 4692..4693, callgraph evidence). Probes
// the eight cells around the target at the approach range (150, or the
// weapon's larger 0x002C9B80 range) with the 0x002E9ACC functor along a line
// from the target; true on the first hit. Copying the target through the
// inline Coord3D::set helper (not struct assignment) is what gives retail's
// frame: with `pos = *targetPos` cl keeps the loop counters in memory and
// moves the range out of the dead `obj` home (0.74 -> exact).
Bool Pathfinder::CanApproachToTarget(Object *obj, const Coord3D *targetPos,
	Rva002C9B80Owner *weapon, Bool flag)
{
	char *ai = obj->m_258;
	if (!ai)
		return false;
	float range = 150.0f;
	unsigned char byte = 0;
	if (weapon)
	{
		float weaponRange = weapon->rva002C9B80(obj, 0.0f);
		if (weaponRange > range)
			range = weaponRange;
		byte = weapon->m_04->get();
	}
	Rva002E9ACC functor(this, obj, (Rva002E8BCFSrc const *)(ai + 0x1CC), byte, flag);
	for (Int i = -1; i < 2; i++)
	{
		for (Int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0)
				continue;
			Coord3D pos;
			copyCoord3D(&pos, targetPos);
			pos.x += i * range;
			pos.y += j * range;
			functor.m_1E = 1;
			functor.m_1F = 0;
			iterateCellsAlongLine(targetPos, &pos,
				TheTerrainLogic->getLayerForDestination(0, targetPos),
				(Rva002F4D8BInfo *)&functor);
			if (functor.m_found)
				return true;
		}
	}
	return false;
}

// Retail 0x002EC0A2..0x002EC3CE (812 bytes), exact /O1 /G7 /arch:SSE.
// Identity: WB 0x00D32F30, Pathfinder/pathfinder.cpp assertions 772..851;
// its name, three conflict passes, arrival-time comparison and seven-argument
// thiscall agree with native. The named BFME1 and GeneralsMD AIPathfind source
// has no corresponding method; this is reconstruction from native and WB.
// Layouts and helper bindings above are proved by native loads/call sites,
// independently of WB's debug-only assertions and shifted Object offsets.
// Standard math.h supplies sqrt's compiler declaration; a bare extern makes
// the two x87 result stores interleave with stack cleanup instead of retail.
int Pathfinder::CalcCollisionFreeExtraCosts(Object *object,PathfindCell *parent,Rva002EBC7FPair *destination,PathfindLayerEnum layer,int lower,int upper,bool ignoreReservations)
{
    Rva002EBC7FPair oldMin,oldMax;
    if (parent) {
        PathCollisionInfo *info=reinterpret_cast<PathCollisionCell *>(parent)->info;
        oldMin.x=info->x-lower; oldMin.y=info->y-lower;
        oldMax.x=info->x+upper; oldMax.y=info->y+upper;
    }
    Rva002EBC7FPair minimum,maximum;
    minimum.x=destination->x-lower; minimum.y=destination->y-lower;
    maximum.x=destination->x+upper; maximum.y=destination->y+upper;
    float ourArrival=-1.0f;
    int cost=0;
    for (int x=minimum.x;x<maximum.x;++x) {
        for (int y=minimum.y;y<maximum.y;++y) {
            if (parent && x>=oldMin.x && x<oldMax.x && y>=oldMin.y && y<oldMax.y) continue;
            PathCollisionCell *cell=reinterpret_cast<PathCollisionCell *>(getCell(layer,x,y));
            if (!cell || !cell->info) continue;
            for (PathCollisionNode *node=cell->info->occupants;node;node=node->next) {
                Object *other=node->object;
                if (other==object || other->container==object) continue;
                bool enemies=object->getRelationship(other)==ENEMIES;
                if (!object->getAI() || !other->getAI()) continue;
                if (static_cast<unsigned>(object->getAI()->rva0026417F(enemies))>static_cast<unsigned>(other->getAI()->rva0026417F(enemies))) continue;
                if (other->IsAtGoalPosition()) return -1;
                if (object->getAI()->locomotor && other->getAI()->locomotor) {
                    Coord3D target;
                    rva002EBC7F(&target,object,destination,1);
                    if (ourArrival<0.0f) {
                        float dx=object->position[0]-target.x;
                        float dy=object->position[1]-target.y;
                        Rva001E46E1 *locomotor=object->getAI()->locomotor;
                        float distance=static_cast<float>(sqrt(dy*dy+dx*dx));
                        ourArrival=distance/locomotor->rva001E46E1(object);
                    }
                    float dx=other->position[0]-target.x;
                    float dy=other->position[1]-target.y;
                    Rva001E46E1 *locomotor=other->getAI()->locomotor;
                    float distance=static_cast<float>(sqrt(dy*dy+dx*dx));
                    float otherArrival=distance/locomotor->rva001E46E1(other);
                    if (otherArrival<ourArrival) cost+=4;
                } else cost+=8;
            }
            for (PathCollisionNode *node=cell->info->goals;node;node=node->next) {
                Object *other=node->object;
                if (other==object || other->container==object) continue;
                bool enemies=object->getRelationship(other)==ENEMIES;
                if (!object->getAI() || !other->getAI()) continue;
                if (static_cast<unsigned>(object->getAI()->rva0026417F(enemies))<=static_cast<unsigned>(other->getAI()->rva0026417F(enemies))) return -1;
            }
            if (!ignoreReservations) {
                for (PathCollisionNode *node=cell->info->reservations;node;node=node->next) {
                    Object *other=node->object;
                    if (other==object) continue;
                    bool enemies=object->getRelationship(other)==ENEMIES;
                    if (!object->getAI() || !other->getAI()) continue;
                    if (static_cast<unsigned>(object->getAI()->rva0026417F(enemies))<=static_cast<unsigned>(other->getAI()->rva0026417F(enemies))) return -1;
                }
            }
        }
    }
    return cost;
}

// Retail 0x002EBE54..0x002EC0A2 (590 bytes), exact /O1 /G7 /arch:SSE.
// WB 0x00D32350 names Pathfinder::CalcExtraCosts and asserts oldCell at line635.
// Six-argument ABI, destination bounds, old-cell layer, enemy filtering,
// priority and shifted 4/8 movement costs are established independently by
// native bytes. WB's old-cell overlap expression has mutually exclusive y
// comparisons and is dead; retail emits no overlap exclusion or old bounds.
// No same-named BFME1/GeneralsMD donor method was found. Reconstructed from
// native/WB using the independently verified CalcCollisionFreeExtraCosts
// layouts, priority bool ABI and standard math declaration above.
int Pathfinder::CalcExtraCosts(Object *object,PathfindCell *oldCell,Rva002EBC7FPair *destination,int lower,int upper,bool ignoreEnemies)
{
    if (!oldCell) return 0;
    Rva002EBC7FPair minimum,maximum;
    minimum.x=destination->x-lower; minimum.y=destination->y-lower;
    maximum.x=destination->x+upper; maximum.y=destination->y+upper;
    // The completed radius parameters become the shift and accumulated cost
    // for this stage (native dead homes +0x18 and +0x14). References retain
    // meaningful stage names without losing the verified storage lifetime.
    int &reduction=upper;
    reduction=0;
    if (lower>=4) reduction=2;
    else if (lower>1) reduction=1;
    float ourArrival=-1.0f;
    int &cost=lower;
    cost=0;
    for (int x=minimum.x;x<maximum.x;++x) {
        for (int y=minimum.y;y<maximum.y;++y) {
            PathCollisionCell *cell=reinterpret_cast<PathCollisionCell *>(getCell(static_cast<PathfindLayerEnum>(oldCell->getLayer()),x,y));
            if (!cell || !cell->info) continue;
            for (PathCollisionNode *node=cell->info->occupants;node;node=node->next) {
                Object *other=node->object;
                if (other==object || other->container==object) continue;
                bool enemies=object->getRelationship(other)==ENEMIES;
                if (enemies && ignoreEnemies) continue;
                if (!object->getAI() || !other->getAI()) continue;
                if (static_cast<unsigned>(object->getAI()->rva0026417F(enemies))>static_cast<unsigned>(other->getAI()->rva0026417F(enemies))) continue;
                int amount;
                if (other->IsAtGoalPosition() || !object->getAI()->locomotor || !other->getAI()->locomotor) amount=8;
                else {
                    Coord3D target;
                    rva002EBC7F(&target,object,destination,1);
                    if (ourArrival<0.0f) {
                        float dx=object->position[0]-target.x;
                        float dy=object->position[1]-target.y;
                        Rva001E46E1 *locomotor=object->getAI()->locomotor;
                        float distance=static_cast<float>(sqrt(dy*dy+dx*dx));
                        ourArrival=distance/locomotor->rva001E46E1(object);
                    }
                    float dx=other->position[0]-target.x;
                    float dy=other->position[1]-target.y;
                    Rva001E46E1 *locomotor=other->getAI()->locomotor;
                    float distance=static_cast<float>(sqrt(dy*dy+dx*dx));
                    float otherArrival=distance/locomotor->rva001E46E1(other);
                    if (!(otherArrival<ourArrival)) continue;
                    amount=4;
                }
                cost+=amount>>reduction;
            }
        }
    }
    return cost;
}

// WorldBuilder names this body GetWallHeight (WB 0x00D3ED70). ZH supplies
// the Bridge height/containment semantics, while retail establishes the
// layer selection, ramp handling, four cell-corner probes and ABI.
// Native 0x002EF68C, 636 bytes; bridge head +0x5C, height[layer] +0x1BE78.
float Pathfinder::GetWallHeight(PathfindLayerEnum layer, const Coord3D *pos, Coord3D *normal)
{
    PathfindCell *cell = static_cast<PathfindCell *>(rva001E3647Pos(layer, pos));
    if (cell && layer != PATHFIND_LAYER_GROUND && cell->getLayer() != layer) {
        PathfindLayerEnum actual = static_cast<PathfindLayerEnum>(cell->getLayer());
        if (actual == 16) {
            if (IsPointOnRamp(pos)) layer = actual;
        } else layer = actual;
    }
    if (layer == PATHFIND_LAYER_GROUND)
        return TheTerrainLogic->getGroundHeight(pos->x, pos->y, normal);
    if (static_cast<unsigned char>(Rva002E6E8AGet(layer))) {
        float height = m_wallLayerHeights[layer - 17];
        if (normal) {
            normal->x = 0.0f;
            normal->y = 0.0f;
            normal->z = 1.0f;
        }
        return height;
    }
    if (layer == 16) {
        for (Bridge *bridge = m_bridges; bridge; bridge = bridge->m_next) {
            if (bridge->isPointOnBridge(pos)) {
                PathfindLayerEnum wallLayer = rva002ED236(0, *pos);
                float height = bridge->getBridgeHeight(pos, normal);
                float result;
                if (static_cast<unsigned char>(Rva002E6E8AGet(wallLayer))) {
                    result = reinterpret_cast<Rva002E7482 *>(this)->rva002E7482(wallLayer) > height
                        ? reinterpret_cast<Rva002E7482 *>(this)->rva002E7482(wallLayer) : height;
                } else result = height;
                return result;
            }
        }
        Coord3D corner0 = *pos;
        corner0.x -= 10.0f;
        corner0.y -= 10.0f;
        Coord3D corner1 = corner0;
        corner1.x += 20.0f;
        Coord3D corner2 = corner1;
        corner2.y += 20.0f;
        Coord3D corner3 = corner0;
        corner3.y += 20.0f;
        for (Bridge *bridge = m_bridges; bridge; bridge = bridge->m_next) {
            if (bridge->isPointOnBridge(&corner0) || bridge->isPointOnBridge(&corner1) ||
                bridge->isPointOnBridge(&corner2) || bridge->isPointOnBridge(&corner3)) {
                PathfindLayerEnum wallLayer = rva002ED236(0, *pos);
                float height = bridge->getBridgeHeight(pos, normal);
                float result;
                if (static_cast<unsigned char>(Rva002E6E8AGet(wallLayer))) {
                    result = reinterpret_cast<Rva002E7482 *>(this)->rva002E7482(wallLayer) > height
                        ? reinterpret_cast<Rva002E7482 *>(this)->rva002E7482(wallLayer) : height;
                } else result = height;
                return result;
            }
        }
    }
    return pos->z;
}

// CheckDestination identity is established by the native diagnostic strings;
// Zero Hour checkDestination supplies the cell iteration purpose. BFME2 adds
// horde/narrow-passage radius overrides and a geometry-aware rectangle query.
// Template kind bytes, human extent, AI and containment accesses are retail facts.
Bool Pathfinder::CheckDestination(Object *obj,Int cellX,Int cellY,PathfindLayerEnum layer,
    Int radius,Bool center,Int *out,Bool flag)
{
    PathfinderCheckCoordinates coordinates;
    if (g_00E03745 && g_00DFEFF0) {
        fprintf((PathfinderLogFile *)g_00DFEFF0,
            "          Pathfinder::CheckDestination called with: obj=%s(%d), cell=%d,%d, layer=%d, iRadius=%d, centerInCell=%s",
            obj->m_template->name(), obj->getID(), cellX,cellY,layer,radius,center?"TRUE":"FALSE");
    }
    if (obj->m_template->hasKind(109)) {
        if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          horde");
        if (layer==PATHFIND_LAYER_GROUND && !flag) {
            if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          layer is LAYER_GROUND");
            rva002E79A8((int)&coordinates.point,1,cellX,cellY,1);
            if (((TerrainLogicCheckDestination *)TheTerrainLogic)->slotC8(&coordinates.point)) {
                if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          narrow passage area");
                radius=1; center=true;
            }
        } else {
            if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          layer != LAYER_GROUND, layer=%d",layer);
            radius=1; center=true;
        }
    }
    if (obj->m_template->hasKind(90) && obj->m_template->hasKind(8) && layer!=PATHFIND_LAYER_GROUND) {
        radius=1; center=false;
    }
    Int upper=radius;
    if (center) ++upper;
    if (obj->rva0028AFBB()) {
        if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          human controlled");
        if (cellX-radius<m_extentLowX || cellX+upper>m_extentHighX || cellY-radius<m_extentLowY || cellY+upper>m_extentHighY) {
            if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"            returning false");
            return false;
        }
    }
    Bool aircraft=false;
    Int ignored=0, objectId=0;
    const LocomotorSet *locomotors=0;
    if (obj->getAI()) {
        if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          I have an AI");
        ignored=((const Rva0006E009DwordField *)obj->getAI())->get();
        aircraft=obj->getAI()->isAircraftThatAdjustsDestination();
        objectId=obj->getID();
        locomotors=(const LocomotorSet *)((char *)obj->getAI()+0x1cc);
    }
    *out=0;
    Rva002E7C99 info;
    info.rva002E7C99((int)this,(int)obj,(int)out,0,ignored,flag,(int)locomotors);
    if (!aircraft && obj->m_template->hasKind(186)) {
        ICoord2DBase &position=coordinates.cells.position;
        position.x=cellX;position.y=cellY;
        GeometryShape shape;
        ((const GeometryInfo *)((char *)obj+0xa8))->rva006BD9C0(shape);
        ICoord2DBase &size=coordinates.cells.size;
        size.x=(int)((shape.major*2.0f+4.0f)*0.1f);
        size.y=(int)((shape.minor*2.0f+4.0f)*0.1f);
        void *contain=*(void **)((char *)obj+0x250);
        if (contain && ((PathfinderContain31 *)contain)->slot7C()) {
            Int count=((PathfinderContain28 *)contain)->slot70();
            if (count>0) {
                float fraction=(float)((PathfinderContain69 *)contain)->slot114(0)/count;
                size.x=(int)((size.x-2.0f)*fraction+2.0f);
                size.y=(int)((size.y-2.0f)*fraction+2.0f);
            }
        }
        return !rva002EED80(&position,&size,obj->GetGoalAngle(),layer,(Rva002E9D09 *)&info);
    }
    if (g_00E03745 && g_00DFEFF0) {
        fprintf((PathfinderLogFile *)g_00DFEFF0,"          BEGIN cell iteration (deep innards), i from %d to %d, j from %d to %d",
            cellX-radius,cellX+upper,cellY-radius,cellY+upper);
    }
    for (Int i=cellX-radius;i<cellX+upper;++i) {
        for (Int j=cellY-radius;j<cellY+upper;++j) {
            PathfindCell *cell=getCell(layer,i,j);
            if (!cell) {
                if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          OFF THE MAP, return false: i=%d, j=%d",i,j);
                return false;
            }
            if (aircraft) {
                if (((Rva0052DB4D *)cell)->rva0052DB4D(objectId)) {
                    if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          checkForAircraft=TRUE, return false: i=%d, j=%d",i,j);
                    return false;
                }
            } else if (((Rva002E9D09 *)&info)->rva002E9D09((Object *)cell,0,0)) return false;
        }
    }
    return true;
}

// The 59-byte executable gap between the verified split helper ending BCF6
// and queueForPath at BD31 is a complete constructor ending in RET. Its stores
// reproduce the GeometryShape initialization in CheckDestination, including
// the name and two tail flags. The original owner name is unproven; this
// address-named adapter reuses the independently supported 36-byte shape view.
struct Rva002EBCF6 : GeometryShape { Rva002EBCF6(); };
Rva002EBCF6::Rva002EBCF6() {}

// The native debug draw call sites push coord/float/duration/12-byte color;
// the layer reset call supplies only ECX. Both release bodies fold to the
// existing single RET at B3FD0. Separate full C++ providers preserve their ABIs.
struct PathfinderDebugColor { float red,green,blue; };
void Rva000B3FD0PathDebug(const Coord3D *,float,Int,PathfinderDebugColor);



// Retail 2F0A72..2F0B4D: search cost through the hierarchical waypoint list.
// Native callers 2FA3F1/2FAD13 establish Pathfinder receiver and cell ABI.
// Info +0 begins with x/y; native vector +1C1CC contains 12B (zone,position).
// ZH costToGoal supplies the grid-cost purpose; WB D642F0 shows the unsigned
// accumulator expression and coordinate copy. No donor name is claimed.
Int Pathfinder::rva002F0A72(PathfindCell *cell, PathfindCell *goal)
{
    unsigned int cost = 0;
    Int x = cell->getXIndex(), y = cell->getYIndex();
    for (_STL::vector<Rva002F35AFHop>::iterator it = m_1C1CC.end();
         it != m_1C1CC.begin(); --it)
    {
        PathfinderCostCellInfo point = (it - 1)->m_position;
        Int nx = point.x, ny = point.y;
        Int dx = reinterpret_cast<Int(__cdecl *)(Int)>(ji_00629952)(x - nx);
        Int dy = reinterpret_cast<Int(__cdecl *)(Int)>(ji_00629952)(y - ny);
        if (dx > dy)
            cost = (cost + 14 * dy) + (cost + 10 * (dx - dy));
        else
            cost = (cost + 14 * dx) + (cost + 10 * (dy - dx));
        cost += 1400;
        x = nx;
        y = ny;
    }
    Int dx = reinterpret_cast<Int(__cdecl *)(Int)>(ji_00629952)(x - goal->getXIndex());
    Int dy = reinterpret_cast<Int(__cdecl *)(Int)>(ji_00629952)(y - goal->getYIndex());
    if (dx > dy)
        return 14 * dy + cost + 10 * (dx - dy);
    return 14 * dx + cost + 10 * (dy - dx);
}

// BFME1 clean IterateCircular1 donor at actual reference checkout 9cbfb551.
// Target700B boundary2F92BC..2F9578, WB D6AD60 and native horde-adjust caller
// establish traversal/ABI; callback70E5 is independently rowed. Retail shortens
// the failure literal and keeps all five predicate calls external.
Bool Pathfinder::rva002F92BC(const ICoord2D *scanCenterCell, Int remainingCellBudget, ICoord2D *foundCell, void *adjustTargetInfoData)
{
	if (g_00E03745 && g_00DFEFF0)
	{
		fprintf((PathfinderLogFile *)g_00DFEFF0,
			"\t\tIterateCircular1 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	Rva002F70E5Context *targetSearch = (Rva002F70E5Context *)adjustTargetInfoData;
	if (targetSearch->rva002F70E5(scanCenterCell->x, scanCenterCell->y))
	{
		if (g_00E03745 && g_00DFEFF0)
			fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\tfunc succeeded found=%d,%d", scanCenterCell->x, scanCenterCell->y);
		foundCell->x=scanCenterCell->x;
		foundCell->y=scanCenterCell->y;
		return true;
	}
	if (g_00E03745 && g_00DFEFF0)
		fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\tfunc failed");

	Int bestOffsetDistanceSquared = 0;
	Int ringExtent = 1;
	Int cellOffsetX = 0;
	Int cellOffsetY = 0;

	while (remainingCellBudget > 0)
	{
		remainingCellBudget -= 4 * ringExtent + 2;
		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F70E5(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F70E5(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F70E5(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F70E5(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		if (bestOffsetDistanceSquared == 0)
		{
			ringExtent += 2;
		}
		else
		{
			if (g_00E03745 && g_00DFEFF0)
				fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\tbest return true. found=%d,%d", foundCell->x, foundCell->y);
			return true;
		}
	}

	if (g_00E03745 && g_00DFEFF0)
		fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\ttotal failure. found");
	return false;
}


// BFME1 IterateCircular1 predicate donor 9cbfb551 and retail2F8E2D..2F90E9.
Bool Pathfinder::rva002F8E2D(const ICoord2D *scanCenterCell, Int remainingCellBudget, ICoord2D *foundCell, void *adjustTargetInfoData)
{
	if (g_00E03745 && g_00DFEFF0)
	{
		fprintf((PathfinderLogFile *)g_00DFEFF0,
			"\t\tIterateCircular1 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	Rva002F6F90Context *targetSearch = (Rva002F6F90Context *)adjustTargetInfoData;
	if (targetSearch->rva002F6F90(scanCenterCell->x, scanCenterCell->y))
	{
		if (g_00E03745 && g_00DFEFF0)
			fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\tfunc succeeded found=%d,%d", scanCenterCell->x, scanCenterCell->y);
		foundCell->x=scanCenterCell->x;
		foundCell->y=scanCenterCell->y;
		return true;
	}
	if (g_00E03745 && g_00DFEFF0)
		fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\tfunc failed");

	Int bestOffsetDistanceSquared = 0;
	Int ringExtent = 1;
	Int cellOffsetX = 0;
	Int cellOffsetY = 0;

	while (remainingCellBudget > 0)
	{
		remainingCellBudget -= 4 * ringExtent + 2;
		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		if (bestOffsetDistanceSquared == 0)
		{
			ringExtent += 2;
		}
		else
		{
			if (g_00E03745 && g_00DFEFF0)
				fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\tbest return true. found=%d,%d", foundCell->x, foundCell->y);
			return true;
		}
	}

	if (g_00E03745 && g_00DFEFF0)
		fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\ttotal failure. found");
	return false;
}


// BFME1 IterateCircular2 clean donor 9cbfb551; retail2F90E9..2F92BC.
Bool Pathfinder::rva002F90E9(ICoord2D *scanCenterCell, Int remainingCellBudget, void *adjustTargetInfoData)
{
	if (g_00E03745 && g_00DFEFF0)
	{
		fprintf((PathfinderLogFile *)g_00DFEFF0,
			"\t\tIterateCircular2 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	Rva002F6F90Context *targetSearch = (Rva002F6F90Context *)adjustTargetInfoData;
	if (targetSearch->rva002F6F90(scanCenterCell->x, scanCenterCell->y))
	{
		return true;
	}

	Int bestOffsetDistanceSquared = 0;
	Int ringExtent = 1;
	Int cellOffsetX = 0;
	Int cellOffsetY = 0;

	while (remainingCellBudget > 0)
	{
		remainingCellBudget -= 4 * ringExtent + 2;
		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		if (bestOffsetDistanceSquared == 0)
		{
			ringExtent += 2;
		}
		else
		{
			return true;
		}
	}

	return false;
}

// BFME1 circular1 donor9cbfb551; native boundary and callback ABI.
Bool Pathfinder::rva002EAE5F(const ICoord2D *scanCenterCell, Int remainingCellBudget, ICoord2D *foundCell, void *adjustTargetInfoData)
{
	if (g_00E03745 && g_00DFEFF0)
	{
		fprintf((PathfinderLogFile *)g_00DFEFF0,
			"\t\tIterateCircular1 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	Rva002E7414 *targetSearch = (Rva002E7414 *)adjustTargetInfoData;
	if ((unsigned char)targetSearch->rva002E7414(scanCenterCell->x, scanCenterCell->y))
	{
		if (g_00E03745 && g_00DFEFF0)
			fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\tfunc succeeded found=%d,%d", scanCenterCell->x, scanCenterCell->y);
		foundCell->x=scanCenterCell->x;
		foundCell->y=scanCenterCell->y;
		return true;
	}
	if (g_00E03745 && g_00DFEFF0)
		fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\tfunc failed");

	Int bestOffsetDistanceSquared = 0;
	Int ringExtent = 1;
	Int cellOffsetX = 0;
	Int cellOffsetY = 0;

	while (remainingCellBudget > 0)
	{
		remainingCellBudget -= 4 * ringExtent + 2;
		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if ((unsigned char)targetSearch->rva002E7414(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if ((unsigned char)targetSearch->rva002E7414(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if ((unsigned char)targetSearch->rva002E7414(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if ((unsigned char)targetSearch->rva002E7414(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		if (bestOffsetDistanceSquared == 0)
		{
			ringExtent += 2;
		}
		else
		{
			if (g_00E03745 && g_00DFEFF0)
				fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\tbest return true. found=%d,%d", foundCell->x, foundCell->y);
			return true;
		}
	}

	if (g_00E03745 && g_00DFEFF0)
		fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\ttotal failure. found");
	return false;
}



// BFME1 circular1 donor9cbfb551; native boundary and callback ABI.
Bool Pathfinder::rva002EB11B(const ICoord2D *scanCenterCell, Int remainingCellBudget, ICoord2D *foundCell, void *adjustTargetInfoData)
{
	if (g_00E03745 && g_00DFEFF0)
	{
		fprintf((PathfinderLogFile *)g_00DFEFF0,
			"\t\tIterateCircular1 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	Rva002E7440 *targetSearch = (Rva002E7440 *)adjustTargetInfoData;
	if (targetSearch->rva002E7440(scanCenterCell->x, scanCenterCell->y))
	{
		if (g_00E03745 && g_00DFEFF0)
			fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\tfunc succeeded found=%d,%d", scanCenterCell->x, scanCenterCell->y);
		foundCell->x=scanCenterCell->x;
		foundCell->y=scanCenterCell->y;
		return true;
	}
	if (g_00E03745 && g_00DFEFF0)
		fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\tfunc failed");

	Int bestOffsetDistanceSquared = 0;
	Int ringExtent = 1;
	Int cellOffsetX = 0;
	Int cellOffsetY = 0;

	while (remainingCellBudget > 0)
	{
		remainingCellBudget -= 4 * ringExtent + 2;
		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002E7440(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002E7440(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002E7440(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002E7440(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		if (bestOffsetDistanceSquared == 0)
		{
			ringExtent += 2;
		}
		else
		{
			if (g_00E03745 && g_00DFEFF0)
				fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\tbest return true. found=%d,%d", foundCell->x, foundCell->y);
			return true;
		}
	}

	if (g_00E03745 && g_00DFEFF0)
		fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\ttotal failure. found");
	return false;
}



// BFME1 circular2 donor9cbfb551; native467B target callback forwarder.
Bool Pathfinder::rva002F379E(ICoord2D *scanCenterCell, Int remainingCellBudget, void *adjustTargetInfoData)
{
	if (g_00E03745 && g_00DFEFF0)
	{
		fprintf((PathfinderLogFile *)g_00DFEFF0,
			"\t\tIterateCircular2 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	Rva002F336AOwner *targetSearch = (Rva002F336AOwner *)adjustTargetInfoData;
	if (targetSearch->rva002F336A(scanCenterCell->x, scanCenterCell->y))
	{
		return true;
	}

	Int bestOffsetDistanceSquared = 0;
	Int ringExtent = 1;
	Int cellOffsetX = 0;
	Int cellOffsetY = 0;

	while (remainingCellBudget > 0)
	{
		remainingCellBudget -= 4 * ringExtent + 2;
		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F336A(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F336A(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F336A(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F336A(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		if (bestOffsetDistanceSquared == 0)
		{
			ringExtent += 2;
		}
		else
		{
			return true;
		}
	}

	return false;
}



// BF1 checkPathCost from clean PathfinderStepD4F90 donor9cbfb551; native
// 2F5C7A..2F600C RET16 and WB D5F9F0 independently name CheckPathCost.
Int Pathfinder::CheckPathCost(Object *obj,const LocomotorSet &locomotorSet,const Coord3D *from,const Coord3D *rawTo)
{
 if(!m_isMapReady)return 0;
 const Int MAX_COST=0x7fff0000;
 Int cellCount=0;
 Coord3D adjustTo;copyCoord3D(&adjustTo,rawTo);
 PathfindLayerEnum goalLayer=TheTerrainLogic->getLayerForDestination(obj,&adjustTo);
 PathfindCell *goal=rva002E8BF8(goalLayer,&adjustTo);
 if(!goal)return MAX_COST;
 Bool center;Int radius;Rva002EBCA7Split(obj,&radius,(unsigned char *)&center);
 PathfindCell *parent;
 {
 ICoord2D start;Rva002E7875WorldToCell(&start,true,from);
 PathfindLayerEnum fromLayer=TheTerrainLogic->getLayerForDestination(obj,from);
 parent=(PathfindCell *)rva001E3647Pos(fromLayer,from);
 if(!parent)return MAX_COST;
 {
 ICoord2D end;ICoord2D *ep=Rva002E7875WorldToCell(&end,true,&adjustTo);
 goal->allocateInfo((In002E6BA1 *)ep);
 if(parent!=goal)parent->allocateInfo((In002E6BA1 *)&start);
 }
 }
 Int priority=obj->m_template->priority;Bool flag=obj->m_template->flag;
 Rva002E8BCF info((const Rva002E8BCFSrc *)&locomotorSet,!flag,priority-1,obj->rva0028AFBB());
 if(!((Rva002E6DC4 *)this)->rva002E6DC4(&info,parent)) {parent->ReleaseInfo();goal->ReleaseInfo();return MAX_COST;}
 parent->StartPathfind((Int)goal);
 parent->m_pathInfo->totalCost=(unsigned short)rva002F0A72(parent,goal);
 AddToOpenList(parent);
 while((parent=rva002F36E5())!=0) {
  parent->PutOnClosedList(&m_closedList);
  if(parent==goal) {Int cost=parent->m_pathInfo->totalCost;m_isTunneling=false;rva002F40E7();return cost;}
  if(cellCount>500)continue;
  CheckChangeLayers(parent,obj);
  static Int deltaX[]={1,0,-1,0,1,-1,-1,1};
  static Int deltaY[]={0,1,0,-1,1,1,-1,-1};
  const Int adjacent[5]={0,1,2,3,0};
  Bool neighborFlags[8]={false,false,false,false,false,false,false};
  for(Int i=0;i<8;++i) {
   neighborFlags[i]=false;
   ICoord2D coords={parent->getXIndex()+deltaX[i],parent->getYIndex()+deltaY[i]};ICoord2D next=coords;
   
   PathfindCell *neighbor=getCell((PathfindLayerEnum)parent->getLayer(),next.x,next.y);
   if(!neighbor)continue;
   if((unsigned char)((Rva002E6AF3 *)neighbor)->get() || (unsigned char)((Rva002E6B06 *)neighbor)->rva002E6B06())continue;
   if(i>=4 && !neighborFlags[adjacent[i-4]] && !neighborFlags[adjacent[i-3]])continue;
   if(!((Rva002E6DC4 *)this)->rva002E6DC4(&info,neighbor))continue;
   neighborFlags[i]=true;neighbor->allocateInfo((In002E6BA1 *)&next);++cellCount;
   Int cost=neighbor->CalcCostSoFar((const Rva002E6C79 *)parent);
   cost+=CalcExtraCosts(obj,parent,(Rva002EBC7FPair *)&next,radius,radius+(center?1:0),true);
   neighbor->m_pathInfo->flags&=~1U;
   neighbor->SetParentCell((Int *)parent);
   neighbor->m_pathInfo->costSoFar=(unsigned short)cost;
   Int remaining=rva002F0A72(neighbor,goal);
   neighbor->m_pathInfo->totalCost=(unsigned short)(neighbor->m_pathInfo->costSoFar+remaining);
   AddToOpenList(neighbor);
  }
 }
 m_isTunneling=false;rva002F40E7();goal->ReleaseInfo();return MAX_COST;
}

// Same-TU callees of GetHordeUnitPath. Retail compiled the cell-info pool
// helpers (0x002E8B7A, 0x002E6BA1) and the ICoord2D equality body in this
// unit: with the bodies visible the cell indices passed to them are not
// escaped, so startCellNdx/goalCellNdx/newCellCoord share retail's frame slots.
extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)
extern int TheMixFileInfoCount;

// Rehomed 0x002E6BA1 (65 B), original Rva002E6BA1Init.cpp: initializer
// copying the cell position plus the owner at +0x30, zeroing +0x08/+0x0C,
// the cost words and +0x14 x5, masking +0x2C, zeroing +0x28, counting.
class Rva002E6BA1
{
public:
	void rva002E6BA1(int a, In002E6BA1 *b);

private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	unsigned short m_10;
	unsigned short m_12;
	int m_14[5];
	int m_28;
	int m_2C;
	int m_30;
};

void Rva002E6BA1::rva002E6BA1(int a, In002E6BA1 *b)
{
	m_30 = a;
	m_00 = b->x;
	m_04 = b->y;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_12 = 0;
	memset(m_14, 0, 20);
	m_2C &= 0xffffffe0;
	m_28 = 0;
	++TheMixFileInfoCount;
}

class MixFileInfoBuffer
{
private:
	void bfmeUnlink();
	friend class Rva002E6BA1;
public:
	friend MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, Int a, In002E6BA1 *in);
};

// Rehomed 0x002E8B7A (33 B), original Rva002E8B7AInit.cpp: takes the pool
// head, unlinks it (0x002E6BE2) and initializes it for the cell (0x002E6BA1).
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, Int a, In002E6BA1 *in)
{
	MixFileInfoBuffer *node = *pp;
	node->bfmeUnlink();
	((Rva002E6BA1 *)node)->rva002E6BA1(a, in);
	return node;
}

// ICoord2D::operator== (0x00004CAD, owner icoord.cpp): the header inline
// retail kept out of line under /O1; only its visibility matters here.
inline bool ICoord2D::operator==(const ICoord2DBase &that) const
{
	return x == that.x && y == that.y;
}

// Pathfinder::GetHordeUnitPath, retail 0x002F6075 (1128 bytes) RET 8. WorldBuilder
// D61920 names it (pathfinder.cpp:11593-11641); caller micropathToPosition
// 0x0026412B. A 200-cell bounded A* from the object cell to the destination
// cell, shaped like CheckPathCost above.
Path *Pathfinder::GetHordeUnitPath(Object *obj, const Coord3D *destination)
{
	m_ignoreObstacleID = (ObjectID)0;
	Bool centerInCell = Rva002EBBFBIsOdd(obj);
	const Coord3D *objPos = (const Coord3D *)obj->position;
	ICoord2D startCellNdx;
	{
		Coord3D from;
		from.x = objPos->x;
		from.y = objPos->y;
		from.z = objPos->z;
		// 0x002E7917 through its hidden-result ABI, writing startCellNdx in place.
		typedef void (Pathfinder::*CellOut)(ICoord2D *, bool, const Coord3D *);
		(this->*reinterpret_cast<CellOut>(&Pathfinder::Rva002E7917))(&startCellNdx, centerInCell, &from);
	}
	ICoord2D goalCellNdx;
	Rva002E7875WorldToCell(&goalCellNdx, centerInCell, destination);
	if (startCellNdx == *(const ICoord2DBase *)&goalCellNdx)
		return 0;

	Int priority = obj->m_template->priority;
	Bool flag = obj->m_template->flag;
	char *ai = obj->m_258;
	Rva002E8BCF info((const Rva002E8BCFSrc *)(ai + 0x1cc), !flag, priority - 1, obj->rva0028AFBB());
	PathfindLayerEnum destinationLayer = TheTerrainLogic->getLayerForDestination(obj, destination);
	PathfindCell *goalCell = getCell(destinationLayer, goalCellNdx.x, goalCellNdx.y);
	if (!goalCell)
		return 0;
	if (!((Rva002E6DC4 *)this)->rva002E6DC4(&info, goalCell))
		return 0;
	PathfindLayerEnum layer = (PathfindLayerEnum)obj->rva0028B511();
	PathfindCell *parentCell = getCell(layer, startCellNdx.x, startCellNdx.y);
	if (!parentCell)
		return 0;

	goalCell->allocateInfo((In002E6BA1 *)&goalCellNdx);
	parentCell->allocateInfo((In002E6BA1 *)&startCellNdx);
	parentCell->StartPathfind((Int)goalCell);
	parentCell->m_pathInfo->totalCost = (unsigned short)rva002F0A72(parentCell, goalCell);
	AddToOpenList(parentCell);

	Int cellCount = 0;
	for (parentCell = rva002F36E5(); parentCell != 0; parentCell = rva002F36E5())
	{
		if (parentCell == goalCell)
		{
			Path *path = new Path;
			PrependCells(path, objPos, goalCell, centerInCell);
			path->wordC = 1;
			rva002F40E7();
			goalCell->ReleaseInfo();
			return path;
		}
		parentCell->PutOnClosedList(&m_closedList);
		if (cellCount > 200)
			break;
		CheckChangeLayers(parentCell, obj);

		static Int deltaX[] = {1, 0, -1, 0, 1, -1, -1, 1};
		static Int deltaY[] = {0, 1, 0, -1, 1, 1, -1, -1};
		const Int adjacent[5] = {0, 1, 2, 3, 0};
		Bool neighborFlags[8];
		for (Int i = 0; i < 8; ++i)
		{
			neighborFlags[i] = false;
			Int newX = parentCell->getXIndex() + deltaX[i];
			Int newY = parentCell->getYIndex() + deltaY[i];
			ICoord2D newCellCoord;
			newCellCoord.x = newX;
			newCellCoord.y = newY;
			PathfindCell *newCell = getCell((PathfindLayerEnum)parentCell->getLayer(), newX, newY);
			if (!newCell)
				continue;
			if ((unsigned char)((Rva002E6B06 *)newCell)->rva002E6B06())
				continue;
			if ((unsigned char)((Rva002E6AF3 *)newCell)->get())
				continue;
			if (newCell->getLayer() != parentCell->getLayer()
				&& newCell->getLayer() != parentCell->getConnectLayer()
				&& newCell->getConnectLayer() != parentCell->getLayer()
				&& !(parentCell->getConnectLayer() == 16 && newCell->getConnectLayer() == parentCell->getConnectLayer()))
				continue;
			if (i >= 4 && !neighborFlags[adjacent[i - 4]] && !neighborFlags[adjacent[i - 3]])
				continue;
			if (!((Rva002E6DC4 *)this)->rva002E6DC4(&info, newCell))
			{
				newCell->allocateInfo((In002E6BA1 *)&newCellCoord);
				newCell->PutOnClosedList(&m_closedList);
				continue;
			}
			neighborFlags[i] = true;
			if (!newCell->m_pathInfo)
				cellCount++;
			newCell->allocateInfo((In002E6BA1 *)&newCellCoord);
			Int newCostSoFar = newCell->CalcCostSoFar((const Rva002E6C79 *)parentCell);
			Int dx = abs(newX - goalCell->getXIndex());
			Int dy = abs(newY - goalCell->getYIndex());
			if (newCell->rvaBit16() && dx + dy > 3)
				newCostSoFar += 10;
			newCell->m_pathInfo->flags &= ~1U;
			Int costRemaining = rva002F0A72(newCell, goalCell);
			if (newCell->getType() == PathfindCell::CELL_OBSTACLE)
				newCostSoFar += 1000;
			newCell->m_pathInfo->costSoFar = (unsigned short)newCostSoFar;
			newCell->SetParentCell((Int *)parentCell);
			newCell->m_pathInfo->totalCost = newCell->m_pathInfo->costSoFar + costRemaining;
			AddToOpenList(newCell);
		}
	}
	rva002F40E7();
	goalCell->ReleaseInfo();
	return 0;
}

// Pathfinder::AdjustDestination, retail [0x002FCFCF,0x002FD344) RET16, 885
// bytes. WorldBuilder D43BA0 names Pathfinder::AdjustDestination (assert
// lines 4455..4457); clean BFME1 PathfinderAdjustDestination003F6090 (donor
// 9cbfb551) supplies the semantic and control spine. Target facts: projectile
// kind bit 25, water kind bit 191 through TerrainLogic slot 0x4C, layer-height
// slot 0x1C, kind mask 0x4000 on template word 0x108 selecting the layer, the
// spiral search budget at TheWritableGlobalData+0x11F0, the found-cell copy
// through Rva002E8C4DCall, and the tighten/cost group check.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct PathfinderSearchRadiusView { char pad[0x11F0]; Int searchRadius; };
static __forceinline Coord3D adjustCellCenter(bool center,Rva002E8C23Pair *cell,PathfindLayerEnum layer) {
	Coord3D pos;return *(Coord3D *)Rva002E8C4DCall((int)&pos,center,cell,layer);
}
static __forceinline Bool findAdjustedCell(Pathfinder *finder,ICoord2D *cell,Bool center,Coord3D *dest,Pathfinder_IsCheckForAdjust *info) {
	ICoord2D found={0,0};
	if(!finder->rva002F8E2D(cell,((const PathfinderSearchRadiusView *)TheWritableGlobalData)->searchRadius,&found,info))return false;
	if(g_00E03745 && g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"  got %d,%d",found.x,found.y);
	*dest=adjustCellCenter(center,(Rva002E8C23Pair *)&found,info->m_layer);return true;
}
Bool Pathfinder::AdjustDestination(Object *obj,const LocomotorSet &locomotorSet,Coord3D *dest,const Coord3D *groupDest)
{
	if(g_00E03745 && g_00DFEFF0)
		fprintf((PathfinderLogFile *)g_00DFEFF0,"  Pathfinder::AdjustDestination() onEnter dest=%g,%g,%g",dest->x,dest->y,dest->z);
	if(obj->m_template->hasKind(25)) {
		if(g_00E03745 && g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"  projectile return TRUE");
		return true;
	}
	Bool center=Rva002EBBFBIsOdd(obj);
	ICoord2D cell;Rva002E7875WorldToCell(&cell,center,dest);
	if(g_00E03745 && g_00DFEFF0)
		fprintf((PathfinderLogFile *)g_00DFEFF0,"  AdjDest obj=%i, dest=%g,%g,%g, center=%i",obj->getID(),dest->x,dest->y,dest->z,center?1:0);
	PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(obj,dest);
	float height=0.0f;
	if(groupDest)height=groupDest->z;
	else if(!obj->m_template->hasKind(191) || !((TerrainLogicWaterQuery *)TheTerrainLogic)->slot4C(dest->x,dest->y,&height,0,0))
		height=TheTerrainLogic->getLayerHeight(dest->x,dest->y,layer,0,true);
	Pathfinder_IsCheckForAdjust info(this,obj,(void *)&locomotorSet,*dest,groupDest,height,(*(const unsigned int *)obj->m_template->kinds & 0x4000)?layer:PATHFIND_LAYER_UNKNOWN);
	if(findAdjustedCell(this,&cell,center,dest,&info)) {
		Bool badGroup=false;
		if(groupDest) {
			if(g_00E03745 && g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"        groupDest tighten path case...");
			TightenPath(obj,locomotorSet,dest,groupDest);
			Int cost=CheckPathCost(obj,locomotorSet,groupDest,dest);
			Int dx=(Int)fabs(groupDest->x-dest->x);
			Int dy=(Int)fabs(groupDest->y-dest->y);
			Int distance=dx+dy;
			if(distance*1.4f<cost) {
				badGroup=true;
				if(g_00E03745 && g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"        badGroup = true in tighten case");
			}
		}
		if(!badGroup)return true;
	}
	if(info.m_28) {
		if(g_00E03745 && g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"  got with allies %d,%d",info.fallback.x,info.fallback.y);
		*dest=adjustCellCenter(center,&info.fallback,info.m_layer);return true;
	}
	if(groupDest) {
		if(g_00E03745 && g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"  IterateCircular with groupDest");
		return rva002F90E9(&cell,((const PathfinderSearchRadiusView *)TheWritableGlobalData)->searchRadius,&Pathfinder_IsCheckForAdjust(this,obj,(void *)&locomotorSet,*dest,0,dest->z,info.m_2C));
	}
	if(g_00E03745 && g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"  got NOTHING");
	return false;
}

extern float g_00BC7838;
struct PathfinderCellPoint : Coord3D {
	__forceinline PathfinderCellPoint() {}
	__forceinline PathfinderCellPoint(const PathfinderCellPoint &o) { x = o.x; y = o.y; z = o.z; }
	__forceinline ~PathfinderCellPoint() {}
};
// 0x002E79A8 (186 B): the cell-to-world centre, WorldBuilder D4DC20 (Zero
// Hour's adjustCoordToCell returning the point): the cell corner plus a half
// cell (centred) or a small inset, scaled by the cell size; ground cells take
// the water height when there is water, else the layer height.
PathfinderCellPoint rva002E79A8(Bool centerInCell, Int cellX, Int cellY, PathfindLayerEnum layer)
{
	PathfinderCellPoint pos;
	if (centerInCell) {
		pos.x = ((float)cellX + 0.5f) * 10.0f;
		pos.y = ((float)cellY + 0.5f) * 10.0f;
	} else {
		pos.x = ((float)cellX + g_00BC7838) * 10.0f;
		pos.y = ((float)cellY + g_00BC7838) * 10.0f;
	}
	if (layer != PATHFIND_LAYER_GROUND || !((TerrainLogicWaterQuery *)TheTerrainLogic)->slot4C(pos.x, pos.y, &pos.z, 0, 0))
		pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, layer, 0, true);
	return pos;
}
// 0x002E8C23 (42 B): a cell's centre point, returned through the hidden pointer.
// In-TU so PatchPath's cell centre stays unescaped and shares goalPos's slot.
PathfinderCellPoint Rva002E8C23Call(Bool centerInCell, PathfindCell *cell)
{
	return rva002E79A8(centerInCell, cell->getXIndex(), cell->getYIndex(), (PathfindLayerEnum)cell->getLayer());
}
void Pathfinder::PrependCells(Path *path,const Coord3D *fromPos,PathfindCell *goalCell,Bool center)
{
 Coord3D pos;
 PathfindCell *cell,*prevCell=0;
 Bool goalCellNull=(goalCell->getParentCell()==0);
 for(cell=goalCell;cell->getParentCell();cell=cell->getParentCell()) {
  pos=Rva002E8C23Call(center,cell);
  if(prevCell && cell->getXIndex()==prevCell->getXIndex() && cell->getYIndex()==prevCell->getYIndex()) {
   PathfindLayerEnum layer=(PathfindLayerEnum)cell->getLayer();
   if(layer==PATHFIND_LAYER_GROUND)layer=(PathfindLayerEnum)prevCell->getLayer();
   path->firstNode->layer=layer;continue;
  }
  Bool canOptimize=true;
  if(cell->getType()==2) {
   if(prevCell && prevCell->getType()!=2) {if(path->firstNode)path->firstNode->canOptimize=false;}
  } else {if(prevCell && prevCell->getType()==2)canOptimize=false;}
  if(cell->getParentWaypoint()) {
   Waypoint *parent=cell->getParentWaypoint();
   Int id=parent->id;pos=parent->location;
   if(id!=0x7fffffff) {
    if(cell->waypoint) {
     if(path->firstNode){path->firstNode->portalID=cell->waypoint->id;path->firstNode->canOptimize=false;}
     path->rva00265596(&cell->waypoint->location,(PathfindLayerEnum)cell->getLayer(),0x7fffffff);
    }
    Waypoint *link=cell->getParentWaypoint()->chainNext;
    while(link) {
     if(path->firstNode){path->firstNode->portalID=link->id;path->firstNode->canOptimize=false;}
     path->rva00265596(&link->location,(PathfindLayerEnum)cell->getLayer(),0x7fffffff);
     if(link->linkCount!=0)break;
     link=link->chainNext;
    }
    if(path->firstNode){path->firstNode->portalID=id;path->firstNode->canOptimize=false;}
   }
  }
  path->rva00265596(&pos,TheTerrainLogic->getLayerForDestination(0,&pos),0x7fffffff);
  path->firstNode->canOptimize=canOptimize;
  if(cell->m_pathInfo->flags&1)path->blockedByAlly=true;
  if(prevCell)prevCell->m_pathInfo->parent=0;
  prevCell=cell;
 }
 if(cell && cell->m_pathInfo) {
  if(goalCellNull) {pos=Rva002E8C23Call(center,cell);path->rva00265596(&pos,(PathfindLayerEnum)cell->getLayer(),0x7fffffff);}
  if(fromPos->x!=path->firstNode->position.x || fromPos->y!=path->firstNode->position.y)
   path->rva00265596(fromPos,(PathfindLayerEnum)cell->getLayer(),0x7fffffff);
 }
}

PathfindCell *Pathfinder::rva002F068F(){PathfindCell *cell=0;if(!m_openCells.empty())cell=m_openCells.front();return cell;}
// Semantic source: BFME1 verified donor0bef414b, AIPathfind.cpp getAircraftPath.
// Target facts: WB D31B00 and native2F3971..2F3B6B RET8; AI+258,
// locomotor+1F0 and appearance3; node pool, ctor, prepend and debug providers.
// Unlike the donor, retail replaces current->next three times without moving
// the cursor to the middle inserted node. Preserve that observed behavior.
// The 48-byte local scratch aggregate describes compiler storage only; its
// start/p3 union reproduces dead-start reuse proved by the retail stack accesses.
class Rva00065964ObjectPool { public: void *rva002635C2() throw(); };
extern Rva00065964ObjectPool g_pathNodePool;
template<int N> class AircraftSlots:public AircraftSlots<N-1>{public:virtual void slot(AircraftSlots<N>*);};
template<> class AircraftSlots<0>{};
struct AircraftLocomotorTemplate { char prefix[0x74];int appearance; };
struct AircraftLocomotor { void *vtable; AircraftLocomotorTemplate *data; };
class AircraftAIView:public AircraftSlots<109>{
public:
 virtual unsigned avoidObject();
 char prefix04[0x1f0-4]; AircraftLocomotor *locomotor;
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;
class AI;
extern AI *TheAI;
struct PathfinderAircraftAIView { char prefix[0x10]; Pathfinder *pathfinder; };
static __forceinline PathNode *makeAircraftNode(const Coord3D *p) {
 void *memory=g_pathNodePool.rva002635C2();
 return memory?new(memory)PathNode(p,PATHFIND_LAYER_GROUND):0;
}
static __forceinline void appendAircraftNode(PathNode *current,PathNode *node) {
 current->next=node;
 if(node) node->previous=current;
}
Path *Pathfinder::GetAircraftPath(const Object *object,const Coord3D *to)
{
 Path *path=new Path;
 AircraftAIView *ai=reinterpret_cast<AircraftAIView *>(object->getAI());
 unsigned avoid=0;
 if(ai) avoid=ai->avoidObject();
 bool clips=false;
 if(ai && ai->locomotor && ai->locomotor->data->appearance==3) clips=true;
 // Local scratch only: retain the target-proven relative homes, not a retail class layout.
 struct { Coord3D p1,p2; union { Coord3D start; Coord3D p3; } stage; Coord3D adjusted; } scratch;
 scratch.adjusted.x=to->x; scratch.adjusted.y=to->y; scratch.adjusted.z=to->z;
 if(clips) rva002E9BE5(reinterpret_cast<const Coord3D *>(object->position),to,100.0f,avoid,&scratch.adjusted);
 path->rva00265596(&scratch.adjusted,PATHFIND_LAYER_GROUND,0x7fffffff);
 // Native start-coordinate storage is later reused for the third detour output.
 scratch.stage.start.x=object->position[0]; scratch.stage.start.y=object->position[1]; scratch.stage.start.z=to->z;
 path->rva00265596(&scratch.stage.start,PATHFIND_LAYER_GROUND,0x7fffffff);
 int limit=20;
 for(PathNode *node=path->firstNode;node && node->next;) {
  if(rva002F3392(node,node->next,avoid,&scratch.p1,&scratch.p2,&scratch.stage.p3)) {
   appendAircraftNode(node,makeAircraftNode(&scratch.stage.p3));
   appendAircraftNode(node,makeAircraftNode(&scratch.p2));
   appendAircraftNode(node,makeAircraftNode(&scratch.p1));
  }
  node=node->next;
  if(--limit<0) break;
 }
 for(PathNode *node=path->firstNode;node && node->next;node=node->next) node->nextOptimized=node->next;
 path->wordC=true;
 if(*(int *)((char *)TheWritableGlobalData+0x9b8)==1) reinterpret_cast<PathfinderAircraftAIView *>(TheAI)->pathfinder->SetDebugPath((Rva002EDEABArg *)path);
 return path;
}

// WB D3AF90 and native2EC8C3..2EC9E1 identify the sixteen-ID goal-node query.
// BFME1 donor0bef PathfinderRva003E5E40 demonstrates visible provider bodies
// for output escape analysis. These three current BFME2 providers are exact
// here; keeping calls out of line lets MSVC reuse dead radius/cell slots.
class PathfinderOverlapTerrainView:public PathfinderNativeSlots<44> { public: virtual bool objectInteractsWithBridgeLayer(Object *,int); };
int Rva002E6E6CGet(int);
extern int g_Va00DFECD0;
ICoord2D *Rva002EBC14Cell(ICoord2D *,void *,const Coord3D *);
void Rva002EBCD6Split(void *,int *,int *);
int Pathfinder::_GetOverlapUnits(Object *object,const Coord3D *position,int *out)
{
 ICoord2D cell;
 int below,above;
 int layers[2];
 Rva002EBC14Cell(&cell,object,position);
 Rva002EBCD6Split(object,&below,&above);
 layers[0]=object->rva0028B511();
 int numLayers=1;
 if (!(unsigned char)Rva002E6E6CGet(layers[0]) && reinterpret_cast<PathfinderOverlapTerrainView *>(TheTerrainLogic)->objectInteractsWithBridgeLayer(object,layers[0])) {
  layers[1]=1; numLayers=2;
 }
 int count=0;
 ++g_Va00DFECD0;
 object->rva002E6B89();
 for(int x=cell.x-below;x<cell.x+above;++x) {
  for(int y=cell.y-below;y<cell.y+above;++y) {
   for(int k=0;k<numLayers;++k) {
    PathCollisionCell *c=reinterpret_cast<PathCollisionCell *>(getCell((PathfindLayerEnum)layers[k],x,y));
    if(c && c->info) {
     for(PathCollisionNode *node=c->info->goals;node;node=node->next) {
      if(node->object->rva002E6B89()) continue;
      out[count++]=node->object->getID();
      if(count==16) return count;
     }
    }
   }
  }
 }
 return count;
}



// Rehomed canonical converter: original PathfindShimWorldToCell.cpp,162B.
// Reuses this TU's existing floor/fistp codegen helper; no new asm is added.
static const float PATHFINDER_CELL_INV = 1.0f / 10.0f;
__declspec(noinline) ICoord2D* __cdecl Rva002E7875WorldToCell(ICoord2D* out, bool center, const Coord3D* pos)
{
	int ix;
	int iy;
	if (center) {
		ix = realToIntFloor(pos->x * PATHFINDER_CELL_INV);
		iy = realToIntFloor(pos->y * PATHFINDER_CELL_INV);
	} else {
		ix = realToIntFloor(pos->x * PATHFINDER_CELL_INV + 0.5f);
		iy = realToIntFloor(pos->y * PATHFINDER_CELL_INV + 0.5f);
	}
	out->x = ix;
	out->y = iy;
	return out;
}

//
// ?Rva002EBC14Cell@@YAPAUICoord2D@@PAU1@PAXPBUCoord3D@@@Z, retail 0x002EBC14 (32 bytes).
// Free __cdecl (ICoord2D*, void*, const Coord3D*) -> ICoord2D*: odd = IsOdd(p),
// WorldToCell(out, odd, pos), return out. Evidence: retail pushes pos then p,
// calls IsOdd, pops p dead into ecx (ecx never read, so not __thiscall),
// pushes eax/out, calls WorldToCell, reloads out into eax, caller-cleans 0xc.
// Callees: the rowed parity test 0x002EBBFB (Rva002EBBFBIsOdd.cpp, rowed with
// an unsigned char result) and the converter rehomed above.
// Retail passes the parity result straight on with no test/setne, so it is
// a bool here, through the bool spelling pinned at the same address; the
// parity body compiles identically under either result type.
struct ICoord2D;
struct Coord3D;
struct ICoord2D *__cdecl Rva002E7875WorldToCell(struct ICoord2D *out, bool center, const struct Coord3D *pos);
bool __cdecl Rva002EBBFBIsOdd(void *p);

__declspec(noinline) struct ICoord2D *__cdecl Rva002EBC14Cell(struct ICoord2D *out, void *p, const struct Coord3D *pos)
{
	Rva002E7875WorldToCell(out, Rva002EBBFBIsOdd(p), pos);
	return out;
}

// ?Rva002EBCD6Split@@YAXPAXPAH1@Z @0x002EBCD6 32B unlock 9 callers
// Evidence: sibling Split at 0x002EBCA7 in Rva002EBBFBIsOdd.cpp; retail calls rowed Get then cdq-sub-sar half store then remainder store.
int __cdecl Rva002E9B31Get(void *p);
__declspec(noinline) void __cdecl Rva002EBCD6Split(void *p, int *outHalf, int *outRest)
{
	int v = Rva002E9B31Get(p);
	int h = v / 2;
	*outHalf = h;
	*outRest = v - h;
}

// WB D3B2A0 / native2EC9E1..2ECAFF: list+14, unique IDs, capacity16.
int Pathfinder::GetOverlapGoalUnits(Object *object,const Coord3D *position,int *out)
{
 ICoord2D cell;
 int below,above;
 int layers[2];
 Rva002EBC14Cell(&cell,object,position);
 Rva002EBCD6Split(object,&below,&above);
 layers[0]=object->rva0028B511();
 int numLayers=1;
 if (!(unsigned char)Rva002E6E6CGet(layers[0]) && reinterpret_cast<PathfinderOverlapTerrainView *>(TheTerrainLogic)->objectInteractsWithBridgeLayer(object,layers[0])) {
  layers[1]=1; numLayers=2;
 }
 int count=0;
 ++g_Va00DFECD0;
 object->rva002E6B89();
 for(int x=cell.x-below;x<cell.x+above;++x) {
  for(int y=cell.y-below;y<cell.y+above;++y) {
   for(int k=0;k<numLayers;++k) {
    PathCollisionCell *c=reinterpret_cast<PathCollisionCell *>(getCell((PathfindLayerEnum)layers[k],x,y));
    if(c && c->info) {
     for(PathCollisionNode *node=c->info->occupants;node;node=node->next) {
      if(node->object->rva002E6B89()) continue;
      out[count++]=node->object->getID();
      if(count==16) return count;
     }
    }
   }
  }
 }
 return count;
}

// WB D3B5B0 / native2ECAFF..2ECC0D: self skipped; same horde1, other2.
int Pathfinder::CountOverlapHordeGoalUnits(Object *object,const Coord3D *position)
{
 if (!object->container) return 0;
 ICoord2D cell;
 int below,above;
 int layers[2];
 Rva002EBC14Cell(&cell,object,position);
 Rva002EBCD6Split(object,&below,&above);
 layers[0]=object->rva0028B511();
 int numLayers=1;
 if (!(unsigned char)Rva002E6E6CGet(layers[0]) && reinterpret_cast<PathfinderOverlapTerrainView *>(TheTerrainLogic)->objectInteractsWithBridgeLayer(object,layers[0])) {
  layers[1]=1; numLayers=2;
 }
 int count=0;
 for(int x=cell.x-below;x<cell.x+above;++x) {
  for(int y=cell.y-below;y<cell.y+above;++y) {
   for(int k=0;k<numLayers;++k) {
    PathCollisionCell *c=reinterpret_cast<PathCollisionCell *>(getCell((PathfindLayerEnum)layers[k],x,y));
    if(c && c->info) {
     for(PathCollisionNode *node=c->info->hordeGoalNodes;node;node=node->next) {
      if(node->object==object) continue;
      if(node->object->container==object->container) ++count;
      else count+=2;
     }
    }
   }
  }
 }
 return count;
}


// WB D3B920 / native2F133C..2F14F9: perimeter query, up to16 unique IDs.
extern GameLogic *TheGameLogic;
int Pathfinder::_GetAdjacentUnits(Object *object,const Coord3D *position,int *out)
{
 ICoord2D cell;
 int below,above;
 int layers[2];
 Rva002EBC14Cell(&cell,object,position);
 Rva002EBCD6Split(object,&below,&above);
 layers[0]=object->rva0028B511();
 int numLayers=1;
 if (!(unsigned char)Rva002E6E6CGet(layers[0]) && reinterpret_cast<PathfinderOverlapTerrainView *>(TheTerrainLogic)->objectInteractsWithBridgeLayer(object,layers[0])) {
  layers[1]=1; numLayers=2;
 }
 int count=0;
 ++g_Va00DFECD0;
 object->rva002E6B89();
 for(int x=cell.x-below-1;x<cell.x+above+1;++x) {
  int step=(x==cell.x-below-1 || x==cell.x+above)?1:below+above+1;
  for(int y=cell.y-below-1;y<cell.y+above+1;y+=step) {
   for(int k=0;k<numLayers;++k) {
    PathCollisionCell *c=reinterpret_cast<PathCollisionCell *>(getCell((PathfindLayerEnum)layers[k],x,y));
    if(c && c->info) {
     for(PathCollisionNode *node=c->info->goals;node;node=node->next) {
      if(node->object->rva002E6B89()) continue;
      out[count++]=node->object->getID();
      if(count==16) return count;
     }
     if(!c->info->goals) {
      Object *fallback=TheGameLogic->findObjectByID((ObjectID)(c->info?c->info->fallbackID:0));
      if(fallback && !fallback->rva002E6B89()) {
       out[count++]=fallback->getID();
       if(count==16) return count;
      }
     }
    }
   }
  }
 }
 return count;
}


// Native2F477E..2F4ABF RET16 full835. ZH clientSafeQuickDoesPathExist
// supplies terrain-zone reachability; BFME2-specific object status, template
// priority, surface override, complete diagnostics and waypoint-zone fallback
// are reconstructed independently from this target. Caller ABI/pin retained.
struct Rva002CECAETarget;
void Rva002CECAEAppend(Rva002CECAETarget *,const char *,...);
class Rva0028B984ByteField {public:unsigned char get()const;};
Bool Pathfinder::QuickDoesPathExist(Object *obj,const Coord3D *from,const Coord3D *to,Int overrideSet)
{
 if(g_00E03745 && g_00DFEFF0) Rva002CECAEAppend((Rva002CECAETarget *)g_00DFEFF0,
  "\t\t  Pathfinder::QuickDoesPathExist() called with: obj=%s(%d), from=%g,%g,%g, to=%g,%g,%g",
  ((const AsciiString *)((const char *)obj->m_template+0x64))->str(),obj->getID(),from->x,from->y,from->z,to->x,to->y,to->z);
 if(obj->testStatus(QuickStatus49)) {
  if(g_00E03745 && g_00DFEFF0)Rva002CECAEAppend((Rva002CECAETarget *)g_00DFEFF0,"\t\t  Pathfinder::QuickDoesPathExist() Failure 1");return false;
 }
 if(((Rva0028B984ByteField *)obj)->get()==1) {
  if(g_00E03745 && g_00DFEFF0)Rva002CECAEAppend((Rva002CECAETarget *)g_00DFEFF0,"\t\t  Pathfinder::QuickDoesPathExist() Success 1");return true;
 }
 LocomotorSet *set;
 char *ai=obj->m_258;
if(!overrideSet && !ai) {if(g_00E03745 && g_00DFEFF0)Rva002CECAEAppend((Rva002CECAETarget *)g_00DFEFF0,"\t\t  Pathfinder::QuickDoesPathExist() Failure 2");return false;} if(overrideSet)set=(LocomotorSet *)overrideSet;else set=(LocomotorSet *)(ai+0x1CC);
 if(!(set->getValidSurfaces()&0x8F)) {
  if(g_00E03745 && g_00DFEFF0)Rva002CECAEAppend((Rva002CECAETarget *)g_00DFEFF0,"\t\t  Pathfinder::QuickDoesPathExist() Failure 3");return false;
 }
 PathfindLayerEnum destinationLayer=TheTerrainLogic->getLayerForDestination(obj,to);
 PathfindLayerEnum fromLayer=TheTerrainLogic->getLayerForDestination(obj,from);
 PathfindCell *parent=rva002E8BF8(fromLayer,from);
 PathfindCell *goal=rva002E8BF8(destinationLayer,to);
 if(goal->getType()==2) {
  if(g_00E03745 && g_00DFEFF0)Rva002CECAEAppend((Rva002CECAETarget *)g_00DFEFF0,"\t\t  Pathfinder::QuickDoesPathExist() Failure 4");return false;
 }
 Bool terrain=false;Int priority=obj->m_template->priority;Bool flag=obj->m_template->flag;
 Rva002E8BCF info((const Rva002E8BCFSrc *)set,!flag,priority-1,obj->rva0028AFBB());
 Rva002E99F9Sub460 *zones=(Rva002E99F9Sub460 *)&m_zoneManager;
 Int zone1=zones->rva0053241F(&info,parent->quickZone());
 if(parent->getType()==4)terrain=true;
 Int zone2=zones->rva0053241F(&info,goal->quickZone());
 if(goal->getType()==4)terrain=true;
 if(terrain) {
  zone1=zones->rva00531FD4(&info,parent->quickZone());
  zone1=zones->rva0053241F(&info,(unsigned short)zone1);
  zone1=zones->rva00531FD4(&info,(unsigned short)zone1);
  zone2=zones->rva00531FD4(&info,goal->quickZone());
  zone2=zones->rva0053241F(&info,(unsigned short)zone2);
  zone2=zones->rva00531FD4(&info,(unsigned short)zone2);
 }
 if(!IsValidMovementPositionForObject(to,destinationLayer,set->getValidSurfaces(),obj)) {
  if(g_00E03745 && g_00DFEFF0)Rva002CECAEAppend((Rva002CECAETarget *)g_00DFEFF0,"\t\t  Pathfinder::QuickDoesPathExist() Failure 5");return false;
 }
 if(zone1==zone2) {
  if(g_00E03745 && g_00DFEFF0)Rva002CECAEAppend((Rva002CECAETarget *)g_00DFEFF0,"\t\t  Pathfinder::QuickDoesPathExist() Success 2");return true;
 }
 if(g_00E03745 && g_00DFEFF0)Rva002CECAEAppend((Rva002CECAETarget *)g_00DFEFF0,"\t\t  Pathfinder::QuickDoesPathExist() Default Exit");
 return rva002F4115(obj,zone1,zone2,(LocomotorSet *)overrideSet);
}

// Native 0x002F52A7..0x002F57E6, RET52. WB D58CF0 identifies
// Pathfinder::CheckForAdjust; ZH checkForAdjust is the semantic guide.
// Retail adds diagnostic logging, layer-footprint and original-Z checks.
Bool Pathfinder::CheckForAdjust(Object *obj, const LocomotorSet &loco,
 Bool isHuman, Int cellX, Int cellY, PathfindLayerEnum layer, Int radius,
 Bool center, Coord3D *dest, const Coord3D *groupDest, float originalZ,
 Int *options, Int onlyIfLayer)
{
 if (g_00E03745 && g_00DFEFF0)
  fprintf((PathfinderLogFile *)g_00DFEFF0,
   "\t\t  Pathfinder::CheckForAdjust called with: obj=%s(%d), loco=%s, isHuman=%s, cell=%d,%d, layer=%d, iRadius=%d, center=%s, groupDest=%g,%g,%g, originalZ=%g, onlyIfLayer=%d",
   ((const AsciiString *)((const char *)obj->m_template+0x64))->str(),obj->getID(),
   ((const AsciiString *)((const char *)&loco+0x18))->str(),isHuman?"TRUE":"FALSE",
   cellX,cellY,layer,radius,center?"TRUE":"FALSE",
   groupDest?groupDest->x:-1.0f,groupDest?groupDest->y:-1.0f,groupDest?groupDest->z:-1.0f,
   originalZ,onlyIfLayer);
 PathfindCell *cell=getCell(layer,cellX,cellY);
 if (!cell) {
  if(g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"        cellP is NULL, return FALSE.");
  return false;
 }
 if(cell->getType()==2) {
  if(g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"        cellP is CLIFF, return FALSE.");
  return false;
 }
 if(isHuman) {
  if(g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"        isHuman is TRUE");
  if(cellX<m_extentLowX || cellY<m_extentLowY || cellX>m_extentHighX || cellY>m_extentHighY) {
   if(g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"        cell %d,%d is outside m_logicalExtent lo:%d,%d hi:%d,%d",cellX,cellY,m_extentLowX,m_extentLowY,m_extentHighX,m_extentHighY);
   return false;
  }
 }
 if(!CheckDestination(obj,cellX,cellY,layer,radius,center,options,false)) {
  if(g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"        CheckDestination failed, return false");
  return false;
 }
 if(g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"        CheckDestination passed");
 Coord3D temporary;
 Coord3D adjustDest=*(Coord3D *)rva002EBC59(&temporary,obj,cellX,cellY,cell->getLayer());
 if(!obj->m_template->hasKind(12)) {
  if(g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"        object is not kindof aircraft");
  if(onlyIfLayer) {
   if(g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"        onlyIfLayer=%d",onlyIfLayer);
   Int extraRadius=radius;
   if(center)extraRadius=radius+1;
   for(Int i=cellX-radius;i<cellX+extraRadius;++i) {
    for(Int j=cellY-radius;j<cellY+extraRadius;++j) {
     PathfindCell *ground=getCell((PathfindLayerEnum)onlyIfLayer,i,j);
     if(!ground || ground->getLayer()!=onlyIfLayer) {
      if(g_00E03745) {
       if(ground) {
        if(g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"        ground unit failed iteration: i=%d, j=%d, cell=VALID, cellLayer=%d, onlyIfLayer",i,j,ground->getLayer(),onlyIfLayer);
       } else {
        if(g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"        ground unit failed iteration: i=%d, j=%d, cell=NULL, onlyIfLayer",i,j,onlyIfLayer);
       }
      }
      return false;
     }
    }
   }
  }
  if(originalZ>0.0f && fabs(adjustDest.z-originalZ)>50.0f) {
   if(g_00E03745 && g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"        MinasTirith check failed, return FALSE: originalZ=%g, adjustDest.z=%g",originalZ,adjustDest.z);
   return false;
  }
  Bool adjustedPathExists=QuickDoesPathExist(obj,(const Coord3D *)obj->position,&adjustDest,0);
  if(g_00E03745 && g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"        adjustedPathExists=%s",adjustedPathExists?"TRUE":"FALSE");
  if(!QuickDoesPathExist(obj,(const Coord3D *)obj->position,dest,0)) {
   if(g_00E03745 && g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"        QuickDoesPathExist1 fails. Try adjusted destination");
   if(QuickDoesPathExist(obj,dest,&adjustDest,0)) {
    if(g_00E03745 && g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"        QuickDoesPathExist2 succeeds. adjustedPathExists");
    adjustedPathExists=true;
   }
  } else {
   if(g_00E03745 && g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"        QuickDoesPathExist1 succeeds");
  }
  if(!adjustedPathExists) {
   if(g_00E03745 && g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"        returning false because adjustedPathExists is false");
   return false;
  }
 }
 if(g_00E03745 && g_00DFEFF0)fprintf((PathfinderLogFile *)g_00DFEFF0,"        dest calculated to be %g,%g,%g and returning true",adjustDest.x,adjustDest.y,adjustDest.z);
 *dest=adjustDest;
 return true;
}

// Pathfinder::AdjustHordeMeleeDestination, retail 0x002FA202 (218 bytes).
// Name from WorldBuilder (pathfinder.cpp line 4599, wb-name-unverified);
// Zero Hour's checkForAdjust purpose with the melee/horde functor: searches
// around dest's cell for one the functor accepts (else the functor's
// fallback cell at +0x1C when +0x24 is set) and moves dest there. The
// spiral-search budget lives at TheWritableGlobalData+0x11F4. The middle
// parameter travels opaquely into the functor's void* slot (callers pass
// the AI's LocomotorSet); spelling it void* keeps this TU free of the AI
// header the sibling AdjustDestination needs.
struct PathfinderHordeMeleeRadiusView { char pad[0x11F4]; Int searchRadius; };
static __forceinline Bool findHordeMeleeCell(Pathfinder *finder,const ICoord2D *cell,Bool center,Coord3D *dest,Pathfinder_IsCheckForMeleeHordeAdjust *info) {
	ICoord2D found={0,0};
	if(!finder->rva002F92BC(cell,((const PathfinderHordeMeleeRadiusView *)TheWritableGlobalData)->searchRadius,&found,info))return false;
	*dest=adjustCellCenter(center,(Rva002E8C23Pair *)&found,info->m_layer);return true;
}
Bool Pathfinder::AdjustHordeMeleeDestination(Object *obj,void *arg,Coord3D *dest)
{
	if(obj->m_template->hasKind(25))return true;
	Bool center=Rva002EBBFBIsOdd(obj);
	ICoord2D cell;Rva002E7875WorldToCell(&cell,center,dest);
	Pathfinder_IsCheckForMeleeHordeAdjust info(this,obj,arg,*dest,TheTerrainLogic->getLayerHeight(dest->x,dest->y,TheTerrainLogic->getLayerForDestination(obj,dest),0,true));
	if(findHordeMeleeCell(this,&cell,center,dest,&info))return true;
	if(info.m_24){*dest=adjustCellCenter(center,&info.m_1C,info.m_layer);return true;}
	return false;
}
// Pathfinder::InternalFindPath, retail [0x002FBBEB,0x002FC95E) RET24, 3443
// bytes. WorldBuilder D55050 names it (its "CritterDesync" log strings and the
// pathfinder.cpp asserts); the A* spine is Zero Hour's internalFindPath. BFME
// adds the CRC log, the KindOf 186 forward goal offset and its retry from the
// unshifted goal, the checkForMovement destination probes, the mine-shaft
// redirect, the hierarchical-path closest-cell fallback and the early give-up
// distance. The 9-argument neighbour expansion 0x002F83F5 is Zero Hour's
// examineNeighboringCells call shape (unnamed in WorldBuilder).
struct TCheckMovementInfo
{
	ICoord2D cell;					// +0x00
	PathfindLayerEnum layer;		// +0x08
	Int radius;						// +0x0C
	Bool centerInCell;				// +0x10
	Bool m_11;
	unsigned char m_pad12[2];
	unsigned int m_14;				// +0x14 option bits
	ObjectID m_18;					// +0x18 an object to ignore
	unsigned char m_1C[0x10];		// +0x1C the mover's Rva002E8BCF
	Int m_2C;
	Bool m_30,m_31,m_32;
	unsigned char m_pad33;
	Int m_34;
};
class Rva002E6FDF
{
public:
	Rva002E6FDF *rva002E6FDF();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	unsigned char m_10;
	unsigned char m_11;
	char m_pad12[2];
	int m_14;
	int m_18;
	int m_1C;
	unsigned char m_20;
	unsigned char m_21;
	char m_pad22[2];
	int m_24;
	unsigned char m_28;
	char m_pad29[3];
	int m_2C;
	unsigned char m_30;
	unsigned char m_31;
	unsigned char m_32;
	char m_pad33[1];
	int m_34;
};
class HierarchicalPath { public: Int lookUpPositionOnPath(const Coord3D *); };
struct PathfinderCellLimitView { char pad[0x1210]; unsigned int maxCells; };
extern Int PathfinderSearchCellsVisited;	// 0x00DFF0CC, also cleared by FindSafePath
// A cell centre temporary passed on by address.
static __forceinline Coord3D *cellPointArg(const PathfinderCellPoint &p) { return (Coord3D *)&p; }
// A Bool argument travels as its whole stack dword (push dword ptr [bool]).
static __forceinline void *boolArg(const Bool &value) { return *(void *const *)&value; }
static __forceinline Bool pathfinderLogOn() { return g_00E03745 && g_00DFEFF0; }
static __forceinline void pathfinderLog(const char *text) { fprintf((PathfinderLogFile *)g_00DFEFF0,text); }
// Coord2D::Rotate(float) inlined: the CRT pair runs, then fsincos replaces it.
static __forceinline void rotateOffset(float &x, float &y, float angle)
{
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);
	__asm
	{
		fld angle
		fsincos
		fstp cosine
		fstp sine
	}
	float rotated = x * cosine - y * sine;
	y = y * cosine + x * sine;
	x = rotated;
}
static __forceinline void setInfoCell(TCheckMovementInfo &info, ICoord2D c) { info.cell = c; }
static __forceinline void setInfoCellYX(TCheckMovementInfo &info, ICoord2D c) { info.cell.y = c.y; info.cell.x = c.x; }
// 0x002E75A3 (304 B), rehomed from AI/PathfinderRva002E75A3.cpp: retail compiles
// it in this object, so InternalFindPath's &clipFrom/&adjustTo stay local.
#include "../../../../Libraries/Include/Lib/IRegion2D.h"
bool __cdecl ClipLine2D(ICoord2D *p1, ICoord2D *p2, ICoord2D *c1, ICoord2D *c2, IRegion2D *clipRegion);
extern float g_00BC7838;
// Retail floors through math.h's float overload (floor(float) -> floorf), not
// realToIntFloor's direct double call: the extra inline level moves a pop ecx.
static __forceinline float clipCellFloor(float f)
{
	return floor(f);
}
static __forceinline long clipCellRound(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
void Pathfinder::rva002E75A3(Coord3D *a, Coord3D *b)
{
	ICoord2D p2;
	ICoord2D p1;
	IRegion2D *clip = (IRegion2D *)&m_clampLo;
	ICoord2D c2;
	ICoord2D c1;
	p1.x = clipCellRound(clipCellFloor(a->x * PATHFINDER_CELL_INV));
	p1.y = clipCellRound(clipCellFloor(a->y * PATHFINDER_CELL_INV));
	p2.x = clipCellRound(clipCellFloor(b->x * PATHFINDER_CELL_INV));
	p2.y = clipCellRound(clipCellFloor(b->y * PATHFINDER_CELL_INV));
	if (!ClipLine2D(&p1, &p2, &c1, &c2, clip))
		return;
	float base = g_00BC7838;
	if (p1.x != c1.x || p1.y != c1.y) {
		a->x = (float)(c1.x * 10) + base;
		a->y = (float)(c1.y * 10) + base;
	}
	if (p2.x != c2.x || p2.y != c2.y) {
		b->x = (float)(c2.x * 10) + base;
		b->y = (float)(c2.y * 10) + base;
	}
}
// 0x002E6FDF (59 B), rehomed from Rva002E6FDFClear.cpp.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
Rva002E6FDF *Rva002E6FDF::rva002E6FDF()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_11 = 0;
	m_14 = 0;
	m_18 = 0;
	_ReadWriteBarrier();
	m_24 = -1;
	m_1C = 0;
	m_20 = 0;
	m_21 = 0;
	m_28 = 0;
	m_2C = 0;
	m_31 = 0;
	m_32 = 0;
	m_30 = 0;
	m_34 = 0;
	return this;
}

// 0x002E6DC4 (168 B), rehomed from Rva002E6DC4Check.cpp: retail compiles it in
// this object, so &info.m_1C handed to it from checkForMovement stays local.
struct Rva002E6DC4_P1
{
	unsigned int m_0;
	unsigned char m_4;
	unsigned char m_5;
	char m_pad6[2];
	int m_8;
	unsigned char m_C;
};
struct Rva002E6DC4_P2Inner
{
	char m_pad[0x28];
	void *m_28;
};
struct Rva002E6DC4_P2
{
	Rva002E6DC4_P2Inner *m_0;
	char m_pad4[8];
	unsigned int m_C;
};
bool Rva002E6DC4::rva002E6DC4(void *a_raw, void *b_raw)
{
	Rva002E6DC4_P1 *a = (Rva002E6DC4_P1 *)a_raw;
	Rva002E6DC4_P2 *b = (Rva002E6DC4_P2 *)b_raw;
	if (!b)
		return false;
	unsigned int flags = b->m_C;
	unsigned char b18 = (unsigned char)(flags >> 18);
	if ((b18 & 1) != 0 && a->m_5 != 0)
		return false;
	unsigned int low = flags & 0xF;
	switch (low) {
	case 3:
		if ((flags & 0x3F0) != 0x10)
			return false;
		break;
	case 4: {
		void *chase = b->m_0 ? b->m_0->m_28 : 0;
		if (chase == m_48)
			return true;
		break;
	}
	default:
		break;
	}
	if ((a->m_0 & g_00DBD33C[low]) == 0)
		return false;
	unsigned char b17 = (unsigned char)(flags >> 17);
	if (a->m_4 != 0 && (b17 & 1) != 0)
		return false;
	if (a->m_C != 0) {
		unsigned char b22 = (unsigned char)(flags >> 22);
		if (((b22 & 1) == 0) && low == 4)
			return false;
	}
	int v = a->m_8;
	if (v < 0 || (int)((flags >> 19) & 3) <= v)
		return true;
	return false;
}
// 0x002EA34A (782 B), rehomed from PathfinderCheckForMovement.cpp.
class StateMachine
{
public:
	Object *getGoalObject();
};
struct CheckMovementAIView
{
	unsigned char m_pad00[0x30];
	StateMachine *m_stateMachine;	// +0x30
};
struct CheckMovementObjectNode
{
	CheckMovementObjectNode *m_next;
	int m_04;
	Object *m_object;	// +0x08
};
struct CheckMovementCellInfo
{
	unsigned char m_pad00[0x14];
	int m_14;
	unsigned char m_pad18[0x20 - 0x18];
	CheckMovementObjectNode *m_objects;	// +0x20
};
struct CheckMovementCell
{
	Int getType() const { return m_flags & 0xf; }
	Int getLayer() const { return (m_flags >> 4) & 0x3f; }
	Bool rvaBit18() const { return (Bool)((m_flags >> 18) & 1); }
	Bool rvaInfo14() const { return m_info ? m_info->m_14 != 0 : false; }
	Bool hasObjects() const { return m_info ? m_info->m_objects != 0 : false; }
	CheckMovementObjectNode *getObjects() const { return m_info ? m_info->m_objects : 0; }

	CheckMovementCellInfo *m_info;
	unsigned char m_pad04[0x0C - 0x04];
	unsigned int m_flags;	// +0x0C
};
static __forceinline void checkCellFlags(Pathfinder *pf, Object *obj, CheckMovementCell *cell, TCheckMovementInfo &info)
{
	if (cell->getType() == 5)
		info.m_34++;
	if (cell->rvaBit18() && obj->rva0028AFBB())
		info.m_34++;
	if (info.m_14 & 8)
	{
		Int layer = cell->getLayer();
		if (info.layer != layer)
		{
			if (info.layer == 1 && layer != 0x10)
				info.m_34++;
			else if ((unsigned char)Rva002E6E8AGet(info.layer) && layer != 0x10)
				info.m_34++;
		}
	}
	if ((info.m_14 & 4) && !((Rva002E6DC4 *)pf)->rva002E6DC4(info.m_1C, cell))
		info.m_34++;
}
static __forceinline Bool checkCellUnits(Object *obj, CheckMovementCell *cell, TCheckMovementInfo &info, ObjectID *lastID)
{
	if (cell->rvaInfo14())
		info.m_32 = true;

	for (CheckMovementObjectNode *node = cell->getObjects(); node; node = node->m_next)
	{
		Object *unit = node->m_object;
		if (unit == obj)
			continue;
		if (unit->getID() == info.m_18)
			continue;
		if (unit->getID() == *lastID)
			continue;
		*lastID = (ObjectID)unit->getID();

		Bool check = false;
		Bool isAlly;
		if (cell->hasObjects())
		{
			isAlly = obj->getRelationship(unit) == ALLIES;
			if (isAlly)
				info.m_31 = true;
			if (info.m_11)
				check = true;
			if (!isAlly && (info.m_14 & 0x10))
				check = true;
		}
		if (unit->IsAtGoalPosition())
		{
			isAlly = obj->getRelationship(unit) == ALLIES;
			check = true;
		}
		if (!check)
			continue;

		if (isAlly && obj->m_template->testKindWord(0x74) && unit->m_template->testKindWord(0x74))
			continue;
		if (obj->m_template->testKindWord(0x7D) && unit->m_template->testKindWord(8))
			continue;
		if (isAlly && obj->m_template->testKindWord(0xBA) && !unit->m_template->testKindWord(0xBA))
		{
			info.m_32 = false;
			continue;
		}
		if (obj->m_template->testKindWord(0xBB))
		{
			info.m_32 = false;
			continue;
		}

		if (isAlly)
		{
			if (!unit->getAI())
				return false;
			if (info.m_14 & 2)
				return false;
			info.m_2C = 1;
			if (unit->m_template->testKindWord(0xBA) && !obj->m_template->testKindWord(0xBA))
				return false;
			continue;
		}

		if (obj->canCrushOrSquishNoAlly(unit, 2))
			continue;
		if (!(info.m_14 & 0x11))
			continue;
		AIUpdateInterface *ai = obj->getAI();
		if (!ai)
			return false;
		Object *goal = ((CheckMovementAIView *)ai)->m_stateMachine->getGoalObject();
		if (goal)
		{
			if (unit == goal || unit->container == goal)
				continue;
			goal = goal->container;
			if (goal && (unit == goal || unit->container == goal))
				continue;
		}
		Object *victim = ai->getCurrentVictim();
		if (!victim)
			return false;
		if (unit == victim || unit->container == victim)
			continue;
		victim = victim->container;
		if (!victim)
			return false;
		if (unit == victim || unit->container == victim)
			continue;
		return false;
	}
	return true;
}
static __forceinline Bool checkCell(Pathfinder *pf, Object *obj, CheckMovementCell *cell, TCheckMovementInfo &info, ObjectID *lastID)
{
	checkCellFlags(pf, obj, cell, info);
	return checkCellUnits(obj, cell, info, lastID);
}
Bool Pathfinder::checkForMovement(Object *obj, TCheckMovementInfo &info)
{
	info.m_2C = 0;
	info.m_31 = false;
	info.m_32 = false;
	info.m_30 = false;
	info.m_34 = 0;

	Int numCellsAbove = info.radius;
	if (info.centerInCell)
		numCellsAbove++;

	ObjectID lastID = (ObjectID)0;
	for (Int i = info.cell.x - info.radius; i < info.cell.x + numCellsAbove; i++)
	{
		for (Int j = info.cell.y - info.radius; j < info.cell.y + numCellsAbove; j++)
		{
			CheckMovementCell *cell = (CheckMovementCell *)getCell(info.layer, i, j);
			if (!cell)
				return false;
			if (!checkCell(this, obj, cell, info, &lastID))
				return false;
		}
	}
	return true;
}
static __forceinline void readMoverInfo(TCheckMovementInfo &info, Object *obj)
{
	char *ai = obj->m_258;
	info.m_18 = ai ? (ObjectID)((const Rva0006E009DwordField *)ai)->get() : (ObjectID)0;
}
struct Gen_p12pod {Int a[3];};
// 0x002E7964 (68 B), rehomed from AI/Rva002E7964BoundedWorldToCell.cpp: the
// world-to-cell conversion bounded by the cell extent at +0x14 (x = -1 outside).
class Rva002E7964 {
public:
 void rva002E7964(ICoord2D*,unsigned char,const Coord3D*);
 char pad[0x14];IRegion2D extent;
};
void Rva002E7964::rva002E7964(ICoord2D *out,unsigned char center,const Coord3D *pos){
 ICoord2D tmp;
 typedef ICoord2D *(__cdecl *CellCall)(ICoord2D*,unsigned char,const Coord3D*);
 reinterpret_cast<CellCall>(Rva002E7875WorldToCell)(&tmp,center,pos);
 if(tmp.x<extent.lo.x || tmp.y<extent.lo.y || tmp.x>extent.hi.x || tmp.y>extent.hi.y)tmp.x=-1;
 *(out?out:out)=tmp;
}
// 0x001E3647 (50 B), rehomed from Common/PathfinderRva001E3647.cpp: the cell
// under a world position, NULL outside the extent. Defined ahead of PatchPath:
// cl then sees goalPos does not escape and hoists its initial loads (y first).
void *Pathfinder::rva001E3647Pos(int layer, const Coord3D *pos)
{
	ICoord2D tmp;
	((Rva002E7964 *)this)->rva002E7964(&tmp, 1, pos);
	void *cell = 0;
	if (tmp.x >= 0)
		cell = getCell((PathfindLayerEnum)layer, tmp.x, tmp.y);
	return cell;
}
struct PathfinderPatchLimitView { char pad[0x120C]; unsigned int maxCells; };
Path *Pathfinder::PatchPath(Object *obj,const LocomotorSet &locomotorSet,Path *originalPath,Bool blocked)
{
	if (!originalPath) return 0;
	Bool centerInCell;
	Int radius;
	Rva002EBCA7Split(obj, &radius, (unsigned char *)&centerInCell);
	Bool isHuman = true;
	if (obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType == 1) isHuman = false;
	_STL::vector<Gen_p12pod> *hops = (_STL::vector<Gen_p12pod> *)&m_1C1CC;
	hops->erase(hops->begin(), hops->end());
	m_zoneManager.rva00531300();
	unsigned int cellCount = 0;
	Coord3D currentPosition;
	copyCoord3D(&currentPosition, (const Coord3D *)obj->position);
	ICoord2D startCellNdx;
	Rva002E7875WorldToCell(&startCellNdx, true, (const Coord3D *)obj->position);
	PathfindCell *parentCell = rva002E8BF8((PathfindLayerEnum)obj->rva0028B511(), &currentPosition);
	if (!parentCell) return 0;
	if (!obj->m_258) return 0;
	m_isTunneling = false;
	parentCell->allocateInfo((In002E6BA1 *)&startCellNdx);
	parentCell->StartPathfind(0);
	AddToOpenList(parentCell);
	PathNode *startNode;
	PathfindCell *candidateGoal;
	{
	Coord3D goalPos;
	copyCoord3D(&goalPos, &(originalPath->lastNode)->position);
	float dx = goalPos.x - currentPosition.x;
	float dy = goalPos.y - currentPosition.y;
	float goalDeltaSqr = dx*dx + dy*dy;
	ICoord2D cellCoord;
	for (startNode = originalPath->lastNode; startNode != originalPath->firstNode; startNode = startNode->previous) {
		Rva002E7875WorldToCell(&cellCoord, true, &startNode->position);
		TCheckMovementInfo info;
		((Rva002E6FDF *)&info)->rva002E6FDF();
		info.cell = cellCoord;
		info.layer = startNode->layer;
		info.centerInCell = centerInCell;
		info.radius = radius;
		info.m_11 = blocked;
		Int cx = cellCoord.x - startCellNdx.x;
		Int cy = cellCoord.y - startCellNdx.y;
		if (cx < -2 || cx > 2) info.m_11 = false;
		if (cy < -2 || cy > 2) info.m_11 = false;
		info.m_14 = (obj->m_template->testKindWord(90) ? 1U : 16U) | 2U;
		readMoverInfo(info, obj);
		if (!checkForMovement(obj, info)) break;
		float nx = startNode->position.x - currentPosition.x;
		float ny = startNode->position.y - currentPosition.y;
		float dist = nx*nx + ny*ny;
		if (dist < goalDeltaSqr) { goalPos = startNode->position; goalDeltaSqr = dist; }
	}
	if (startNode == originalPath->lastNode) { rva002F40E7(); return 0; }
	candidateGoal = (PathfindCell *)rva001E3647Pos(1, &goalPos);
	candidateGoal->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&cellCoord, true, &goalPos));
	}
	PathfinderSearchCellsVisited = 0;
	while ((parentCell = rva002F36E5()) != 0) {
		PathfinderCellPoint cellCenter = Rva002E8C23Call(centerInCell, parentCell);
		PathNode *matchNode;
		Bool found = false;
		for (matchNode = originalPath->lastNode; matchNode != startNode; matchNode = matchNode->previous) {
			if (cellCenter.x == matchNode->position.x && cellCenter.y == matchNode->position.y) { found = true; break; }
		}
		if (found) {
			m_isTunneling = false;
			Path *path = new Path;
			for (PathNode *node = originalPath->lastNode; node != matchNode; node = node->previous)
				path->rva00265596(&node->position, node->layer, 0x7FFFFFFF);
			PrependCells(path, (const Coord3D *)obj->position, parentCell, centerInCell);
			path->rva00364551(obj, locomotorSet.getValidSurfaces(), blocked, 0);
			rva002F40E7();
			parentCell->ReleaseInfo();
			candidateGoal->ReleaseInfo();
			return path;
		}
		parentCell->PutOnClosedList(&m_closedList);
		if (cellCount < ((const PathfinderPatchLimitView *)TheWritableGlobalData)->maxCells) {
			CheckChangeLayers(parentCell, obj);
			cellCount += rva002F83F5(parentCell, 0, locomotorSet, isHuman, centerInCell, radius, &startCellNdx, obj, 0);
		}
	}
	m_isTunneling = false;
	rva002F40E7();
	candidateGoal->ReleaseInfo();
	return 0;
}

Path *Pathfinder::FindSafePath(Object *obj,const LocomotorSet &loco,const Coord3D *from,
const Coord3D *repulsor1,const Coord3D *repulsor2,float radius)
{
if(!m_isMapReady)return 0;
Bool center;Int cellRadius;Rva002EBCA7Split(obj,&cellRadius,(unsigned char *)&center);
float repulsorDistance=radius*radius;Int count=0;Bool human=true;
if(obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType==1)human=false;
_STL::vector<Gen_p12pod> *hops=(_STL::vector<Gen_p12pod> *)&m_1C1CC;hops->erase(hops->begin(),hops->end());m_zoneManager.rva00531300();
PathfindCell *parent=rva002E8BF8((PathfindLayerEnum)obj->rva0028B511(),(Coord3D *)obj->position);
if(!parent || !obj->m_258)return 0;
ICoord2D *startCell;{ICoord2D start;Rva002E7875WorldToCell(&start,true,(Coord3D *)obj->position);
parent->allocateInfo((In002E6BA1 *)&start);startCell=&start;}parent->StartPathfind(0);AddToOpenList(parent);
PathfinderSearchCellsVisited=0;float farthest=0;
while((parent=rva002F36E5())!=0) {
PathfinderCellPoint cellCenter=Rva002E8C23Call(center,parent);
float dx=cellCenter.x-repulsor1->x,dy=cellCenter.y-repulsor1->y;
float distance=dx*dx+dy*dy;
dx=cellCenter.x-repulsor2->x;dy=cellCenter.y-repulsor2->y;
float distance2=dx*dx+dy*dy;Bool ok=false;
if(distance>distance2)distance=distance2;
if(distance>repulsorDistance)ok=true;
if(!rva002F068F() && count>0)ok=true;
if(distance>farthest){farthest=distance;if(count>2000)ok=true;}
if(ok && bfmeWrapE6E90(obj,(void *)parent->getXIndex(),(void *)parent->getYIndex(),(void *)parent->getLayer(),(void *)cellRadius,boolArg(center))) {
Path *path=BuildActualPath(obj,loco.getValidSurfaces(),(Coord3D *)obj->position,parent,center,false,true);
rva002F40E7();parent->ReleaseInfo();return path;
}
parent->PutOnClosedList(&m_closedList);CheckChangeLayers(parent,obj);
count+=rva002F83F5(parent,0,loco,human,center,cellRadius,startCell,obj,0);
}
m_isTunneling=false;rva002F40E7();return 0;
}
Path *Pathfinder::InternalFindPath(Object *obj, const LocomotorSet &locomotorSet, const Coord3D *from,
	const Coord3D *rawTo, HierarchicalPath *hierarchicalPath, Bool *destinationAdjusted)
{
	if (g_00DFEFF0)
		pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() called");
	Bool goalBlocked = false;
	Bool centerInCell = true;
	Int radius = 0;
	Rva002EBCA7Split(obj, &radius, (unsigned char *)&centerInCell);

	Bool isHuman = true;
	if (obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType == 1) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 1");
		isHuman = false;
	}

	if (rawTo->x == 0.0f && rawTo->y == 0.0f) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 2 return NULL");
		return NULL;
	}
	if (!m_isMapReady) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 3 return NULL");
		return NULL;
	}

	Coord3D adjustTo;
	copyCoord3D(&adjustTo, rawTo);
	Coord3D clipFrom;
	copyCoord3D(&clipFrom, from);
	rva002E75A3(&clipFrom, &adjustTo);

	if (!centerInCell) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 4");
		adjustTo.x += 5.0f;
		adjustTo.y += 5.0f;
	}
	Coord3D unshiftedTo;
	copyCoord3D(&unshiftedTo, &adjustTo);

	if (obj->m_template->testKindWord(186)) {
		float offsetX = 20.0f;
		float offsetY = 0.0f;
		rotateOffset(offsetX, offsetY, obj->GetGoalAngle() + 3.14159265359f);
		adjustTo.x += offsetX;
		adjustTo.y += offsetY;
	}

	m_isTunneling = false;
	PathfindLayerEnum destinationLayer = TheTerrainLogic->getLayerForDestination(NULL, &adjustTo);
	PathfindCell *goalCell = (PathfindCell *)rva001E3647Pos(destinationLayer, &adjustTo);
	if (goalCell == NULL) {
		if (!obj->m_template->testKindWord(186))
			return NULL;
		adjustTo = unshiftedTo;
		goalCell = (PathfindCell *)rva001E3647Pos(destinationLayer, &adjustTo);
		if (goalCell == NULL)
			return NULL;
	}

	TCheckMovementInfo info;
	Int blockers;
	ICoord2D *startCell;
	{
	ICoord2D cell;
	Rva002E7875WorldToCell(&cell, true, &adjustTo);
	((Rva002E6FDF *)&info)->rva002E6FDF();
	info.cell = cell;
	info.layer = destinationLayer;
	info.centerInCell = centerInCell;
	if (obj->m_template->testKindWord(90)) {
		info.radius = 1;
		info.m_14 = 0xC;
	} else {
		info.radius = 1;
		info.m_14 = 0x1C;
	}
	readMoverInfo(info, obj);
	info.m_11 = true;
	{
		Int priority = obj->m_template->priority;
		Bool flag = obj->m_template->flag;
		char *ai = obj->m_258;
		*(Rva002E8BCF *)info.m_1C = Rva002E8BCF((const Rva002E8BCFSrc *)(ai + 0x1CC), !flag, priority - 1, obj->rva0028AFBB());
	}
	if (!CheckDestination(obj, cell.x, cell.y, destinationLayer, radius, centerInCell, &blockers, true)
		|| !checkForMovement(obj, info)) {
		if (obj->m_template->testKindWord(186)) {
			adjustTo = unshiftedTo;
			destinationLayer = TheTerrainLogic->getLayerForDestination(NULL, &adjustTo);
			goalCell = (PathfindCell *)rva001E3647Pos(destinationLayer, &adjustTo);
			if (goalCell == NULL)
				return NULL;
			{
			ICoord2D retryCell;
			ICoord2D *cell = Rva002E7875WorldToCell(&retryCell, true, &adjustTo);
			Int infoX = cell->x;
			Int infoY = cell->y;
			ICoord2D goal = *cell;
			info.cell.x = infoX;
			info.cell.y = infoY;
			if (!CheckDestination(obj, goal.x, goal.y, destinationLayer, radius, centerInCell, &blockers, true)
				|| !checkForMovement(obj, info))
				goalBlocked = true;
			}
		} else {
			goalBlocked = true;
		}
	}
	}

	{ ICoord2D startCellNdx; Rva002E7875WorldToCell(&startCellNdx, true, &clipFrom); startCell = &startCellNdx; }
	PathfindLayerEnum layer = (PathfindLayerEnum)obj->rva0028B511();
	PathfindCell *parentCell = rva002E8BF8(layer, &clipFrom);
	if (parentCell == NULL) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 7 return NULL");
		return NULL;
	}

	Bool viaMineshaft = false;
	if (m_srcMineshaft && m_destMineshaft && m_srcMineshaft != m_destMineshaft) {
		const Rva002F35AFHop *hopEnd = m_1C1CC.end();
		for (const Rva002F35AFHop *hop = m_1C1CC.begin(); hop != hopEnd; ++hop) {
			if (hop->m_zone == m_srcMineshaft->m_portal) {
				viaMineshaft = true;
				adjustTo = m_srcMineshaft->m_position;
				rva002E75A3(&clipFrom, &adjustTo);
				unshiftedTo = adjustTo;
				destinationLayer = TheTerrainLogic->getLayerForDestination(NULL, &adjustTo);
				goalCell = (PathfindCell *)rva001E3647Pos(destinationLayer, &adjustTo);
				break;
			}
		}
	}

	{ ICoord2D pos2d; goalCell->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&pos2d, true, &adjustTo)); }
	if (parentCell != goalCell) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 8");
		ICoord2D pos2d;
		parentCell->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&pos2d, true, &clipFrom));
	}

	if (parentCell->getType() == PathfindCell::CELL_OBSTACLE
		&& (parentCell->m_pathInfo ? parentCell->m_pathInfo->obstacleID : (ObjectID)0) != m_ignoreObstacleID) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 9");
		m_isTunneling = true;
	} else {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 10");
		m_isTunneling = false;
	}

	if (((const Rva0028B984ByteField *)obj)->get()) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 11");
		parentCell->StartPathfind((Int)goalCell);
		parentCell->m_pathInfo->totalCost = (unsigned short)rva002F0A72(parentCell, goalCell);
		AddToOpenList(parentCell);
		Path *path = BuildActualPath(obj, locomotorSet.getValidSurfaces(), from, goalCell, centerInCell, false, true);
		rva002F40E7();
		goalCell->ReleaseInfo();
		if (pathfinderLogOn())
			fprintf((PathfinderLogFile *)g_00DFEFF0, "CritterDesync:    Pathfinder::InternalFindPath() 12 return %s", path ? "VALID" : "NULL");
		return path;
	}

	Int priority = obj->m_template->priority;
	Bool flag = obj->m_template->flag;
	Rva002E8BCF moverInfo((const Rva002E8BCFSrc *)&locomotorSet, !flag, priority - 1, obj->rva0028AFBB());
	Rva002E99F9Sub460 *zones = (Rva002E99F9Sub460 *)&m_zoneManager;
	Int zone1 = zones->rva0053241F(&moverInfo, parentCell->quickZone());
	Int zone2 = zones->rva0053241F(&moverInfo, goalCell->quickZone());
	if (goalCell->IsObstaclePresent(m_ignoreObstacleID) || parentCell->IsObstaclePresent(m_ignoreObstacleID) || m_isTunneling) {
		zone2 = zones->rva00531FD4(&moverInfo, (unsigned short)zone2);
		zone2 = zones->rva0053241F(&moverInfo, (unsigned short)zone2);
		zone1 = zones->rva00531FD4(&moverInfo, (unsigned short)zone1);
		zone1 = zones->rva0053241F(&moverInfo, (unsigned short)zone1);
		if (g_00E03745 && g_00DFEFF0)
			fprintf((PathfinderLogFile *)g_00DFEFF0, "CritterDesync:    Pathfinder::InternalFindPath() 13");
	}
	if (zone1 != zone2) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:\tPathfinder::InternalFindPath() 13.5");
		if (!rva002F4115(obj, zone1, zone2, NULL))
			goalBlocked = true;
	}
	if (!IsValidMovementPositionForObject(&adjustTo, destinationLayer, locomotorSet.getValidSurfaces(), obj))
		goalBlocked = true;
	if (!IsValidMovementPositionForObject(from, layer, locomotorSet.getValidSurfaces(), obj)) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 16");
		m_isTunneling = true;
	}
	if (!m_isTunneling) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 17");
		((Rva002E6FDF *)&info)->rva002E6FDF();
		info.layer = (PathfindLayerEnum)parentCell->getLayer();
		info.centerInCell = centerInCell;
		info.radius = radius;
		info.m_14 = 0;
		readMoverInfo(info, obj);
		{ ICoord2D startCellNdx; info.cell = *Rva002E7875WorldToCell(&startCellNdx, true, &clipFrom); }
		info.m_11 = true;
		if (!checkForMovement(obj, info)) {
			if (pathfinderLogOn())
				pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 18");
			m_isTunneling = true;
		}
	}

	parentCell->StartPathfind((Int)goalCell);
	parentCell->m_pathInfo->totalCost = (unsigned short)rva002F0A72(parentCell, goalCell);
	AddToOpenList(parentCell);

	Int cellCount = 0;
	PathfinderSearchCellsVisited = 0;
	PathfindCell *closestCell = NULL;
	Int closestPathIndex = 0;
	Int closestDist = 0x7fffffff;
	Int nearestGoalDist = 0x7fffffff;
	Int giveUpDist = 0x7fffffff;
	while ((parentCell = rva002F36E5()) != NULL) {
		if (parentCell == goalCell) {
			m_isTunneling = false;
			Path *path = BuildActualPath(obj, locomotorSet.getValidSurfaces(), from, goalCell, centerInCell, false, false);
			if (viaMineshaft) {
				PathfindLayerEnum srcLayer = TheTerrainLogic->getLayerForDestination(NULL, &m_srcMineshaft->m_position);
				path->rva002655E3(&m_srcMineshaft->m_position, srcLayer, m_srcMineshaft->m_portal);
				PathfindLayerEnum destLayer = TheTerrainLogic->getLayerForDestination(NULL, &m_destMineshaft->m_position);
				path->rva002655E3(&m_destMineshaft->m_position, destLayer, 0x7fffffff);
				path->SetLastNodePortal(m_destMineshaft->m_portal);
			}
			Coord3D direction = *((const Thing *)obj)->getUnitDirectionVector2D();
			path->rva00365E98(obj, &direction, locomotorSet.getValidSurfaces(), false);
			rva002F40E7();
			parentCell->ReleaseInfo();
			if (pathfinderLogOn())
				fprintf((PathfinderLogFile *)g_00DFEFF0, "CritterDesync:    Pathfinder::InternalFindPath() 19 return %s", path ? "VALID" : "NULL");
			return path;
		}

		parentCell->PutOnClosedList(&m_closedList);
		if ((unsigned int)cellCount > ((const PathfinderCellLimitView *)TheWritableGlobalData)->maxCells) {
			if (pathfinderLogOn())
				pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 20 failed path break");
			break;
		}

		if (!m_isTunneling) {
			Int dx = abs(goalCell->getXIndex() - parentCell->getXIndex());
			Int dy = abs(goalCell->getYIndex() - parentCell->getYIndex());
			Int dist = dx*dx + dy*dy;
			if (dist < nearestGoalDist) {
				if (dx + dy > 25) {
					float reach = (float)sqrt((double)dist) + 25.0f;
					giveUpDist = (Int)(reach * reach);
				} else {
					giveUpDist = dist * 4;
				}
				nearestGoalDist = dist;
			}
			dist += (Int)m_1C1CC.size()*10*10*100;
			if (hierarchicalPath) {
				Int pathIndex = hierarchicalPath->lookUpPositionOnPath((const Coord3D *)parentCell->m_pathInfo);
				if (pathIndex > closestPathIndex || (pathIndex == closestPathIndex && dist < closestDist)) {
					closestDist = dist;
					closestPathIndex = pathIndex;
					if (bfmeWrapE6E90(obj, (void *)parentCell->getXIndex(), (void *)parentCell->getYIndex(),
							(void *)parentCell->getLayer(), (void *)radius, boolArg(centerInCell))
						&& ((Rva002E6DC4 *)this)->rva002E6DC4(&moverInfo, parentCell)
						&& rva002EDFF9(obj, cellPointArg(Rva002E8C23Call(centerInCell, parentCell))))
						closestCell = parentCell;
				}
			} else if (dist < closestDist) {
				closestDist = dist;
				if (bfmeWrapE6E90(obj, (void *)parentCell->getXIndex(), (void *)parentCell->getYIndex(),
						(void *)parentCell->getLayer(), (void *)radius, boolArg(centerInCell))
					&& ((Rva002E6DC4 *)this)->rva002E6DC4(&moverInfo, parentCell)
					&& rva002EDFF9(obj, cellPointArg(Rva002E8C23Call(centerInCell, parentCell))))
					closestCell = parentCell;
			}
		}

		if (goalBlocked) {
			Int dx = abs(goalCell->getXIndex() - parentCell->getXIndex());
			Int dy = abs(goalCell->getYIndex() - parentCell->getYIndex());
			Int dist = dx*dx + dy*dy;
			if (dist > giveUpDist) {
				Bool giveUp = false;
				if (hierarchicalPath == NULL)
					giveUp = true;
				if (cellCount > 2000)
					giveUp = true;
				if (dist < 100)
					giveUp = false;
				if (giveUp)
					continue;
			}
		}

		CheckChangeLayers(parentCell, obj);
		cellCount += rva002F83F5(parentCell, goalCell, locomotorSet, isHuman, centerInCell, radius, startCell, obj, 0);
	}

	if (pathfinderLogOn())
		pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 21");
	if (closestCell) {
		*destinationAdjusted = true;
		m_isTunneling = false;
		Path *path = BuildActualPath(obj, locomotorSet.getValidSurfaces(), from, closestCell, centerInCell, false, true);
		rva002F40E7();
		goalCell->ReleaseInfo();
		return path;
	}
	m_isTunneling = false;
	rva002F40E7();
	goalCell->ReleaseInfo();
	if (pathfinderLogOn())
		pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 24 return NULL");
	return NULL;
}

// 0x002E7917: Rva002E7875WorldToCell clamped to the cell extent at +0x14.
PathfinderCellIndex Pathfinder::Rva002E7917(bool center, const Coord3D *pos)
{
	PathfinderCellIndex tmp;
	Rva002E7875WorldToCell(&tmp, center, pos);
	if (tmp.x < m_clampLo.x)
		tmp.x = m_clampLo.x;
	if (tmp.y < m_clampLo.y)
		tmp.y = m_clampLo.y;
	if (tmp.x > m_clampHi.x)
		tmp.x = m_clampHi.x;
	if (tmp.y > m_clampHi.y)
		tmp.y = m_clampHi.y;
	return tmp;
}
// 0x002E8BF8: world position to cell through the clamp wrapper.
PathfindCell *Pathfinder::rva002E8BF8(PathfindLayerEnum layer, const Coord3D *pos)
{
	PathfinderCellIndex cell = Rva002E7917(true, pos);
	return getCell(layer, cell.x, cell.y);
}

// 0x002EBCA7: splits Get(p) into half and odd bit.
void __cdecl Rva002EBCA7Split(void *p, int *outHalf, unsigned char *outOdd)
{
	int v = Rva002E9B31Get(p);
	*outHalf = v;
	*outOdd = (v % 2 == 1);
	*outHalf /= 2;
}

// WorldBuilder's MathCoord2D.h Coord2D (asserts compiled out): a 2-float
// vector with a user copy constructor, so by-value arguments and results go
// through memory. Its inline operator- and operator+ are not inlined at /O1
// and their COMDATs are retail 0x001040AE and 0x0007DEC8.
class MathCoord2D
{
public:
	MathCoord2D() {}
	MathCoord2D(const MathCoord2D &that) : x(that.x), y(that.y) {}
	MathCoord2D(float ix, float iy) : x(ix), y(iy) {}
	MathCoord2D(Int ix, Int iy) : x((float)ix), y((float)iy) {}
	~MathCoord2D() {}
	float dot(const MathCoord2D &c) const { return y * c.y + x * c.x; }
	MathCoord2D &operator*=(float s) { x *= s; y *= s; return *this; }
	MathCoord2D &operator-=(const MathCoord2D &c) { x -= c.x; y -= c.y; return *this; }
	MathCoord2D &operator+=(const MathCoord2D &c) { x += c.x; y += c.y; return *this; }
	__forceinline float GetLengthEstimate() const { return fabs(x) > fabs(y) ? fabs(x) + fabs(y) * 0.25f : fabs(y) + fabs(x) * 0.25f; }
	__forceinline float GetLength() const { return (float)sqrt(x * x + y * y); }
	__forceinline void Normalize() { float inv = 1.0f / GetLength(); x *= inv; y *= inv; }
	float x;
	float y;
};
inline MathCoord2D operator-(MathCoord2D left, const MathCoord2D &right)
{
	left -= right;
	return left;
}
inline MathCoord2D operator+(MathCoord2D left, const MathCoord2D &right)
{
	left += right;
	return left;
}
// Pathfinder::ExamineNeighboringCellsForSidewaysAttack, retail 0x002F8B00 (813 B),
// WorldBuilder D66060. The goal is the target cell, or, when the parent is
// within attack range, the point offset cells off the parent's facing line
// beside the target. The goal cell gets path info for the examination at
// 0x002F83F5 and drops it again when nothing else holds it.
Int Pathfinder::ExamineNeighboringCellsForSidewaysAttack(PathfindCell *parentCell,const ICoord2D *targetNdx,Int offset,const LocomotorSet &locomotorSet,Bool isHuman,Bool centerInCell,Int radius,ICoord2D *startCellNdx,Object *obj,Int attackDistance)
{
	ICoord2D goalNdx;
	Int px1=parentCell->getXIndex();
	Int px2=parentCell->getXIndex();
	Int py1=parentCell->getYIndex();
	Int py2=parentCell->getYIndex();
	Int distSqr=(px1-targetNdx->x)*(px2-targetNdx->x)+(py1-targetNdx->y)*(py2-targetNdx->y);
	if(distSqr*5*5<(offset+attackDistance)*(offset+attackDistance)){
		float orientation=obj->m_orientation;
		float angle=parentCell->rva0052DD75(orientation,10,0.5f);
		MathCoord2D parentWorld(parentCell->getXIndex()*10,parentCell->getYIndex()*10);
		float s=Sin(angle);
		MathCoord2D dir;
		dir.x=Cos(angle);
		dir.y=s;
		MathCoord2D targetWorld(targetNdx->x*10,targetNdx->y*10);
		if(centerInCell){
			parentWorld.x+=5.0f;
			parentWorld.y+=5.0f;
		}
		MathCoord2D delta=targetWorld-parentWorld;
		float dot=dir.dot(delta);
		dir*=dot;
		MathCoord2D p=parentWorld+dir;
		p-=targetWorld;
		if(p.GetLengthEstimate()<0.0001f){
			p.x=dir.y;
			p.y=-dir.x;
		}
		p.Normalize();
		p*=(float)offset;
		p+=targetWorld;
		goalNdx=Rva002E7917(centerInCell,(const Coord3D *)&p);
	}else{
		goalNdx=*targetNdx;
	}
	PathfindCell *goalCell=getCell(PATHFIND_LAYER_GROUND,goalNdx.x,goalNdx.y);
	if(!goalCell)return 0;
	Bool hadInfo=goalCell->m_pathInfo!=0;
	if(!hadInfo)goalCell->allocateInfo((In002E6BA1 *)&goalNdx);
	Int count=rva002F83F5(parentCell,goalCell,locomotorSet,isHuman,centerInCell,radius,startCellNdx,obj,attackDistance);
	if(!hadInfo){
		if(!(unsigned char)((Rva002E6AF3 *)goalCell)->get()&&!(unsigned char)((Rva002E6B06 *)goalCell)->rva002E6B06())goalCell->ReleaseInfo();
	}
	return count;
}


// Native 0x002ED7F7..0x002EDCF7 (1280 bytes), RET 12; WorldBuilder D45C80
// names AdjustToMeleeDestination in pathfinder.cpp:4872. The destination-cell
// zone must agree with the mover before the direct placement is tried. Failing
// that, the four-leg square spiral accepts only a closer reachable placement.
// Keep one counter across all four legs: its lifetime reuses the dead Object
// parameter slot. Natural cell/step and destination-cell/budget lifetimes
// reproduce the native frame without the old bank's forced storage unions.
// Initialize the walk budget before x/y to retain the native load scheduling.
struct Rva002ED7F7Budget{char pad[0x1200];int maxSteps;};
class Rva002EC3CEProbes{public:bool rva002EAA41(int,int,int,int,int,bool);bool rva002E7BF0(int,int,bool,int,int,int,void*,bool);};
static __forceinline void subtractMelee(Coord3D &a,const Coord3D&b){a.x-=b.x;a.y-=b.y; a.z-=b.z;}
static __forceinline float distanceMelee(const Coord3D&a){return a.z*a.z+a.y*a.y+a.x*a.x;}
bool Pathfinder::adjustToMeleeDestination(Object*obj,const LocomotorSet&set,Coord3D*dest){
 int i;
 int radius;Bool center;Rva002EBCA7Split(obj,&radius,(unsigned char*)&center);
 ICoord2D cell;((Rva002E7964*)this)->rva002E7964(&cell,center,dest);if(cell.x<0)return false;
 PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(obj,dest);PathfindCell *destinationCell=getCell(layer,cell.x,cell.y);
 Coord3D from;from.x=obj->position[0];from.y=obj->position[1];from.z=obj->position[2];Coord3D delta;delta.x=from.x;delta.y=from.y;delta.z=from.z;subtractMelee(delta,*dest);float bestDist=distanceMelee(delta);
 ICoord2D start;Rva002E7875WorldToCell(&start,true,&from);PathfindLayerEnum fromLayer=(PathfindLayerEnum)obj->rva0028B511();PathfindCell *fromCell=rva002E8BF8(fromLayer,&from);if(!fromCell)return false;
 int width=obj->m_template->priority;bool centerOff=obj->m_template->flag;
 Rva002E8BCF query((const Rva002E8BCFSrc*)&set,!centerOff,width-1,obj->rva0028AFBB());
 Rva002E99F9Sub460 *zoneView=(Rva002E99F9Sub460*)&m_zoneManager;
 unsigned zone=zoneView->rva0053241F(&query,fromCell->quickZone());bool bridge=false;
 if(fromCell->getType()==4){bridge=true;unsigned ground=zoneView->rva00531FD4(&query,zone);zone=zoneView->rva0053241F(&query,ground);}
 if(zone==zoneView->rva0053241F(&query,destinationCell->quickZone())&&((Rva002EC3CEProbes*)this)->rva002EAA41((int)obj,cell.x,cell.y,layer,radius,center))return true;
 int left=((const Rva002ED7F7Budget*)TheWritableGlobalData)->maxSteps;int x=cell.x;int y=cell.y;int steps=1;
 while(left>0){
 for(i=steps;i>0;--i){++x;--left;if(((Rva002EC3CEProbes*)this)->rva002E7BF0((int)&query,zone,center,x,y,layer,dest,bridge)){
  delta=from;subtractMelee(delta,*dest);if(bestDist>distanceMelee(delta)&&((Rva002EC3CEProbes*)this)->rva002EAA41((int)obj,x,y,layer,radius,center))return true;
 }}

 for(i=steps;i>0;--i){++y;--left;if(((Rva002EC3CEProbes*)this)->rva002E7BF0((int)&query,zone,center,x,y,layer,dest,bridge)){
  delta=from;subtractMelee(delta,*dest);if(bestDist>distanceMelee(delta)&&((Rva002EC3CEProbes*)this)->rva002EAA41((int)obj,x,y,layer,radius,center))return true;
 }}
++steps;
 for(i=steps;i>0;--i){--x;--left;if(((Rva002EC3CEProbes*)this)->rva002E7BF0((int)&query,zone,center,x,y,layer,dest,bridge)){
  delta=from;subtractMelee(delta,*dest);if(bestDist>distanceMelee(delta)&&((Rva002EC3CEProbes*)this)->rva002EAA41((int)obj,x,y,layer,radius,center))return true;
 }}

 for(i=steps;i>0;--i){--y;--left;if(((Rva002EC3CEProbes*)this)->rva002E7BF0((int)&query,zone,center,x,y,layer,dest,bridge)){
  delta=from;subtractMelee(delta,*dest);if(bestDist>distanceMelee(delta)&&((Rva002EC3CEProbes*)this)->rva002EAA41((int)obj,x,y,layer,radius,center))return true;
 }}
++steps;
 }
 return false;
}
