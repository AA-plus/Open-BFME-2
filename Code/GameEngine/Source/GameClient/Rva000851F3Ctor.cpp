// cl: /MD /EHsc /DNDEBUG
// ??0Rva000851F3@@QAE@XZ, retail 0x000851F3, 71 bytes.
// Ctor storing the real three-slot vtable BC745C at +0, then ParabolicEase
// at +0x10 via rowed 0x0008517E
// with (0 0 1) then zeroing +4 +8 +0x20 +0x24 +0x28 +0x18 +0x1c.
// Evidence: rowed ParabolicEase forward 0x0008517E; callers 0x0008990C 0x00312C95.
// BC745C = {scalar-delete 85241, purecall 3B810, purecall 3B810}; its
// first pointer incidentally spells "ARH". Plain cleanup 8523A restores
// the table; scalar-delete 85241 is 29B/RET4 and restores it before delete.
// Derived BC74F4 has matching RET4/RET24 slots. The first slot argument
// and final unused word of the second retain only their ABI word views.
// Original names, complete layout and historical class identity are unknown.
#include "../../Include/GameClient/Rva0008990CArrayOwner.h"

Rva000851F3::Rva000851F3()
{
	m_10.rva0008517E(0.0f, 0.0f, 1.0f);
	m_04 = 0;
	m_08 = 0;
	m_20 = 0;
	m_24 = false;
	m_28 = 0;
	m_18 = 0.0f;
	m_1C = 0.0f;
}

// ??0Rva00312C95@@QAE@XZ, retail 0x00312C95, 93 bytes: the derived 0x60-byte
// object (vtable 0x00BC7514) GiantBirdAIUpdate keeps at +0x4C8 and the
// 0x0008B7CF product holds twice. After the base it builds a 12-byte vector
// header at +0x2C through the folded _Vector_base constructor 0x00211E58
// (the call cannot throw: retail keeps no unwind state), then zeroes its
// floats, int and flags and re-clears the base's +0x24 flag.
class GameWindow;
namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &a) throw();
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}

struct Rva00312C95Triple
{
	float x, y, z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

class Rva00312C95 : public Rva000851F3
{
public:
	Rva00312C95();
private:
	_STL::_Vector_base<GameWindow *, _STL::allocator<GameWindow *> > m_2C;	// +0x2C
	float m_38;
	float m_3C;
	int m_40;
	bool m_44;
	bool m_45;
	bool m_46;
	Rva00312C95Triple m_48;
	Rva00312C95Triple m_54;
};

Rva00312C95::Rva00312C95() : m_2C(_STL::allocator<GameWindow *>())
{
	m_40 = 0;
	m_38 = 0.0f;
	m_3C = 0.0f;
	m_48.zero();
	m_24 = false;
	m_44 = false;
	m_45 = false;
	m_46 = false;
	m_54.zero();
}
