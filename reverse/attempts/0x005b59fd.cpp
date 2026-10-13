// ?rva005B59FD@Class@AptCreateAHero@@QAEXXZ
// partial score=0.985 date=2026-10-13
// ?rva005B59FD@Class@AptCreateAHero@@QAEXXZ
// partial score=0.985 date=2026-10-13
// Retail 0x005B59FD (178B). Owner-embedded port in AptCreateAHeroClassConstructor.cpp
// compiles 177B with everything exact except the owner+0x21C address form:
// retail does mov+lea TWICE (owner to eax then esi, killing this); every
// spelling tried hoists 0x21C to edi with add (array-decay, explicit char
// arithmetic, volatile owner local, direct volatile, union member view).
// Tried 5 shapes, all neutral (177/178, same hoist). The hoist merges the two
// identical owner+0x21C computations; retail's source must defeat CSE in a way
// not yet found (different ASTs with same value still merge; volatile owner
// moved the second base to edi, not esi). Next: find what puts the second
// owner load into esi (this dead after delegate save) with lea instead of
// ecx+add; or a spelling whose two address computations don't merge.
// Kept in owner file (build-green): Class::rva005B59FD/rva005B5418/
// rva0047A69C decls + Rva005B3676Owner m_adder union view. Method reverted.
// t=30 model=muse-spark
void AptCreateAHero::Class::rva005B59FD()
{
	{ AsciiString name("AptCreateAHero::Class::Exit"); m_owner->m_adder.AddCommandMap(name, AptRef<AptCommandMap>(MakeDelegate(this, &Class::rva005B5418))); }
	{ AsciiString name("AptCreateAHero::Class::OnMapClick"); m_owner->m_adder.AddCommandMap(name, AptRef<AptCommandMap>(MakeDelegate(this, &Class::rva0047A69C))); }
}
