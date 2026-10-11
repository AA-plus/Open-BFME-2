// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva004DCC62@Rva004DCC62@@QAEPAXPBX@Z @0x004DCC62, 34B.
// RB node create: allocate 0x18 via rowed allocator 0x000307F0 then rowed
// pair-copy _Construct 0x00469D1A for the two-byte key plus aligned
// four-byte mapped value at +0x10. Callers 0x004D1CAB 0x004D1CC4
// pass this in ecx plus the value; this is unused. Unblocks 0x004D1C81.
#include <map>
// Native 4DCC76 calls the 469D1A placement wrapper, whose existing
// two-byte key view preserves the original key bits and aligned int value.
struct Rva00469D1AElement { short words[1]; };
typedef _STL::pair<const Rva00469D1AElement, int> NativeNodeValue;
namespace _STL {
template <> class allocator<char> {
public:
	static char *allocate(unsigned int bytes, const void *hint);
};
template <> void _Construct<NativeNodeValue, NativeNodeValue>(NativeNodeValue *, const NativeNodeValue &);
}

class Rva004DCC62
{
public:
	void *rva004DCC62(const void *src);

private:
	char m_pad[0x10];
	_STL::pair<const Rva00469D1AElement, int> m_value;
};

void *Rva004DCC62::rva004DCC62(const void *src)
{
	char *node = _STL::allocator<char>::allocate(0x18, 0);
	_STL::_Construct((NativeNodeValue *)(node + 0x10), *(const NativeNodeValue *)src);
	return node;
}
