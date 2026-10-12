// ?rva002C58B3@Rva002C589B@@QAEXXZ
// partial score=0.984 date=2026-10-13
// ?rva002C58B3@Rva002C589B@@QAEXXZ
// partial score=0.984 date=2026-10-13
// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc
// Reconciled into the owner TU Rva002C589BDtor.cpp: views are
// layout-identical (m_frame/m_position/m_18/m_19/m_unknown1C/m_ptr/m_34),
// canonical Coord3D for floats and position, cast for the clearer pointee.
// 92/92 with a 3-line push-edi rotation (retail byte-stores then save vs
// ours save then stores); byte-after-floats reorder and entry fence both
// churn wider. Pure save-hoist heuristic. t=25 model=muse-spark
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// Pointee-side view for the reset below: 12 zero bytes at +0x554 plus the
// rowed disp32 dword clearer at +0x564 (0x003ECB0B). The cast from the
// unit's Rva003ECDB7Object is layout evidence from the bank (identical
// member offsets); the call resolves by the rowed mangled name.
class Rva003ECB0BDwordClearer
{
public:
	void clear();
	char m_pad[0x554];
	Coord3D m_vec;
};

// ?rva002C58B3@Rva002C589B@@QAEXXZ @0x002C58B3 92B: reset. int at +8 to -1,
// floats of the canonical position to 0, bytes at +0x18/+0x19 and int at
// +0x1C to 0, 12 zero bytes at m_ptr+0x554 via Coord3D temp copy, rowed
// clear 0x003ECB0B on m_ptr, ObjectID at +0x34 to INVALID_ID. Caller
// 0x002C5D02. Statement order mirrors the .985 bank.
void Rva002C589B::rva002C58B3()
{
	m_frame = -1;
	m_unknown1C = 0;
	m_19 = false;
	m_18 = false;
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
	_ReadWriteBarrier();
	Coord3D tmp = { 0.0f, 0.0f, 0.0f };
	((Rva003ECB0BDwordClearer *)m_ptr)->m_vec = tmp;
	((Rva003ECB0BDwordClearer *)m_ptr)->clear();
	m_34 = INVALID_ID;
}
