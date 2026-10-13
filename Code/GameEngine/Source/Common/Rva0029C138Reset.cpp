// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
// Target Ghidra43-byte body: clear the list header at+0x910, then write
// signed bit pattern-2 to four words at+0x914/+0x918/+0x91C/+0x920.
// The list call uses the already rowed39-byte node-clear implementation.
// list<int> here is an ABI call view: the clear helper frees nodes without
// reading their payload. The original payload type spelling, class/method and
// complete object size remain unknown. The adjacent 219-byte query establishes
// two signed coordinate words per node and inclusive bounding limits at the
// four offsets. Its integer product is converted to float only after IMUL;
// horizontal edges and edges wholly above/below/left of the point are skipped.
// WB 0x00DB6570 has the same checks and wrapped list iteration, but no name.
// Original class and method names remain unasserted.
#include <list>
#include "../../../Libraries/Include/Lib/ICoord2D.h"
namespace _STL {
template<> void _List_base<int,allocator<int> >::clear();
template <class T, class L, class R>
static inline bool operator!=(const _List_iterator<T,L>& a,
                              const _List_iterator<T,R>& b) {
    return a._M_node != b._M_node;
}
}
class Rva0029C138 {
public:
    void rva0029C138();
    bool rva0029C163(const ICoord2D& point);
private:
    unsigned char m_prefix[0x910];
    _STL::list<ICoord2D> m_points;
    int m_word914,m_word918,m_word91C,m_word920;
};
void Rva0029C138::rva0029C138() {
    reinterpret_cast<_STL::_List_base<int,_STL::allocator<int> >*>(&m_points)->clear();
    m_word914=-2;
    m_word918=-2;
    m_word91C=-2;
    m_word920=-2;
}

bool Rva0029C138::rva0029C163(const ICoord2D& point) {
    if (point.x < m_word914) return false;
    if (point.y < m_word918) return false;
    if (point.x > m_word91C) return false;
    if (point.y > m_word920) return false;

    bool inside = false;
    for (_STL::list<ICoord2D>::iterator it = m_points.begin();
         it != m_points.end();) {
        ICoord2D a = *it;
        it++;
        ICoord2D b;
        if (it != m_points.end()) b = *it;
        else b = *m_points.begin();

        if (a.y == b.y) continue;
        if (a.y < point.y && b.y < point.y) continue;
        if (a.y >= point.y && b.y >= point.y) continue;
        if (a.x < point.x && b.x < point.x) continue;

        float intersection = (float)((point.y-a.y)*(b.x-a.x)) /
                             (float)(b.y-a.y) + (float)a.x;
        if (intersection >= (float)point.x) inside = !inside;
    }
    return inside;
}
