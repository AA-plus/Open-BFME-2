// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD
// Retail 0x003A0D0A 88B, WB twin EF2670 (identity remains address-derived).
// Target facts: owner +08, unit record array +130 with stride18, second name
// +10 in each record, count +1D8; existing TeamTemplateInfo ctor independently
// establishes seven records and that count. Empty object is the exported
// AsciiString::TheEmptyString at RVA9E0878. Registry and +38 append calls use
// their owned opaque providers; their higher-level purpose is not asserted.
#include "ascii_string.h"
class Player;
class Rva004EC05A { public: void rva004EC05A(void *); };
struct Rva002A8AB1Record;
class Rva002A8F24 { public: Rva002A8AB1Record *rva002A8AB1(void *); };
extern Rva002A8F24 *g_00DFEEF8;
struct UnitInfo { int m_00,m_04,m_08; AsciiString m_0c,m_name10; int m_14; };
class TeamPrototype { public: void __declspec(noinline) rva003A0D0A(); private:
 char pad0[8]; Player *owner; char padc[0x130-12]; UnitInfo units[7]; int count;
};
void TeamPrototype::rva003A0D0A()
{
 if(owner) {
  Rva002A8AB1Record *record=g_00DFEEF8->rva002A8AB1(owner);
  if(record) {
   for(int i=0;i<count;++i) {
    if(units[i].m_name10.compare(AsciiString::TheEmptyString)!=0)
     ((Rva004EC05A *)record)->rva004EC05A(&units[i].m_name10);
   }
  }
 }
}

namespace _STL {
struct _Rb_tree_node_base {
 int _M_color;
 _Rb_tree_node_base *_M_parent;
 _Rb_tree_node_base *_M_left;
 _Rb_tree_node_base *_M_right;
};
template <class _Dummy> class _Rb_global {
public:
 static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}
struct TeamFactoryNode : _STL::_Rb_tree_node_base {
 int m_key0;
 int m_key1;
 TeamPrototype *m_proto;
};
class TeamFactory {
public:
 void rva003A262C();
private:
 char m_pad[0xB0];
 _STL::_Rb_tree_node_base *m_header;
};
// ?rva003A262C@TeamFactory@@QAEXXZ @0x003A262C (45B)
void TeamFactory::rva003A262C()
{
 for (_STL::_Rb_tree_node_base *node = m_header->_M_left; node != m_header; node = _STL::_Rb_global<bool>::_M_increment(node))
  static_cast<TeamFactoryNode *>(node)->m_proto->rva003A0D0A();
}
