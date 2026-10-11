// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0022A8F3Subsystem@@QAE@XZ @0x0022E092 55B
// Evidence: pin ctor; caller GameEngine::init 0x0022EDEF TheLivingWorldAutoResolveWeaponStore; callees baseConstruct 0x001B4E63 and hash_map 0x0022D95A; pattern mirrors PlayerAITypeSetCtor.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT; the same declaration-only form suppresses this TU's copy so callers
// bind retail's instead.
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}
#include "ascii_string.h"

struct Rva0022D95AElement
{
	char bytes[1];
};

class BFME2NativeNetwork
{
public:
};

// 0x001B4E63 is the rowed SubsystemInterface ctor.
class SubsystemInterface { public: SubsystemInterface(); };

class __declspec(novtable) Rva0022A8F3SubsystemBase
{
public:
	Rva0022A8F3SubsystemBase() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	virtual ~Rva0022A8F3SubsystemBase();
private:
	unsigned char m_04;
	int m_08;
};

class Rva0022A8F3Subsystem : public Rva0022A8F3SubsystemBase
{
public:
	Rva0022A8F3Subsystem();
	virtual ~Rva0022A8F3Subsystem();
private:
	_STL::hash_map<int, Rva0022D95AElement> m_map0C;
};

Rva0022A8F3Subsystem::Rva0022A8F3Subsystem()
{
}
