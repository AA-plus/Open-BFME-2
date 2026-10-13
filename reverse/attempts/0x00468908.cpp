// ?_M_create_nodes@?$_Deque_base@VBuddyResponse@@V?$allocator@VBuddyResponse@@@_STL@@@_STL@@IAEXPAPAVBuddyResponse@@0@Z
// partial score=0.72 date=2026-10-13
// ?rva00468908 (215B, native 0x00468908..0x004689DE RET0, SEH prolog)
// w7-mo4 draft bank, 2026-10-13. The picker row carried no bank and the old
// Ghidra name (_M_create_nodes@_Deque_base<BuddyResponse>) was refuted. Callee
// identity from the ledger rows at the call targets:
//   0x0002F681 INIException::INIException(int, const char*, ...)
//   0x00629094 __CxxThrowException
//   0x0002DEED INI::getNextTokenOrNull(const char*)   (called twice on [ebp+8])
//   0x000055F5 StringBase<char>::set(const char*)     (twice, on two 4-byte members)
//   0x0002EF72 INI::parseUnsignedInt(INI*, void*, void*, const void*)  (4 pushes)
//   0x004688D1 vector<BfmeStringRecord00466E64>::push_back (on instance+0x180)
//   0x00466E23 ~BfmeStringRecord00466E64 (the 12-byte record dtor)
// So this is an INI field-parse proc: it bounds a 12-byte string-record vector
// at instance+0x180 to 4 entries (else INIException code 4 + throw), reads two
// tokens, requires both non-empty, builds a 12-byte record {StringBase name;
// StringBase value; unsigned flag=0x1869F}, parses an unsigned int into the
// flag, pushes the record into the vector, then runs the record dtor.
// First draft diffs (ours vs retail): the instance register (eax vs esi, retail
// loads esi=[ebp+0xc] first), the 0xC constant materialisation order around cdq
// (retail push 0xc; cdq; pop ecx) and one extra cdq. Not exact yet.
// draft reconstruction of 0x00468908 (215B) - INI field parse proc pushing a
// 12-byte string record into a vector at instance+0x180, max 4 entries.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode /I.
typedef bool Bool;
typedef int Int;

class StringBase { public: void set(const char *s); private: const char *m_data; };

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);
	static void parseUnsignedInt(INI *ini, void *store, void *field, const void *userData);
};

struct BfmeStringRecord00466E64
{
	StringBase m_name;
	StringBase m_value;
	unsigned m_flag;
	~BfmeStringRecord00466E64();
};

namespace _STL {
template <class T> class allocator {};
template <class T, class A> class vector
{
public:
	void push_back(const T &value);
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class INIException
{
public:
	INIException(int code, const char *format, ...);
};

extern "C" void __stdcall __CxxThrowException(void *obj, void *type);
extern void *const g_INIExceptionType;
extern const char g_00C44380Message[];
extern const char g_00CFE2FCFile[];

struct BuddyResponseOwner
{
	char m_pad00[0x180];
	_STL::vector<BfmeStringRecord00466E64, _STL::allocator<BfmeStringRecord00466E64> > m_responses; // +0x180
};

void rva00468908(INI *ini, BuddyResponseOwner *instance, void *store, const void *userData)
{
	if ((instance->m_responses.m_finish - instance->m_responses.m_start) / 12 >= 4)
		throw INIException(4, g_00C44380Message, 1, g_00CFE2FCFile);
	const char *first = ini->getNextTokenOrNull(0);
	const char *second = ini->getNextTokenOrNull(0);
	if (!first || !*first || !second || !*second)
		return;
	BfmeStringRecord00466E64 record;
	record.m_name.set(first);
	record.m_value.set(second);
	INI::parseUnsignedInt(ini, store, &record.m_flag, userData);
	instance->m_responses.push_back(record);
}
