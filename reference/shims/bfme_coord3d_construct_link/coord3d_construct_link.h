// Link view for STLport's _Construct<Coord3D, Coord3D>.
// Retail's single copy (the body the census proves retail for every vector<Coord3D>/list<Coord3D> user)
// copies x, y, z member by member behind a null check, because retail's Coord3D has an inline copy
// constructor. The canonical POD Coord3D (Lib/Coord3D.h) copies with movsd instead, so a unit that
// includes it emits a differing COMDAT and, when it is first in link order, makes the link keep it.
// Include this right after Lib/Coord3D.h (and after <list>/<vector>): the specialization emits the
// retail shape and every inlined copy of the element takes it too.
#pragma once
#include <stl/_construct.h>

namespace _STL {
template <> inline __declspec(noinline) void _Construct<Coord3D, Coord3D>(Coord3D *p, const Coord3D &v)
{
    if (p) {
        p->x = v.x;
        p->y = v.y;
        p->z = v.z;
    }
}
}
