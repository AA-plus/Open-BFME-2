// ?Render@SegLineRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@ABVSphereClass@@PAVVector4@@@Z
// partial score=0.7032564496041185 date=2026-10-13
// ?Render@SegLineRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@ABVSphereClass@@PAVVector4@@@Z
// SPDX-License-Identifier: GPL-3.0-or-later
// Adapted from Command & Conquer Generals Zero Hour, copyright 2025 Electronic Arts Inc.
// Complete semantic bank. Native191C10..195AA2,16018B; not byte exact.
// WB A454A0 and ZH SegLineRenderer establish identity/control flow.
// Native VB24B/four arguments, both lock12B, FVF fields10/44/24/0C.
// Matrix row16B empty ctor lifetime is a structural inference from two native
// ctor iterators, count4/stride16/callback47A6A9; original typedef unknown.
// Remaining geometry scheduling, stack homes, and loop ordering differ.
// cl: /I. /Ireference/shims/banked_segline /EHsc /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
#define Matrix4x4 Matrix4
#if defined(_MSC_VER)
#pragma once
#endif
#ifndef MATRIX4_H
#define MATRIX4_H
#include "always.h"
#include "vector4.h"
#include "matrix3d.h"
#include "matrix3.h"
struct SegMatrixRow : Vector4 {
SegMatrixRow();
SegMatrixRow &operator=(const Vector4 &v) {Vector4::operator=(v);return *this;}
};
class Matrix4x4
{
public:
Matrix4x4(void) {};
Matrix4x4(const Matrix4x4 & m);
WWINLINE explicit Matrix4x4(bool identity);
WWINLINE explicit Matrix4x4(const Matrix3D & m);
WWINLINE explicit Matrix4x4(const Matrix3x3 & m);
WWINLINE explicit Matrix4x4(const Vector4 & v0, const Vector4 & v1, const Vector4 & v2, const Vector4 & v3);
WWINLINE explicit Matrix4x4(	float m11,float m12,float m13,float m14,
float m21,float m22,float m23,float m24,
float m31,float m32,float m33,float m34,
float m41,float m42,float m43,float m44 );
WWINLINE void		Make_Identity(void);
WWINLINE void		Init(const Matrix3D & m);
WWINLINE void		Init(const Matrix3x3 & m);
WWINLINE void		Init(const Vector4 & v0, const Vector4 & v1, const Vector4 & v2, const Vector4 & v3);
WWINLINE void		Init(	float m11,float m12,float m13,float m14,
float m21,float m22,float m23,float m24,
float m31,float m32,float m33,float m34,
float m41,float m42,float m43,float m44 );
WWINLINE void		Init_Ortho(float left,float right,float bottom,float top,float znear,float zfar);
WWINLINE void		Init_Perspective(float hfov,float vfov,float znear,float zfar);
WWINLINE void		Init_Perspective(float left,float right,float bottom,float top,float znear,float zfar);
WWINLINE Vector4 & operator [] (int i) { return Row[i]; }
WWINLINE const Vector4 & operator [] (int i) const { return Row[i]; }
WWINLINE Matrix4x4 Transpose(void) const;
WWINLINE Matrix4x4 Inverse(void) const;
WWINLINE Matrix4x4 & operator = (const Matrix4x4 & m);
WWINLINE Matrix4x4 & operator += (const Matrix4x4 & m);
WWINLINE Matrix4x4 & operator -= (const Matrix4x4 & m);
WWINLINE Matrix4x4 & operator *= (float d);
WWINLINE Matrix4x4 & operator /= (float d);
WWINLINE friend Matrix4x4 operator - (const Matrix4x4& a);
WWINLINE friend Matrix4x4 operator * (const Matrix4x4& a,float d);
WWINLINE friend Matrix4x4 operator * (float d,const Matrix4x4& a);
WWINLINE friend Matrix4x4 operator / (const Matrix4x4& a,float d);
WWINLINE friend Matrix4x4 operator + (const Matrix4x4& a, const Matrix4x4& b);
WWINLINE friend Matrix4x4 Add(const Matrix4x4& a);
WWINLINE friend Matrix4x4 operator - (const Matrix4x4 & a, const Matrix4x4 & b);
WWINLINE friend Matrix4x4 Subtract(const Matrix4x4 & a, const Matrix4x4 & b);
WWINLINE friend Matrix4x4 operator * (const Matrix4x4 & a, const Matrix4x4 & b);
WWINLINE friend Matrix4x4 Multiply(const Matrix4x4 & a, const Matrix4x4 & b);
WWINLINE friend Matrix4x4 operator * (const Matrix4x4 & a, const Matrix3D & b);
WWINLINE friend Matrix4x4 operator * (const Matrix3D & a, const Matrix4x4 & b);
friend int operator == (const Matrix4x4 & a, const Matrix4x4 & b);
friend int operator != (const Matrix4x4 & a, const Matrix4x4 & b);
WWINLINE friend void Swap(Matrix4x4 & a,Matrix4x4 & b);
WWINLINE friend Vector4 operator * (const Matrix4x4 & a, const Vector4 & v);
WWINLINE friend Vector4 operator * (const Matrix4x4 & a, const Vector3 & v);
static void	Multiply(const Matrix4x4 &A,const Matrix4x4 &B,Matrix4x4 * set_result);
static void	Multiply(const Matrix3D &A,const Matrix4x4 &B,Matrix4x4 * set_result);
static void	Multiply(const Matrix4x4 &A,const Matrix3D &B,Matrix4x4 * set_result);
static WWINLINE void	Transform_Vector(const Matrix4x4 & tm,const Vector3 & in,Vector3 * out);
static WWINLINE void	Transform_Vector(const Matrix4x4 & tm,const Vector3 & in,Vector4 * out);
static WWINLINE void	Transform_Vector(const Matrix4x4 & tm,const Vector4 & in,Vector4 * out);
protected:
SegMatrixRow Row[4];
};
WWINLINE Matrix4x4::Matrix4x4(bool identity)
{
if (identity) {
Make_Identity();
}
}
WWINLINE Matrix4x4::Matrix4x4(const Matrix4x4 & m)
{
Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3];
}
WWINLINE Matrix4x4::Matrix4x4(const Matrix3D & m)
{
Init(m);
}
WWINLINE Matrix4x4::Matrix4x4(const Vector4 & r0, const Vector4 & r1, const Vector4 & r2, const Vector4 & r3)
{
Init(r0,r1,r2,r3);
}
WWINLINE Matrix4x4::Matrix4x4(float m11,float m12,float m13,float m14, float m21,float m22,float m23,float m24,
float m31,float m32,float m33,float m34, float m41,float m42,float m43,float m44 )
{
Init(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
}
WWINLINE void Matrix4x4::Make_Identity(void)
{
Row[0].Set(1.0,0.0,0.0,0.0);
Row[1].Set(0.0,1.0,0.0,0.0);
Row[2].Set(0.0,0.0,1.0,0.0);
Row[3].Set(0.0,0.0,0.0,1.0);
}
WWINLINE void Matrix4x4::Init(const Matrix3D & m)
{
Row[0] = m[0]; Row[1] = m[1]; Row[2] = m[2]; Row[3] = Vector4(0.0,0.0,0.0,1.0);
}
WWINLINE void Matrix4x4::Init(const Vector4 & r0, const Vector4 & r1, const Vector4 & r2, const Vector4 & r3)
{
Row[0] = r0; Row[1] = r1; Row[2] = r2; Row[3] = r3;
}
WWINLINE void Matrix4x4::Init(float m11,float m12,float m13,float m14, float m21,float m22,float m23,float m24,
float m31,float m32,float m33,float m34, float m41,float m42,float m43,float m44)
{
Row[0].Set(m11,m12,m13,m14);
Row[1].Set(m21,m22,m23,m24);
Row[2].Set(m31,m32,m33,m34);
Row[3].Set(m41,m42,m43,m44);
}
WWINLINE void Matrix4x4::Init_Ortho
(
float left,
float right,
float bottom,
float top,
float znear,
float zfar
)
{
assert(znear >= 0.0f);
assert(zfar > znear);
Make_Identity();
Row[0][0] = 2.0f / (right - left);
Row[0][3] = -(right + left) / (right - left);
Row[1][1] = 2.0f / (top - bottom);
Row[1][3] = -(top + bottom) / (top - bottom);
Row[2][2] = -2.0f / (zfar - znear);
Row[2][3] = -(zfar + znear) / (zfar - znear);
}
WWINLINE void Matrix4x4::Init_Perspective(float hfov,float vfov,float znear,float zfar)
{
assert(znear > 0.0f);
assert(zfar > znear);
Make_Identity();
Row[0][0] = static_cast<float>(1.0 / tan(hfov*0.5));
Row[1][1] = static_cast<float>(1.0 / tan(vfov*0.5));
Row[2][2] = -(zfar + znear) / (zfar - znear);
Row[2][3] = static_cast<float>(-(2.0*zfar*znear) / (zfar - znear));
Row[3][2] = -1.0f;
Row[3][3] = 0.0f;
}
WWINLINE void Matrix4x4::Init_Perspective
(
float left,
float right,
float bottom,
float top,
float znear,
float zfar
)
{
assert(znear > 0.0f);
assert(zfar > 0.0f);
Make_Identity();
Row[0][0] = static_cast<float>(2.0*znear / (right - left));
Row[0][2] = (right + left) / (right - left);
Row[1][1] = static_cast<float>(2.0*znear / (top - bottom));
Row[1][2] = (top + bottom) / (top - bottom);
Row[2][2] = -(zfar + znear) / (zfar - znear);
Row[2][3] = static_cast<float>(-(2.0*zfar*znear) / (zfar - znear));
Row[3][2] = -1.0f;
Row[3][3] = 0.0f;
}
WWINLINE Matrix4x4 Matrix4x4::Transpose() const
{
return Matrix4x4(
Vector4(Row[0][0], Row[1][0], Row[2][0], Row[3][0]),
Vector4(Row[0][1], Row[1][1], Row[2][1], Row[3][1]),
Vector4(Row[0][2], Row[1][2], Row[2][2], Row[3][2]),
Vector4(Row[0][3], Row[1][3], Row[2][3], Row[3][3])
);
}
WWINLINE Matrix4x4 Matrix4x4::Inverse() const
{
WWASSERT_PRINT(0,"Matrix4x4::Inverse does not work, re-implement!");
Matrix4x4 a(*this);
Matrix4x4 b(true);
int i, j, i1;
for (j=0; j<4; j++) {
i1 = j;
for (i=j+1; i<4; i++) {
if (WWMath::Fabs(a[i][j]) > WWMath::Fabs(a[i1][j])) {
i1 = i;
}
}
Swap(a.Row[i1], a.Row[j]);
Swap(b.Row[i1], b.Row[j]);
if (a[j][j]==0.) {
}
b.Row[j] /= a.Row[j][j];
a.Row[j] /= a.Row[j][j];
for (i=0; i<4; i++) {
if (i != j) {
b.Row[i] -= a[i][j] * b.Row[j];
a.Row[i] -= a[i][j] * a.Row[j];
}
}
}
return b;
}
WWINLINE Matrix4x4 & Matrix4x4::operator = (const Matrix4x4 & m)
{
Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3];
return *this;
}
WWINLINE Matrix4x4& Matrix4x4::operator += (const Matrix4x4 & m)
{
Row[0] += m.Row[0]; Row[1] += m.Row[1]; Row[2] += m.Row[2]; Row[3] += m.Row[3];
return *this;
}
WWINLINE Matrix4x4& Matrix4x4::operator -= (const Matrix4x4 & m)
{
Row[0] -= m.Row[0]; Row[1] -= m.Row[1]; Row[2] -= m.Row[2]; Row[3] -= m.Row[3];
return *this;
}
WWINLINE Matrix4x4& Matrix4x4::operator *= (float d)
{
Row[0] *= d; Row[1] *= d; Row[2] *= d; Row[3] *= d;
return *this;
}
WWINLINE Matrix4x4& Matrix4x4::operator /= (float d)
{
float ood = d;
Row[0] *= ood; Row[1] *= ood; Row[2] *= ood; Row[3] *= ood;
return *this;
}
WWINLINE Matrix4x4 operator - (const Matrix4x4 & a)
{
return Matrix4x4(-a.Row[0], -a.Row[1], -a.Row[2], -a.Row[3]);
}
WWINLINE Matrix4x4 operator * (const Matrix4x4 & a, float d)
{
return Matrix4x4(a.Row[0] * d, a.Row[1] * d, a.Row[2] * d, a.Row[3] * d);
}
WWINLINE Matrix4x4 operator * (float d, const Matrix4x4 & a)
{
return a*d;
}
WWINLINE Matrix4x4 operator / (const Matrix4x4 & a, float d)
{
float ood = 1.0f / d;
return Matrix4x4(a.Row[0] * ood, a.Row[1] * ood, a.Row[2] * ood, a.Row[3] * ood);
}
WWINLINE Matrix4x4 operator + (const Matrix4x4 & a, const Matrix4x4 & b)
{
return Matrix4x4(
a.Row[0] + b.Row[0],
a.Row[1] + b.Row[1],
a.Row[2] + b.Row[2],
a.Row[3] + b.Row[3]
);
}
WWINLINE Matrix4x4 Add(const Matrix4x4 & a, const Matrix4x4 & b)
{ return a+b; }
WWINLINE Matrix4x4 operator - (const Matrix4x4 & a, const Matrix4x4 & b)
{
return Matrix4x4(
a.Row[0] - b.Row[0],
a.Row[1] - b.Row[1],
a.Row[2] - b.Row[2],
a.Row[3] - b.Row[3]
);
}
WWINLINE Matrix4x4 Subtract(const Matrix4x4 & a, const Matrix4x4 & b)
{ return a-b; }
WWINLINE Matrix4x4 operator * (const Matrix4x4 & a, const Matrix4x4 & b)
{
#define ROWCOL(i, j) a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j] + a[i][3]*b[3][j]
return Matrix4x4(
Vector4(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2), ROWCOL(0,3)),
Vector4(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2), ROWCOL(1,3)),
Vector4(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2), ROWCOL(2,3)),
Vector4(ROWCOL(3,0), ROWCOL(3,1), ROWCOL(3,2), ROWCOL(3,3))
);
#undef ROWCOL
}
WWINLINE Matrix4x4 Multiply(const Matrix4x4 & a, const Matrix4x4 & b)
{ return a*b; }
WWINLINE Matrix4x4 operator * (const Matrix4x4 & a, const Matrix3D & b)
{
#define ROWCOL(i,j) a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j]
#define ROWCOL_LAST(i,j) a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j] + a[i][3]
return Matrix4x4(
Vector4(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2), ROWCOL_LAST(0,3)),
Vector4(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2), ROWCOL_LAST(1,3)),
Vector4(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2), ROWCOL_LAST(2,3)),
Vector4(ROWCOL(3,0), ROWCOL(3,1), ROWCOL(3,2), ROWCOL_LAST(3,3))
);
#undef ROWCOL
#undef ROWCOL_LAST
}
WWINLINE Matrix4x4 operator * (const Matrix3D & a, const Matrix4x4 & b)
{
#define ROWCOL(i,j) a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j] + a[i][3]*b[3][j]
return Matrix4x4(
Vector4(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2), ROWCOL(0,3)),
Vector4(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2), ROWCOL(1,3)),
Vector4(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2), ROWCOL(2,3)),
Vector4(b[3][0], b[3][1], b[3][2], b[3][3])
);
#undef ROWCOL
}
WWINLINE Vector4 operator * (const Matrix4x4 & a, const Vector3 & v) {
return Vector4(
a[0][0] * v[0] + a[0][1] * v[1] + a[0][2] * v[2] + a[0][3] * 1.0f,
a[1][0] * v[0] + a[1][1] * v[1] + a[1][2] * v[2] + a[1][3] * 1.0f,
a[2][0] * v[0] + a[2][1] * v[1] + a[2][2] * v[2] + a[2][3] * 1.0f,
a[3][0] * v[0] + a[3][1] * v[1] + a[3][2] * v[2] + a[3][3] * 1.0f
);
}
WWINLINE Vector4 operator * (const Matrix4x4 & a, const Vector4 & v) {
return Vector4(
a[0][0] * v[0] + a[0][1] * v[1] + a[0][2] * v[2] + a[0][3] * v[3],
a[1][0] * v[0] + a[1][1] * v[1] + a[1][2] * v[2] + a[1][3] * v[3],
a[2][0] * v[0] + a[2][1] * v[1] + a[2][2] * v[2] + a[2][3] * v[3],
a[3][0] * v[0] + a[3][1] * v[1] + a[3][2] * v[2] + a[3][3] * v[3]
);
}
WWINLINE void Matrix4x4::Transform_Vector(const Matrix4x4 & A,const Vector3 & in,Vector3 * out)
{
Vector3 tmp;
Vector3 * v;
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
WWINLINE void Matrix4x4::Transform_Vector(const Matrix4x4 & A,const Vector3 & in,Vector4 * out)
{
out->X = (A[0][0] * in.X + A[0][1] * in.Y + A[0][2] * in.Z + A[0][3]);
out->Y = (A[1][0] * in.X + A[1][1] * in.Y + A[1][2] * in.Z + A[1][3]);
out->Z = (A[2][0] * in.X + A[2][1] * in.Y + A[2][2] * in.Z + A[2][3]);
out->W = 1.0f;
}
WWINLINE void	Matrix4x4::Transform_Vector(const Matrix4x4 & A,const Vector4 & in,Vector4 * out)
{
Vector4 tmp;
Vector4 * v;
if (out == &in) {
tmp = in;
v = &tmp;
} else {
v = (Vector4 *)&in;
}
out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z + A[0][3] * v->W);
out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z + A[1][3] * v->W);
out->Z = (A[2][0] * v->X + A[2][1] * v->Y + A[2][2] * v->Z + A[2][3] * v->W);
out->W = (A[3][0] * v->X + A[3][1] * v->Y + A[3][2] * v->Z + A[3][3] * v->W);
}
#endif
#if defined(_MSC_VER)
#pragma once
#endif
#ifndef DX8_FVF_H
#define DX8_FVF_H
#include "always.h"
#include <d3d8.h>
#ifdef WWDEBUG
#include "wwdebug.h"
#endif
class StringClass;
enum {
DX8_FVF_XYZ				= D3DFVF_XYZ,
DX8_FVF_XYZN			= D3DFVF_XYZ|D3DFVF_NORMAL,
DX8_FVF_XYZNUV1		= D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1,
DX8_FVF_XYZNUV2		= D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2,
DX8_FVF_XYZNDUV1		= D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1|D3DFVF_DIFFUSE,
DX8_FVF_XYZNDUV2		= D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2|D3DFVF_DIFFUSE,
DX8_FVF_XYZDUV1		= D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_DIFFUSE,
DX8_FVF_XYZDUV2		= D3DFVF_XYZ|D3DFVF_TEX2|D3DFVF_DIFFUSE,
DX8_FVF_XYZUV1			= D3DFVF_XYZ|D3DFVF_TEX1,
DX8_FVF_XYZUV2			= D3DFVF_XYZ|D3DFVF_TEX2,
DX8_FVF_XYZNDUV1TG3	= (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX4|D3DFVF_TEXCOORDSIZE2(0)|D3DFVF_TEXCOORDSIZE3(1)|D3DFVF_TEXCOORDSIZE3(2)|D3DFVF_TEXCOORDSIZE3(3)),
DX8_FVF_XYZNUV2DMAP	= (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX3 | D3DFVF_TEXCOORDSIZE1(0) | D3DFVF_TEXCOORDSIZE4(1) | D3DFVF_TEXCOORDSIZE2(2) ),
DX8_FVF_XYZNDCUBEMAP	= D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE
};
struct VertexFormatXYZ
{
float x;
float y;
float z;
};
struct VertexFormatXYZNUV1
{
float x;
float y;
float z;
float nx;
float ny;
float nz;
float u1;
float v1;
};
struct VertexFormatXYZNUV2
{
float x;
float y;
float z;
float nx;
float ny;
float nz;
float u1;
float v1;
float u2;
float v2;
};
struct VertexFormatXYZN
{
float x;
float y;
float z;
float nx;
float ny;
float nz;
};
struct VertexFormatXYZNDUV1
{
float x;
float y;
float z;
float nx;
float ny;
float nz;
unsigned diffuse;
float u1;
float v1;
};
struct VertexFormatXYZNDUV2
{
float x;
float y;
float z;
float nx;
float ny;
float nz;
unsigned diffuse;
float u1;
float v1;
float u2;
float v2;
};
struct VertexFormatXYZDUV1
{
float x;
float y;
float z;
unsigned diffuse;
float u1;
float v1;
};
struct VertexFormatXYZDUV2
{
float x;
float y;
float z;
unsigned diffuse;
float u1;
float v1;
float u2;
float v2;
};
struct VertexFormatXYZUV1
{
float x;
float y;
float z;
float u1;
float v1;
};
struct VertexFormatXYZUV2
{
float x;
float y;
float z;
float u1;
float v1;
float u2;
float v2;
};
struct VertexFormatXYZNDUV1TG3
{
float x;
float y;
float z;
float nx;
float ny;
float nz;
unsigned diffuse;
float u1;
float v1;
float Sx;
float Sy;
float Sz;
float Tx;
float Ty;
float Tz;
float SxTx;
float SxTy;
float SxTz;
};
struct VertexFormatXYZNUV2DMAP
{
float x;
float y;
float z;
float nx;
float ny;
float nz;
float T1x;
float T1y;
float T1z;
float T1w;
float T2x;
float T2y;
};
struct VertexFormatXYZNDCUBEMAP
{
float x;
float y;
float z;
float nx;
float ny;
float nz;
unsigned diffuse;
};
class FVFInfoClass : public W3DMPO
{
W3DMPO_GLUE(FVFInfoClass)
mutable unsigned						FVF;
bool AdditionalBasis;
unsigned ExtensionCount;
mutable unsigned						fvf_size;
unsigned							location_offset;
unsigned							normal_offset;
unsigned							blend_offset;
unsigned target_unknown_1c_20[2];
unsigned							texcoord_offset[D3DDP_MAXTEXCOORD];
unsigned							diffuse_offset;
unsigned							specular_offset;
public:
FVFInfoClass(unsigned FVF, unsigned vertex_size=0);
inline unsigned Get_Location_Offset() const { return location_offset; }
inline unsigned Get_Normal_Offset() const { return normal_offset; }
#ifdef WWDEBUG
inline unsigned Get_Tex_Offset(unsigned int n) const { WWASSERT(n<D3DDP_MAXTEXCOORD); return texcoord_offset[n]; }
#else
inline unsigned Get_Tex_Offset(unsigned int n) const { return texcoord_offset[n]; }
#endif
inline unsigned Get_Diffuse_Offset() const { return diffuse_offset; }
inline unsigned Get_Specular_Offset() const { return specular_offset; }
inline unsigned Get_FVF() const { return FVF; }
inline unsigned Get_FVF_Size() const { return fvf_size; }
void Get_FVF_Name(StringClass& fvfname) const;
inline void Set_FVF(unsigned fvf) const { FVF=fvf; }
inline void Set_FVF_Size(unsigned size) const { fvf_size=size; }
};
#endif
#if defined(_MSC_VER)
#pragma once
#endif
#ifndef DX8VERTEXBUFFER_H
#define DX8VERTEXBUFFER_H
#include "always.h"
#include "wwdebug.h"
#include "refcount.h"
#include "dx8fvf.h"
const unsigned dynamic_fvf_type=D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2|D3DFVF_DIFFUSE;
class DX8Wrapper;
class SortingRendererClass;
class Vector2;
class Vector3;
class Vector4;
class StringClass;
class DX8VertexBufferClass;
class FVFInfoClass;
struct IDirect3DVertexBuffer8;
class VertexBufferClass;
struct VertexFormatXYZNDUV2;
class VertexBufferLockClass
{
protected:
VertexBufferClass* VertexBuffer;
void* Vertices;
VertexBufferLockClass(VertexBufferClass* vertex_buffer_) : VertexBuffer(vertex_buffer_) {}
public:
void* Get_Vertex_Array() { return Vertices; }
};
class VertexBufferClass : public W3DMPO, public RefCountClass
{
protected:
VertexBufferClass(unsigned type, unsigned FVF, unsigned short VertexCount, unsigned vertex_size=0);
virtual ~VertexBufferClass() throw();
public:
inline const FVFInfoClass& FVF_Info() const { return *fvf_info; }
inline unsigned short Get_Vertex_Count() const { return VertexCount; }
inline unsigned Type() const { return type; }
void Add_Engine_Ref() const;
void Release_Engine_Ref() const;
inline unsigned Engine_Refs() const { return engine_refs; }
class WriteLockClass : public VertexBufferLockClass
{
public:
WriteLockClass(VertexBufferClass* vertex_buffer, int flags=0);
__declspec(noinline) ~WriteLockClass();
};
class AppendLockClass : public VertexBufferLockClass
{
public:
AppendLockClass(VertexBufferClass* vertex_buffer,unsigned start_index, unsigned index_range, int flags=0);
__declspec(noinline) ~AppendLockClass();
};
static unsigned Get_Total_Buffer_Count();
static unsigned Get_Total_Allocated_Vertices();
static unsigned Get_Total_Allocated_Memory();
protected:
unsigned							type;
unsigned short					VertexCount;
mutable int						engine_refs;
FVFInfoClass*					fvf_info;
bool								m_BFMEExplicitVertexSize;
unsigned char					m_BFMEPadding[3];
};
class DynamicVBAccessClass
{
friend DX8Wrapper;
friend SortingRendererClass;
const FVFInfoClass& FVFInfo;
unsigned Type;
unsigned FormatIndex;
unsigned Declaration;
unsigned short VertexCount;
unsigned short VertexBufferOffset;
VertexBufferClass* VertexBuffer;
void Allocate_Sorting_Dynamic_Buffer();
void Allocate_DX8_Dynamic_Buffer();
public:
DynamicVBAccessClass(unsigned type,unsigned format_index,unsigned short vertex_count,unsigned declaration);
~DynamicVBAccessClass();
const FVFInfoClass& FVF_Info() const { return FVFInfo; }
unsigned Get_Type() const { return Type; }
unsigned short Get_Vertex_Count() const { return VertexCount; }
static void _Deinit();
static void _Reset(bool frame_changed);
static unsigned short Get_Default_Vertex_Count(void);
class WriteLock
{
DynamicVBAccessClass* DynamicVBAccess;
VertexFormatXYZNDUV2 * Vertices;
unsigned char DeviceGuard;
public:
WriteLock(DynamicVBAccessClass* vb_access);
~WriteLock();
VertexFormatXYZNDUV2 * Get_Formatted_Vertex_Array();
};
friend WriteLock;
};
inline VertexFormatXYZNDUV2 * DynamicVBAccessClass::WriteLock::Get_Formatted_Vertex_Array()
{
WWASSERT(DynamicVBAccess->VertexBuffer->FVF_Info().Get_FVF() == (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2|D3DFVF_DIFFUSE));
return Vertices;
}
class DX8VertexBufferClass : public VertexBufferClass
{
protected:
~DX8VertexBufferClass();
public:
enum UsageType {
USAGE_DEFAULT=0,
USAGE_DYNAMIC=1,
USAGE_SOFTWAREPROCESSING=2,
USAGE_NPATCHES=4
};
DX8VertexBufferClass(unsigned FVF, unsigned short VertexCount, UsageType usage=USAGE_DEFAULT, unsigned vertex_size=0);
DX8VertexBufferClass(const Vector3* vertices, const Vector3* normals, const Vector2* tex_coords, unsigned short VertexCount,UsageType usage=USAGE_DEFAULT);
DX8VertexBufferClass(const Vector3* vertices, const Vector3* normals, const Vector4* diffuse, const Vector2* tex_coords, unsigned short VertexCount,UsageType usage=USAGE_DEFAULT);
DX8VertexBufferClass(const Vector3* vertices, const Vector4* diffuse, const Vector2* tex_coords, unsigned short VertexCount,UsageType usage=USAGE_DEFAULT);
DX8VertexBufferClass(const Vector3* vertices, const Vector2* tex_coords, unsigned short VertexCount,UsageType usage=USAGE_DEFAULT);
IDirect3DVertexBuffer8* Get_DX8_Vertex_Buffer() { return VertexBuffer; }
void Copy(const Vector3* loc, unsigned first_vertex, unsigned count);
void Copy(const Vector3* loc, const Vector2* uv, unsigned first_vertex, unsigned count);
void Copy(const Vector3* loc, const Vector3* norm, unsigned first_vertex, unsigned count);
void Copy(const Vector3* loc, const Vector3* norm, const Vector2* uv, unsigned first_vertex, unsigned count);
void Copy(const Vector3* loc, const Vector3* norm, const Vector2* uv, const Vector4* diffuse, unsigned first_vertex, unsigned count);
void Copy(const Vector3* loc, const Vector2* uv, const Vector4* diffuse, unsigned first_vertex, unsigned count);
protected:
IDirect3DVertexBuffer8*		VertexBuffer;
void Create_Vertex_Buffer(UsageType usage);
};
class SortingVertexBufferClass : public VertexBufferClass
{
friend DX8Wrapper;
friend SortingRendererClass;
friend VertexBufferClass::WriteLockClass;
friend VertexBufferClass::AppendLockClass;
friend DynamicVBAccessClass::WriteLock;
VertexFormatXYZNDUV2* VertexBuffer;
protected:
~SortingVertexBufferClass() throw();
public:
SortingVertexBufferClass(unsigned short VertexCount);
};
#endif
#if defined(_MSC_VER)
#pragma once
#endif
#ifndef DX8INDEXBUFFER_H
#define DX8INDEXBUFFER_H
#include "always.h"
#include "wwdebug.h"
#include "refcount.h"
#include "sphere.h"
class DX8Wrapper;
class SortingRendererClass;
struct IDirect3DIndexBuffer8;
class DX8IndexBufferClass;
class SortingIndexBufferClass;
class IndexBufferClass : public W3DMPO, public RefCountClass
{
protected:
virtual ~IndexBufferClass();
public:
IndexBufferClass(unsigned type, unsigned index_count);
void Copy(unsigned int* indices,unsigned start_index,unsigned index_count);
void Copy(unsigned short* indices,unsigned start_index,unsigned index_count);
inline unsigned Get_Index_Count() const { return index_count; }
inline unsigned Type() const { return type; }
void Add_Engine_Ref() const;
void Release_Engine_Ref() const;
inline unsigned Engine_Refs() const { return engine_refs; }
class WriteLockClass
{
IndexBufferClass* index_buffer;
unsigned short* indices;
public:
WriteLockClass(IndexBufferClass* index_buffer, int flags=0);
~WriteLockClass();
unsigned short* Get_Index_Array() { return indices; }
};
class AppendLockClass
{
IndexBufferClass* index_buffer;
unsigned short* indices;
public:
AppendLockClass(IndexBufferClass* index_buffer,unsigned start_index, unsigned index_range);
~AppendLockClass();
unsigned short* Get_Index_Array() { return indices; }
};
static unsigned Get_Total_Buffer_Count();
static unsigned Get_Total_Allocated_Indices();
static unsigned Get_Total_Allocated_Memory();
protected:
mutable int					engine_refs;
unsigned					index_count;
unsigned						type;
};
class DynamicIBAccessClass : public W3DMPO
{
W3DMPO_GLUE(DynamicIBAccessClass)
friend DX8Wrapper;
friend SortingRendererClass;
unsigned Type;
unsigned short IndexCount;
unsigned short IndexBufferOffset;
IndexBufferClass* IndexBuffer;
void Allocate_Sorting_Dynamic_Buffer();
void Allocate_DX8_Dynamic_Buffer();
public:
DynamicIBAccessClass(unsigned short type, unsigned short index_count);
~DynamicIBAccessClass();
unsigned Get_Type() const { return Type; }
unsigned short Get_Index_Count() const { return IndexCount; }
static void _Deinit();
static void _Reset(bool frame_changed);
static unsigned short Get_Default_Index_Count(void);
class WriteLockClass
{
DynamicIBAccessClass* DynamicIBAccess;
unsigned short* Indices;
unsigned char DeviceGuard;
public:
WriteLockClass(DynamicIBAccessClass* ib_access);
~WriteLockClass();
unsigned short* Get_Index_Array() { return Indices; }
};
friend WriteLockClass;
};
class DX8IndexBufferClass : public IndexBufferClass
{
friend IndexBufferClass::WriteLockClass;
friend IndexBufferClass::AppendLockClass;
public:
enum UsageType {
USAGE_DEFAULT=0,
USAGE_DYNAMIC=1,
USAGE_SOFTWAREPROCESSING=2,
USAGE_NPATCHES=4
};
DX8IndexBufferClass(unsigned short index_count,UsageType usage=USAGE_DEFAULT);
#ifdef BFME_DYNAMIC_IB_UINT_CTOR_ABI
DX8IndexBufferClass(unsigned index_count,UsageType usage);
#endif
~DX8IndexBufferClass();
void Copy(unsigned int* indices,unsigned start_index,unsigned index_count);
void Copy(unsigned short* indices,unsigned start_index,unsigned index_count);
inline IDirect3DIndexBuffer8* Get_DX8_Index_Buffer()	{ return index_buffer; }
private:
IDirect3DIndexBuffer8*	index_buffer;
};
class SortingIndexBufferClass : public IndexBufferClass
{
friend DX8Wrapper;
friend SortingRendererClass;
friend IndexBufferClass::WriteLockClass;
friend IndexBufferClass::AppendLockClass;
friend DynamicIBAccessClass::WriteLockClass;
public:
SortingIndexBufferClass(unsigned short index_count);
~SortingIndexBufferClass();
protected:
unsigned short* index_buffer;
};
extern int IndexBufferExceptionFunc(void);
#endif
#include "rendobj.h"
#include "seglinerenderer.h"
#include "ww3d.h"
class CameraClass;
#include "rinfo.h"
#include "dx8wrapper.h"
#include "sortingrenderer.h"
#include "vp.h"
#include "vector3i.h"
#define BFME_RANDOM3CLASS_CTOR_NOINLINE
#include "random.h"
#include "v3_rnd.h"
#include "meshgeometry.h"
#ifndef W3D_ELINE_TILED_TEXTURE_MAP
#define W3D_ELINE_MERGE_INTERSECTIONS 				0x00000001
#define W3D_ELINE_FREEZE_RANDOM						0x00000002
#define W3D_ELINE_DISABLE_SORTING					0x00000004
#define W3D_ELINE_END_CAPS 							0x00000008
#define W3D_ELINE_TEXTURE_MAP_MODE_MASK 			0xFF000000
#define W3D_ELINE_TEXTURE_MAP_MODE_OFFSET 		24
#define W3D_ELINE_UNIFORM_WIDTH_TEXTURE_MAP		0x00000000
#define W3D_ELINE_UNIFORM_LENGTH_TEXTURE_MAP 	0x00000001
#define W3D_ELINE_TILED_TEXTURE_MAP					0x00000002
#define W3D_ELINE_DEFAULT_BITS	(W3D_ELINE_MERGE_INTERSECTIONS | (W3D_ELINE_UNIFORM_WIDTH_TEXTURE_MAP << W3D_ELINE_TEXTURE_MAP_MODE_OFFSET))
struct W3dEmitterLinePropertiesStruct
{
uint32			Flags;
uint32			SubdivisionLevel;
float32			NoiseAmplitude;
float32			MergeAbortFactor;
float32			TextureTileFactor;
float32			UPerSec;
float32			VPerSec;
uint32			Reserved[9];
};
#endif
#if MAX_SEGLINE_SUBDIV_LEVELS > 7
#define SEGLINE_CHUNK_SIZE (1 << MAX_SEGLINE_SUBDIV_LEVELS)
#else
#define SEGLINE_CHUNK_SIZE (128)
#endif
#ifdef _INTERNAL
#endif
#define MAX_SEGLINE_POINT_BUFFER_SIZE (1 + SEGLINE_CHUNK_SIZE)
#define MAX_SEGLINE_POLY_BUFFER_SIZE (SEGLINE_CHUNK_SIZE * 2)
struct BFME2TextureRef {TextureClass *ptr;};
void BFME2Set_Texture(unsigned,const BFME2TextureRef &);
void SegLineRendererClass::Render
(
RenderInfoClass & rinfo,
const Matrix3D & transform,
unsigned int num_points,
Vector3 * points,
const SphereClass & obj_sphere,
Vector4 * rgbas
)
{
Matrix4x4 view;
DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
Matrix4x4 identity(true);
DX8Wrapper::Set_Transform(D3DTS_WORLD,identity);
DX8Wrapper::Set_Transform(D3DTS_VIEW,identity);
unsigned int delta = WW3D::Get_Sync_Time() - LastUsedSyncTime;
float del = (float)delta;
Vector2 uv_offset = CurrentUVOffset + UVOffsetDeltaPerMS * del;
uv_offset.X = uv_offset.X - floorf(uv_offset.X);
uv_offset.Y = uv_offset.Y - floorf(uv_offset.Y);
CurrentUVOffset = uv_offset;
LastUsedSyncTime = WW3D::Get_Sync_Time();
TextureMapMode map_mode = Get_Texture_Mapping_Mode();
const float parallel_factor = 0.9f;
unsigned int chunk_size = (SEGLINE_CHUNK_SIZE >> SubdivisionLevel) + 1;
if (chunk_size > num_points) chunk_size = num_points;
for (unsigned int chidx = 0; chidx < num_points - 1; chidx += (chunk_size - 1)) {
unsigned int point_cnt = num_points - chidx;
point_cnt = MIN(point_cnt, chunk_size);
unsigned int pidx;
unsigned int sidx;
unsigned int iidx;
Vector3 xformed_pts[MAX_SEGLINE_POINT_BUFFER_SIZE];
Matrix3D view2(	view[0].X,view[0].Y,view[0].Z,view[0].W,
view[1].X,view[1].Y,view[1].Z,view[1].W,
view[2].X,view[2].Y,view[2].Z,view[2].W);
#ifdef ALLOW_TEMPORARIES
Matrix3D modelview=view2*transform;
#else
Matrix3D modelview;
modelview.mul(view2, transform);
#endif
VectorProcessorClass::Transform(&xformed_pts[0],
&points[chidx], modelview, point_cnt);
float base_tex_v[MAX_SEGLINE_POINT_BUFFER_SIZE];
float u_values[2];
switch (map_mode) {
case UNIFORM_WIDTH_TEXTURE_MAP:
for (pidx = 0; pidx < point_cnt; pidx++) {
base_tex_v[pidx] = 0.0f;
}
u_values[0] = 0.0f;
u_values[1] = 1.0f;
break;
case UNIFORM_LENGTH_TEXTURE_MAP:
for (pidx = 0; pidx < point_cnt; pidx++) {
base_tex_v[pidx] = (float)(pidx + chidx) * TextureTileFactor;
}
u_values[0] = 0.0f;
u_values[1] = 0.0f;
break;
default:
case TILED_TEXTURE_MAP:
for (pidx = 0; pidx < point_cnt; pidx++) {
base_tex_v[pidx] = (float)(pidx + chidx) * TextureTileFactor;
}
u_values[0] = 0.0f;
u_values[1] = 1.0f;
break;
}
Vector3 xformed_subdiv_pts[MAX_SEGLINE_POINT_BUFFER_SIZE];
float subdiv_tex_v[MAX_SEGLINE_POINT_BUFFER_SIZE];
Vector4 subdiv_rgbas[MAX_SEGLINE_POINT_BUFFER_SIZE];
unsigned int sub_point_cnt;
Vector4 *rgbasPointer = rgbas ? &rgbas[ chidx ] : NULL;
subdivision_util(point_cnt, xformed_pts, base_tex_v, &sub_point_cnt, xformed_subdiv_pts, subdiv_tex_v, rgbasPointer, subdiv_rgbas);
Vector3 *points = xformed_subdiv_pts;
float *tex_v = subdiv_tex_v;
Vector4 *diffuse = subdiv_rgbas;
point_cnt = sub_point_cnt;
enum SegmentEdge {
FIRST_EDGE     = 0,
TOP_EDGE			= 0,
BOTTOM_EDGE		= 1,
MAX_EDGE			= 1,
NUM_EDGES		= 2
};
bool switch_edges = false;
struct LineSegment {
Vector3	StartPlane;
Vector3	EdgePlane[NUM_EDGES];
};
LineSegment segment[MAX_SEGLINE_POINT_BUFFER_SIZE + 1];
struct LineSegmentIntersection  {
unsigned int	PointCount;
unsigned int	NextSegmentID;
Vector3			Direction;
Vector3			Point;
float				TexV;
Vector4			RGBA;
bool				Fold;
bool				Parallel;
};
float radius = Width * 0.5f;
LineSegmentIntersection intersection[MAX_SEGLINE_POINT_BUFFER_SIZE + 1][NUM_EDGES];
for (sidx = 1; sidx < point_cnt; sidx++) {
Vector3 &curr_point = points[sidx - 1];
Vector3 &next_point = points[sidx];
if (Equal_Within_Epsilon(curr_point, next_point, 0.0001f))
{
next_point.X += 0.001f;
}
Vector3 &segdir = segment[sidx].StartPlane;
segdir = next_point - curr_point;
segdir.Normalize();
Vector3 nearest = curr_point + segdir * -Vector3::Dot_Product(segdir, curr_point);
Vector3 offset;
Vector3::Cross_Product(segdir, nearest, &offset);
offset.Normalize();
Vector3 top = curr_point + offset * radius;
Vector3 bottom = curr_point + offset * -radius;
Vector3 top_normal;
Vector3::Cross_Product(top, segdir, &top_normal);
top_normal.Normalize();
segment[sidx].EdgePlane[TOP_EDGE] = top_normal;
Vector3 bottom_normal;
Vector3::Cross_Product(segdir, bottom, &bottom_normal);
bottom_normal.Normalize();
segment[sidx].EdgePlane[BOTTOM_EDGE] = bottom_normal;
if (sidx > 1) {
Vector3 prev_plane;
Vector3::Cross_Product(points[sidx - 2], curr_point, &prev_plane);
prev_plane.Normalize();
Vector3 curr_plane;
Vector3::Cross_Product(curr_point, next_point, &curr_plane);
curr_plane.Normalize();
if (Vector3::Dot_Product(prev_plane, curr_plane) < 0.0f) {
switch_edges = !switch_edges;
intersection[sidx][TOP_EDGE].Fold = true;
intersection[sidx][BOTTOM_EDGE].Fold = true;
} else {
intersection[sidx][TOP_EDGE].Fold = false;
intersection[sidx][BOTTOM_EDGE].Fold = false;
}
}
if (switch_edges) {
segment[sidx].EdgePlane[TOP_EDGE] = -bottom_normal;
segment[sidx].EdgePlane[BOTTOM_EDGE] = -top_normal;
}
}
unsigned int numsegs = point_cnt - 1;
unsigned int num_intersections[NUM_EDGES];
num_intersections[TOP_EDGE] = point_cnt;
num_intersections[BOTTOM_EDGE] = point_cnt;
intersection[0][TOP_EDGE].PointCount = 0;
intersection[0][TOP_EDGE].NextSegmentID = 0;
intersection[0][TOP_EDGE].Direction.Set(1,0,0);
intersection[0][TOP_EDGE].Point.Set(0,0,0);
intersection[0][TOP_EDGE].TexV = 0.0f;
intersection[0][TOP_EDGE].RGBA.Set(0, 0, 0, 0);
intersection[0][TOP_EDGE].Fold = true;
intersection[0][TOP_EDGE].Parallel = false;
intersection[0][BOTTOM_EDGE].PointCount = 0;
intersection[0][BOTTOM_EDGE].NextSegmentID = 0;
intersection[0][BOTTOM_EDGE].Point.Set(0,0,0);
intersection[0][BOTTOM_EDGE].TexV = 0.0f;
intersection[0][BOTTOM_EDGE].RGBA.Set(0, 0, 0, 0);
intersection[0][BOTTOM_EDGE].Direction.Set(1,0,0);
intersection[0][BOTTOM_EDGE].Fold = true;
intersection[0][BOTTOM_EDGE].Parallel = false;
intersection[1][TOP_EDGE].PointCount = 1;
intersection[1][TOP_EDGE].NextSegmentID = 1;
intersection[1][TOP_EDGE].Point = points[0];
intersection[1][TOP_EDGE].TexV = tex_v[0];
intersection[1][TOP_EDGE].RGBA = diffuse[0];
intersection[1][TOP_EDGE].Fold = true;
intersection[1][TOP_EDGE].Parallel = false;
intersection[1][BOTTOM_EDGE].PointCount = 1;
intersection[1][BOTTOM_EDGE].NextSegmentID = 1;
intersection[1][BOTTOM_EDGE].Point = points[0];
intersection[1][BOTTOM_EDGE].TexV = tex_v[0];
intersection[1][BOTTOM_EDGE].RGBA = diffuse[0];
intersection[1][BOTTOM_EDGE].Fold = true;
intersection[1][BOTTOM_EDGE].Parallel = false;
Vector3 top;
Vector3 bottom;
Vector3 &first_point = points[0];
Vector3 *first_plane = &(segment[1].EdgePlane[0]);
top = first_point - first_plane[TOP_EDGE] * Vector3::Dot_Product(first_plane[TOP_EDGE], first_point);
top.Normalize();
intersection[1][TOP_EDGE].Direction = top;
bottom = first_point - first_plane[BOTTOM_EDGE] * Vector3::Dot_Product(first_plane[BOTTOM_EDGE], first_point);
bottom.Normalize();
intersection[1][BOTTOM_EDGE].Direction = bottom;
Vector3 segdir = points[1] - points[0];
segdir.Normalize();
Vector3 start_pl;
Vector3::Cross_Product(top, bottom, &start_pl);
start_pl.Normalize();
float dp = Vector3::Dot_Product(segdir, start_pl);
if (dp > 0.0f) {
segment[0].StartPlane = segment[0].EdgePlane[TOP_EDGE] = segment[0].EdgePlane[BOTTOM_EDGE] = start_pl;
} else {
segment[0].StartPlane = segment[0].EdgePlane[TOP_EDGE] = segment[0].EdgePlane[BOTTOM_EDGE] = -start_pl;
}
segment[1].StartPlane = segment[0].StartPlane;
unsigned int last_isec = num_intersections[TOP_EDGE];
intersection[last_isec][TOP_EDGE].PointCount = 1;
intersection[last_isec][TOP_EDGE].NextSegmentID = numsegs + 1;
intersection[last_isec][TOP_EDGE].Point = points[point_cnt - 1];
intersection[last_isec][TOP_EDGE].TexV = tex_v[point_cnt - 1];
intersection[last_isec][TOP_EDGE].RGBA = diffuse[point_cnt - 1];
intersection[last_isec][TOP_EDGE].Fold = true;
intersection[last_isec][TOP_EDGE].Parallel = false;
intersection[last_isec][BOTTOM_EDGE].PointCount = 1;
intersection[last_isec][BOTTOM_EDGE].NextSegmentID = numsegs + 1;
intersection[last_isec][BOTTOM_EDGE].Point = points[point_cnt - 1];
intersection[last_isec][BOTTOM_EDGE].TexV = tex_v[point_cnt - 1];
intersection[last_isec][BOTTOM_EDGE].RGBA = diffuse[point_cnt - 1];
intersection[last_isec][BOTTOM_EDGE].Fold = true;
intersection[last_isec][BOTTOM_EDGE].Parallel = false;
Vector3 &last_point = points[point_cnt - 1];
Vector3 *last_plane = &(segment[numsegs].EdgePlane[0]);
top = last_point - last_plane[TOP_EDGE] * Vector3::Dot_Product(last_plane[TOP_EDGE], last_point);
top.Normalize();
intersection[last_isec][TOP_EDGE].Direction = top;
bottom = last_point - last_plane[BOTTOM_EDGE] * Vector3::Dot_Product(last_plane[BOTTOM_EDGE], last_point);
bottom.Normalize();
intersection[last_isec][BOTTOM_EDGE].Direction = bottom;
segdir = points[point_cnt - 1] - points[point_cnt - 2];
segdir.Normalize();
Vector3::Cross_Product(top, bottom, &start_pl);
start_pl.Normalize();
dp = Vector3::Dot_Product(segdir, start_pl);
if (dp > 0.0f) {
segment[numsegs + 1].StartPlane = segment[numsegs + 1].EdgePlane[TOP_EDGE] =
segment[numsegs + 1].EdgePlane[BOTTOM_EDGE] = start_pl;
} else {
segment[numsegs + 1].StartPlane = segment[numsegs + 1].EdgePlane[TOP_EDGE] =
segment[numsegs + 1].EdgePlane[BOTTOM_EDGE] = -start_pl;
}
float vdp;
for (iidx = 2; iidx < num_intersections[TOP_EDGE]; iidx++) {
Vector3 &midpoint = points[iidx - 1];
float mid_tex_v = tex_v[iidx - 1];
Vector4 mid_diffuse = diffuse[iidx - 1];
intersection[iidx][TOP_EDGE].PointCount = 1;
intersection[iidx][TOP_EDGE].NextSegmentID = iidx;
intersection[iidx][TOP_EDGE].Point = midpoint;
intersection[iidx][TOP_EDGE].TexV = mid_tex_v;
intersection[iidx][TOP_EDGE].RGBA = mid_diffuse;
intersection[iidx][BOTTOM_EDGE].PointCount = 1;
intersection[iidx][BOTTOM_EDGE].NextSegmentID = iidx;
intersection[iidx][BOTTOM_EDGE].Point = midpoint;
intersection[iidx][BOTTOM_EDGE].TexV = mid_tex_v;
intersection[iidx][BOTTOM_EDGE].RGBA = mid_diffuse;
vdp = Vector3::Dot_Product(segment[iidx - 1].EdgePlane[TOP_EDGE], segment[iidx].EdgePlane[TOP_EDGE]);
if (fabs(vdp) < parallel_factor) {
Vector3::Cross_Product(segment[iidx - 1].EdgePlane[TOP_EDGE], segment[iidx].EdgePlane[TOP_EDGE],
&(intersection[iidx][TOP_EDGE].Direction));
intersection[iidx][TOP_EDGE].Direction.Normalize();
if (Vector3::Dot_Product(intersection[iidx][TOP_EDGE].Direction, midpoint) < 0.0f) {
intersection[iidx][TOP_EDGE].Direction = -intersection[iidx][TOP_EDGE].Direction;
}
intersection[iidx][TOP_EDGE].Parallel = false;
} else {
Vector3 pl;
if (vdp > 0.0f) {
pl = segment[iidx - 1].EdgePlane[TOP_EDGE] + segment[iidx].EdgePlane[TOP_EDGE];
} else {
pl = segment[iidx - 1].EdgePlane[TOP_EDGE] - segment[iidx].EdgePlane[TOP_EDGE];
}
pl.Normalize();
intersection[iidx][TOP_EDGE].Direction = midpoint - pl * Vector3::Dot_Product(pl, midpoint);
intersection[iidx][TOP_EDGE].Direction.Normalize();
intersection[iidx][TOP_EDGE].Parallel = true;
}
vdp = Vector3::Dot_Product(segment[iidx - 1].EdgePlane[BOTTOM_EDGE], segment[iidx].EdgePlane[BOTTOM_EDGE]);
if (fabs(vdp) < parallel_factor) {
Vector3::Cross_Product(segment[iidx - 1].EdgePlane[BOTTOM_EDGE], segment[iidx].EdgePlane[BOTTOM_EDGE],
&(intersection[iidx][BOTTOM_EDGE].Direction));
intersection[iidx][BOTTOM_EDGE].Direction.Normalize();
if (Vector3::Dot_Product(intersection[iidx][BOTTOM_EDGE].Direction, midpoint) < 0.0f) {
intersection[iidx][BOTTOM_EDGE].Direction = -intersection[iidx][BOTTOM_EDGE].Direction;
}
intersection[iidx][BOTTOM_EDGE].Parallel = false;
} else {
Vector3 pl;
if (vdp > 0.0f) {
pl = segment[iidx - 1].EdgePlane[BOTTOM_EDGE] + segment[iidx].EdgePlane[BOTTOM_EDGE];
} else {
pl = segment[iidx - 1].EdgePlane[BOTTOM_EDGE] - segment[iidx].EdgePlane[BOTTOM_EDGE];
}
pl.Normalize();
intersection[iidx][BOTTOM_EDGE].Direction = midpoint - pl * Vector3::Dot_Product(pl, midpoint);
intersection[iidx][BOTTOM_EDGE].Direction.Normalize();
intersection[iidx][BOTTOM_EDGE].Parallel = true;
}
Vector3::Cross_Product(intersection[iidx][TOP_EDGE].Direction, intersection[iidx][BOTTOM_EDGE].Direction, &start_pl);
start_pl.Normalize();
dp = Vector3::Dot_Product(segment[iidx].StartPlane, start_pl);
if (dp > 0.0f) {
segment[iidx].StartPlane = start_pl;
} else {
segment[iidx].StartPlane = -start_pl;
}
}
if (Is_Merge_Intersections()) {
unsigned int iidx_r;
unsigned int iidx_w;
bool merged = true;
while (merged) {
merged = false;
SegmentEdge edge;
for (edge = FIRST_EDGE; edge <= MAX_EDGE; edge = (SegmentEdge)((int)edge + 1)) {
unsigned int num_isects = num_intersections[edge];
for (iidx_r = 1, iidx_w = 1; iidx_r < num_isects; iidx_r++, iidx_w++) {
LineSegmentIntersection *curr_int = &(intersection[iidx_r][edge]);
LineSegmentIntersection *next_int = &(intersection[iidx_r + 1][edge]);
LineSegmentIntersection *write_int = &(intersection[iidx_w][edge]);
LineSegmentIntersection *prev_int = &(intersection[iidx_w - 1][edge]);
LineSegment *next_seg = &(segment[next_int->NextSegmentID]);
LineSegment *curr_seg = &(segment[curr_int->NextSegmentID]);
LineSegment *prev_seg = &(segment[prev_int->NextSegmentID]);
while	(	(!next_int->Fold &&
(Vector3::Dot_Product(curr_int->Direction, next_seg->StartPlane) > 0.0f) &&
(Vector3::Dot_Product(curr_int->Direction, next_seg->EdgePlane[edge]) > 0.0f )) ||
(!curr_int->Fold &&
(Vector3::Dot_Product(next_int->Direction, -curr_seg->StartPlane) > 0.0f) &&
(Vector3::Dot_Product(next_int->Direction, prev_seg->EdgePlane[edge]) > 0.0f )) ) {
unsigned int new_count = curr_int->PointCount + next_int->PointCount;
float oo_new_count = 1.0f / (float)new_count;
float curr_factor = oo_new_count * (float)curr_int->PointCount;
float next_factor = oo_new_count * (float)curr_int->PointCount;
Vector3 new_point = curr_int->Point * curr_factor + next_int->Point * next_factor;
float new_tex_v = curr_int->TexV * curr_factor + next_int->TexV * next_factor;
Vector4 new_diffuse = curr_int->RGBA * curr_factor + next_int->RGBA * next_factor;
bool new_parallel;
Vector3 new_direction;
vdp = Vector3::Dot_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge]);
if (fabs(vdp) < parallel_factor) {
Vector3::Cross_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge], &new_direction);
new_direction.Normalize();
if (Vector3::Dot_Product(new_direction, new_point) < 0.0f) {
new_direction = -new_direction;
}
new_parallel = false;
} else {
Vector3 pl;
if (vdp > 0.0f) {
pl = prev_seg->EdgePlane[edge] + next_seg->EdgePlane[edge];
} else {
pl = prev_seg->EdgePlane[edge] - next_seg->EdgePlane[edge];
}
pl.Normalize();
if (curr_int->Parallel) {
new_direction = new_direction - pl * Vector3::Dot_Product(pl, new_direction);
new_direction.Normalize();
} else {
Vector3::Cross_Product(curr_seg->EdgePlane[edge], pl, &new_direction);
new_direction.Normalize();
}
new_parallel = true;
}
if (MergeAbortFactor > 0.0f) {
float abort_dist = radius * MergeAbortFactor;
float abort_dist2 = abort_dist * abort_dist;
Vector3 diff_curr = curr_int->Point -
new_direction * Vector3::Dot_Product(curr_int->Point, new_direction);
if (diff_curr.Length2() > abort_dist2) break;
Vector3 next_curr = next_int->Point -
new_direction * Vector3::Dot_Product(next_int->Point, new_direction);
if (next_curr.Length2() > abort_dist2) break;
}
merged = true;
curr_int->Direction = new_direction;
curr_int->Parallel = new_parallel;
curr_int->Point = new_point;
curr_int->TexV = new_tex_v;
curr_int->RGBA = new_diffuse;
curr_int->PointCount = new_count;
curr_int->NextSegmentID = next_int->NextSegmentID;
curr_int->Fold = curr_int->Fold || next_int->Fold;
num_intersections[edge]--;
iidx_r++;
if (iidx_r == num_isects) {
break;
}
next_int = &(intersection[iidx_r + 1][edge]);
next_seg = &(segment[next_int->NextSegmentID]);
}
write_int->PointCount		= curr_int->PointCount;
write_int->NextSegmentID	= curr_int->NextSegmentID;
write_int->Point				= curr_int->Point;
write_int->TexV				= curr_int->TexV;
write_int->RGBA				= curr_int->RGBA;
write_int->Direction			= curr_int->Direction;
write_int->Fold				= curr_int->Fold;
}
if (iidx_r == num_isects) {
LineSegmentIntersection *write_int = &(intersection[iidx_w][edge]);
LineSegmentIntersection *curr_int = &(intersection[iidx_r][edge]);
write_int->PointCount		= curr_int->PointCount;
write_int->NextSegmentID	= curr_int->NextSegmentID;
write_int->Point				= curr_int->Point;
write_int->TexV				= curr_int->TexV;
write_int->RGBA				= curr_int->RGBA;
write_int->Direction			= curr_int->Direction;
write_int->Fold				= curr_int->Fold;
}
#ifdef ENABLE_WWDEBUGGING
unsigned int total_cnt = 0;
for (unsigned int nidx = 0; nidx <= num_intersections[edge]; nidx++) {
total_cnt += intersection[nidx][edge].PointCount;
}
assert(total_cnt == point_cnt);
#endif
}
}
}
unsigned int vnum = num_intersections[TOP_EDGE] + num_intersections[BOTTOM_EDGE];
VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum);
TriIndex v_index_array[MAX_SEGLINE_POLY_BUFFER_SIZE];
unsigned int vidx = 0;
unsigned int tidx = 0;
Vector3 &top_dir = intersection[1][TOP_EDGE].Direction;
top = top_dir * Vector3::Dot_Product(points[0], top_dir);
Vector3 &bottom_dir = intersection[1][BOTTOM_EDGE].Direction;
bottom = bottom_dir * Vector3::Dot_Product(points[0], bottom_dir);
vArray[vidx].x = top.X;
vArray[vidx].y = top.Y;
vArray[vidx].z = top.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[1][TOP_EDGE].RGBA);
vArray[vidx].u1 = u_values[0] + uv_offset.X;
vArray[vidx].v1 = intersection[1][TOP_EDGE].TexV + uv_offset.Y;
vidx++;
vArray[vidx].x = bottom.X;
vArray[vidx].y = bottom.Y;
vArray[vidx].z = bottom.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[1][BOTTOM_EDGE].RGBA);
vArray[vidx].u1 = u_values[1] + uv_offset.X;
vArray[vidx].v1 = intersection[1][BOTTOM_EDGE].TexV + uv_offset.Y;
vidx++;
unsigned int last_top_vidx = 0;
unsigned int last_bottom_vidx = 1;
unsigned int top_int_idx = 1;
unsigned int bottom_int_idx = 1;
pidx = 0;
unsigned int residual_top_points = intersection[1][TOP_EDGE].PointCount;
unsigned int residual_bottom_points = intersection[1][BOTTOM_EDGE].PointCount;
unsigned int delta = MIN(residual_top_points, residual_bottom_points) - 1;
residual_top_points -= delta;
residual_bottom_points -= delta;
pidx += delta;
for (; ; ) {
if (residual_top_points == 1 && residual_bottom_points == 1) {
v_index_array[tidx].I = last_top_vidx;
v_index_array[tidx].J = last_bottom_vidx;
v_index_array[tidx].K = vidx;
tidx++;
v_index_array[tidx].I = last_bottom_vidx;
v_index_array[tidx].J = vidx + 1;
v_index_array[tidx].K = vidx;
tidx++;
last_top_vidx = vidx;
last_bottom_vidx = vidx + 1;
top_int_idx++;
bottom_int_idx++;
residual_top_points = intersection[top_int_idx][TOP_EDGE].PointCount;
residual_bottom_points = intersection[bottom_int_idx][BOTTOM_EDGE].PointCount;
pidx++;
Vector3 &top_dir = intersection[top_int_idx][TOP_EDGE].Direction;
top = top_dir * Vector3::Dot_Product(points[pidx], top_dir);
Vector3 &bottom_dir = intersection[bottom_int_idx][BOTTOM_EDGE].Direction;
bottom = bottom_dir * Vector3::Dot_Product(points[pidx], bottom_dir);
vArray[vidx].x = top.X;
vArray[vidx].y = top.Y;
vArray[vidx].z = top.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[top_int_idx][TOP_EDGE].RGBA);
vArray[vidx].u1 = u_values[0] + uv_offset.X;
vArray[vidx].v1 = intersection[top_int_idx][TOP_EDGE].TexV + uv_offset.Y;
vidx++;
vArray[vidx].x = bottom.X;
vArray[vidx].y = bottom.Y;
vArray[vidx].z = bottom.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[bottom_int_idx][BOTTOM_EDGE].RGBA);
vArray[vidx].u1 = u_values[1] + uv_offset.X;
vArray[vidx].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV + uv_offset.Y;
vidx++;
} else {
if (residual_top_points > 1) {
v_index_array[tidx].I = last_top_vidx;
v_index_array[tidx].J = last_bottom_vidx;
v_index_array[tidx].K = vidx;
tidx++;
last_bottom_vidx = vidx;
residual_top_points--;
bottom_int_idx++;
residual_bottom_points = intersection[bottom_int_idx][BOTTOM_EDGE].PointCount;
pidx++;
Vector3 &bottom_dir = intersection[bottom_int_idx][BOTTOM_EDGE].Direction;
bottom = bottom_dir * Vector3::Dot_Product(points[pidx], bottom_dir);
vArray[vidx].x = bottom.X;
vArray[vidx].y = bottom.Y;
vArray[vidx].z = bottom.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[bottom_int_idx][BOTTOM_EDGE].RGBA);
vArray[vidx].u1 = u_values[1] + uv_offset.X;
vArray[vidx].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV + uv_offset.Y;
vidx++;
} else {
v_index_array[tidx].I = last_top_vidx;
v_index_array[tidx].J = last_bottom_vidx;
v_index_array[tidx].K = vidx;
tidx++;
last_top_vidx = vidx;
residual_bottom_points--;
top_int_idx++;
residual_top_points = intersection[top_int_idx][TOP_EDGE].PointCount;
pidx++;
Vector3 &top_dir = intersection[top_int_idx][TOP_EDGE].Direction;
top = top_dir * Vector3::Dot_Product(points[pidx], top_dir);
vArray[vidx].x = top.X;
vArray[vidx].y = top.Y;
vArray[vidx].z = top.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[top_int_idx][TOP_EDGE].RGBA);
vArray[vidx].u1 = u_values[0] + uv_offset.X;
vArray[vidx].v1 = intersection[top_int_idx][TOP_EDGE].TexV + uv_offset.Y;
vidx++;
}
}
delta = MIN(residual_top_points, residual_bottom_points) - 1;
residual_top_points -= delta;
residual_bottom_points -= delta;
pidx += delta;
if (	(top_int_idx >= num_intersections[TOP_EDGE] && residual_top_points == 1) ||
(bottom_int_idx >= num_intersections[BOTTOM_EDGE] && residual_bottom_points == 1)) {
assert(top_int_idx == num_intersections[TOP_EDGE]);
assert(bottom_int_idx == num_intersections[BOTTOM_EDGE]);
assert(pidx == point_cnt - 1);
break;
}
}
unsigned int rgba;
rgba=DX8Wrapper::Convert_Color(Color,Opacity);
bool rgba_all=(rgba==0xFFFFFFFF);
bool sorting = (!Is_Sorting_Disabled()) && (Shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO && Shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE);
ShaderClass shader = Shader;
shader.Set_Cull_Mode(ShaderClass::CULL_MODE_DISABLE);
VertexMaterialClass *mat;
if (!rgba_all || (rgba != 0) ) {
shader.Set_Primary_Gradient(ShaderClass::GRADIENT_MODULATE);
mat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
} else {
shader.Set_Primary_Gradient(ShaderClass::GRADIENT_DISABLE);
mat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_NODIFFUSE);
}
if (Texture) {
shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
} else {
shader.Set_Texturing(ShaderClass::TEXTURING_DISABLE);
}
DynamicVBAccessClass Verts((sorting?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8),5,vnum,0);
{
DynamicVBAccessClass::WriteLock Lock(&Verts);
unsigned int i;
unsigned char *vb=(unsigned char*)Lock.Get_Formatted_Vertex_Array();
const FVFInfoClass& fvfinfo=Verts.FVF_Info();
const unsigned int verticesOffset = fvfinfo.Get_Location_Offset();
const unsigned diffuseOffset = fvfinfo.Get_Diffuse_Offset();
const unsigned textureOffset = fvfinfo.Get_Tex_Offset(0);
const unsigned vbSize = fvfinfo.Get_FVF_Size();
for (i=0; i<vnum; i++)
{
Vector3 *vertex = reinterpret_cast<Vector3 *>(vb + verticesOffset);
vertex->X = vArray[i].x;
vertex->Y = vArray[i].y;
vertex->Z = vArray[i].z;
*reinterpret_cast<unsigned int *>(vb + diffuseOffset) = vArray[i].diffuse;
Vector2 *texture = reinterpret_cast<Vector2 *>(vb + textureOffset);
texture->U = vArray[i].u1;
texture->V = vArray[i].v1;
vb += vbSize;
}
}
DynamicIBAccessClass ib_access((sorting?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8),tidx*3);
{
unsigned int i;
DynamicIBAccessClass::WriteLockClass lock(&ib_access);
unsigned short* inds=lock.Get_Index_Array();
for (i=0; i<tidx; i++)
{
*inds++=v_index_array[i].I;
*inds++=v_index_array[i].J;
*inds++=v_index_array[i].K;
}
}
DX8Wrapper::Set_Index_Buffer(ib_access,0);
DX8Wrapper::Set_Vertex_Buffer(Verts);
DX8Wrapper::Set_Material(mat);
BFME2Set_Texture(0,*(const BFME2TextureRef *)&Texture);
DX8Wrapper::Set_Shader(shader);
if (sorting) {
SortingRendererClass::Insert_Triangles(obj_sphere,0,tidx,0,vnum);
} else {
DX8Wrapper::Draw_Triangles(0,tidx,0,vnum);
}
REF_PTR_RELEASE(mat);
}
DX8Wrapper::Set_Transform(D3DTS_VIEW,view);
}
VertexFormatXYZDUV1 *SegLineRendererClass::getVertexBuffer(unsigned int number)
{
if (number > m_vertexBufferSize)
{
unsigned int numberToAlloc = number + (number >> 1);
delete [] m_vertexBuffer;
m_vertexBuffer = W3DNEWARRAY VertexFormatXYZDUV1[numberToAlloc];
m_vertexBufferSize = numberToAlloc;
}
return m_vertexBuffer;
}
SegMatrixRow::SegMatrixRow() {}
