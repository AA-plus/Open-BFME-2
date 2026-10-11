// cl: /O1 /arch:SSE /G7 /Oy- /MD
// Native 002F600C..002F6075, framed ECX member and RET 16. EAX is zero
// on every exit. The original class, argument roles and query are unknown.
// The target compares packed input bits 4..9 with receiver +14, passes
// thirteen arguments to 002F52A7 (RET 52, AL result), and on success with
// the updated first word zero sets byte +18 and copies +1C's XYZ to +28.
// These declarations are measured ABI views, not recovered source types.
struct Rva002F600CCoord { float x, y, z; };
struct Rva002F600CMetadata
{
    unsigned char prefix0C[12];
    unsigned int packed;
};
class Rva002F52A7Query;

// LINK: 0x002F52A7 is rowed as Pathfinder::CheckForAdjust (pathfinder.cpp); the query object is the pathfinder and the old
// all-integer call shape stays through a member-pointer cast.
class Object;
class LocomotorSet;
struct Coord3D;
enum PathfindLayerEnum { BFME_LAYER_GROUND };
class Pathfinder
{
public:
    bool CheckForAdjust(Object *obj, const LocomotorSet &locoSet, bool a, int b, int c, PathfindLayerEnum layer, int d,
        bool e, Coord3D *position, const Coord3D *zero, float value, int *word, int finalZero);
};
typedef bool (Pathfinder::*Rva002F52A7Shape)(unsigned int, unsigned int, unsigned char, unsigned int, unsigned int, unsigned int,
    unsigned int, unsigned char, Rva002F600CCoord *, unsigned int, float, unsigned int *, unsigned int);
class Rva002F600CContext
{
public:
    int rva002F600C(unsigned int word, const Rva002F600CMetadata *metadata,
        unsigned int c, unsigned int d);
private:
    Rva002F52A7Query *query;
    unsigned int word04, word08, word0C;
    unsigned char option10;
    unsigned char padding11[3];
    unsigned int kind14;
    bool success18;
    unsigned char padding19[3];
    Rva002F600CCoord position1C, position28;
};

// ?rva002F600C@Rva002F600CContext@@QAEHIPBURva002F600CMetadata@@II@Z
int Rva002F600CContext::rva002F600C(unsigned int word,
    const Rva002F600CMetadata *metadata, unsigned int c, unsigned int d)
{
    if (word)
    {
        unsigned int kind = (metadata->packed >> 4) & 63;
        if (kind14 == kind &&
            (((Pathfinder *)query)->*reinterpret_cast<Rva002F52A7Shape>(&Pathfinder::CheckForAdjust))(word04, word08, 1, c, d, kind, word0C,
                option10, &position1C, 0, 0.0f, &word, 0) && !word)
        {
            success18 = true;
            position28 = position1C;
        }
    }
    return 0;
}
