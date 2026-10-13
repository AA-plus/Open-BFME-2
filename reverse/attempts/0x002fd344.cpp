// ?FindPath@Pathfinder@@QAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@2PA_N@Z
// partial score=0.99 date=2026-10-13
// ?FindPath@Pathfinder@@QAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@2PA_N@Z
// partial score=0.99 date=2026-10-13
// Home TU: Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp (its own
// // cl: line). This bank is a patch fragment against master 506dfa240e, not a
// standalone TU (the full TU exceeds the 64 KiB stash limit). Apply:
//  1. class LocomotorSet: add
//       const char *name() const { return m_nameBuffer ? m_nameBuffer+8 : ""; }
//     and after m_scalesWalls: char m_gap16[2]; char *m_nameBuffer;
//  2. class PathfindZoneManager: add void rva005312BE(); void rva00531300();
//  3. class Pathfinder, after InternalFindPath:
//       Path *FindPath(Object *,const LocomotorSet &,const Coord3D *,const Coord3D *,Bool *);
//  4. Insert the code below right after Pathfinder::InternalFindPath's body.
// W7-MP5 r3: the erase no longer needs a pin. Replacing the inlined
// m_1C1CC.clear() with a call through a distinct 12-byte view type
// `struct Gen_p12pod { int words[3]; }` makes _STL::vector<Gen_p12pod>::erase
// compile in this unit (same 3-pointer layout) and the REL32 resolves by that
// mangled name to the rowed ICF body 0x002A133B. Add the Gen_p12pod struct at
// file scope in the inserted block and clear via:
//   { _STL::vector<Gen_p12pod> *hops = reinterpret_cast<_STL::vector<Gen_p12pod> *>(&m_1C1CC);
//     hops->erase(hops->begin(), hops->end()); }
// Result under explain_mismatch: 781 bytes, 2 diffs left:
//  - 2fd505/2fd50a loop-latch reloads of the scaled delta: retail reloads
//    y (xmm2,[ebp-0x20]) before x (xmm1,[ebp-0x24]); ours x then y. Tried and
//    no better: explicit sub/scale, while loop, Bool local, scale local, delta
//    at function scope, derived Coord3D with inline set/sub/scale, every sub and
//    scale permutation (9..13 diffs), direct GetLength, explicit delta init,
//    loop-body y-first explicit subs, S2 carriers on the loop/break conditions
//    (add bytes), step/increment forms. The latch load order is the scheduler's.
// Key fix (20 -> 3 diffs): the in-TU noinline inline Coord3D::length,
// GetLength and Normalize. Without their bodies cl 7.1 under /EHsc keeps
// delta's and destination's slots apart (frame 0x24, not 0x18) and swaps
// xmm1/xmm3; only-length or only-Normalize visible leaves 20 diffs. /EHa
// packs the slots but breaks EH-state order (61 diffs). The inner block
// around the handle packs it into the dead rawTo slot [ebp+0x14] (45 without).
// Coord3D::sub and Coord3D::scale as Zero Hour's header defines them inline.
// The 12-byte hop record view whose erase mangles to the ICF-shared
// vector<Gen_p12pod>::erase body at 0x002A133B.
struct Gen_p12pod { int words[3]; };
static __forceinline void subCoord3D(Coord3D *dst, const Coord3D *a)
{
	dst->x -= a->x;
	dst->y -= a->y;
	dst->z -= a->z;
}
static __forceinline void scaleCoord3D(Coord3D *dst, float scale)
{
	dst->x *= scale;
	dst->y *= scale;
	dst->z *= scale;
}
// coord3d.cpp's select-any Coord3D bodies, visible here so cl sees they keep
// no pointer to the vector FindPath measures and normalizes.
__declspec(noinline) inline float Coord3D::length() const { return (float)sqrt(x * x + y * y + z * z); }
__declspec(noinline) inline float Coord3D::GetLength() const
{
	float x_value = x;
	float y_value = y;
	float z_value = z;
	return (float)sqrt(x_value * x_value + y_value * y_value + z_value * z_value);
}
__declspec(noinline) inline float Coord3D::Normalize()
{
	float len = GetLength();
	float scale = 1.0f / len;
	x *= scale;
	y *= scale;
	z *= scale;
	return len;
}
// The hierarchical search result is released by the rowed 0x002EAD62.
class Rva002EAD62 { public: void rva002EAD62(); };
struct PathfinderSearchHandle {
	HierarchicalPath *path;
	__forceinline PathfinderSearchHandle(HierarchicalPath *p) : path(p) {}
	__forceinline ~PathfinderSearchHandle() { ((Rva002EAD62 *)this)->rva002EAD62(); }
};
// Retail 2FD344..2FD651 and WB D48230 identify FindPath and its five args.
// ZH findPath supplies hierarchical search before the direct search; target
// adds the diagnostic stream, quick-path backoff and destination-adjust flag.
Path *Pathfinder::FindPath(Object *obj, const LocomotorSet &locos, const Coord3D *from,
	const Coord3D *rawTo, Bool *destinationAdjusted)
{
	if (g_00E03745) {
		if (g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0, "CritterDesync:    Pathfinder::FindPath() called");
		if (g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0, "    obj=%s, locomotorSet=%s, from=%g,%g,%g, to=%g,%g,%g",
			obj->m_template->name(), locos.name(), from->x, from->y, from->z, rawTo->x, rawTo->y, rawTo->z);
	}
	*destinationAdjusted = false;
	Bool human = true;
	if (obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType == 1) {
		if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0, "CritterDesync:    isHuman set to FALSE");
		human = false;
	}
	Coord3D adjusted; copyCoord3D(&adjusted, rawTo);
	if (!QuickDoesPathExist(obj, from, &adjusted, 0)) {
		*destinationAdjusted = true;
		Coord3D delta; copyCoord3D(&delta, &adjusted);
		subCoord3D(&delta, from);
		delta.z = 0;
		Int steps = (Int)(delta.length() / 30.0f) - 1;
		if (steps > 5) steps = 5;
		delta.Normalize();
		scaleCoord3D(&delta, 30.0f);
		for (Int i = 0; i < steps; i++) {
			subCoord3D(&adjusted, &delta);
			if (QuickDoesPathExist(obj, from, &adjusted, 0)) break;
		}
	}
	{
		_STL::vector<Gen_p12pod> *hops = reinterpret_cast<_STL::vector<Gen_p12pod> *>(&m_1C1CC);
		hops->erase(hops->begin(), hops->end());
	} m_zoneManager.rva005312BE();
	m_srcMineshaft = 0; m_destMineshaft = 0;
	{
	Coord3D destination; copyCoord3D(&destination, &adjusted);
	PathfinderSearchHandle hierarchical((HierarchicalPath *)FindClosestHierarchicalPath(human, locos, obj, from, &adjusted, false, &destination));
	if (!hierarchical.path) {
		if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0, "CritterDesync:    FindHierarchicalPath fails");
		m_zoneManager.rva00531300();
	} else if (destination.x != adjusted.x || destination.y != adjusted.y) *destinationAdjusted = true;
	return InternalFindPath(obj, locos, from, &destination, hierarchical.path, destinationAdjusted);
	}
}
