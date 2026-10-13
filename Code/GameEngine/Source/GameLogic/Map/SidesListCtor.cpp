// cl: /O1 /G7 /arch:SSE /EHsc /MD /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
// BFME1 donor874e38488 SidesListCtorThunk.cpp supplies the constructor
// structure; retail32EE24..32EF22 independently establishes BFME2 offsets,
// arrays20 of60B, 28B teams and 28B auxiliary records. Snapshot and subsystem
// base layouts agree with existing target xfer/clear/copy bodies.
#include <stdlib.h>
namespace _STL { void __cdecl free(void *) throw(...); }
#define free _STL::free
#include <vector>
#include <map>
#include <list>
#undef free
#include "ascii_string.h"
#include "Common/Snapshot.h"
class SubsystemInterface {
public:
    SubsystemInterface();
    virtual ~SubsystemInterface();
private:
    int m_data[2];
};
#include "../../../../Libraries/Include/Lib/BfmeE16.h"
class Rva00330757Member {
public:
    Rva00330757Member() throw();
    ~Rva00330757Member() {}
private:
    _STL::vector<BfmeE16> m_items;
    int m_flags;
};
struct BfmePod128 { ~BfmePod128(); int a[32]; };
struct BfmeE8 { int a[2]; };
class SidesInfo {
public:
    SidesInfo();
    ~SidesInfo();
private:
    char m_data[0x60];
};
class TeamsInfoRec {
public:
    TeamsInfoRec();
    ~TeamsInfoRec();
private:
    char m_data[0x1C];
};
class Rva001976F0 {
public:
    Rva001976F0();
    ~Rva001976F0();
private:
    int m_key;
    _STL::vector<BfmePod128> m_first;
    _STL::vector<BfmePod128> m_second;
};
class SidesList : public SubsystemInterface, public Snapshot, public Rva00330757Member {
public:
    SidesList();
    virtual ~SidesList();
    virtual void loadPostProcess();
    virtual void crc(Xfer *);
    virtual void xfer(Xfer *);
    void clear();
private:
    _STL::list<AsciiString> m_list;
    _STL::map<int,_STL::vector<BfmePod128> > m_castleBuildLists;
    _STL::map<int,_STL::vector<_STL::vector<BfmeE8> > > m_castlePaths;
    int m_numSides;
    SidesInfo m_sides[20];
    int m_numSkirmishSides;
    SidesInfo m_skirmishSides[20];
    TeamsInfoRec m_teams;
    TeamsInfoRec m_skirmishTeams;
    bool m_cleared;
    Rva001976F0 m_extra[20];
};
typedef char SidesListSize[sizeof(SidesList)==0x11B0?1:-1];
SidesList::SidesList() : m_numSides(0),m_numSkirmishSides(0),m_cleared(true)
{
    clear();
}

// The auxiliary record constructor is the typed twin of the rowed 32C19D.
Rva001976F0::Rva001976F0() {}

// Retail posts the slot-zero member callback with the complete SidesList owner.
class Rva00281A15Listener { public: virtual void notify(void *); };
class SidesListNotifier {
public:
    void post(void (Rva00281A15Listener::*callback)(void *), void *owner);
public:
    struct Post { void (Rva00281A15Listener::*callback)(void *); void *owner; };
    void dispatch(const Post *);
};
void SidesListNotifier::post(void (Rva00281A15Listener::*callback)(void *), void *owner)
{
    Post p; p.callback=callback; p.owner=owner; dispatch(&p);
}
// ?SidesList::~SidesList present-unmatched
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline SidesList::~SidesList()
{
    reinterpret_cast<SidesListNotifier *>(static_cast<Rva00330757Member *>(this))->post(&Rva00281A15Listener::notify, this);
}

// ?bfmeAnchorSidesListDtor absent-from-retail
void bfmeAnchorSidesListDtor(SidesList *p)
{
	p->SidesList::~SidesList();
}

// Native 0x0077B9F6 is the complete 11-byte list-member cleanup at +0x20.
// The exact 240-byte destructor and complete EH graph bind this action to
// the existing STLport list<AsciiString> destructor at 0x00207F08.

// Native SidesList action 0x77ba01 is a complete 11-byte map-member cleanup
// of parent 0x32ec63; the exact parent and EH graph bind its
// standard template destructor through the independently proved wrapper fold.

// Native SidesList action 0x77ba0c is a complete 11-byte map-member cleanup
// of parent 0x32ec63; the exact parent and EH graph bind its
// standard template destructor through the independently proved wrapper fold.

// Native SidesList action 0x77bace is a complete 11-byte map-member cleanup
// of parent 0x32ee24; the exact parent and EH graph bind its
// standard template destructor through the independently proved wrapper fold.

// Native SidesList action 0x77bad9 is a complete 11-byte map-member cleanup
// of parent 0x32ee24; the exact parent and EH graph bind its
// standard template destructor through the independently proved wrapper fold.
