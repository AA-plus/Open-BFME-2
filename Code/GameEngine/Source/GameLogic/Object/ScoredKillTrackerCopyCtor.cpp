// cl: /ICode/GameEngine/Source/Common /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// class-gate: allow ScoredKillTracker copy-constructor view whose tracked-kill list is typed by the list copy twin retail calls (0x0055AB41) rather than the shared view's list<int> (pinned to the twin 0x00445E8B)
// ??0ScoredKillTracker@@QAE@ABV0@@Z, retail 0x0055AB99..0x0055AC1F (134
// bytes, EH): ScoredKillTracker's copy constructor (layout as in
// ScoredKillTrackerView.h). It copies Snapshot, the lifetime, the indexed
// filter (rowed 0x003623E5 view), the +0xC scalar, starts unhooked
// (keeper 0, player -1), copies the tracked-kill list (rowed list copy
// 0x0055AB41) and count and the position, then rehooks to the source's
// keeper (rowed hookToKeeper 0x0055A93C). Finishes the 1.0 bank whose
// list<int> bound the other list-copy twin.
#include <list>
#define BFME_SNAPSHOT_NAME_SLOT 1
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS 1
#include "Common/Snapshot.h"
#undef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#undef BFME_SNAPSHOT_NAME_SLOT
#include "../../../Libraries/Include/Lib/Coord3D.h"

struct Rva0055AB41Element { double words[1]; };
namespace _STL {
template<> list<Rva0055AB41Element, allocator<Rva0055AB41Element> >::list(const list<Rva0055AB41Element, allocator<Rva0055AB41Element> > &x);
}

class Rva00360D26Member {
public:
 Rva00360D26Member();
 ~Rva00360D26Member();
 int index;
};
struct ScoredKillTrackerPosition {
 Coord3D value;
 ScoredKillTrackerPosition(const ScoredKillTrackerPosition &other) {
  value.x=other.value.x;value.y=other.value.y;value.z=other.value.z;
 }
};
class Rva0039BCF8;
class ScoredKillTracker:public Snapshot {
public:
 ScoredKillTracker(const ScoredKillTracker &);
 virtual ~ScoredKillTracker();
 virtual void LoadPostProcess();
 virtual const char *GetSnapshotName() const;
 virtual void DoXfer(Xfer *);
 void hookToKeeper(Rva0039BCF8 *);
private:
 unsigned m_lifetime;
 Rva00360D26Member m_filter;
 unsigned m_value0c;
 Rva0039BCF8 *m_keeper;
 int m_playerIndex;
 _STL::list<Rva0055AB41Element> m_trackedKills;
 int m_trackedKillsCount;
 ScoredKillTrackerPosition m_position;
};
typedef char ScoredKillTrackerSizeIs44[sizeof(ScoredKillTracker)==44?1:-1];

ScoredKillTracker::ScoredKillTracker(const ScoredKillTracker &other):Snapshot(other),
 m_lifetime(other.m_lifetime),m_filter(other.m_filter),m_value0c(other.m_value0c),m_keeper(0),m_playerIndex(-1),m_trackedKills(other.m_trackedKills),m_trackedKillsCount(other.m_trackedKillsCount),m_position(other.m_position) {
 if(other.m_keeper)hookToKeeper(other.m_keeper);
}
