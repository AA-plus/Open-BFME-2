// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva004ADC38@Rva004ADC38@@QAEXHHHHH@Z @0x004ADC38 80B ret 0x14.
// The owner lives at this-0x18. When it has no entry from 0x0028AC4E, or
// that entry's 0x001E46E1 float is not greater than zero, forward the five
// arguments to 0x004500A3 and set status 0x4A.

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

class Object;

struct Rva0028AC4EEntry;

class Rva001E46E1
{
public:
	float rva001E46E1(Object *obj);
};

class Object
{
public:
	const Rva0028AC4EEntry *rva0028AC4E() const;
	void setStatus(ObjectStatusTypes status, bool set);
};

class SpecialPowerTemplate;
class Object;
struct Coord3D;
class Waypoint;

// 0x004500A3 is rowed as SpecialAbilityUpdate::initiateIntentToDoSpecialPower
// (555B; slot 0); same five-word shape, so this resolves to the rowed body
// instead of the unrowed Rva004500A3 spelling (sole U on this unit).
class SpecialAbilityUpdate
{
public:
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *a, const Object *b, const Coord3D *c, unsigned int d, const Waypoint *e);
};

class Rva004ADC38
{
public:
	void rva004ADC38(int a, int b, int c, int d, int e);
};

void Rva004ADC38::rva004ADC38(int a, int b, int c, int d, int e)
{
	Object *owner = *(Object **)((char *)this - 0x18);
	const Rva0028AC4EEntry *entry = owner->rva0028AC4E();
	if (entry == 0 || ((Rva001E46E1 *)entry)->rva001E46E1(owner) != 0.0f)
	{
		((SpecialAbilityUpdate *)this)->SpecialAbilityUpdate::initiateIntentToDoSpecialPower((const SpecialPowerTemplate *)a, (const Object *)b, (const Coord3D *)c, d, (const Waypoint *)e);
		owner->setStatus((ObjectStatusTypes)0x4A, true);
	}
}
