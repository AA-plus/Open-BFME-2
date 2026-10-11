// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0RegionAwardDispute@@QAE@HABV?$vector@IV?$allocator@I@_STL@@@_STL@@H@Z,
// retail 0x004FC002 (90 bytes, RET 0x0C): the living-world region award
// dispute's constructor (vtable 0x00BFE280, the class whose destructor is
// rowed as Rva002B644A 0x004FC05C; its only caller 0x002B9A90). It keeps the
// region (+4), copies the disputing players' IDs (+8, rowed STLport
// vector<unsigned int> copy constructor 0x002CFAB9), takes the flags with
// bit 0x20 set (+0x14), no winner yet (+0x18 = -1) and unresolved (+0x1C),
// then evaluates the dispute (0x004FBF8E, pinned by address: its own body is
// a logged wall). The vtable store is an explicit member with a TU-local
// stand-in, as in DeployStyleAIUpdateCtor.cpp; the vector is a call-only
// view of the STLport class so its copy stays out of line.
namespace _STL
{
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	vector(const vector &other);
	~vector();
	void push_back(const T &value);	// the folded push_back 0x004DFCB0
	unsigned int size() const { return m_finish - m_start; }
	const T &operator[](unsigned int i) const { return m_start[i]; }
private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

// The Snapshot base (its vtable 0x00BBB554 is restored by the rowed
// destructor) is a constructed subobject while the members are built.
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

struct RegionAwardDisputeFlags
{
	RegionAwardDisputeFlags() {}
	RegionAwardDisputeFlags(int bits) : m_bits(bits) {}
	void set(int mask) { m_bits |= mask; }
	int m_bits;
};

class RegionAwardDispute : public Snapshot
{
public:
	virtual ~RegionAwardDispute();
	RegionAwardDispute(int region, const _STL::vector<unsigned int> &players, int flags);
	void rva004FBF8E();
	int GetResolvableBy();			// 0x004FBED6
	void rva004FC0ED(const _STL::vector<int> &players);
private:
	int m_region;				// +0x04
	_STL::vector<unsigned int> m_players;	// +0x08
	RegionAwardDisputeFlags m_flags;	// +0x14
	int m_winner;				// +0x18
	bool m_resolved;			// +0x1C
};

RegionAwardDispute::RegionAwardDispute(int region, const _STL::vector<unsigned int> &players, int flags)
	: m_region(region), m_players(players), m_winner(-1)
{
	m_flags = RegionAwardDisputeFlags(flags);
	m_resolved = false;
	m_flags.set(0x20);
	rva004FBF8E();
}

class Rva002B2B66 { public: int rva002B2B66(); };	// rowed 0x002B2B66, the local player's id
class Rva004FBDB0 { public: void rva004FBDB0(bool local); };	// rowed 0x004FBDB0
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

// Retail 0x004FC0ED, 94 bytes (RET 4; its caller is LivingWorldLogic's
// dispute opening 0x002B9A90 when the region already has one): appends the
// nonzero player ids to the dispute and tells the dispute (0x004FBDB0)
// whether the local player is the one that can settle it.
void RegionAwardDispute::rva004FC0ED(const _STL::vector<int> &players)
{
	for (unsigned int i = 0; i < players.size(); ++i)
	{
		if (players[i])
			m_players.push_back(*(const unsigned int *)&players[i]);
	}
	int local = ((Rva002B2B66 *)TheLivingWorldLogic)->rva002B2B66();
	((Rva004FBDB0 *)this)->rva004FBDB0(local == GetResolvableBy());
}
