// cl: /MD /EHsc
// ??1Rva005EE05E@@UAE@XZ @0x005EE05E 14B
// Dtor stores vtable 0x008786A8 then tail-jmps to member clear at +4 through
// rowed 0x005EDFF5. Evidence: pin ??1Rva005EE05E, vtable immediate, rowed
// clear, callers deleting dtor plus thunk.
class RegionAwardOwner;
class AsciiString;

// The rowed 0x54-byte member constructor 0x005EDB74.
class Rva005EDE64
{
public:
	Rva005EDE64(RegionAwardOwner *owner, int value, const AsciiString &name);
private:
	char m_body[0x54];
};

class Rva005EDFF5
{
public:
	void clear();
	Rva005EDE64 *m_ptr;
};

class Rva005EE05E
{
public:
	Rva005EE05E(int value, const AsciiString &name);
	virtual ~Rva005EE05E();
private:
	Rva005EDFF5 m_04;	// +4
};

Rva005EE05E::~Rva005EE05E()
{
	m_04.clear();
}

// ??0Rva005EE05E@@QAE@HABVAsciiString@@@Z @0x005EE014 74B: the matching
// constructor (same vtable 0x008786A8, sole caller 0x005D1335): creates the
// +4 member around itself (passed as its RegionAwardOwner) and the two
// arguments through the rowed constructor 0x005EDB74.
Rva005EE05E::Rva005EE05E(int value, const AsciiString &name)
{
	m_04.m_ptr = new Rva005EDE64(reinterpret_cast<RegionAwardOwner *>(this), value, name);
}
