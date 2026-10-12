// cl: /O1 /G7 /arch:SSE /GX- /MD /DNDEBUG
// Out-of-line copies of BFME2 partition-filter constructors. Each stores the
// base's zero next link (+0x04), the filter's vftable and its members, as the
// filters AIClosestObjectQueries.cpp, AIAreaEnemySearch.cpp,
// AIAttackApproachTargetStateOnEnter.cpp and Drawable_rva00272AD5.cpp declare
// them (class names and vftables from those units; this unit repeats only
// what the constructors touch). Retail keeps these copies out of line beside
// their callers; here each constructor is select-any like every other unit's
// inline copy, and an anchor keeps the noinline body emitted.
inline void *operator new(unsigned int, void *p) { return p; }

class Object;
class Player;
class PolygonTrigger;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10: Rva0026119DFilter, out-of-line constructor copy at 0x0026FFA4 (13B).
class Rva0026119DFilter : public Rva000421C8
{
public:
	Rva0026119DFilter();
	virtual bool allow(Object *obj);
};

__declspec(noinline) inline Rva0026119DFilter::Rva0026119DFilter()
{
}

// ?bfmeAnchorRva0026FFA4 absent-from-retail
void *bfmeAnchorRva0026FFA4(void *where)
{
	return ::new (where) Rva0026119DFilter();
}

// vftable 0x00BFAD04: Rva00260E2AFilter, out-of-line constructor copy at 0x0026FF8E (22B).
class Rva00260E2AFilter : public Rva000421C8
{
public:
	Rva00260E2AFilter(const Player *player);
	virtual bool allow(Object *obj);
	const Player *m_player;
};

__declspec(noinline) inline Rva00260E2AFilter::Rva00260E2AFilter(const Player *player) : m_player(player)
{
}

// ?bfmeAnchorRva0026FF8E absent-from-retail
void *bfmeAnchorRva0026FF8E(void *where, const Player *player)
{
	return ::new (where) Rva00260E2AFilter(player);
}

// vftable 0x00BFAD28: Rva0026137EFilter, out-of-line constructor copy at 0x0026FFBE (29B).
class Rva0026137EFilter : public Rva000421C8
{
public:
	Rva0026137EFilter(Player *player, bool match);
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
};

__declspec(noinline) inline Rva0026137EFilter::Rva0026137EFilter(Player *player, bool match) : m_player(player), m_match(match)
{
}

// ?bfmeAnchorRva0026FFBE absent-from-retail
void *bfmeAnchorRva0026FFBE(void *where, Player *player, bool match)
{
	return ::new (where) Rva0026137EFilter(player, match);
}

// vftable 0x00BF91BC: Rva002611BFFilter, out-of-line constructor copy at 0x002623AB (22B).
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj);
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

__declspec(noinline) inline Rva002611BFFilter::Rva002611BFFilter(const Object *obj) : m_obj(obj)
{
}

// ?bfmeAnchorRva002623AB absent-from-retail
void *bfmeAnchorRva002623AB(void *where, const Object *obj)
{
	return ::new (where) Rva002611BFFilter(obj);
}

// vftable 0x00BFBC90: Rva00260EB1Filter, out-of-line constructor copy at 0x0028AABB (36B).
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match);
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

__declspec(noinline) inline Rva00260EB1Filter::Rva00260EB1Filter(const Object *obj, int flags, bool match) : m_obj(obj), m_flags(flags), m_match(match)
{
}

// ?bfmeAnchorRva0028AABB absent-from-retail
void *bfmeAnchorRva0028AABB(void *where, const Object *obj, int flags, bool match)
{
	return ::new (where) Rva00260EB1Filter(obj, flags, match);
}

// vftable 0x00C07150: Rva002619C1Filter, out-of-line constructor copy at 0x002FD66B (22B).
class Rva002619C1Filter : public Rva000421C8
{
public:
	Rva002619C1Filter(const Object *obj);
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

__declspec(noinline) inline Rva002619C1Filter::Rva002619C1Filter(const Object *obj) : m_obj(obj)
{
}

// ?bfmeAnchorRva002FD66B absent-from-retail
void *bfmeAnchorRva002FD66B(void *where, const Object *obj)
{
	return ::new (where) Rva002619C1Filter(obj);
}

// vftable 0x00C0716C: Rva00261353Filter, out-of-line constructor copy at 0x002FD69E (22B).
class Rva00261353Filter : public Rva000421C8
{
public:
	Rva00261353Filter(int playerIndex);
	virtual bool allow(Object *obj);
	int m_playerIndex;
};

__declspec(noinline) inline Rva00261353Filter::Rva00261353Filter(int playerIndex) : m_playerIndex(playerIndex)
{
}

// ?bfmeAnchorRva002FD69E absent-from-retail
void *bfmeAnchorRva002FD69E(void *where, int playerIndex)
{
	return ::new (where) Rva00261353Filter(playerIndex);
}

// vftable 0x00C07178: Rva00261BFBFilter, out-of-line constructor copy at 0x002FD6B4 (22B).
class Rva00261BFBFilter : public Rva000421C8
{
public:
	Rva00261BFBFilter(const Object *obj);
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

__declspec(noinline) inline Rva00261BFBFilter::Rva00261BFBFilter(const Object *obj) : m_obj(obj)
{
}

// ?bfmeAnchorRva002FD6B4 absent-from-retail
void *bfmeAnchorRva002FD6B4(void *where, const Object *obj)
{
	return ::new (where) Rva00261BFBFilter(obj);
}

// vftable 0x00C07184: Rva00261723Filter, out-of-line constructor copy at 0x002FD6CA (22B).
class Rva00261723Filter : public Rva000421C8
{
public:
	Rva00261723Filter(const PolygonTrigger *trigger);
	virtual bool allow(Object *obj);
	const PolygonTrigger *m_trigger;
};

__declspec(noinline) inline Rva00261723Filter::Rva00261723Filter(const PolygonTrigger *trigger) : m_trigger(trigger)
{
}

// ?bfmeAnchorRva002FD6CA absent-from-retail
void *bfmeAnchorRva002FD6CA(void *where, const PolygonTrigger *trigger)
{
	return ::new (where) Rva00261723Filter(trigger);
}

// vftable 0x00C07190: Rva002614DFFilter, out-of-line constructor copy at 0x002FD6E0 (22B).
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj);
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

__declspec(noinline) inline Rva002614DFFilter::Rva002614DFFilter(const Object *obj) : m_obj(obj)
{
}

// ?bfmeAnchorRva002FD6E0 absent-from-retail
void *bfmeAnchorRva002FD6E0(void *where, const Object *obj)
{
	return ::new (where) Rva002614DFFilter(obj);
}

// vftable 0x00BCECF0: Rva002614ECFilter (allow 0x002614EC in
// BfmeThreeHundredFifteen.cpp), out-of-line constructor copy at 0x000E9E03 (36B).
class Rva2225E0Filter;
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(Rva2225E0Filter *sub, void *extra, bool flag);
	virtual bool allow(Object *what);
	Rva2225E0Filter *m_bfmeSub;
	void *m_bfmeExtra;
	bool m_bfmeFlag;
};

__declspec(noinline) inline Rva002614ECFilter::Rva002614ECFilter(Rva2225E0Filter *sub, void *extra, bool flag) : m_bfmeSub(sub), m_bfmeExtra(extra), m_bfmeFlag(flag)
{
}

// ?bfmeAnchorRva000E9E03 absent-from-retail
void *bfmeAnchorRva000E9E03(void *where, Rva2225E0Filter *sub, void *extra, bool flag)
{
	return ::new (where) Rva002614ECFilter(sub, extra, flag);
}

// Three (int, bool) partition filters with out-of-line constructor copies at
// 0x003BA6F1 / 0x003BA70E / 0x003BA72B (29B each). vftable 0x00C1FDE0 is
// Rva002613AFFilter's (allow 0x002613AF, getPlayerMask 0x002613A3, as
// ScriptConditions_Rva003EA764.cpp declares it); 0x00C1FDEC and 0x00C1FDF8
// hold the allow bodies at 0x00261750 and 0x0026176E and keep the base
// getPlayerMask, so those two classes carry address-derived names.
class Rva002613AFFilter : public Rva000421C8
{
public:
	Rva002613AFFilter(int playerMask, bool match);
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	int m_playerMask;
	bool m_match;
};

__declspec(noinline) inline Rva002613AFFilter::Rva002613AFFilter(int playerMask, bool match) : m_playerMask(playerMask), m_match(match)
{
}

// ?bfmeAnchorRva003BA6F1 absent-from-retail
void *bfmeAnchorRva003BA6F1(void *where, int playerMask, bool match)
{
	return ::new (where) Rva002613AFFilter(playerMask, match);
}

class ThingTemplate;
// vftable 0x00C1FDEC is pinned as ??_7Rva00261750Filter (Zero Hour's PartitionFilterThing
// at ScriptActions::doMoveUnitTowardsNearest): +0x08 the thing template.
class Rva00261750Filter : public Rva000421C8
{
public:
	Rva00261750Filter(const ThingTemplate *thing, bool match);
	virtual bool allow(Object *obj);
	const ThingTemplate *m_thing;
	bool m_match;
};

__declspec(noinline) inline Rva00261750Filter::Rva00261750Filter(const ThingTemplate *thing, bool match) : m_thing(thing), m_match(match)
{
}

// ?bfmeAnchorRva003BA70E absent-from-retail
void *bfmeAnchorRva003BA70E(void *where, const ThingTemplate *thing, bool match)
{
	return ::new (where) Rva00261750Filter(thing, match);
}

class Rva0026176EFilter : public Rva000421C8
{
public:
	Rva0026176EFilter(int value, bool match);
	virtual bool allow(Object *obj);
	int m_value;
	bool m_match;
};

__declspec(noinline) inline Rva0026176EFilter::Rva0026176EFilter(int value, bool match) : m_value(value), m_match(match)
{
}

// ?bfmeAnchorRva003BA72B absent-from-retail
void *bfmeAnchorRva003BA72B(void *where, int value, bool match)
{
	return ::new (where) Rva0026176EFilter(value, match);
}
