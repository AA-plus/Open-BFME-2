// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva0059BB50@Rva0059BB50@@QAEXHHHH@Z
// retail 0x0059BB50..0x0059BD2D (477 bytes) thiscall RET 0x10, EH frame
// (state 0: the candidate record vector, state 1: the copied link map).
//
// Target facts: the only caller, the guarded forwarder 0x004FB303, passes the
// subobject at this+0x120 and four stack words (the move vector, a player id,
// an unused word and the 0xE04508 channel table). The body looks up the player
// (0x002B51F8), gets the garrison record vector for that player (0x004FF9C9),
// and per record resolves the army (0x002E0A9F), skipping armies with no units
// (+0x40/+0x44 8-byte vector). Records with candidates from 0x00502381 go to
// sibling 0x0059B8FD; the rest take the closest hero (0x004FFB00), its region
// owner (0x002B488E then 0x00318C79), copy the link multimap of the territory
// from the 0xE04544 int map (copy ctor 0x0050055D, dtor 0x002B82D5), walk
// equal_range(1) (0x002F1C89) and append a move through rowed
// vector<BfmePod20>::push_back 0x0059B8C6 for the first owned region
// (0x002E0BC0) nearer than the hero (0x0050059A).
// WorldBuilder lead only: the WB twin 0x014FFDD0 calls the same graph under
// the names GetGarrisonArmies/findArmy/GetID/GetRegionInfo. The class and
// method identity are unproven, so the placeholder names stay; field and
// argument names are inferred.
#include <map>
#include <vector>

namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern unsigned int g_Va00E04544;

typedef _STL::map<int, int> Rva0059BB50IntMap;
typedef _STL::pair<const int, int> Rva0059BB50IntValue;
typedef _STL::_Rb_tree<int, Rva0059BB50IntValue, _STL::_Select1st<Rva0059BB50IntValue>,
	_STL::less<int>, _STL::allocator<Rva0059BB50IntValue> > Rva0059BB50IntTree;
typedef _STL::pair<Rva0059BB50IntTree::iterator, Rva0059BB50IntTree::iterator> Rva0059BB50Range;

class Rva002E2903Player;
struct Rva002B488EResult;

struct BfmePod20
{
	int m_id;
	bool m_flag;
	int m_08;
	int m_0c;
	int m_step;
};

namespace _STL {
template <> void vector<BfmePod20>::push_back(const BfmePod20 &);
}

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
	Rva002B488EResult *rva002B488E(int id);
};

class Rva002E0A9FElem
{
public:
	int rva002E0A9F(void *id);
};

class Rva002E071E
{
public:
	int rva002E0BC0(int id);
};

class Rva00318C79Owner
{
public:
	int rva00318C79();
};

int __cdecl rva0050059A(int from, int to);

struct Rva00501E3FElement
{
	int id;
	char map[12];
	void *opaque;
};
typedef _STL::vector<Rva00501E3FElement> Rva0059BB50Records;

struct Rva005011DA : Rva0059BB50Records
{
	~Rva005011DA();
};

class Rva0050055D
{
public:
	Rva0050055D(const Rva0050055D &other);
	char m_data[24];
};

class Rva002B82D5 : public Rva0050055D
{
public:
	Rva002B82D5(const Rva0050055D &other) : Rva0050055D(other) {}
	~Rva002B82D5();
};

struct Rva004FF5B7Node
{
	char m_pad00[0x10];
	int m_10;
	int m_14;
};

struct Rva004FF5B7Iter
{
	Rva004FF5B7Node *m_ptr;
};

class Rva004FF5B7
{
public:
	Rva004FF5B7Iter rva004FF5B7(int key);
};

class Rva004FF9C9
{
public:
	void *rva004FF9C9(int key);
};

struct Rva004FFB00Hero
{
	int m_id;
};

class Rva0059CFAACallee
{
public:
	Rva004FFB00Hero *rva004FFB00(int playerId, int *territory, int *distance);
};

class Rva00502381
{
public:
	void rva00502381(int who, int limit, const int *key, Rva0059BB50Records *out);
};

struct Rva0059BB50Pair8
{
	int m_a;
	int m_b;
};

struct Rva0059BB50Units
{
	char m_pad00[0x40];
	Rva0059BB50Pair8 *m_start;
	Rva0059BB50Pair8 *m_finish;
	unsigned int size() const { return m_finish - m_start; }
};

struct Rva0059BB50Army
{
	char m_pad00[0x20];
	int m_id;
	char m_pad24[0x54];
	Rva0059BB50Units *m_units;
};

class Rva0059BB50
{
public:
	void rva0059BB50(int moves, int playerId, int unused, int armies);
	void rva0059B8FD(_STL::vector<BfmePod20> *moves, int playerId,
		Rva00501E3FElement *garrison, Rva0059BB50Records *candidates, int armies);
};

void Rva0059BB50::rva0059BB50(int moves, int playerId, int unused, int armies)
{
	Rva002E2903Player *player =
		((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(playerId, 0);
	Rva0059BB50Records *garrisons =
		(Rva0059BB50Records *)((Rva004FF9C9 *)armies)->rva004FF9C9(playerId);
	for (unsigned int i = 0; i < garrisons->size(); ++i)
	{
		Rva0059BB50Army *army = (Rva0059BB50Army *)((Rva002E0A9FElem *)player)->rva002E0A9F((void *)(*garrisons)[i].id);
		if (army->m_units->size() == 0)
			continue;
		BfmePod20 move;
		move.m_id = army->m_id;
		move.m_flag = false;
		move.m_08 = 0;
		move.m_step = -1;
		Rva005011DA candidates;
		((Rva00502381 *)armies)->rva00502381(playerId, 1, (const int *)(*garrisons)[i].opaque, &candidates);
		if (candidates.size() > 0)
		{
			rva0059B8FD((_STL::vector<BfmePod20> *)moves, playerId, &(*garrisons)[i], &candidates, armies);
			continue;
		}
		int distance = 0;
		int *territory = (int *)(*garrisons)[i].opaque;
		int from = ((Rva00318C79Owner *)((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B488E(
			((Rva0059CFAACallee *)armies)->rva004FFB00(playerId, territory, &distance)->m_id))->rva00318C79();
		Rva002B82D5 links(*(const Rva0050055D *)&((Rva0059BB50IntMap *)&g_Va00E04544)->find(*territory)->second);
		Rva0059BB50Range range = ((Rva0059BB50IntTree *)&links)->equal_range(1);
		for (Rva0059BB50IntTree::iterator it = range.first; it != range.second; ++it)
		{
			Rva004FF5B7Iter region = ((Rva004FF5B7 *)armies)->rva004FF5B7((*it).second);
			if ((unsigned char)((Rva002E071E *)player)->rva002E0BC0(region.m_ptr->m_10)
				&& rva0050059A(from, region.m_ptr->m_14) < distance)
			{
				move.m_step = region.m_ptr->m_14;
				((_STL::vector<BfmePod20> *)moves)->push_back(move);
				break;
			}
		}
	}
}
