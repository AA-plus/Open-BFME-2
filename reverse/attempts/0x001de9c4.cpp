// ?rva001DE9C4@Eva@@QAEHPBD@Z
// partial score=0.9633 date=2026-10-13
// ?rva001DE9C4@Eva@@QAEHPBD@Z
// partial score=0.9633 date=2026-10-13 W7-MP6 r3
// nd 28 -> 6 SIZE-EXACT 161B. The decisive shape (from the WB D91920 body) is ONE shared `int id`
// assigned in both m_flag44 paths and a SINGLE trailing `if (id == -1) throw`, not per-path
// early returns: cl then merges the node/id web into EDI like retail (key=EBX, this=ESI) and the
// iterator-temp table field survives as mov [ebp-4],esi. The iterator must be built as
// `it = Rva0041534BIter(m_table48.rva00056F61(&tmp), &m_table48)` (assignment from a ctor-built
// iterator) or the dead table field is folded out and the shape reverts to 159B/nd28.
// REMAINING nd6 = ONE shrink-wrapped `push edi`: retail saves EDI in the entry prologue (before
// _strcmpi), ours saves it after the None early-out (still on both live paths). Tried inert:
// flag grid (O2/Os/Ot/Oy/G6/G7/EHsc), id=-1 init, cmp local, it hoisted before the check.
// partial score=0.93 date=2026-09-28
// ?rva001DE9C4@Eva@@QAEHPBD@Z
// partial score=0.93 date=2026-09-28
// cl: /O1 /DNDEBUG /MD /GX-
// ?rva001DE78E@Eva@@QAEHPBVAsciiString@@@Z @0x001DE78E 39B: Eva event id lookup via rowed Rva00056F61 table at +0x34.
// Donor shape from Code/GameEngine/Source/GameClient/Rva0021311FGet.cpp (iterator find 0x0041534B in embedded table returning node+8).
// Callers at 0x001DEA26 0x001DECB0 0x001DF70F 0x003392CF 0x003E5467 pass global Eva at 0x009FDC30 with AsciiString key; EVA: prefix and Unknown EVA event strings prove Eva.
// Returns -1 on miss else node+8 message id; ret 4 is thiscall with one arg.
class AsciiString;

template <typename T>
class StringBase
{
private:
	friend class AsciiString;
	friend class Eva;
	void releaseBuffer();
	StringBase(const T *text);
	StringBase(const StringBase<T> &that);
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
};

class AsciiString
{
public:
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	~AsciiString() {}
private:
	char *m_text;
};
class Rva00056F61;
struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
	Rva0041534BIter(void *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
};
struct Rva00056F61Node
{
	Rva00056F61Node *m_next;
	AsciiString m_name;
};
class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
	void *rva00056F61(const AsciiString *key);
	void *m_unused;
	union {
		Rva00056F61Node **m_begin;
		Rva00056F61Node ** volatile m_beginVolatile;
	};
	Rva00056F61Node **m_end;
};
class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
	char *mFailureMessage;
	int m_argCount;
};
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
class Eva
{
public:
	int rva001DE78E(const AsciiString *key);
	int rva001DE9C4(const char *key);
private:
	char m_pad[0x34];
	Rva00056F61 m_table34;
	int m_pad40;
	int m_flag44;
	Rva00056F61 m_table48;
};
int Eva::rva001DE78E(const AsciiString *key)
{
	Rva0041534BIter it = m_table34.rva0041534B(key);
	if (it.m_node == 0)
		return -1;
	return *(int *)((char *)it.m_node + 8);
}
// ?rva001DE9C4@Eva@@QAEHPBD@Z present-unmatched
int Eva::rva001DE9C4(const char *key)
{
	if (_strcmpi("None", key) == 0)
		return -1;
	int id;
	if (m_flag44 == 0)
	{
		Rva0041534BIter it(0, &m_table48);
		{
			AsciiString tmp(key);
			it = Rva0041534BIter(m_table48.rva00056F61(&tmp), &m_table48);
			((StringBase<char> *)&tmp)->releaseBuffer();
		}
		if (it.m_node == 0)
			throw INIException(3, "Expected a recognized Eva event name or 'None'; got '%s'", key);
		id = *(int *)((char *)it.m_node + 8);
	}
	else
	{
		{
			AsciiString tmp(key);
			id = rva001DE78E(&tmp);
			((StringBase<char> *)&tmp)->releaseBuffer();
		}
	}
	if (id == -1)
		throw INIException(3, "Expected a recognized Eva event name or 'None'; got '%s'", key);
	return id;
}
