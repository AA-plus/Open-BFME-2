// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /O1 /G7 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// LivingWorldPlayer.cpp -- LivingWorldPlayer members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function; retail supplies the bytes. The player's queued command points at
// +0x298 drop by the dequeued unit's cost (rowed 0x004E1755) and clamp at 0.
//
// RemoveArmy takes an iterator into m_armyVec (+0x1B8, WB member name), hands
// the army's id (+0x78) to the game logic (0x0023D007, unrowed: forwards to
// the member at GameLogic+0x184) and erases it. The army vector erases
// through the folded pointer-vector erase (rowed as vector<void *>), so the
// view below holds void pointers.

typedef int Int;

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "FixedStorage128.h"
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/INIException.h"

class INI;

namespace _STL
{
	// Keep the already verified pointer-vector erase provider out of line.
	template <> void **vector<void *>::erase(void **position);
}

// Native2E12F3..2E134C and WBDE4FC0 prove the216-byte stride and
// the key atAC. Native2E1451..2E14DD and the verified UnitRevivalEntry
// copies establish the consumed experience/rank/upgrade fields. The remaining
// fields and the key-search method name remain unknown.
struct LivingWorldPlayerRecordView
{
	char unknown00[8];
    float experience;
    int rank, level;
    BfmeFixedStorage128 upgrades;
    char unknown94[0xAC - 0x94];
	int key;
	char unknownB0[0xD8 - 0xB0];
};

struct LivingWorldArmy
{
public:
	unsigned char m_pad00[0x78];
	Int m_id;				// +0x78
};

class GameLogic
{
public:
	void rva0023D007(Int armyID);		// 0x0023D007
};

extern GameLogic *TheGameLogic;

class Rva00319CED
{
public:
	Int rva004E1755();			// 0x004E1755, command-point cost
};

// The existing61B provider consumes a24-byte subrecord. These are
// pointer views into that record; no objects of the declaration-only class
// are constructed here.
class Rva001EAFC1 { public: Rva001EAFC1 &operator=(const Rva001EAFC1 &); };
struct LivingWorldRevivalUnitDataView {
    char unknown00[8]; float experience; int rank; BfmeFixedStorage128 upgrades;
    char unknown90[4]; char record94[0x18];
};
class Rva002E0D93;
class Rva002E204D { public: Rva002E0D93 *rva002E204D(Rva002E0D93 *); };
// Existing opaque native predicate at 0x00318F42. Native and WB identify
// the receiver as an element of m_armyVec; its original method is unknown.
class Mbr002E0B30 { public: unsigned char pred(); };
// Three-word RGB copies are proven by the native color setter and the
// recovered MultiplayerColorDefinition constructor. Reference getNumColors
// supplies the lazy-count semantics; target settings fields are38 and40.
// The extra color triplets' original field names remain unknown.
struct LivingWorldPlayerRGBColorView { float r,g,b; };
class MultiplayerColorDefinition { public:
 char unknown00[4]; LivingWorldPlayerRGBColorView rgbAt04;
 char unknown10[0x24-0x10]; LivingWorldPlayerRGBColorView rgbAt24,rgbAt30;
};
class MultiplayerSettings { public:
 MultiplayerColorDefinition *getColor(int);
 int getNumColors() { if(numColors==0) numColors=listCount; return numColors; }
private: char unknown00[0x38]; int listCount; int unknown3C; int numColors;
};
extern MultiplayerSettings *TheMultiplayerSettings;

// WBDE4E00 names FindArmyWithHero and asserts KINDOF_HERO at line787.
// Native2E1257 tests that flag at template113 and searches summary pairs40,
// stride8, through the existing integer-returning indexed getter. Its result
// is a pointer in this caller; the hero entry key lives atC0. Original template
// qualifiers and entry type names remain unknown, so retain opaque views.
class Rva0040CB2CIndexedField { public: int get(int) const; };
struct PlayerHeroEntryView { char unknown00[0xC0]; int heroKey; };
struct PlayerHeroPairView { int first,second; };
struct PlayerHeroSummaryView { char unknown00[0x40]; _STL::vector<PlayerHeroPairView> entries; };
struct PlayerHeroArmyView { char unknown00[0x78]; PlayerHeroSummaryView *summary; };
struct PlayerHeroTemplateView { char unknown00[0x113]; unsigned char flags; };

// Native AddArmy accesses the army summary through +78 and its two packed
// colors at24/28. Existing army-id and RGB views are retained separately;
// their original shared type spellings are not established by these accesses.
struct PlayerArmyColorSummaryView { char unknown00[0x24]; unsigned day,night; };
class ModuleData;
struct Rva0040E6D6Arg;
class Rva0023CFFCLogic {public:void rva0023CFFC(Rva0040E6D6Arg*);};

class LivingWorldPlayer
{
public:
	typedef _STL::vector<void *> ArmyVec;

	static void ParseLivingWorldPlayer(INI *ini, void *instance);

	void OnUnitDequeued(Rva00319CED *unit);
	void SetColorIndex(Int color);
    void AddArmy(LivingWorldArmy *army);
	void *FindArmyWithHero(void *thing, int key);
	void **RemoveArmy(void **&iter);
	bool rva002E12F3(int key);
	bool rva002E0B30();
    void RemoveRevivalUnit(int key);
    void GetRevivalUnitData(int key, LivingWorldRevivalUnitDataView *out);
    int rva002E199E(const void *thing);

private:
	unsigned char m_pad000[0x180];
	Int m_colorIndex;
	LivingWorldPlayerRGBColorView m_color184,m_color190,m_color19C;
	_STL::vector<LivingWorldPlayerRecordView> m_records;
	unsigned char m_pad1B4[4];
	ArmyVec m_armyVec;			// +0x1B8
	unsigned char m_pad1C4[0x298 - 0x1c4];
	Int m_queuedCommandPoints;		// +0x298
};

// LivingWorldPlayer::OnUnitDequeued, retail 0x002E0764.
void LivingWorldPlayer::OnUnitDequeued(Rva00319CED *unit)
{
	m_queuedCommandPoints -= unit->rva004E1755();
	if (m_queuedCommandPoints < 0)
		m_queuedCommandPoints = 0;
}

// LivingWorldPlayer::RemoveArmy, retail 0x002E10FE.
void **LivingWorldPlayer::RemoveArmy(void **&iter)
{
	TheGameLogic->rva0023D007(((LivingWorldArmy *)*iter)->m_id);
	return m_armyVec.erase(iter);
}

// Full89-byte RET4 body, with no relocations. The unsigned loop index and
// STLport size calculation retain retail's signed pointer-range division.
bool LivingWorldPlayer::rva002E12F3(int key)
{
	for (unsigned int i = 0; i < m_records.size(); ++i)
	{
		if (m_records[i].key == key)
			return true;
	}
	return false;
}

// WBDE5040 names RemoveRevivalUnit; native2E2225..2E2285 RET4.
// Reuse the full61B216-byte vector erase at2E204D under its owner spelling.
void LivingWorldPlayer::RemoveRevivalUnit(int key)
{
    if (key == 0) return;
    for (unsigned int i = 0; i < m_records.size(); ++i) {
        if (m_records[i].key == key) {
            reinterpret_cast<Rva002E204D *>(&m_records)->rva002E204D(
                reinterpret_cast<Rva002E0D93 *>(&m_records[i]));
            break;
        }
    }
}
// WBDE64F0 names GetRevivalUnitData; native2E1451..2E14DD RET8.
// Output field offsets are target facts; its original type name is unknown.
void LivingWorldPlayer::GetRevivalUnitData(int key, LivingWorldRevivalUnitDataView *out)
{
    if (key == 0) return;
    for (unsigned int i = 0; i < m_records.size(); ++i) {
        const LivingWorldPlayerRecordView &entry = m_records[i];
        if (entry.key == key) {
            out->rank = entry.rank;
            out->experience = entry.experience;
            out->upgrades = entry.upgrades;
            *reinterpret_cast<Rva001EAFC1 *>(out->record94) =
                *reinterpret_cast<const Rva001EAFC1 *>(entry.unknownB0);
            break;
        }
    }
}
// Native2E0B30..2E0B76, 70B; WBDE45B0 independently scans the army vector
// at1B8 and calls318F42 until true. Signed span arithmetic retains retail's
// recomputed vector count. Player/m_armyVec identity is established by the
// existing RemoveArmy body; the predicate and member names remain unknown.
bool LivingWorldPlayer::rva002E0B30()
{
 int *span=(int *)&m_armyVec;
 for(unsigned int i=0; i<(unsigned)((span[1]-span[0])>>2); ++i)
  if (((Mbr002E0B30 *)m_armyVec[i])->pred()) return true;
 return false;
}

// WBDE36A0 names SetColorIndex; native2E0F91..2E1001 RET4,112B.
// Keep the old index unless settings and an in-range new index are available.
// Once selected, copy definition triplets24/04/30 to player184/190/19C.
void LivingWorldPlayer::SetColorIndex(Int color)
{
 if(m_colorIndex==color || !TheMultiplayerSettings || color<0 ||
    color>=TheMultiplayerSettings->getNumColors()) return;
 m_colorIndex=color;
 MultiplayerColorDefinition *definition=TheMultiplayerSettings->getColor(color);
 if(definition) {
  m_color184=definition->rgbAt24;
  m_color190=definition->rgbAt04;
  m_color19C=definition->rgbAt30;
 }
}

// Native2E1257..2E12F3 RET8,156B; no borrowed callee types or new pins.
void *LivingWorldPlayer::FindArmyWithHero(void *thing, int key)
{
 if(!(((PlayerHeroTemplateView*)thing)->flags & 4))return 0;
 for(unsigned i=0;i<m_armyVec.size();++i) {
  PlayerHeroArmyView *army=(PlayerHeroArmyView*)m_armyVec[i];
  PlayerHeroSummaryView *summary=army->summary;
  if(!summary)continue;
  for(int j=0;j<(int)summary->entries.size();++j) {
   PlayerHeroEntryView *entry=(PlayerHeroEntryView*)((Rva0040CB2CIndexedField*)summary)->get(j);
   if(entry->heroKey==key)return army;
  }
 }
 return 0;
}

// WB DE3D70 names AddArmy; native2E246D..2E2504 RET4 establishes
// registration, the1B8 pointer-vector member and packed-color propagation.
// The established ModuleData pointer-vector provider is a storage view;
// it does not establish the original army-vector element spelling.
void LivingWorldPlayer::AddArmy(LivingWorldArmy *army)
{
 if (!army) return;
 ((_STL::vector<const ModuleData*>*)&m_armyVec)->push_back(*(const ModuleData**)&army);
 if(m_colorIndex>=0 && m_colorIndex<(army?TheMultiplayerSettings:TheMultiplayerSettings)->getNumColors()) {
  unsigned day=*(unsigned*)((char*)(army?TheMultiplayerSettings:TheMultiplayerSettings)->getColor(m_colorIndex)+0x10);
  unsigned night=*(unsigned*)((char*)(army?TheMultiplayerSettings:TheMultiplayerSettings)->getColor(m_colorIndex)+0x20);
  (*(PlayerArmyColorSummaryView**)((char*)army+0x78))->day=day;(*(PlayerArmyColorSummaryView**)((char*)army+0x78))->night=night;
 } else {(*(PlayerArmyColorSummaryView**)((char*)army+0x78))->day=0xff000000;(*(PlayerArmyColorSummaryView**)((char*)army+0x78))->night=0xff000000;}
 ((Rva0023CFFCLogic*)TheGameLogic)->rva0023CFFC((Rva0040E6D6Arg*)*(PlayerArmyColorSummaryView**)((char*)army+0x78));
}

// Native2E199E..2E1A1A, complete124B RET4; WBDE5150 independently
// searches the same216B revival records and compares record+D4 against
// the argument+64 through StringBase<char>::compare. Return keyAC on a
// match, zero otherwise. Original method and argument class names unknown.
int LivingWorldPlayer::rva002E199E(const void *thing)
{
    for (unsigned int i=0; i<m_records.size(); ++i) {
        const LivingWorldPlayerRecordView &record=m_records[i];
        const StringBase<char> &name=*(const StringBase<char> *)((const char *)&record+0xD4);
        const StringBase<char> &wanted=*(const StringBase<char> *)((const char *)thing+0x64);
        if (name.compare(wanted)==0) return record.key;
    }
    return 0;
}

// WB DE74D0 names LivingWorldPlayer::ParseLivingWorldPlayer at source lines
// 1489..1499. Both retail2E1D22 and WB share the two error literals, null-input
// checks, getNextToken/initFromINI and two conditional lookup calls before
// LivingWorldCampaign::AddPlayer. The two consumed stack arguments are INI*
// and an instance pointer; no stronger original instance type is asserted.
// Replace the split-out free-function placeholder and manual throw/zero
// ThrowInfo anchor with this named static callback and ordinary C++ throws.
// The record's original class/type names remain unknown; keep its rowed views.
// Retail body241B and EH handler778800 remain under their existing boundaries.
struct FieldParse
{
	const char *token;
	void (__cdecl *parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
};

// The parsers retail's LivingWorldPlayer table reaches, each an already-rowed
// body: INI::parseAsciiString (0x0002F11E), INI::parseInt (0x0002EF56) and
// INI::parseBool (0x0002E850). Declared with the real INI* first argument so the
// records below bind to those rowed symbols.

// Retail VA 0x00C049D8 (.rdata, file offset 0x00800E18): the seven field records
// of the 0x28-byte LivingWorldPlayer and the zero terminator, 128 bytes - the
// ledger's own bound. Four names through INI::parseAsciiString at +0xC/+0x10/
// +0x14 (the three template/region strings of the rowed record's +0x8 AsciiString
// pair) and three ints/bools at +0x18..+0x24. Every parse target is a rowed,
// byte-matched body.
// The full eight-record array emits ?g_00C049D8@@3QBUFieldParse@@B;
// its sizeof128 and every retail pointer are verified by data_rows.csv.
extern const struct FieldParse g_00C049D8[] =
{
	{ "PlayerTemplate",    &INI::parseAsciiString, 0, 0x0C },
	{ "AITemplate",        &INI::parseAsciiString, 0, 0x10 },
	{ "BaseRegion",        &INI::parseAsciiString, 0, 0x14 },
	{ "MP_SlotColorIndex", &INI::parseInt,         0, 0x18 },
	{ "IsDumb",             &INI::parseBool,        0, 0x24 },
	{ "TeamNumber",         &INI::parseInt,         0, 0x1C },
	{ "LWHandicap",         &INI::parseInt,         0, 0x20 },
	{ 0, 0, 0, 0 }
};

class Rva002E18C3Lookup
{
public:
	AsciiString *find(const AsciiString &name);
};

extern class Rva002E18C3Lookup *Va00DFF0B0Lookup;
extern class Rva002E18C3Lookup *Va00E03140Lookup;

class Rva002E0F1E
{
public:
	virtual ~Rva002E0F1E();
	UnicodeString m_04;
	AsciiString m_08;
	AsciiString m_0c;
	AsciiString m_10;
	AsciiString m_14;
	int m_18;
	int m_1c;
	int m_20;
	bool m_24;
};

class Rva002E0EF7 : public Rva002E0F1E
{
public:
	Rva002E0EF7();
};

class Rva002E0A0A
{
	char opaque[40];
};

class LivingWorldCampaign
{
public:
	void AddPlayer(const Rva002E0A0A &arg);
};

void LivingWorldPlayer::ParseLivingWorldPlayer(INI *ini, void *instance)
{
	if (ini == 0 || instance == 0)
	{
		throw INIException(3, "ParseLivingWorldPlayer::Invalid data passed in.");
	}
	Rva002E0EF7 record;
	const char *tok = ini->getNextToken(0);
	record.m_08 = tok;
	if (record.m_08.getLength() == 0)
	{
		throw INIException(3, "ParseLivingWorldPlayer::No name specified.");
	}
	ini->initFromINI(&record, g_00C049D8);
	AsciiString *found = Va00DFF0B0Lookup->find(record.m_0c);
	if (found == 0)
		goto done;
	if (record.m_24)
		goto append;
	{
		AsciiString *found2 = Va00E03140Lookup->find(record.m_10);
		if (found2 == 0)
			goto done;
	}
append:
	((LivingWorldCampaign *)instance)->AddPlayer(*(const Rva002E0A0A *)&record);
done:;
}
