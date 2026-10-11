// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva003A23A5@Team@@QAEXH_N@Z @0x003A23A5 203B.
// Identity: WorldBuilder Team.cpp twin 0x00EFC000 (unnamed, call graph);
// Team::~Team (0x003A354F) drains the +0x130 set through it with false and
// ScriptActions::rva003C207C hands it a unit's ObjectID and its bool
// argument (both WB twins read the flag as a byte).
// Target facts: the ObjectID set<int> at +0x130 is looked up through the
// pinned folded _M_find 0x00388F63; nothing happens when membership already
// equals the flag; otherwise the ID is inserted (rowed set<int>::insert
// 0x000BC15D) or the found node erased (folded tree erase 0x005530A8), then
// the object is fetched through TheGameLogic->findObjectByID and, when it
// carries a GateOpenAndCloseBehavior (function-static name key, findModule
// 0x0028B6D6, module interface at +4), its want-open count moves by +1/-1
// (rowed changeWantOpenCount 0x00498831). The name is address-derived.
#include <set>
#include "ascii_string.h"
#include "../GameLogicObjectLookupView.h"

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
typedef _Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> > Lk11RbIntSet;
template <> pair<Lk11RbIntSet::iterator, bool> Lk11RbIntSet::insert_unique(const int &);
}
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
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

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

enum NameKeyType {};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Module;

class Object
{
	friend class Team;
protected:
	Module *findModule(NameKeyType key) const;
};

extern GameLogic *TheGameLogic;

class GateOpenAndCloseBehavior
{
public:
	void changeWantOpenCount(int delta);
};

class Team
{
public:
	void rva003A23A5(int id, bool add);
private:
	char m_00[0x130];
	_STL::set<int> m_130;			// +0x130
};

void Team::rva003A23A5(int id, bool add)
{
	_STL::set<int>::iterator it = m_130.find(id);
	if (add == (it != m_130.end()))
		return;

	if (add)
		m_130.insert(id);
	else
		m_130.erase(it);

	Object *obj = TheGameLogic->findObjectByID((ObjectID)id);
	if (!obj)
		return;

	static NameKeyType key = TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
	Module *module = obj->findModule(key);
	GateOpenAndCloseBehavior *gate = module ? (GateOpenAndCloseBehavior *)((char *)module - 4) : 0;
	if (gate)
		gate->changeWantOpenCount(add ? 1 : -1);
}
