// ?IsValidHordeMemberRegularMovement@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@11@Z
// partial score=0.5 date=2026-10-13
// ?IsValidHordeMemberRegularMovement@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@11@Z
// partial (W7-MO1 r1, ~120 line-diffs, mostly by-value call region).
// FRAGMENT for Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp: needs
// `Bool IsValidHordeMemberRegularMovement(...);` + `Int rva002EB4DF...` style decl in
// class Pathfinder (see decl), Rva002F06A3Template + SameCell fwd decls below.
// KEY FINDING: retail builds by-value args field-by-field (dword MOVES) + saves esp
// after each (no EH frame). Landed PathfinderSelectBridgeLayer.cpp PROVES the recipe:
// shadow param type with user copy-ctor + dtor (Rva002ED236Pos). CONFLICT: SameCell is
// rowed with canonical POD Coord3D params, so the shadow-typed call cannot resolve.
// BLOCKED on class-lane: re-row SameCell with shadow params OR prove canonical dtor.
// Middle/late body (locomotor/layer/cell/link-bit logic) untested pending call fix.
// Native 0x002F06A3..0x002F07F5 RET16 (338 bytes); WB D60E80
// (pathfinder.cpp:11414..11416, position asserts) identifies
// Pathfinder::IsValidHordeMemberRegularMovement. True when the rowed static
// 0x002EE49B accepts the move over the two by-value positions; otherwise the
// destination cell must suit the member's locomotor set, and a layer change
// from `from` must connect and not leave for a flagged layer. The template
// count/flag live at +0x56C/+0x634; the locomotor source rides at AI+0x1CC.
struct Rva002F06A3Template
{
	char m_pad000[0x56C];
	Int m_56C;
	char m_pad570[0x634 - 0x570];
	unsigned char m_634;
};
bool __stdcall Rva002EE49BSameCell(void *object, Coord3D first, Coord3D second);
Bool Pathfinder::IsValidHordeMemberRegularMovement(Object *obj, const Coord3D *from,
	const Coord3D *to, const Coord3D *other)
{
	if (Rva002EE49BSameCell(obj, *to, *other))
		return true;
	unsigned char flag = ((const Rva002F06A3Template *)obj->m_template)->m_634;
	Int count = ((const Rva002F06A3Template *)obj->m_template)->m_56C;
	char *ai = (char *)obj->getAI();
	Rva002E8BCF locomotors((const Rva002E8BCFSrc *)(ai + 0x1CC),
		flag == 0, count - 1, obj->rva0028AFBB());
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(obj, to);
	ICoord2D cell;
	Rva002EBC14Cell(&cell, obj, to);
	PathfindCell *toCell = getCell(layer, cell.x, cell.y);
	if (!((Rva002E6DC4 *)this)->rva002E6DC4(&locomotors, toCell))
		return false;
	PathfindLayerEnum fromLayer = TheTerrainLogic->getLayerForDestination(obj, from);
	if (fromLayer == layer)
		return true;
	Rva002EBC14Cell(&cell, obj, from);
	PathfindCell *fromCell = getCell(fromLayer, cell.x, cell.y);
	unsigned int toInfo = toCell->m_info;
	unsigned int fromInfo = fromCell->m_info;
	if (((toInfo >> 6) ^ fromInfo) & 0x3f0)
	{
		if (!(((fromInfo >> 6) ^ toInfo) & 0x3f0))
			return false;
	}
	if (fromLayer != PATHFIND_LAYER_GROUND)
	{
		if (fromLayer == 16)
			return true;
		if (!(unsigned char)Rva002E6E8AGet(fromLayer))
			return true;
	}
	if (layer == 16)
		return true;
	return false;
}
