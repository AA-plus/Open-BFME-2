// ?Add_Line@Render2DClass@@QAEXABVVector2@@0MK@Z
// partial score=0.9 date=2026-10-12
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Render2DClass::Add_Line overloads (retail 0x00042A4D 563B, 0x00042C80 573B).
// Clean BFME1 donor 0bef414 AddLine.cpp: same 44-byte batch layout and owned
// 11BD80 allocator as the landed Add_Tri/Add_Quad siblings; native 563/573
// extents proven; zero/half/one are verified target constants. Sibling of
// Render2DClassAddTri.cpp: same allocateGeometry006e helper, coordinate
// conversion and color-converter global; four vertices, per-endpoint colors
// in the two-color overload, indices packed as dword pairs.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "../../../../../reference/shims/wwmath/Vector2.h"

typedef unsigned long BfmeUInt32;

struct BfmeRenderVertex
{
	float x;
	float y;
	float z;
	unsigned char m_unmodelled_0C[0x0C];
	BfmeUInt32 color;
	float u;
	float v;
	unsigned char m_unmodelled_24[0x08];
};

typedef BfmeUInt32(__cdecl *BfmeColorConverter)(BfmeUInt32 color);

// Native DEC49C already defined by Rva00118B50State.cpp.
extern float g_Va00DEC49C;

// BFME1 converter storage was 0x012D7198; BFME2 binds the existing 0x00DB5FC8 owner.
// Existing BFME2 global g_Va00DB5FC8 is defined by GlobalGetterSingles.cpp.
// Retail keeps a function pointer in the slot the setter writes as an int, so the call is made
// through the address of the member rather than through a pointer variable.
extern int g_Va00DB5FC8;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.h
class Render2DClass
{
private:
	unsigned char m_unmodelled_00[0x04];
	float m_coordinateScaleX;
	float m_coordinateScaleY;
	float m_biasedCoordinateOffsetX;
	float m_biasedCoordinateOffsetY;
	unsigned char m_unmodelled_14[0x40];
	unsigned char m_texturingEnabled;

	BfmeRenderVertex *allocateGeometry006e(
		unsigned int vertexCount,
		unsigned int indexCount,
		BfmeUInt32 **indices,
		BfmeUInt32 *baseVertexPair);

	void convertPosition006e(BfmeRenderVertex &vertex, float x, float y)
	{
		vertex.x = x * m_coordinateScaleX + m_biasedCoordinateOffsetX;
		vertex.y = y * m_coordinateScaleY + m_biasedCoordinateOffsetY;
		vertex.z = g_Va00DEC49C;
	}

public:
	void Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color);
	void Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color, BfmeUInt32 color2);
};

struct GeometryOutput006e
{
	BfmeUInt32 *indices;
	BfmeUInt32 base;
};

struct CornerOffset006e
{
	float X;
	float Y;
};

// ?Add_Line@Render2DClass@@QAEXABVVector2@@0MK@Z
void Render2DClass::Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color)
{
	CornerOffset006e corner_offset;
	corner_offset.X = a.Y - b.Y;
	corner_offset.Y = b.X - a.X;
	float len2 = corner_offset.X * corner_offset.X + corner_offset.Y * corner_offset.Y;
	GeometryOutput006e output;
	BfmeRenderVertex *vertices;
	if (len2 == 0.0f)
		return;

	float oolen = WWMath::Inv_Sqrt(len2);
	oolen *= width;
	oolen *= 0.5f;
	corner_offset.X *= oolen;
	corner_offset.Y = corner_offset.Y * oolen;

	vertices = allocateGeometry006e(4, 6, &output.indices, &output.base);

	convertPosition006e(vertices[0], a.X - corner_offset.X, a.Y - corner_offset.Y);
	convertPosition006e(vertices[1], a.X + corner_offset.X, a.Y + corner_offset.Y);
	convertPosition006e(vertices[2], b.X - corner_offset.X, b.Y - corner_offset.Y);
	convertPosition006e(vertices[3], b.X + corner_offset.X, b.Y + corner_offset.Y);

	vertices[0].u = vertices[1].u = vertices[0].v = vertices[2].v = 0.0f;
	vertices[3].v = 1.0f;
	vertices[2].u = vertices[3].u = vertices[1].v = 1.0f;

	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color =
		(*(BfmeColorConverter *)&g_Va00DB5FC8)(color);

	output.indices[0] = output.base + 0x00010000;
	output.indices[1] = output.base + 0x00020002;
	output.indices[2] = output.base + 0x00030001;
}

// ?Add_Line@Render2DClass@@QAEXABVVector2@@0MKK@Z
void Render2DClass::Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color, BfmeUInt32 color2)
{
	GeometryOutput006e output;
	BfmeRenderVertex *vertices;
	Vector2 corner_offset(a.Y - b.Y, b.X - a.X);
	float len2 = corner_offset.Length2();
	if (len2 == 0.0f)
		return;

	float oolen = WWMath::Inv_Sqrt(len2);
	oolen *= width;
	oolen *= 0.5f;
	corner_offset.X *= oolen;
	corner_offset.Y = corner_offset.Y * oolen;

	vertices = allocateGeometry006e(4, 6, &output.indices, &output.base);

	convertPosition006e(vertices[0], a.X - corner_offset.X, a.Y - corner_offset.Y);
	convertPosition006e(vertices[1], a.X + corner_offset.X, a.Y + corner_offset.Y);
	convertPosition006e(vertices[2], b.X - corner_offset.X, b.Y - corner_offset.Y);
	convertPosition006e(vertices[3], b.X + corner_offset.X, b.Y + corner_offset.Y);

	vertices[0].u = vertices[1].u = vertices[0].v = vertices[2].v = 0.0f;
	vertices[3].v = 1.0f;
	vertices[2].u = vertices[3].u = vertices[1].v = 1.0f;

	vertices[0].color = vertices[1].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color);
	vertices[2].color = vertices[3].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color2);

	output.indices[0] = output.base + 0x00010000;
	output.indices[1] = output.base + 0x00020002;
	output.indices[2] = output.base + 0x00030001;
}


