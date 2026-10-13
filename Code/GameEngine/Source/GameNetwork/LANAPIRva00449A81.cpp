// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc
// ?setName@LANGameInfo@@QAEXVUnicodeString@@@Z @0x00449A81 55B: Zero Hour's
// inline LANGameInfo::setName (GameNetwork/LANGameInfo.h), m_gameName = name,
// kept out of line. Target evidence: LANAPI::RequestGameCreate calls it on
// the new 0xF6C-byte LANGameInfo; the body stores the by-value UnicodeString
// into +0xF64 (LANGameInfo's m_gameName, see LANGameInfoCtor.cpp) through
// StringBase<G>::set 0x37150 and releases the argument (0x36E70) after an
// EH_prolog.
#include "unicode_string.h"

class LANGameInfo
{
public:
	void setName(UnicodeString name);
private:
	unsigned char m_pad00[0xF64];
	UnicodeString m_gameName;			// +0xF64
};

void LANGameInfo::setName(UnicodeString name)
{
	UnicodeString &slot = m_gameName;
	slot.set(name);
}
