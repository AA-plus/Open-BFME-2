// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00524436@@QAE@XZ @0x00524436 65B evidence: dtor via rowed clear 0x00523F8C plus vector CameraMarker at +0xc via dup 0x005243BB plus vector AsciiString at +0 via 0x0002CC70; precedent Rva00524265Dtor single-vector shape; callers 0x005248D0 0x0052634F 0x0052936C 0x005C7954
#include <vector>

#include "ascii_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}

class CameraMarker
{
public:
	~CameraMarker();
};

class Rva00524021
{
public:
	void rva00523F8C();
};

class Rva00524436
{
public:
	~Rva00524436();
private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_00;
	_STL::vector<CameraMarker, _STL::allocator<CameraMarker> > m_0c;
};

// bfme link decl-only begin
namespace _STL { template <> void _Destroy<CameraMarker *>(CameraMarker *,CameraMarker *); }
namespace _STL { template <> void __destroy<CameraMarker *,CameraMarker>(CameraMarker *,CameraMarker *,CameraMarker *); }
namespace _STL { template <> void __destroy_aux<CameraMarker *>(CameraMarker *,CameraMarker *,_STL::__false_type const &); }
namespace _STL { template <> vector<CameraMarker,_STL::allocator<CameraMarker> >::~vector(); }
// bfme link decl-only end
Rva00524436::~Rva00524436()
{
	((Rva00524021 *)this)->rva00523F8C();
}
