// ?rva002AEEA7@Player@@QAEXH@Z
// partial score=0.7 date=2026-10-13
// ?rva002AEEA7@Player@@QAEXH@Z
// partial score=0.93 date=2026-10-13
// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /O1 /arch:SSE /G7
// stlport
// ?rva002AEEA7@Player@@QAEXH@Z @0x002AEEA7 400B. Player orders all units to
// enter KindOf-7 structures: partition query over the KindOf-7/all-objects
// filter, raw prototype/team/member walks, contain and canEnterObject gates,
// then AICommandInterface::rva0026C347 on each entering unit.
//
// Triple-loop skeleton, raw sentinel prototype walk, eight-byte MI Team PMF
// (pfn rowed 0x005C4AF5) and prototype offsets (+0x32C list, +0x334 team
// head) follow the landed siblings PlayerHuntCommands.cpp (setUnitsShouldHunt
// 0x002AE9B8) and PlayerTeamCommands.cpp (ungarrisonAllUnits 0x002AF037).
// The team advance is a raw PMF local (no null guard, as retail shows none);
// the object walk uses the (obj = cur()) != 0 for-condition plus an explicit
// reload null-skip, the S2 ScriptConditions idiom. The partition prologue
// (filter temporaries, forwarder, base-vptr reset) copies the matched
// Rva004AC7C9FindModuleObject.cpp spelling with bit index 7. Contain lives
// at object +0x250, the AI at +0x258 with commands at +0x20. All callees
// rowed: BitSet 0x00045411, filter 0x0004584D, forwarder 0x006256F0,
// next 0x00045623, dtor 0x0004AA28, iterate 0x00263864, advance 0x00263526,
// getControllingPlayer 0x0028AFA9, canEnterObject 0x0041C2D0,
// rva0026C347 0x0026C347. Original name unknown: honest address-derived name.
typedef int Int;
typedef bool Bool;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum CanEnterType
{
	CHECK_CAPACITY = 0,
	DONT_CHECK_CAPACITY = 1,
	COMBATDROP_INTO = 2
};

class Object;
class Team;
class Player;
template<class T> class DLINK_ITERATOR;

template <int NUMBITS> class BitFlags;

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();
	unsigned int m_bits[7];
};

extern BfmeFixedStorage0004543D g_009FEFA4;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual Bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual Bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

struct BfmeWideResult
{
	void *m_value;
	~BfmeWideResult();
	Object *next() throw();
};

struct BfmeResultA
{
	void *m_value;
	BfmeResultA();
	BfmeResultA(const BfmeResultA &that);
	__forceinline ~BfmeResultA() { ((BfmeWideResult *)this)->~BfmeWideResult(); }
};

class BfmeResultForwardB
{
public:
	BfmeResultA bfmeForwardResultB(int value);
};

class PartitionManager;
extern PartitionManager *ThePartitionManager;

struct BfmeWidePayloadCompat
{
	void *m_start;
	void *m_04;
	void *m_08;
	void *m_cursor;
};

class ContainModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void *getContainedObjectSource();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37();
	virtual bool isValidContainerFor(const Object *obj, bool checkCapacity, bool flag);
	virtual void addToContain(Object *obj);
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80();
	virtual int getPlayerWhoEntered();
};

class AICommandInterface
{
public:
	void rva0026C347(Object *target, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad[0x20];
	AICommandInterface m_command;
};

class Thing
{
public:
	virtual ~Thing();
};

class Object : public Thing
{
public:
	virtual ~Object();
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Player *getControllingPlayer() const;
private:
	const void *m_template;
	unsigned char m_pad08[0x38 - 0x08];
	struct Coord3D { float x; float y; float z; } m_pos;
	unsigned char m_pad44[0x250 - 0x44];
	ContainModuleInterface *m_contain;
	unsigned char m_pad254[4];
	AIUpdateInterface *m_ai;
};

class Rva2AE9B8TeamBase1 {};
class Rva2AE9B8TeamBase2 {};

class Team : public Rva2AE9B8TeamBase1, public Rva2AE9B8TeamBase2
{
public:
	Team *dlink_next_TeamInstanceList() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

template<> class DLINK_ITERATOR<Object>
{
public:
	Object *cur() const { return m_cur; }
	bool done() const { return m_cur == 0; }
	void advance();
private:
	Object *m_cur;
	unsigned char m_abi[20];
};

struct Rva2AE9B8Prototype
{
	char pad[0x334];
	Team *head;
};

struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	Rva2AE9B8Prototype *m_value;
};

class BFMEActionManager;
extern BFMEActionManager *TheActionManager;

class BFMEActionManager
{
public:
	bool canEnterObject(const Object *obj, const Object *objectToEnter,
		CommandSourceType commandSource, CanEnterType mode, bool passThrough, bool *outFlag);
};

class Player
{
public:
	void rva002AEEA7(int val);
	int getPlayerMask() const { return 1 << m_playerIndex; }
private:
	unsigned char m_pad[0x54];
	int m_playerIndex;
	unsigned char m_pad58[0x32C - 0x58];
	PlayerTeamNode *m_playerTeamPrototypes;
};

void Player::rva002AEEA7(int val)
{
	BfmeResultA hits = ((BfmeResultForwardB *)ThePartitionManager)->bfmeForwardResultB(
		(int)&Rva0004584D(*(const BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7),
			g_009FEFA4));
	PlayerTeamNode *cur = m_playerTeamPrototypes->m_next;
	if (cur != m_playerTeamPrototypes)
	{
		Team *(Team::*pmf)() const = &Team::dlink_next_TeamInstanceList;
		for (; cur != m_playerTeamPrototypes; cur = cur->m_next)
		{
			Team *team = cur->m_value->head;
			if (!team)
				continue;
			do
			{
				DLINK_ITERATOR<Object> objIter = team->iterate_TeamMemberList();
				for (; objIter.cur() != 0; objIter.advance())
				{
					Object *obj = objIter.cur();
					if (!obj)
						continue;
					AIUpdateInterface *ai = obj->getAIUpdateInterface();
					if (!ai)
						continue;
					BfmeWidePayloadCompat *payload = (BfmeWidePayloadCompat *)((BfmeWideResult *)&hits)->m_value;
					payload->m_cursor = payload->m_start;
					Object *theBuilding = ((BfmeWideResult *)&hits)->next();
					while (theBuilding != 0)
					{
						ContainModuleInterface *contain = theBuilding->getContain();
						if (contain != 0)
						{
							int entered = contain->getPlayerWhoEntered();
							if (entered && entered != obj->getControllingPlayer()->getPlayerMask())
							{
								theBuilding = ((BfmeWideResult *)&hits)->next();
								continue;
							}
						}
						Bool noEntry;
						if (!TheActionManager->canEnterObject(obj, theBuilding,
							(CommandSourceType)val, CHECK_CAPACITY, false, &noEntry))
						{
							theBuilding = ((BfmeWideResult *)&hits)->next();
							continue;
						}
						if (noEntry)
						{
							theBuilding = ((BfmeWideResult *)&hits)->next();
							continue;
						}
						ai->m_command.rva0026C347(theBuilding, (CommandSourceType)val);
						theBuilding = ((BfmeWideResult *)&hits)->next();
					}
				}
				team = (team->*pmf)();
			} while (team != 0);
		}
	}
}
