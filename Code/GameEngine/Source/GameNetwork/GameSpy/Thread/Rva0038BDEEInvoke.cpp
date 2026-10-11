// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?invoke@Rva0038BDEEReceiver@@QAEXPAX@Z @0x0038BDEE 41B
// Evidence: called by matched PeerThreadClass::stopHostingAlready 0x0038D53B plus 6 more; callees rowed _peerStopGame 0x00699410 plus basic_string assign 0x0001B790 plus string openstaging 0x00819890; prev PeerResponseAssign next OwnedRecordDeque.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <string>
#include <cstddef>
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

extern "C" void peerStopGame(void *peer);

class Rva0038BDEEReceiver
{
public:
	void invoke(void *peer);
private:
	char m_pad00[0xC4];
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_C4;
	char m_pad1[0x49C - 0xC4 - sizeof(_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >)];
	bool m_49C;
};

void Rva0038BDEEReceiver::invoke(void *peer)
{
	peerStopGame(peer);
	m_C4 = "openstaging";
	m_49C = false;
}
