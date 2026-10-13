// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHs /MD /D_STLP_USE_STATIC_LIB
// Fix over the banked 0.93 attempt, from the retail unwind map: state 0
// destroys the member at +4 through the folded 7-byte virtual dtor 0x0049B47C,
// so RegionBonusInfo has a virtual destructor; state 1 destroys +0x20 through the
// vector<AsciiString> dtor 0x0042CC70 and state 2 destroys +0x2C through the
// BfmeE16 vector dtor 0x0047FAB3, so the first vector holds AsciiStrings.
// The 0.3 default at +0x54 is a compiler literal (retail pool 0x007CCB3C).
// stlport
//
// ??0Rva002105A6@@QAE@H@Z @ 0x00210973 133B
// Ctor for Rva002105A6 (0x58 bytes via factory 0x00210AB8). Evidence: ID at
// +0 from counter 0x009FE1BC via caller 0x00210AE5; RegionBonusInfo at +4 via
// rowed 0x0020E42C; vectors at +0x20 plus 0x2C via rowed Vector_base BfmeE16
// 0x00211E58; strings at +0x38 plus 0x44 emptied plus -1 at +0x3C plus 0x40;
// floats 0 at +0x48 plus 0x4C plus 0x50 plus table 0x007CCB3C at +0x54; tail
// Clear via rowed 0x00210749; dtor rowed 0x002105A6.

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

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<BfmeE16,_STL::allocator<BfmeE16> >::~_Vector_base(); }
namespace _STL { template <> vector<BfmeE16,_STL::allocator<BfmeE16> >::~vector(); }
// bfme link decl-only end
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
// Suppress this TU's non-retail BfmeE16 proxy deallocate copy (family2-LK3 row 34):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<BfmeE16*, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16*, size_t);
}

class RegionBonusInfo
{
public:
	RegionBonusInfo();
	virtual ~RegionBonusInfo();
private:
	int m_values[6];
};

class Rva00210749
{
public:
	void rva00210749();
};


class Rva002105A6
{
public:
	Rva002105A6(int id);
private:
	int m_id;
	RegionBonusInfo m_rva04;
	_STL::vector<AsciiString> m_vec20;
	_STL::vector<BfmeE16> m_vec2C;
	AsciiString m_str38;
	int m_3C;
	int m_40;
	AsciiString m_str44;
	float m_48;
	float m_4C;
	float m_50;
	float m_54;
};

// ??0Rva002105A6@@QAE@H@Z @0x00210973
Rva002105A6::Rva002105A6(int id)
	: m_id(id)
	, m_3C(-1)
	, m_40(-1)
{
	m_48 = 0.0f;
	m_4C = 0.0f;
	m_50 = 0.0f;
	m_54 = 0.3f;
	((Rva00210749 *)this)->rva00210749();
}
