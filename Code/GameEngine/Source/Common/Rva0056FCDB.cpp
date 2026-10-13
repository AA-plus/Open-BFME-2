// cl: /O1 /arch:SSE /G7 /Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?rva0056FCDB@Rva0056FCDB@@QAEXF@Z @0x0056FCDB 24B. Address-derived class and method; call target and field store are packet evidence.
int Rva0056F690Hook(int, int);

class Rva0056FCDB
{
public:
	void rva0056FCDB(short value);
	int m_unknown;
	int m_value;
};

// Select-any like the AptOnlineLogin.cpp copy (this retail body comes first in
// link order, so it is the copy the link keeps); the anchor keeps the body emitted.
inline void Rva0056FCDB::rva0056FCDB(short value)
{
	m_value = Rva0056F690Hook(value, value);
}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitRva0056FCDBSetter@@YAXPAVRva0056FCDB@@F@Z absent-from-retail
void bfmeEmitRva0056FCDBSetter(Rva0056FCDB *p, short value)
{
	p->Rva0056FCDB::rva0056FCDB(value);
}
