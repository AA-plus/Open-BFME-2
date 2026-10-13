// ?isFlankedBy@HordeContain@@UAE_NPAVObject@@@Z
// partial score=0.97 date=2026-10-13
// ?isFlankedBy@HordeContain@@UAE_NPAVObject@@@Z
// partial score=0.97 date=2026-10-13
// Retail 0x00473D55 (446B, slot 147). Owner-embedded version in
// Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
// was 442/446 with head exact through the provider gates and the found-path.
// Remaining walls (all scheduling, patterns decoded):
// (1) dir homes: retail loads attacker.x/y into xmm0/1, subs our.y then our.x,
//     stores dir.x FIRST after the cos-arg pops (no early store). Every spelling
//     tried stores one component early (single-expr x-first, y-first, split,
//     ax/ay temps). Next: y-first single-expr was closest-skewed; try struct
//     forms that delay both stores past the pops.
// (2) dot order: retail facing.y*z*x accumulating in xmm0. Mine permutes
//     (z-first). May self-heal once dir matches.
// (3) dot branch: retail reloads halfArc (movss xmm1,[ebp-8]) then
//     comiss xmm1,xmm0 + jbe. A volatile-ha copy forced the reload but landed
//     half in xmm0 with jb. Next: separate dot statement + volatile-ha read
//     after it, so dot sits in xmm0 and half reloads to xmm1.
// (4) LAND-BLOCKER (callee lane): _M_find/operator[] on map<int,
//     Rva00462D35Mapped> do not resolve (rowed 0x388f63/0x28932c are int-int
//     plus other ICF twins, none with this mapped type). operator[] folded in
//     one build, _M_find never. Needs the ICF fold-proof lane
//     (tools/pin_admission.py --add + --icf-owner style) OR same-TU emission
//     acceptance by add_match (untested: bytes were never exact).
// File diffs to re-apply (all build-green 134/134): interface gap147 ->
// isFlankedBy decl; HordeContain override decl; HordeContainModuleDataFields
// m_25C(float)/m_264(uint); HordeContain m_2CCBegin/End/Cap(float*);
// Thing::getUnitDirectionVector2D decl; Coord3D::Normalize decl;
// float Sin/Cos decls; Rva0028C197Slot149 iface.
// t=50 model=muse-spark
bool HordeContain::isFlankedBy(Object *attacker)
{
	const HordeContainModuleDataFields *data = fields();
	if (data->m_25C >= 360.0f)
		return false;
	if (!attacker->isKindOf(13))
		return false;
	Rva0028C197Slot149 *provider = (Rva0028C197Slot149 *)attacker->rva0028C197();
	if (!provider || !provider->slot149())
		return false;
	_STL::map<int, Rva00462D35Mapped>::iterator it = m_2DC.find(attacker->getID());
	if (it != m_2DC.end())
		return TheGameLogic->m_frame < (*it).second.m_bits;
	float halfArc = (float)cos(data->m_25C * 0.008725f);
	const Coord3D *ourPos = m_object->getPosition();
	Coord3D dir;
	dir.y = attacker->m_position.y - ourPos->y;
	dir.x = attacker->m_position.x - ourPos->x;
	dir.z = 0.0f;
	dir.Normalize();
	const Coord3D *facing = ((const Thing *)m_object)->getUnitDirectionVector2D();
	float ha = *(volatile float *)&halfArc;
	if (ha <= facing->y * dir.y + facing->z * dir.z + facing->x * dir.x)
		goto angleLoop;
flanked:
	m_2DC[attacker->getID()].m_bits = TheGameLogic->m_frame + data->m_264;
	m_2E8 = false;
	return true;
angleLoop:
	{
		float *angle = m_2CCBegin;
		if (angle == m_2CCEnd)
			goto noFlank;
		do {
			if (halfArc > Sin(*angle) * dir.y + Cos(*angle) * dir.x)
				goto flanked;
			++angle;
		} while (angle != m_2CCEnd);
	}
noFlank:
	m_2DC[attacker->getID()].m_bits = 0;
	return false;
}
