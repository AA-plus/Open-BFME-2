// ?Add_Line@Render2DClass@@QAEXABVVector2@@0MKK@Z
// partial score=0.96 date=2026-10-13
// ?Add_Line@Render2DClass@@QAEXABVVector2@@0MKK@Z
// partial score=0.94 date=2026-10-13
// TU-formulation (QuadColor home): 573/573, 16 home-slot diffs (single-expr oolen, convertedColor order fix); packing positional-but-unsatisfiable
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/wwmath
#include "Vector2.h"
// BFME2 target body at RVA 0x000428C7. The reference donor identifies this as
// Render2DClass::Add_Quad(const RectClass &, unsigned long), BFME1 VA 0x006E73C0.
// Donor revision 6583b3c1ff21db4a561285717028fdafc780b7db; source SHA256
// a375d5ed06b1066effaee8352a6e0d4e9977dcfdca526139a03e0091893e9ad3.
// Target callers at 0x444D76, 0x445BBE, 0x445C27, 0x445C71, 0x445E62 and
// 0x446076 pass W3DDisplay::m_render2D, RectClass and color. The target body
// accesses the scale and offset fields at Render2DClass+0x04..+0x10 and uses
// the batch allocator at 0x0011BD80; the donor's source shape compiles to its
// 390-byte target extent with BFME2's globals substituted.

class RectClass
{
public:
	float Left;
	float Top;
	float Right;
	float Bottom;
};

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

typedef BfmeUInt32 (__cdecl *BfmeColorConverter)(BfmeUInt32 color);

extern "C" float g_BfmeRender2DZ;
extern int g_Va00DB5FC8;

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
		vertex.z = g_BfmeRender2DZ;
	}

public:
	void Add_Quad(const RectClass &screen, BfmeUInt32 color);
	void Add_Quad(const RectClass &screen, const RectClass &uv,
		BfmeUInt32 color0, BfmeUInt32 color1,
		BfmeUInt32 color2, BfmeUInt32 color3);
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

void Render2DClass::Add_Quad(const RectClass &screen, BfmeUInt32 color)
{
	BfmeUInt32 baseVertexPair;
	BfmeUInt32 *indices;
	BfmeRenderVertex *vertices = allocateGeometry006e(4, 6, &indices, &baseVertexPair);

	convertPosition006e(vertices[0], screen.Left, screen.Top);
	convertPosition006e(vertices[1], screen.Left, screen.Bottom);
	convertPosition006e(vertices[2], screen.Right, screen.Top);
	convertPosition006e(vertices[3], screen.Right, screen.Bottom);

	vertices[0].u = vertices[1].u = vertices[0].v = vertices[2].v = 0.0f;
	float one = 1.0f;
	vertices[2].u = vertices[3].u = vertices[1].v = vertices[3].v = one;

	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color =
		(*(BfmeColorConverter *)&g_Va00DB5FC8)(color);

	indices[0] = baseVertexPair + 0x00010000;
	indices[1] = baseVertexPair + 0x00020002;
	indices[2] = baseVertexPair + 0x00030001;
}

// Clean BFME 1 donor: reference/open-bfme-1/game/Libraries/Source/WWVegas/
// WW3D2/Render2DClassAddQuad.cpp at 0bef414b52a39a3ab1ec98dca60d8a214de4260e.
// Native 0x00042719..0x000428C7 uses the same 44-byte vertex and allocator
// as the overload above, with four independently converted corner colors.
// The matched sibling's position helper includes Z; keeping that assignment
// within the helper reproduces retail's last-vertex base and push scheduling.
void Render2DClass::Add_Quad(const RectClass &screen, const RectClass &uv,
	BfmeUInt32 color0, BfmeUInt32 color1,
	BfmeUInt32 color2, BfmeUInt32 color3)
{
	BfmeUInt32 baseVertexPair;
	BfmeUInt32 *indices;
	BfmeRenderVertex *vertices = allocateGeometry006e(4, 6, &indices, &baseVertexPair);

	convertPosition006e(vertices[0], screen.Left, screen.Top);
	convertPosition006e(vertices[1], screen.Left, screen.Bottom);
	convertPosition006e(vertices[2], screen.Right, screen.Top);
	convertPosition006e(vertices[3], screen.Right, screen.Bottom);

	vertices[0].u = vertices[1].u = uv.Left;
	vertices[2].u = vertices[3].u = uv.Right;
	vertices[0].v = vertices[2].v = uv.Top;
	vertices[1].v = vertices[3].v = uv.Bottom;

	vertices[0].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color0);
	vertices[1].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color2);
	vertices[2].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color1);
	vertices[3].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color3);

	indices[0] = baseVertexPair + 0x00010000;
	indices[1] = baseVertexPair + 0x00020002;
	indices[2] = baseVertexPair + 0x00030001;
}

// ?Add_Line@Render2DClass@@QAEXABVVector2@@0MK@Z, retail 0x00042A4D, 563B.
// BFME1 donor 0bef414 AddLine.cpp port; same batch/allocator/converter as Add_Quad siblings.
void Render2DClass::Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color)
{
	GeometryOutput006e output;
	BfmeRenderVertex *vertices;
	Vector2 corner_offset(a.Y - b.Y, b.X - a.X);
	float len2 = corner_offset.Length2();
	if (len2 == 0.0f)
		return;

	float oolen = WWMath::Inv_Sqrt(len2) * width * 0.5f;
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

	float oolen = WWMath::Inv_Sqrt(len2) * width * 0.5f;
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

	BfmeUInt32 convertedColor = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color);
	vertices[0].color = vertices[1].color = convertedColor;
	BfmeUInt32 convertedColor2 = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color2);
	vertices[2].color = vertices[3].color = convertedColor2;

	output.indices[0] = output.base + 0x00010000;
	output.indices[1] = output.base + 0x00020002;
	output.indices[2] = output.base + 0x00030001;
}
