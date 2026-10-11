// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Zero Hour's ScriptConditions::evaluateScienceAcquired (retail 0x003E4403,
// 108B) and evaluateCanPurchaseScience (0x003E446F, 98B), next after the
// FromUnit evaluators as in Zero Hour: the science looked up by internal
// name on TheScienceStore first, then per player of the BFME2 player mask
// the rowed ScriptEngine science query 0x00357B3D (its row types the
// science as ObjectID) or Player::isCapableOfPurchasingScience.
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
typedef int PlayerMaskType;
enum ScienceType
{
    SCIENCE_INVALID = -1
};
enum ObjectID
{
    INVALID_ID = 0
};
class ScienceStore
{
public:
};
extern ScienceStore *TheScienceStore;
ScienceType __stdcall Rva001FF725Get(const AsciiString &);
// Native 1FF725 consumes only its stack argument and replaces ECX before
// the name lookup. A checked four-byte member-pointer view retains the
// callers' observed receiver load without asserting a second callee identity.
union NativeScienceCall {
 ScienceType (__stdcall *target)(const AsciiString &);
 ScienceType (ScienceStore::*member)(const AsciiString &) const;
};
typedef char SciencePointerWidth[sizeof(NativeScienceCall)==4 ? 1 : -1];
class Player
{
public:
    int getPlayerIndex() const { return m_playerIndex; }
    bool isCapableOfPurchasingScience(ScienceType science) const;
private:
    unsigned char m_pad00[0x54];
    int m_playerIndex; // +0x54
};
class PlayerList
{
public:
    Player *getEachPlayerFromMask(PlayerMaskType &maskToAdjust);
};
extern PlayerList *ThePlayerList;
class ScriptEngine
{
public:
    int rva00357B82(Parameter *playerParm);
    bool rva00357B3D(int playerIndex, ObjectID science, bool clearIt);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool evaluateScienceAcquired(Parameter *pPlayerParm, Parameter *pScienceParm);
    bool evaluateCanPurchaseScience(Parameter *pPlayerParm, Parameter *pScienceParm);
};

bool ScriptConditions::evaluateScienceAcquired(Parameter *pPlayerParm, Parameter *pScienceParm)
{
    NativeScienceCall call={&Rva001FF725Get};
    ScienceType science = (TheScienceStore->*call.member)(pScienceParm->getString());
    if (science == SCIENCE_INVALID)
        return false;
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask)
    {
        Player *player = ThePlayerList->getEachPlayerFromMask(mask);
        if (player && TheScriptEngine->rva00357B3D(player->getPlayerIndex(), (ObjectID)science, true))
            return true;
    }
    return false;
}

bool ScriptConditions::evaluateCanPurchaseScience(Parameter *pPlayerParm, Parameter *pScienceParm)
{
    NativeScienceCall call={&Rva001FF725Get};
    ScienceType science = (TheScienceStore->*call.member)(pScienceParm->getString());
    if (science == SCIENCE_INVALID)
        return false;
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask)
    {
        Player *player = ThePlayerList->getEachPlayerFromMask(mask);
        if (player && player->isCapableOfPurchasingScience(science))
            return true;
    }
    return false;
}
