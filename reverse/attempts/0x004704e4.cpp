// ?notifyOfMemberDeath@HordeContain@@UAEXPAVObject@@@Z
// partial score=0.85 date=2026-10-13
// ?notifyOfMemberDeath@HordeContain@@UAEXPAVObject@@@Z
// partial score=0.85 date=2026-10-13
// Retail 0x004704E4 (563B). Owner-embedded port in HordeContainIface11CSlots.cpp
// compiles 579B (+16B). Head exact through EH prolog. Walls:
// (1) prologue: retail sub-0x54 + and-mem scratch-zero + test-edi, no ebx;
//     mine sub-0x58 + push-ebx + xor-ebx + cmp-reg (extra dword home + pinned
//     ebx-zero for null-check). Same ebx-zero family as SidesList/CrashSite.
// (2) real callee Drawable::rva00272945(int) identified (rowed 0x00272945)
//     and wired via owner Drawable decl (resolves now).
// Infra KEPT in owner file (build-green 134/134): gap13->notifyOfMemberDeath
// REVERTED (link hazard), override decl REVERTED; helper views + owner
// Drawable::rva00272945 decl KEPT. Method reverted below.
// t=30 model=muse-spark
// ?notifyOfMemberDeath@HordeContain@@UAEXPAVObject@@@Z @0x004704E4 (563B,
// slot after rva00469F2F of the +0x11C vtable 0x00C44C58). Death cleanup:
// special-unit/producer removal, flank/kind gates, map/list erasure, empty
//-horde teardown with Eva event, frame stamp, drawable refresh and the
// special-unit + refill tail. Evidence: WB 0x10B3BB0 branch structure +
// retail 563B; offsets shared with the rows above.
void HordeContain::notifyOfMemberDeath(Object *obj)
{
	union { Rva0046247DPair pair; struct { int pad; int id; } words; } scratch;
	scratch.pair.m04 = 0;
	if (!obj)
		return;
	((HordeDeathControl *)m_2C8)->slot6(obj);
	if (!((Rva004693AD *)(UpdateModule *)this)->rva004693AD((Rva004693ADArg *)obj)) {
		scratch.words.id = obj->getID();
		m_194.push_front(m_17C[scratch.words.id]);
	}
	if (obj->isKindOf(HORDE_DEATH_KIND)) {
		Object *other = TheGameLogic->findObjectByID((ObjectID)obj->getID());
		if (other) {
			Rva00265254 mask(0, 0x67, 0x69, 0x1bb);
			((Rva001E42F2 *)other)->rva001E42F2(mask.words);
			((Rva0030A92C *)other)->rva0030A92C(((HordeDeathHeight *)TheTerrainLogic)->height(obj->m_position.x, obj->m_position.y, obj->rva0028B511(), false, true));
		}
	}
	if (obj->m_254) {
		const unsigned *data = ((HordeDeathBody *)obj->m_254)->slot15();
		if (data)
			m_29C = data[2];
		else
			m_29C = 0;
	}
	scratch.words.id = obj->getID();
	((Rva00463D9BTree *)&m_17C)->erase(*(const Rva00463D9BElement *)&scratch.words.id);
	scratch.words.id = obj->getID();
	m_170.erase(scratch.words.id);
	while (((UpdateModule *)this)->rva00470B21()) {
	}
	const _STL::list<Object *> *items = ((Rva0046247DPair *)((Rva0046247D *)(UpdateModule *)this)->rva0046247D(scratch.pair))->m04;
	if (items->empty() && m_170.empty()) {
		TheEva->reportEvaEvent(((HordeDeathDataView *)m_moduleData)->deathEvent, &obj->m_position, 0);
		TheGameLogic->destroyObject(m_object);
	}
	m_298 = TheGameLogic->m_frame;
	if (TheWritableGlobalData->m_9A6) {
		Drawable *drawable = ((Thing *)m_object)->getDrawable();
		if (drawable && ((HordeDeathDrawable *)drawable)->refresh)
			drawable->rva00272945(((HordeDeathInterface *)(Rva0046BB38Iface11C *)this)->slot96(0));
	}
	checkSpecialUnitDeath(obj);
	const HordeContainModuleDataFields *md = fields();
	if (md && !md->m_1D8) {
		_STL::list<const Object *> contained;
		rva0046D1F7(contained);
		if ((unsigned)((Rva00291793 *)&contained)->rva00291793() < md->m_268)
			rva004696E5();
	}
}
