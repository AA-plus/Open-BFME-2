// ?rva002E53FA@OptionPreferences@@QAEXH@Z
// stlport
//
// ?rva002E53FA@OptionPreferences@@QAEXH@Z, retail 0x002E53FA,
// 96 bytes. AudioLOD setter twin of rva002E537B: writes the AudioLOD name
// for val through base-map subscript 0x002031FB plus StringBase::set
// 0x000055F5; level name from rowed indexed getter 0x00202678; key
// "AudioLOD" at 0x804CB8; manager at 0x9FE144.

// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB

#include <map>
#include <stdlib.h>
#include <string.h>

typedef bool Bool;
typedef int Int;

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

// The rowed GameLODManager::getAudioLODLevelName at 0x00202678 (the retail
// caller sets ecx to TheGameLODManager immediately before the call).
class GameLODManager
{
public:
	const char *getAudioLODLevelName(Int i);
};

extern GameLODManager *TheGameLODManager;


class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	void rva002E53FA(Int val);
};

void OptionPreferences::rva002E53FA(Int val)
{
	AsciiString key("AudioLOD");
	const char *levelName = TheGameLODManager->getAudioLODLevelName(val);
	AsciiString &value = (*this)[key];
	value.set(levelName);
}
