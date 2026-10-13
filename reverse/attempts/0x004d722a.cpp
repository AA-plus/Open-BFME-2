// ?friend_checkForSleepTransitions@State@@QAE?AW4StateReturnType@@W42@@Z
// partial score=0.52 date=2026-10-13
// ?friend_checkForSleepTransitions@State@@QAE?AW4StateReturnType@@W42@@Z
// partial score=0.52 date=2026-10-12
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX-
// ?friend_checkForSleepTransitions@State@@QAE?AW4StateReturnType@@W42@@Z @0x004D722A 115B ret 4.
// Identity: WorldBuilder pin; the WB twin names State::friend_checkForSleepTransitions
// in EA's own StateMachine.cpp. Body ported from the BFME1 donor with the BFME2
// deltas: begin+count table at +0x10/+0x14, machine at +0x18. The recursion
// counter is retail .data 0x00E043FC.
typedef int Int;
typedef int StateID;
typedef bool Bool;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum
{
	EXIT_MACHINE_WITH_SUCCESS = 9998,
	EXIT_MACHINE_WITH_FAILURE = 9999
};

class StateMachine
{
public:
	StateReturnType internalSetState(StateID id);
};

class State;

typedef Bool (*StateTransFuncPtr)(State *state, void *userData);

struct BfmeTransitionInfo
{
	StateTransFuncPtr test;		// +0x00
	StateID toStateID;			// +0x04
	void *userData;				// +0x08
};

class StIncrementer
{
public:
	__forceinline StIncrementer(Int &count) : m_count(count) { ++m_count; }
	__forceinline ~StIncrementer() { --m_count; }

private:
	Int &m_count;
};

class State
{
public:
	StateReturnType friend_checkForSleepTransitions(StateReturnType status);

private:
	char m_pad00[0x10];
	BfmeTransitionInfo *m_transitions;	// +0x10
	Int m_transitionCount;				// +0x14
	StateMachine *m_machine;			// +0x18
};

// The BFME1 donor declares this counter inside the function; this unit spells
// it at unit scope (retail .data 0x00E043FC, no guard).
static Int checkfortransitionsnum = 0;

StateReturnType State::friend_checkForSleepTransitions(StateReturnType status)
{
	StateReturnType result = status;
	StIncrementer inc(checkfortransitionsnum);
	if (checkfortransitionsnum >= 20)
		result = STATE_FAILURE;
	else
	{
		Int remaining = m_transitionCount;
		const BfmeTransitionInfo *it = m_transitions;
		for (; remaining != 0; --remaining, ++it)
		{
			if (!it->test(this, it->userData))
				continue;

			// test returned true; check if the machine should exit, else move
			StateMachine *machine = m_machine;
			if (it->toStateID == EXIT_MACHINE_WITH_SUCCESS)
				result = STATE_SUCCESS;
			else if (it->toStateID == EXIT_MACHINE_WITH_FAILURE)
				result = STATE_FAILURE;
			else
				result = machine->internalSetState(it->toStateID);
			break;
		}
	}
	return result;
}
