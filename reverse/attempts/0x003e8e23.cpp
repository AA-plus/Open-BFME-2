// ?rva003E8E23@ScriptConditions@@IAE_NPAVParameter@@000@Z
// partial score=0.97 date=2026-10-12
// Bank for ?rva003E8E23@ScriptConditions@@IAE_NPAVParameter@@000@Z 0x003E8E23 (459 B), improved 2026-10-12 (W6-S2).
// Lives at the end of Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsPlayerUnitCounts.cpp with these TU additions:
//   Rva00376A62{rva00376A84}, ObjectTypes{isInSet via cast}, ObjectTypesTemp{ctor decl, inline dtor ::delete m_types},
//   Script_objectTypesFromParam decl, ScriptEngine::rva00357475(const AsciiString&,Bool*) + getObjectTypes, member decl.
// 462 vs 459 B with ONE diff block: the return-true path's inline ObjectTypesTemp dtor. Retail: test ecx,ecx; je; mov eax,[ecx];
// push 0; call [eax]; jmp; xor eax,eax; push eax; call delete; ours (and retail's normal exit) use the CSE'd-zero form
// (xor eax,eax; cmp ecx,eax; ...). The (obj=iter2.cur())!=0 loop + _ReadWriteBarrier() at the body top (the idiom of
// rva003E8863/8B47) fixed the member register roles that blocked the old 466 B bank.
// ?rva003E8E23@ScriptConditions@@IAE_NPAVParameter@@000@Z @ 0x003E8E23 459B
// PLAYER_HAS_OBJECT_OF_VETERANCY (condition 146; BFME 1 donor ScriptConditionsRva00326F40.cpp twin): some member of the
// player's teams whose template is in the type list or equivalent to the named template has an experience rank
// that satisfies the six-way comparison against the rank parameter.
Bool ScriptConditions::rva003E8E23(Parameter *playerParm, Parameter *typeParm, Parameter *comparisonParm, Parameter *rankParm)
{
	Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357475(*playerParm->getString(), 0));
	if (!player)
		return false;
	const ThingTemplate *thingTemplate = 0;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(*typeParm->getString());
	ObjectTypesTemp typesTemp;
	if (types)
		Script_objectTypesFromParam(typeParm, typesTemp.m_types);
	else
		thingTemplate = TheThingFactory->findTemplate(*typeParm->getString());
	PlayerTeamNode *head = player->getPlayerTeams();
	for (PlayerTeamNode *it = head->m_next; it != player->getPlayerTeams(); it = it->m_next)
	{
		for (DLINK_ITERATOR<Team> iter = it->m_value->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			Object *obj;
			for (DLINK_ITERATOR<Object> iter2 = team->iterate_TeamMemberList(); (obj = iter2.cur()) != 0; iter2.advance())
			{
				_ReadWriteBarrier();
				Bool typeMatches;
				if (types)
					typeMatches = typesTemp.m_types->isInSet(obj->getTemplate());
				else
					typeMatches = obj->getTemplate()->isEquivalentTo(thingTemplate);
				if (typeMatches)
				{
					ExperienceTracker *tracker = obj->getExperienceTracker();
					if (tracker)
					{
						Int rank = tracker->getRank();
						Bool matches = false;
						switch (comparisonParm->getInt())
						{
							case 0: matches = rank < rankParm->getInt(); break;
							case 1: matches = rank <= rankParm->getInt(); break;
							case 2: matches = rank == rankParm->getInt(); break;
							case 3: matches = rank >= rankParm->getInt(); break;
							case 4: matches = rank > rankParm->getInt(); break;
							case 5: matches = rank != rankParm->getInt(); break;
						}
						if (matches == 1)
							return true;
					}
				}
			}
		}
	}
	return false;
}
