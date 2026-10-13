// ?getClosestPointOnLand@Pathfinder@@QAE_NPBUCoord3D@@PAVObject@@PAU2@@Z
// partial score=0.96 date=2026-10-13
// ?getClosestPointOnLand@Pathfinder@@QAE_NPBUCoord3D@@PAVObject@@PAU2@@Z
// partial score=0.96 date=2026-10-13
// FRAGMENT for Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp (W7-MO1 r1, 15 diffs).
// Apply: add `class Rva002E7E26;` near other fwd decls; add the two decls below
// to class Pathfinder; append the rest at EOF. All callees rowed (2EB4DF, 2E7DF5,
// 2E7E26, 6BD9C0, 36410). Padding floats read retail DBD364/DBD368 (match!).
// WALLS: (A) xmm rotation acc xmm2 vs xmm0 over 12 insns (named-const hoist,
// single-expr, scale-temp, init-then-add all zero-delta); (B) EH or[ebp-4],-1
// before lea+3rd-movs vs ours movs/or/lea (throw() on EB4DF, barrier move/remove
// all zero-or-worse). Prior bank scores .942-.9557 standalone; this TU version
// supersedes with native views + TerrainLogicWaterQuery::slot4C for isUnderwater.
class Rva002E7E26;
/// in class Pathfinder:
///  Bool getClosestPointOnLand(const Coord3D *,Object *,Coord3D *);
///  Int rva002EB4DF(const ICoord2DBase *,const ICoord2DBase *,float,Int,Rva002E7E26 *);

// Native 002EE7EE..002EE96B RET12 (381 bytes); WB D644A0 (pathfinder.cpp:12323,
// KINDOF_SHIP assert) independently names Pathfinder::getClosestPointOnLand.
// Object geometry (+0xA8) and facing (+0x44) are target offsets; the visitor
// layout (closest result +0x10, availability byte +0x20) is shared with the
// rowed 49B constructor 0x002E7DF5 and the 176B callback 0x002E7E26.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
struct _Rva002E7DF5Cell { int x, y, z; };
class Rva002E7DF5
{
public:
	Rva002E7DF5(int, const _Rva002E7DF5Cell &) throw();
	int owner;
	int sourceWords[3];
	Coord3D closest;
	float cost;
	bool found;
};
float BfmeShipLandPaddingX = 20.0f;
float BfmeShipLandPaddingY = 20.0f;
Bool Pathfinder::getClosestPointOnLand(const Coord3D *position, Object *object, Coord3D *out)
{
	if (((TerrainLogicWaterQuery *)TheTerrainLogic)->slot4C(position->x, position->y, 0, 0, 0)) {
		union { int alignment; char bytes[sizeof(Rva002E7DF5)]; } storage;
		{
			GeometryShape shape;
			reinterpret_cast<const GeometryInfo *>((const char *)object + 0xa8)->rva006BD9C0(shape);
			const float &minorRef = shape.minor;
			float minorSize = minorRef;
			minorSize += BfmeShipLandPaddingY;
			minorSize *= 2.0f;
			minorSize *= 0.1f;
			int minorCells = (int)minorSize;
			const float &majorRef = shape.major;
			float majorSize = majorRef;
			majorSize += BfmeShipLandPaddingX;
			majorSize *= 2.0f;
			majorSize *= 0.1f;
			int majorCells = (int)majorSize;
			ICoord2DBase diameter = { majorCells, minorCells };
			new ((void *)&storage) Rva002E7DF5((int)this, *reinterpret_cast<const _Rva002E7DF5Cell *>(position));
			int y = realToIntFloor(position->y * 0.1f + 0.5f);
			int x = realToIntFloor(position->x * 0.1f + 0.5f);
			ICoord2DBase center = { x, y };
			rva002EB4DF(&center, &diameter, object->m_orientation, 1, reinterpret_cast<Rva002E7E26 *>(&storage));
			*out = reinterpret_cast<Rva002E7DF5 *>(&storage)->closest;
		}
		_ReadWriteBarrier();
		return reinterpret_cast<Rva002E7DF5 *>(&storage)->found;
	}
	else {
		*out = *position;
		return true;
	}
}
