// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX-
//
// ?isWithinAttackRange@Weapon@@QBE_NPBVObject@@0MH@Z @0x002CB933 52B
// Evidence: pinned name; BFME1 donor game/GameEngine/Source/GameLogic/Object/Weapon_isWithinAttackRange.cpp
// (isWithinAttackRange overloads forwarding source/target plus positions at +0x38 into inner);
// retail outer takes (source target float int) and forwards both plus derived positions.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Object
{
public:
	char m_pad[0x38];
	Coord3D m_position;
};

// LINK: 0x002CB35C is rowed as Rva002C9B80Owner::isWithinAttackRange (WeaponRva002CB2D1Range.cpp); the old six-slot
// call shape is kept through a member-pointer cast.
class Rva002C9B80Owner
{
public:
	bool isWithinAttackRange(Object *a, const Coord3D *b, Object *c, const Coord3D *d, float e, bool f);
};
typedef bool (Rva002C9B80Owner::*Rva002CB35CShape)(int, void *, void *, void *, float, int);

class Weapon
{
public:
	bool isWithinAttackRange(const Object *source, const Object *target, float extra, int flag) const;
	char isWithinAttackRange(Object *source, void *pos, float extra, int flag) const;
};

bool Weapon::isWithinAttackRange(const Object *source, const Object *target, float extra, int flag) const
{
	if (source && target)
		return (((Rva002C9B80Owner *)this)->*reinterpret_cast<Rva002CB35CShape>(&Rva002C9B80Owner::isWithinAttackRange))((int)source, (void *)&source->m_position, (void *)target, (void *)&target->m_position, extra, flag);
	return false;
}

// ?isWithinAttackRange@Weapon@@QBEDPAVObject@@PAXMH@Z @0x002CB902 49B
// Evidence: pin address-named; BFME1 donor Weapon_isWithinAttackRange.cpp Coord3D overload
// forwards (source sourcePos 0 pos extra flag) into 0x002CB35C; neighbour 0x002CB933 same inner.
char Weapon::isWithinAttackRange(Object *source, void *pos, float extra, int flag) const
{
	if (source && pos)
		return (((Rva002C9B80Owner *)this)->*reinterpret_cast<Rva002CB35CShape>(&Rva002C9B80Owner::isWithinAttackRange))((int)source, (void *)&source->m_position, 0, pos, extra, flag);
	return 0;
}
