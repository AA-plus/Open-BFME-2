// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (nineteenth batch; see GapBodiesGE01.cpp). Each begins after its
// neighbour's padding and ends in its own ret. Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.
#include "ascii_string.h"

// --- 0x0002BEFB (19B): exchange two dwords through their pointers.
void rva0002BEFB(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

// --- 0x0002C655 (20B): bucket of a key: the empty hash functor at +0 (the
// rowed rts::hash<AsciiString> 0x0002BF8C, whose header names this caller)
// modulo the bucket count.
namespace rts
{
	template <class T> struct hash
	{
	};
	template <> struct hash<AsciiString>
	{
		unsigned int operator()(const AsciiString &key) const;
	};
}

class Rva0002C655
{
public:
	unsigned int rva0002C655(const AsciiString &key, unsigned int n) const;
private:
	rts::hash<AsciiString> m_hash;
};

unsigned int Rva0002C655::rva0002C655(const AsciiString &key, unsigned int n) const
{
	return m_hash(key) % n;
}

// --- 0x0002C7E8 (21B): case-insensitive key equality through the rowed
// StringBase<char>::compareNoCase 0x00006A00; the functor's this is unused.
class Rva0002C7E8
{
public:
	bool rva0002C7E8(const AsciiString &a, const AsciiString &b) const;
};

bool Rva0002C7E8::rva0002C7E8(const AsciiString &a, const AsciiString &b) const
{
	return ((const StringBase<char> &)a).compareNoCase((const StringBase<char> &)b) == 0;
}
