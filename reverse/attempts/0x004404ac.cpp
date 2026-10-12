// ?rva004404AC@AptMpGameSetup@@QAEX_NH@Z
// partial score=0.8 date=2026-10-13
// Home TU (views/flags): Code/GameEngine/Source/GameClient/GUI/MpGameSetupSlots.cpp; needs its class views + pins 2156/3879 + rowed callees. 513/526B v1, systematic reg rotation.
// ?rva004404AC@AptMpGameSetup@@QAEX_NH@Z, retail 0x004404AC, 526 bytes.
// Slot-widget refresh gate: clamp the slot, gate the color combo on
// observer state, enable handicap/hero/template combos, hide lists,
// refresh the hero display and push the map-preview flag from an AI search.
// BFME2 facts (all retail-measured): slot index reuses edi; observer lives
// in bl with a byte home; the color combo copies by the folded ctor;
// hero enable uses m_rules.m_00, hide gating uses m_rules.m_04; the tail
// AI search double-calls getConstSlot like the donor.
void AptMpGameSetup::rva004404AC(bool enable, int slot)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	bool observer;
	bool foundAI;
	if (!game)
		return;
	if (slot == -1 || slot >= 8)
		slot = game->v13();
	if (slot != -1 && slot < 8)
	{
		observer = game->getConstSlot(slot)->isObserver();
		MpGameSetupComboRef combo(m_colorCombo[slot]);
		if (combo.m_window != NULL)
		{
			if (observer)
				combo.rva00323736(true);
			combo.m_window->winEnable(enable && !observer);
		}
	}
	if (m_handicap[slot] != NULL)
		m_handicap[slot]->winEnable(enable && !observer);
	GameWindow *hero = m_hero[slot];
	if (hero != NULL)
	{
		if (m_rules.m_00 == 1)
			hero->winEnable(enable && !observer);
		else
		{
			hero->winEnable(false);
			if (Rva00322910(hero) != 0)
			{
				GadgetComboBoxSetSelectedPos(hero, 0, 0);
				HandleHeroSelection(slot);
			}
		}
		UpdateHeroDisplay(slot);
	}
	if (m_playerTemplate[slot] != NULL)
		m_playerTemplate[slot]->winEnable(enable);
	GameWindow **teamCombo = &m_team[slot];
	if (*teamCombo != NULL)
	{
		bool hideDone;
		if (enable && !observer && m_rules.m_04 == 1)
			hideDone = true;
		else
		{
			GadgetComboBoxHideList(*teamCombo);
			hideDone = false;
		}
		(*teamCombo)->winEnable(hideDone);
	}
	if (game->v13() == slot)
	{
		if (enable)
		{
			if (game->getConstSlot(game->v13())->m_hasMap)
			{
				if (!observer)
					foundAI = true;
				else if (game->v12())
				{
					for (int i = 0; i < 8; ++i)
					{
						if (!game->getConstSlot(i))
							continue;
						if (game->getConstSlot(i)->isAI())
						{
							foundAI = true;
							break;
						}
					}
				}
			}
		}
	}
	((AptMapPreview *)&m_60)->rva0057C597(foundAI);
}
