// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?triggerAbilityEffect@SpecialDisguiseUpdate@@UAEXXZ, retail 0x004B0653 (431 bytes).
// Slot 17 of SpecialDisguiseUpdate's vftable 0x00856398 (the address sits at
// 0x008563DC). Like the other SpecialAbilityUpdate slot-17 overrides it first
// runs the base slot (pinned triggerAbilityEffect 0x0045108D). Then, for an
// idle owner (AIUpdateInterface slot 110 at Object+0x258) in ability state 1
// (+0x24): if model condition 300 is already set (pinned Object test
// 0x0006F039) it is cleared and the pinned 0x004B04B2 gets true; otherwise
// the owner's contain module (Object+0x250) is told to act on its contents
// (slot 42) when it reports any (slot 69), the drawable gets the pinned
// 0x00275DCE(2, 0.2, 0.7, 2.0), condition 300 is set, 0x004B04B2 gets
// whether the owner is the local player's, and for the local player the
// drawable's "DisguiseStarted" sound (rowed keyed lookup 0x00274CD8) is
// played for the owner through TheAudio (slot 25), as in
// TurretAIStartRotOrPitchSound.cpp. Method identity beyond the slot is not
// established.
//
// ?rva004B04B2@SpecialDisguiseUpdate@@QAEX_N@Z, retail 0x004B04B2 (323 bytes).
// The visual swap the slot-17 override above calls with whether to take the
// owner's own template (true) or the disguise template (the rowed 0x004B031E
// lookup, false); WB's debug body 0x01106BA0 and Zero Hour's
// StealthUpdate::changeVisualDisguise give its shape. Where the module data's
// +0xDC flag is set and the owner passes the pinned test 0x0006F039(300) it
// sets condition 214, tells the AI (slot 142) 7, sets weapon-set flag 0x15 and
// calls 0x0028B78A(6). Then, if the disguise template exists, it copies the
// 0x4C-byte condition block at Object +0x10C (rowed 0x00045455), keeps the old
// drawable's +0x44C word, destroys the drawable (GameClient slot 29), creates
// the new one (0x002CF21B; WB spells two newDrawable calls, which gives retail's
// hoisted pushes and merged tail), binds it (0x0023CD4A), copies position,
// orientation and this+0x8C (drawable +0xB0), re-applies the conditions
// through the rowed 0x001E42F2/0x001E431E, restores the +0x44C word
// (0x0027290C) and re-selects it (InGameUI slot 66) if the old one was selected.

#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

class AIUpdateInterface
{
public:
	SLOT08(s00,s01,s02,s03,s04,s05,s06,s07)
	SLOT08(s08,s09,s0A,s0B,s0C,s0D,s0E,s0F)
	SLOT08(s10,s11,s12,s13,s14,s15,s16,s17)
	SLOT08(s18,s19,s1A,s1B,s1C,s1D,s1E,s1F)
	SLOT08(s20,s21,s22,s23,s24,s25,s26,s27)
	SLOT08(s28,s29,s2A,s2B,s2C,s2D,s2E,s2F)
	SLOT08(s30,s31,s32,s33,s34,s35,s36,s37)
	SLOT08(s38,s39,s3A,s3B,s3C,s3D,s3E,s3F)
	SLOT08(s40,s41,s42,s43,s44,s45,s46,s47)
	SLOT08(s48,s49,s4A,s4B,s4C,s4D,s4E,s4F)
	SLOT08(s50,s51,s52,s53,s54,s55,s56,s57)
	SLOT08(s58,s59,s5A,s5B,s5C,s5D,s5E,s5F)
	SLOT08(s60,s61,s62,s63,s64,s65,s66,s67)
	virtual void s68(); virtual void s69(); virtual void s6A(); virtual void s6B();
	virtual void s6C(); virtual void s6D();
	virtual bool isIdle(); // slot 110
	SLOT08(s6F,s70,s71,s72,s73,s74,s75,s76)
	SLOT08(s77,s78,s79,s7A,s7B,s7C,s7D,s7E)
	SLOT08(s7F,s80,s81,s82,s83,s84,s85,s86)
	virtual void s87(); virtual void s88(); virtual void s89(); virtual void s8A();
	virtual void s8B(); virtual void s8C(); virtual void s8D();
	virtual void rva004B04B2Slot142(int value); // slot 142 (+0x238)
};

class ContainModuleInterface
{
public:
	SLOT08(s00,s01,s02,s03,s04,s05,s06,s07)
	SLOT08(s08,s09,s0A,s0B,s0C,s0D,s0E,s0F)
	SLOT08(s10,s11,s12,s13,s14,s15,s16,s17)
	SLOT08(s18,s19,s1A,s1B,s1C,s1D,s1E,s1F)
	SLOT08(s20,s21,s22,s23,s24,s25,s26,s27)
	virtual void s28(); virtual void s29();
	virtual void rva42(int which); // slot 42
	virtual void s2B(); virtual void s2C(); virtual void s2D(); virtual void s2E(); virtual void s2F();
	SLOT08(s30,s31,s32,s33,s34,s35,s36,s37)
	SLOT08(s38,s39,s3A,s3B,s3C,s3D,s3E,s3F)
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44();
	virtual unsigned int rva69(int which); // slot 69
};

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);
	~Rva0036CA00Str() { if (m_ref) m_ref->Release_Ref(); }
	OpaqueRefCounted *m_ref;
};

class Rva002390CB
{
public:
	Rva002390CB();
	Rva002390CB(const Rva002390CB &other);
	int m_0;
	Rva0036CA00Str m_4;
};

class Thing
{
public:
	void setOrientation(float angle); // 0x0030AB9D
	unsigned char m_thingPad[0xB0];
};

class Drawable : public Thing
{
public:
	void setPosition(const Coord3D *position); // 0x002710E7
	void rva0027290C(int value);
	void rva00275DCE(int mode, float a, float b, float c);
	Rva002390CB rva00274CD8(const AsciiString &name); // keyed sound lookup

	int m_b0; // +0xB0
	unsigned char m_padB4[0x43C - 0xB4];
	bool m_43C; // +0x43C
	unsigned char m_pad43D[0x44C - 0x43D];
	int m_44C; // +0x44C
};

class ThingFactory
{
public:
	void *newDrawable(void *tmplate, int a, int b); // 0x002CF21B
};
extern ThingFactory *TheThingFactory;
extern GameLogic *TheGameLogic;

class GameClient
{
public:
	SLOT08(s00,s01,s02,s03,s04,s05,s06,s07)
	SLOT08(s08,s09,s0A,s0B,s0C,s0D,s0E,s0F)
	SLOT08(s10,s11,s12,s13,s14,s15,s16,s17)
	virtual void s18(); virtual void s19(); virtual void s1A(); virtual void s1B(); virtual void s1C();
	virtual void destroyDrawable(Drawable *draw); // slot 29 (+0x74)
};
extern GameClient *TheGameClient;

class InGameUI
{
public:
	SLOT08(s00,s01,s02,s03,s04,s05,s06,s07)
	SLOT08(s08,s09,s0A,s0B,s0C,s0D,s0E,s0F)
	SLOT08(s10,s11,s12,s13,s14,s15,s16,s17)
	SLOT08(s18,s19,s1A,s1B,s1C,s1D,s1E,s1F)
	SLOT08(s20,s21,s22,s23,s24,s25,s26,s27)
	SLOT08(s28,s29,s2A,s2B,s2C,s2D,s2E,s2F)
	SLOT08(s30,s31,s32,s33,s34,s35,s36,s37)
	SLOT08(s38,s39,s3A,s3B,s3C,s3D,s3E,s3F)
	virtual void s40(); virtual void s41();
	virtual void selectDrawable(Drawable *draw); // slot 66 (+0x108)
};
extern InGameUI *TheInGameUI;

class WeaponTemplateSetHead
{
public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &other); // 0x00045455
	unsigned char m_data[0x4C];
};

class Rva001E42F2
{
public:
	void rva001E42F2(const int *block);
};

class Rva001E431E
{
public:
	void rva001E431E(const int *block);
};

class Rva004B031E
{
public:
	void *rva004B031E();
};

enum WeaponSetType
{
	WEAPONSET_NONE = 0
};

class Player;

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
private:
	unsigned char m_pad00[0x10];
	Player *m_local; // +0x10
};

extern PlayerList *ThePlayerList;

class ModelConditionFlags
{
public:
	__forceinline unsigned int testMask(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	__forceinline void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	__forceinline void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class Object
{
public:
	bool rva0006F039(int bit) const; // tests a word-run bit at +0x10C
	void rva0028AE6D();
	void *getTemplate() const { return m_template; }
	void setWeaponSetFlag(WeaponSetType type);
	void rva0028B78A(int value);
	Drawable *getDrawable() const;
	Player *getControllingPlayer() const;

	// Inlined at its call sites; the out-of-line body is the matched row in
	// AIInternalMoveToStateOnExit.cpp, so this view must not emit a copy.
	__declspec(dllimport) __forceinline void setModelConditionState(unsigned int bit)
	{
		if (m_conditionBits.testMask(bit) == 0)
		{
			m_conditionBits.set(bit);
			rva0028AE6D();
		}
	}
	__declspec(dllimport) __forceinline void clearModelConditionState(unsigned int bit)
	{
		if (m_conditionBits.testMask(bit) != 0)
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}

	unsigned char m_pad000[0x04];
	void *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position; // +0x38
	float m_orientation; // +0x44
	unsigned char m_pad048[0x74 - 0x48];
	int m_id; // +0x74
	unsigned char m_pad078[0x10C - 0x78];
	ModelConditionFlags m_conditionBits; // +0x10C
	unsigned char m_pad158[0x250 - 0x158];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
};

class Rva002D9531
{
public:
	void rva002D9531(int objectID); // AudioEventRTS::setObjectID
};

template <int N> class DisguiseAudioSlots : public DisguiseAudioSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class DisguiseAudioSlots<0>
{
};

class AudioManager : public DisguiseAudioSlots<25>
{
public:
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event); // slot 25
};

extern AudioManager *TheAudio;

class ModuleData;

class SpecialAbilityUpdate
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16();
	virtual void triggerAbilityEffect();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x24 - 0x0C];
	int m_state; // +0x24
};

class SpecialDisguiseUpdateModuleData
{
public:
	unsigned char m_pad00[0xDC];
	bool m_DC; // +0xDC
};

class SpecialDisguiseUpdate : public SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
	void rva004B04B2(bool value);
private:
	unsigned char m_pad28[0x8C - 0x28];
	int m_8C; // +0x8C
};

// ?triggerAbilityEffect@SpecialDisguiseUpdate@@UAEXXZ @0x004B0653
void SpecialDisguiseUpdate::triggerAbilityEffect()
{
	SpecialAbilityUpdate::triggerAbilityEffect();

	Object *obj = m_object;
	if (!obj->m_ai->isIdle() || m_state != 1)
		return;

	if (obj->rva0006F039(300))
	{
		obj->clearModelConditionState(300);
		rva004B04B2(true);
		return;
	}

	ContainModuleInterface *contain = obj->m_contain;
	if (contain && contain->rva69(0) > 0)
		obj->m_contain->rva42(0);

	Drawable *draw = obj->getDrawable();
	if (draw)
		draw->rva00275DCE(2, 0.2f, 0.7f, 2.0f);

	obj->setModelConditionState(300);

	Player *localPlayer = ThePlayerList->getLocalPlayer();
	bool isLocal = true;
	if (obj->getControllingPlayer() != localPlayer)
		isLocal = false;
	rva004B04B2(isLocal);

	if (isLocal && draw)
	{
		BfmeAudioEventPrefix136 sound(*(const OpaqueRefElement4 *)&draw->rva00274CD8(AsciiString("DisguiseStarted")).m_4, 0);
		reinterpret_cast<Rva002D9531 *>(&sound)->rva002D9531(obj->m_id);
		TheAudio->addAudioEvent(&sound);
	}
}

// ?rva004B04B2@SpecialDisguiseUpdate@@QAEX_N@Z @0x004B04B2
void SpecialDisguiseUpdate::rva004B04B2(bool value)
{
	Object *obj = m_object;
	Drawable *draw = obj->getDrawable();
	bool wasSelected = draw->m_43C != 0;
	const SpecialDisguiseUpdateModuleData *data = (const SpecialDisguiseUpdateModuleData *)m_moduleData;
	if (data->m_DC && obj->rva0006F039(300))
	{
		obj->setModelConditionState(214);
		obj->m_ai->rva004B04B2Slot142(7);
		obj->setWeaponSetFlag((WeaponSetType)0x15);
		obj->rva0028B78A(6);
	}
	if (((Rva004B031E *)this)->rva004B031E())
	{
		WeaponTemplateSetHead conditions(*(const WeaponTemplateSetHead *)((const char *)obj + 0x10C));
		int savedValue = draw->m_44C;
		TheGameClient->destroyDrawable(draw);
		if (value)
			draw = (Drawable *)TheThingFactory->newDrawable(obj->getTemplate(), 0, -1);
		else
			draw = (Drawable *)TheThingFactory->newDrawable(((Rva004B031E *)this)->rva004B031E(), 0, -1);
		if (draw)
		{
			TheGameLogic->bindObjectAndDrawable((Object *)obj, (Drawable *)draw);
			draw->setPosition(&obj->m_position);
			draw->setOrientation(obj->m_orientation);
			draw->m_b0 = m_8C;
			((Rva001E42F2 *)obj)->rva001E42F2((const int *)&conditions);
			((Rva001E431E *)obj)->rva001E431E((const int *)&conditions);
			draw->rva0027290C(savedValue);
			if (wasSelected)
				TheInGameUI->selectDrawable(draw);
		}
	}
}
