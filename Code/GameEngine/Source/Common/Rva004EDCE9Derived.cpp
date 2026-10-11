// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva004EDCE9::~
// Rva004EDCE9 at 0x004EDCE9 (pinned opaque SEH base dtor; identity
// unproven). Each class below stores its own vtable and tail-calls the base
// destructor; the base itself is only declared here (defined nowhere -- it
// resolves via the pin), because a same-TU definition would capture the call
// locally instead of at the ledger address. Owner identities are unproven
// (opaque Rva names). One ledger row per destructor, landed one commit at
// a time.

class Rva004EDCE9
{
public:
	virtual ~Rva004EDCE9();
};

class AITacticOffensive : public Rva004EDCE9
{
public:
	virtual ~AITacticOffensive();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline AITacticOffensive::~AITacticOffensive()
{
}

// ?bfmeAnchorAITacticOffensiveDtor absent-from-retail
void bfmeAnchorAITacticOffensiveDtor(AITacticOffensive *p)
{
	p->AITacticOffensive::~AITacticOffensive();
}

class AITacticDefensive : public Rva004EDCE9
{
public:
	virtual ~AITacticDefensive();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline AITacticDefensive::~AITacticDefensive()
{
}

// ?bfmeAnchorAITacticDefensiveDtor absent-from-retail
void bfmeAnchorAITacticDefensiveDtor(AITacticDefensive *p)
{
	p->AITacticDefensive::~AITacticDefensive();
}

class Rva005DCBE3 : public Rva004EDCE9
{
public:
	virtual ~Rva005DCBE3();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva005DCBE3::~Rva005DCBE3()
{
}

// ?bfmeAnchorRva005DCBE3Dtor absent-from-retail
void bfmeAnchorRva005DCBE3Dtor(Rva005DCBE3 *p)
{
	p->Rva005DCBE3::~Rva005DCBE3();
}

class Rva005DCC24 : public Rva004EDCE9
{
public:
	virtual ~Rva005DCC24();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva005DCC24::~Rva005DCC24()
{
}

// ?bfmeAnchorRva005DCC24Dtor absent-from-retail
void bfmeAnchorRva005DCC24Dtor(Rva005DCC24 *p)
{
	p->Rva005DCC24::~Rva005DCC24();
}
