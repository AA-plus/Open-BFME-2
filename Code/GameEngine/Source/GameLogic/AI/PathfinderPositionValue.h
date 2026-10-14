#ifndef BFME2_PATHFINDER_POSITION_VALUE_H
#define BFME2_PATHFINDER_POSITION_VALUE_H

#include "../../../../Libraries/Include/Lib/Coord3D.h"

// The by-value position at native 0x002EE49B has the canonical three-float
// layout and a memberwise copy constructor. Native caller 0x00471464 builds
// each stack argument component by component; WB 0x00D63210 tracks both
// argument destructors. Keep the ABI value view separate from the layout-only
// canonical Coord3D so unrelated users do not acquire nontrivial copy behavior.
struct Rva002EE49BPosition : Coord3D
{
    Rva002EE49BPosition(const Coord3D &p) { x = p.x; y = p.y; z = p.z; }
    Rva002EE49BPosition(const Rva002EE49BPosition &p) { x = p.x; y = p.y; z = p.z; }
    ~Rva002EE49BPosition() {}
};

#endif
