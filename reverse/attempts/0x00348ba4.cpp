// ?computePath@AIAttackMeleeHordeApproachTargetState@@MAE_NXZ
// partial score=0.99 date=2026-10-12
diff --git a/Code/GameEngine/Source/GameLogic/AI/AIStatesBfmeOnExit.cpp b/Code/GameEngine/Source/GameLogic/AI/AIStatesBfmeOnExit.cpp
index 832a2011ce..f78960573c 100644
--- a/Code/GameEngine/Source/GameLogic/AI/AIStatesBfmeOnExit.cpp
+++ b/Code/GameEngine/Source/GameLogic/AI/AIStatesBfmeOnExit.cpp
@@ -206,6 +206,8 @@ public:
 	// The rowed Int body at 0x002F1BA2 (PathfinderCoordLineWalk.cpp); its callers
 	// test only al, so this TU calls it through a Bool view.
 	Bool Rva002F1BA2(void *obj, void *surfaces, PathfindLayerEnum layer, const Coord3D *from, const Coord3D *to);
+	Bool IsLineBlocked(void *obj, void *surfaces, PathfindLayerEnum layer, const Coord3D *from, const Coord3D *to);
+	Bool AdjustHordeMeleeDestination(Object *obj, void *arg, Coord3D *dest);
 };
 class AI
 {
@@ -472,6 +474,8 @@ public:
 	void friend_setGoalObject(Object *obj);
 	const LocomotorSet &getLocomotorSet() const { return *(const LocomotorSet *)m_locomotorSet; }
 	Path *getPath() const { return m_path; }
+	Bool isWaitingForPath() const { return m_bfmeFlag3B1; }
+	void setPathExtraDistance(Real dist);
 	Bool getBfmeFlag3B1() const { return m_bfmeFlag3B1; }
 	void *getValidLocomotorSurfaces() const { return m_validLocomotorSurfaces; }
 private:
@@ -518,6 +522,7 @@ class ThingTemplate
 public:
 	Bool testKindByte115() const { return (m_kindOf[1] & 0x20) != 0; }
 	Bool testKindByte11F() const { return (m_kindOf[11] & 0x80) != 0; }
+	Bool testKindByte108() const { return (m_pad00[0x108] & 0x80) != 0; }
 	Real getBfmeReal53C() const { return m_bfmeReal53C; }
 private:
 	unsigned char m_pad00[0x114];
@@ -539,6 +544,10 @@ struct Coord3D
 	void sub(const Coord3D *a) { x -= a->x; y -= a->y; z -= a->z; }
 	void add(const Coord3D *a) { x += a->x; y += a->y; z += a->z; }
 	Real length() const;
+	void normalize();
+	Real GetLength() const;
+	void set(const Coord3D *p) { x = p->x; y = p->y; z = p->z; }
+	Coord3D &operator*=(Real s) { x *= s; y *= s; z *= s; return *this; }
 };
 
 // The contain module's slot 87 hands back the position an entering unit
@@ -623,6 +632,7 @@ public:
 	void setOrientation(Real angle);
 	void setPosition(const Coord3D *pos);
 	Bool isAboveTerrain() const;
+	const Coord3D *getUnitDirectionVector2D() const;
 private:
 	unsigned char m_pad00[0x04];
 	const ThingTemplate *m_template; // +0x04
@@ -659,6 +669,9 @@ public:
 	Real GetRelativeAngle(const Coord3D *pos) const;
 	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
 	void rva0028AD32();
+	void rva0028ACDC(const Coord3D *pos);
+	bool isMobile() const;
+	Real rva002C97E8(const Coord3D *from, const Coord3D *to) const;
 	void rva0028AE6D();
 	void *rva0028C197() const;
 	int rva0028B511() const;
@@ -1606,3 +1619,134 @@ StateReturnType AIAttackMeleeHordeApproachTargetState::update()
 	return STATE_CONTINUE;
 	}
 }
+extern const int g_009BA4E4;
+Bool rva003449C5(Coord3D *goalPos, Object *source, Object *victim);
+static __declspec(noinline) Bool isSamePosition(const Coord3D *ourPos,
+	const Coord3D *prevTargetPos, const Coord3D *curTargetPos)
+{
+	Coord3D diff;
+	diff.x = curTargetPos->x - prevTargetPos->x;
+	diff.y = curTargetPos->y - prevTargetPos->y;
+	Coord3D toTarget;
+	toTarget.x = curTargetPos->x - ourPos->x;
+	toTarget.y = curTargetPos->y - ourPos->y;
+	const float TOLERANCE_FACTOR = 1.0f / (10.0f * 10.0f);
+	float toleranceSqr = (toTarget.x*toTarget.x+toTarget.y*toTarget.y) * TOLERANCE_FACTOR;
+	if (diff.x * diff.x + diff.y * diff.y > toleranceSqr)
+		return false;
+	return true;
+}
+
+Bool AIAttackMeleeHordeApproachTargetState::computePath()
+{
+	Bool forceRepath = false;
+	m_successOnPathFailure = false;
+	Object *source = getMachineOwner();
+	if (!source->isMobile())
+		return false;
+	AIUpdateInterface *ai = source->getAI();
+	if (m_waitingForPath)
+		return true;
+	if (!ai->getPath() && !ai->isWaitingForPath())
+		forceRepath = true;
+	if (!forceRepath && TheGameLogic->getFrame() - m_approachTimestamp < (unsigned int)g_009BA4E4)
+		return true;
+	m_approachTimestamp = TheGameLogic->getFrame();
+
+	Object *victim = getMachine()->getGoalObject();
+	if (victim)
+	{
+		if (victim->testStatus(OBJECT_STATUS_BFME_26) && victim->getContainedBy())
+			victim = victim->getContainedBy();
+		// if our victim's position hasn't changed, don't re-path
+		if (!forceRepath && isSamePosition(source->getPosition(), &m_prevVictimPos, victim->getPosition()))
+			return true;
+		if (!source->getCurrentWeapon(0))
+			return false;
+
+		m_prevVictimPos = *victim->getPosition();
+		ai->ignoreObstacle(0);
+		ai->setPathExtraDistance(100.0f);
+		Coord3D *goal = &m_goalPosition;
+		*goal = m_prevVictimPos;
+		Coord3D delta;
+		Coord3D *d = &delta;
+		d->x = goal->x;
+		d->y = goal->y;
+		d->z = goal->z;
+		if (rva00344EB2Gate(source, victim)
+			&& TheAI->pathfinder()->QuickDoesPathExist(source, source->getPosition(), victim->getPosition(), 0))
+		{
+			delta = *victim->getUnitDirectionVector2D();
+			MemberwiseCoord3D scaled(delta);
+			scaled *= victim->getBoundingCircleRadius() * 2.0f + 60.0f;
+			scaled.z += goal->z;
+			scaled.x += goal->x;
+			scaled.y += goal->y;
+			m_goalPosition.set(&scaled);
+			TheAI->pathfinder()->adjustToPossibleDestination(source, ai->getLocomotorSet(), goal);
+			critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 23");
+			setAdjustsDestination(false);
+			ai->requestPath(goal, false);
+			m_waitingForPath = ai->isWaitingForPath();
+			if (ai->getPath())
+				m_waitingForPath = false;
+			return true;
+		}
+		{
+			delta.sub(source->getPosition());
+			delta.normalize();
+			delta.scale(source->getBoundingCircleRadius() * 0.7f);
+			if (victim->rva0028B511() == 1)
+			{
+				Coord3D destination;
+				destination.set(goal);
+				destination.sub(&delta);
+				if (!TheAI->pathfinder()->IsLineBlocked(source, ai->getValidLocomotorSurfaces(),
+						LAYER_GROUND, goal, &destination))
+					*goal = destination;
+				if (victim->getTemplate()->testKindByte108())
+					rva00344D60(goal, source, victim);
+			}
+			if (!rva003449C5(goal, source, victim))
+			{
+				m_successOnPathFailure = true;
+				return false;
+			}
+			source->rva0028AD32();
+			if (!m_isInitialApproach)
+				rva00344D60(goal, source, 0);
+			Coord3D adjusted;
+			adjusted.x = goal->x;
+			adjusted.y = goal->y;
+			adjusted.z = goal->z;
+			if (!TheAI->pathfinder()->AdjustHordeMeleeDestination(source, (void*)&ai->getLocomotorSet(), &adjusted) && !m_isInitialApproach)
+				return true;
+			*goal = adjusted;
+			Real before = victim->rva002C97E8(victim->getPosition(), source->getPosition());
+			Real after = victim->rva002C97E8(victim->getPosition(), goal);
+			delta = *goal;
+			delta.sub(source->getPosition());
+			Real improvement = before - after;
+			Real dist = delta.GetLength();
+			if (improvement < dist * 0.5f && ai->getPath() && source->getContain())
+			{
+				HordeContainInterface *horde = source->getContain()->getHordeContainInterface();
+				if (horde && horde->isMeleeTargetReady(victim))
+				{
+					m_successOnPathFailure = true;
+					return false;
+				}
+			}
+			if (m_isInitialApproach)
+				source->rva0028ACDC(goal);
+		}
+		ai->requestPath(goal, false);
+		m_waitingForPath = ai->isWaitingForPath();
+		if (ai->getPath())
+			m_waitingForPath = false;
+		return true;
+	}
+	return false;
+}
+
