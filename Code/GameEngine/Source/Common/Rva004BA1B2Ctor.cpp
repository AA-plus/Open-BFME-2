// cl: /O1 /G7 /arch:SSE /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004BA1B2@@QAE@XZ, retail 0x004BA1B2 22B: default ctor constructs the Object-pointer vector at +4 via the existing 29B base fold 0x00211E58.
// Native caller4C78AF sets the first word from yielded Object*, then the
// ManTheWalls helpers4C7621/4C76AC/4C7734 use the +4 member as a vector
// with four-byte Object* elements. The 16-byte entry's copy at4C7330 and
// iteration at4C799B independently agree. The old E16 stand-in recovered
// the empty header bytes without establishing its element type. The first
// word is deliberately left uninitialized, as native22 does; the caller sets it.
// Both the Object-vector base29 and this constructor22 independently match
// in the improved ManTheWalls bank. The original record name remains unknown.
#include <vector>

class Object;
namespace _STL {
template<> __declspec(noinline)
_Vector_base<Object *,allocator<Object *> >::_Vector_base(const allocator<Object *> &a)
 : _M_start(0),_M_finish(0),_M_end_of_storage(a,0) {}
}
// Keep the standard empty base visible and out of line, as the complete
// native22/29 constructor pair proves in the ManTheWalls bank. /O1 retains
// the native allocator-proxy call; the pointer-specialized /O2 form inlined it.

class Rva004BA1B2 {
public:
	Rva004BA1B2();
private:
	Object *m_owner;
	_STL::vector<Object *> m_members;
};

Rva004BA1B2::Rva004BA1B2()
{
}
