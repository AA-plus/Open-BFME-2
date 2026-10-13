// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004E3CD0@@QAE@XZ @ 0x004E3C8F (65B). Ctor: vtable 0x00862054,
// BfmeVNITree at +4 via pin 0x005011C1, zero +0x10, vector at +0x14 via
// row 0x00211E58 (ICF fold), flags +0x20/0x21=0 +0x22=1, float +0x24 from
// g_Va00BBB8D8. Callers 0x004E3D1B 0x004E3D38 0x004E3F8B prove base;
// neighbours 0x004E3C71 and dtor 0x004E3CD0 share flags.
#include <vector>

// LINK: the 12-byte tree is rowed as map<int, BfmePod24>'s default ctor
// (0x005011C1); only that ctor is used here.
struct BfmePod24;
namespace _STL
{
template <class T> struct less;
template <class T> class allocator;
template <class A, class B> struct pair;
template <class K, class V, class C, class A> class map
{
public:
	map();
private:
	char m_pad[12];
};
}
typedef _STL::map<int, BfmePod24, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > > BfmeVNITree;

class Rva004E2382
{
public:
    ~Rva004E2382();
private:
    char m_pad[32];
};

// Base ctor is size-independent: use BfmeE16 stand-in to call rowed
// 0x00211E58. Real element is Rva004E2382 32B per dtor 0x004E3C32.
#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

typedef _STL::vector<BfmeE16, _STL::allocator<BfmeE16> > E16Vec;


class Rva004E3CD0
{
public:
    Rva004E3CD0();
    virtual ~Rva004E3CD0();
private:
    BfmeVNITree m_04;
    int m_10;
    E16Vec m_14;
    bool m_20;
    bool m_21;
    bool m_22;
    float m_24;
};

Rva004E3CD0::Rva004E3CD0() : m_10(0)
{
    float one = 1.0f;
    m_20 = false;
    m_21 = false;
    m_22 = true;
    m_24 = one;
}
