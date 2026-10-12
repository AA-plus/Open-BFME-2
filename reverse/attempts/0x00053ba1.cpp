// ?shouldPlayLocally@MilesAudioManager@@QAE_NPBVAudioEventRTS@@@Z
// partial score=0.9 date=2026-10-12
// Patch for Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp:
// replace its Rva0036CA00Str class with the one below and insert the body after it.
class Rva0036CA00Str {
public:
    // The select-any copy 0x000A8C7C (Rva0036CA00StrCopy.cpp), visible here
    // so cl knows the copy keeps no pointer to itself.
    __declspec(noinline) Rva0036CA00Str(const Rva0036CA00Str &other) : m_ptr(other.m_ptr)
    {
        if (m_ptr) reinterpret_cast<OpaqueRefCounted *>(m_ptr)->Add_Ref();
    }
    ~Rva0036CA00Str() { reinterpret_cast<OpaqueRefCounted *>(m_ptr)->Release_Ref(); }
    PlayingAudio *operator->(void) const { return m_ptr; }
    PlayingAudio *get(void) const { return m_ptr; }
private:
    PlayingAudio *m_ptr;
};

// MilesAudioManager::shouldPlayLocally, retail 0x00053BA1 (320 B; WB 0x007A88A0,
// MilesAudioManager.cpp:14080..14109). Zero Hour's AudioManager test with
// BFME's two owner kinds: music (+0xB0 sound type 0) and type 3, sounds with
// no player restriction (+0x48 bits 0x20/0x40/0x80/0x100) and "everyone"
// sounds always play. A game-owned event (+0x30 kind 0) compares its owning
// player with the local one (the player bit when they are the same, else
// the allies or enemies bit by relationship to the local default team); a
// living-world event (kind 1) compares its owner with the living-world local
// player and its alliance test. The info reference (+0x08) is held counted.
class BfmeMemberRV;
class BfmeThingRV { public: BfmeMemberRV *bfmePickRV(void); };
class Team;
enum Relationship { REL_ENEMIES, REL_NEUTRAL, REL_ALLIES };
class Player
{
public:
    Relationship getRelationship(const Team *that) const;
    char at000[0x2EC];
    Team *m_defaultTeam;    // +0x2EC
};
class PlayerList { public: Player *getNthPlayer(int index); };
extern PlayerList *ThePlayerList;
class Rva002DA414 { public: void *rva002DA414(void); };
class Rva002D9C7A { public: int rva002D9C7A(void); };
class Rva002B2B66 { public: int rva002B2B66(void); };
class Rva002E071E { public: int rva002E0BC0(int playerID); };
struct LivingWorldLogicAudioView
{
    char at00[0x98];
    Rva002E071E *m_localPlayer;     // +0x98
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

bool MilesAudioManager::shouldPlayLocally(const AudioEventRTS *event)
{
    Rva0036CA00Str infoRef(*reinterpret_cast<const Rva0036CA00Str *>(&event->m_info));
    const AudioEventInfo *ei = reinterpret_cast<const AudioEventInfo *>(infoRef.get());

    if (ei->m_atB0 == 0 || ei->m_atB0 == 3 || (ei->m_type & 0x1E0) == 0 || (ei->m_type & 0x100))
        return true;

    if (event->m_viewType == 0)
    {
        if (!ThePlayerList)
            return true;
        Player *localPlayer = (Player *)((BfmeThingRV *)ThePlayerList)->bfmePickRV();
        Player *owningPlayer = ThePlayerList->getNthPlayer((int)((Rva002DA414 *)event)->rva002DA414());
        if ((ei->m_type & 0x20) && (ei->m_type & 1) && owningPlayer == 0)
            return true;
        if (owningPlayer == 0 || localPlayer == 0 || localPlayer->m_defaultTeam == 0)
            return false;
        if (owningPlayer == localPlayer)
            return (ei->m_type >> 5) & 1;
        if (owningPlayer->getRelationship(localPlayer->m_defaultTeam) == REL_ALLIES)
            return (ei->m_type >> 6) & 1;
        return (ei->m_type >> 7) & 1;
    }
    if (event->m_viewType == 1)
    {
        int owner = ((Rva002D9C7A *)event)->rva002D9C7A();
        if (((Rva002B2B66 *)TheLivingWorldLogic)->rva002B2B66() == owner)
            return (ei->m_type >> 5) & 1;
        Rva002E071E *local = ((LivingWorldLogicAudioView *)TheLivingWorldLogic)->m_localPlayer;
        if (local && (unsigned char)local->rva002E0BC0(owner))
            return (ei->m_type >> 6) & 1;
        return (ei->m_type >> 7) & 1;
    }
    return true;
}
