// cl: /G7 /O1 /arch:SSE /ICode/Libraries/Include/Lib
// stlport
//
// ?rva000062FD@Rva000062FDRegion@@QBE_NABVCoord2D@@0@Z @0x000062FD (294B), RET 8.
// Native 62FD..6423 and WB 0x426C30: two-axis slab test of a segment (origin,
// delta) against the 16-byte rectangle in ECX (x_min,y_min,x_max,y_max floats).
// Per axis: a delta within +-0.0001 (areApproxEqual(d, 0, 0.0001), inlined as
// d < tol && d > -tol) means the origin must lie inside the slab, else the two
// slab entry parameters (extent - origin) * (1 / d) are ordered through
// address-taken locals (they live in the dead parameter slots) and the segment
// is rejected when the nearer one is beyond 1 or the farther one is negative.
// The y axis ends in one combined `||` test. Named after its address, not
// Region2D: the canonical Region2D header carries no methods and a private copy
// of it is refused (the caller Rva00261D2EFilter.cpp casts to this view).
#include "Coord2D.h"

class Rva000062FDRegion
{
public:
    bool rva000062FD(const Coord2D &start, const Coord2D &delta) const;

    float x_min;
    float y_min;
    float x_max;
    float y_max;
};

static __forceinline bool areApproxEqual(float a, float b, float tol) { return a < b + tol && a > b - tol; }
bool Rva000062FDRegion::rva000062FD(const Coord2D &start, const Coord2D &delta) const
{
    if (areApproxEqual(delta.x, 0.0f, 0.0001f))
    {
        if (x_min > start.x || start.x > x_max)
            return false;
    }
    else
    {
        float t1 = (x_min - start.x) * (1.0f / delta.x);
        float t2 = (x_max - start.x) * (1.0f / delta.x);
        float *pmin = t1 < t2 ? &t1 : &t2;
        float vmin = *pmin;
        float *pmax = t1 > t2 ? &t1 : &t2;
        if (vmin > 1.0f)
            return false;
        if (*pmax < 0.0f)
            return false;
    }
    if (areApproxEqual(delta.y, 0.0f, 0.0001f))
    {
        if (y_min > start.y || start.y > y_max)
            return false;
    }
    else
    {
        float t1 = (y_min - start.y) * (1.0f / delta.y);
        float t2 = (y_max - start.y) * (1.0f / delta.y);
        float *pmin = t1 < t2 ? &t1 : &t2;
        float vmin = *pmin;
        float *pmax = t1 > t2 ? &t1 : &t2;
        if (vmin > 1.0f || *pmax < 0.0f)
            return false;
    }
    return true;
}
