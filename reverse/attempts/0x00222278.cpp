// ?Rva00222278Parse@@YAXPAVINI@@PAX@Z
// partial score=0.9028 date=2026-10-13
// ?Rva00222278Parse@@YAXPAVINI@@PAX@Z
// partial score=0.96 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
#include "ascii_string.h"
#include <stl/_prolog.h>
#include <stl/type_traits.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()
#include <map>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class INI { public: const char *getNextToken(const char *s); };
class Rva00221A58 { public: Rva00221A58(const Rva00221A58 &other); private: char m_pad[0x1C]; };
class Rva00221B42 { private: char m_pad[0x20]; };
class Rva00221C15 { public: Rva00221C15(const AsciiString &a, const Rva00221A58 &b, INI *ini); const void *m_vtable; int m_refs; Rva00221B42 m_08; };
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C { TargetRef00217D4C *m_ptr; TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other); };
struct TreeHintRef00221D6B { TargetRef00217D4C *m_ptr; };
typedef _STL::map<AsciiString, TreeHintRef00221D6B, _STL::less<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, TreeHintRef00221D6B> > > Map00221D6B;
typedef _STL::map<AsciiString, AsciiString, _STL::less<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, AsciiString> > > AsciiMap;
struct Owner00222278 { char m_00[0x0C]; Rva00221A58 m_0C; Map00221D6B m_28; };
void __cdecl Rva00222278Parse(INI *ini, void *ownerPtr)
{
	AsciiString key(ini->getNextToken((const char *)0));
	Owner00222278 *owner = (Owner00222278 *)ownerPtr;
	Rva00221C15 *obj = new Rva00221C15(key, ((Owner00222278 *)ownerPtr)->m_0C, ini);
	ownerPtr = obj;
	if (obj) ++obj->m_refs;
	if (((AsciiMap &)owner->m_28).find(key) == ((AsciiMap &)owner->m_28).end()) ((TreeHintRef00217D4C &)owner->m_28[key]) = (const TreeHintRef00217D4C &)ownerPtr;
	if (obj) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)obj);
}
