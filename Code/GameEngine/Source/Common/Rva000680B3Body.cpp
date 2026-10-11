// cl: /DNDEBUG /MD
//
// Dump range 1 (0x000680B3 35B): dual guarded member dispatches. The first
// guard calls through +0x3850; the second restores esi before the branch
// and tail-jumps through +0x3854. Honest address-derived names; callees
// are pins (unrowed siblings 0x000EB3D1/0x000E7B04). No header edits.

// LINK: the two callees are rowed at 0x000EB3D1 and 0x000E7B04 on classes of their own names.
class Rva000EB3D1
{
public:
	void rva000EB3D1();
};

class Rva000E7B04
{
public:
	void rva000E7B04();
};

class Rva000680B3Host
{
public:
	void rva000680B3();

	char m_pad[0x3850];
	Rva000EB3D1 *m_3850; // +0x3850
	Rva000E7B04 *m_3854; // +0x3854
};

void Rva000680B3Host::rva000680B3()
{
	if (m_3850)
		m_3850->rva000EB3D1();
	if (m_3854)
		m_3854->rva000E7B04();
}
