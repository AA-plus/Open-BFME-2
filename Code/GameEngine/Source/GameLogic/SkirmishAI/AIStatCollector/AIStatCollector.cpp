// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// AIStatCollector is established by the
// Register/UnRegister sibling owner and the SkirmishAIManager allocation.
// Native 4E030B..4E0425 proves the offsets and allocation sizes below.
// The hash table stores four-byte counts (Register increments node+8),
// while listener pointees remain opaque. The existing const ModuleData*
// container spelling binds the proven49B push_back provider; it does not
// establish the original receiver class. Target Register proves a vptr at0
// and callback-selection flags at8; WB Register/addInfoReceiver establish
// method identities independently of those storage and receiver observations.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <hash_map>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}
#include <vector>

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

#include <cstddef>

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}
class Player;
class Object;
class ModuleData;
class Rva004DF98BReceiver { public: virtual void v0(void *,int); virtual void v1(void *); int m_pad; int m_flags; };
namespace _STL { template <> void vector<const ModuleData *>::push_back(const ModuleData *const &); }
class Rva005961D6 { public: Rva005961D6(); private: char bytes[0xa4]; };
class Rva00596069 { public: Rva00596069(); private: char bytes[0x10]; };
class Rva005965A5 { public: Rva005965A5(); private: char bytes[0x1c]; };
class AIEconomyStats { public: AIEconomyStats(int); private: char bytes[0x1c]; };
class Rva00283081 { public: Rva00283081(float,int) throw(); private: char bytes[0x24]; };
class Rva002A8F24;
extern Rva002A8F24 *g_00DFEEF8;
struct CollectorManagerView { char prefix[0x878]; float interval; };
void *Rva004DF983Field(void *);
class AIStatCollector {
public: AIStatCollector(Player *);
 void Register(Object *,int);
 void addInfoReceiver(const ModuleData *);
private:
 Rva005961D6 *units;
 Rva00596069 *otherUnits;
 Rva005965A5 *structures;
 AIEconomyStats *resources;
 Rva00283081 *positions;
 _STL::hash_map<int,int> counts;
 Player *player;
 _STL::vector<const ModuleData *> listeners;
};
typedef char AIStatCollectorNativeSize[(sizeof(AIStatCollector)==0x38)?1:-1];
// The target has no operator-delete rollback state for this last helper's
// construction. Its throw() declaration preserves that native EH behavior;
// the existing helper provider keeps the same binary constructor ABI.
AIStatCollector::AIStatCollector(Player *owner)
 :units(0),otherUnits(0),structures(0),resources(0),player(owner)
{
 units=new Rva005961D6;
 otherUnits=new Rva00596069;
 structures=new Rva005965A5;
 resources=new AIEconomyStats(reinterpret_cast<int>(player));
 positions=new Rva00283081(reinterpret_cast<CollectorManagerView *>(g_00DFEEF8)->interval,
                          reinterpret_cast<int>(&Rva004DF983Field));
}

// Independently recovered native cdecl callback at4DF983..4DF98B.
void *Rva004DF983Field(void *owner) { return static_cast<char *>(owner)+0x38; }

void AIStatCollector::Register(Object *a,int mask) {
 const ModuleData **beg= listeners.begin(); const ModuleData **end=listeners.end();
 for (;beg!=end;++beg) { Rva004DF98BReceiver *e=(Rva004DF98BReceiver *)*beg; if(e->m_flags & mask) e->v0(a,mask); }
}

// WB addInfoReceiver at129B9C0; native appends one pointer at vector2C.
void AIStatCollector::addInfoReceiver(const ModuleData *receiver)
{
 listeners.push_back(receiver);
}
