// cl: /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /O1 /G7 /arch:SSE /ICode/Libraries/Include /DNDEBUG /MD
// Formation facing rotation.
//
// ?rva0042245F@Formation@@QAEXM@Z @0x0042245F 229B (thiscall, RET4): builds
// a rotation about +Z by angle + PI/2 and rotates every slot's integer
// template offset into its float position.
// Evidence: retail body (cos/sin imports, 1.5707964f at 0x00BC2A24, the
// constant-folded Matrix3D(axis, s, c) for axis (0,0,1), slot stride 0x20,
// ints at +0x10/+0x14 read y first, floats stored at +0x18/+0x1C). WB twin
// 0x0113A900 (vector3.h/Matrix3D.h asserts, named Matrix3D::Set) shows
// Vector3 axis(0,0,1), Matrix3D(axis, angle + PI/2) and, per slot,
// Vector3 v(x, y, 0) through Matrix3D::Transform_Vector into a temporary
// stored at +0x18. Callers: AIGroup formation move 0x00372571 (the REL32 at
// 0x00372782), 0x0037FAC6 and 0x00547CB6. Class and member names are not
// recovered, hence the address name (pinned in reverse/symbols.csv).
#include "matrix3d.h"

// Slot position: the WB twin assigns it through a call taking the
// Vector3 (0x0041C550 there), inlined in retail.
struct FormationSlotPos
{
	void set(const Vector3 &v)
	{
		x = v.X;
		y = v.Y;
	}
	float x;
	float y;
};

// Slot template offset (the WB twin takes its address first).
struct FormationSlotOffset
{
	int x;
	int y;
};

// One formation slot (32 bytes).
struct FormationSlot
{
	char m_pad00[0x10];
	FormationSlotOffset m_offset;
	FormationSlotPos m_pos;
};

class Formation
{
public:
	void rva0042245F(float angle);
	FormationSlot *m_begin;
	FormationSlot *m_end;
};

void Formation::rva0042245F(float angle)
{
	Matrix3D m(Vector3(0.0f, 0.0f, 1.0f), angle + WWMATH_PI / 2);
	for (FormationSlot *it = m_begin; it != m_end; ++it)
	{
		const FormationSlotOffset &offset = it->m_offset;
		Vector3 v((float)offset.x, (float)offset.y, 0.0f);
		Vector3 r;
		Matrix3D::Transform_Vector(m, v, &r);
		it->m_pos.set(r);
	}
}
