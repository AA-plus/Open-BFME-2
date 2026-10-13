// cl: /MD
// The float-pair subtraction at 0x001040AE that followed these comparisons is
// MathCoord2D's inline operator-, now rowed in GameLogic/Pathfinder/pathfinder.cpp.

// Reference semantics: BFME1 Bfme5NinetyTwo.cpp at
// 9cbfb551fe20dae985f91f2319d8997287b6a705 (unchanged from 40e7f2f).
// Retail 0x00104079..0x001040AE is a cdecl comparison of two float pairs.
// The original type and function name remain unknown; use only the native
// float[2] access contract, consistent with the adjacent subtraction above.
bool Rva00104079PairDiffers(const float *left, const float *right)
{
    int equal;
    if (left[0] == right[0] && left[1] == right[1])
        equal = 1;
    else
        equal = 0;
    unsigned char same = (unsigned char)equal;
    return same == 0;
}

// The complete native predecessor 0x0010404E..0x00104079 compares the same
// primitive float-pair access contract and returns a full integer zero/one.
// This is not the interior false-return fragment at 0x00104076.
int Rva0010404EPairEqual(const float *left, const float *right)
{
    if (left[0] == right[0] && left[1] == right[1])
        return 1;
    return 0;
}
