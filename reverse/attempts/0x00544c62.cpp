// ?rva00544C62@Rva00544C62@@QAEHXZ
// partial score=0.5 date=2026-10-13
// cl: /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// stlport
// ?rva00544C62@Rva00544C62@@QAEHXZ, retail 0x00544C62 (473 bytes). WorldBuilder
// AIHarvest.cpp (assert95) names the harvest-approach state body. First full
// reconstruction from the WB debug body and retail bytes. Vtable slots
// (AI 0x17C; result 0x1C/0x2C/0x44), offsets (machine +0x18/+0x14/+0x24,
// AI +0x258, this +0x20 24B store) and all callees are target facts; class and
// vocabulary names are honest address-derived views.
#include "unicode_string.h"
#include "Coord3D.h"

template <int N> class VGap : public VGap<N - 1>
{
public:
	virtual void vgap(char (*)[N]);
};
template <> class VGap<0>
{
};
class AIUpdateInterface : public VGap<95>
{
public:
	virtual void *slot95();
};
class Rva00544C62Result : public VGap<7>
{
public:
	virtual float slot07(int a, int b);
	virtual void v08(char (*)[8]);
	virtual void v09(char (*)[9]);
	virtual void v10(char (*)[10]);
	virtual void slot11(int a);
	virtual void v12(char (*)[12]);
	virtual void v13(char (*)[13]);
	virtual void v14(char (*)[14]);
	virtual void v15(char (*)[15]);
	virtual void v16(char (*)[16]);
	virtual void slot17(int a);
};
class Object
{
public:
	char m_pad00[0x258];
	AIUpdateInterface *m_ai;
};
class AIStateMachine
{
public:
	char m_pad00[0x14];
	Object *m_14;
};
class LocomotorSet;
class Pathfinder
{
public:
	bool AdjustDestination(Object *obj, const LocomotorSet &set, Coord3D *from, const Coord3D *to);
	bool IsPointOnWall(int pos, bool flag);
	bool IsPointOnRamp(const Coord3D *pos);
};
class BfmeThingCME
{
public:
	int rva0027F108(void *ptr, float f, int a, int b);
};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class AI
{
public:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
enum StateReturnType
{
	STATE_CONTINUE = 0
};
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};
struct Rva00544C62Vec24
{
	__int64 m_00;
	__int64 m_08;
	__int64 m_10;
};
class Rva00544C62 : public AIInternalMoveToState
{
public:
	int rva00544C62();
	char m_pad04[0x18 - 0x04];
	AIStateMachine *m_machine;
	Rva00544C62Vec24 m_20;
};
int Rva00544C62::rva00544C62()
{
	Rva00544C62Result *res = (Rva00544C62Result *)((AIUpdateInterface *)*(void **)((char *)*(void **)((char *)m_machine + 0x14) + 0x258))->slot95();
	if (!res)
		return -2;
	char *p24 = (char *)m_machine + 0x24;
	if (!p24)
		return -2;
	float f = res->slot07(0, 0);
	void *cme = (void *)((BfmeThingCME *)TheTerrainLogic)->rva0027F108(p24, f, 0, 0);
	if (!cme)
	{
		res->slot11(1);
		return -2;
	}
	int arg = *(int *)((char *)cme + 0x10);
	((Rva00544C62Result *)cme)->slot17(arg);
	*(Rva00544C62Vec24 *)((char *)this + 0x20) = *(Rva00544C62Vec24 *)p24;
	if (!*(char *)((char *)cme + 0x18))
		return AIInternalMoveToState::onEnter();
	Coord3D base;
	base.x = *(float *)((char *)cme + 0x1c);
	base.y = *(float *)((char *)cme + 0x20);
	base.z = *(float *)((char *)cme + 0x24);
	float s = GetGameLogicRandomValueReal(0.5f, 5.0f, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Ai\\AIHarvest.cpp", 0x5f);
	base.scale(s);
	for (int i = 0; i < 5; ++i)
	{
		Coord3D pos;
		pos.x = base.x + ((Coord3D *)((char *)this + 0x24))->x;
		pos.y = base.y + ((Coord3D *)((char *)this + 0x24))->y;
		AIStateMachine *m2 = m_machine;
		Object *o2 = m2->m_14;
		AIUpdateInterface *a2 = o2->m_ai;
		Pathfinder *pf = TheAI->m_pathfinder;
		if (!pf->AdjustDestination(o2, *(const LocomotorSet *)((char *)a2 + 0x1cc), &pos, 0))
			continue;
		if (pf->IsPointOnWall((int)&pos, 0))
			continue;
		if (pf->IsPointOnRamp(&pos))
			continue;
		*(Coord3D *)((char *)this + 0x24) = pos;
		break;
	}
	base.scale(0.5f);
	return AIInternalMoveToState::onEnter();
}
