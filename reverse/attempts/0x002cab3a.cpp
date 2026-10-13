// ?adjustTargetPositionOnVictim@WeaponTemplate@@QAE?AUTargetCoord@@PAVObject@@0_N@Z
// partial score=0.98 date=2026-10-13
// ?adjustTargetPositionOnVictim (W7-MO1 r1, 5B merge wall)
// FRAGMENT for WeaponTemplateTargetPositions.cpp + Object decls (see log).
// Native 002CAB3A..002CAC6E RET16 (308B); WB BB2780 (Weapon.cpp:1736..1749)
// identifies WeaponTemplate::adjustTargetPositionOnVictim.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct TargetHeightCapView { char unknown00[0x11c4]; float heightCap; };
int GetGameLogicRandomValue(int, int, char *, int);
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
				float c = cap;
				pos.z = c + pos.z;
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
