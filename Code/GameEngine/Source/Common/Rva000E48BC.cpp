// cl: /MD
//
// ?rva000E48BC@Rva000E48BC@@QAE_NPAVRva000E488F@@@Z, retail 0x000E48BC, 252 bytes.
// Updates world pos at +0 from offset at +0x10 via Drawable at +0x2C matrix
// then checks container predicate and returns changed.
// Evidence: retail push ebp plus mov ebp esp plus sub esp 0x0c frame; mov
// esi ecx plus mov ecx [esi+0x2C] plus test plus mov bl [esi+0x80] plus je;
// push edi plus lea edi [esi+0x10] plus call getTransformMatrix at 0x0027628E
// plus cmp esi edi plus jne plus movss mulss addss rows plus pop edi; mov
// ecx [ebp+8] plus push esi plus call 0x000E488F plus neg sbb inc plus xor
// ecx ecx plus cmp bl al plus mov [esi+0x80] al plus setne cl plus mov al cl;
// Matrix3D Transform_Vector alias check plus Z Y X row order proven by
// retail movss sequence; container Rva000E488F rowed; Drawable
// getTransformMatrix pinned; callers at 0x000E5819; unblocks 0x000E57FF.
// Layout begin +0 plus +0x10 plus +0x2C plus +0x80 proven by retail loads;
// element and owner unproven so honest Rva names only.
#define WWINLINE __forceinline

class Vector3
{
public:
	float X;
	float Y;
	float Z;
	WWINLINE float &operator[](int i) { return (&X)[i]; }
	WWINLINE const float &operator[](int i) const { return (&X)[i]; }
	WWINLINE Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
};

class Vector4
{
public:
	float X;
	float Y;
	float Z;
	float W;
	WWINLINE float &operator[](int i) { return (&X)[i]; }
	WWINLINE const float &operator[](int i) const { return (&X)[i]; }
};

#pragma optimize("ty", on)
class Matrix3D
{
public:
	Vector4 Row[3];
	WWINLINE Vector4 &operator[](int i) { return Row[i]; }
	WWINLINE const Vector4 &operator[](int i) const { return Row[i]; }
	static WWINLINE void Transform_Vector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		Vector3 *v;
		if (out == &in) {
			tmp = in;
			v = &tmp;
		} else {
			v = (Vector3 *)&in;
		}
		out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z + A[0][3]);
		out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z + A[1][3]);
		out->Z = (A[2][0] * v->X + A[2][1] * v->Y + A[2][2] * v->Z + A[2][3]);
	}
	// LINK: same-body file-static helper (identical inlined bytes; kept inside
	// the same optimize region so codegen matches). This TU's Transform_Vector
	// copy is not retail's (home: frustum.cpp @0x7B501); the call below inlines
	// it but still emits the loser COMDAT. Rebinding there emits nothing
	// (internal linkage, fully inlined). No flags touched.
	static WWINLINE void bfme_xform(const Matrix3D &A, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		Vector3 *v;
		if (out == &in) {
			tmp = in;
			v = &tmp;
		} else {
			v = (Vector3 *)&in;
		}
		out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z + A[0][3]);
		out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z + A[1][3]);
		out->Z = (A[2][0] * v->X + A[2][1] * v->Y + A[2][2] * v->Z + A[2][3]);
	}
};
#pragma optimize("", on)

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
};

class Rva000E488F
{
public:
	bool rva000E488F(void *arg);
};

class Rva000E48BC
{
public:
	bool rva000E48BC(Rva000E488F *container);
	int rva000E49B8(int player);
	Vector3 m_pos;
	float m_extent; // +0x0C, proven by the 0x000E49B8 sample loads [esi+0xC]
	Vector3 m_offset;
	char m_pad1C[0x2C - 0x1C];
	Drawable *m_drawable;
	char m_pad30[0x80 - 0x30];
	bool m_flag;
};

bool Rva000E48BC::rva000E48BC(Rva000E488F *container)
{
	bool old = m_flag;
	if (m_drawable) {
		Vector3 *out = &m_pos;
		const Vector3 *in = &m_offset;
		const Matrix3D *mtx = m_drawable->getTransformMatrix();
		Matrix3D::bfme_xform(*mtx, *in, out);
	}
	bool cur = !container->rva000E488F(this);
	m_flag = cur;
	return old != cur;
}

// ?rva000E49B8@Rva000E48BC@@QAEHH@Z, retail 0x000E49B8..0x000E4BD5, 541 bytes.
// Shrouded-bounds query: flag test at drawable+0x260 bit 44, then the world
// position (m_pos, refreshed through the drawable matrix from m_offset) plus
// the four +/-m_extent samples fed to the rowed PartitionManager
// getShroudStatusForPlayer thunk 0x007397F0 (SHROUD_CLEAR = 0 means visible).
// Live int result proven by retail EAX returns; the 1 constant is hoisted to
// EBX, and the transform's alias test uses the conditional form
// (bfme_xform_cond) that retail's jne/jmp layout and Z,Y,X row order need.
// m_extent at +0x0C is proven by the five sample loads [esi+0xC]; the sample-4
// addss operand order needs the volatile read of m_pos.X in sample 3 (the IR
// numbering flip), which is what makes this body byte-exact.
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "PartitionRangeQueryCallView.h"

class ShroudManager;
extern ShroudManager *TheShroudManager;

struct BitFlagsView
{
	unsigned m_bits[4];
	__forceinline bool test(int bit) const { return (m_bits[bit >> 5] & (1 << (bit & 31))) != 0; }
};

// The shroud-bounds query at 0x000E49B8 inlines the same transform with the
// alias test written as a conditional expression (retail's jne/jmp layout and
// its Z,Y,X row order). File scope so it is compiled outside the pragma
// optimize region that the 0x000E48BC row above was verified under.
static WWINLINE void bfme_xform_cond(const Matrix3D &A, const Vector3 &in, Vector3 *out)
{
	Vector3 tmp;
	Vector3 *v = (out == &in) ? (tmp = in, &tmp) : (Vector3 *)&in;
	out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z + A[0][3]);
	out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z + A[1][3]);
	out->Z = (A[2][0] * v->X + A[2][1] * v->Y + A[2][2] * v->Z + A[2][3]);
}

template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}

int Rva000E48BC::rva000E49B8(int player)
{
	const int visible = 1;
	Drawable *d = m_drawable;
	if (d && ((const BitFlagsView *)((char *)d + 0x260))->test(44))
		return visible;
	if (TheShroudManager) {
	if (d) {
		Vector3 *out = &m_pos;
		const Vector3 *in = &m_offset;
		const Matrix3D *mtx = d->getTransformMatrix();
		bfme_xform_cond(*mtx, *in, out);
	}
	Coord3D c;
	c.x = __vref(m_pos.X);
	c.y = m_pos.Y;
	c.z = m_pos.Z;
	if (!reinterpret_cast<PartitionManager*>(TheShroudManager)->getShroudStatusForPlayer(player, &c))
		return visible;
	c.x = m_pos.X + m_extent;
	c.y = m_pos.Y;
	c.z = m_pos.Z;
	if (!reinterpret_cast<PartitionManager*>(TheShroudManager)->getShroudStatusForPlayer(player, &c))
		return visible;
	c.x = m_pos.X - m_extent;
	c.y = m_pos.Y;
	c.z = m_pos.Z;
	if (!reinterpret_cast<PartitionManager*>(TheShroudManager)->getShroudStatusForPlayer(player, &c))
		return visible;
	c.x = m_pos.X;
	c.y = m_pos.Y + m_extent;
	c.z = m_pos.Z;
	if (!reinterpret_cast<PartitionManager*>(TheShroudManager)->getShroudStatusForPlayer(player, &c))
		return visible;
	c.x = m_pos.X;
	c.y = m_pos.Y - m_extent;
	c.z = m_pos.Z;
	if (!reinterpret_cast<PartitionManager*>(TheShroudManager)->getShroudStatusForPlayer(player, &c))
		return visible;
 }
	return 0;
}

