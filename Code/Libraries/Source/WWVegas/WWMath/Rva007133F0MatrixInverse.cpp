// cl: /O2 /arch:SSE /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug
// Retail 0x007133F0 (332B, ret 4), between Matrix3D::Get_Inverse (0x00713290,
// matrix3d_inverse.cpp) and Matrix3D::Multiply (0x00713540): a Matrix3D
// inverse taken through the 4x4 Gauss-Jordan Matrix4::Inverse. Donor:
// Open-BFME-1 09f941a50d game/Libraries/Source/WWVegas/WWMath/Rva008D7C20.cpp
// (BFME1 0x008D7C20, before its Multiply), same body. Target evidence: the
// Matrix4(const Matrix3D &) widening (three rows plus 0,0,0,1) inlined, then a
// thiscall with a hidden result pointer to 0x00715EB0, then the first three
// result rows copied element by element into the out-parameter. Unlike BFME1,
// which inlines the header's __forceinline Gauss-Jordan Inverse here, BFME2
// calls it out of line: the 2069-byte body at 0x00715EB0 inside matrix4.cpp's
// retail range is that Inverse (pivot search with WWMath::Fabs masking, row
// swaps, reciprocal row scale, elimination), so this TU declares Inverse in a
// TU-scoped Matrix4 view (as Rva00715E90Cluster.cpp does) instead of taking
// the header's inline definition. Class and method names are address-derived;
// the original name is unproven in both games.
#include "vector4.h"
#include "matrix3d.h"

class Matrix4
{
public:
	explicit Matrix4(const Matrix3D &m)
	{
		Row[0] = m[0]; Row[1] = m[1]; Row[2] = m[2]; Row[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
	}
	Matrix4 Inverse(void) const;
	Vector4 &operator[](int i) { return Row[i]; }
	const Vector4 &operator[](int i) const { return Row[i]; }
	Vector4 Row[4];
};
class Rva007133F0MatrixInverse : public Matrix3D
{
public:
	void inverse(Matrix3D &out) const;
};

void Rva007133F0MatrixInverse::inverse(Matrix3D &out) const
{
	Matrix4 mat(*this);
	Matrix4 result = mat.Inverse();
	out[0][0] = result[0][0];
	out[0][1] = result[0][1];
	out[0][2] = result[0][2];
	out[0][3] = result[0][3];
	out[1][0] = result[1][0];
	out[1][1] = result[1][1];
	out[1][2] = result[1][2];
	out[1][3] = result[1][3];
	out[2][0] = result[2][0];
	out[2][1] = result[2][1];
	out[2][2] = result[2][2];
	out[2][3] = result[2][3];
}
