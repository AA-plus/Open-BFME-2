// cl: /MD
//
// Opaque single-inheritance destructor tail-calling AITacticDefensive::~
// AITacticDefensive at 0x005DCB27 (row in Rva004EDCE9Derived.cpp). The class below
// stores its own vtable (0xC71FBC, DIR32 auto-patch) and tail-calls the base
// destructor; the base itself is only declared here (defined once in
// Rva004EDCE9Derived.cpp), because a same-TU definition would capture the
// call locally instead of at the ledger address. Owner identity is unproven
// (opaque Rva name). One ledger row per destructor, landed one commit at a
// time.

class AITacticDefensive
{
public:
	virtual ~AITacticDefensive();
};

class Rva005AA735 : public AITacticDefensive
{
public:
	virtual ~Rva005AA735();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva005AA735::~Rva005AA735()
{
}

// ?bfmeAnchorRva005AA735Dtor absent-from-retail
void bfmeAnchorRva005AA735Dtor(Rva005AA735 *p)
{
	p->Rva005AA735::~Rva005AA735();
}
