// cl: /DNDEBUG /MD /EHsc /G7
// Clean donor transfer from Open-BFME-1 9e3be919b10ae956e3c8a13995e0d62f2be1d016,
// game/Libraries/Source/WWVegas/WW3D2/Rva009793C0PivotFade.cpp.
// BFME2's matched PivotClass constructor and assignment establish stride 0x58
// and a float at +0x54. The target getter establishes the pointer at this+0x14.
// The original method name and the scalar's fade meaning remain unproven.
// Visibility guide: the same donor revision's htree.h Get_Visibility body.
struct Rva0019B0B0Pivot {
    unsigned char before[0x50];
    bool visible;
    unsigned char beforeScalar[3];
    float scalar;
};
class Rva0019B0B0Tree {
public:
    float pivotScalar(int index) const;
    bool pivotVisible(int index) const;
};
float Rva0019B0B0Tree::pivotScalar(int index) const
{
    const Rva0019B0B0Pivot *pivots =
        *(Rva0019B0B0Pivot *const *)((const char *)this + 0x14);
    return pivots[index].scalar;
}

bool Rva0019B0B0Tree::pivotVisible(int index) const
{
    const Rva0019B0B0Pivot *pivots =
        *(Rva0019B0B0Pivot *const *)((const char *)this + 0x14);
    return pivots[index].visible;
}
