// ?rva0035818E@ScriptEngine@@QAEXABVAsciiString@@PAUCoord3D@@@Z
// partial score=0.9679368809803592 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /I. /Ireference/shims/bfmelist /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /MD /EHsc
// stlport
#include "ascii_string.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include <list>
unsigned long Rva003ECA13Get(const AsciiString &);
struct ScriptPositionRecord {
 ScriptPositionRecord();
 unsigned long key;
 Coord3D position;
};
struct BfmeFloat4Record00469C61 { unsigned char bytes[16]; };
class Rva00357E14 { public: void rva00357E14(const BfmeFloat4Record00469C61 &); };
typedef _STL::list<ScriptPositionRecord> ScriptPositionList;
namespace _STL {
template<> list<ScriptPositionRecord>::iterator list<ScriptPositionRecord>::erase(iterator);
}
class ScriptEngine {
public:
 void rva0035818E(const AsciiString &,Coord3D *);
 char pad[0x1a498];
 ScriptPositionList positions;
};
void ScriptEngine::rva0035818E(const AsciiString &name,Coord3D *position)
{
 if(name.isEmpty())return;
 unsigned long key=Rva003ECA13Get(name);
 for(ScriptPositionList::iterator it=positions.begin();it!=positions.end();++it){
  if(it->key==key){
   if(position)it->position=*position;
   else positions.erase(it);
   return;
  }
 }
 ScriptPositionRecord record;
 record.key=key;
 record.position=*position;
 ((Rva00357E14 *)&positions)->rva00357E14((const BfmeFloat4Record00469C61 &)record);
}

/* Separate translation-unit trial for the two unbound providers.
This is evidence only: constructor and erase must remain opaque to the parent.
// cl: /O1 /G7 /arch:SSE /I. /Ireference/shims/bfmelist /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /MD /EHsc
// stlport
#include "ascii_string.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include <list>
unsigned long Rva003ECA13Get(const AsciiString &);
struct ScriptPositionRecord {
 ScriptPositionRecord();
 unsigned long key;
 Coord3D position;
};
struct BfmeFloat4Record00469C61 { unsigned char bytes[16]; };
class Rva00357E14 { public: void rva00357E14(const BfmeFloat4Record00469C61 &); };
typedef _STL::list<ScriptPositionRecord> ScriptPositionList;
namespace _STL {
template<> list<ScriptPositionRecord>::iterator list<ScriptPositionRecord>::erase(iterator);
}
ScriptPositionRecord::ScriptPositionRecord():key(0){}
namespace _STL {
template<> __declspec(noinline) list<ScriptPositionRecord>::iterator list<ScriptPositionRecord>::erase(iterator pos){
 _List_node_base *next=pos._M_node->_M_next;
 _List_node_base *prev=pos._M_node->_M_prev;
 _Node *node=(_Node *)pos._M_node;
 prev->_M_next=next;next->_M_prev=prev;
 _Destroy(&node->_M_data);
 this->_M_node.deallocate(node,1);
 return iterator((_Node *)next);
}
}

ScriptPositionList::iterator callPositionErase(ScriptPositionList *list, ScriptPositionList::iterator it) { return list->erase(it); }

*/
