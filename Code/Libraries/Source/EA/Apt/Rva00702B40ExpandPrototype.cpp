// BFME 1 has two ICF-folded callers at 0x8CDE30 and 0x8CE410, so the target
// owner stays RVA-named. Retail at 0x702B40 reads two values from the payload
// at +4 and +8 and forwards them to the target's thiscall helper at 0x700170.
class Rva00700170;
// LINK: the expansion step is rowed as AptBasePtrStack::rva00700170 (0x00700170).
class AptBasePtrStack
{
public:
	void rva00700170(void *first, void *second);
};

struct Rva00702B40Payload
{
	int m_opcode;
	void *m_first;
	void *m_second;
};

void __cdecl rva00702b40(Rva00700170 *state, const Rva00702B40Payload *call)
{
	((AptBasePtrStack *)state)->rva00700170(call->m_first, call->m_second);
}
