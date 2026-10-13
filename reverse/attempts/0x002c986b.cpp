// ?Get2DBorderVectorTo@Object@@QBEXPAUCoord3D@@PBU2@@Z
// partial score=0.83 date=2026-10-13
// ?Get2DBorderVectorTo@Object@@QBEXPAUCoord3D@@PBU2@@Z (W7-MO1 r1, 20 line-diffs)
// FRAGMENT for Code/GameEngine/Source/Common/GapBodiesSeat1B.cpp: add the two
// method decls to the existing minimal Object class, append the body at EOF.
// All 3 callees rowed. Zero-init-regs shape right; WALL: zero-init hoisting above
// compare spills compare to xmm4/5 (retail: radius->xmm0, comiss, jb). else-assign
// gives homes (24). NEXT: pin zero-inits below compare without homes.
// --- 0x002C986B (119B): Object::Get2DBorderVectorTo (WorldBuilder Object.h).
// Border vector to a position: the center vector scaled by the overshoot
// fraction, or zero when inside the +0xB8 radius.
void Object::Get2DBorderVectorTo(Coord3D *out, const Coord3D *pos) const
{
	Coord3D temp;
	Get2DCenterVectorTo(&temp, pos);
	float len = temp.length();
	float radius = *(const float *)((const char *)this + 0xb8);
	float ox = 0.0f, oy = 0.0f, oz = 0.0f;
	if (radius < len) {
		float f = (len - radius) / len;
		ox = temp.x * f;
		oy = temp.y * f;
		oz = temp.z * f;
	}
	out->x = ox;
	out->y = oy;
	out->z = oz;
}
