// cl: /MD /GX
// ?rva00239105@Rva00239105@@QAEXXZ @0x00239105 (29B): two-member dispatcher.
// Retail: esi=ecx; ecx=[esi+0x18]; je skip; call 0x42C5BC; ecx=[esi+0x1C];
// test; pop esi; je ret; jmp 0x42CADD (tail). No stack args (ret, not ret N).
// Callees pinned TU-local to the unclaimed 7B thunks (range 0, owned elsewhere);
// address-derived names.
class Rva00239105A
{
public:
	void thru();
};

class Rva0042CADDOwner
{
public:
	void rva0042CADD();	// rowed at 0x0042CADD
};

class Rva00239105
{
public:
	void rva00239105();
private:
	char m_pad[0x18];
	Rva00239105A *m_18;
	Rva0042CADDOwner *m_1C;
};

// ?rva00239105@Rva00239105@@QAEXXZ
void Rva00239105::rva00239105()
{
	if (m_18 != 0) {
		m_18->thru();
	}
	if (m_1C != 0) {
		m_1C->rva0042CADD();
	}
}
