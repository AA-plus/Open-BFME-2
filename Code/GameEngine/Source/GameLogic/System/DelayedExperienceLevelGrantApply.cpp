// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP=
#include "ascii_string.h"
// DelayedExperienceLevelGrantSystem's per-entry level application, retail
// 0x00420C8E..0x00420DF1 (357 bytes, thiscall, ret 12). Its one caller is
// the system's update (0x00420EB3 at 0x00420EF8), which drains the queued
// (object, level, grant) entries of DelayedExperienceLevelGrantXfer.cpp.
//
// Target facts: every +0x30 string of the level goes to
// Object::addAttributeModifierToPool(name, -1) and every +0x4C entry to the
// object's rowed 0x00293077; a CreateAHero object (template +0x11F bit 0x40)
// has its CreateAHeroManager record (by object +0x74) take the level's +0xFC
// command set; a granted level after logic frame 10 runs the system's
// unrowed 0x00420B61 (level, object) and sets model condition 0xD2 for three
// seconds (3 * frame rate); the experience tracker (object +0x264) takes the
// level (rowed 0x0039B2E6); a non-empty +0x58 condition set is applied
// (0x001E431E); a level with its +0x100 flag tells the object's
// "BannerCarrierUpdate" module (static name key) the +0xFC value; a +0x104
// value other than -1 goes to the object's rowed 0x0028EC68 (value, 0, 1).
// Structural inference: the method and level field names are not
// established; the views below are address-derived.

typedef int Int;
typedef unsigned int UnsignedInt;

class ModelConditionFlags
{
public:
	bool rva000B3EB3() const;									// 0x000B3EB3
};

template <class T> struct GrantVectorView
{
	T *m_begin;
	T *m_end;
	T *m_storage;
	UnsignedInt size() const { return (UnsignedInt)(m_end - m_begin); }
	T &operator[](UnsignedInt i) { return m_begin[i]; }
};

struct Rva0039B2E6Input;

struct ExperienceLevelView
{
	unsigned char m_pad00[0x30];
	GrantVectorView<AsciiString> m_attributeModifiers;		// +0x30
	unsigned char m_pad3C[0x4C - 0x3C];
	GrantVectorView<const void *> m_upgrades;				// +0x4C
	ModelConditionFlags m_conditions;						// +0x58
	unsigned char m_pad59[0xFC - 0x59];
	Int m_commandSet;										// +0xFC
	bool m_bannerCarrier;									// +0x100
	Int m_specialCondition;									// +0x104
};

struct ThingTemplateView
{
	unsigned char m_pad[0x11F];
	unsigned char m_11F;
};

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ModelConditionFlagType { MODELCONDITION_D2 = 0xD2 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);					// 0x00148E1A
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Module;

class Rva0039B2E6
{
public:
	void rva0039B2E6(const Rva0039B2E6Input &level);			// 0x0039B2E6
};

class Rva001E431E
{
public:
	void rva001E431E(const Int *flags);						// 0x001E431E
};

class Rva00496CA8
{
public:
	void rva00496CA8(Int value);								// 0x00496CA8
};

class DelayedExperienceLevelGrantSystem;

class Object
{
	friend class DelayedExperienceLevelGrantSystem;
public:
	bool addAttributeModifierToPool(const AsciiString &name, Int count);	// 0x0028EA91
	void rva00293077(const void *upgrade);					// 0x00293077
	void setSpecialModelConditionState(ModelConditionFlagType type, UnsignedInt frames);	// 0x0028AEB2
	void rva0028EC68(Int value, void *p, Int flag);			// 0x0028EC68
protected:
	Module *findModule(NameKeyType key) const;				// 0x0028B6D6
public:
	unsigned char m_pad00[4];
	ThingTemplateView *m_template;							// +0x04
	unsigned char m_pad08[0x74 - 0x08];
	Int m_heroID;											// +0x74
	unsigned char m_pad78[0x264 - 0x78];
	Rva0039B2E6 *m_experienceTracker;						// +0x264
};

class CreateAHeroData;
class CreateAHeroHero
{
public:
	bool UpdateCommandSet(UnsignedInt commandSet);			// 0x00407705
};
class Rva00219B9E
{
public:
	CreateAHeroData *rva002197A6(Int id);						// 0x002197A6
};
class CreateAHeroManager;
extern CreateAHeroManager *TheCreateAHeroManager;

class GameLogic;
extern GameLogic *TheGameLogic;
struct GameLogicFrameView
{
	unsigned char m_pad[0x40];
	UnsignedInt m_frame;										// +0x40
};

extern int g_Va00DBA4E4;

class DelayedExperienceLevelGrantSystem
{
public:
	void rva00420B61(ExperienceLevelView *level, Object *obj);	// 0x00420B61
	void rva00420C8E(ExperienceLevelView *level, Object *obj, bool grant);
};

// ?rva00420C8E@DelayedExperienceLevelGrantSystem@@QAEXPAUExperienceLevelView@@PAVObject@@_N@Z
void DelayedExperienceLevelGrantSystem::rva00420C8E(ExperienceLevelView *level, Object *obj, bool grant)
{
	UnsignedInt i;
	for (i = 0; i < level->m_attributeModifiers.size(); ++i)
		obj->addAttributeModifierToPool(level->m_attributeModifiers[i], -1);
	for (i = 0; i < level->m_upgrades.size(); ++i)
		obj->rva00293077(level->m_upgrades[i]);

	if (obj->m_template->m_11F & 0x40)
	{
		CreateAHeroData *hero = ((Rva00219B9E *)TheCreateAHeroManager)->rva002197A6(obj->m_heroID);
		if (hero)
			((CreateAHeroHero *)hero)->UpdateCommandSet(level->m_commandSet);
	}

	UnsignedInt frame = ((GameLogicFrameView *)TheGameLogic)->m_frame;
	if (grant && frame >= 10)
	{
		rva00420B61(level, obj);
		obj->setSpecialModelConditionState(MODELCONDITION_D2, g_Va00DBA4E4 * 3);
	}

	obj->m_experienceTracker->rva0039B2E6(*(const Rva0039B2E6Input *)level);

	if (level->m_conditions.rva000B3EB3())
		((Rva001E431E *)obj)->rva001E431E((const Int *)&level->m_conditions);

	if (level->m_bannerCarrier)
	{
		static NameKeyType key = TheNameKeyGenerator->nameToKey("BannerCarrierUpdate");
		Module *module = obj->findModule(key);
		if (module)
			((Rva00496CA8 *)module)->rva00496CA8(level->m_commandSet);
	}

	Int special = level->m_specialCondition;
	if (special != -1)
		obj->rva0028EC68(special, 0, 1);
}
