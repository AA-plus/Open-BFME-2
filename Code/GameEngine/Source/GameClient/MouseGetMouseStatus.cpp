// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?getMouseStatus@Mouse@@QAEPBUMouseIO@@XZ, retail 0x000425A2, 7 bytes:
//
//     lea eax,[ecx+0x4F0C] / ret
//
// The address of the Mouse's current polled state. Three TUs call it; two
// already emit exactly these bytes from TU-local views (their digests agree)
// while InGameUI.cpp's Zero Hour header view puts m_currMouse at +0x1D0 and
// its copy loses the COMDAT fold. Retail's disp32 (+0x4F0C) is read off the
// rowed body itself: a lea of [ecx+0x4F0C] at a ret-padded function start.
// This out-of-line definition is the strong home; the select-any copies
// elsewhere fold to it. It repoints the Rva000425A2LeaGetter scaffold row
// (same address, same bytes, unwitnessed pointee) at the recovered identity.
//
// Layout lead: the sibling caller views in
// BfmeOwnVVDTranslateGameMessage.cpp and AptMessengerCallbacks.cpp, which
// both place m_currMouse at +0x4F0C and emit byte-identical copies.

struct ICoord2D
{
	int x;
	int y;
};

struct MouseIO
{
	ICoord2D pos; // +0x00
	char m_pad08[0x18 - 8];
	int leftState; // +0x18
};

class Mouse
{
public:
	const MouseIO *getMouseStatus();

private:
	char m_pad00[0x4F0C];
	MouseIO m_currMouse; // +0x4F0C
};

// ?getMouseStatus@Mouse@@QAEPBUMouseIO@@XZ
const MouseIO *Mouse::getMouseStatus()
{
	return &m_currMouse;
}
