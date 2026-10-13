// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD /O1 /arch:SSE /G7
//
// ??1AutoAbilityBehavior@@UAE@XZ, retail 0x0045A37F, 73 bytes.
// AutoAbilityBehavior dtor over the rowed UpdateModule base 0x0024A797.
// Restores three vtables 0x00C4175C/+0x0C 0x007EFF90/+0x10 0x00C41750,
// destroys the AsciiString at +0x20 through the folded 0x00036410, then calls
// the base dtor. Layout follows the pinned ctor at 0x0045A78F (same three
// stores plus string null at +0x20) and the rowed UpdateModule ctor at
// 0x00253390 in UpdateModuleCtor.cpp (MI base with vptrs at +0/+0xC/+0x10
// plus scalars to 0x20). Called by the audited ??_G wrapper at 0x0045A560
// (slot 0 of 0x00C4175C). Shape follows Rva0024A797Derived MI precedent.
// BFME1 donor AutoAbilityBehaviorDestructorThunk.cpp:65 proves the string
// plus UpdateModule base; retail followed.

#include "ascii_string.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum
{
	MAX_COMMANDS_PER_SET = 0x20
};

enum GUICommandType
{
	GUI_COMMAND_SPECIAL_POWER_BFME = 0x18
};

class Overridable
{
public:
	inline Overridable *friend_getFinalOverride() { if(m_nextOverride)return m_nextOverride->friend_getFinalOverride();return this; }
__declspec(noinline) inline const Overridable *friend_getFinalOverride() const { if(m_nextOverride)return m_nextOverride->friend_getFinalOverride(); return this; }
private:
	unsigned char m_pad00[4]; Overridable *m_nextOverride; unsigned char m_pad08[8];
};

class SpecialPowerTemplate : public Overridable
{
public:
	const SpecialPowerTemplate *getFO() const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }
	const AsciiString &getName() const { return getFO()->m_name; }
	Int getSpecialPowerType() const { return getFO()->m_type; }
	AsciiString m_name; // +0x10
	unsigned char m_pad14[0x1C - 0x14];
	Int m_type; // +0x1C
};

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class CommandButton
{
public:
	GUICommandType getCommandType() const { return m_command; }
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
private:
	unsigned char m_pad00[0x14];
	GUICommandType m_command; // +0x14
	unsigned char m_pad18[0x44 - 0x18];
	const SpecialPowerTemplate *m_specialPower; // +0x44
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int i) const;
};

class Object
{
public:
	const AsciiString *rva00290E67() const;
};

class ControlBar;
extern ControlBar *TheControlBar;

// TheControlBar's command-set lookup at 0x0031D5F8, rowed under an address
// name.
class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *name);
};


class Thing;
class ModuleData;

class BehaviorModuleBase
{
	virtual void unused();
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	virtual ~UpdateModule();
	UpdateModule(Thing *thing, const ModuleData *moduleData);
protected:
	Object *getObject() const { return m_object; }
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
};

#include "ascii_string.h"

struct Rva0045A6D3Arg
{
	char _pad[0x10];
	AsciiString m_10;
};

class AutoAbilityBehaviorModuleData
{
public:
	unsigned char m_pad00[0x18];
	AsciiString m_specialPowerName; // +0x18
	unsigned char m_pad1C[0x5C - 0x1C];
	Bool m_startsActive; // +0x5C
};

// Three target-observed float fields at +0x24/+0x28/+0x2C, grouped only
// to keep their constructor stores together; no original vector type is claimed.
struct AbilityStateVector
{
    float x, y, z;
    AbilityStateVector() { x = 0.0f; y = 0.0f; z = 0.0f; }
};
class AutoAbilityBehavior : public UpdateModule
{
public:
	virtual ~AutoAbilityBehavior();
	AutoAbilityBehavior(Thing *thing, const ModuleData *moduleData);
	void rva0045A413();
	void rva0045A6FE(void *button);
	int isAutoAbilityCommand(const Rva0045A6D3Arg *arg);

private:
	const AutoAbilityBehaviorModuleData *getAutoAbilityBehaviorModuleData() const { return (const AutoAbilityBehaviorModuleData *)m_moduleData; }
	AsciiString m_str20; // +0x20
	AbilityStateVector m_state; // +0x24..+0x2C: measured scalar layout
	Bool m_30;
};

int AutoAbilityBehavior::isAutoAbilityCommand(const Rva0045A6D3Arg *arg)
{
	if (m_str20.isEmpty() || m_str20.compare(arg->m_10) != 0)
		return 0;
	return 1;
}

AutoAbilityBehavior::~AutoAbilityBehavior()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleOther@@EAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Retail 0x0045A63F is a cdecl lookup, not a member (no ECX use and RET).
// The object list at +0x244 is null terminated; each primary module vslot
// +0x10 returns its name key. AutoAbilityBehavior's class string supplies
// the cached key. The optional command name is the module data's +0x18
// AsciiString, independently established by its matched destructor.
// No donor establishes the original public name of this lookup.
enum NameKeyType { NK_UNKNOWN = 0 };
class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

struct Rva0045A63FData
{
    char pad[0x18];
    StringBase<char> command;
};
class Rva0045A63FModule
{
public:
    virtual void slot0() = 0;
    virtual void slot4() = 0;
    virtual void slot8() = 0;
    virtual void slotC() = 0;
    virtual NameKeyType getModuleNameKey() const = 0;
    const Rva0045A63FData *data;
};
struct Rva0045A63FObject
{
    char pad[0x244];
    Rva0045A63FModule **modules;
};

Rva0045A63FModule *Rva0045A63F(const Rva0045A63FObject *obj, const AsciiString &command)
{
    static NameKeyType key = TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");
    Rva0045A63FModule *result = 0;
    for (Rva0045A63FModule **iter = obj->modules; *iter; ++iter)
    {
        if ((*iter)->getModuleNameKey() == key)
        {
            result = *iter;
            if (result->data->command.getLength() <= 0 || result->data->command.compare(*(const StringBase<char> *)&command) == 0)
                break;
            result = 0;
        }
    }
    return result;
}

// Native 45A78F..45A8C2, including LEAVE/RET8: 307 bytes. The matched
// 24AFAD factory and destructor/vtable cluster independently identify this
// constructor. BFME1 cee35b7d8ca077d7255f1c39cb69e9fd9627aa85,
// game/GameEngine/Source/GameLogic/Object/Behavior/AutoAbilityBehaviorConstructor.cpp,
// supplies the inactive clear/sleep semantics. The active command search,
// module-data +0x18/+0x5C and scalar fields come from BFME2 retail.
// Visible Overridable helpers reproduce both existing providers (24 and 14
// bytes); retaining the const call lets VC7.1 spill the selected template
// from ECX as retail does. No new helper identity or address pin is introduced.
AutoAbilityBehavior::AutoAbilityBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
	, m_30(false)
{
	const AutoAbilityBehaviorModuleData *data = getAutoAbilityBehaviorModuleData();
	if (data->m_startsActive)
	{
		Object *obj = getObject();
		const SpecialPowerTemplate *spTemplate = TheSpecialPowerStore->findSpecialPowerTemplate(data->m_specialPowerName);
		const AsciiString &spName = spTemplate->getName();
		const CommandSet *commandSet = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(obj->rva00290E67());
		for (Int i = 0; i < MAX_COMMANDS_PER_SET; i++)
		{
			const CommandButton *button = commandSet->getCommandButton(i);
			// Preserve the button while resolving and comparing override templates.
			const CommandButton *volatile savedButton = button;
			if (button == NULL || button->getCommandType() != GUI_COMMAND_SPECIAL_POWER_BFME)
				continue;
			const SpecialPowerTemplate *buttonTemplate = button->getSpecialPowerTemplate()->getFO();
			if (buttonTemplate->m_type != spTemplate->getFO()->m_type)
				continue;
			button = savedButton;
			if (button->getSpecialPowerTemplate()->getName() == spName)
			{
				rva0045A6FE((void *)button);
				break;
			}
		}
	}
	else
	{
		rva0045A413();
		setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
	}
}
