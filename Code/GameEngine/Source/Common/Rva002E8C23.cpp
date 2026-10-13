// cl: /MD
// 0x002E8C23 (Rva002E8C23Call) now lives in GameLogic/Pathfinder/pathfinder.cpp.
#include "../../../Libraries/Include/Lib/Coord3D.h"

bool __cdecl Rva002EBBFBIsOdd(void *p);

#include "../../../Libraries/Include/Lib/ICoord2D.h"

ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);

class Object;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

struct Rva002E8C23Pair
{
	int m00;
	int m04;
};

// ?Rva002E8C4DCall@@YAHHEPAURva002E8C23Pair@@H@Z @0x002E8C4D 33B: free cdecl wrapper
// passing through two ints plus fields from ptr+0/+4 to pinned 0x002E79A8;
// evidence pin ?rva002E79A8@@YAXHEHHH@Z and LINK 5 files plus adjacent row 0x002E8C23.
int __cdecl Rva002E8C4DCall(int a1, unsigned char a2, Rva002E8C23Pair *a3, int a4);

// @0x002EDE5B 80B dump lane range 13. Terrain cell resolve: IsOdd flag,
// TerrainLogic layer for (a, pos), WorldToCell into a cell temp, rowed 8C4D
// query, 12B cell written back over pos. Identity unproven.
// Note: retail keeps the IsOdd byte in a dword slot and pushes the whole
// slot for the bool center arg; *(bool *)&flag reproduces that raw push
// (a plain unsigned char arg would emit a normalizing cmp/setne).
int __cdecl Rva002EDE5B(void *a, Coord3D *pos)
{
	unsigned char flag = Rva002EBBFBIsOdd(a);
	ICoord2D tmpC;
	Coord3D tmp18;
	int cell = Rva002E8C4DCall((int)&tmp18, flag, (Rva002E8C23Pair *)Rva002E7875WorldToCell(&tmpC, *(bool *)&flag, pos), TheTerrainLogic->getLayerForDestination((Object *)a, pos));
	Coord3D *src = (Coord3D *)cell;
	*pos = *src;
	return cell;
}
