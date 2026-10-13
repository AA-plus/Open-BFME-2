// cl: /O1 /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?parse@VersionBlockParser@@AAE_NPBD@Z @0x004289B8 367B.
// Private version-block parser: validates the ||VER1| header (memcmp), reads the
// size with sscanf, requires the block length to be below it, then splits
// key=value pairs on = and | into records pushed into the vector and finally
// sorts them. Evidence: WB debug body for the branch structure; strings ||VER1|
// and %d|; callees all rowed; caller VersionBlockParserCtor 0x428C04.
// Codegen: /EHs-c- /EHs drops the extern-C no-throw assumption so the inline
// ~basic_string free keeps retail's unwind state store.
#include <vector>
#include <string>
#include <algorithm>
extern "C" int __cdecl memcmp(const void *a, const void *b, unsigned int n);
extern "C" unsigned int __cdecl strlen(const char *s);
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buf, const char *fmt, ...);

// The vector instance retail links is the one rowed for the 0x18-byte record
// named BfmeNarrowRecord00427F75; the parser's local entry derives from it.
struct BfmeNarrowRecord00427F75
{
	_STL::basic_string<char> m_key;
	_STL::basic_string<char> m_value;
	BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &);
	~BfmeNarrowRecord00427F75();
};

struct VersionBlockEntry : public BfmeNarrowRecord00427F75
{
	VersionBlockEntry();
	~VersionBlockEntry();
};

class VersionBlockKeyCompare
{
public:
	bool operator()(const VersionBlockEntry &a, const VersionBlockEntry &b) const
	{
		return a.m_key < b.m_key;
	}
};

class VersionBlockParser
{
public:
	VersionBlockParser(const char *versionBlock);
private:
	int m_size;
	_STL::vector<BfmeNarrowRecord00427F75> m_records;
	bool parse(const char *versionBlock);
};

bool VersionBlockParser::parse(const char *versionBlock)
{
	if (memcmp(versionBlock, "||VER1|", 7) != 0)
		return false;
	if (sscanf(versionBlock + 7, "%d|", &m_size) != 1)
		return false;
	if (strlen(versionBlock) >= (unsigned int)m_size)
		return false;
	char *s = (char *)(versionBlock + 7);
	while (*s != 0)
	{
		if (*s == '|')
			break;
		++s;
	}
	if (*s != 0)
		++s;
	while (*s != 0)
	{
		char *keyStart = s;
		while (*s != 0 && *s != '=' && *s != '|')
			++s;
		if (*s != '=')
			continue;
		_STL::basic_string<char> key(keyStart, s);
		++s;
		char *valStart = s;
		while (*s != 0 && *s != '|')
			++s;
		_STL::basic_string<char> val(valStart, s);
		VersionBlockEntry e;
		e.m_key.assign(key);
		e.m_value.assign(val);
		m_records.push_back(e);
		if (*s != 0)
			++s;
	}
	_STL::sort((VersionBlockEntry *)&*m_records.begin(), (VersionBlockEntry *)&*m_records.end(), VersionBlockKeyCompare());
	return true;
}
