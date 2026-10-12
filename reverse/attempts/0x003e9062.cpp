// ?evaluateSkirmishSpecialPowerIsReady@ScriptConditions@@IAE_NPAVParameter@@0@Z
// partial score=0.93 date=2026-10-12
// Bank for ?evaluateSkirmishSpecialPowerIsReady@ScriptConditions@@IAE_NPAVParameter@@0@Z 0x003E9062 (404 B).
// Lives at the end of Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_evaluateTeamStateIs.cpp
// with these additions to that TU: Parameter gets `unsigned char m_pad1C[4]; int m_cachedFrame; // +0x20`
// after m_afterString[8]; BitFlags<N> gets `bool any() const;`; ObjectStatusTypes gets OBJECT_STATUS_02 = 2;
// Object gets `SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *) const;` and
// `bool isDisabled() const;` defined after BitFlags as ((const BitFlags<11>*)((const char*)this+0x1C8))->any();
// ScriptConditions gets the member declaration. Compiles 411 vs 404 B: frame matches (0x34), diffs are
// register roles only (retail keeps pPower in EDI at entry and reloads it after each team iteration, ours EBX;
// retail keeps the player-list node in memory ([ebp+8]) where ours uses EDI; mov edx,eax before test of player).
// Retail passes iter.cur() (not pObj) to canUseSpecialPower: pObj's register is reused for the module.
// ?evaluateSkirmishSpecialPowerIsReady@ScriptConditions@@IAE_NPAVParameter@@0@Z,
// retail 0x003E9062 (404 bytes, EH, RET 8): Zero Hour's body (BFME 1 donor
// ScriptConditionsSkirmishSpecialPowerIsReady.cpp): the power parameter
// caches -1 (never true) or the frame it may next be ready (at Parameter+0x20
// here); per player of the mask, each member of each team instance of each
// team prototype that is neither under construction nor disabled, has the
// power's module and may use it (SpecialPowerStore::canUseSpecialPower)
// reports ready, else lowers the next frame to its ready frame. Target
// evidence: the rowed callees and the SKIRMISH_SPECIAL_POWER_READY name come
// from the donor identity; this dispatcher slot is not independently named.
class SpecialPowerTemplate;

class SpecialPowerModuleInterface
{
public:
	virtual void slot00();
	virtual bool isReady() const;
	virtual void slot08();
	virtual void slot0C();
	virtual unsigned int getReadyFrame() const;
};

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
	bool canUseSpecialPower(Object *obj, const SpecialPowerTemplate *power);
};
extern SpecialPowerStore *TheSpecialPowerStore;

bool ScriptConditions::evaluateSkirmishSpecialPowerIsReady(Parameter *pSkirmishPlayerParm, Parameter *pPower)
{
	if (pPower->m_cachedFrame == -1)
		return false;
	if (pPower->m_cachedFrame > 0 && (unsigned int)pPower->m_cachedFrame > TheGameLogic->getFrame())
		return false;
	unsigned int nextFrame = g_009BA4E4 * 10 + TheGameLogic->getFrame();
	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate(pPower->getString());
	if (power == 0) {
		pPower->m_cachedFrame = -1;
		return false;
	}

	int mask = TheScriptEngine->rva00357B82(pSkirmishPlayerParm);
	while (mask) {
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
		if (pPlayer == 0)
			continue;
		for (PlayerTeamList::const_iterator it = pPlayer->getPlayerTeams()->begin(); it != pPlayer->getPlayerTeams()->end(); ++it) {
			for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
				Team *team = iter.cur();
				for (DLINK_ITERATOR<Object> oiter = team->iterate_TeamMemberList(); !oiter.done(); oiter.advance()) {
					Object *pObj = oiter.cur();
					if (pObj == 0)
						continue;
					if (pObj->testStatus(OBJECT_STATUS_02) || pObj->isDisabled())
						continue;
					SpecialPowerModuleInterface *mod = pObj->getSpecialPowerModule(power);
					if (mod) {
						if (!TheSpecialPowerStore->canUseSpecialPower(oiter.cur(), power))
							continue;
						if (mod->isReady())
							return true;
						if (mod->getReadyFrame() < nextFrame)
							nextFrame = mod->getReadyFrame();
					}
				}
			}
		}
	}
	pPower->m_cachedFrame = nextFrame;
	return false;
}
