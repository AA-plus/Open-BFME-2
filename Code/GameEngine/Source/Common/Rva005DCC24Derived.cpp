// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva005DCC24::~
// Rva005DCC24 at 0x005DCC24 (row in Rva004D759CDerived.cpp). Each class below
// stores its own vtable and tail-calls the base destructor; the base itself
// is only declared here (defined once in Rva004D759CDerived.cpp), because a
// same-TU definition would capture the call locally instead of at the ledger
// address. Owner identities are unproven (opaque Rva names). One ledger row
// per destructor, landed one commit at a time.

class Rva005DCC24
{
public:
	virtual ~Rva005DCC24();
};

class AIRoamingDefenseTactic : public Rva005DCC24
{
public:
	virtual ~AIRoamingDefenseTactic();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline AIRoamingDefenseTactic::~AIRoamingDefenseTactic()
{
}

// ?bfmeAnchorAIRoamingDefenseTacticDtor absent-from-retail
void bfmeAnchorAIRoamingDefenseTacticDtor(AIRoamingDefenseTactic *p)
{
	p->AIRoamingDefenseTactic::~AIRoamingDefenseTactic();
}

class AIStartWoTRBattleTactic : public Rva005DCC24
{
public:
	virtual ~AIStartWoTRBattleTactic();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline AIStartWoTRBattleTactic::~AIStartWoTRBattleTactic()
{
}

// ?bfmeAnchorAIStartWoTRBattleTacticDtor absent-from-retail
void bfmeAnchorAIStartWoTRBattleTacticDtor(AIStartWoTRBattleTactic *p)
{
	p->AIStartWoTRBattleTactic::~AIStartWoTRBattleTactic();
}

class AIReturnTheRingTactic : public Rva005DCC24
{
public:
	virtual ~AIReturnTheRingTactic();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline AIReturnTheRingTactic::~AIReturnTheRingTactic()
{
}

// ?bfmeAnchorAIReturnTheRingTacticDtor absent-from-retail
void bfmeAnchorAIReturnTheRingTacticDtor(AIReturnTheRingTactic *p)
{
	p->AIReturnTheRingTactic::~AIReturnTheRingTactic();
}

class AIRingHeroTactic : public Rva005DCC24
{
public:
	virtual ~AIRingHeroTactic();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline AIRingHeroTactic::~AIRingHeroTactic()
{
}

// ?bfmeAnchorAIRingHeroTacticDtor absent-from-retail
void bfmeAnchorAIRingHeroTacticDtor(AIRingHeroTactic *p)
{
	p->AIRingHeroTactic::~AIRingHeroTactic();
}

class AIFarmKillSquad : public Rva005DCC24
{
public:
	virtual ~AIFarmKillSquad();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline AIFarmKillSquad::~AIFarmKillSquad()
{
}

// ?bfmeAnchorAIFarmKillSquadDtor absent-from-retail
void bfmeAnchorAIFarmKillSquadDtor(AIFarmKillSquad *p)
{
	p->AIFarmKillSquad::~AIFarmKillSquad();
}
