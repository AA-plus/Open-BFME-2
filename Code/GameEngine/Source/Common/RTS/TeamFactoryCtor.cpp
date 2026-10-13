// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0TeamFactory@@QAE@XZ, retail 0x003A25B1, 109 bytes.
//
// Evidence from the retail body: the rowed SubsystemInterface ctor 0x001B4E63
// (twelve-byte base), the inlined trivial Snapshot ctor's vptr store at +0xC
// (0x00BBB554, canonical Snapshot header), the two TeamFactory vtables
// 0x0081AE2C / 0x0081AE1C, the rowed pod-map ctor 0x0024613C at +0xB0, zeroes
// at +0xBC and +0xC0, and memset(this+0x10, 0, 0xA0) for the forty-pointer
// m_dummyTeams array. Layout: SubsystemInterface(0xC) + Snapshot(4) +
// m_dummyTeams[40] (0xA0) + map (0xC) + two ints = 0xC4, the size the
// GameEngineInit view gives TeamFactory. TeamFactoryDtor.cpp (rowed at
// 0x003A383A) stores the same two vtables and destroys the +0xB0 member, and
// TeamFactoryClear.cpp names the +0x10 array and the +0xB0 map, so the member
// roles come from the rowed family rather than from this TU's guess.

#define __PLACEMENT_VEC_NEW_INLINE
#include <map>
#include <string.h>

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	char m_pad04[8];
};

struct BfmePod8
{
	int words[2];
};

class TeamPrototype;

class TeamFactory : public SubsystemInterface, public Snapshot
{
public:
	TeamFactory();
	virtual ~TeamFactory();

protected:
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);

private:
	TeamPrototype *m_dummyTeams[40]; // +0x10
	std::map<int, BfmePod8> m_prototypes; // +0xB0
	int m_uniqueTeamPrototypeID; // +0xBC
	int m_uniqueTeamID; // +0xC0
};

TeamFactory::TeamFactory()
	: m_uniqueTeamPrototypeID(0), m_uniqueTeamID(0)
{
	memset(m_dummyTeams, 0, sizeof(m_dummyTeams));
}
