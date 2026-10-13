// ?rva00425842@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.8 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/ini
// "FormationTemplate" INI block parser (retail 0x00425842, 818 B) and the
// 16-byte template constructor it calls (retail 0x004257AD, 84 B).
// Target evidence: GapBodiesS3E's block table pairs "FormationTemplate" with
// 0x00425842; the literals name the block and its "Rows" field (parsed by the
// rowed 0x00425421 into the three-level deque the rowed 0x00425806 builds at
// +0x08 and the rowed 0x00425756 destroys). Each parsed cell key is looked up
// in the int map at 0x00E03168; the template gets a per-row list of cell lists
// (+0x00, 12-byte elements) and a de-duplicated per-row list (+0x0C), and is
// appended to the pointer deque at 0x00E03174 whose index the int map at
// 0x00E0319C records under the template key (FormationSelectionCriteria
// 0x00424185 reads it back). Original class and member names are unknown:
// LightPoint/LightSubPoint/CameraMarker are the ledger's existing spellings
// for this object (rowed dtors 0x004247E3 and LightPointDtor.cpp), the STL
// views use the ledger's folded callee spellings, and no container code is
// instantiated here.
#include "ascii_string.h"
#include "Common/INIException.h"

class INI;
typedef void (*Parser)(INI *, void *, void *, const void *);
struct FieldParse
{
	const char *token;
	Parser parse;
	const void *userData;
	int offset;
};
class INI
{
public:
	AsciiString getNextQuotedAsciiString();
	AsciiString getFilename() const;
	int getLineNum() const;
	void initFromINI(void *what, const FieldParse *table);
};
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;
void Rva00425421Parse(INI *ini, void *what);
void rva00425842(INI *ini, void *instance, void *store, const void *userData);

class ModuleData;
struct BfmeOpaque40;
struct Rva001408C0Target;
struct BfmeWordValue4
{
	int m_key;
};

namespace _STL {
template <class T> class allocator
{
public:
	allocator() {}
};
template <class A, class B> struct pair
{
	pair();
	A first;
	B second;
};
template <class P> struct _Select1st
{
};
template <class T> struct less
{
};
template <class T> struct _Const_traits
{
};
template <class T> struct _Nonconst_traits
{
};
template <class V> struct _Rb_tree_node
{
	int _M_color;
	void *_M_parent;
	void *_M_left;
	void *_M_right;
	V _M_value_field;
};
template <class V, class Tr> struct _Rb_tree_iterator
{
	_Rb_tree_iterator();
	void *_M_node;
};
template <class K, class V, class KoV, class C, class A> class _Rb_tree
{
	friend void ::rva00425842(INI *, void *, void *, const void *);
	template <class KT> _Rb_tree_node<V> *_M_find(const KT &key) const;
	_Rb_tree_node<V> *_M_header;
	unsigned _M_node_count;
	C _M_key_compare;
};
template <class K, class T, class C = less<K>, class A = allocator<pair<const K, T> > > class map
{
public:
	T &operator[](const K &key);
	_Rb_tree<K, pair<const K, T>, _Select1st<pair<const K, T> >, C, A> _M_t;
};
// The tree member spells the rowed unsigned-key find 0x00357180 this set's
// lookups fold to.
template <class K, class C = less<K>, class A = allocator<K> > class set
{
public:
	set();
	pair<_Rb_tree_iterator<K, _Const_traits<K> >, bool> insert(const K &value);
	_Rb_tree<unsigned, pair<const unsigned, void *>, _Select1st<pair<const unsigned, void *> >,
		less<unsigned>, allocator<pair<const unsigned, void *> > > _M_t;
};
template <class T, class A = allocator<T> > class vector
{
public:
	vector(unsigned count, const T &value, const A &alloc = A());
	~vector();
	void push_back(const T &value);
	T &operator[](unsigned n) { return _M_start[n]; }
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
template <class T> struct _Deque_iterator_base
{
	void _M_increment();
	int _M_subtract(const _Deque_iterator_base &other) const;
	T *_M_cur;
	T *_M_first;
	T *_M_last;
	T **_M_node;
};
template <class T, class Tr> struct _Deque_iterator : _Deque_iterator_base<T>
{
	T &operator*() const { return *this->_M_cur; }
	T &operator[](int n) const;
	_Deque_iterator &operator++() { this->_M_increment(); return *this; }
	bool operator!=(const _Deque_iterator &other) const { return this->_M_cur != other._M_cur; }
};
template <class T, class A = allocator<T> > class deque
{
public:
	typedef _Deque_iterator<T, _Nonconst_traits<T> > iterator;
	iterator begin() { return _M_start; }
	iterator end() { return _M_finish; }
	T &front() { return *_M_start; }
	T &operator[](int n) { return _M_start[n]; }
	int size() const { return _M_finish._M_subtract(_M_start); }
	void push_back(const T &value);
	iterator _M_start;
	iterator _M_finish;
	T **_M_map;
	unsigned _M_map_size;
};
}

// Rows and cells are 40-byte deques; the rowed iterator helpers spell their
// elements with the neutral BfmeOpaque40.
struct BfmeOpaque40 : _STL::deque<BfmeOpaque40>
{
};
typedef _STL::deque<BfmeWordValue4> CellKeys;
namespace _STL {
template <> class deque<deque<CellKeys> > : public deque<BfmeOpaque40>
{
public:
	~deque();
};
}

class Rva00425806
{
public:
	Rva00425806();
	int m_key;
	int m_04;
	_STL::deque<_STL::deque<CellKeys> > m_rows;
};

class Rva00421CE9 : public _STL::set<Rva001408C0Target *>
{
public:
	~Rva00421CE9();
};

typedef _STL::vector<const ModuleData *> UnitList;
struct CameraMarker
{
	_STL::vector<UnitList> m_cells;
	UnitList m_units;
};
struct LightSubPoint : CameraMarker
{
	LightSubPoint(unsigned columns);
	~LightSubPoint();
};
class LightPoint
{
public:
	LightPoint(int key, int rows, int columns) : m_points(rows, LightSubPoint(columns))
	{
		m_key = key;
	}
	_STL::vector<CameraMarker> m_points;
	int m_key;
};

typedef _STL::map<int, int> IntMap;
typedef _STL::_Rb_tree_node<_STL::pair<const int, int> > IntMapNode;
extern unsigned int g_Va00E03168;
extern unsigned int g_Va00E03174;
extern unsigned int g_Va00E0319C[3];
#define unitTypes (*reinterpret_cast<IntMap *>(&g_Va00E03168))
#define formationTemplates (*reinterpret_cast<_STL::deque<void *> *>(&g_Va00E03174))
#define formationIndices (*reinterpret_cast<IntMap *>(g_Va00E0319C))

void rva00425842(INI *ini, void *, void *, const void *)
{
	Rva00425806 data;
	AsciiString name = ini->getNextQuotedAsciiString();
	if (name.isEmpty())
		throw INIException(3, "Formation Template must have name at %s:%d", ini->getFilename().str(), ini->getLineNum());
	data.m_key = TheNameKeyGenerator->nameToKey(name);
	if (formationIndices._M_t._M_find(data.m_key) != formationIndices._M_t._M_header)
		throw INIException(3, "Formation Template name must be unique %s:%d", ini->getFilename().str(), ini->getLineNum());
	FieldParse fields[] = {
		{ "Rows", (Parser)Rva00425421Parse, 0, 0 },
		{ 0, 0, 0, 0 }
	};
	ini->initFromINI(&data, fields);
	int rows = data.m_rows.size();
	int columns = data.m_rows.front().size();
	LightPoint *formation = new LightPoint(data.m_key, rows, columns);
	_STL::vector<CameraMarker> &points = formation->m_points;
	Rva00421CE9 seen;
	for (int row = rows - 1; row >= 0; --row)
	{
		for (int column = 0; column < columns; ++column)
		{
			CellKeys &cell = reinterpret_cast<CellKeys &>(data.m_rows[row][column]);
			for (CellKeys::iterator it = cell.begin(); it != cell.end(); ++it)
			{
				const int &key = (*it).m_key;
				IntMapNode *unit = unitTypes._M_t._M_find(key);
				if (unit == unitTypes._M_t._M_header)
					throw INIException(3, "Invalid unit type '%s' at %s:%d",
						TheNameKeyGenerator->keyToName((NameKeyType)key).str(),
						ini->getFilename().str(), ini->getLineNum());
				int &value = unit->_M_value_field.second;
				points[row].m_cells[column].push_back(reinterpret_cast<const ModuleData *>(&value));
				if (seen._M_t._M_find(reinterpret_cast<const unsigned &>(value)) == seen._M_t._M_header)
				{
					seen.insert(reinterpret_cast<Rva001408C0Target *const &>(value));
					points[row].m_units.push_back(reinterpret_cast<const ModuleData *>(value));
				}
			}
		}
	}
	formationTemplates.push_back(reinterpret_cast<void *&>(formation));
	formationIndices[data.m_key] = formationTemplates.size() - 1;
}
