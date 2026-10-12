// cl: /O1 /G7 /arch:SSE /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0022C38BSubsystem@@QAE@XZ retail 0x0022DE2E 33B, the subsystem
// GameEngine::init creates through initSubsystem<Rva0022C38BSubsystem>
// (pinned): the canonical subsystem base constructor, the derived vtable
// 0x007E7660, then an empty vector at +0xC through the ICF-shared
// _Vector_base constructor 0x00211E58. Retail builds it without an EH
// frame. The element type is unknown; int stands in for it (all element
// types share the one folded base constructor).
#include <vector>

typedef bool Bool;
#include "subsystem_interface.h"

class Rva0022C38BSubsystem : public SubsystemInterface
{
public:
	Rva0022C38BSubsystem();
	virtual ~Rva0022C38BSubsystem();
private:
	_STL::vector<int> m_entries; // +0xC
};

Rva0022C38BSubsystem::Rva0022C38BSubsystem()
{
}
