// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva000795C1Record@@QAE@PAXI@Z @0x0058062B 27B (renamed from the
// address-derived Rva0058062B: the class IS the 16-byte sort comparator
// record). Stores first arg at +0x00 then constructs vector<ushort> at +0x04
// with second arg via rowed 0x002339F3, returns this. Evidence: the 87-byte
// body at 0x0058113D builds the sort's 16-byte by-value record argument
// in place with this ctor (sub esp,0x10; ecx=esp; pushes; call) and passes
// it with no copy, which is only possible when the constructed temporary
// already has the parameter's type; sizes match (16 bytes) and the member
// layout (pointer plus three-pointer vector) is the record layout.
// Callers: 0x00581171 passes the list object plus the element's v07 result;
// ret 8 with this in eax.
#include <vector>

class Rva000795C1Record
{
public:
    Rva000795C1Record(void *a, unsigned int n);

private:
    void *m_00;
    _STL::vector<unsigned short> m_04;
};

Rva000795C1Record::Rva000795C1Record(void *a, unsigned int n) : m_00(a), m_04(n)
{
}
