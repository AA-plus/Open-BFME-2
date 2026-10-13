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

class Rva0039205C
{
public:
	Rva0039205C() : m_count(0), m_cost(0), m_status(-1) {}
	~Rva0039205C();
	int m_count;
	unsigned int m_cost;
	char m_pad08[8];
	int m_status;
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
// Start-node lookup, BuildAssistant quoteWall (slot 20) into result
// (+0x10 status, +0x04 cost), funds check at +0x94, cached cost at +0x54.
// Success path holds a dummy AsciiString so its result cleanup stays
// separate from the failure cleanups (retail 218B vs merged 202B).
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
    if (result.m_status != 0) {
        if (result.m_status == 7)
            return 2;
        return 9;
    }
    if (player->m_money < result.m_cost)
        return 2;
    m_totalCost = result.m_cost;
    AsciiString dummy("x");
    return zero;
}
