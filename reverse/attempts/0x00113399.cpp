// ?rva00113399@W3DTerrainBackground@@QAEXPAGPAXHHHH0AAH@Z
// partial score=0.989 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [00113399,00113C07),2158B, RET32. WorldBuilder places the body in
// W3DTerrainBackground.cpp (unnamed there). Rectangle form of the ZH
// fillVBRecursive triangle fan: clamp the (width x height) block at
// (xOffset, yOffset) to the map extent, walk its left and right edges with
// the advance helpers 0x0011274C / 0x001127F2 and emit three indices per
// fan triangle into ib (when present), counting through curIndex. Corner
// triangles are emitted only for in-mesh corners (0x001126FD); when the
// auxiliary height buffer is present every emitted triangle is also cast
// through getTriangleIntersection (0x0011319A). Retail computes the last
// triangle's right-vertex Y from the X origin (+0x50); kept as found.
// Bank state: correct 2158B size, 0x90 frame and register allocation, 12
// differing lines. The fix was defining the callees test/advanceYThenX/
// advanceScan (from Rva00729300BitPlanes.cpp) in this TU so intra-TU mod/ref
// keeps right.y in ebx, and writing (m_width + 1) inline (retail [ebp+4Ch] is
// its CSE). Remaining: commutative operand order of the minX lea, the maxY
// clamp lea and the topRight test y-arg (push edx deferred), and the
// point.x-before-m_xOrigin load order at the three later triangle starts.
// Source operand order, /EHs-c-, struct vs memberwise prev copies make no
// difference; scalar prev ints break the size. Land beside the callees.

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned short UnsignedShort;

#define MAP_XY_FACTOR 10.0f
#define MAP_HEIGHT_SCALE (10.0f / 256.0f)

class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

class BoundedShortGrid
{
public:
	short rva00062A58(Int x, Int y);
};

typedef unsigned char Byte;

struct Rva00729300Bytes
{
	Byte *m_begin;
	Byte *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	Byte operator[]( int index ) const { return m_begin[index]; }
};

class Rva00729300BitPlane
{
public:
	bool test( int x, int y ) const;

public:
	Byte m_opaque00[0x08];
	int m_width;
	int m_height;
	Byte m_opaque10[0x24];
	int m_stride;
	Byte m_opaque38[0x0c];
	Rva00729300Bytes m_bits;
};
bool Rva00729300BitPlane::test( int x, int y ) const
{
	register const Rva00729300BitPlane *self = this;
	if( x < 0 || y < 0 || y >= self->m_height || x >= self->m_width )
	{
		return false;
	}

	const int index = self->m_stride * y + (x >> 3);
	if( (unsigned)index >= self->m_bits.size() )
	{
		return false;
	}

	int mask = 1;
	mask <<= x & 7;
	Byte value = self->m_bits[index];
	bool result = (value & mask) != 0;
	return result;
}

class WorldHeightMap
{
public:
	Int getXExtent() { return m_width; }
	Int getYExtent() { return m_height; }
	Int getBorderSize() { return m_borderSize; }
	UnsignedShort getHeight(Int x, Int y) { return ((BoundedShortGrid *)this)->rva00062A58(x, y); }
	bool isInMesh(Int x, Int y) { return ((const Rva00729300BitPlane *)this)->test(x, y); }

private:
	unsigned char m_pad00[0x08];
	Int m_width;
	Int m_height;
	Int m_borderSize;
};

class Rva001127F2TerrainPrefix
{
public:
	bool advanceScan( ICoord2D &right, int xOffset, int yOffset,
		int width, int height );
    bool advanceYThenX(ICoord2D &point,int xOffset,int yOffset,int width,int height);

private:
	unsigned char m_pad00[0x50];
	int m_xOrigin;
	int m_yOrigin;
	int m_unmodelled58;
	Rva00729300BitPlane *m_map;
};



// The full BFME1 ba7ddda7 donor with the same +10 origin/map shift also
// places this entire 166B body at 1127F2..112898. Independent native RET20,
// two scan loops, ordered coordinate updates and calls to 1126FD establish
// the behavior. Its earlier bank differed in loop bounds; the donor source
// now reproduces every byte. Original owner and directional labels remain
// unproven; keep this separate observed prefix from the other receiver.
bool Rva001127F2TerrainPrefix::advanceScan( ICoord2D &right, int xOffset,
	int yOffset, int width, int height )
{
	Rva00729300BitPlane *map = m_map;
	int mapWidth = map->m_width;
	int mapHeight = map->m_height;
	int yOrigin = m_yOrigin;
	int limitX = mapWidth - m_xOrigin;
	int limitY = mapHeight - yOrigin;
	limitX--;
	limitY--;
	while( right.x < width + xOffset && right.x < limitX )
	{
		right.x++;
		if( m_map->test( right.x + m_xOrigin, right.y + m_yOrigin ) )
			return true;
	}
	while( right.y < yOffset + height - 1 && right.y < limitY - 1 )
	{
		right.y++;
		if( m_map->test( right.x + m_xOrigin, right.y + m_yOrigin ) )
			return true;
	}
	return false;
}


// Native 11274C..1127F2 is the Y-first counterpart: both loops and RET20
// independently reproduce all 166 bytes with this compatible observed prefix.
// Shared offsets do not establish a shared original class or allocation size.
bool Rva001127F2TerrainPrefix::advanceYThenX(ICoord2D &point,
    int xOffset,int yOffset,int width,int height) {
    Rva00729300BitPlane *map = m_map;
    int mapWidth = map->m_width;
    int mapHeight = map->m_height;
    int yOrigin = m_yOrigin;
    int limitX = mapWidth - m_xOrigin;
    int limitY = mapHeight - yOrigin;
    limitX--;
    limitY--;
    while (point.y < height + yOffset && point.y < limitY) {
        point.y++;
        if (m_map->test(point.x + m_xOrigin, point.y + m_yOrigin))
            return true;
    }
    while (point.x < xOffset + width - 1 && point.x < limitX - 1) {
        point.x++;
        if (m_map->test(point.x + m_xOrigin, point.y + m_yOrigin))
            return true;
    }
    return false;
}

class W3DTerrainBackground
{
public:
	void getTriangleIntersection(Vector3 *heights, int x, int y, int width, int height,
		const Vector3 &v0, const Vector3 &v1, const Vector3 &v2);
	void rva00113399(UnsignedShort *ib, void *heights, Int xOffset, Int yOffset,
		Int width, Int height, UnsignedShort *ndx, Int &curIndex);

private:
	bool advanceLeft(ICoord2D &left, Int xOffset, Int yOffset, Int width, Int height)
	{
		return ((Rva001127F2TerrainPrefix *)this)->advanceYThenX(left, xOffset, yOffset, width, height);
	}
	bool advanceRight(ICoord2D &right, Int xOffset, Int yOffset, Int width, Int height)
	{
		return ((Rva001127F2TerrainPrefix *)this)->advanceScan(right, xOffset, yOffset, width, height);
	}

	unsigned char m_pad00[0x50];
	Int m_xOrigin;
	Int m_yOrigin;
	Int m_width;
	WorldHeightMap *m_map;
};

// ?rva00113399@W3DTerrainBackground@@QAEXPAGPAXHHHH0AAH@Z
void W3DTerrainBackground::rva00113399(UnsignedShort *ib, void *heights, Int xOffset, Int yOffset,
	Int width, Int height, UnsignedShort *ndx, Int &curIndex)
{
	Int minX = m_xOrigin + xOffset;
	Int minY = m_yOrigin + yOffset;
	Int limitX = m_map->getXExtent() - 1;
	Int limitY = m_map->getYExtent() - 1;
	Int maxX = xOffset + width;
	if (maxX + m_xOrigin > limitX)
		maxX = limitX - m_xOrigin;
	Int maxY = yOffset + height;
	if (maxY + m_yOrigin > limitY)
		maxY = limitY - m_yOrigin;
	Bool topRightInMesh = m_map->isInMesh(m_xOrigin + maxX, m_yOrigin + maxY);
	Int topRightNdx = ndx[maxX + maxY * (m_width + 1)];

	ICoord2D left;
	left.x = xOffset;
	left.y = yOffset;
	ICoord2D right;
	right.x = xOffset;
	right.y = yOffset;
	advanceLeft(left, xOffset, yOffset, width, height);
	advanceRight(right, xOffset, yOffset, width, height);

	UnsignedShort prevNdxLeft;
	UnsignedShort prevNdxRight;
	if (m_map->isInMesh(minX, minY)) {
		if (ib)
			ib[curIndex] = ndx[xOffset + yOffset * (m_width + 1)];
		curIndex++;
		prevNdxRight = ndx[right.x + right.y * (m_width + 1)];
		if (ib)
			ib[curIndex] = prevNdxRight;
		curIndex++;
		prevNdxLeft = ndx[left.x + left.y * (m_width + 1)];
		if (ib)
			ib[curIndex] = prevNdxLeft;
		curIndex++;
		if (heights) {
			Vector3 v0;
			Vector3 v1;
			Vector3 v2;
			v0.X = minX * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v0.Y = minY * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v0.Z = m_map->getHeight(minX, minY) * MAP_HEIGHT_SCALE;
			v1.X = (m_xOrigin + right.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v1.Y = (m_yOrigin + right.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v1.Z = m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * MAP_HEIGHT_SCALE;
			v2.X = (m_xOrigin + left.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v2.Y = (m_yOrigin + left.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v2.Z = m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * MAP_HEIGHT_SCALE;
			getTriangleIntersection((Vector3 *)heights, xOffset, yOffset, width, height, v0, v1, v2);
		}
	} else {
		prevNdxRight = ndx[right.x + right.y * (m_width + 1)];
		prevNdxLeft = ndx[left.x + left.y * (m_width + 1)];
		curIndex++;
		curIndex++;
		curIndex++;
	}

	Bool didLeft = true;
	Bool didRight = true;
	while (didLeft || didRight) {
		ICoord2D prevLeft = left;
		didLeft = advanceLeft(left, xOffset, yOffset, width, height);
		if (didLeft) {
			if (ib)
				ib[curIndex] = prevNdxLeft;
			curIndex++;
			if (ib)
				ib[curIndex] = prevNdxRight;
			curIndex++;
			prevNdxLeft = ndx[left.x + left.y * (m_width + 1)];
			if (ib)
				ib[curIndex] = prevNdxLeft;
			curIndex++;
			if (heights) {
				Vector3 v0;
				Vector3 v1;
				Vector3 v2;
				v0.X = (m_xOrigin + prevLeft.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v0.Y = (m_yOrigin + prevLeft.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v0.Z = m_map->getHeight(m_xOrigin + prevLeft.x, m_yOrigin + prevLeft.y) * MAP_HEIGHT_SCALE;
				v1.X = (m_xOrigin + right.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v1.Y = (m_yOrigin + right.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v1.Z = m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * MAP_HEIGHT_SCALE;
				v2.X = (m_xOrigin + left.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v2.Y = (m_yOrigin + left.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v2.Z = m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * MAP_HEIGHT_SCALE;
				getTriangleIntersection((Vector3 *)heights, xOffset, yOffset, width, height, v0, v1, v2);
			}
		}
		ICoord2D prevRight = right;
		didRight = advanceRight(right, xOffset, yOffset, width, height);
		if (didRight) {
			if (ib)
				ib[curIndex] = prevNdxLeft;
			curIndex++;
			if (ib)
				ib[curIndex] = prevNdxRight;
			curIndex++;
			prevNdxRight = ndx[right.x + right.y * (m_width + 1)];
			if (ib)
				ib[curIndex] = prevNdxRight;
			curIndex++;
			if (heights) {
				Vector3 v0;
				Vector3 v1;
				Vector3 v2;
				v0.X = (m_xOrigin + left.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v0.Y = (m_yOrigin + left.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v0.Z = m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * MAP_HEIGHT_SCALE;
				v1.X = (m_xOrigin + prevRight.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v1.Y = (m_yOrigin + prevRight.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v1.Z = m_map->getHeight(m_xOrigin + prevRight.x, m_yOrigin + prevRight.y) * MAP_HEIGHT_SCALE;
				v2.X = (m_xOrigin + right.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v2.Y = (m_yOrigin + right.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v2.Z = m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * MAP_HEIGHT_SCALE;
				getTriangleIntersection((Vector3 *)heights, xOffset, yOffset, width, height, v0, v1, v2);
			}
		}
	}

	if (topRightInMesh) {
		if (ib)
			ib[curIndex] = prevNdxLeft;
		curIndex++;
		if (ib)
			ib[curIndex] = prevNdxRight;
		curIndex++;
		if (ib)
			ib[curIndex] = topRightNdx;
		curIndex++;
		if (heights) {
			Vector3 v0;
			Vector3 v1;
			Vector3 v2;
			v0.X = (m_xOrigin + left.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v0.Y = (m_yOrigin + left.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v0.Z = m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * MAP_HEIGHT_SCALE;
			v1.X = (m_xOrigin + right.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v1.Y = (m_xOrigin + right.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v1.Z = m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * MAP_HEIGHT_SCALE;
			v2.X = (minX + width) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v2.Y = (minY + width) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v2.Z = m_map->getHeight(minX + width, minY + width) * MAP_HEIGHT_SCALE;
			getTriangleIntersection((Vector3 *)heights, xOffset, yOffset, width, height, v0, v1, v2);
		}
	}
}
