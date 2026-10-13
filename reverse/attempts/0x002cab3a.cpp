// ?adjustTargetPositionOnVictim@WeaponTemplate@@QAE?AUTargetCoord@@PAVObject@@0_N@Z
// partial score=0.99 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ireference/shims/bfme2_ascii
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "ascii_string.h"
class Matrix3D;

enum ObjectStatusTypes
{
	TARGET_CONTACT_STATUS_55 = 0x55
};

class ThingTemplate
{
public:
	char m_pad00[0x108];
	unsigned char flag108;
	unsigned char flag109;
};

class Object
{
public:
	bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*)const;
	bool testStatus(ObjectStatusTypes) const;
	bool getWorldspaceBestContactPoint(Coord3D*,const Coord3D*,const char*,int,int,bool) const;
};

class Rva0073A1C0FloatField
{
public:
	float get() const;
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct TargetHeightCapView { char unknown00[0x11c4]; float heightCap; };
int GetGameLogicRandomValue(int, int, char *, int);
class Rva002CAAFA {
public:bool rva002CAAFA(Object *victim,Coord3D *out);
private:char unknown00[0x90];AsciiString bone;
};
// Target002CAAFA..002CAB3A: the WeaponTemplate caller supplies this and
// victim/output; native +90 StringBase and logical-bone query fix the layout.
// The old neutral ABI view name is preserved; original helper name unknown.
// ?rva002CAAFA@Rva002CAAFA@@QAE_NPAVObject@@PAUCoord3D@@@Z
bool Rva002CAAFA::rva002CAAFA(Object *victim,Coord3D *out)
{
 if(!bone.isEmpty()){
  if(victim->getSingleLogicalBonePosition(bone.str(),out,0))return true;
 }
 return false;
}
struct TargetCoord : Coord3D
{
	__forceinline TargetCoord() {}
	__forceinline TargetCoord(const TargetCoord &p) { x = p.x; y = p.y; z = p.z; }
};
class WeaponTemplate
{
public:
	TargetCoord adjustTargetPositionOnVictim(Object *source, Object *victim, bool randomContact);
};
TargetCoord WeaponTemplate::adjustTargetPositionOnVictim(Object *source, Object *victim, bool randomContact)
{
	TargetCoord pos;
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	if (!victim)
		return pos;
	if (reinterpret_cast<Rva002CAAFA *>(this)->rva002CAAFA(victim, &pos))
		return pos;
	if (randomContact) {
		victim->getWorldspaceBestContactPoint(&pos, (const Coord3D *)((const char *)source + 0x38), 0, 3,
			GetGameLogicRandomValue(0, 12345678, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Weapon.cpp", 1749), false);
	}
	else {
		static_cast<Coord3D &>(pos) = *(const Coord3D *)((const char *)victim + 0x38);
		float height = reinterpret_cast<const Rva0073A1C0FloatField *>((const char *)victim + 0xa8)->get();
		const ThingTemplate *victimT = *(const ThingTemplate *const *)((const char *)victim + 4);
		const ThingTemplate *sourceT = *(const ThingTemplate *const *)((const char *)source + 4);
		if ((victimT->flag108 & 0x80) && !(sourceT->flag109 & 8) && !source->testStatus(TARGET_CONTACT_STATUS_55) && victim->testStatus(TARGET_CONTACT_STATUS_55)) {
			const float &cap = reinterpret_cast<const TargetHeightCapView *>(TheWritableGlobalData)->heightCap;
			if (height > cap) {
				pos.z = cap + pos.z;
			}
			else {
				float z = pos.z;
				pos.z = z + height;
			}
		}
		else {
			float z = pos.z;
			pos.z = z + height;
		}
	}
	return pos;
}
