// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?getScienceFromInternalName@ScienceStore@@QBE?AW4ScienceType@@ABVAsciiString@@@Z @0x001FF725 30B
// Zero Hour's ScienceStore::getScienceFromInternalName (Common/RTS/Science.cpp):
// if the AsciiString is empty return SCIENCE_INVALID (-1), else tail-jmp to
// NameKeyGenerator::nameToKey via TheNameKeyGenerator. Every retail caller
// (0x003062B6, 0x003BC6E6, 0x003BC7D0, 0x003E4414, 0x003E4480) loads
// TheScienceStore into ECX first; the body never reads it. Via rowed isEmpty
// 0x00001E2F.
#include "ascii_string.h"
enum ScienceType { SCIENCE_INVALID = -1 };
enum NameKeyType { NAMEKEY_INVALID = -1 };
class NameKeyGenerator {
public:
	NameKeyType nameToKey(const AsciiString &str);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class ScienceStore {
public:
	ScienceType getScienceFromInternalName(const AsciiString &name) const;
};

ScienceType ScienceStore::getScienceFromInternalName(const AsciiString &name) const
{
	if (name.isEmpty())
		return SCIENCE_INVALID;
	return (ScienceType)TheNameKeyGenerator->nameToKey(name);
}
