// cl: /O1 /G7 /MD /arch:SSE /EHsc
// Native69C5F..69CE6 full135 RET16; original method name remains unknown.
// Owner: W3DGameClient::addScorch calls67EA3 on TheTerrainRenderObject.
// That native sibling proves arrayE0 stride1C capacity500, position4/radius10,
// type14/flag18, count3790 and cached3794. This loop marks overlaps.
// Ref: BF1@575ba2b BaseHeightMap addScorch is a subsystem/layout guide;
// the overlap algorithm and every accessed target offset come from retail.
// Native uses x87 FSQRT between SSE vector length and SSE radius comparison.
// This narrow WWMath-style primitive preserves that proven x87 codegen shape.
// The location is a by-value Vector3 (W3DTerrainVisual's forwarder 0x00091EEC
// pushes its 12-byte position then the radius); this TU views it as WWMath's
// X/Y/Z float triple.
static __forceinline float scorchSqrt(float value)
{
    float result;
    __asm { fld value
            fsqrt
            fstp result }
    return result;
}
class Vector3
{
public:
    float X, Y, Z;
    Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
    __declspec(dllimport) __forceinline float Length() const { return scorchSqrt(Z*Z + Y*Y + X*X); }
};
__forceinline Vector3 operator-(const Vector3 &a,
                                           const Vector3 &b)
{
    return Vector3(a.X-b.X, a.Y-b.Y, a.Z-b.Z);
}
struct TerrainScorchEntry
{
    void *snapshotView; // untouched leading word; no original field name asserted
    Vector3 position;
    float radius;
    int type;
    bool active;
    char padding[3];
};
class BaseHeightMapRenderObjClass
{
public:
    void rva00069C5F(Vector3 location, float radius);
private:
    char unreconstructed[0xE0];
    TerrainScorchEntry scorches[500];
    int count, cached;
};
void BaseHeightMapRenderObjClass::rva00069C5F(Vector3 location, float radius)
{
    for (int i=0; i<count; ++i)
    {
        TerrainScorchEntry &scorch=scorches[i];
        Vector3 delta=location-scorch.position;
        float distance=delta.Length();
        if (scorch.radius+radius > distance) scorch.active=true;
    }
    cached=0;
}
