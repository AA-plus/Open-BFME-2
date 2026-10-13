// ?rva00492BEB@SpecialAbilityUpdate@@QAE?AW4UpdateSleepTime@@XZ
// /arch:SSE comes from retail region flags (0x1D8E99..0x60273F: O1/SSE/G7); the holder local is load-bearing (reads owner->m_holder once, before the null tests).
// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /MD /ICode/Libraries/Include
//
// ?rva00492BEB@SpecialAbilityUpdate@@QAE?AW4UpdateSleepTime@@XZ @0x00492BEB 110B.
// When the dword at +0x20 is 2, look up the id at +0x30. If that object, the
// owner at this-8, its pointer at +0x258, and the pointer at +0x1F0 of that
// are all live, copy the found position at +0x38 into a stack Coord3D and
// pass it to 0x001E702E. Then tail into SpecialAbilityUpdate::update.

#include "../../../Common/GameLogicObjectLookupView.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0
};

#include "Lib/Coord3D.h"

class Object;
class Thing;

class Rva001E702E
{
public:
	void rva001E702E(Thing *obj, int pos, int flag);
};

class Rva00492BEBHolder
{
public:
	char m_pad[0x1F0];
	Rva001E702E *m_inner;
};

class Object
{
public:
	char m_pad[0x38];
	Coord3D m_pos;
	char m_pad44[0x258 - 0x44];
	Rva00492BEBHolder *m_holder;
};

extern GameLogic *TheGameLogic;

class SpecialAbilityUpdate
{
public:
	virtual UpdateSleepTime update();
	UpdateSleepTime rva00492BEB();

private:
	char m_pad[0x20 - 4];
	int m_mode;
	char m_pad24[0x30 - 0x24];
	ObjectID m_id;
};

UpdateSleepTime SpecialAbilityUpdate::rva00492BEB()
{
	if (m_mode == 2)
	{
		Object *owner = *(Object **)((char *)this - 8);
		Object *found = TheGameLogic->findObjectByID(this ? m_id : m_id);
		Rva00492BEBHolder *holder = owner->m_holder;
		if (found != 0 && owner->m_holder != 0)
		{
			Coord3D pos;
			pos.x = found->m_pos.x;
			pos.y = found->m_pos.y;
			pos.z = found->m_pos.z;
			if (holder->m_inner != 0)
				holder->m_inner->rva001E702E((Thing *)owner, (int)&pos, 0);
		}
	}
	return SpecialAbilityUpdate::update();
}
