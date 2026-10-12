// cl: /DNDEBUG /MD
//
// ?friend_setGoalObject@AIUpdateInterface@@QAEXPAVObject@@@Z, retail 0x00262B0F, 42 bytes.
// Retail42B262B0F..262B39 RET4: machine30, lock38, virtual goal setter
// slot14 (+38), restoring the prior lock. WB E46FC0 has the same
// sequence and "Friend_setGlobalObject re-locking" diagnostic. ZH
// AIUpdate.cpp friend_setGoalObject has this exact diagnostic and
// behavior; the spelling is donor-carried. Native callers34BB5B,
// 26D3FB and3497E6 pass their Object victim without integer conversion.

class Object;

class StateMachine
{
public:
	virtual void s00();
	virtual void s04();
	virtual void s08();
	virtual void s0C();
	virtual void s10();
	virtual void s14();
	virtual void s18();
	virtual void s1C();
	virtual void s20();
	virtual void s24();
	virtual void s28();
	virtual void s2C();
	virtual void s30();
	virtual void s34();
	virtual void setGoalObject(const Object *obj);
	char m_pad04[0x38 - 4];
	bool m_locked;
};

class AIUpdateInterface
{
	char m_pad00[0x30];
	StateMachine *m_machine;
public:
	void friend_setGoalObject(Object *obj);
};

void AIUpdateInterface::friend_setGoalObject(Object *obj)
{
	bool wasLocked = m_machine->m_locked;
	m_machine->m_locked = false;
	m_machine->setGoalObject(obj);
	if (wasLocked)
		m_machine->m_locked = true;
}
