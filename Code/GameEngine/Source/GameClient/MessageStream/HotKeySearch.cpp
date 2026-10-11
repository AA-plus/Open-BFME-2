// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc
// HotKeyManager::searchHotKey, retail 0x00358B9E (194 bytes): the hot key a
// label marks with '&' (the character after the first ampersand, translated
// to an AsciiString), or the empty string. Its own unit: HotKey.cpp builds
// without /arch:SSE /G7 /EHsc. Body from the banked BFME 1 hotkey donor
// (Open-BFME-1 1399ad37, GameClient HotKey.cpp) over BFME 2's canonical
// strings; it becomes exact once StringBase::isEmpty is declared throw(),
// as retail compiles its calls.
#include "ascii_string.h"
#include "unicode_string.h"
template<> inline void StringBase<unsigned short>::concat(unsigned short character)
{ concat(&character, 1); }
class GameTextInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13();
	// Slot 14 (+0x38): the text a label names.
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};
extern GameTextInterface *TheGameText;

class HotKeyManager
{
public:
	AsciiString searchHotKey( const AsciiString& );
	AsciiString searchHotKey( const UnicodeString& );
};

// ?searchHotKey@HotKeyManager@@QAE?AVAsciiString@@ABVUnicodeString@@@Z
AsciiString HotKeyManager::searchHotKey( const UnicodeString& uStr )
{
	if (uStr.isEmpty())
		return AsciiString::TheEmptyString;

	const unsigned short *marker = uStr.str();
	while (marker && *marker)
	{
		if (*marker == L'&')
		{
			UnicodeString tmp = UnicodeString::TheEmptyString;
			tmp.StringBase<unsigned short>::concat(*(marker + 1));
			AsciiString retStr;
			retStr.translate( tmp );
			return retStr;
		}
		marker++;
	}
	return AsciiString::TheEmptyString;
}

// HotKeyManager::searchHotKey(const AsciiString &), retail 0x00358CCD (90
// bytes): the hot key of the text a label names (TheGameText slot 14).
AsciiString HotKeyManager::searchHotKey( const AsciiString& label )
{
	return searchHotKey(TheGameText->fetch(label));
}
