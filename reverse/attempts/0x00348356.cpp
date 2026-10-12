// ?updateInternal@AIAttackApproachTargetState@@AAE?AW4StateReturnType@@XZ
// partial score=0.85 date=2026-10-12
// ?updateInternal@AIAttackApproachTargetState@@AAE?AW4StateReturnType@@XZ
// partial current-TU port date=2026-10-12
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// Port of the Oct-9 bank into the current TU: needs its views; append after
// the TU's own views and adapt getAI->getObservedAI.
static __forceinline void coordScale(Coord3D* a, Real n) {a->x*=n; a->y*=n; a->z*=n;}
static __forceinline void coordAdd(Coord3D* a,const Coord3D* b) {a->x+=b->x;a->y+=b->y;a->z+=b->z;}
struct ApproachLogStatusView {unsigned char pad[0x1B4]; Int value;};

StateReturnType AIAttackApproachTargetState::updateInternal()
{
	AIUpdateInterface *ai = getMachineOwner()->getObservedAI();
	if (((TurretStateMachine *)getMachine())->rva004D7ADD())
	{
		ai->notifyVictimIsDead();
		ai->setCurrentVictim(0);
		return STATE_FAILURE;
	}

	m_stopIfInRange = !ai->isAttackPath();
	if (m_waiting)
		m_stopIfInRange = true;

	Object *source = getMachineOwner();
	Weapon *weapon = source->getCurrentWeapon();
	Object *victim = getMachineGoalObject();
	if (weapon && ((const Rva002C9400ByteField *)weapon->getTemplate())->get())
		m_stopIfInRange = false;

	if (victim)
	{
		if (victim->testStatus(OBJECT_STATUS_33))
			return STATE_FAILURE;
		if (victim->rva002943B2(source->getControllingPlayer()))
			return STATE_FAILURE;

		ai->setCurrentVictim(victim);

		Bool lead = rva00344EB2Gate(source, victim);
		Bool inRange = false;
		if (weapon)
		{
			if (lead)
			{
				Coord3D pos;
				pos.x = victim->getPosition()->x;
				pos.y = victim->getPosition()->y;
				pos.z = victim->getPosition()->z;
				const Coord3D *victimDir = victim->getUnitDirectionVector2D();
				Coord3D dir;
				dir.x = victimDir->x;
				dir.y = victimDir->y;
				dir.z = victimDir->z;
				Real dist = victim->rva0028AC7D() * 4.0f;
				coordScale(&dir,dist);
				coordAdd(&pos,&dir);
				inRange = ((Rva002C9B80Owner *)weapon)->isWithinAttackRange(source, source->getPosition(),
					victim, &pos, 0.0f, true);
			}
			else
			{
				inRange = weapon->isWithinAttackRange((const Object *)source, victim, 0.0f, 1);
			}
		}
		Bool viewBlocked = !rva003430A3(source, victim, weapon);

		if (weapon && weapon->getTemplate()->isContactWeapon() && inRange)
			return STATE_SUCCESS;
		if (m_stopIfInRange && weapon && inRange && ai->isDoingGroundMovement() &&
			!victim->isSignificantlyAboveTerrain() && !viewBlocked)
			return STATE_SUCCESS;

		if (m_waiting)
			return TheGameLogic->getFrame() > m_waitFrame ? STATE_FAILURE : STATE_CONTINUE;

		if (ai->getAIUpdateModuleData()->m_24 && source->rva0028B511() >= 17 && !inRange &&
			!ai->isQuickPathAvailable(victim->getPosition()))
		{
			m_waiting = true;
			m_waitFrame = TheGameLogic->getFrame() + LOGICFRAMES_PER_SECOND * 10;
			return STATE_CONTINUE;
		}

		Bool checkRange = true;
		Int stateID = ai->rva00260DED();
		if (stateID == 0x11)
			checkRange = false;
		if (stateID == 0x10)
			checkRange = false;
		if (stateID == 0x23)
			checkRange = false;
		if (!ai->m_3c7)
			checkRange = false;
		Team *team = source->m_team;
		if (team && team->m_proto->m_216 && team->getTeamTargetObject())
			checkRange = false;
		if (checkRange && !rva00344EB2Gate(source, victim))
			checkRange = false;
		if (checkRange)
		{
			Real range = ai->getAIUpdateModuleData()->m_20;
			if (range > 0.0f)
			{
				Coord3D delta;
				delta.x = victim->getPosition()->x - source->getPosition()->x;
				delta.y = victim->getPosition()->y - source->getPosition()->y;
				delta.z = victim->getPosition()->z - source->getPosition()->z;
				Real dist = delta.length();
				UnsignedInt mood = ai->getMoodMatrixValue();
				if ((mood & MM_Controller_Player) == 0)
				{
					switch (mood & MM_Mood_Bitmask)
					{
						case MM_Mood_Sleep:
							range = 0.0f;
							break;
						case MM_Mood_Alert:
							range *= TheAI->getAiData()->m_alertRangeModifier;
							break;
						case MM_Mood_Aggressive:
							range *= TheAI->getAiData()->m_aggressiveRangeModifier;
							break;
					}
				}
				if (dist > range)
					return STATE_FAILURE;
			}
		}

		if (computePath() == false)
		{
			if (theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile, "%i AIAttackApproachTargetState success [3]", source->m_id);
			return STATE_SUCCESS;
		}
		if (m_waiting)
			return STATE_CONTINUE;

		StateReturnType code = AIInternalMoveToState::update();
		if (code == STATE_CONTINUE)
			return code;

		const Coord3D *victimPos = victim->getPosition();
		Real vdx = victimPos->x - m_prevVictimPos.x;
		Real vdy = victimPos->y - m_prevVictimPos.y;
		Real vdz = victimPos->z - m_prevVictimPos.z;
		Real odx = m_ownerPosition.x - source->getPosition()->x;
		Real ody = m_ownerPosition.y - source->getPosition()->y;
		Real odz = m_ownerPosition.z - source->getPosition()->z;
		Bool victimMoved = vdz * vdz + vdy * vdy + vdx * vdx > 100.0f;
		Bool ownerMoved = odz * odz + ody * ody + odx * odx > 100.0f;
		if (inRange && !viewBlocked)
			return STATE_SUCCESS;
		if (victimMoved || ownerMoved)
			return STATE_SUCCESS;
		if (TheAI->pathfinder()->CanApproachToTarget(source, victimPos, (Rva002C9B80Owner *)weapon, false))
			return STATE_SUCCESS;
		m_waiting = true;
		m_waitFrame = TheGameLogic->getFrame() + LOGICFRAMES_PER_SECOND * 10;
		return STATE_CONTINUE;
	}

	if (((const ApproachLogStatusView*)TheGameLogic)->value > 0 && m_stopIfInRange && weapon)
	{
		if (theLogicRandomLogFile)
			fprintf(theLogicRandomLogFile, "masiwar called by AIAttackApproachTargetState::updateInternal [2]");
	}
	if (m_stopIfInRange && weapon && weapon->isWithinAttackRange(source, &m_goalPosition, 0.0f, 1))
	{
		Bool viewBlocked = false;
		if (ai->isDoingGroundMovement())
			viewBlocked = TheAI->pathfinder()->isAttackViewBlockedByObstacle(source, source->getPosition(), 0, &m_goalPosition);
		if (!viewBlocked)
			return STATE_SUCCESS;
	}
	if (computePath() == false)
		return STATE_FAILURE;
	return AIInternalMoveToState::update();
}
