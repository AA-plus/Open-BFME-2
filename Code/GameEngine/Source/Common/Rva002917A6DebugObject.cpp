// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Retail 0x002917A6 (66B, EH, cdecl), an EH-prolog start Ghidra never listed:
// the debug stream insertion of an object -- the rowed DescribeObject
// (0x0028F982) label streamed through the rowed Debug string insertion
// (0x000028E8, the StringBase<char> template instance), returning the stream.
#include "ascii_string.h"

class Debug
{
public:
	virtual void slot00();
};
class Object;

template <class T> Debug &operator<<(Debug &dbg, const StringBase<T> &text);
AsciiString DescribeObject(const Object *obj);

static __forceinline const StringBase<char> &asBase(const AsciiString &text)
{
	return reinterpret_cast<const StringBase<char> &>(text);
}

Debug &operator<<(Debug &dbg, const Object *obj)
{
	dbg << asBase(DescribeObject(obj));
	return dbg;
}
