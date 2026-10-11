// cl: /O1 /MD
class Player;
class Object
{
public:
	Player *getControllingPlayer() const;
};
class Rva002AA5E1Host
{
public:
	void rva002AA5E1(void *a, int b, float c);
};

// 0x002AA5E1 is rowed as Player::addSkillPointsForDamage (253B,
// PlayerAddSkillPointsForDamage.cpp; WB Player.cpp3341) - same
// (Object*, Object*, float) shape on the controlling player, so this
// resolves to the rowed body instead of the unrowed host spelling.
class Player
{
public:
	bool addSkillPointsForDamage(Object *a, const Object *b, float c);
};
class Rva0028B749Host
{
public:
	void rva0028B749(int a, float b);
};
// ?rva0028B749@Rva0028B749Host@@QAEXHM@Z
void Rva0028B749Host::rva0028B749(int a, float b)
{
	Player *p = ((const Object *)this)->getControllingPlayer();
	if (p != 0)
		p->addSkillPointsForDamage((Object *)this, (const Object *)a, b);
}
