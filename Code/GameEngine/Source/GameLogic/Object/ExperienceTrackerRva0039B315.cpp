// cl: /ICode/GameEngine/Source/Common /O1 /arch:SSE /DNDEBUG /MD /G6
//
// ?rva0039B315@ExperienceTracker@@QAEXM_N000@Z, retail 0x0039b315, 188 bytes. Banked partial (score 0.96) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// sink-chain LOOP (not recursion): walk m_experienceSink via findObjectByID,
// scale per tracker, single trailing transfer 0x0039B16F on the final tracker.
// Retail has no self-call and no loop-back before the transfer; the loop-back
// jne targets the lookup, and null-sink breaks to MULT (not return).
class Object;
class ExperienceTracker;

#include "GameLogicObjectLookupView.h"
class BfmeGlob939D:public GameLogic{public:char bfmeCall939D();};
extern GameLogic *TheGameLogic;

class PlayerList
{
public:
	int rva002A7C0B(bool b);			// 0x002A7C0B
};
extern PlayerList *ThePlayerList;

class MultiPlayMults
{
public:
	float getBuildingXPMult(int player) const;	// 0x002359A6
	float getUnitXPMult(int player) const;		// 0x0023598B
};

class GlobalData
{
public:
	unsigned char m_pad[0xEC4];
	MultiPlayMults m_multiPlayMults;		// +0xEC4
};
extern GlobalData *TheWritableGlobalData;

class ThingTemplate
{
public:
	bool isStructure() const { return (m_kindOf[0x108 - 0x100] & 0x80) != 0; }
private:
	unsigned char m_pad[0x100];
	unsigned char m_kindOf[0x10];			// +0x100
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
private:
	void *m_vtbl;
	const ThingTemplate *m_template;		// +0x04
	unsigned char m_pad08[0x264 - 8];
	ExperienceTracker *m_experienceTracker;		// +0x264
};

class ExperienceTracker
{
public:
	void rva0039B315(float amount, bool a, bool b, bool c, bool d);
	void rva0039B16F(float amount, bool a, bool b, bool c, bool d, float mult);	// 0x0039B16F

private:
	unsigned char m_pad00[0x1C];
	float m_experienceScalar;			// +0x1C
	unsigned char m_pad20[0x34 - 0x20];
	Object *m_parent;				// +0x34
	unsigned int m_experienceSink;			// +0x38
};

void ExperienceTracker::rva0039B315(float amount, bool a, bool b, bool c, bool d)
{
	ExperienceTracker *tracker = this;
	unsigned sink;
	GameLogic *gameLogic = TheGameLogic;
	goto cond;
body:
	{
		const Object *obj = gameLogic->findObjectByID((ObjectID)sink);
		if ((0 == obj))
			goto mult;
		d = false;
		c = true;
		amount *= tracker->m_experienceScalar;
		tracker = obj->getExperienceTracker();
	}
cond:
	if ((sink = tracker->m_experienceSink))
		goto body;
mult:
	float mult = 1.0f;
	if (reinterpret_cast < BfmeGlob939D*>(gameLogic)->bfmeCall939D())
	{
		const long player = ThePlayerList->rva002A7C0B(false);
		if (tracker->m_parent->getTemplate()->isStructure())
			mult = TheWritableGlobalData->m_multiPlayMults.getBuildingXPMult(player);
		else
			mult = TheWritableGlobalData->m_multiPlayMults.getUnitXPMult(player);
	}
	tracker->rva0039B16F(amount, a, b, c, d, mult);
}
