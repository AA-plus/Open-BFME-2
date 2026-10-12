// ?rva0059BD85@LivingWorldAIArmyMover@@QAE_NPAURange0059BD85@@HPAX@Z
// cl: /O1 /MD
// ?rva0059BD85@LivingWorldAIArmyMover@@QAE_NPAURange0059BD85@@HPAX@Z @0x0059BD85 (52B)
// Thiscall range find over 20-byte stride comparing first field with key.
// Native callers59C7BC and59CBxx pass the army mover in ECX; the body
// does not read it. WB14FCAD0 independently makes the same member call.
// This repairs the earlier free-stdcall declaration; original method name
// remains unknown. Native52B and RET0C are unchanged; no new retail bytes.
// Count via signed idiv 0x14 then unsigned index loop with jbe. Middle
// arg unused but kept for ret 0xC. Caller 0x0059C7BC. Evidence leaf lane.
// Register note: retail saves esi AND edi, holds the index in esi and
// divides by edi. The index must be declared BEFORE the count so the
// scheduler allocates it to esi; declaring it after lets the divisor
// claim esi and the body drops to 50B with one pop instead of two.
struct Elem0059BD85
{
	void *m_key;
	char m_pad[16];
};
struct Range0059BD85
{
	Elem0059BD85 *m_begin;
	Elem0059BD85 *m_end;
};
class LivingWorldAIArmyMover {public:bool rva0059BD85(Range0059BD85*,int,void*);};
bool LivingWorldAIArmyMover::rva0059BD85(Range0059BD85 *range, int unused, void *key)
{
	unsigned int i = 0;
	int count = (char *)range->m_end - (char *)range->m_begin;
	count /= (int)sizeof(Elem0059BD85);
	for (; i < (unsigned int)count; ++i)
	{
		if (range->m_begin[i].m_key == key)
			return true;
	}
	return false;
}