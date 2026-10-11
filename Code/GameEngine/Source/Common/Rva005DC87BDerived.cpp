// cl: /MD
//
// Opaque single-inheritance destructors tail-calling AITacticSiege::~
// AITacticSiege at 0x005DC87B (row in Rva005DC73CDerived.cpp). Each class below
// stores its own vtable and tail-calls the base destructor; the base itself
// is only declared here (defined once in Rva005DC73CDerived.cpp), because a
// same-TU definition would capture the call locally instead of at the ledger
// address. Owner identities are unproven (opaque Rva names). One ledger row
// per destructor, landed one commit at a time.

class AITacticSiege
{
public:
	virtual ~AITacticSiege();
};

class AISiegeGatesTactic : public AITacticSiege
{
public:
	virtual ~AISiegeGatesTactic();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline AISiegeGatesTactic::~AISiegeGatesTactic()
{
}

// ?bfmeAnchorAISiegeGatesTacticDtor absent-from-retail
void bfmeAnchorAISiegeGatesTacticDtor(AISiegeGatesTactic *p)
{
	p->AISiegeGatesTactic::~AISiegeGatesTactic();
}

class AISimpleSiegeTactic : public AITacticSiege
{
public:
	virtual ~AISimpleSiegeTactic();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline AISimpleSiegeTactic::~AISimpleSiegeTactic()
{
}

// ?bfmeAnchorAISimpleSiegeTacticDtor absent-from-retail
void bfmeAnchorAISimpleSiegeTacticDtor(AISimpleSiegeTactic *p)
{
	p->AISimpleSiegeTactic::~AISimpleSiegeTactic();
}
