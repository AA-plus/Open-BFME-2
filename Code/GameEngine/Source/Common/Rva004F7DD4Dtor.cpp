// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1Rva004F7DD4@@QAE@XZ retail 0x004F7DD4 8B
// Rb dtor tail-jump: add ecx,4 then jmp Vector_base dtor 0x004F7D7F.
// Target callers 0x004F88DE/0x004F8B09 and deleting dtor 0x004F7E91 establish
// this destructor. Its tail target 0x004F7D7F is the rowed vector destructor
// in StlSweepR3Rva004F7D7F.cpp, not the void-pointer _Vector_base owner at
// 0x000251F0. The one-byte opaque element identity comes from that row;
// the target byte worker and three-pointer member layout establish the ABI.
struct Rva004F7D7FRecord;
namespace _STL {
template <class _Tp> class allocator {
};
template <class _Tp, class _Alloc> class vector
{
public:
	void *_M_start;
	void *_M_finish;
	void *_M_end;
	~vector();
};
}

struct Rva004F7DD4
{
	int m_dummy;
	_STL::vector<Rva004F7D7FRecord, _STL::allocator<Rva004F7D7FRecord> > m_vec;
	~Rva004F7DD4();
};

Rva004F7DD4::~Rva004F7DD4()
{
}
