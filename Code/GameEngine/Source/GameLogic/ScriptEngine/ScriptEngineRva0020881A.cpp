// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// Native ScriptEngine lookup family: 20874B/207B, 20881A/134B, 2088A0/200B.
// The resolved/original string key and map offsets 190A0/190AC come from
// these complete bodies; parent DoXfer supplies the stored-value accesses.
// Counter field names are carried from the existing ScriptEngine home.
// In particular, the second timer flag's name is a reference lead; the
// target proves its byte initialization, not that name.
#include "ascii_string.h"
#include <map>

// Compare this TU's iterators directly; the generic iterator-base member has
// a different out-of-line copy in the current link order.
namespace _STL {
template<class T,class L,class R>
static inline bool operator!=(const _Rb_tree_iterator<T,L>& a,const _Rb_tree_iterator<T,R>& b) {
 return a._M_node!=b._M_node;
}
}
struct ScriptCounter
{
	int m_value;
	bool m_isCountdownTimer;
	bool m_isMillisecondTimer;
 ScriptCounter() : m_value(0), m_isCountdownTimer(false), m_isMillisecondTimer(false) {}
};

typedef _STL::pair<AsciiString,AsciiString> ScriptKey;
class Rva002046C0Owner { public: AsciiString resolveName(const AsciiString &); };
typedef _STL::_Rb_tree<ScriptKey,_STL::pair<const ScriptKey,ScriptCounter>,
 _STL::_Select1st<_STL::pair<const ScriptKey,ScriptCounter> >,_STL::less<ScriptKey>,
 _STL::allocator<_STL::pair<const ScriptKey,ScriptCounter> > > ScriptCounterTree;
typedef _STL::_Rb_tree<ScriptKey,_STL::pair<const ScriptKey,bool>,
 _STL::_Select1st<_STL::pair<const ScriptKey,bool> >,_STL::less<ScriptKey>,
 _STL::allocator<_STL::pair<const ScriptKey,bool> > > ScriptFlagTree;

// The retail trees use the existing byte allocator and omit the throwing
// allocator cleanup wrapper. Node sizes are 0x20 and 0x1C, respectively.
// ?_M_create_node@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UScriptCounter@@@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UScriptCounter@@@_STL@@@2@U?$less@U?$pair@VAsciiString@@V1@@_STL@@@2@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UScriptCounter@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UScriptCounter@@@_STL@@@2@ABU?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UScriptCounter@@@2@@Z
template <>
ScriptCounterTree::_Link_type ScriptCounterTree::_M_create_node(const ScriptCounterTree::value_type &value) {
 _Link_type node=(_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<ScriptCounterTree::value_type>),0);
 _STL::_Construct(&node->_M_value_field,value);
 return node;
}
// ?_M_create_node@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@_STL@@@2@U?$less@U?$pair@VAsciiString@@V1@@_STL@@@2@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@_STL@@@2@ABU?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@2@@Z
template <>
ScriptFlagTree::_Link_type ScriptFlagTree::_M_create_node(const ScriptFlagTree::value_type &value) {
 _Link_type node=(_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<ScriptFlagTree::value_type>),0);
 _STL::_Construct(&node->_M_value_field,value);
 return node;
}

class ScriptEngine {
public:
 void *rva0020881A(AsciiString name);
protected:
 ScriptCounter *bfmeCounter(AsciiString name);
 bool *bfmeFlagForWrite(AsciiString name);
private:
 char m_unreconstructed[0x190A0];
 _STL::map<ScriptKey,ScriptCounter> m_counters;
 _STL::map<ScriptKey,bool> m_flags;
};
// Retail's complete 207B and 200B lookup-and-insert bodies. The key is the
// resolved script name followed by the original name; the values are the
// target's integer/two-byte counter and Boolean flag, respectively.
ScriptCounter *ScriptEngine::bfmeCounter(AsciiString name) {
 AsciiString resolved = ((Rva002046C0Owner *)this)->resolveName(name);
 ScriptKey key(resolved,name);
 _STL::pair<_STL::map<ScriptKey,ScriptCounter>::iterator,bool> result =
  m_counters.insert(_STL::make_pair(key,ScriptCounter()));
 return &result.first->second;
}

bool *ScriptEngine::bfmeFlagForWrite(AsciiString name) {
 AsciiString resolved = ((Rva002046C0Owner *)this)->resolveName(name);
 ScriptKey key(resolved,name);
 _STL::pair<_STL::map<ScriptKey,bool>::iterator,bool> result =
  m_flags.insert(_STL::make_pair(key,false));
 return &result.first->second;
}


void *ScriptEngine::rva0020881A(AsciiString name) {
 AsciiString resolved = ((Rva002046C0Owner *)this)->resolveName(name);
 ScriptKey key(resolved,name);
 _STL::map<ScriptKey,bool>::iterator found=m_flags.find(key);
 if(found!=m_flags.end()) return &found->second;
 return 0;
}
