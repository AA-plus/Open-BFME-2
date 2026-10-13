// ??0Rva0042FD9E@@QAE@XZ
// partial score=0.96 date=2026-10-13
// ??0Rva0042FD9E@@QAE@XZ
// partial score=0.96 date=2026-10-13
// ??0Rva0042FD9E@@QAE@XZ
// partial score=0.96 date=2026-10-13
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /arch:SSE
// stlport
// ??0Rva0042FD9E@@QAE@XZ, retail 0x0042FD9E, 129 bytes.
// Ctor with vtable 0x00C3C960, map<int,void*> at +0x28, ints/floats zeroed, int at +0x0C set to -1, global 0x00E03220 stores this.
// Evidence: target bytes only; map ctor 0x0033C432 rowed (signed-key mangling kept); clear respelled to rowed unsigned-key 0x00357416 via unsigned-map ref cast (signed clear misresolves to 0x286656 twin); vtable and global from immediates. Wall: or(+0x0C)/xorps order swapped + EH-state-1 store hoisted above zero stores; /O1/G7/EHsc/barrier-before-b20 probed, barrier sinks mov ecx,edi only.
// ??0Rva0042FD9E@@QAE@XZ present-unmatched
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <map>
extern const void *const g_00C3C960[];
extern void *g_00E03220;
class Rva0042FD9EBase
{
public:
	Rva0042FD9EBase() {}
	~Rva0042FD9EBase();
};
class Rva0042FD9E : public Rva0042FD9EBase
{
public:
	Rva0042FD9E();
private:
	const void *m_vtable;
	bool m_b04;
	bool m_b05;
	bool m_b06;
	bool m_b07;
	int m_i08;
	int m_i0C;
	int m_i10;
	int m_i14;
	int m_i18;
	int m_i1C;
	bool m_b20;
	int m_i24;
	_STL::map<int, void *> m_map28;
	float m_f34;
	float m_f38;
	float m_f3C;
};
Rva0042FD9E::Rva0042FD9E()
	: Rva0042FD9EBase()
	, m_vtable(reinterpret_cast<const void *>(g_00C3C960))
{
	m_i0C = -1;
	_ReadWriteBarrier();
	m_b04 = false;
	m_b05 = false;
	m_b06 = false;
	m_b07 = false;
	m_i08 = 0;
	m_i10 = 0;
	m_i14 = 0;
	m_i18 = 0;
	m_i1C = 0;
	m_i24 = 0;
	m_f34 = 0.0f;
	m_f38 = 0.0f;
	m_f3C = 0.0f;
	_ReadWriteBarrier();
	m_b20 = false;
	reinterpret_cast<_STL::map<unsigned int, void *> &>(m_map28).clear();
	g_00E03220 = this;
}
