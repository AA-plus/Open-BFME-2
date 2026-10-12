// cl: /DNDEBUG /MD /EHsc /Ob2
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/BfmeNamedApplyBH.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// ScriptActions::bfmeAddBH 0x003C420A (59B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
//
// Open-BFME5: the named apply at retail 0x002F83D0, 62 bytes.  The name is
// handed to the registry by value; nothing happens unless it resolves.

class StringBaseNarrowBH
{
protected:
	StringBaseNarrowBH(const StringBaseNarrowBH &other) throw();

	~StringBaseNarrowBH(void) throw();

	char *m_bfmeNarrowBH;
};

class AsciiStringBH : public StringBaseNarrowBH
{
public:
	AsciiStringBH(const AsciiStringBH &other) throw() : StringBaseNarrowBH(other)
	{
	}

	~AsciiStringBH(void) throw()
	{
	}
};

class BfmeRegistryBH
{
public:
	void *bfmeFindBH(AsciiStringBH name) throw();
};

// retail 0x012ED80C is the game's TheSpecialPowerStore, so the global must carry
// that name and its pointee type.  SpecialPowerStore itself is declared by
// game/GameEngine/Source/Common/System/game_engine_subsystems.h; only the address
// of the global is referenced here, so a forward declaration of the pointee is
// enough and the registry view below is still reached by cast (which emits
// nothing).
class SpecialPowerStore;

extern SpecialPowerStore *TheSpecialPowerStore;	// retail 0x012ED80C

class AsciiString;
class SpecialPowerTemplate;
struct Coord3D;

class BfmeTargetBH
{
public:
	char m_bfmePadTBH[0x38];
	char m_bfmePosition[4];
};

// WB: a callgraph caller of FireSpecialPowerAtPosition, so a ScriptActions
// member; its own name is not recovered.
class ScriptActions
{
public:
	bool FireSpecialPowerAtPosition(const AsciiString &playerName,
		const SpecialPowerTemplate *power, const Coord3D *position) throw();

	void bfmeAddBH(const AsciiString &playerName, const AsciiStringBH &name, BfmeTargetBH *target);
};

void ScriptActions::bfmeAddBH(const AsciiString &playerName, const AsciiStringBH &name,
		BfmeTargetBH *target)
{
	void *found = ((BfmeRegistryBH *)TheSpecialPowerStore)->bfmeFindBH(name);

	if (found != 0)
		FireSpecialPowerAtPosition(playerName, (const SpecialPowerTemplate *)found,
			(const Coord3D *)target->m_bfmePosition);
}
