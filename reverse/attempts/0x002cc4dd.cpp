// ?rva002CC4DD@Weapon@@QAEXXZ
// partial score=0.95 date=2026-10-13
// ?rva002CC4DD@Weapon@@QAEXXZ
// partial score=0.95 date=2026-10-13
// ?rva002CC4DD@Weapon@@QAEXXZ
// partial score=0.94 date=2026-10-13
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// stlport
// ?rva002CC4DD@Weapon@@QAEXXZ @0x002CC4DD 155B trial r3: declaration-order
// variant (logic first) to force EDI-cached GameLogic + homed tmplName/owner.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"
#pragma function(memset)
extern "C" void *memset(void *dst, int value, unsigned int size);

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class ThingTemplate;
class Team;
struct CreateMask
{
	unsigned char data[0x10];
};
class Object;
class Player;
class GameLogic;

class WeaponTemplate
{
public:
	char m_pad00[0x178];
	AsciiString m_name178;
};

class Weapon
{
public:
	void rva002CC4DD();
private:
	char m_pad00[4];
	WeaponTemplate *m_template;
	ObjectID m_owner08;
	char m_pad0C[0x5C - 0x0C];
	ObjectID m_spawned5C;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	char m_pad00[0x74];
	ObjectID m_id74;
};

class Player
{
public:
	char m_pad00[0x2EC];
	Team *m_team2EC;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, bool flag);
};
extern ThingFactory *g_009FF000;

void Weapon::rva002CC4DD()
{
	const AsciiString &tmplName = m_template->m_name178;
	if (((const StringBase<char> *)&tmplName)->isEmpty())
		return;
	Object *owner;
	GameLogic *logic = TheGameLogic;
	owner = logic->findObjectByID(m_owner08);
	if (!owner)
	{
		m_spawned5C = INVALID_OBJECT_ID;
		return;
	}
	Object *spawned = logic->findObjectByID(m_spawned5C);
	_ReadWriteBarrier();
	if (spawned)
		return;
	m_spawned5C = INVALID_OBJECT_ID;
	void *tmpl = (void *)g_009FF000->findTemplate(tmplName);
	CreateMask mask;
	memset(&mask, 0, 0x10);
	Player *player = owner->getControllingPlayer();
	Team *team = player->m_team2EC;
	Object *created = ((ThingFactory *)g_009FF000)->newObject((const ThingTemplate *)tmpl, team, &mask, false);
	if (!created)
		return;
	m_spawned5C = created->m_id74;
}
