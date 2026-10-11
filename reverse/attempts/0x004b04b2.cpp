// ?rva004B04B2@SpecialDisguiseUpdate@@QAEX_N@Z
// partial score=0.98 date=2026-10-11
// Remaining: retail tests and sets object status bit 0x400000 with the mask
// in eax and two [esi+0x124] memory operands; every form tried here (plain
// word, volatile, bitfield, BitFlags-style test/set by value or reference,
// Object-level helpers, word-array bit index) either CSEs the load or the
// field address. Everything else (layout, 0x4C flags copy, callees) matches.
// cl: /O1 /MD /EHsc /DNDEBUG
// ?rva004B04B2@SpecialDisguiseUpdate@@QAEX_N@Z, retail 0x004B04B2..0x004B05F5
// (323 bytes): BFME2's form of Zero Hour's StealthUpdate::changeVisualDisguise
// on the SpecialDisguiseUpdate module (pinned name; its sibling 0x004B05F5
// calls it with true). If the module data's +0xDC flag is set and the object
// is of kind 0x12C, it raises object status bit 0x400000 (rowed 0x0028AE6D on
// the change), tells the object's +0x258 body slot 142 (7), sets weapon set
// flag 0x15 and runs the rowed 0x0028B78A(6). When the disguise template
// lookup (rowed 0x004B031E) answers, it saves the model condition flags and
// terrain decal, destroys the drawable (TheGameClient slot 29), makes a new
// one from the object's own template (restore) or the disguise template,
// binds it, places and turns it like the object, copies +0x8C to its
// +0xB0, restores the flags (rowed 0x001E42F2/0x001E431E) and decal (rowed
// 0x0027290C) and reselects it through TheInGameUI slot 66 if it was
// selected. Offsets past the cited callees are not otherwise named.
#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class Thing
{
public:
	Drawable *getDrawable() const;
	void setOrientation(float angle);
};

struct Coord3D;

class Rva004B04B2Body
{
public:
#define V(n) virtual void v##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
	V(90) V(91) V(92) V(93) V(94) V(95) V(96) V(97) V(98) V(99)
	V(100) V(101) V(102) V(103) V(104) V(105) V(106) V(107) V(108) V(109)
	V(110) V(111) V(112) V(113) V(114) V(115) V(116) V(117) V(118) V(119)
	V(120) V(121) V(122) V(123) V(124) V(125) V(126) V(127) V(128) V(129)
	V(130) V(131) V(132) V(133) V(134) V(135) V(136) V(137) V(138) V(139)
	V(140) V(141)
#undef V
	virtual void slot142(int value);
};

enum KindOfType { KINDOF_12C = 0x12C };
enum WeaponSetType { WEAPONSET_15 = 0x15 };

// The flags copy: Zero Hour's ModelConditionFlags, a 0x4C-byte bit set.
class WeaponTemplateSetHead
{
public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &that);
private:
	unsigned char m_bits[0x4C];
};


class Object
{
public:
	bool isKindOf(KindOfType t) const;
	void rva0028AE6D();
	void setWeaponSetFlag(WeaponSetType wst);
	void rva0028B78A(int value);
	unsigned char m_pad00[4];
	void *m_template;				// +0x04
	unsigned char m_pad08[0x38 - 8];
	unsigned char m_position[0xC];			// +0x38
	float m_orientation;				// +0x44
	unsigned char m_pad48[0x10C - 0x48];
	unsigned char m_modelConditionFlags[0x124 - 0x10C];	// +0x10C

	volatile unsigned int m_status;			// +0x124
	unsigned char m_pad128[0x258 - 0x128];
	Rva004B04B2Body *m_body;			// +0x258
};

class Rva001E42F2 { public: void rva001E42F2(const int *flags); };
class Rva001E431E { public: void rva001E431E(const int *flags); };

class Drawable
{
public:
	void setPosition(const Coord3D *pos);
	void rva0027290C(int decal);
	unsigned char m_pad00[0xB0];
	int m_B0;					// +0xB0
	unsigned char m_padB4[0x43C - 0xB4];
	bool m_selected;				// +0x43C
	unsigned char m_pad43D[0x44C - 0x43D];
	int m_terrainDecal;				// +0x44C
};

class GameClient
{
public:
#define V(n) virtual void v##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28)
#undef V
	virtual void destroyDrawable(Drawable *draw);	// slot 29
};
extern GameClient *TheGameClient;

class ThingFactory
{
public:
	void *newDrawable(void *thingTemplate, int statusBits, int arg);
};
extern ThingFactory *TheThingFactory;

class InGameUI
{
public:
#define V(n) virtual void v##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65)
#undef V
	virtual void selectDrawable(Drawable *draw);	// slot 66
};
extern InGameUI *TheInGameUI;

class Rva004B031E { public: void *rva004B031E(); };

struct SpecialDisguiseUpdateModuleData
{
	unsigned char m_pad00[0xDC];
	bool m_DC;					// +0xDC
};

class SpecialDisguiseUpdate
{
public:
	void rva004B04B2(bool restore);
private:
	int m_00;
	const SpecialDisguiseUpdateModuleData *m_data;	// +0x04
	Object *m_object;				// +0x08
	unsigned char m_pad0C[0x8C - 0xC];
	int m_8C;					// +0x8C
};

void SpecialDisguiseUpdate::rva004B04B2(bool restore)
{
	Object *self = m_object;
	Drawable *draw = ((Thing *)self)->getDrawable();
	bool wasSelected = draw->m_selected != 0;

	if (m_data->m_DC && self->isKindOf(KINDOF_12C))
	{
		if (!(self->m_status & 0x400000))
		{
			self->m_status |= 0x400000;
			self->rva0028AE6D();
		}
		self->m_body->slot142(7);
		self->setWeaponSetFlag(WEAPONSET_15);
		self->rva0028B78A(6);
	}

	if (((Rva004B031E *)this)->rva004B031E())
	{
		WeaponTemplateSetHead flags(*(const WeaponTemplateSetHead *)self->m_modelConditionFlags);
		int decal = draw->m_terrainDecal;
		TheGameClient->destroyDrawable(draw);
		void *tmpl = restore ? self->m_template : ((Rva004B031E *)this)->rva004B031E();
		draw = (Drawable *)TheThingFactory->newDrawable(tmpl, 0, -1);
		if (draw)
		{
			TheGameLogic->bindObjectAndDrawable(self, draw);
			draw->setPosition((const Coord3D *)self->m_position);
			((Thing *)draw)->setOrientation(self->m_orientation);
			draw->m_B0 = m_8C;
			((Rva001E42F2 *)self)->rva001E42F2((const int *)&flags);
			((Rva001E431E *)self)->rva001E431E((const int *)&flags);
			draw->rva0027290C(decal);
			if (wasSelected)
				TheInGameUI->selectDrawable(draw);
		}
	}
}
