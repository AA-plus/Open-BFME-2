// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G7 /Oy-
// stlport
//
// ??0Rva003F877E@@QAE@HH@Z @0x003F877E 43B.
// Ctor of unknown class with vtable 0x00837318: stores two int args at +4/+8,
// then constructs vector<BfmeE16> at +0xC via rowed Vector_base 0x00211E58.
// Evidence: leaf lane; callees all rowed; caller Parse body at 0x003F91A4;
// layout matches sibling Rva003F8ED6 ctor (vector at +0xC, same flags);
// base-before-vtable order proves 2-int base; ret 8 with ecx=this proves HH.
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

struct Base003F877E
{
	Base003F877E(int a, int b) : m_04(a), m_08(b) {}
	int m_04;
	int m_08;
};

class Rva003F877E : public Base003F877E
{
public:
	Rva003F877E(int a, int b);
	virtual ~Rva003F877E();
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_0C;
};

Rva003F877E::Rva003F877E(int a, int b) : Base003F877E(a, b), m_0C()
{
}
// Rva003F91A4Parse: native 0x003F91A4..0x003F9258 including INT3 tail.
// The retail assertion names LogicTurn::ParseINI; original declaration and
// unused trailing arguments remain unproven. Keep the opaque cdecl prefix.
// Target evidence: scanInt token; 24B allocation; constructor receives the
// holder pointer bits and scanned int; INI field table then holder append.
// The constructor's int-typed first argument is the existing opaque ABI,
// not proof that the original source represented that pointer as an int.
// Reconstructed from retail; canonical INIException copying gives native
// direct exception construction. The EH and throw-data graphs are verified.
#include "ascii_string.h"
struct FieldParse;
class INI {
public:
 AsciiString getNextQuotedAsciiString();
 int scanInt(const char *);
 void initFromINI(void *,const FieldParse *);
};
class ModuleData;
struct Rva003F9048 {
 void rva003F9048(const ModuleData *);
};
class INIException {
public:
 char *message; int error;
 INIException(int,const char *,...);
 ~INIException();
 INIException(const INIException &);
 INIException &operator=(const INIException &);
};
// Descriptive data roles; original table names remain unproven.
extern const FieldParse g_logicTurnFields;
// Retail proves two accessed cdecl arguments; no trailing-parameter claim.
void Rva003F91A4Parse(INI *ini,Rva003F9048 *outer) {
 if(!ini || !outer) throw INIException(3,"Invalid data in LogicTurn::ParseINI");
 AsciiString token=ini->getNextQuotedAsciiString();
 int phase=ini->scanInt(token.str());
 Rva003F877E *created=new Rva003F877E(reinterpret_cast<int>(outer),phase);
 ini->initFromINI(created,&g_logicTurnFields);
 outer->rva003F9048(reinterpret_cast<const ModuleData*>(created));
}
