// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??0SpawnArmy@@QAE@ABV0@@Z @ 0x004E2F9F (295B).
// Copy ctor of the ModuleData class with vtable 0x00861F28 whose dtor is
// rowed at 0x004E3184. Same temp is built here and torn down by that dtor
// in caller 0x004FB924. _Construct wrapper at 0x004E3706 treats it as
// 88-byte BfmePod88. Members call StringBase<char> copy at 0x000365F0 and
// vector<AsciiString> copy at 0x000BC07E. Layout from the dtor TU plus
// retail offsets. Snapshot base dtor arms EH state 0 before the first member
// like retail.
#include <memory>
#include <vector>

#include "ascii_string.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> vector<AsciiString, allocator<AsciiString> >::vector(const vector<AsciiString, allocator<AsciiString> >&);
template <> AsciiString *__uninitialized_copy(const AsciiString*, const AsciiString*, AsciiString*, const __false_type&);
}

class SpawnArmy : public Snapshot {
public:
    virtual ~SpawnArmy();
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer*);
    SpawnArmy(const SpawnArmy &o);
private:
    AsciiString m_04;
    AsciiString m_08;
    AsciiString m_0c;
    AsciiString m_10;
    AsciiString m_14;
    AsciiString m_18;
    AsciiString m_1c;
    float m_20;
    float m_24;
    AsciiString m_28;
    AsciiString m_2c;
    AsciiString m_30;
    AsciiString m_34;
    _STL::vector<AsciiString> m_vec38;
    float m_44;
    int m_48;
    int m_4c;
    AsciiString m_50;
    bool m_54;
    bool m_55;
};

SpawnArmy::SpawnArmy(const SpawnArmy &o)
    : m_04(o.m_04), m_08(o.m_08), m_0c(o.m_0c), m_10(o.m_10),
      m_14(o.m_14), m_18(o.m_18), m_1c(o.m_1c),
      m_20(o.m_20), m_24(o.m_24),
      m_28(o.m_28), m_2c(o.m_2c), m_30(o.m_30), m_34(o.m_34),
      m_vec38(o.m_vec38),
      m_44(o.m_44), m_48(o.m_48), m_4c(o.m_4c),
      m_50(o.m_50), m_54(o.m_54), m_55(o.m_55)
{
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0BfmePod88@@QAE@ABU0@@Z=??0SpawnArmy@@QAE@ABV0@@Z")
