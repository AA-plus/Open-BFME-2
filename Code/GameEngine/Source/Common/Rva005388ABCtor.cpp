// cl: /O1 /EHsc- /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE /G7
// stlport
// ??0Rva005388AB@@QAE@XZ @0x005388AB 23B
// Evidence: leaf lane, callees all rowed (Vector_base 0x00211E58 row PlayerAITypeSetCtor), callers 0x0030C5AB 0x0030C808 unclaimed, prev 0x00538839 reserve next 0x005388C2 QuadStrip copy, byte flag at +0x20 set 1 with vector base at +0.
#include <vector>

struct PlayerAITypeEntry
{
	char m_data[16];
};

class Rva005388AB
{
public:
	Rva005388AB();
private:
	_STL::vector<PlayerAITypeEntry> m_vec;
	char m_pad0C[0x20 - 0x0C];
	unsigned char m_20;
};

// bfme link decl-only begin
namespace _STL { template <> void _Destroy<PlayerAITypeEntry *>(PlayerAITypeEntry *,PlayerAITypeEntry *); }
namespace _STL { template <> void _Destroy<PlayerAITypeEntry>(PlayerAITypeEntry *); }
namespace _STL { template <> void __destroy<PlayerAITypeEntry *,PlayerAITypeEntry>(PlayerAITypeEntry *,PlayerAITypeEntry *,PlayerAITypeEntry *); }
namespace _STL { template <> void __destroy_aux<PlayerAITypeEntry *>(PlayerAITypeEntry *,PlayerAITypeEntry *,_STL::__false_type const &); }
namespace _STL { template <> _Vector_base<PlayerAITypeEntry,_STL::allocator<PlayerAITypeEntry> >::~_Vector_base(); }
namespace _STL { template <> vector<PlayerAITypeEntry,_STL::allocator<PlayerAITypeEntry> >::~vector(); }
namespace _STL { template <> void _STLP_alloc_proxy<PlayerAITypeEntry *,PlayerAITypeEntry,_STL::allocator<PlayerAITypeEntry> >::deallocate(PlayerAITypeEntry *,unsigned int); }
namespace _STL { template <> void allocator<PlayerAITypeEntry>::deallocate(PlayerAITypeEntry *,unsigned int) const; }
// bfme link decl-only end
Rva005388AB::Rva005388AB() : m_vec()
{
	m_20 = 1;
}
