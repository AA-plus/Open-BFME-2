// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00505D91@Rva00506909@@AAEPAURva00506909Item@@ABVAsciiString@@@Z, retail 0x00505D91, 51 bytes.
// A private member of the Rva00506909 object (AITacticsGenerator.cpp), the
// +0x04 pool sibling of its rowed 0x00505DC4/0x00505DF7/0x00505E2A finders.
// Evidence: search ptr range +0x4 +0x8 for elem whose AsciiString at +0x2c matches arg via rowed compare 0x000069D6 then virtual slot 0x24 else null; caller 0x00506651.
#include "ascii_string.h"

class Rva00505D91Elem
{
public:
	virtual void dummy0();
	virtual void dummy1();
	virtual void dummy2();
	virtual void dummy3();
	virtual void dummy4();
	virtual void dummy5();
	virtual void dummy6();
	virtual void dummy7();
	virtual void dummy8();
	virtual void *slot9();
	char m_pad[0x2c - 4];
	AsciiString m_2c;
};

struct Rva00506909Item;

class Rva00506909
{
	char m_00[4];
	Rva00505D91Elem **m_04;
	Rva00505D91Elem **m_08;
	Rva00506909Item *rva00505D91(const AsciiString &name);
};

Rva00506909Item *Rva00506909::rva00505D91(const AsciiString &name)
{
	Rva00505D91Elem **end = m_08;
	for (Rva00505D91Elem **it = m_04; it != end; ++it) {
		AsciiString *s = (AsciiString *)((char *)*it + 0x2c);
		if (s->compare(name) == 0)
			return (Rva00506909Item *)(*it)->slot9();
	}
	return 0;
}
