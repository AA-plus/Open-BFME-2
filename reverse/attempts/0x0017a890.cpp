// ?rva009148C0@PointGroupClass@@QAEXPAVVector3@@PAMPAEH@Z
// partial score=0.6 date=2026-10-13
// cl: /O2 /arch:SSE /G7 /DBFME_WWSTRING_CTOR_BUFFER_RELOAD /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/banked_segline /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Link view first: Vector4(x,y,z,w) stays inline without emitting an SSE
// copy that competes with retail's integer-move owner (0x006D8A30).
#include "../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
// ?rva00913AF0@PointGroupClass@@QAEXH_N@Z
// Full body byte-exact; integration remains blocked, so this is not progress.
// 2026-10-06 follow-up: bracketing ONLY Set_Shader's definition in
// reference/shims/banked_segline/dx8wrapper.h with pragma optimize("gsy", on)
// and optimize("", on) resolves its new COMDAT variant without changing
// this 3377-byte body. Set_Transform still conflicts. Its banked header has
// old projection handling; the bfmecamera implementation and existing
// DeviceProjectionMatrix declaration preserve this body but not its helper.
// Making all matrix inline dependencies size-optimized resolves the helper
// but shrinks this body to3266; narrowing to the four-vector constructor or
// Transpose does not resolve the helper. All trial header changes reverted.
// The sorting Insert provider at0x0012FE00 landed in6c063da4fc.
// PointGroup vertex-buffer submission, retail RVA 0x00179B50, 3377 bytes.
// Ported from Open-BFME-1 PointGroupClassSubmit.cpp at 6583b3c1ff;
// resumed bank from 2026-10-05. The donor provides the submission semantics
// and address-derived method name. BFME2 Render's call at RVA 0x0017F6C6
// proves this helper's receiver and two arguments independently.
// Target accesses prove the 24-byte VB access, 12-byte write lock and FVF
// offsets below. Ghidra's 3371-byte extent omits the final six-byte epilogue;
// retail ends at 0x0017A881, before padding to the next entry at 0x0017A890.
// BFME_WWSTRING_CTOR_BUFFER_RELOAD reproduces the target's inlined snapshot
// string constructor at 0x0017A025. Full body and relocations are verified.
#define Matrix4x4 Matrix4
// BFME1's pointgr.h lacks the BFME2 vertex-fill helper declaration, and
// renaming the header's class would re-mangle its static table members away
// from pointgr.cpp's definitions. Carry the landed layout TU-locally under
// the class's real name instead (same offsets the header produces; statics
// link against Code/Libraries/Source/WWVegas/WW3D2/pointgr.cpp).
#include "sharebuf.h"
#include "shader.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
class VertexMaterialClass;
class TextureClass;
class PointGroupClass
{
public:
	enum PointModeEnum {
		TRIS,
		QUADS,
		SCREENSPACE
	};

	enum FlagsType {
		TRANSFORM,
		// BFME drift: the second flag is the billboard toggle that replaced
		// the removed Billboard member (see the BFME1 header's drift note).
		BILLBOARD,
	};

	void rva00913AF0(int vnum, bool no_diffuse);
	void rva009148C0(Vector3 *point_loc, float *point_size, unsigned char *point_orientation,
		int active_points);

private:
	virtual void abstract_dtor(void);
	ShareBufferClass<Vector3> *PointLoc;
	ShareBufferClass<Vector4> *PointDiffuse;
	ShareBufferClass<unsigned int> *APT;
	ShareBufferClass<float> *PointSize;
	ShareBufferClass<unsigned char> *PointOrientation;
	ShareBufferClass<unsigned char> *PointFrame;
	int PointCount;
	unsigned char FrameRowColumnCountLog2;
	TextureClass *Texture;
	ShaderClass Shader;
	PointModeEnum PointMode;
	unsigned int Flags;
	float DefaultPointSize;
	Vector3 DefaultPointColor;
	float DefaultPointAlpha;
	unsigned char DefaultPointOrientation;
	unsigned char DefaultPointFrame;
	float VPXMin;
	float VPYMin;
	float VPXMax;
	float VPYMax;
	static Vector3 _TriVertexLocationOrientationTable[256][3];
	static Vector3 _QuadVertexLocationOrientationTable[256][4];
	static Vector3 _ScreenspaceVertexLocationSizeTable[2][3];
	static VertexMaterialClass *PointMaterial;
};
#include "vector.h"
#include "matrix4.h"
#include "dx8wrapper.h"
#include "ww3d.h"
#include "texture.h"
#include "vertmaterial.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "sortingrenderer.h"

extern VectorClass<Vector3> VertexLoc;
extern VectorClass<Vector2> VertexUV;
extern VectorClass<Vector4> VertexDiffuse;
extern DX8IndexBufferClass *Tris;
extern DX8IndexBufferClass *Quads;
extern SortingIndexBufferClass *SortingTris;
extern SortingIndexBufferClass *SortingQuads;
// Retail's second sorting flag at VA 0x00DB5F7D is owned by
// GlobalByteGetters.cpp; reuse that definition instead of the donor's name.
extern unsigned char g_Va00DB5F7D;

// D3DX rotation import: retail calls the local thunk _D3DXMatrixRotationZ@8
// at 0x0062AF5C (matched row, jmp [__imp__D3DXMatrixRotationZ]). The dx81 SDK
// header chain already declares D3DXMatrixRotationZ without dllimport, so the
// call is a direct REL32 to that thunk; nothing is declared here.

// Ground multipliers for the billboard-less quad rotation path (retail
// pointgr.cpp keeps these as file statics right after the screenspace table
// at 0x009B6500; retail's copies are unused there and never emitted).
static Vector3 GroundMultiplierX(1.0f, 0.0f, 0.0f);
static Vector3 GroundMultiplierY(0.0f, 1.0f, 0.0f);

// BFME2's FVF record: the stride, location, first texture-coordinate and
// diffuse offsets read here sit at +0x0C/+0x10/+0x24/+0x44 (retail 0x0017A2C5..
// 0x0017A2CE; Line3DClassRender.cpp reads the same stride/location/diffuse).
class PointGroupTargetFVF {
	char beforeStride[12];
	unsigned stride;
	unsigned location;
	char beforeTex[0x24 - 0x14];
	unsigned tex0;
	char beforeDiffuse[0x44 - 0x28];
	unsigned diffuse;

public:
	unsigned Get_FVF_Size() const { return stride; }
	unsigned Get_Location_Offset() const { return location; }
	unsigned Get_Tex_Offset(unsigned) const { return tex0; }
	unsigned Get_Diffuse_Offset() const { return diffuse; }
};

struct BfmeSortingVBAccess {
	const PointGroupTargetFVF &FVFInfo;
	unsigned Type;
	unsigned formatIndex;
	unsigned unused_0x0C;
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	class BoxVertexBufferClass *VertexBuffer;

	BfmeSortingVBAccess(unsigned type, unsigned format_index,
		unsigned short vertex_count, unsigned buffer);
	~BfmeSortingVBAccess();

	const PointGroupTargetFVF &FVF_Info() const { return FVFInfo; }

	class WriteLock {
		BfmeSortingVBAccess *DynamicVBAccess;
		VertexFormatXYZNDUV2 *Vertices;
		unsigned char targetDeviceGuard[4];

	public:
		WriteLock(BfmeSortingVBAccess *vb_access);
		~WriteLock();
		VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() { return Vertices; }
	};
};

extern void BoxSetTexture(unsigned stage, TextureBaseClass *&texture);

// Retail 0x0012FE00 takes an xyz center and four 32-bit ranges (the view
// DX8DrawTrianglesDispatch.cpp pins).
struct TargetCenter3 { float x, y, z; TargetCenter3(float a,float b,float c):x(a),y(b),z(c){} };
class BfmeSortingDispatchAt0012FE00 {
public:
	static void Insert(const TargetCenter3& center, unsigned start,
		unsigned polygons, unsigned minimum, unsigned vertices);
};

static __forceinline void InsertPointTriangles(
	unsigned a, unsigned b, unsigned c, unsigned d)
{
	TargetCenter3 center(0.0f, 0.0f, 0.0f);
	BfmeSortingDispatchAt0012FE00::Insert(center, a, b, c, d);
}

static __forceinline void ClampPointColor(Vector4 &color)
{
	if (!CPUDetectClass::Has_CMOV_Instruction()) {
		color.X = color.X <= 0.0f ? 0.0f : (color.X > 1.0f ? 1.0f : color.X);
		color.Y = color.Y <= 0.0f ? 0.0f : (color.Y > 1.0f ? 1.0f : color.Y);
		color.Z = color.Z <= 0.0f ? 0.0f : (color.Z > 1.0f ? 1.0f : color.Z);
		color.W = color.W <= 0.0f ? 0.0f : (color.W > 1.0f ? 1.0f : color.W);
		return;
	}

	// Retain the donor's bounded 94-byte CMOV implementation: VC7.1 emits
	// branches for the equivalent integer clamp expressions. The independently
	// matched BFME1 Clamp_Color at 0x0090F310 and its point-submit evidence
	// establish this codegen blocker; the surrounding algorithm is C++.
	__asm
	{
		mov esi, dword ptr color
		mov edx, 0x3f800000

		mov edi, dword ptr [esi]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi], edi

		mov edi, dword ptr [esi+4]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi+4], edi

		mov edi, dword ptr [esi+8]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi+8], edi

		mov edi, dword ptr [esi+12]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi+12], edi
	}
}

static __forceinline unsigned ConvertPointColor(Vector4 clamped_color)
{
	ClampPointColor(clamped_color);
	return DX8Wrapper::Convert_Color(
		reinterpret_cast<const Vector3 &>(clamped_color), clamped_color[3]);
}

static __forceinline unsigned ConvertDefaultPointColor(Vector4 color)
{
	ClampPointColor(color);
	return DX8Wrapper::Convert_Color(reinterpret_cast<const Vector3 &>(color), color.W);
}

void PointGroupClass::rva00913AF0(int vnum, bool no_diffuse)
{
	Matrix4 world, view;
	DX8Wrapper::Get_Transform(D3DTS_WORLD, world);
	DX8Wrapper::Get_Transform(D3DTS_VIEW, view);
	Matrix4 identity(true);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, identity);
	DX8Wrapper::Set_Transform(D3DTS_VIEW, identity);
	DX8Wrapper::Set_Material(PointMaterial);
	DX8Wrapper::Set_Shader(Shader);
	BoxSetTexture(0, reinterpret_cast<TextureBaseClass *&>(Texture));
	const bool sort = (Shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO)
		&& (Shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE)
		&& WW3D::Is_Sorting_Enabled() && g_Va00DB5F7D;
	IndexBufferClass *indexbuffer;
	int verticesperprimitive;
	if (PointMode == QUADS) {
		verticesperprimitive = 2;
		indexbuffer = sort ? static_cast<IndexBufferClass *>(SortingQuads)
			: static_cast<IndexBufferClass *>(Quads);
	} else {
		verticesperprimitive = 3;
		indexbuffer = sort ? static_cast<IndexBufferClass *>(SortingTris)
			: static_cast<IndexBufferClass *>(Tris);
	}
	unsigned default_color = ConvertDefaultPointColor(Vector4(
		DefaultPointColor.X, DefaultPointColor.Y, DefaultPointColor.Z, DefaultPointAlpha));
	int current = 0;
	while (current < vnum) {
		int delta = MIN(vnum - current, 2048);
		BfmeSortingVBAccess PointVerts(
			sort ? BUFFER_TYPE_DYNAMIC_SORTING : BUFFER_TYPE_DYNAMIC_DX8, 5, delta, 0);
		{
			BfmeSortingVBAccess::WriteLock Lock(&PointVerts);
			unsigned char *vb = (unsigned char *)Lock.Get_Formatted_Vertex_Array();
			const PointGroupTargetFVF &fvfinfo = PointVerts.FVF_Info();
			unsigned stride = fvfinfo.Get_FVF_Size();
			unsigned char *position = vb + fvfinfo.Get_Location_Offset();
			unsigned char *uv = vb + fvfinfo.Get_Tex_Offset(0);
			unsigned char *color = vb + fvfinfo.Get_Diffuse_Offset();
			if (no_diffuse) {
				for (int i = current; i < current + delta; i++) {
					*(Vector3 *)position = VertexLoc[i];
					*(Vector2 *)uv = VertexUV[i];
					*(unsigned *)color = default_color;
					position += stride;
					uv += stride;
					color += stride;
				}
			} else {
				for (int i = current; i < current + delta; i++) {
					*(Vector3 *)position = VertexLoc[i];
					*(Vector2 *)uv = VertexUV[i];
					*(unsigned *)color = ConvertPointColor(VertexDiffuse[i]);
					position += stride;
					uv += stride;
					color += stride;
				}
			}
		}
		DX8Wrapper::Set_Index_Buffer(indexbuffer, 0);
		DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass *>(&PointVerts));
		if (sort) {
			InsertPointTriangles(0, delta / verticesperprimitive, 0, delta);
		} else {
			DX8Wrapper::Draw_Triangles(0, delta / verticesperprimitive, 0, delta);
		}
		current += delta;
	}
	DX8Wrapper::Set_Transform(D3DTS_VIEW, view);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, world);
}

// PointGroupClass::rva009148C0 at retail 0x0017A890 (12000 bytes including the
// twelve-entry switch table; the 11909-byte queue truncates the last case and
// epilogue). The vertex location fill: BFME split the Zero Hour Update_Arrays
// vertex-position switch into this helper, called by Render 0x0017F400 at
// 0x0017F6C6 with (location, size, orientation, count).
void PointGroupClass::rva009148C0(Vector3 *point_loc, float *point_size,
	unsigned char *point_orientation, int active_points)
{
	int vert, i, j;

	// This defines the loop we run: the LSB indicates whether there is a size override array, the
	// next bit indicates whether there is an orientation override array, and the higher bits
	// indicate the point mode.
	enum LoopSelectionEnum {
		TRIS_NOSIZE_NOORIENT		= ((int)TRIS << 2) + 0,
		TRIS_SIZE_NOORIENT		= ((int)TRIS << 2) + 1,
		TRIS_NOSIZE_ORIENT		= ((int)TRIS << 2) + 2,
		TRIS_SIZE_ORIENT			= ((int)TRIS << 2) + 3,
		QUADS_NOSIZE_NOORIENT	= ((int)QUADS << 2) + 0,
		QUADS_SIZE_NOORIENT		= ((int)QUADS << 2) + 1,
		QUADS_NOSIZE_ORIENT		= ((int)QUADS << 2) + 2,
		QUADS_SIZE_ORIENT			= ((int)QUADS << 2) + 3,
		SCREEN_NOSIZE_NOORIENT	= ((int)SCREENSPACE << 2) + 0,
		SCREEN_SIZE_NOORIENT		= ((int)SCREENSPACE << 2) + 1,
		SCREEN_NOSIZE_ORIENT		= ((int)SCREENSPACE << 2) + 2,
		SCREEN_SIZE_ORIENT		= ((int)SCREENSPACE << 2) + 3,
	};
	LoopSelectionEnum loop_sel = (LoopSelectionEnum)(((int)PointMode << 2) +
		(point_orientation ? 2 : 0) + (point_size ? 1 : 0));

	vert = 0;
	Vector3 *vertex_loc = &VertexLoc[0];

	switch (loop_sel) {

		case TRIS_NOSIZE_NOORIENT:
			{
				// Setup constant vertex offsets (since size and orientation are invariants)
				Vector3 scaled_offset[3];
				scaled_offset[0] = _TriVertexLocationOrientationTable[DefaultPointOrientation][0] * DefaultPointSize;
				scaled_offset[1] = _TriVertexLocationOrientationTable[DefaultPointOrientation][1] * DefaultPointSize;
				scaled_offset[2] = _TriVertexLocationOrientationTable[DefaultPointOrientation][2] * DefaultPointSize;

				// Add vertex offsets to point locations to get vertex locations
				i=0; if(active_points>=4) { int groups=(active_points-4)/4+1; do {
					vertex_loc[0].X = point_loc[0].X + scaled_offset[0].X;
					vertex_loc[0].Y = point_loc[0].Y + scaled_offset[0].Y;
					vertex_loc[0].Z = point_loc[0].Z + scaled_offset[0].Z;
					vertex_loc[1].X = point_loc[0].X + scaled_offset[1].X;
					vertex_loc[1].Y = point_loc[0].Y + scaled_offset[1].Y;
					vertex_loc[1].Z = point_loc[0].Z + scaled_offset[1].Z;
					vertex_loc[2].X = point_loc[0].X + scaled_offset[2].X;
					vertex_loc[2].Y = point_loc[0].Y + scaled_offset[2].Y;
					vertex_loc[2].Z = point_loc[0].Z + scaled_offset[2].Z;
					vertex_loc[3].X = point_loc[1].X + scaled_offset[0].X;
					vertex_loc[3].Y = point_loc[1].Y + scaled_offset[0].Y;
					vertex_loc[3].Z = point_loc[1].Z + scaled_offset[0].Z;
					vertex_loc[4].X = point_loc[1].X + scaled_offset[1].X;
					vertex_loc[4].Y = point_loc[1].Y + scaled_offset[1].Y;
					vertex_loc[4].Z = point_loc[1].Z + scaled_offset[1].Z;
					vertex_loc[5].X = point_loc[1].X + scaled_offset[2].X;
					vertex_loc[5].Y = point_loc[1].Y + scaled_offset[2].Y;
					vertex_loc[5].Z = point_loc[1].Z + scaled_offset[2].Z;
					vertex_loc[6].X = point_loc[2].X + scaled_offset[0].X;
					vertex_loc[6].Y = point_loc[2].Y + scaled_offset[0].Y;
					vertex_loc[6].Z = point_loc[2].Z + scaled_offset[0].Z;
					vertex_loc[7].X = point_loc[2].X + scaled_offset[1].X;
					vertex_loc[7].Y = point_loc[2].Y + scaled_offset[1].Y;
					vertex_loc[7].Z = point_loc[2].Z + scaled_offset[1].Z;
					vertex_loc[8].X = point_loc[2].X + scaled_offset[2].X;
					vertex_loc[8].Y = point_loc[2].Y + scaled_offset[2].Y;
					vertex_loc[8].Z = point_loc[2].Z + scaled_offset[2].Z;
					vertex_loc[9].X = point_loc[3].X + scaled_offset[0].X;
					vertex_loc[9].Y = point_loc[3].Y + scaled_offset[0].Y;
					vertex_loc[9].Z = point_loc[3].Z + scaled_offset[0].Z;
					vertex_loc[10].X = point_loc[3].X + scaled_offset[1].X;
					vertex_loc[10].Y = point_loc[3].Y + scaled_offset[1].Y;
					vertex_loc[10].Z = point_loc[3].Z + scaled_offset[1].Z;
					vertex_loc[11].X = point_loc[3].X + scaled_offset[2].X;
					vertex_loc[11].Y = point_loc[3].Y + scaled_offset[2].Y;
					vertex_loc[11].Z = point_loc[3].Z + scaled_offset[2].Z;
				i+=4;point_loc+=4;vertex_loc+=12;
				} while(--groups); }
				for (;i < active_points;++i,++point_loc,vertex_loc+=3) {
					vertex_loc[ 0].X = point_loc[0].X + scaled_offset[0].X;
					vertex_loc[ 0].Y = point_loc[0].Y + scaled_offset[0].Y;
					vertex_loc[ 0].Z = point_loc[0].Z + scaled_offset[0].Z;
					vertex_loc[ 1].X = point_loc[0].X + scaled_offset[1].X;
					vertex_loc[ 1].Y = point_loc[0].Y + scaled_offset[1].Y;
					vertex_loc[ 1].Z = point_loc[0].Z + scaled_offset[1].Z;
					vertex_loc[ 2].X = point_loc[0].X + scaled_offset[2].X;
					vertex_loc[ 2].Y = point_loc[0].Y + scaled_offset[2].Y;
					vertex_loc[ 2].Z = point_loc[0].Z + scaled_offset[2].Z;
				}
			}
			break;

		case TRIS_SIZE_NOORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				i=0; if(active_points>=4) { int groups=(active_points-4)/4+1; do {
					vertex_loc[0].X = point_loc[0].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[i + 0];
					vertex_loc[0].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[i + 0];
					vertex_loc[0].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[i + 0];
					vertex_loc[1].X = point_loc[0].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[i + 0];
					vertex_loc[1].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[i + 0];
					vertex_loc[1].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[i + 0];
					vertex_loc[2].X = point_loc[0].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[i + 0];
					vertex_loc[2].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[i + 0];
					vertex_loc[2].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[i + 0];

					vertex_loc[3].X = point_loc[1].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[i + 1];
					vertex_loc[3].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[i + 1];
					vertex_loc[3].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[i + 1];
					vertex_loc[4].X = point_loc[1].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[i + 1];
					vertex_loc[4].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[i + 1];
					vertex_loc[4].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[i + 1];
					vertex_loc[5].X = point_loc[1].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[i + 1];
					vertex_loc[5].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[i + 1];
					vertex_loc[5].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[i + 1];

					vertex_loc[6].X = point_loc[2].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[i + 2];
					vertex_loc[6].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[i + 2];
					vertex_loc[6].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[i + 2];
					vertex_loc[7].X = point_loc[2].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[i + 2];
					vertex_loc[7].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[i + 2];
					vertex_loc[7].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[i + 2];
					vertex_loc[8].X = point_loc[2].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[i + 2];
					vertex_loc[8].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[i + 2];
					vertex_loc[8].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[i + 2];

					vertex_loc[9].X = point_loc[3].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[i + 3];
					vertex_loc[9].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[i + 3];
					vertex_loc[9].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[i + 3];
					vertex_loc[10].X = point_loc[3].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[i + 3];
					vertex_loc[10].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[i + 3];
					vertex_loc[10].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[i + 3];
					vertex_loc[11].X = point_loc[3].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[i + 3];
					vertex_loc[11].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[i + 3];
					vertex_loc[11].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[i + 3];
				i+=4;point_loc+=4;vertex_loc+=12;
				} while(--groups); }
				for (;i < active_points;++i,++point_loc,vertex_loc+=3) {
					vertex_loc[ 0].X = point_loc[0].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[i];
					vertex_loc[ 0].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[i];
					vertex_loc[ 0].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[i];
					vertex_loc[ 1].X = point_loc[0].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[i];
					vertex_loc[ 1].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[i];
					vertex_loc[ 1].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[i];
					vertex_loc[ 2].X = point_loc[0].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[i];
					vertex_loc[ 2].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[i];
					vertex_loc[ 2].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[i];
				}
			}
			break;

		case TRIS_NOSIZE_ORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				i=0; if(active_points>=4) { int groups=(active_points-4)/4+1; do {
					vertex_loc[0].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i + 0]][0].X * DefaultPointSize;
					vertex_loc[0].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i + 0]][0].Y * DefaultPointSize;
					vertex_loc[0].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i + 0]][0].Z * DefaultPointSize;
					vertex_loc[1].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i + 0]][1].X * DefaultPointSize;
					vertex_loc[1].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i + 0]][1].Y * DefaultPointSize;
					vertex_loc[1].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i + 0]][1].Z * DefaultPointSize;
					vertex_loc[2].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i + 0]][2].X * DefaultPointSize;
					vertex_loc[2].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i + 0]][2].Y * DefaultPointSize;
					vertex_loc[2].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i + 0]][2].Z * DefaultPointSize;

					vertex_loc[3].X = point_loc[1].X + _TriVertexLocationOrientationTable[point_orientation[i + 1]][0].X * DefaultPointSize;
					vertex_loc[3].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[point_orientation[i + 1]][0].Y * DefaultPointSize;
					vertex_loc[3].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[point_orientation[i + 1]][0].Z * DefaultPointSize;
					vertex_loc[4].X = point_loc[1].X + _TriVertexLocationOrientationTable[point_orientation[i + 1]][1].X * DefaultPointSize;
					vertex_loc[4].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[point_orientation[i + 1]][1].Y * DefaultPointSize;
					vertex_loc[4].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[point_orientation[i + 1]][1].Z * DefaultPointSize;
					vertex_loc[5].X = point_loc[1].X + _TriVertexLocationOrientationTable[point_orientation[i + 1]][2].X * DefaultPointSize;
					vertex_loc[5].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[point_orientation[i + 1]][2].Y * DefaultPointSize;
					vertex_loc[5].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[point_orientation[i + 1]][2].Z * DefaultPointSize;

					vertex_loc[6].X = point_loc[2].X + _TriVertexLocationOrientationTable[point_orientation[i + 2]][0].X * DefaultPointSize;
					vertex_loc[6].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[point_orientation[i + 2]][0].Y * DefaultPointSize;
					vertex_loc[6].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[point_orientation[i + 2]][0].Z * DefaultPointSize;
					vertex_loc[7].X = point_loc[2].X + _TriVertexLocationOrientationTable[point_orientation[i + 2]][1].X * DefaultPointSize;
					vertex_loc[7].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[point_orientation[i + 2]][1].Y * DefaultPointSize;
					vertex_loc[7].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[point_orientation[i + 2]][1].Z * DefaultPointSize;
					vertex_loc[8].X = point_loc[2].X + _TriVertexLocationOrientationTable[point_orientation[i + 2]][2].X * DefaultPointSize;
					vertex_loc[8].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[point_orientation[i + 2]][2].Y * DefaultPointSize;
					vertex_loc[8].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[point_orientation[i + 2]][2].Z * DefaultPointSize;

					vertex_loc[9].X = point_loc[3].X + _TriVertexLocationOrientationTable[point_orientation[i + 3]][0].X * DefaultPointSize;
					vertex_loc[9].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[point_orientation[i + 3]][0].Y * DefaultPointSize;
					vertex_loc[9].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[point_orientation[i + 3]][0].Z * DefaultPointSize;
					vertex_loc[10].X = point_loc[3].X + _TriVertexLocationOrientationTable[point_orientation[i + 3]][1].X * DefaultPointSize;
					vertex_loc[10].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[point_orientation[i + 3]][1].Y * DefaultPointSize;
					vertex_loc[10].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[point_orientation[i + 3]][1].Z * DefaultPointSize;
					vertex_loc[11].X = point_loc[3].X + _TriVertexLocationOrientationTable[point_orientation[i + 3]][2].X * DefaultPointSize;
					vertex_loc[11].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[point_orientation[i + 3]][2].Y * DefaultPointSize;
					vertex_loc[11].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[point_orientation[i + 3]][2].Z * DefaultPointSize;
				i+=4;point_loc+=4;vertex_loc+=12;
				} while(--groups); }
				for (;i < active_points;++i,++point_loc,vertex_loc+=3) {
					vertex_loc[ 0].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i]][0].X * DefaultPointSize;
					vertex_loc[ 0].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i]][0].Y * DefaultPointSize;
					vertex_loc[ 0].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i]][0].Z * DefaultPointSize;
					vertex_loc[ 1].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i]][1].X * DefaultPointSize;
					vertex_loc[ 1].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i]][1].Y * DefaultPointSize;
					vertex_loc[ 1].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i]][1].Z * DefaultPointSize;
					vertex_loc[ 2].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i]][2].X * DefaultPointSize;
					vertex_loc[ 2].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i]][2].Y * DefaultPointSize;
					vertex_loc[ 2].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i]][2].Z * DefaultPointSize;
				}
			}
			break;

		case TRIS_SIZE_ORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				i=0; if(active_points>=4) { int groups=(active_points-4)/4+1; do {
					vertex_loc[0].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i + 0]][0].X * point_size[i + 0];
					vertex_loc[0].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i + 0]][0].Y * point_size[i + 0];
					vertex_loc[0].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i + 0]][0].Z * point_size[i + 0];
					vertex_loc[1].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i + 0]][1].X * point_size[i + 0];
					vertex_loc[1].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i + 0]][1].Y * point_size[i + 0];
					vertex_loc[1].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i + 0]][1].Z * point_size[i + 0];
					vertex_loc[2].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i + 0]][2].X * point_size[i + 0];
					vertex_loc[2].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i + 0]][2].Y * point_size[i + 0];
					vertex_loc[2].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i + 0]][2].Z * point_size[i + 0];

					vertex_loc[3].X = point_loc[1].X + _TriVertexLocationOrientationTable[point_orientation[i + 1]][0].X * point_size[i + 1];
					vertex_loc[3].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[point_orientation[i + 1]][0].Y * point_size[i + 1];
					vertex_loc[3].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[point_orientation[i + 1]][0].Z * point_size[i + 1];
					vertex_loc[4].X = point_loc[1].X + _TriVertexLocationOrientationTable[point_orientation[i + 1]][1].X * point_size[i + 1];
					vertex_loc[4].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[point_orientation[i + 1]][1].Y * point_size[i + 1];
					vertex_loc[4].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[point_orientation[i + 1]][1].Z * point_size[i + 1];
					vertex_loc[5].X = point_loc[1].X + _TriVertexLocationOrientationTable[point_orientation[i + 1]][2].X * point_size[i + 1];
					vertex_loc[5].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[point_orientation[i + 1]][2].Y * point_size[i + 1];
					vertex_loc[5].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[point_orientation[i + 1]][2].Z * point_size[i + 1];

					vertex_loc[6].X = point_loc[2].X + _TriVertexLocationOrientationTable[point_orientation[i + 2]][0].X * point_size[i + 2];
					vertex_loc[6].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[point_orientation[i + 2]][0].Y * point_size[i + 2];
					vertex_loc[6].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[point_orientation[i + 2]][0].Z * point_size[i + 2];
					vertex_loc[7].X = point_loc[2].X + _TriVertexLocationOrientationTable[point_orientation[i + 2]][1].X * point_size[i + 2];
					vertex_loc[7].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[point_orientation[i + 2]][1].Y * point_size[i + 2];
					vertex_loc[7].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[point_orientation[i + 2]][1].Z * point_size[i + 2];
					vertex_loc[8].X = point_loc[2].X + _TriVertexLocationOrientationTable[point_orientation[i + 2]][2].X * point_size[i + 2];
					vertex_loc[8].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[point_orientation[i + 2]][2].Y * point_size[i + 2];
					vertex_loc[8].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[point_orientation[i + 2]][2].Z * point_size[i + 2];

					vertex_loc[9].X = point_loc[3].X + _TriVertexLocationOrientationTable[point_orientation[i + 3]][0].X * point_size[i + 3];
					vertex_loc[9].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[point_orientation[i + 3]][0].Y * point_size[i + 3];
					vertex_loc[9].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[point_orientation[i + 3]][0].Z * point_size[i + 3];
					vertex_loc[10].X = point_loc[3].X + _TriVertexLocationOrientationTable[point_orientation[i + 3]][1].X * point_size[i + 3];
					vertex_loc[10].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[point_orientation[i + 3]][1].Y * point_size[i + 3];
					vertex_loc[10].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[point_orientation[i + 3]][1].Z * point_size[i + 3];
					vertex_loc[11].X = point_loc[3].X + _TriVertexLocationOrientationTable[point_orientation[i + 3]][2].X * point_size[i + 3];
					vertex_loc[11].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[point_orientation[i + 3]][2].Y * point_size[i + 3];
					vertex_loc[11].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[point_orientation[i + 3]][2].Z * point_size[i + 3];
				i+=4;point_loc+=4;vertex_loc+=12;
				} while(--groups); }
				for (;i < active_points;++i,++point_loc,vertex_loc+=3) {
					vertex_loc[ 0].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i]][0].X * point_size[i];
					vertex_loc[ 0].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i]][0].Y * point_size[i];
					vertex_loc[ 0].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i]][0].Z * point_size[i];
					vertex_loc[ 1].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i]][1].X * point_size[i];
					vertex_loc[ 1].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i]][1].Y * point_size[i];
					vertex_loc[ 1].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i]][1].Z * point_size[i];
					vertex_loc[ 2].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i]][2].X * point_size[i];
					vertex_loc[ 2].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i]][2].Y * point_size[i];
					vertex_loc[ 2].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i]][2].Z * point_size[i];
				}
			}
			break;

		case QUADS_NOSIZE_NOORIENT:
			{
				// Setup constant vertex offsets (since size and orientation are invariants)
				Vector3 scaled_offset[4];
				scaled_offset[0] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][0] * DefaultPointSize;
				scaled_offset[1] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][1] * DefaultPointSize;
				scaled_offset[2] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][2] * DefaultPointSize;
				scaled_offset[3] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][3] * DefaultPointSize;

				// Add vertex offsets to point locations to get vertex locations
				i=0; if(active_points>=4) { int groups=(active_points-4)/4+1; do {
					vertex_loc[0].X = point_loc[0].X + scaled_offset[0].X;
					vertex_loc[0].Y = point_loc[0].Y + scaled_offset[0].Y;
					vertex_loc[0].Z = point_loc[0].Z + scaled_offset[0].Z;
					vertex_loc[1].X = point_loc[0].X + scaled_offset[1].X;
					vertex_loc[1].Y = point_loc[0].Y + scaled_offset[1].Y;
					vertex_loc[1].Z = point_loc[0].Z + scaled_offset[1].Z;
					vertex_loc[2].X = point_loc[0].X + scaled_offset[2].X;
					vertex_loc[2].Y = point_loc[0].Y + scaled_offset[2].Y;
					vertex_loc[2].Z = point_loc[0].Z + scaled_offset[2].Z;
					vertex_loc[3].X = point_loc[0].X + scaled_offset[3].X;
					vertex_loc[3].Y = point_loc[0].Y + scaled_offset[3].Y;
					vertex_loc[3].Z = point_loc[0].Z + scaled_offset[3].Z;
					vertex_loc[4].X = point_loc[1].X + scaled_offset[0].X;
					vertex_loc[4].Y = point_loc[1].Y + scaled_offset[0].Y;
					vertex_loc[4].Z = point_loc[1].Z + scaled_offset[0].Z;
					vertex_loc[5].X = point_loc[1].X + scaled_offset[1].X;
					vertex_loc[5].Y = point_loc[1].Y + scaled_offset[1].Y;
					vertex_loc[5].Z = point_loc[1].Z + scaled_offset[1].Z;
					vertex_loc[6].X = point_loc[1].X + scaled_offset[2].X;
					vertex_loc[6].Y = point_loc[1].Y + scaled_offset[2].Y;
					vertex_loc[6].Z = point_loc[1].Z + scaled_offset[2].Z;
					vertex_loc[7].X = point_loc[1].X + scaled_offset[3].X;
					vertex_loc[7].Y = point_loc[1].Y + scaled_offset[3].Y;
					vertex_loc[7].Z = point_loc[1].Z + scaled_offset[3].Z;
					vertex_loc[8].X = point_loc[2].X + scaled_offset[0].X;
					vertex_loc[8].Y = point_loc[2].Y + scaled_offset[0].Y;
					vertex_loc[8].Z = point_loc[2].Z + scaled_offset[0].Z;
					vertex_loc[9].X = point_loc[2].X + scaled_offset[1].X;
					vertex_loc[9].Y = point_loc[2].Y + scaled_offset[1].Y;
					vertex_loc[9].Z = point_loc[2].Z + scaled_offset[1].Z;
					vertex_loc[10].X = point_loc[2].X + scaled_offset[2].X;
					vertex_loc[10].Y = point_loc[2].Y + scaled_offset[2].Y;
					vertex_loc[10].Z = point_loc[2].Z + scaled_offset[2].Z;
					vertex_loc[11].X = point_loc[2].X + scaled_offset[3].X;
					vertex_loc[11].Y = point_loc[2].Y + scaled_offset[3].Y;
					vertex_loc[11].Z = point_loc[2].Z + scaled_offset[3].Z;
					vertex_loc[12].X = point_loc[3].X + scaled_offset[0].X;
					vertex_loc[12].Y = point_loc[3].Y + scaled_offset[0].Y;
					vertex_loc[12].Z = point_loc[3].Z + scaled_offset[0].Z;
					vertex_loc[13].X = point_loc[3].X + scaled_offset[1].X;
					vertex_loc[13].Y = point_loc[3].Y + scaled_offset[1].Y;
					vertex_loc[13].Z = point_loc[3].Z + scaled_offset[1].Z;
					vertex_loc[14].X = point_loc[3].X + scaled_offset[2].X;
					vertex_loc[14].Y = point_loc[3].Y + scaled_offset[2].Y;
					vertex_loc[14].Z = point_loc[3].Z + scaled_offset[2].Z;
					vertex_loc[15].X = point_loc[3].X + scaled_offset[3].X;
					vertex_loc[15].Y = point_loc[3].Y + scaled_offset[3].Y;
					vertex_loc[15].Z = point_loc[3].Z + scaled_offset[3].Z;
				i+=4;point_loc+=4;vertex_loc+=16;
				} while(--groups); }
				for (;i < active_points;++i,++point_loc,vertex_loc+=4) {
					vertex_loc[ 0].X = point_loc[0].X + scaled_offset[0].X;
					vertex_loc[ 0].Y = point_loc[0].Y + scaled_offset[0].Y;
					vertex_loc[ 0].Z = point_loc[0].Z + scaled_offset[0].Z;
					vertex_loc[ 1].X = point_loc[0].X + scaled_offset[1].X;
					vertex_loc[ 1].Y = point_loc[0].Y + scaled_offset[1].Y;
					vertex_loc[ 1].Z = point_loc[0].Z + scaled_offset[1].Z;
					vertex_loc[ 2].X = point_loc[0].X + scaled_offset[2].X;
					vertex_loc[ 2].Y = point_loc[0].Y + scaled_offset[2].Y;
					vertex_loc[ 2].Z = point_loc[0].Z + scaled_offset[2].Z;
					vertex_loc[ 3].X = point_loc[0].X + scaled_offset[3].X;
					vertex_loc[ 3].Y = point_loc[0].Y + scaled_offset[3].Y;
					vertex_loc[ 3].Z = point_loc[0].Z + scaled_offset[3].Z;
				}
			}
			break;

		case QUADS_SIZE_NOORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i = 0; i < active_points; i++, point_loc++, vertex_loc += 4) {
					vertex_loc[ 0].X = point_loc[0].X + _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[i];
					vertex_loc[ 0].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[i];
					vertex_loc[ 0].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[i];
					vertex_loc[ 1].X = point_loc[0].X + _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[i];
					vertex_loc[ 1].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[i];
					vertex_loc[ 1].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[i];
					vertex_loc[ 2].X = point_loc[0].X + _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[i];
					vertex_loc[ 2].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[i];
					vertex_loc[ 2].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[i];
					vertex_loc[ 3].X = point_loc[0].X + _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].X * point_size[i];
					vertex_loc[ 3].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].Y * point_size[i];
					vertex_loc[ 3].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].Z * point_size[i];
				}
			}
			break;

		case QUADS_NOSIZE_ORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i = 0; i < active_points; i++, point_loc++, vertex_loc += 4) {
					vertex_loc[ 0].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[i]][0].X * DefaultPointSize;
					vertex_loc[ 0].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[i]][0].Y * DefaultPointSize;
					vertex_loc[ 0].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[i]][0].Z * DefaultPointSize;
					vertex_loc[ 1].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[i]][1].X * DefaultPointSize;
					vertex_loc[ 1].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[i]][1].Y * DefaultPointSize;
					vertex_loc[ 1].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[i]][1].Z * DefaultPointSize;
					vertex_loc[ 2].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[i]][2].X * DefaultPointSize;
					vertex_loc[ 2].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[i]][2].Y * DefaultPointSize;
					vertex_loc[ 2].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[i]][2].Z * DefaultPointSize;
					vertex_loc[ 3].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[i]][3].X * DefaultPointSize;
					vertex_loc[ 3].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[i]][3].Y * DefaultPointSize;
					vertex_loc[ 3].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[i]][3].Z * DefaultPointSize;
				}
			}
			break;

		case QUADS_SIZE_ORIENT:
			{
				if (!(Flags & (1 << BILLBOARD))) {
					Matrix4 view;
					DX8Wrapper::Get_Transform(D3DTS_VIEW, view);

					// Scale vertex offsets and add them to point locations to get vertex locations
					for (i = 0; i < active_points; i++, point_loc++, vertex_loc += 4) {
						// If we're not billboarding, then the coordinate we have is in screen space.
						Matrix4 rotMat;
						D3DXMatrixRotationZ(&(D3DXMATRIX&) rotMat, ((float)point_orientation[i] / 255.0f * 2 * D3DX_PI));

						Vector4 orientedVecX = rotMat * GroundMultiplierX;
						Vector4 orientedVecY = rotMat * GroundMultiplierY;

						vertex_loc[ 0].X = point_loc[0].X +	(orientedVecX.X + orientedVecY.X) * point_size[i];
						vertex_loc[ 0].Y = point_loc[0].Y +	(orientedVecX.Y + orientedVecY.Y) * point_size[i];
						vertex_loc[ 0].Z = point_loc[0].Z;

						vertex_loc[ 1].X = point_loc[0].X +	(orientedVecX.X - orientedVecY.X) * point_size[i];
						vertex_loc[ 1].Y = point_loc[0].Y +	(orientedVecX.Y - orientedVecY.Y) * point_size[i];
						vertex_loc[ 1].Z = point_loc[0].Z;

						vertex_loc[ 2].X = point_loc[0].X +	-(orientedVecX.X + orientedVecY.X) * point_size[i];
						vertex_loc[ 2].Y = point_loc[0].Y +	-(orientedVecX.Y + orientedVecY.Y) * point_size[i];
						vertex_loc[ 2].Z = point_loc[0].Z;

						vertex_loc[ 3].X = point_loc[0].X +	(-orientedVecX.X + orientedVecY.X) * point_size[i];
						vertex_loc[ 3].Y = point_loc[0].Y +	(-orientedVecX.Y + orientedVecY.Y) * point_size[i];
						vertex_loc[ 3].Z = point_loc[0].Z;

						// now apply the view transform so that this data is in the format expected
						// upon the functions return.
						Vector4 result = view * vertex_loc[ 0];
						vertex_loc[ 0].X = result.X;
						vertex_loc[ 0].Y = result.Y;
						vertex_loc[ 0].Z = result.Z;

						result = view * vertex_loc[ 1];
						vertex_loc[ 1].X = result.X;
						vertex_loc[ 1].Y = result.Y;
						vertex_loc[ 1].Z = result.Z;

						result = view * vertex_loc[ 2];
						vertex_loc[ 2].X = result.X;
						vertex_loc[ 2].Y = result.Y;
						vertex_loc[ 2].Z = result.Z;

						result = view * vertex_loc[ 3];
						vertex_loc[ 3].X = result.X;
						vertex_loc[ 3].Y = result.Y;
						vertex_loc[ 3].Z = result.Z;
					}
				} else {

					// Scale vertex offsets and add them to point locations to get vertex locations
					for (i = 0; i < active_points; i++, point_loc++, vertex_loc += 4) {
						vertex_loc[ 0] = point_loc[0] + _QuadVertexLocationOrientationTable[point_orientation[i]][0] * point_size[i];
						vertex_loc[ 1] = point_loc[0] + _QuadVertexLocationOrientationTable[point_orientation[i]][1] * point_size[i];
						vertex_loc[ 2] = point_loc[0] + _QuadVertexLocationOrientationTable[point_orientation[i]][2] * point_size[i];
						vertex_loc[ 3] = point_loc[0] + _QuadVertexLocationOrientationTable[point_orientation[i]][3] * point_size[i];
					}
				}
			}
			break;

		// Orientations are ignored for screensize pointgroups
		case SCREEN_NOSIZE_NOORIENT:
		case SCREEN_NOSIZE_ORIENT:
			{
				// Offsets need to be scaled to the current screen resolution

   			// First find x and y scale factors (sizes in pixels need to be
   			// normalized to 2D cam viewplane of -1,-1 to 1,1)
   			int xres, yres, bitdepth;
   			bool windowed;
   			WW3D::Get_Render_Target_Resolution(xres, yres, bitdepth, windowed);

   			float x_scale = (VPXMax - VPXMin) / xres;
   			float y_scale = (VPYMax - VPYMin) / yres;

   			int size_idx = (DefaultPointSize <= 1.0f) ? 0 : 1;

				Vector3 scaled_locs[3];
				scaled_locs[0].X = _ScreenspaceVertexLocationSizeTable[size_idx][0].X * x_scale;
				scaled_locs[0].Y = _ScreenspaceVertexLocationSizeTable[size_idx][0].Y * y_scale;
				scaled_locs[0].Z = _ScreenspaceVertexLocationSizeTable[size_idx][0].Z;
				scaled_locs[1].X = _ScreenspaceVertexLocationSizeTable[size_idx][1].X * x_scale;
				scaled_locs[1].Y = _ScreenspaceVertexLocationSizeTable[size_idx][1].Y * y_scale;
				scaled_locs[1].Z = _ScreenspaceVertexLocationSizeTable[size_idx][1].Z;
				scaled_locs[2].X = _ScreenspaceVertexLocationSizeTable[size_idx][2].X * x_scale;
				scaled_locs[2].Y = _ScreenspaceVertexLocationSizeTable[size_idx][2].Y * y_scale;
				scaled_locs[2].Z = _ScreenspaceVertexLocationSizeTable[size_idx][2].Z;

				// Add vertex offsets to point locations to get vertex locations
				i=0; if(active_points>=4) { int groups=(active_points-4)/4+1; do {
					vertex_loc[0] = point_loc[0] + scaled_locs[0];
					vertex_loc[1] = point_loc[0] + scaled_locs[1];
					vertex_loc[2] = point_loc[0] + scaled_locs[2];
					vertex_loc[3] = point_loc[1] + scaled_locs[0];
					vertex_loc[4] = point_loc[1] + scaled_locs[1];
					vertex_loc[5] = point_loc[1] + scaled_locs[2];
					vertex_loc[6] = point_loc[2] + scaled_locs[0];
					vertex_loc[7] = point_loc[2] + scaled_locs[1];
					vertex_loc[8] = point_loc[2] + scaled_locs[2];
					vertex_loc[9] = point_loc[3] + scaled_locs[0];
					vertex_loc[10] = point_loc[3] + scaled_locs[1];
					vertex_loc[11] = point_loc[3] + scaled_locs[2];
				i+=4;point_loc+=4;vertex_loc+=12;
				} while(--groups); }
				for (;i < active_points;++i,++point_loc,vertex_loc+=3) {
					vertex_loc[ 0] = point_loc[0] + scaled_locs[0];
					vertex_loc[ 1] = point_loc[0] + scaled_locs[1];
					vertex_loc[ 2] = point_loc[0] + scaled_locs[2];
				}
			}
			break;

		case SCREEN_SIZE_NOORIENT:
		case SCREEN_SIZE_ORIENT:
			{
				// Offsets need to be scaled to the current screen resolution

   			// First find x and y scale factors (sizes in pixels need to be
   			// normalized to 2D cam viewplane of -1,-1 to 1,1)
   			int xres, yres, bitdepth;
   			bool windowed;
   			WW3D::Get_Render_Target_Resolution(xres, yres, bitdepth, windowed);

   			float x_scale = (VPXMax - VPXMin) / xres;
   			float y_scale = (VPYMax - VPYMin) / yres;

				Vector3 scaled_locs[2][3];
				scaled_locs[0][0].X = _ScreenspaceVertexLocationSizeTable[0][0].X * x_scale;
				scaled_locs[0][0].Y = _ScreenspaceVertexLocationSizeTable[0][0].Y * y_scale;
				scaled_locs[0][0].Z = _ScreenspaceVertexLocationSizeTable[0][0].Z;
				scaled_locs[0][1].X = _ScreenspaceVertexLocationSizeTable[0][1].X * x_scale;
				scaled_locs[0][1].Y = _ScreenspaceVertexLocationSizeTable[0][1].Y * y_scale;
				scaled_locs[0][1].Z = _ScreenspaceVertexLocationSizeTable[0][1].Z;
				scaled_locs[0][2].X = _ScreenspaceVertexLocationSizeTable[0][2].X * x_scale;
				scaled_locs[0][2].Y = _ScreenspaceVertexLocationSizeTable[0][2].Y * y_scale;
				scaled_locs[0][2].Z = _ScreenspaceVertexLocationSizeTable[0][2].Z;
				scaled_locs[1][0].X = _ScreenspaceVertexLocationSizeTable[1][0].X * x_scale;
				scaled_locs[1][0].Y = _ScreenspaceVertexLocationSizeTable[1][0].Y * y_scale;
				scaled_locs[1][0].Z = _ScreenspaceVertexLocationSizeTable[1][0].Z;
				scaled_locs[1][1].X = _ScreenspaceVertexLocationSizeTable[1][1].X * x_scale;
				scaled_locs[1][1].Y = _ScreenspaceVertexLocationSizeTable[1][1].Y * y_scale;
				scaled_locs[1][1].Z = _ScreenspaceVertexLocationSizeTable[1][1].Z;
				scaled_locs[1][2].X = _ScreenspaceVertexLocationSizeTable[1][2].X * x_scale;
				scaled_locs[1][2].Y = _ScreenspaceVertexLocationSizeTable[1][2].Y * y_scale;
				scaled_locs[1][2].Z = _ScreenspaceVertexLocationSizeTable[1][2].Z;

				// Add vertex offsets to point locations to get vertex locations
				i=0; if(active_points>=4) { int groups=(active_points-4)/4+1; do {
					vertex_loc[0] = point_loc[0] + scaled_locs[(point_size[i + 0] <= 1.0f) ? 0 : 1][0];
					vertex_loc[1] = point_loc[0] + scaled_locs[(point_size[i + 0] <= 1.0f) ? 0 : 1][1];
					vertex_loc[2] = point_loc[0] + scaled_locs[(point_size[i + 0] <= 1.0f) ? 0 : 1][2];
					vertex_loc[3] = point_loc[1] + scaled_locs[(point_size[i + 1] <= 1.0f) ? 0 : 1][0];
					vertex_loc[4] = point_loc[1] + scaled_locs[(point_size[i + 1] <= 1.0f) ? 0 : 1][1];
					vertex_loc[5] = point_loc[1] + scaled_locs[(point_size[i + 1] <= 1.0f) ? 0 : 1][2];
					vertex_loc[6] = point_loc[2] + scaled_locs[(point_size[i + 2] <= 1.0f) ? 0 : 1][0];
					vertex_loc[7] = point_loc[2] + scaled_locs[(point_size[i + 2] <= 1.0f) ? 0 : 1][1];
					vertex_loc[8] = point_loc[2] + scaled_locs[(point_size[i + 2] <= 1.0f) ? 0 : 1][2];
					vertex_loc[9] = point_loc[3] + scaled_locs[(point_size[i + 3] <= 1.0f) ? 0 : 1][0];
					vertex_loc[10] = point_loc[3] + scaled_locs[(point_size[i + 3] <= 1.0f) ? 0 : 1][1];
					vertex_loc[11] = point_loc[3] + scaled_locs[(point_size[i + 3] <= 1.0f) ? 0 : 1][2];
				i+=4;point_loc+=4;vertex_loc+=12;
				} while(--groups); }
				for (;i < active_points;++i,++point_loc,vertex_loc+=3) {
					vertex_loc[ 0] = point_loc[0] + scaled_locs[(point_size[i] <= 1.0f) ? 0 : 1][0];
					vertex_loc[ 1] = point_loc[0] + scaled_locs[(point_size[i] <= 1.0f) ? 0 : 1][1];
					vertex_loc[ 2] = point_loc[0] + scaled_locs[(point_size[i] <= 1.0f) ? 0 : 1][2];
				}
			}
			break;

		default:
			break;
	}
}
