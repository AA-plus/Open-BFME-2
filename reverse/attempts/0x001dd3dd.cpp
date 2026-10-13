// ?rva001DD3DD@Eva@@QAEXXZ
// partial score=0.9172399445214979 date=2026-10-13
// cl: /I. /O1 /G7 /EHs /DNDEBUG /MD /arch:SSE /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Existing 80-byte status clearer at 0x001DCD3C, moved here so Eva's
// element reset loop can see its register effects. Retail writes the 0x34-byte
// status layout; retain the observed write order and the existing barrier.
// -1 is the immutable float at .rdata RVA 0x007BB9AC (data_ledger.csv), so use
// the verified compiler literal rather than an address-named global.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva001DCD3C
{
public:
    void rva001DCD3C();
private:
    volatile float m_00;
    volatile float m_04;
    volatile float m_08;
    volatile float m_0C;
    volatile float m_10;
    volatile float m_14;
    volatile float m_18;
    volatile float m_1C;
    volatile unsigned char m_20;
    volatile unsigned char m_21;
    volatile unsigned char m_22;
    volatile unsigned char m_pad23;
    volatile float m_24;
    volatile float m_28;
    volatile float m_2C;
    volatile int m_30;
};
void Rva001DCD3C::rva001DCD3C()
{
    float v = -1.0f;
    float zero = 0.0f;
    m_00 = v;
    m_04 = v;
    _ReadWriteBarrier();
    m_20 = 0;
    m_08 = zero;
    m_0C = zero;
    m_10 = zero;
    m_21 = 0;
    m_14 = zero;
    m_18 = zero;
    m_1C = zero;
    m_22 = 0;
    m_24 = zero;
    m_28 = zero;
    m_2C = zero;
    m_30 = 0;
}

// Eva status is a non-owning 52-byte value. Its default construction calls
// the rowed clearer; its out-of-line copy is the existing 0x001DD0A0 pin.
// The empty destructor and nontrivial copy reproduce retail temporary lifetime.
struct BfmePod52 {
 BfmePod52() { reinterpret_cast<Rva001DCD3C*>(this)->rva001DCD3C(); }
 BfmePod52(const BfmePod52 &other);
 ~BfmePod52() {}
 int a[13];
};
namespace _STL {
template<class T> struct _EvaResizeArgument { typedef const T& type; };
template<> struct _EvaResizeArgument<BfmePod52> { typedef BfmePod52 type; };
}
#include "reference/shims/eva_vector/EvaVectorABI.h"
#include <hash_map>
#include <list>

namespace _STL {
template<> vector<BfmePod52, allocator<BfmePod52> >::iterator vector<BfmePod52, allocator<BfmePod52> >::erase(iterator first, iterator last);
template<> void vector<BfmePod52, allocator<BfmePod52> >::_M_fill_insert(iterator position, size_type count, const BfmePod52 &value);
}

// Eva.cpp -- Eva event-status queries recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv). WB's debug Eva.cpp names each member and its
// diagnostics (Eva.cpp:1408..1447): an invalid EvaEventID, and a status array
// whose size differs from the info array's; retail keeps the checks and
// drops the messages. Layout (target): m_allEventInfos, 0x30-byte records at
// +0x1C; the parallel status array, 0x34-byte records at +0x5C. The status
// record's members are rowed under placeholder names (0x001DCDAF,
// 0x001DD240); field names past WB's are not recovered.

#include "Code/Libraries/Include/Lib/Coord2D.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

enum EvaEventID
{
	EVA_INVALID = -1
};

// STLport vector view: inline size() divides the pointer difference.
template <class T> class EvaVectorView
{
public:
	UnsignedInt size() const { return UnsignedInt(m_finish - m_start); }
	T &operator[](UnsignedInt i) { return m_start[i]; }
	const T &operator[](UnsignedInt i) const { return m_start[i]; }
	T *begin() const { return m_start; }
	T *end() const { return m_finish; }

private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};

struct Vec001DCDAF
{
	Real x;
	Real y;
	Real z;
};

// A returned position. The memberwise copy constructor is what gives the
// retail return copies their fld/fstp-then-mov shape; the float constructor
// builds a result in place.
struct EvaCoord
{
	EvaCoord() {}
	EvaCoord(const EvaCoord &p) : x(p.x), y(p.y), z(p.z) {}
	EvaCoord(Real ax, Real ay, Real az) : x(ax), y(ay), z(az) {}
	Real x;
	Real y;
	Real z;
};

// One event's info record (0x30 bytes), seen by the status updates as their
// argument.
struct Arg001DCDAF
{
	unsigned char m_data[0x0c];
	UnsignedInt m_delayFrames;				// +0x0C, observed retail unsigned test
	unsigned char m_pad10[0x20 - 0x10];
	EvaEventID *m_eventIDsStart;			// +0x20, observed retail pointer read
	EvaEventID *m_eventIDsFinish;			// +0x24, observed retail pointer read
	unsigned char m_pad28[0x2c - 0x28];
	Bool m_2c;						// +0x2C, observed retail byte test
	unsigned char m_pad2d[0x30 - 0x2d];
};

class Player
{
public:
	int rva002ABCF0(unsigned char flag, int *out);		// 0x002ABCF0, the player's best object
};

// The object view: its position at +0x38.
struct EvaObjectView
{
	unsigned char m_pad00[0x38];
	EvaCoord m_position;					// +0x38
};

// The living-world player: its region name at +0x2C, its side at +0x14.
struct EvaWorldMapPlayer
{
	unsigned char m_pad00[0x14];
	int m_14;						// +0x14
	unsigned char m_pad18[0x2c - 0x18];
	unsigned char m_regionName[4];				// +0x2C
};

// One event's status record (0x34 bytes).
class Rva001DCDAF
{
public:
	Bool rva001DCDAF(const Arg001DCDAF *info, const Vec001DCDAF *pos, const Vec001DCDAF *pos2);	// 0x001DCDAF
	void rva001DD7C1(Arg001DCDAF *info, const Vec001DCDAF *position);
	EvaCoord getPlayPositionForEvent(const Arg001DCDAF *info, Player *localPlayerRTS, EvaWorldMapPlayer *localPlayerWorldMap) const;

	Real m_blockedTime;					// +0x00, > 0 blocks the event
	Real m_aboutToPlayTime;					// +0x04, >= 0 when about to play
	EvaCoord m_position;					// +0x08
	unsigned char m_pad14[0x20 - 0x14];
	Bool m_hasPosition;					// +0x20
	unsigned char m_pad21;
	Bool m_hasPlayed;					// +0x22
	unsigned char m_pad23[0x30 - 0x23];
	UnsignedInt m_lastReallyPlayedFrame;			// +0x30
};

class GameLogic
{
public:
	Bool rva001DCD1C();					// 0x001DCD1C

	unsigned char m_pad00[0x40];
	UnsignedInt m_frame;				// +0x40, observed retail load
};

class Eva;
extern GameLogic *TheGameLogic;
extern Eva *TheEva;

// The status record's played counter (0x001DD240), placeholder-rowed under
// another class name.
class Rva001DD240
{
public:
	void rva001DD240(UnsignedInt *info);			// 0x001DD240
};

// The report internalReportEvaEvent takes (WB's report record; rowed under
// the placeholder Rva001DD063, default constructor 0x001DD1D0): the event,
// then two optional positions, each behind a presence flag.
struct Rva001DD063
{
	Rva001DD063();						// 0x001DD1D0

	EvaEventID m_eventID;					// +0x00
	Bool m_hasPosition;					// +0x04
	Bool m_hasSecondPosition;				// +0x05
	unsigned char m_pad06[2];
	Coord3D m_position;					// +0x08
	Coord3D m_secondPosition;				// +0x14
};

// A delayed report keyed by the frame it is due (0x001DD2BF), held in Eva's
// multiset.
struct Rva001DD1B3
{
	// Body kept visible (and out of line) so the key temporary is known not to escape; the
	// emitted copy matches the rowed ctor at 0x001DD2BF.
	__declspec(noinline) Rva001DD1B3(const Int &frame, const Rva001DD063 &report) : m_frame(frame), m_report(report) {}

	Int m_frame;						// +0x00
	Rva001DD063 m_report;					// +0x04
};

// stlport
#include <set>
typedef _STL::_Rb_tree<Rva001DD1B3, Rva001DD1B3, _STL::_Identity<Rva001DD1B3>, _STL::less<Rva001DD1B3>, _STL::allocator<Rva001DD1B3> > EvaDelayedTree;
namespace _STL {
template<> EvaDelayedTree::iterator EvaDelayedTree::insert_equal(const Rva001DD1B3 &);
}
typedef char EvaDelayedSetWidth[(sizeof(_STL::multiset<Rva001DD1B3, _STL::less<Rva001DD1B3>, _STL::allocator<Rva001DD1B3> >)==12)?1:-1];

// The report internalReportEvaEvent takes: the event, then two optional
// positions, each behind a presence flag.
struct EvaEventReport
{
	EvaEventID m_eventID;					// +0x00
	Bool m_hasPosition;					// +0x04
	Bool m_hasSecondPosition;				// +0x05
	unsigned char m_pad06[2];
	Vec001DCDAF m_position;					// +0x08
	Vec001DCDAF m_secondPosition;				// +0x14
};

// The existing STLport owners define these opaque record spellings. Their
// vector and hash-table assignments are rowed at 0x001DEF89 and 0x001DE3E3;
// call those owners directly rather than adding container aliases.
struct Rva001DEF89Record { Rva001DEF89Record(); Rva001DEF89Record(const Rva001DEF89Record&); ~Rva001DEF89Record(); Rva001DEF89Record&operator=(const Rva001DEF89Record&); char bytes[48]; };
struct Rva001DE3E3Record { Rva001DE3E3Record(); Rva001DE3E3Record(const Rva001DE3E3Record&); ~Rva001DE3E3Record(); Rva001DE3E3Record&operator=(const Rva001DE3E3Record&); char bytes[1]; bool operator<(const Rva001DE3E3Record&)const; bool operator==(const Rva001DE3E3Record&)const; };
typedef _STL::vector<Rva001DEF89Record, _STL::allocator<Rva001DEF89Record> > EvaInfoRecords;
typedef _STL::hashtable<_STL::pair<const int,Rva001DE3E3Record>, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<const int,Rva001DE3E3Record> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int,Rva001DE3E3Record> > > EvaEventTable;
namespace _STL {
template<> EvaInfoRecords &EvaInfoRecords::operator=(const EvaInfoRecords &);
template<> EvaEventTable &EvaEventTable::operator=(const EvaEventTable &);
template<> void _List_base<int, allocator<int> >::clear();
}
class Rva001DEE92Member { public: void rva001DEE92(int count); char *m_begin; char *m_end; char *m_storage; };
class Rva001DD70F { public: void rva001DD846(); };
typedef char EvaInfoRecordsWidth[(sizeof(EvaInfoRecords)==12)?1:-1];
typedef char EvaEventTableWidth[(sizeof(EvaEventTable)==20)?1:-1];
typedef char EvaListWidth[(sizeof(_STL::_List_base<int,_STL::allocator<int> >)==4)?1:-1];

class Eva
{
public:
 void rva001DD3DD();
	void rva001DF1A4();
	Bool reportEvaEvent(EvaEventID eventID, const Coord3D *position, const Coord3D *secondPosition);
	Bool internalReportEvaEvent(const EvaEventReport *report);	// 0x001DD468
	void countEvaEventAsPlayed(EvaEventID eventID);
	Bool isEventBlockedByTimeout(EvaEventID eventID) const;
	Bool isEventAboutToPlay(EvaEventID eventID) const;
	Bool getLastReallyPlayedFrameForEvaEvent(EvaEventID eventID, UnsignedInt *frame) const;

private:
	unsigned char m_pad00[0x10];
	EvaDelayedTree m_delayedEvents;	// +0x10
	EvaVectorView<Arg001DCDAF> m_allEventInfos;		// +0x1C (WB name)
	unsigned char m_pad28[0x5c - 0x28];
	EvaVectorView<Rva001DCDAF> m_eventStatus;		// +0x5C
	_STL::_List_base<int, _STL::allocator<int> > m_queue; // +0x68
	int m_queuePosition; // +0x6C
	int m_70;
	int m_74;
	int m_78;
	Bool m_7C;
 char m_pad7d[0x90-0x7d];
 unsigned int m_cycleDuration;
};

// Eva::reportEvaEvent, retail 0x001DE2DA (247 bytes; WorldBuilder's Eva.cpp
// names it): validates the event, records the optional positions in a report
// and either queues it for a later frame (info delay > 0 and the logic is not
// in the paused/replay state tested by 0x001DCD1C) or reports it now.
Bool Eva::reportEvaEvent(EvaEventID eventID, const Coord3D *position, const Coord3D *secondPosition)
{
	if (eventID == EVA_INVALID)
		return false;
	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
		return false;
	if (m_eventStatus.size() != m_allEventInfos.size())
		return false;
	Rva001DD063 report;
	report.m_eventID = eventID;
	if (position)
	{
		report.m_position = *position;
		report.m_hasPosition = true;
	}
	else
		report.m_hasPosition = false;
	if (secondPosition)
	{
		report.m_secondPosition = *secondPosition;
		report.m_hasSecondPosition = true;
	}
	else
		report.m_hasSecondPosition = false;
	const UnsignedInt &delay = m_allEventInfos[eventID].m_delayFrames;
	if (delay > 0)
	{
		GameLogic *logic = TheGameLogic;
		if (!logic->rva001DCD1C())
		{
			m_delayedEvents.insert_equal(Rva001DD1B3(logic->m_frame + delay, report));
			return true;
		}
	}
	return internalReportEvaEvent(reinterpret_cast<const EvaEventReport *>(&report));
}

// Eva::countEvaEventAsPlayed, retail 0x001DD4E3 (90 bytes).
void Eva::countEvaEventAsPlayed(EvaEventID eventID)
{
	if (eventID == EVA_INVALID)
		return;
	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
		return;
	if (m_eventStatus.size() != m_allEventInfos.size())
		return;
	((Rva001DD240 *)&m_eventStatus[eventID])->rva001DD240((UnsignedInt *)&m_allEventInfos[eventID]);
}

// Eva::isEventBlockedByTimeout, retail 0x001DD53D (99 bytes): an invalid
// event counts as blocked.
Bool Eva::isEventBlockedByTimeout(EvaEventID eventID) const
{
	if (eventID == EVA_INVALID)
		return true;
	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
		return true;
	if (m_eventStatus.size() != m_allEventInfos.size())
		return true;
	return m_eventStatus[eventID].m_blockedTime > 0.0f;
}

// Eva::isEventAboutToPlay, retail 0x001DD5A0 (100 bytes).
Bool Eva::isEventAboutToPlay(EvaEventID eventID) const
{
	if (eventID == EVA_INVALID)
		return false;
	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
		return false;
	if (m_eventStatus.size() != m_allEventInfos.size())
		return false;
	return m_eventStatus[eventID].m_aboutToPlayTime >= 0.0f;
}

// Eva::getLastReallyPlayedFrameForEvaEvent, retail 0x001DD604 (108 bytes):
// the frame is cleared first and set only for an event that has played.
Bool Eva::getLastReallyPlayedFrameForEvaEvent(EvaEventID eventID, UnsignedInt *frame) const
{
	*frame = 0;
	if (eventID == EVA_INVALID)
		return false;
	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
		return false;
	if (m_eventStatus.size() != m_allEventInfos.size())
		return false;
	if (!m_eventStatus[eventID].m_hasPlayed)
		return false;
	*frame = m_eventStatus[eventID].m_lastReallyPlayedFrame;
	return true;
}

// ?rva001DD7C1@Rva001DCDAF@@QAEXPAUArg001DCDAF@@PBUVec001DCDAF@@@Z 74B @0x001DD7C1.
// Class identity follows the existing 0x34-byte Rva001DCDAF status record;
// retail writes its +0x22 flag, +0x24 position and +0x30 frame. The argument
// pointer fields and GameLogic frame offset are direct retail observations;
// the semantic member names remain structural inferences.
void Rva001DCDAF::rva001DD7C1(Arg001DCDAF *info, const Vec001DCDAF *position)
{
	((Rva001DD240 *)this)->rva001DD240((UnsignedInt *)info);
	EvaEventID *eventID = info->m_eventIDsStart;
	EvaEventID *eventIDsFinish = info->m_eventIDsFinish;
	while (eventID != eventIDsFinish)
	{
		TheEva->countEvaEventAsPlayed(*eventID);
		++eventID;
	}
	m_hasPlayed = true;
	m_lastReallyPlayedFrame = TheGameLogic->m_frame;
	*(Vec001DCDAF *)((unsigned char *)this + 0x24) = *position;
}

// The living-world region manager's lookups (TheLivingWorldLogic +0xB0):
// 0x002104B6 finds a region by name, 0x0020EA58 its centre point; the region
// keeps its owner at +0x13C.
class Rva002104B6
{
public:
	void *rva002104B6(void *name);
};

class Rva0020E89C;
class LivingWorldRegionManager
{
public:
	bool GetRegionCenterPoint(Rva0020E89C *region, Coord2D *center);
};

struct EvaRegionView
{
	unsigned char m_pad00[0x13c];
	int m_13c;						// +0x13C
};

class LivingWorldLogic
{
public:
	void *getRegionManager() const { return m_regionManager; }

	unsigned char m_pad00[0xb0];
	void *m_regionManager;					// +0xB0
};
extern LivingWorldLogic *TheLivingWorldLogic;

// 0x002BF5B0 maps a world-map point to a 3D position (rowed as
// Rva002BF4F3::rva002BF5B0).
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;
class Vector3;
class Rva002BF4F3
{
public:
	bool rva002BF5B0(const Vector3 *in, Vector3 *out);
};

// EvaEventStatus::getPlayPositionForEvent, retail 0x001DCE6B (279 bytes;
// WorldBuilder's Eva.cpp 0x00AC8E80, whose assert names both player
// parameters): the event's own position unless the info record's +0x2C byte
// is set, else the RTS player's best object, else the world-map player's
// region centre, else (-100, -100, 0).
EvaCoord Rva001DCDAF::getPlayPositionForEvent(const Arg001DCDAF *info, Player *localPlayerRTS, EvaWorldMapPlayer *localPlayerWorldMap) const
{
	if (m_hasPosition && !info->m_2c)
		return m_position;
	if (localPlayerRTS)
	{
		EvaObjectView *obj = (EvaObjectView *)localPlayerRTS->rva002ABCF0(1, 0);
		if (obj)
			return obj->m_position;
	}
	else if (localPlayerWorldMap)
	{
		EvaRegionView *region = (EvaRegionView *)((Rva002104B6 *)TheLivingWorldLogic->getRegionManager())->rva002104B6(localPlayerWorldMap->m_regionName);
		if (region && region->m_13c == localPlayerWorldMap->m_14)
		{
			Coord2D center;
			if (((LivingWorldRegionManager *)TheLivingWorldLogic->getRegionManager())->GetRegionCenterPoint((Rva0020E89C *)region, &center))
			{
				Coord3D pos;
				pos.x = center.x;
				pos.y = center.y;
				pos.z = 0.0f;
				((Rva002BF4F3 *)g_00DFEF18)->rva002BF5B0((const Vector3 *)&center, (Vector3 *)&pos);
				return EvaCoord(pos.x, pos.y, pos.z);
			}
		}
	}
	return EvaCoord(-100.0f, -100.0f, 0.0f);
}

// Eva::internalReportEvaEvent, retail 0x001DD468 (123 bytes). WorldBuilder's
// Eva.cpp names this member; its report flags select the two optional positions.
// Array extents and strides are retail observations (0x30 info, 0x34 status).
// Keep the negated equality and member call: MSVC 7.1 emits the retail count
// evaluation order and preloads both array bases before pushing the positions.
Bool Eva::internalReportEvaEvent(const EvaEventReport *report)
{
	EvaEventID eventID = report->m_eventID;
	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
		return false;
	if (!(m_eventStatus.size() == m_allEventInfos.size()))
		return false;
	Arg001DCDAF *info = &m_allEventInfos[0];
	Rva001DCDAF *status = &m_eventStatus[0];
	Bool (Rva001DCDAF::*set)(const Arg001DCDAF *, const Vec001DCDAF *, const Vec001DCDAF *) = &Rva001DCDAF::rva001DCDAF;
	return (status[eventID].*set)(&info[eventID],
		report->m_hasPosition ? &report->m_position : 0,
		report->m_hasSecondPosition ? &report->m_secondPosition : 0);
}

// Retail 0x001DF1A4, 120 bytes; WorldBuilder Eva.cpp vtable lead.
// The method name is unrecovered. Retail copies the 48-byte info-record vector
// and its event table, sizes and clears the 52-byte status records, clears the
// delayed-report tree and queue, then resets the observed flags/queue position.
// The visible status clearer preserves ECX/EDX across the element loop.
void Eva::rva001DF1A4()
{
 EvaInfoRecords &records = *reinterpret_cast<EvaInfoRecords *>(&m_allEventInfos);
 records = *reinterpret_cast<const EvaInfoRecords *>(reinterpret_cast<char *>(this)+0x28);
 *reinterpret_cast<EvaEventTable *>(reinterpret_cast<char *>(this)+0x34) = *reinterpret_cast<const EvaEventTable *>(reinterpret_cast<char *>(this)+0x48);
 int count = (int)records.size();
 Rva001DEE92Member *status = reinterpret_cast<Rva001DEE92Member *>(&m_eventStatus);
 status->rva001DEE92(count);
 reinterpret_cast<Rva001DD70F *>(reinterpret_cast<char *>(this)+0x10)->rva001DD846();
 Rva001DCD3C *p = reinterpret_cast<Rva001DCD3C *>(status->m_begin);
 Rva001DCD3C *end = reinterpret_cast<Rva001DCD3C *>(m_eventStatus.end());
 for (; p != end; ++p)
  p->rva001DCD3C();
 if (m_78 == 0)
  m_74 = 1;
 m_7C = true;
 m_queue.clear();
 m_queuePosition = *reinterpret_cast<int *>(&m_queue);
 m_70 = 0;
}

// Retail 0x001DED5E (73 bytes) and 0x001DEE92 (33 bytes).
// The value-resize ABI is proven by the outgoing 52-byte argument and
// the rowed erase/fill callees. Use the full STLport vector API.
namespace _STL {
template void vector<BfmePod52,allocator<BfmePod52> >::resize(unsigned int,BfmePod52);

}

// BfmePod52 is a provisional name shared by distinct record views elsewhere.
// Retain the served address identity until Eva's real status type is reconciled.
void Rva001DEE92Member::rva001DEE92(int count) {
 reinterpret_cast<_STL::vector<BfmePod52,_STL::allocator<BfmePod52> >*>(this)->resize((unsigned int)count, BfmePod52());
}

// Native1DDBF3: the table clear3A2A41 followed by release of the bucket array+4.
// Target1DF057 establishes the20-byte member extent; original class spelling
// and unread field meanings remain neutral/carried from the existing view.
// EHs preserves the retail state ending before free; all pre-existing Eva
// bodies remain byte-exact under this matched-sibling setting.
extern "C" void __cdecl free(void *block) throw(...);
class Rva000427195 {public:void rva003A2A41();};
struct Rva001DDBF3Buckets
{
	void **begin, **end, **capacity;
	~Rva001DDBF3Buckets() { if (begin) free(begin); }
};
struct Rva001DDBF3
{
	__declspec(noinline) ~Rva001DDBF3();
	void *unknown00;
	Rva001DDBF3Buckets buckets;
	unsigned count;
};
typedef char Rva001DDBF3Extent[(sizeof(Rva001DDBF3)==20)?1:-1];
Rva001DDBF3::~Rva001DDBF3()
{
	((Rva000427195 *)this)->rva003A2A41();
}

// Target native1DD3DD..1DD468,139B; translateGameMessage42B68F calls
// through TheEva. A hotkey advances through remembered event positions.
// The adjacent named Eva report/status methods establish owner; original
// member name is unknown. The ZH Eva subsystem is context, not a same-body donor.
struct EvaCycleNode { EvaCycleNode*next;EvaCycleNode*prev;int id;Coord3D position; };
template<int N> class EvaCycleSlots : public EvaCycleSlots<N-1> {public: virtual void slot(EvaCycleSlots<N>*);};
template<> class EvaCycleSlots<0> {};
class EvaCycleClient : public EvaCycleSlots<31> {public:virtual unsigned getFrame() const;};
class EvaCycleView : public EvaCycleSlots<21> {public:virtual void lookAt(const Coord3D*);};
class GameClient;extern GameClient*TheGameClient;
class View;extern View*TheTacticalView;
void Eva::rva001DD3DD()
{
 EvaCycleNode*head=*(EvaCycleNode**)&m_queue;
 if(head->next!=head && !TheGameLogic->rva001DCD1C()) {
  unsigned now=((EvaCycleClient*)TheGameClient)->getFrame();
  if((EvaCycleNode*)m_queuePosition!=*(EvaCycleNode**)&m_queue && (unsigned)m_70+(unsigned)(m_cycleDuration*0.03f)>=now) {
   ++*(_STL::list<int>::iterator*)&m_queuePosition;
   if((EvaCycleNode*)m_queuePosition==*(EvaCycleNode**)&m_queue)m_queuePosition=(int)(*(EvaCycleNode**)&m_queue)->next;
  } else m_queuePosition=(int)(*(EvaCycleNode**)&m_queue)->next;
  if((EvaCycleNode*)m_queuePosition!=*(EvaCycleNode**)&m_queue) {
   ((EvaCycleView*)TheTacticalView)->lookAt(&((EvaCycleNode*)m_queuePosition)->position);
   m_70=now;
  }
 }
}
