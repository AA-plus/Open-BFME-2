// ?ExamineNeighboringCellsForSidewaysAttack@Pathfinder@@QAEHPAVObject@@PBUCoord3D@@@Z
// partial score=0.985 date=2026-10-13
// ?ExamineNeighboringCellsForSidewaysAttack@Pathfinder@@QAEHPAVObject@@PBUCoord3D@@@Z
// partial score=0.985 date=2026-10-13
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// retail 0x002F8B00..0x002F8E2D (813 bytes). WB twin 0xD66060 Pathfinder::ExamineNeighboringCellsForSidewaysAttack.
// Best: compiled 816 bytes, ratio 0.95; only stack layout differs: retail keeps goalNdx in the
// targetWorld slot (-0x24, frame 0x2C) while this draft gives goalNdx its own slot (frame 0x34),
// which shifts delta to -0x34 and the Add argument scheduling by one store.
// dir.x stored early / dir.y stored after the Sub call is what gives retail's forwarding of Sin into [ebp+0x10].
// Update 2026-10-13 (w6-sol3): 813B vs 813B, 263/263 instructions, 14 diff lines left (y-term sub order, dir.x store timing, goalNdx lands at the delta slot -0x2c instead of targetWorld's -0x24); frame 0x2c matches. Structure: vectors passed through function-pointer casts of the rowed
// void(float*,float,float,const float*) helpers as void(Vec*,Vec,const Vec&) (hidden-out slot, no eax-reuse), goalNdx materialised from gx/gy in a
// trailing sibling scope. _ReadWriteBarrier() between the distSqr computation and the range test (plus Int reach=attackDistance+offset) fixed the ebx/edi parameter-register roles: retail keeps offset/attackDistance in edi/ebx and hadInfo in the [ebp+0xf] arg-home byte. Scratch compile: put the function in pathfinder.cpp (class decls + pin ?rva002F83F5@Pathfinder@@QAEHPAVPathfindCell@@0ABVLocomotorSet@@_N2HABUICoord2D@@PAVObject@@H@Z=0x002F83F5).
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef int Int;
enum PathfindLayerEnum { PATHFIND_LAYER_UNKNOWN = 0, PATHFIND_LAYER_GROUND = 1 };
struct ICoord2D { Int x,y; };
class LocomotorSet;
class Object { public: char m_pad00[0x44]; float m_orientation; };
struct In002E6BA1 { Int x,y; };
class MixFileInfoBuffer;
extern Int TheMixFileInfoPool;
void Rva0052DBCDInit();
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **,Int,In002E6BA1 *);
class Rva002E6AF3 { public: Int get() const; };
class Rva002E6B06 { public: Int rva002E6B06(); };
struct PathfinderGroundInfo { Int x,y; Int parent; void *parentWaypoint; };
class PathfindCell
{
public:
	void ReleaseInfo();
	float rva0052DD75(float facing, Int count, float weight);
	__forceinline void allocateInfo(In002E6BA1 *pos) {
		if(!m_pathInfo) { if(!TheMixFileInfoPool)Rva0052DBCDInit();m_pathInfo=(PathfinderGroundInfo *)Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool,(Int)this,pos); }
		else m_pathInfo->parentWaypoint=0;
	}
	Int getXIndex() const { return m_pathInfo->x; }
	Int getYIndex() const { return m_pathInfo->y; }
	PathfinderGroundInfo *m_pathInfo;
};
float Sin(float x);
float Cos(float x);
class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	void Rva002E7917(ICoord2D *out,bool center,const Coord3D *pos);
	Int rva002F83F5(PathfindCell *parentCell, PathfindCell *goalCell, const LocomotorSet &locomotorSet, Bool isHuman, Bool centerInCell, Int radius, const ICoord2D &startCellNdx, Object *obj, Int attackDistance);
	Int ExamineNeighboringCellsForSidewaysAttack(PathfindCell *parentCell, const ICoord2D *targetNdx, Int offset, const LocomotorSet &locomotorSet, Bool isHuman, Bool centerInCell, Int radius, const ICoord2D &startCellNdx, Object *obj, Int attackDistance);
};
extern "C" double __cdecl fabs(double);
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// Pathfinder::ExamineNeighboringCellsForSidewaysAttack, retail 0x002F8B00 (813 bytes).
// Name and branch structure from WorldBuilder 0x00D66060: the goal cell is the target
// cell, or (when the parent is within attack range) the cell found by projecting the
// parent's facing line onto the target and stepping offset cells off it.
// Retail passes the 2-float vector by value through the rowed 0x001040AE / 0x0007DEC8
// helpers (argument-area save: a non-POD vector) and takes the result in a hidden slot.
class Rva002F8B00Vec
{
public:
	Rva002F8B00Vec() {}
	Rva002F8B00Vec(const Rva002F8B00Vec &that) : x(that.x), y(that.y) {}
	Rva002F8B00Vec(float ix, float iy) : x(ix), y(iy) {}
	Rva002F8B00Vec(Int ix, Int iy) : x((float)ix), y((float)iy) {}
	~Rva002F8B00Vec() {}
	float dot(const Rva002F8B00Vec &c) const { return y * c.y + x * c.x; }
	Rva002F8B00Vec &operator*=(float s) { x *= s; y *= s; return *this; }
	Rva002F8B00Vec &operator-=(const Rva002F8B00Vec &c) { x -= c.x; y -= c.y; return *this; }
	Rva002F8B00Vec &operator+=(const Rva002F8B00Vec &c) { x += c.x; y += c.y; return *this; }
	__forceinline float GetLengthEstimate() const { return fabs(x) > fabs(y) ? fabs(x) + fabs(y) * 0.25f : fabs(y) + fabs(x) * 0.25f; }
	__forceinline float GetLength() const { return (float)sqrt(x * x + y * y); }
	__forceinline void Normalize() { float inv = 1.0f / GetLength(); x *= inv; y *= inv; }
	float x;
	float y;
};
void __cdecl Rva001040AESub(float *out,float x,float y,const float *b);
void Rva0007DEC8Add(float *out,float x,float y,const float *b);
typedef void (__cdecl *Rva002F8B00VecOp)(Rva002F8B00Vec *,Rva002F8B00Vec,const Rva002F8B00Vec &);
Int Pathfinder::ExamineNeighboringCellsForSidewaysAttack(PathfindCell *parentCell,const ICoord2D *targetNdx,Int offset,const LocomotorSet &locomotorSet,Bool isHuman,Bool centerInCell,Int radius,const ICoord2D &startCellNdx,Object *obj,Int attackDistance)
{
	Int gx,gy;
	Int distSqr=(parentCell->getXIndex()-targetNdx->x)*(parentCell->getXIndex()-targetNdx->x)+(parentCell->getYIndex()-targetNdx->y)*(parentCell->getYIndex()-targetNdx->y);
	Int reach=attackDistance+offset;
	_ReadWriteBarrier();
	if(distSqr*5*5<reach*reach){
		float orientation=obj->m_orientation;
		float angle=parentCell->rva0052DD75(orientation,10,0.5f);
		Rva002F8B00Vec parentWorld(parentCell->getXIndex()*10,parentCell->getYIndex()*10);
		float s=Sin(angle);
		Rva002F8B00Vec dir;
		dir.x=Cos(angle);
		Rva002F8B00Vec targetWorld(targetNdx->x*10,targetNdx->y*10);
		if(centerInCell){
			parentWorld.x+=5.0f;
			parentWorld.y+=5.0f;
		}
		Rva002F8B00Vec delta;
		reinterpret_cast<Rva002F8B00VecOp>(&Rva001040AESub)(&delta,targetWorld,parentWorld);
		dir.y=s;
		float dot=dir.dot(delta);
		dir*=dot;
		Rva002F8B00Vec p;
		reinterpret_cast<Rva002F8B00VecOp>(&Rva0007DEC8Add)(&p,parentWorld,dir);
		p-=targetWorld;
		if(p.GetLengthEstimate()<0.0001f){
			p.x=dir.y;
			p.y=-dir.x;
		}
		p.Normalize();
		p*=(float)offset;
		p+=targetWorld;
		ICoord2D *r=(this->*reinterpret_cast<ICoord2D *(Pathfinder::*)(ICoord2D *,bool,const Coord3D *)>(&Pathfinder::Rva002E7917))((ICoord2D *)&dir,centerInCell,(const Coord3D *)&p);
		gx=r->x;
		gy=r->y;
	}else{
		gx=targetNdx->x;
		gy=targetNdx->y;
	}
	{
	ICoord2D goalNdx;
	goalNdx.x=gx;
	goalNdx.y=gy;
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
}
