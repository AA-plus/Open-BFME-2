// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x00467DE6 (123B, EH, cdecl), an EH-prolog start Ghidra never listed:
// an INI field parse callback in the shape of Zero Hour's
// TransportContainModuleData::parseInitialPayload (neighbours: the
// TransportContain destructor and Rva00467DCDDestroy.cpp). It reads a name and
// an optional count (default 1) and appends the {name, count} record to the
// list at instance + 0xA4 through the rowed push_back 0x00467DB3, whose pinned
// spelling is for a list of pointers; the record is passed by reference
// through it. Names are address-derived.
#include "ascii_string.h"

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	int scanInt(const char *token);
};

class Rva00467DB3Obj;

namespace _STL
{
template <class T> class allocator;
template <class T, class A> class list
{
public:
	void push_back(const T &);
};
}

struct Rva00467DE6Payload
{
	Rva00467DE6Payload() : count(0) {}
	AsciiString name;
	int count;
};

void __cdecl rva00467DE6(INI *ini, void *instance, void *store, const void *userData)
{
	const char *name = ini->getNextToken(0);
	const char *countText = ini->getNextTokenOrNull(0);
	int count = countText ? ini->scanInt(countText) : 1;
	Rva00467DE6Payload payload;
	payload.name.set(name);
	payload.count = count;
	reinterpret_cast<_STL::list<Rva00467DB3Obj *, _STL::allocator<Rva00467DB3Obj *> > *>(
		static_cast<char *>(instance) + 0xA4)->push_back(reinterpret_cast<Rva00467DB3Obj *const &>(payload));
}
