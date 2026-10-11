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
