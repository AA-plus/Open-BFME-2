// ?rva0021F5F8@CreateAHeroManager@@QAEXXZ
// partial score=0.97 date=2026-10-13
// ?rva0021F5F8@CreateAHeroManager@@QAEXXZ
// partial score=0.97 date=2026-10-13
// ?rva0021F5F8@CreateAHeroManager@@QAEXXZ
// partial score=0.9662 date=2026-10-13
// ?rva0021F5F8@CreateAHeroManager@@QAEXXZ
// partial score=0.98 date=2026-10-11
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0021F19B@@QAE@XZ
// retail 0x0021F19B..0x0021F403 (617 bytes) thiscall RET 0.
//
// The create-a-hero file list's constructor (callers 0x0021F4F0 and
// 0x0021F60D). Its vector of (file name, system flag) pairs is filled from
// "Data\SystemHeroes\" + "MyHero*.cah" through
// FileSystem::getFileListInDirectory (pinned 0x00600FC9), each entry the
// file name after its last '\' and flagged as a system hero, then sorted
// with the rowed comparator sort 0x0021F13C. Unless the flag byte
// 0x009FE34C is set it appends the user's heroes: L"MyHero*.cah" in
// TheGameState's save directory (0x002DC267) through the wide listing
// (pinned 0x006007DA, its set rowed as Rva0021C459), each name narrowed
// through AsciiString(const UnicodeString&). The name stays address-derived.
#include <set>
#include <vector>
#include <algorithm>
#include "ascii_string.h"
#include "unicode_string.h"

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
}

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &a, const AsciiString &b) const;
};
typedef _STL::set<AsciiString, BfmeStringNoCaseLess> FilenameList;

// The wide file list (a set of UnicodeString) under its rowed spelling: its
// constructor is the folded set constructor 0x000D3A71, its destructor
// 0x0021D5D5.
class Rva0021C459 : public FilenameList
{
public:
	~Rva0021C459();
};

class FileSystem
{
public:
	void getFileListInDirectory(const AsciiString &directory, const AsciiString &searchName, FilenameList &filenameList, bool searchSubdirectories) const;	// 0x00600FC9
};

class Rva006007DAFileSystem
{
public:
	void rva006007DA(const UnicodeString *directory, const UnicodeString *searchName, Rva0021C459 *filenameList, bool searchSubdirectories);	// 0x006007DA
};
extern FileSystem *TheFileSystem;

class GameState;
extern GameState *TheGameState;

// The game state's save directory (0x002DC267), rowed under its own spelling.
class Rva002DC267
{
public:
	UnicodeString rva002DC267() const;
};

// The wide listing takes its strings by address; retail passes temporaries.
static __forceinline const UnicodeString *byAddress(const UnicodeString &text)
{
	return &text;
}

extern unsigned char g_rva005B5C02Flag;

typedef _STL::pair<const AsciiString, char> HeroFileEntry;

// The sorted element and comparator under their rowed spellings.
class Rva0021915B;
struct Rva0021B753
{
	bool operator()(const Rva0021915B &a, const Rva0021915B &b) const;
};

namespace _STL {
template <> void vector<HeroFileEntry, allocator<HeroFileEntry> >::push_back(const HeroFileEntry &value);
template <> void sort<Rva0021915B *, Rva0021B753>(Rva0021915B *first, Rva0021915B *last, Rva0021B753 comp);
}

class Rva0021F19B
{
public:
	Rva0021F19B();

private:
	_STL::vector<int> m_files;	// the (file name, system flag) pairs
};

Rva0021F19B::Rva0021F19B()
{
	_STL::vector<HeroFileEntry> &files = *reinterpret_cast<_STL::vector<HeroFileEntry> *>(&m_files);
	{
		FilenameList filenameList;
		TheFileSystem->getFileListInDirectory(AsciiString("Data\\SystemHeroes\\"), AsciiString("MyHero*.cah"), filenameList, false);
		for (FilenameList::iterator it = filenameList.begin(); it != filenameList.end(); ++it)
		{
			AsciiString path = *it;
			const char *slash = path.reverseFind('\\');
			HeroFileEntry entry(AsciiString(slash ? slash + 1 : path.str()), false);
			entry.second = true;
			files.push_back(entry);
		}
	}
	_STL::sort(reinterpret_cast<Rva0021915B *>(&*files.begin()), reinterpret_cast<Rva0021915B *>(&*files.end()), Rva0021B753());

	if (!g_rva005B5C02Flag)
	{
		Rva0021C459 filenameList;
		((Rva006007DAFileSystem *)TheFileSystem)->rva006007DA(byAddress(((const Rva002DC267 *)TheGameState)->rva002DC267()),
			byAddress(UnicodeString(L"MyHero*.cah")), &filenameList, false);
		for (FilenameList::iterator it = filenameList.begin(); it != filenameList.end(); ++it)
		{
			AsciiString path(*(const UnicodeString *)&*it);
			const char *slash = path.reverseFind('\\');
			HeroFileEntry entry(AsciiString(slash ? slash + 1 : path.str()), false);
			files.push_back(entry);
		}
	}
}

// ?rva0021F5F8@CreateAHeroManager@@QAEXXZ, retail 0x0021F5F8..0x0021F797
// (415 bytes, EH; caller the screen destructor 0x00513BAB): reconciles the
// hero files with the manager's heroes. For each listed file whose
// suffix-stripped name (0x0021C12F, pinned) the hero list (+0x174) does not
// know, it writes the save directory plus the file name to the debugger;
// then each hero that is not a system hero (+0x48, unless the 0x009FE34C
// flag is set) and has a name (+0x4C) is saved under its file name
// (0x0021A651) through 0x004098BE. The list is destroyed through its rowed
// destructor 0x0021DB35. Address-derived names.
class CreateAHeroData;
class Rva0040A3F9
{
public:
	CreateAHeroData *rva0040A5CF(const AsciiString &name);	// 0x0040A5CF
	CreateAHeroData *rva0040A32F(int index);				// 0x0040A32F
	CreateAHeroData **m_begin;
	CreateAHeroData **m_end;
};
struct Rva0021F5F8Hero
{
	unsigned char m_pad00[0x48];
	bool m_system;					// +0x48
	unsigned char m_pad49[0x4c - 0x49];
	AsciiString m_name;				// +0x4C
};
class CreateAHeroHero { public: bool rva004098BE(const AsciiString &file, bool system); };
AsciiString Rva0021A651Filename(const AsciiString &name);
AsciiString Rva0021C12FStripName(const AsciiString &file);

class Rva0021DB35 { public: ~Rva0021DB35(); };
class Rva0021F5F8FileList
{
public:
	Rva0021F5F8FileList() { ((Rva0021F19B *)this)->Rva0021F19B::Rva0021F19B(); }
	~Rva0021F5F8FileList() { ((Rva0021DB35 *)this)->~Rva0021DB35(); }
	HeroFileEntry *m_begin;
	HeroFileEntry *m_end;
	HeroFileEntry *m_capacity;
};

class BFME2WideConcatPair
{
public:
	__forceinline BFME2WideConcatPair(const UnicodeString &left, const UnicodeString &right) : m_left(&left), m_right(&right) {}
	operator UnicodeString();						// 0x0021C3F7 (pinned UnicodeString spelling)
	const UnicodeString *m_left;
	const UnicodeString *m_right;
};
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringW(const unsigned short *text);

class CreateAHeroManager
{
public:
	void rva0021F5F8();
	unsigned char m_pad000[0x174];
	Rva0040A3F9 m_heroes;			// +0x174
};

void CreateAHeroManager::rva0021F5F8()
{
	Rva0021F5F8FileList files;
	for (HeroFileEntry *it = files.m_begin; it != files.m_end; ++it)
	{
		AsciiString name = Rva0021C12FStripName(it->first);
		if (!m_heroes.rva0040A5CF(name))
		{
			UnicodeString message((const UnicodeString &)(UnicodeString)BFME2WideConcatPair(
				((const Rva002DC267 *)TheGameState)->rva002DC267(), UnicodeString(it->first)));
			OutputDebugStringW(message.str());
		}
	}
	unsigned int count = m_heroes.m_end - m_heroes.m_begin;
	for (unsigned int i = 0; i < count; ++i)
	{
		Rva0021F5F8Hero *hero = (Rva0021F5F8Hero *)m_heroes.rva0040A32F(i);
		if (hero && (!hero->m_system || g_rva005B5C02Flag) && !hero->m_name.isEmpty())
		{
			AsciiString file = Rva0021A651Filename(hero->m_name);
			((CreateAHeroHero *)hero)->rva004098BE(file, hero->m_system || g_rva005B5C02Flag);
		}
	}
}
