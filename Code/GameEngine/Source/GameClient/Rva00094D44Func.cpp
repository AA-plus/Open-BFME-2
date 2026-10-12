// cl: /MD /EHsc /DNDEBUG
// ?rva00094D44@@YGMMMM@Z @0x00094D44 100B: free function returning a float
// from three float args. Defaults to the 999999.0f compiler literal (retail
// .rdata 0xBC7484); when the .data pointer global is set, overrides with the
// dot of its +0x84 16-byte record against (a, b, c) plus the record tail, in
// retail evaluation order (z*c + y*b + x*a + w). Honest address-derived name;
// boundary verified (push ebp at 0x94D44, fld + leave + ret 0xC at end).
struct RvaVec4B { float x; float y; float z; float w; };
struct RvaVec3B { float x; float y; float z; };
struct RvaDE4880Owner { unsigned char m_pad[0x84]; RvaVec4B m_84; unsigned char m_pad94[0xD4 - 0x94]; RvaVec3B m_D4; float m_E0; };
static RvaDE4880Owner *g_00DE4880;
float __stdcall rva00094D44(float a, float b, float c)
{
	RvaDE4880Owner *g = g_00DE4880;
	float r = 999999.0f;
	if (g) {
		RvaVec4B v = g->m_84;
		r = v.z * c;
		r += v.y * b;
		r += v.x * a;
		r += v.w;
	}
	return r;
}

// BFME1 34f59164 Rva006E1CA0VectorLength.cpp supplies the clean expression.
// Target evidence independently establishes native94DE5..94E2C (71B RET0),
// one __cdecl pointer argument, float loads0/4/8, sqrt thunk62921C and ST0
// result. The owner/type name is unknown; retain an address-qualified view.
#include <math.h>

class Rva00094DE5Vector
{
public:
 static float length(const Rva00094DE5Vector *vector);
private:
 float x;
 float y;
 float z;
};

float Rva00094DE5Vector::length(const Rva00094DE5Vector *vector)
{
 return sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
}

// Retail 0x00094E2C (147B, RET 0xC), the next slot of the same table after
// 0x00094D44 and the same 999999.0f default: with the 0x00DE4880 state set,
// the +0xE0 radius less the distance from (a, b, c) to its +0xD4 centre,
// built from three fabs differences summed z first. Address-derived name.
float __stdcall rva00094E2C(float a, float b, float c)
{
	RvaDE4880Owner *g = g_00DE4880;
	float r = 999999.0f;
	if (g) {
		RvaVec3B center = g->m_D4;
		r = g->m_E0;
		RvaVec3B d;
		d.x = (float)fabs(center.x - a);
		d.y = (float)fabs(center.y - b);
		d.z = (float)fabs(center.z - c);
		r -= (float)sqrt(d.z * d.z + d.y * d.y + d.x * d.x);
	}
	return r;
}

// Native 94DB3..94DD3 (32B RET4): returns the +0x6C/+0x70/+0x74 float
// triple as a three-float value (the matrix column-getter shape of
// Matrix3D::Get_Y_Vector). No caller or table reaches it; owner unknown.
struct Rva00094DB3Vector
{
	Rva00094DB3Vector(float x, float y, float z) { X = x; Y = y; Z = z; }
	float X, Y, Z;
};

class Rva00094DB3
{
public:
	Rva00094DB3Vector rva00094DB3() const;
private:
	unsigned char m_pad[0x6C];
	float m_6C, m_70, m_74;
};

Rva00094DB3Vector Rva00094DB3::rva00094DB3() const
{
	return Rva00094DB3Vector(m_6C, m_70, m_74);
}
