// cl: /O1 /EHsc /MD /arch:SSE
// VictoryConditions.cpp -- VictoryConditions members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function (vtable pairing); retail supplies the bytes. The body is Zero
// Hour's (GameLogic/ScriptEngine/VictoryConditions.cpp) with BFME2's observer
// branch, which also requires a positive count at +0x88, and a range check on
// the local slot.
//
// Layout (target evidence): m_players[20] at +0x18, m_localSlotNum at +0x68,
// m_singleAllianceRemaining at +0x85, m_isObserver at +0x86, an int at +0x88.
// hasBeenDefeated is vtable slot 15 (+0x3C).

typedef bool Bool;
typedef int Int;

class PlayerTemplate;
class Team;
enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };
class Player {
public:
 Bool rva002AA223() const;
 Bool isLocalPlayer() const;
 Relationship getRelationship(const Team *that) const;
 Team *getDefaultTeam() const { return defaultTeam; }
 char prefix[0x34]; const PlayerTemplate *playerTemplate;
 char pad38[0x2EC - 0x38]; Team *defaultTeam; // +0x2EC
};
class Rva0023D229 {public:void rva0023D24C(Int slot);};
class GameLogic;
extern GameLogic *TheGameLogic;
class PlayerList {public:char prefix[0x18];Player *neutralPlayer;};
extern PlayerList *ThePlayerList;
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator {public:NameKeyType nameToKey(const char *);};
extern NameKeyGenerator *TheNameKeyGenerator;
class PlayerTemplateStore {public:const PlayerTemplate *findPlayerTemplate(NameKeyType)const;};
extern PlayerTemplateStore *ThePlayerTemplateStore;


enum { MAX_PLAYER_COUNT = 20 };

class VictoryConditions
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual Bool hasAchievedVictory(Player *player);	// +0x38
	virtual Bool hasBeenDefeated(Player *player);		// +0x3C
	virtual Bool hasSinglePlayerBeenDefeated(Player *player);	// +0x40
 virtual void slot17();virtual void slot18();
	virtual Bool isLocalAlliedDefeat();			// +0x4C
 virtual void slot20();virtual void slot21();virtual void slot22();
 virtual void slot23();virtual void slot24();virtual void slot25();
 virtual Bool rva00420017(Player *player);


private:
	unsigned char m_pad04[0x18 - 4];
	Player *m_players[MAX_PLAYER_COUNT];		// +0x18
	Int m_localSlotNum;				// +0x68
	unsigned char m_pad6C[0x85 - 0x6c];
	Bool m_singleAllianceRemaining;			// +0x85
	Bool m_isObserver;				// +0x86
	Int m_field88;					// +0x88
 Int m_cachedPlayerCount; // +0x8C
};

// Zero Hour's file-static areAllies, retail 0x0041FE35 (46 bytes): kept out
// of line, cl 7.1 passes its two players in EDI and ESI.
#pragma auto_inline(off)
static Bool areAllies(const Player *p1, const Player *p2)
{
	if (p1 != p2 &&
		p1->getRelationship(p2->getDefaultTeam()) == ALLIES &&
		p2->getRelationship(p1->getDefaultTeam()) == ALLIES)
		return true;
	return false;
}
#pragma auto_inline(on)

// VictoryConditions::hasAchievedVictory, retail 0x0041FEEB (131 bytes),
// vtable slot 14: Zero Hour's body, which BFME2 also refuses for the player
// flagged by 0x002AA223, gates on a positive +0x88 count and reports the
// winning slot to TheGameLogic (0x0023D24C). Retail saves EBX/EDI only after
// the early return (126 of 131 bytes here); banked at 0.93.
// ?hasAchievedVictory@VictoryConditions@@UAE_NPAVPlayer@@@Z present-unmatched
Bool VictoryConditions::hasAchievedVictory(Player *player)
{
	if (!player || player->rva002AA223())
		return false;

	if (m_singleAllianceRemaining && m_field88 > 0)
	{
		for (Int i=0; i<MAX_PLAYER_COUNT; ++i)
		{
			if (m_players[i] && !hasSinglePlayerBeenDefeated(m_players[i]) && (player == m_players[i] || areAllies(m_players[i], player)))
			{
				((Rva0023D229 *)TheGameLogic)->rva0023D24C(i);
				return true;
			}
		}
	}

	return false;
}

// VictoryConditions::isLocalAlliedDefeat, retail 0x004200CB.
Bool VictoryConditions::isLocalAlliedDefeat()
{
	if (m_isObserver)
	{
		if (m_field88 > 0)
			return m_singleAllianceRemaining;
		return false;
	}
	if (m_localSlotNum < 0 || m_localSlotNum >= sizeof(m_players) / sizeof(m_players[0]))
		return false;
	return hasBeenDefeated(m_players[m_localSlotNum]);
}

// Native420017..42008F RET4; WB11156D0 VictoryConditions.cpp cache-one flow.
// Same eligibility test as GeneralsMD cachePlayerPtrs; target extracts it into
// a bool helper and uses the member counter+8C. Original helper name unknown.
Bool VictoryConditions::rva00420017(Player *player)
{
 const PlayerTemplate *civilian = ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey("FactionCivilian"));
 if (player && player != ThePlayerList->neutralPlayer && player->playerTemplate && player->playerTemplate != civilian && !player->rva002AA223()) {
  m_players[m_cachedPlayerCount] = player;
  if (m_players[m_cachedPlayerCount]->isLocalPlayer()) m_localSlotNum=m_cachedPlayerCount;
  ++m_cachedPlayerCount;
  return true;
 }
 return false;
}
