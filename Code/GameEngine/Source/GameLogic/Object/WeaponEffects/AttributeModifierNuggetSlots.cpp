// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// AttributeModifierNugget (Made002CC64B, vtable 0x00C64370) slots 5 and 6,
// shaped as the ParalyzeNugget's rowed pair 0x005091D6/0x0050921D
// (Made002CC711Ctor.cpp):
// ?rva00508B9E@Made002CC64B@@UAEXPAURva00508987Weapon@@PAVObject@@@Z, retail
// 0x00508B9E (71 bytes): an accepted target (slot 1) gets the modifier (rowed
// 0x00508987); with a positive radius (+0x130) the area around the target's
// position follows through slot 6.
// ?rva00508C46@Made002CC64B@@UAEXPAURva00508987Weapon@@PBUCoord3D@@@Z, retail
// 0x00508C46 (149 bytes): every Object within the radius (at least 1) of the
// position (ThePartitionManager 0x006255D0, distance type 3) that slot 1
// accepts gets the modifier.
// Storage view: the constructor lives in Made002CC64BCtor.cpp; nothing here
// emits a vtable.
#include "../../../Common/PartitionRangeQueryCallView.h"

struct Coord3D;
struct Rva00508987Weapon;

class Object
{
public:
	char m_pad00[0x38];
	float m_x38;	// +0x38, the position
};

extern PartitionManager *ThePartitionManager;

class Rva00507823
{
public:
	virtual ~Rva00507823();
	virtual bool accepts(Rva00508987Weapon *weapon, Object *target) = 0;
	virtual void s08() = 0; virtual void s0C() = 0; virtual void s10() = 0;
	virtual void rva00508B9E(Rva00508987Weapon *weapon, Object *target) = 0;
	virtual void rva00508C46(Rva00508987Weapon *weapon, const Coord3D *position) = 0;
private:
	char m_pad[0x128 - 4];
};

class Made002CC64B : public Rva00507823
{
public:
	void rva00508987(Rva00508987Weapon *weapon, Object *target);
	virtual void rva00508B9E(Rva00508987Weapon *weapon, Object *target);
	virtual void rva00508C46(Rva00508987Weapon *weapon, const Coord3D *position);
private:
	char m_pad128[0x130 - 0x128];
	float m_130;	// +0x130, the effect radius
};

void Made002CC64B::rva00508B9E(Rva00508987Weapon *weapon, Object *target)
{
	if (accepts(weapon, target))
		rva00508987(weapon, target);
	if (m_130 > 0.0f)
		rva00508C46(weapon, (const Coord3D *)&target->m_x38);
}

void Made002CC64B::rva00508C46(Rva00508987Weapon *weapon, const Coord3D *position)
{
	float range = m_130 > 1.0f ? m_130 : 1.0f;
	BfmeWideResult result = ThePartitionManager->rva006255D0(position, range, 3, 0);
	for (Object *target = result.next(); target; target = result.next())
		if (accepts(weapon, target))
			rva00508987(weapon, target);
}
