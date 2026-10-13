// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?setLogin@LANGameSlot@@QAEXVAsciiString@@@Z, retail 0x0024955E, 55 bytes,
// and ?setHost@LANGameSlot@@QAEXVAsciiString@@@Z, retail 0x00249595, 55
// bytes: Zero Hour's inline LANGameSlot setters (GameNetwork/LANGameInfo.h),
// m_user.setLogin(name) / m_user.setHost(name), which translate the by-value
// AsciiString into LANPlayer's m_login / m_host (slot +0x1B0 / +0x1B4, the
// LANPlayer at +0x1AC) through rowed UnicodeString::translate and destroy the
// argument in the EH epilogue (rowed narrow releaseBuffer). Target evidence:
// LANAPI::RequestGameCreate calls them on its local LANGameSlot, and the
// host-name handler of LANAPICallbacks.cpp on a getLANSlot result; both are
// __thiscall with ret 4. Retail keeps them out of line.
typedef unsigned short WideChar;
typedef bool Bool;

#include "ascii_string.h"


#include "unicode_string.h"

class LANGameSlot
{
public:
	void setLogin(AsciiString name);
	void setHost(AsciiString name);
private:
	char m_pad[0x1B0];
	UnicodeString m_login;				// +0x1B0, m_user.m_login
	UnicodeString m_host;				// +0x1B4, m_user.m_host
};

void LANGameSlot::setLogin(AsciiString name)
{
	m_login.translate(name);
}

void LANGameSlot::setHost(AsciiString name)
{
	m_host.translate(name);
}
