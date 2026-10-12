// ?InternalFindPath@Pathfinder@@QAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@2PAVHierarchicalPath@@PA_N@Z
// partial score=0.95 date=2026-10-13
// ?InternalFindPath@Pathfinder@@QAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@2PAVHierarchicalPath@@PA_N@Z
// Bank: apply these class-view edits to Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp
// (diff vs master at bank time), then append the body below. Compiles to 3443B there.
// 61a62,63
// >     // The same KindOf bit read as BitFlags words (dword tests in retail).
// >     __forceinline unsigned int testKindWord(unsigned int bit) const { return ((const unsigned int *)kinds)[bit>>5] & (1u<<(bit&31)); }
// 124a127,128
// > 	void rva002655E3(const Coord3D *pos, PathfindLayerEnum layer, Int portal);
// > 	void SetLastNodePortal(Int portal);
// 145c149
// < struct PathfinderGroundInfo { PathfinderCostCellInfo position;Int parent;Waypoint *parentWaypoint;unsigned short totalCost,costSoFar;char pad14[0x2c-0x14];unsigned int flags; };
// ---
// > struct PathfinderGroundInfo { PathfinderCostCellInfo position;Int parent;Waypoint *parentWaypoint;unsigned short totalCost,costSoFar;char pad14[0x28-0x14];ObjectID obstacleID;unsigned int flags; };
// 179a184
// >  Bool IsObstaclePresent(ObjectID) const;
// 556a562,564
// > struct PathfinderMineshaft { Int m_00; Int m_portal; Int m_08; Coord3D m_position; };
// > struct TCheckMovementInfo;
// > class HierarchicalPath;
// 584a593,597
// > 	Path *InternalFindPath(Object *,const LocomotorSet &,const Coord3D *,const Coord3D *,HierarchicalPath *,Bool *);
// > 	Int rva002F83F5(PathfindCell *,PathfindCell *,const LocomotorSet &,Bool,Bool,Int,ICoord2D *,Object *,Int);
// > 	Bool checkForMovement(Object *,TCheckMovementInfo &);
// > 	Bool rva002EDFF9(Object *,Coord3D *);
// > 	void rva002E75A3(Coord3D *,Coord3D *);
// 641c654,656
// <     MixFileInfoBuffer *m_closedList;Bool m_isTunneling;char m_pad039[0x5c-0x39];
// ---
// >     MixFileInfoBuffer *m_closedList;Bool m_isTunneling;char m_pad039[0x48-0x39];
// > 	ObjectID m_ignoreObstacleID;	// +0x48
// > 	char m_pad04C[0x5c-0x4c];
// 651c666,669
// <  char pad1c1d8[0x1d1f0-0x1c1d8];PathfinderOpenQueue m_openCells;
// ---
// >  // +0x1C1D8/+0x1C1DC: mine-shaft portals; WorldBuilder asserts m_destMineshaft
// >  // on the second. Each carries a zone/portal ID at +4 and its position at +0xC.
// >  PathfinderMineshaft *m_srcMineshaft,*m_destMineshaft;
// >  char pad1c1e0[0x1d1f0-0x1c1e0];PathfinderOpenQueue m_openCells;
// Pathfinder::InternalFindPath, retail [0x002FBBEB,0x002FC95E) RET24, 3443
// bytes. WorldBuilder D55050 names it (its "CritterDesync" log strings and the
// pathfinder.cpp asserts); the A* spine is Zero Hour's internalFindPath. BFME
// adds the CRC log, the KindOf 186 forward goal offset and its retry from the
// unshifted goal, the checkForMovement destination probes, the mine-shaft
// redirect, the hierarchical-path closest-cell fallback and the early give-up
// distance. The 9-argument neighbour expansion 0x002F83F5 is Zero Hour's
// examineNeighboringCells call shape (unnamed in WorldBuilder).
struct TCheckMovementInfo
{
	ICoord2D cell;					// +0x00
	PathfindLayerEnum layer;		// +0x08
	Int radius;						// +0x0C
	Bool centerInCell;				// +0x10
	Bool m_11;
	unsigned char m_pad12[2];
	unsigned int m_14;				// +0x14 option bits
	ObjectID m_18;					// +0x18 an object to ignore
	unsigned char m_1C[0x10];		// +0x1C the mover's Rva002E8BCF
	Int m_2C;
	Bool m_30,m_31,m_32;
	unsigned char m_pad33;
	Int m_34;
};
class Rva002E6FDF { public: Rva002E6FDF *rva002E6FDF(); };
class HierarchicalPath { public: Int lookUpPositionOnPath(const Coord3D *); };
struct PathfinderCellLimitView { char pad[0x1210]; unsigned int maxCells; };
extern Int PathfinderSearchCellsVisited;	// 0x00DFF0CC, also cleared by FindSafePath
// The cell centre Rva002E8C23Call builds into a scratch the caller destroys.
struct PathfinderCellCenter { Coord3D pos; __forceinline PathfinderCellCenter() {} __forceinline ~PathfinderCellCenter() {} };
// A Bool argument travels as its whole stack dword (push dword ptr [bool]).
static __forceinline void *boolArg(const Bool &value) { return *(void *const *)&value; }
static __forceinline Bool pathfinderLogOn() { return g_00E03745 && g_00DFEFF0; }
static __forceinline void pathfinderLog(const char *text) { fprintf((PathfinderLogFile *)g_00DFEFF0,text); }
// Coord2D::Rotate(float) inlined: the CRT pair runs, then fsincos replaces it.
static __forceinline void rotateOffset(float &x, float &y, float angle)
{
	struct { float cosine; float sine; } trig;
	trig.sine = (float)sin(angle);
	trig.cosine = (float)cos(angle);
	__asm
	{
		fld angle
		fsincos
		fstp trig.cosine
		fstp trig.sine
	}
	float &sine = trig.sine;
	float &cosine = trig.cosine;
	float rotated = x * cosine - y * sine;
	y = y * cosine + x * sine;
	x = rotated;
}
static __forceinline void readMoverInfo(TCheckMovementInfo &info, Object *obj)
{
	char *ai = obj->m_258;
	info.m_18 = ai ? (ObjectID)((const Rva0006E009DwordField *)ai)->get() : (ObjectID)0;
}
Path *Pathfinder::InternalFindPath(Object *obj, const LocomotorSet &locomotorSet, const Coord3D *from,
	const Coord3D *rawTo, HierarchicalPath *hierarchicalPath, Bool *destinationAdjusted)
{
	if (g_00DFEFF0)
		pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() called");
	Bool goalBlocked = false;
	Bool centerInCell = true;
	Int radius = 0;
	Rva002EBCA7Split(obj, &radius, (unsigned char *)&centerInCell);

	Bool isHuman = true;
	if (obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType == 1) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 1");
		isHuman = false;
	}

	if (rawTo->x == 0.0f && rawTo->y == 0.0f) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 2 return NULL");
		return NULL;
	}
	if (!m_isMapReady) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 3 return NULL");
		return NULL;
	}

	Coord3D adjustTo;
	copyCoord3D(&adjustTo, rawTo);
	Coord3D clipFrom;
	copyCoord3D(&clipFrom, from);
	rva002E75A3(&clipFrom, &adjustTo);

	if (!centerInCell) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 4");
		adjustTo.x += 5.0f;
		adjustTo.y += 5.0f;
	}
	Coord3D unshiftedTo;
	copyCoord3D(&unshiftedTo, &adjustTo);

	if (obj->m_template->testKindWord(186)) {
		float offsetX = 20.0f;
		float offsetY = 0.0f;
		rotateOffset(offsetX, offsetY, obj->GetGoalAngle() + 3.14159265359f);
		adjustTo.x += offsetX;
		adjustTo.y += offsetY;
	}

	m_isTunneling = false;
	PathfindLayerEnum destinationLayer = TheTerrainLogic->getLayerForDestination(NULL, &adjustTo);
	PathfindCell *goalCell = (PathfindCell *)rva001E3647Pos(destinationLayer, &adjustTo);
	if (goalCell == NULL) {
		if (!obj->m_template->testKindWord(186))
			return NULL;
		adjustTo = unshiftedTo;
		goalCell = (PathfindCell *)rva001E3647Pos(destinationLayer, &adjustTo);
		if (goalCell == NULL)
			return NULL;
	}

	ICoord2D cell;
	Rva002E7875WorldToCell(&cell, true, &adjustTo);
	TCheckMovementInfo info;
	((Rva002E6FDF *)&info)->rva002E6FDF();
	info.cell = cell;
	info.layer = destinationLayer;
	info.radius = 1;
	info.centerInCell = centerInCell;
	info.m_14 = 0xC;
	if (!obj->m_template->testKindWord(90))
		info.m_14 |= 0x10;
	readMoverInfo(info, obj);
	info.m_11 = true;
	{
		Int priority = obj->m_template->priority;
		Bool flag = obj->m_template->flag;
		char *ai = obj->m_258;
		*(Rva002E8BCF *)info.m_1C = Rva002E8BCF((const Rva002E8BCFSrc *)(ai + 0x1CC), !flag, priority - 1, obj->rva0028AFBB());
	}
	Int blockers;
	if (!CheckDestination(obj, cell.x, cell.y, destinationLayer, radius, centerInCell, &blockers, true)
		|| !checkForMovement(obj, info)) {
		if (obj->m_template->testKindWord(186)) {
			adjustTo = unshiftedTo;
			destinationLayer = TheTerrainLogic->getLayerForDestination(NULL, &adjustTo);
			goalCell = (PathfindCell *)rva001E3647Pos(destinationLayer, &adjustTo);
			if (goalCell == NULL)
				return NULL;
			cell = *Rva002E7875WorldToCell(&cell, true, &adjustTo);
			info.cell = cell;
			if (!CheckDestination(obj, cell.x, cell.y, destinationLayer, radius, centerInCell, &blockers, true)
				|| !checkForMovement(obj, info))
				goalBlocked = true;
		} else {
			goalBlocked = true;
		}
	}

	Rva002E7875WorldToCell(&cell, true, &clipFrom);
	PathfindLayerEnum layer = (PathfindLayerEnum)obj->rva0028B511();
	PathfindCell *parentCell = rva002E8BF8(layer, &clipFrom);
	if (parentCell == NULL) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 7 return NULL");
		return NULL;
	}

	Bool viaMineshaft = false;
	if (m_srcMineshaft && m_destMineshaft && m_srcMineshaft != m_destMineshaft) {
		for (const Rva002F35AFHop *hop = m_1C1CC.begin(); hop != m_1C1CC.end(); ++hop) {
			if (hop->m_zone == m_srcMineshaft->m_portal) {
				viaMineshaft = true;
				adjustTo = m_srcMineshaft->m_position;
				rva002E75A3(&clipFrom, &adjustTo);
				unshiftedTo = adjustTo;
				destinationLayer = TheTerrainLogic->getLayerForDestination(NULL, &adjustTo);
				goalCell = (PathfindCell *)rva001E3647Pos(destinationLayer, &adjustTo);
				break;
			}
		}
	}

	goalCell->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&cell, true, &adjustTo));
	if (parentCell != goalCell) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 8");
		parentCell->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&cell, true, &clipFrom));
	}

	if (parentCell->getType() == PathfindCell::CELL_OBSTACLE
		&& (parentCell->m_pathInfo ? parentCell->m_pathInfo->obstacleID : (ObjectID)0) != m_ignoreObstacleID) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 9");
		m_isTunneling = true;
	} else {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 10");
		m_isTunneling = false;
	}

	if (((const Rva0028B984ByteField *)obj)->get()) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 11");
		parentCell->StartPathfind((Int)goalCell);
		parentCell->m_pathInfo->totalCost = (unsigned short)rva002F0A72(parentCell, goalCell);
		AddToOpenList(parentCell);
		Path *path = BuildActualPath(obj, locomotorSet.getValidSurfaces(), from, goalCell, centerInCell, false, true);
		rva002F40E7();
		goalCell->ReleaseInfo();
		if (pathfinderLogOn())
			fprintf((PathfinderLogFile *)g_00DFEFF0, "CritterDesync:    Pathfinder::InternalFindPath() 12 return %s", path ? "VALID" : "NULL");
		return path;
	}

	Int priority = obj->m_template->priority;
	Bool flag = obj->m_template->flag;
	Rva002E8BCF moverInfo((const Rva002E8BCFSrc *)&locomotorSet, !flag, priority - 1, obj->rva0028AFBB());
	Rva002E99F9Sub460 *zones = (Rva002E99F9Sub460 *)&m_zoneManager;
	Int zone1 = zones->rva0053241F(&moverInfo, parentCell->quickZone());
	Int zone2 = zones->rva0053241F(&moverInfo, goalCell->quickZone());
	if (goalCell->IsObstaclePresent(m_ignoreObstacleID) || parentCell->IsObstaclePresent(m_ignoreObstacleID) || m_isTunneling) {
		zone2 = zones->rva00531FD4(&moverInfo, (unsigned short)zone2);
		zone2 = zones->rva0053241F(&moverInfo, (unsigned short)zone2);
		zone1 = zones->rva00531FD4(&moverInfo, (unsigned short)zone1);
		zone1 = zones->rva0053241F(&moverInfo, (unsigned short)zone1);
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 13");
	}
	if (zone1 != zone2) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:\tPathfinder::InternalFindPath() 13.5");
		if (!rva002F4115(obj, zone1, zone2, NULL))
			goalBlocked = true;
	}
	if (!IsValidMovementPositionForObject(&adjustTo, destinationLayer, locomotorSet.getValidSurfaces(), obj))
		goalBlocked = true;
	if (!IsValidMovementPositionForObject(from, layer, locomotorSet.getValidSurfaces(), obj)) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 16");
		m_isTunneling = true;
	}
	if (!m_isTunneling) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 17");
		((Rva002E6FDF *)&info)->rva002E6FDF();
		info.layer = (PathfindLayerEnum)parentCell->getLayer();
		info.centerInCell = centerInCell;
		info.radius = radius;
		info.m_14 = 0;
		readMoverInfo(info, obj);
		info.cell = *Rva002E7875WorldToCell(&cell, true, &clipFrom);
		info.m_11 = true;
		if (!checkForMovement(obj, info)) {
			if (pathfinderLogOn())
				pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 18");
			m_isTunneling = true;
		}
	}

	parentCell->StartPathfind((Int)goalCell);
	parentCell->m_pathInfo->totalCost = (unsigned short)rva002F0A72(parentCell, goalCell);
	AddToOpenList(parentCell);

	Int cellCount = 0;
	PathfinderSearchCellsVisited = 0;
	PathfindCell *closestCell = NULL;
	Int closestPathIndex = 0;
	Int closestDist = 0x7fffffff;
	Int nearestGoalDist = 0x7fffffff;
	Int giveUpDist = 0x7fffffff;
	while ((parentCell = rva002F36E5()) != NULL) {
		if (parentCell == goalCell) {
			m_isTunneling = false;
			Path *path = BuildActualPath(obj, locomotorSet.getValidSurfaces(), from, goalCell, centerInCell, false, false);
			if (viaMineshaft) {
				path->rva002655E3(&m_srcMineshaft->m_position,
					TheTerrainLogic->getLayerForDestination(NULL, &m_srcMineshaft->m_position), m_srcMineshaft->m_portal);
				path->rva002655E3(&m_destMineshaft->m_position,
					TheTerrainLogic->getLayerForDestination(NULL, &m_destMineshaft->m_position), 0x7fffffff);
				path->SetLastNodePortal(m_destMineshaft->m_portal);
			}
			Coord3D direction = *((const Thing *)obj)->getUnitDirectionVector2D();
			path->rva00365E98(obj, &direction, locomotorSet.getValidSurfaces(), false);
			rva002F40E7();
			parentCell->ReleaseInfo();
			if (pathfinderLogOn())
				fprintf((PathfinderLogFile *)g_00DFEFF0, "CritterDesync:    Pathfinder::InternalFindPath() 19 return %s", path ? "VALID" : "NULL");
			return path;
		}

		parentCell->PutOnClosedList(&m_closedList);
		if ((unsigned int)cellCount > ((const PathfinderCellLimitView *)TheWritableGlobalData)->maxCells) {
			if (pathfinderLogOn())
				pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 20 failed path break");
			break;
		}

		if (!m_isTunneling) {
			Int dx = abs(goalCell->getXIndex() - parentCell->getXIndex());
			Int dy = abs(goalCell->getYIndex() - parentCell->getYIndex());
			Int dist = dx*dx + dy*dy;
			if (dist < nearestGoalDist) {
				if (dx + dy > 25) {
					float reach = (float)(sqrt((double)dist) + 25.0f);
					giveUpDist = (Int)(reach * reach);
				} else {
					giveUpDist = dist * 4;
				}
				nearestGoalDist = dist;
			}
			dist += (Int)m_1C1CC.size()*10*10*100;
			if (hierarchicalPath) {
				Int pathIndex = hierarchicalPath->lookUpPositionOnPath((const Coord3D *)parentCell->m_pathInfo);
				if (pathIndex > closestPathIndex || (pathIndex == closestPathIndex && dist < closestDist)) {
					closestDist = dist;
					closestPathIndex = pathIndex;
					if (bfmeWrapE6E90(obj, (void *)parentCell->getXIndex(), (void *)parentCell->getYIndex(),
							(void *)parentCell->getLayer(), (void *)radius, boolArg(centerInCell))
						&& ((Rva002E6DC4 *)this)->rva002E6DC4(&moverInfo, parentCell)
						&& rva002EDFF9(obj, (Coord3D *)Rva002E8C23Call((Int)&PathfinderCellCenter(), centerInCell, (Rva002E8C23Param *)parentCell)))
						closestCell = parentCell;
				}
			} else if (dist < closestDist) {
				closestDist = dist;
				if (bfmeWrapE6E90(obj, (void *)parentCell->getXIndex(), (void *)parentCell->getYIndex(),
						(void *)parentCell->getLayer(), (void *)radius, boolArg(centerInCell))
					&& ((Rva002E6DC4 *)this)->rva002E6DC4(&moverInfo, parentCell)
					&& rva002EDFF9(obj, (Coord3D *)Rva002E8C23Call((Int)&PathfinderCellCenter(), centerInCell, (Rva002E8C23Param *)parentCell)))
					closestCell = parentCell;
			}
		}

		if (goalBlocked) {
			Int dx = abs(goalCell->getXIndex() - parentCell->getXIndex());
			Int dy = abs(goalCell->getYIndex() - parentCell->getYIndex());
			Int dist = dx*dx + dy*dy;
			if (dist > giveUpDist) {
				Bool giveUp = false;
				if (hierarchicalPath == NULL)
					giveUp = true;
				if (cellCount > 2000)
					giveUp = true;
				if (dist < 100)
					giveUp = false;
				if (giveUp)
					continue;
			}
		}

		CheckChangeLayers(parentCell, obj);
		cellCount += rva002F83F5(parentCell, goalCell, locomotorSet, isHuman, centerInCell, radius, &cell, obj, 0);
	}

	if (pathfinderLogOn())
		pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 21");
	if (closestCell) {
		*destinationAdjusted = true;
		m_isTunneling = false;
		Path *path = BuildActualPath(obj, locomotorSet.getValidSurfaces(), from, closestCell, centerInCell, false, true);
		rva002F40E7();
		goalCell->ReleaseInfo();
		return path;
	}
	m_isTunneling = false;
	rva002F40E7();
	goalCell->ReleaseInfo();
	if (pathfinderLogOn())
		pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 24 return NULL");
	return NULL;
}
