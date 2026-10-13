// ?rva005D89F0@Rva005D8964@@UAE_NPAVObject@@@Z
// partial score=0.9 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Trial for 0x005D89F0 (115B): victim-within-50 predicate, slot 7 of Rva005D8964.
class Object;
class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};
class Object
{
public:
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface *const *)((const char *)this + 0x258); }
	float posX() const { return *(const float *)((const char *)this + 0x38); }
	float posY() const { return *(const float *)((const char *)this + 0x3C); }
	float posZ() const { return *(const float *)((const char *)this + 0x40); }
};
class Rva005EE2A0
{
public:
	virtual ~Rva005EE2A0();
};
class Rva005D8964 : public Rva005EE2A0
{
public:
	virtual bool rva005D89F0(Object *other);
};
bool Rva005D8964::rva005D89F0(Object *other)
{
	Object *victim = other->getAI()->getCurrentVictim();
	if (victim) {
		float ox = other->posX();
		float vx = victim->posX();
		float dx = vx - ox;
		float vz = victim->posZ();
		float oz = other->posZ();
		float dz = vz - oz;
		float vy = victim->posY();
		float oy = other->posY();
		float dy = vy - oy;
		float distSq = dz * dz + dy * dy + dx * dx;
		return distSq <= 2500.0f;
	}
	return false;
}
