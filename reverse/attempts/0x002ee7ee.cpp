// ?getClosestPointOnLand@Pathfinder@@QAE_NPBUCoord3D@@PAVObject@@PAU2@@Z
// partial score=0.9795 date=2026-10-13
// FRAGMENT for Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp.
// Apply to the home TU at 21fd99a5b7: add class Rva002E7E26; before Pathfinder,
// add these two public declarations, then append the definitions below:
// Bool getClosestPointOnLand(const Coord3D*,Object*,Coord3D*);
// Int rva002EB4DF(const ICoord2DBase*,const ICoord2DBase*,float,Int,Rva002E7E26*);
// Use the home flags /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc and canonical headers.
// WB D644A0, pathfinder.cpp12323; retail 002EE7EE..002EE96B, RET 12, frame 5C.
// Full 381-byte body, every call resolves. All arithmetic is now exact:
// reference-bound inline operands/constants reproduce native XMM2/0/1.
// The existing g_00DBD33C[16] data owner supplies padding words at DBD364/368;
// do not add overlapping data rows or new address-named padding globals.
// Remaining only: ours OR [ebp-4],-1 precedes the output copy; retail places
// it after the second MOVSD, then LEA ECX before the third MOVSD. Same EH state.
// Real visitor/rectangle/polygon visibility plus visitor ctor also permits a
// natural local visitor without the storage/barrier, but perturbs arithmetic
// scheduling and does not fix this final cleanup-order difference.
// No exact claim: a future landing must run the entire home TU's byte gates.
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

static __forceinline int landCells(const float & radius,const float & padding){const float & scale=2.0f;const float & inv=0.1f;return (int)(((radius+padding)*scale)*inv);}
Bool Pathfinder::getClosestPointOnLand(const Coord3D *position, Object *object, Coord3D *out)
{
	if (((TerrainLogicWaterQuery *)TheTerrainLogic)->slot4C(position->x, position->y, 0, 0, 0)) {
		union { int alignment; char bytes[sizeof(Rva002E7DF5)]; } storage;
		{
			GeometryShape shape;
			reinterpret_cast<const GeometryInfo *>((const char *)object + 0xa8)->rva006BD9C0(shape);
int minorCells=landCells(shape.minor,(*reinterpret_cast<const float *>(&g_00DBD33C[11])));
int majorCells=landCells(shape.major,(*reinterpret_cast<const float *>(&g_00DBD33C[10])));
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
