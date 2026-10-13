// ?canMake@AIBuildableWallSegment@@UAEHPAVPlayer@@@Z
// partial score=0.97 date=2026-10-13
// ?canMake@AIBuildableWallSegment@@UAEHPAVPlayer@@@Z
// partial score=0.88 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /MD /EHsc
// WorldBuilder names 0x1538510 AIBuildableWallSegment::build. The paired
// retail body 0x00596D99..0x00596E13 preserves its base-build fallback,
// start-node lookup, virtual wall construction and terminal-hub ID update.
// Target offsets differ from WB: Object position +0x38 and ID +0x74;
// produced ID +0x24 and start-node ID +0x4C are observed in retail.
// Unrecovered virtual slots and class extents remain opaque.
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

class Object
{
public:
    char m_unrecovered00[0x38];
    Coord3D m_position;
    char m_unrecovered44[0x74 - 0x44];
    ObjectID m_id;
};

class Player
{
public:
	char m_pad00[0x94];
	unsigned int m_money;	// +0x94
};
extern GameLogic *TheGameLogic;

class Rva004D9A3C;
// Canonical layout from the matched 0x0039225E ctor row (Rva0039225ECtor.cpp):
// the ctor body order m_20=-1; m_unk00=0; m_array08=0; m_1C=0; m_1D=0; m_pad04=0; m_24=0
// is exactly retail's six ebx zero stores plus or [ebp-0x28],-1, and it makes cl
// hoist 0 into EBX for the whole body (push ebx first, cmp eax,ebx, mov [ebp-4],ebx).
class Rva0039205C
{
public:
	Rva0039205C()
	{
		m_20 = -1;
		m_unk00 = 0;
		m_array08 = 0;
		m_1C = 0;
		m_1D = 0;
		m_pad04 = 0;
		m_24 = 0;
	}
	~Rva0039205C();
public:
	int m_unk00; // +0
	int m_pad04; // +4
	Rva004D9A3C *m_array08; // +8
	unsigned char m_1C; // +0xC
	unsigned char m_1D; // +0xD
	int m_20; // +0x10
	int m_24; // +0x14
};
class BuildAssistant
{
public:
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual bool buildWall(Object *startNode, const Coord3D *startPosition,
                           const Coord3D &endPosition, Player *player,
                           bool option, Object **terminalHub);
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual bool quoteWall(Rva0039205C *result, Object *startNode,
                           const Coord3D *startPosition,
                           const Coord3D &endPosition, bool option);
};
class Rva00A027B8;
extern Rva00A027B8 *g_00A027B8;

class Rva0055ADD8
{
public:
    int rva0055ADD8(int ignored);
};

class AIBuildableStructure
{
public:
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual int canMake(Player *player); // slot 4 (base 0x00573CFB)
    virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12();
    virtual Coord3D getWorldPosition(); // slot 13, hidden result pointer
    virtual bool build(Player *player); // WB 0x1506950; retail 0x00573C7C, a vtable slot (0x0086E2AC)
protected:
    char m_unrecovered04[0x24 - 4];
    ObjectID m_producedObjectID;
    char m_unrecovered28[0x4C - 0x28];
};

class AIBuildableWallSegment : public AIBuildableStructure
{
public:
    bool build(Player *player);
    float getTotalCost(Player *player);
    int canMake(Player *player);
private:
    ObjectID m_startNodeID;
    char m_unrecovered50[4];
    int m_totalCost;
};

bool AIBuildableWallSegment::build(Player *player)
{
    if (m_startNodeID == INVALID_OBJECT_ID)
        return AIBuildableStructure::build(player);
    Object *startNode = TheGameLogic->findObjectByID(m_startNodeID);
    Object *terminalHub = 0;
    if (((BuildAssistant *)g_00A027B8)->buildWall(startNode, &startNode->m_position,
                            getWorldPosition(), player, false, &terminalHub))
    {
        m_producedObjectID = terminalHub->m_id;
        return true;
    }
    ((Rva0055ADD8 *)this)->rva0055ADD8((int)player);
    return false;
}

class Rva00573B23
{
public:
    float rva00573DCD(int player);
};

// WB 0x1538930 names getTotalCost. Retail 0x00596C6B..0x00596C7C
// tail-calls the existing base-cost provider for an unset start node;
// otherwise FILD establishes the signed cached cost at +0x54.
float AIBuildableWallSegment::getTotalCost(Player *player)
{
    if (m_startNodeID == INVALID_OBJECT_ID)
        return ((Rva00573B23 *)this)->rva00573DCD((int)player);
    return (float)m_totalCost;
}

// 0x00596E15 (218B, RET4): AIBuildableWallSegment::canMake (WB 0x15386C0).
// W7-MP5 r3: canonical Rva0039205C makes every retail instruction shape match
// (push ebx/esi, xor ebx,ebx, six ebx stores, mov [ebp-4],ebx, cmp eax,ebx).
// Without the dummy the success/failure dtors tail-merge to 202B (one shared
// call 0x39205C, return value in EBX); retail keeps TWO dtor sites and returns
// 0 via xor eax,eax / 9 via push 9+pop esi. AsciiString dummy keeps the paths
// separate (213B, nd~5): default-ctor form costs 11B (lea+mov [ebp-0x18],ebx+
// call 0x36410) + 4B frame; retail's extra 16B is its own failure-path dtor.
// Remaining lever: force the dtor duplication without the dummy (cl tail-merge).
int AIBuildableWallSegment::canMake(Player *player)
{
    register int zero = 0;
    if (m_startNodeID == zero)
        return AIBuildableStructure::canMake(player);
    Object *startNode = TheGameLogic->findObjectByID(m_startNodeID);
    Rva0039205C result;
    bool failed = !((BuildAssistant *)g_00A027B8)->quoteWall(
        &result, startNode, &startNode->m_position, getWorldPosition(), false);
    if (failed)
        return 9;
    if (result.m_20 != 0) {
        if (result.m_20 == 7)
            return 2;
        return 9;
    }
    if (player->m_money < result.m_pad04)
        return 2;
    m_totalCost = result.m_pad04;
    AsciiString dummy;
    return zero;
}
