// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
//
// ??0LANGameSlot@@QAE@ABV0@@Z @0x0044B27F 107B: LANGameSlot's copy
// constructor (callers 0x0044B6E9 0x00582402 0x0058265D 0x00582D16; Zero
// Hour's LANAPI::RequestGameCreate passes a local slot by value to
// LANGameInfo::setSlot). It copies the rowed GameSlot base (0x002295D7,
// 0x1AC bytes), installs the LANGameSlot vtable 0x00C3E4FC (the one the
// default constructor 0x00448150 stores), copies the LANPlayer at +0x1AC
// (rowed copy 0x0044A901), the AsciiString at +0x1C8 and the last-heard
// word at +0x1CC.
//
// ??_GLANGameSlot@@UAEPAXI@Z @0x0044818B 28B: slot 0 of that vtable, the
// scalar deleting destructor this unit emits with the vtable; it calls the
// implicit ~LANGameSlot 0x00447B0E and the global operator delete.

#include "ascii_string.h"

class GameSlot {
public:
	GameSlot(const GameSlot &other);
	virtual ~GameSlot();

	char m_pad[0x1A8];
};

class LANPlayer
{
public:
	LANPlayer(const LANPlayer &other);
	~LANPlayer();

private:
	char m_pad[0x1C];
};

class LANGameSlot : public GameSlot
{
public:
	LANGameSlot(const LANGameSlot &other);
	virtual ~LANGameSlot();

private:
	LANPlayer m_user;				// +0x1AC
	AsciiString m_serial;				// +0x1C8
	unsigned int m_lastHeard;			// +0x1CC
};

LANGameSlot::LANGameSlot(const LANGameSlot &other) :
	GameSlot(other),
	m_user(other.m_user),
	m_serial(other.m_serial),
	m_lastHeard(other.m_lastHeard)
{
}
