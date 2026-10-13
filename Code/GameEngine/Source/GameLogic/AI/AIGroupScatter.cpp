// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// stlport
// AIGroup::groupScatter, native 0036F757..0036F917 (448 bytes).
// Identity and ordering: WB EE56B0 and ZH AIGroup::groupScatter.
// BFME2 allocates a plain iterator and calls Object::rva0028AD32.
// The real move wrapper and Coord2D normalization are visible so MSVC
// can prove that their coordinate addresses do not escape and reuse slots.
#include <list>
// class-gate: allow Coord3D visible planar helpers need this TU-scoped method view;
// adding Normalize2D to the canonical declaration changes TeamTemplateInfo's
// verified restore order. Native 00005AB2 is the existing Normalize2D owner.
// Layout remains the canonical three floats; no shared header or ABI changes.
struct Coord3D
{
    float x, y, z;
    float GetLength2D() const;
    float Normalize2D();
};
#include "Coord2D.h"
template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#ifndef NULL
#define NULL 0
#endif

inline Real sqr(Real x) { return x * x; }

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

// Only the word computeGroundPath reads: Object::m_ai+0x1DC is handed to
// Pathfinder::IsLineBlocked as its second argument (Zero Hour passes the
// locomotor set's valid surfaces there to isLinePassable).
// Throwing C++ spelling of the rowed game allocator at 0x00030830.
void Rva00030830GameFree(void *block);
enum AICommandType
{
	AICMD_MOVE_TO_POSITION = 0
};
// The 0xC0 command block of AICommandInterfaceAttackCommands.cpp: opaque
// constructor 0x00351BD0, inline coordinate-buffer free on teardown.
struct AICommandParms
{
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);
	~AICommandParms() { if (m_coordsStart) Rva00030830GameFree(m_coordsStart); }

	AICommandType m_cmd; // +0x00
	CommandSourceType m_cmdSource; // +0x04
	Coord3D m_pos; // +0x08
	char m_pad14[0x20 - 0x14];
	void *m_coordsStart; // +0x20
	char m_pad24[0xC0 - 0x24];
};
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
	void aiIdle(CommandSourceType cmdSource);
	void rva0036F6A7(float angle, CommandSourceType cmdSource);
	// Zero Hour's aiGoProne (0x0036F400: AICMD 0x1D copying the DamageInfo
	// into the command block at +0x3C), rowed under a placeholder whose
	// parameter class Rva003427DD is that DamageInfo.
	void rva0036F400(const class Rva003427DD *info, CommandSourceType cmdSource);
	// Retail 0x0026C26D; visible here (as in BFME1's twin) so VC7.1 sees it
	// does not retain the position.
	__declspec(noinline) void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource)
	{
		AICommandParms parms(AICMD_MOVE_TO_POSITION, (CommandSourceType)cmdSource);
		parms.m_pos = *pos;
		aiDoCommand(&parms);
	}
};

class AIUpdateInterface
{
public:
	void *getValidSurfaces() const { return m_validSurfaces; }
	void aiMoveToPosition(const Coord3D *pos,CommandSourceType cmd) { m_commands.aiMoveToPosition(pos,cmd); }
	AICommandInterface *getCommands() { return &m_commands; }

private:
	char m_pad0[0x20];
	AICommandInterface m_commands;
	char m_pad21[0x1DC-0x24];
	void *m_validSurfaces;	// +0x1DC
};

class ThingTemplate
{
public:
	UnsignedInt isKindOf(UnsignedInt mask) const { return m_kindOf & mask; }

private:
	char m_pad0[0x108];
	UnsignedInt m_kindOf;	// +0x108
};

class Object
{
public:
	Bool rva002907A1();
	void rva0028AD32();
	Int rva0028B511() const;	// the pathfind layer (as Object::getLayer callers)
	Bool isDisabledByHeld() const { return (m_disabledMask[0] & 8) != 0; }
	UnsignedInt isKindOf(UnsignedInt mask) const { return m_template->isKindOf(mask); }
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	AIUpdateInterface *getAI() { return m_ai; }
	UnsignedInt getFormationID() const { return m_formationID; }
	Real getBoundingCircleRadius() const { return m_boundingRadius; }

private:
	char m_pad0[4];
	const ThingTemplate *m_template;	// +0x04
	char m_pad8[0x38 - 0x08];
	Coord3D m_position;
	char m_pad44[0xB8 - 0x44];
	Real m_boundingRadius;
	char m_padBC[0x1C8 - 0xBC];
	unsigned char m_disabledMask[0x258 - 0x1C8];
	AIUpdateInterface *m_ai;
	char m_pad25C[0x410-0x25C];
	UnsignedInt m_formationID;
};

enum IterOrderType
{
	ITER_FASTEST = 0,
	ITER_SORTED_NEAR_TO_FAR = 1,
	ITER_SORTED_FAR_TO_NEAR = 2
};

class Object;

class SimpleObjectIterator
{
public:
	SimpleObjectIterator();
	virtual ~SimpleObjectIterator();
	virtual Object *first();
	virtual Object *next();
	void insert(Object *obj, Real numeric);
	void sort(IterOrderType order);
private:
	unsigned char m_pad04[0x3C - 0x04];
};


struct Coord3DCopy : public Coord3D { Coord3DCopy() {} Coord3DCopy(const Coord3D &p) {x=p.x;y=p.y;z=p.z;} };
class AIGroup
{
public:
	Bool getMinMaxAndCenter(Coord2D *minimumBounds, Coord2D *maximumBounds, Coord3D *groupCenter);
	void groupScatter(CommandSourceType);
	void groupRotateFiringarc(const Coord3D *pos, CommandSourceType cmdSource);

private:
	virtual ~AIGroup();
	void recompute();

	std::list<Object *> m_memberList;	// +0x04
	Real m_speed;						// +0x08
	Bool m_dirty;						// +0x0C
	char m_pad0D[0x14 - 0x0D];
	void *m_groundPath;					// +0x14
	Coord3D m_pathStart;				// +0x18
	Coord3D m_pathEnd;					// +0x24
};

// ZH getMinMaxAndCenter; native 0036D14F..0036D2C5 provides target
// layouts; use source divisions so MSVC emits retail reciprocal scaling.
inline Bool AIGroup::getMinMaxAndCenter(Coord2D *min, Coord2D *max, Coord3D *center)
{
	Int count = 0;
	min->x = 1e10f;
	max->x = -1e10f;
	min->y = 1e10f;
	max->y = -1e10f;
	center->x = 0.0f;
	center->y = 0.0f;
	center->z = 0.0f;

	std::list<Object *>::iterator i;
	UnsignedInt id = 0;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i) {
		if ((*i)->isDisabledByHeld()) {
			continue;
		}
		AIUpdateInterface *ai = (*i)->getAIUpdateInterface();
		if (ai) {
			const Coord3D *objPos = (*i)->getPosition();
			center->x += objPos->x;
			center->y += objPos->y;
			center->z += objPos->z;

			min->x = min->x > objPos->x ? objPos->x : min->x;
			max->x = max->x < objPos->x ? objPos->x : max->x;
			min->y = min->y > objPos->y ? objPos->y : min->y;
			max->y = max->y < objPos->y ? objPos->y : max->y;
			UnsignedInt curID = (*i)->getFormationID();
			if (count == 0) {
				id = curID;
			} else {
				if (id == 0) {
					id = 0;
				}
			}

			count++;
		}
	}

	center->x /= count;
	center->y /= count;
	center->z /= count;
	Bool isFormation = (id != 0);
	if (count < 2)
		isFormation = false;
	return isFormation;
}

// ZH groupScatter; native 0036F757..0036F917 and WB EE56B0.
// Bounding helper defined in this TU proves output lifetime for slot reuse.
void AIGroup::groupScatter(CommandSourceType cmdSource)
{
	if (m_dirty)
		recompute();

	Coord3D center;
	Coord2D min;
	Coord2D max;
	Coord3DCopy dest;

	getMinMaxAndCenter(&min, &max, &center);

	SimpleObjectIterator *iter = new SimpleObjectIterator;
	for (std::list<Object*>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Real dx, dy;
		if ((*i)->isDisabledByHeld())
			continue;
		if ((*i)->isKindOf(4))
			continue;
		if ((*i)->getAI() == 0)
			continue;
		Coord3DCopy unitPos = *(*i)->getPosition();
		(*i)->rva0028AD32();
		dx = unitPos.x - center.x;
		dy = unitPos.y - center.y;
		iter->insert((*i), dx * dx + dy * dy);
	}

	iter->sort(ITER_SORTED_FAR_TO_NEAR);
	Object *theUnit;
	for (theUnit = iter->first(); theUnit; theUnit = iter->next())
	{
		__vref(center.x) -= 0.01f;
		AIUpdateInterface *ai = theUnit->getAI();
		Coord3DCopy unitPos = *theUnit->getPosition();
		Coord2D delta;
		dest = unitPos;
		delta.x = unitPos.x - center.x;
		delta.y = unitPos.y - center.y;
		delta.normalize();
		dest.x += delta.x * theUnit->getBoundingCircleRadius() * 4;
		dest.y += delta.y * theUnit->getBoundingCircleRadius() * 4;
		ai->aiMoveToPosition(&dest, cmdSource);
	}
}

#include <math.h>
inline float Coord2D::length() const {return (float)sqrt(x*x+y*y);}
inline void Coord2D::normalize(){float len=length();if(len!=0.0f){x/=len;y/=len;}}

// Both levels must remain visible: the length helper proves that the address
// passed to Normalize2D does not escape. This lets MSVC eliminate the initial
// coordinate stores before the subtraction in groupRotateFiringarc.
inline float Coord3D::GetLength2D() const
{
	float xValue = x;
	float yValue = y;
	return (float)sqrt(xValue * xValue + yValue * yValue);
}

__declspec(noinline) inline float Coord3D::Normalize2D()
{
	float len = GetLength2D();
	float scale = 1.0f / len;
	x *= scale;
	y *= scale;
	return len;
}

// The canonical coordinate is a plain layout view. WB EEBCC0 shows a copied
// three-float local with an empty destructor, then sub and GetLengthSqrd2D.
struct RotateCoord : Coord3D
{
	RotateCoord(const Coord3D &p) { x = p.x; y = p.y; z = p.z; }
	~RotateCoord() {}
	void sub(const Coord3D *p) { x -= p->x; y -= p->y; z -= p->z; }
	float GetLengthSqrd2D() const { return x * x + y * y; }
};

float ACos(float x);

// Native 003706C8..00370795 (205 bytes), WB EEBCC0, AIGroup.cpp:4256.
void AIGroup::groupRotateFiringarc(const Coord3D *pos, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		if (!obj)
			continue;
		AIUpdateInterface *ai = obj->getAI();
		if (!ai)
			continue;
		RotateCoord dir(*pos);
		dir.sub(obj->getPosition());
		if (dir.GetLengthSqrd2D() < 1.0f)
			continue;
		dir.Normalize2D();
		float angle;
		if (dir.y < 0.0f)
			angle = -ACos(dir.x);
		else
			angle = ACos(dir.x);
		ai->getCommands()->rva0036F6A7(angle, cmdSource);
	}
}
