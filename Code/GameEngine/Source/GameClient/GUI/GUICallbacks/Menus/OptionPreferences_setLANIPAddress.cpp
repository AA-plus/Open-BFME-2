// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?setLANIPAddress@OptionPreferences@@QAEXI@Z, retail 0x002E50BB,
// 143 bytes. Dedicated TU.
//
// ZH/BFME1 OptionPreferences::setLANIPAddress shape verbatim (four-octet
// "%d.%d.%d.%d" format plus named key plus named slot split assigning through
// the prefs map). Same push-sink recipe as the landed setCampaignDifficulty
// sibling. Same string plumbing with pinned operator[]/assign/ctor/release/
// format callees. Retail keeps default EH.

#include <map>

typedef bool Bool;
typedef int Int;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

typedef _STL::map<AsciiString, AsciiString> AsciiPreferenceMap;

namespace _STL
{
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &key);
}

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	void setLANIPAddress(AsciiString IP);
	void setLANIPAddress(unsigned int ip);
	void setOnlineIPAddress(AsciiString IP);
	void setOnlineIPAddress(unsigned int ip);
};

// ?setLANIPAddress@OptionPreferences@@QAEXVAsciiString@@@Z, retail
// 0x002E505A (97 bytes), directly before the unsigned overload: ZH's
// string overload, verbatim.
// Select-any like the OptionsMenu.cpp copy (this retail body comes first in
// link order, so it is the copy the link keeps); the anchor keeps the noinline
// body emitted.
inline __declspec(noinline) void OptionPreferences::setLANIPAddress(AsciiString IP)
{
	(*this)["IPAddress"] = IP;
}

// Retain the inline bodies' ledger emission without changing their callers.
// ?bfmeEmitOptionPreferencesSetIP@@YAXPAVOptionPreferences@@@Z absent-from-retail
void bfmeEmitOptionPreferencesSetIP(OptionPreferences *p)
{
	AsciiString empty;
	p->OptionPreferences::setLANIPAddress(empty);
	p->OptionPreferences::setOnlineIPAddress(empty);
}

// ?setLANIPAddress@OptionPreferences@@QAEXI@Z
void OptionPreferences::setLANIPAddress(unsigned int ip)
{
	AsciiString text;
	text.format("%d.%d.%d.%d", ip >> 24,
		((ip & 0xff0000) >> 16), ((ip & 0xff00) >> 8), (ip & 0xff));
	AsciiString key("IPAddress");
	AsciiString &slot = (*this)[key];
	slot = text;
}

// ?setOnlineIPAddress@OptionPreferences@@QAEXVAsciiString@@@Z, retail
// 0x002E520C (97 bytes), directly before the unsigned overload: ZH's
// string overload, verbatim.
// Select-any, as setLANIPAddress above.
inline __declspec(noinline) void OptionPreferences::setOnlineIPAddress(AsciiString IP)
{
	(*this)["GameSpyIPAddress"] = IP;
}

// ?setOnlineIPAddress@OptionPreferences@@QAEXI@Z
void OptionPreferences::setOnlineIPAddress(unsigned int ip)
{
	AsciiString text;
	text.format("%d.%d.%d.%d", ip >> 24,
		((ip & 0xff0000) >> 16), ((ip & 0xff00) >> 8), (ip & 0xff));
	AsciiString key("GameSpyIPAddress");
	AsciiString &slot = (*this)[key];
	slot = text;
}
