// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// ??1LANGameSlot@@UAE@XZ @0x00447B0E 74B: Zero Hour's LANGameSlot declares
// no destructor (GameNetwork/LANGameInfo.h), so this is the implicit virtual
// one. Target evidence: slot 0 of vtable 0x00C3E4FC, which the slot
// constructors 0x00448150 and 0x0044B27F install, is the scalar deleting
// destructor 0x0044818B calling this body; LANGameInfo's destructor
// 0x004482FB destroys its eight 0x1D0-byte slots with it. It releases the
// AsciiString at +0x1C8 (releaseBuffer 0x00036410), destroys the LANPlayer at
// +0x1AC (0x00447ACA) and runs ~GameSlot (0x002294FD) without re-storing the
// vtable, which is how MSVC 7.1 compiles an implicit destructor (a
// user-written one stores it first). Base size 0x1AC proven by
// SaveGameInfoCopyBFME2.

#include "ascii_string.h"

class GameSlot
{
public:
	virtual ~GameSlot();

private:
	char m_body[0x1AC - 4];
};

class LANPlayer
{
public:
	~LANPlayer();

private:
	char m_body[0x1C];
};

class LANGameSlot : public GameSlot
{
public:
	LANGameSlot();

private:
	LANPlayer m_user;				// +0x1AC
	AsciiString m_serial;				// +0x1C8
	unsigned int m_lastHeard;			// +0x1CC
};

// Makes this unit emit the implicit destructor; not retail code.
// ?<LANGameSlot::~LANGameSlot anchor> absent-from-retail
void bfmeAnchorLANGameSlotDtor(LANGameSlot *slot)
{
	slot->LANGameSlot::~LANGameSlot();
}
