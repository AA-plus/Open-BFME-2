// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ??1Rva001D92C0@@UAE@XZ, retail 0x001D92C0..0x001D93B2 (242 bytes, EH):
// the destructor of the armor template store whose scalar deleting
// destructor is 0x001D93B2 (vtable 0x00BD9CB0; its slot 4 is the "RIF:
// Armor reloaded" notice 0x001D8FAD). It deletes the ArmorTemplate held by
// every entry of its NameKeyType hash map at +0x0C and clears the map, then
// deletes every template of its pointer vector at +0x20 by index and empties
// it; then the +0x2C and +0x20 vectors' storage goes to GameFree, the map dies
// (inline destructor running the hashtable destructor 0x001D904A; its
// out-of-line copy for the unwind map is the 5-byte thunk 0x001D92BB) and
// SubsystemInterface last. The walk binds retail's shared hashtable begin
// 0x00427195 and prefix ++ 0x0041E832 through the GameWindow-keyed spelling
// those rows use. The second vector's role is not established.
#include <hash_map>
#include <vector>
#include "ascii_string.h"

void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template<> inline _Vector_base<void *, allocator<void *> >::~_Vector_base() { if (_M_start) Rva00030830GameFree(_M_start); }
template<> vector<void *>::iterator vector<void *>::erase(iterator first, iterator last);
}

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

namespace rts
{
template <typename T> struct hash
{
	size_t operator()(const T &value) const { return (size_t)value; }
};
}

class ArmorTemplate
{
private:
	float m_head;				// +0x00
	float m_damageCoefficient[27];		// +0x04
	float m_damageScalar;			// +0x70
	int m_flag;				// +0x74
	AsciiString m_name;			// +0x78
};

typedef _STL::pair<const NameKeyType, ArmorTemplate> ArmorTemplatePair;
typedef _STL::hashtable<ArmorTemplatePair, NameKeyType, rts::hash<NameKeyType>, _STL::_Select1st<ArmorTemplatePair>, _STL::equal_to<NameKeyType>, _STL::allocator<ArmorTemplatePair> > ArmorTemplateTable;
namespace _STL {
template <> void ArmorTemplateTable::clear();
}

// Native 0x001D904A..0x001D9083 clears the table, then frees bucket storage
// at +4 through the member vector's lifetime. The other table words remain
// opaque. Its parent calls this complete destructor out of line.
class Rva001D904A
{
public:
	__declspec(noinline) ~Rva001D904A();
	ArmorTemplateTable &table() { return *reinterpret_cast<ArmorTemplateTable *>(this); }
private:
	unsigned char m_unknown00[4];
	_STL::vector<void *> m_buckets;
	unsigned int m_unknown10;
};

Rva001D904A::~Rva001D904A()
{
	table().clear();
}

class GameWindow; class WindowVideo;
class WindowVideoManager { public: struct hashConstGameWindowPtr { size_t operator()(const GameWindow *) const; }; };
typedef _STL::pair<const GameWindow * const, WindowVideo *> Rva00206DA4Pair;
typedef _STL::hashtable<Rva00206DA4Pair, const GameWindow *, WindowVideoManager::hashConstGameWindowPtr, _STL::_Select1st<Rva00206DA4Pair>, _STL::equal_to<const GameWindow *>, _STL::allocator<Rva00206DA4Pair> > Rva00206DA4Table;
namespace _STL {
template <> Rva00206DA4Table::iterator Rva00206DA4Table::begin();
template <> Rva00206DA4Table::iterator &Rva00206DA4Table::iterator::operator++();
}

struct Rva001D92BB
{
	~Rva001D92BB() {}
	Rva001D904A m_table;
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	int m_04;
	int m_08;
};

class Rva001D92C0 : public SubsystemInterface
{
public:
	virtual ~Rva001D92C0();
private:
	Rva001D92BB m_templates;		// +0x0C
	_STL::vector<void *> m_list;		// +0x20
	_STL::vector<void *> m_2C;		// +0x2C
};

Rva001D92C0::~Rva001D92C0()
{
	{
		Rva00206DA4Table *table = reinterpret_cast<Rva00206DA4Table *>(&m_templates.m_table);
		for (Rva00206DA4Table::iterator it = table->begin(); it._M_cur; ++it)
			delete reinterpret_cast<ArmorTemplate *>(it._M_cur->_M_val.second);
	}
	m_templates.m_table.table().clear();
	{
		for (unsigned int i = 0; i < m_list.size(); ++i)
			delete static_cast<ArmorTemplate *>(m_list[i]);
	}
	m_list.clear();
}
