// ?rva003E59B0@ScriptConditions@@QAE_NPBVAsciiString@@0PAVParameter@@_N@Z
// partial score=0.80174 date=2026-10-13
// ?rva003E59B0@ScriptConditions@@QAE_NPBVAsciiString@@0PAVParameter@@_N@Z
// partial score=0.97 date=2026-10-12
// cl: /G7 /O1 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /I.
// ?rva003E59B0@ScriptConditions@@QAE_NPBVAsciiString@@0PAVParameter@@_N@Z, retail 0x003E59B0
// (313 bytes, RET 0x10): the unit form of the castle area test in ScriptConditions_Rva003E6ED0.cpp
// -- the named unit against the named castle or, with no castle name and a player parameter naming
// no player, the closest KindOf-120 object to the unit through the same filter chain; the unit's
// didEnter / didExit against the castle's areas 1..7.
#include "ascii_string.h"

class Player;
class Object;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD28, allow 0x0026137E, slot 2 0x00261368: +0x08 a player, +0x0C whether a hit allows.
class Rva0026137EFilter : public Rva000421C8
{
public:
	Rva0026137EFilter(Player *player, bool match) : m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
};

// The 224-bit KindOf mask; the (unused, bit) constructor is 0x00045411.
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(int unused, int bit) throw();	// 0x00045411
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

#define REALLY_FAR (100000 * 10.0f)

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class PolygonTrigger;

class Module
{
public:
	virtual void moduleSlot();
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();	// 0x003955DA
	PolygonTrigger *rva00395E53(int index);	// 0x00395E53
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	bool didEnter(PolygonTrigger *trigger);	// 0x0028D718
	bool didExit(PolygonTrigger *trigger);	// 0x0028D757
	char m_pad00[0x38];
	Coord3D m_pos;	// +0x38
	friend class ScriptConditions;
protected:
	Module *findModule(NameKeyType key) const;	// 0x0028B6D6
};

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);	// 0x002A7B91
};
extern PlayerList *ThePlayerList;

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;		// +0x0C
	AsciiString m_string;	// +0x10
};

class ScriptEngine
{
public:
	Object *getUnitNamed(const AsciiString &name);		// 0x003588E7
	int rva00357475(const AsciiString &name, bool *found);	// 0x00357475
};
extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
public:
	bool rva003E59B0(const AsciiString *unitName, const AsciiString *castleName, Parameter *playerParm, bool entered);
};

bool ScriptConditions::rva003E59B0(const AsciiString *unitName, const AsciiString *castleName,
	Parameter *playerParm, bool entered)
{
	Object *obj = TheScriptEngine->getUnitNamed(*unitName);
	if (!obj)
		return false;
	Object *castle;
	if (castleName) {
		castle = TheScriptEngine->getUnitNamed(*castleName);
	} else {
		if (!playerParm)
			return false;
		Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357475(playerParm->getString(), 0));
		if (player)
			return false;
		castle = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, 0,
			Rva0004584D(BfmeFixedStorage0004543D(0, 0x78), *(const BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)
				.link(&Rva0026137EFilter(player, true)));
	}
	if (!castle)
		return false;
	CastleBehavior *behavior = (CastleBehavior *)castle->findModule(CastleBehavior::rva0003955DA());
	if (!behavior)
		return false;
	int i = 0;
	do {
		++i;
		PolygonTrigger *area = behavior->rva00395E53(i);
		if (!area)
			return false;
		if (entered ? obj->didEnter(area) : obj->didExit(area))
			return true;
	} while (i < 7);
	return false;
}
