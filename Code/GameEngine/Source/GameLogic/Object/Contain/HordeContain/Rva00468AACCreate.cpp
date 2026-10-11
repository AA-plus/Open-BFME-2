// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva00468AAC@Rva00468AAC@@QAEPAVHordeMeleeSwarm@@PAX@Z, retail 0x00468AAC
// (55 bytes, RET 4): the melee-behaviour factory slot after the
// Rva00587752Record deleting destructor: a new 0x18-byte HordeMeleeSwarm
// for the given horde (rowed constructor 0x005843DA). Address-derived owner.
class HordeMeleeSwarm
{
public:
	HordeMeleeSwarm(void *horde);
private:
	unsigned char m_bytes[0x18];
};

class Rva00468AAC
{
public:
	HordeMeleeSwarm *rva00468AAC(void *horde);
};

HordeMeleeSwarm *Rva00468AAC::rva00468AAC(void *horde)
{
	return new HordeMeleeSwarm(horde);
}
