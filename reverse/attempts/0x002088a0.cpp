// ?rva002088A0@ScriptEngine@@QAEPAXVAsciiString@@@Z
// partial score=0.99 date=2026-10-11
// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
#include "ascii_string.h"
#include <map>
struct ScriptCounter {
 int m_value;
 bool m_isCountdownTimer;
 bool m_isMillisecondTimer;
 ScriptCounter() : m_value(0),m_isCountdownTimer(false),m_isMillisecondTimer(false) {}
};
class Rva002046C0Owner { public: AsciiString resolveName(const AsciiString &); };
typedef _STL::pair<AsciiString,AsciiString> ScriptKey;
class ScriptEngine : public Rva002046C0Owner {
public: void *rva002088A0(AsciiString name);
private: char pad[0x190AC]; _STL::map<ScriptKey,bool> m_flags;
};
void *ScriptEngine::rva002088A0(AsciiString name) {
 AsciiString resolved = resolveName(name);
 ScriptKey key(resolved,name);
 _STL::pair<_STL::map<ScriptKey,bool>::iterator,bool> result = m_flags.insert(_STL::make_pair(key,false));
 return &result.first->second;
}
