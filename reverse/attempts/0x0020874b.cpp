// ?rva0020874B@ScriptEngine@@QAEPAXVAsciiString@@@Z
// partial score=0.99 date=2026-10-11
// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
#include "ascii_string.h"
#include <map>
// Target initializes an integer and two bytes; the second field name is
// carried from the existing home/reference, not proved by parent DoXfer.
struct ScriptCounter {
 int m_value;
 bool m_isCountdownTimer;
 bool m_isMillisecondTimer;
 ScriptCounter() : m_value(0),m_isCountdownTimer(false),m_isMillisecondTimer(false) {}
};
class Rva002046C0Owner { public: AsciiString resolveName(const AsciiString &); };
typedef _STL::pair<AsciiString,AsciiString> ScriptKey;
class ScriptEngine : public Rva002046C0Owner {
public: void *rva0020874B(AsciiString name);
private: char pad[0x190A0]; _STL::map<ScriptKey,ScriptCounter> m_counters;
};
void *ScriptEngine::rva0020874B(AsciiString name) {
 AsciiString resolved = resolveName(name);
 ScriptKey key(resolved,name);
 _STL::pair<_STL::map<ScriptKey,ScriptCounter>::iterator,bool> result = m_counters.insert(_STL::make_pair(key,ScriptCounter()));
 return &result.first->second;
}
