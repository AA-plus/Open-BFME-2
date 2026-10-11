// ?rva00297000@Object@@QAEXPBVCommandButton@@PAV1@HH@Z
// partial score=0.97 date=2026-10-11
// NOTE: supersedes a prior 0.94 bank (in history) built on ZH doSpecialPower
// with options&0x20000000 gating, noinline rva0028C24C and a
// getCommandInterface helper. This version verifies better (102/104 insns;
// flags-byte gate, slot-1 virtual, explicit gotos) but compare both before
// the next attempt: the prior noinline/getCommandInterface ideas are untested
// here, and its SpecialPowerStore context may explain the virtual slot.
// cl: /DNDEBUG /MD
//
// AIGroup::groupDoCommandButtonAtPosition, retail 0x0036DCB8 (47 bytes), and
// AIGroup::groupDoCommandButtonAtObject, retail 0x0036DCE7 (47 bytes), ported
// from Zero Hour's GameEngine/Source/GameLogic/AI/AIGroup.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference): every member does
// the command button. BFME 2's Object::doCommandButtonAtPosition (0x00297149)
// and doCommandButtonAtObject (0x00297000) take a fourth argument, passed 0
// here. The member list follows AIGroupIsIdle.cpp's view (list head at +4).
#include <list>

class CommandButton;
struct Coord3D;
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};
enum WeaponLockType
{
	LOCKED_TEMPORARILY = 1
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class SpecialPowerTemplate;

template<int N>
class BitFlags
{
public:
	bool any() const;
	bool test(const void *other) const;
};

class AICommandInterface;
class Object;

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
	void rva0026C2D9(Object *obj, int a, CommandSourceType src);
	void rva0026C347(Object *obj, CommandSourceType src);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad[0x20];
};

class Module;
struct Rva00297000Ref
{
	virtual void *slot00();
	virtual const BitFlags<11> *slot04(void *out);
};

class CommandButton
{
public:
	unsigned char m_pad00[0x14];
	int m_commandType;			// +0x14
	unsigned char m_pad18[0x1C - 0x18];
	unsigned m_options;			// +0x1C
	unsigned char m_pad20[0x44 - 0x20];
	SpecialPowerTemplate *m_specialPower;	// +0x44
	unsigned char m_pad48[0x80 - 0x48];
	WeaponSlotType m_weaponSlot;		// +0x80
};

class Object
{
public:
	void rva00297149(const CommandButton *commandButton, const Coord3D *pos, int cmdSource, int bfmeArg);
	void rva00297000(const CommandButton *commandButton, Object *obj, int cmdSource, int bfmeArg);
	void doCommandButtonAtPosition(const CommandButton *commandButton, const Coord3D *pos, CommandSourceType cmdSource)
	{
		rva00297149(commandButton, pos, cmdSource, 0);
	}
	void doCommandButtonAtObject(const CommandButton *commandButton, Object *obj, CommandSourceType cmdSource)
	{
		rva00297000(commandButton, obj, cmdSource, 0);
	}
	void rva0028C24C();
	void doSpecialPowerAtObject(const SpecialPowerTemplate *tpl, Object *obj, unsigned int options, bool b);
	bool setWeaponLock(WeaponSlotType slot, WeaponLockType lock);
protected:
	class Module *findModule(NameKeyType key) const;
public:
	unsigned char m_pad00[0x1C8];
	unsigned m_disabled;			// +0x1C8
	unsigned char m_pad1CC[0x258 - 0x1CC];
	AIUpdateInterface *m_ai;		// +0x258
};

class AIGroup
{
public:
	void groupDoCommandButtonAtPosition( const CommandButton *commandButton, const Coord3D *pos, CommandSourceType cmdSource );
	void groupDoCommandButtonAtObject( const CommandButton *commandButton, Object *obj, CommandSourceType cmdSource );

private:
	std::list<Object *> m_memberList;
};

//-------------------------------------------------------------------------------------------------
void AIGroup::groupDoCommandButtonAtPosition( const CommandButton *commandButton, const Coord3D *pos, CommandSourceType cmdSource )
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		(*i)->doCommandButtonAtPosition( commandButton, pos, cmdSource );
	}
}

//-------------------------------------------------------------------------------------------------
void AIGroup::groupDoCommandButtonAtObject( const CommandButton *commandButton, Object *obj, CommandSourceType cmdSource )
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		(*i)->doCommandButtonAtObject( commandButton, obj, cmdSource );
	}
}

//-------------------------------------------------------------------------------------------------
void Object::rva00297000(const CommandButton *commandButton, Object *target, int cmdSource, int flags)
{
	int m_out;
	if (*(char *)&flags != 0) {
		static NameKeyType s_autoAbilityKey = TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");
		Module *module = findModule(s_autoAbilityKey);
		if (((const BitFlags<11> *)&m_disabled)->any()) {
			Rva00297000Ref *ref = (Rva00297000Ref *)((char *)module + 0x10);
			const BitFlags<11> *mask = ref->slot04(&m_out);
			if (!mask->test(&m_disabled))
				goto doReturn;
			goto skip1;
		}
	} else {
		if (((const BitFlags<11> *)&m_disabled)->any())
			return;
	}
skip1:
	if (commandButton == 0)
		return;
	AIUpdateInterface *ai = m_ai;
	switch (commandButton->m_commandType) {
	case 14:
		if (ai != 0)
			((AICommandInterface *)((char *)ai + 0x20))->aiIdle((CommandSourceType)cmdSource);
		break;
	case 23:
		rva0028C24C();
		setWeaponLock(commandButton->m_weaponSlot, LOCKED_TEMPORARILY);
		((AICommandInterface *)((char *)ai + 0x20))->rva0026C2D9(target, 1, (CommandSourceType)cmdSource);
		break;
	case 24:
	case 38: {
		if (commandButton->m_specialPower == 0)
			break;
		unsigned options = commandButton->m_options | 0x40000;
		if (*(char *)&flags != 0)
			options |= 0x20000000;
		doSpecialPowerAtObject(commandButton->m_specialPower, target, options, cmdSource == 1);
		break;
	}
	case 29:
		if (ai != 0)
			((AICommandInterface *)((char *)ai + 0x20))->rva0026C347(target, (CommandSourceType)cmdSource);
		break;
	}
doReturn:
	return;
}
