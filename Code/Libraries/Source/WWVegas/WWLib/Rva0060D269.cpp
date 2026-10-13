// cl: /O1 /G6 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_CSTD_FUNCTION_IMPORTS
// stlport
//
// ?rva0060D269@Rva0060D269@@QAEAAIABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z @ 0x0060D269, 128 bytes.
// Dedicated TU: the XferSave owner TU carries /MD rows and a different
// class view; the R1 member-visibility lever needs the visible
// __declspec(noinline) Rva0060CAEA::rva0060CB61 definition here (the
// rowed 0x60CB61 body in stlport_string_find_0060CAEA.cpp is identical).
namespace _STL { void __cdecl free(void *); }
#include <string>
#include <vector>
#include <hash_map>
class ModuleData;
namespace _STL { template<> void vector<const ModuleData *>::push_back(const ModuleData *const&); }
class XferException {
public: XferException(int,const char*,...); XferException(const XferException&); ~XferException();
 void *text; int tag;
};
class BfmeByteStream {
public: virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual int write(const void*,int); virtual int skip(int,int);
};
struct Rva0060CAEANode { void *next; _STL::string key; unsigned int value; };
struct Rva0060CAEAIterator { Rva0060CAEANode *cur; const void *table;
 Rva0060CAEAIterator(Rva0060CAEANode*c,const void*t):cur(c),table(t){} };
class Rva0060CAEA { public: Rva0060CAEAIterator rva0060CB61(const _STL::string&); Rva0060CAEANode *rva0060CAEA(const _STL::string&)const throw(); };
class Rva0060D269 { public: unsigned int &rva0060D269(const _STL::string&); };
class XferSave {
public:
 virtual ~XferSave();
 void rva0060D2E9(const char*);
 int rva0060D435(const char*);
private:
 BfmeByteStream *volatile stream;
 bool flag; char pad9[3];
 void *positions[3];
 char names[20]; char secondNames[16];
 unsigned int previousNames;
};
typedef _STL::pair<const _STL::string,unsigned int> XferNamePair;
typedef _STL::hashtable<XferNamePair,_STL::string,_STL::hash<_STL::string>,
 _STL::_Select1st<XferNamePair>,_STL::equal_to<_STL::string>,_STL::allocator<XferNamePair> > XferNameTable;
namespace _STL { template<> XferNamePair &XferNameTable::_M_insert(const XferNamePair&); }
unsigned int &Rva0060D269::rva0060D269(const _STL::string &key) {
 Rva0060CAEANode *node;
 { Rva0060CAEAIterator it=((Rva0060CAEA*)this)->rva0060CB61(key); node=it.cur; }
 return !node ? ((XferNameTable*)this)->_M_insert(XferNamePair(key,0)).second : node->value;
}

// Actual rowed member ?rva0060CB61@Rva0060CAEA@@QAE?AURva0060CAEAIterator@@ABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z at 0x0060CB61 from Code/Libraries/Source/WWVegas/WWLib/stlport_string_find_0060CAEA.cpp.
inline __declspec(noinline) Rva0060CAEAIterator Rva0060CAEA::rva0060CB61(const _STL::string &key)
{
	return Rva0060CAEAIterator(rva0060CAEA(key), this);
}
