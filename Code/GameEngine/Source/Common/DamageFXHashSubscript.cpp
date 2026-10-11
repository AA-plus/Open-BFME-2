// stlport
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// STLport hash_map::operator[] applied to the native DamageFX table.
// Retail 360A92..360AF3: 0x780-byte mapped object, ctor3608C9,
// 480-dword pair copy, find148B27 and insert3609F7. The existing
// address-derived template views are opaque interfaces to folded helpers;
// the native node stores the full 0x784-byte pair, not their small placeholders.
#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
}

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
// Suppress the TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}
class INI;
class DamageFX { public:
 class DFX { public: DFX(); char bytes[0x10]; };
 static void parseAmount(INI*,void*,void*,const void*);
 static void parseMajorFXList(INI*,void*,void*,const void*);
 static void parseMinorFXList(INI*,void*,void*,const void*);
 static void parseTime(INI*,void*,void*,const void*);
};
class Rva003608C9 { public: Rva003608C9(); DamageFX::DFX values[0x78]; };
struct Rva00148B27Element { char bytes[8]; };
struct Rva003609F7Element { char bytes[1]; };
typedef _STL::hashtable<_STL::pair<const int,Rva00148B27Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<const int,Rva00148B27Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<const int,Rva00148B27Element> > > FindTable;
typedef _STL::hashtable<_STL::pair<const int,Rva003609F7Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<const int,Rva003609F7Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<const int,Rva003609F7Element> > > InsertTable;
class Rva00360A92 { public: Rva003608C9 &rva00360A92(const int &key); };
Rva003608C9 &Rva00360A92::rva00360A92(const int &key)
{
    FindTable::iterator it = ((FindTable*)this)->find(key);
    if (it._M_cur == 0) {
        _STL::pair<const int,Rva003608C9> pair(key,Rva003608C9());
        _STL::pair<const int,Rva003609F7Element> &inserted = ((InsertTable*)this)->_M_insert(*(const _STL::pair<const int,Rva003609F7Element>*)&pair);
        return *(Rva003608C9*)((char*)&inserted+4);
    }
    return *(Rva003608C9*)((char*)it._M_cur+8);
}

struct FieldParse { const char *token; void (*parse)(INI*,void*,void*,const void*); const void *data; unsigned offset; };
extern const char *TheVeterancyNames[];
static const FieldParse DamageFXFields[] = {
 {"AmountForMajorFX",DamageFX::parseAmount,0,0},
 {"MajorFX",DamageFX::parseMajorFXList,0,0},
 {"MinorFX",DamageFX::parseMinorFXList,0,0},
 {"ThrottleTime",DamageFX::parseTime,0,0},
 {"VeterancyAmountForMajorFX",DamageFX::parseAmount,TheVeterancyNames,0},
 {"VeterancyMajorFX",DamageFX::parseMajorFXList,TheVeterancyNames,0},
 {"VeterancyMinorFX",DamageFX::parseMinorFXList,TheVeterancyNames,0},
 {"VeterancyThrottleTime",DamageFX::parseTime,TheVeterancyNames,0},
 {0,0,0,0}
};
enum NameKeyType { NAMEKEY_INVALID=0, FORCE_NAMEKEY_LONG=0x7fffffff };
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator *TheNameKeyGenerator;
class INI { public: const char *getNextToken(const char*); void initFromINI(void*,const FieldParse*); };
class Rva003605AF { public: void rva003605AF(); };
class DamageFXStore { public: static void parseDamageFXDefinition(INI*); char base[0xC]; Rva00360A92 map; };
extern DamageFXStore *TheDamageFXStore;
// ZH DamageFXStore::parseDamageFXDefinition, reconciled to native 30x4 DFX.
// Native registration token DamageFX -> 360B0F, with TheDamageFXStore global
// and the exact nine-entry field table at VA C168F8 independently decoded.
void DamageFXStore::parseDamageFXDefinition(INI *ini)
{
 int key = TheNameKeyGenerator->nameToKey(ini->getNextToken(0));
 Rva003608C9 &dfx = TheDamageFXStore->map.rva00360A92(key);
 ((Rva003605AF*)&dfx)->rva003605AF();
 ini->initFromINI(&dfx,DamageFXFields);
}
