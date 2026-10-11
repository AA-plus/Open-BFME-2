// ?rva005775C1@Rva0057709A@@QAEXH@Z
// partial score=0.95 date=2026-10-11
// cl: /MD /EHsc /DNDEBUG
//
// ?rva005775C1@Rva0057709A@@QAEXH@Z retail 0x005775C1 (115 bytes, EH,
// ret 4): slot 15 of the PlanRetreatsPhaseBehavior table 0x00C6E8A8 (owner
// built by the rowed 0x0057709A, the Impl at +0x08). When the Impl's +0x14
// selection holder already holds the army with this id (+0x0C) it refreshes
// that selection (rowed 0x00576FBA); otherwise it clears the holder (rowed
// 0x0057702E) and installs a new 0x1C-byte selection for the id, built by
// the unrowed selection constructor 0x005774E3 (pinned under an address
// name) and stored through the rowed 0x0057704C. The method name is a
// placeholder for the vtable slot.

struct Rva0057702EBase
{
	char m_pad00[0x0C];
	int m_0C;	// the selected army id
};
class Rva0057702E
{
public:
	void rva0057702E();
	Rva0057702EBase *m_ptr;
};
class Rva0057704C
{
public:
	void rva0057704C(Rva0057702EBase *selection);
};
class Rva00576FBA
{
public:
	void rva00576FBA();
};
class Rva005774E3
{
public:
	Rva005774E3(void *owner, int id);
private:
	char m_data[0x1C];
};
struct Rva005775C1Impl
{
	char m_pad00[0x14];
	Rva0057702E m_14;	// the current selection holder
};
class Rva0057709A
{
public:
	void rva005775C1(int id);
private:
	char m_pad00[0x08];
	Rva005775C1Impl *m_08;
};

void Rva0057709A::rva005775C1(int id)
{
	Rva0057702E *holder = &m_08->m_14;
	Rva0057702EBase *current = holder->m_ptr;
	if (current && current->m_0C == id)
	{
		((Rva00576FBA *)current)->rva00576FBA();
	}
	else
	{
		holder->rva0057702E();
		Rva005774E3 *selection = new Rva005774E3(m_08, id);
		((Rva0057704C *)&m_08->m_14)->rva0057704C((Rva0057702EBase *)selection);
	}
}
