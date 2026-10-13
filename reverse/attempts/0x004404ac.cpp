// ?rva004404AC@AptMpGameSetup@@QAEX_NH@Z
// partial score=0.85 date=2026-10-13
// ?rva004404AC@AptMpGameSetup@@QAEX_NH@Z
// partial score=0.85 date=2026-10-13
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// FRAGMENT for Code/GameEngine/Source/GameClient/GUI/MpGameSetupSlots.cpp (needs its class views).
// 513/526B. R3: holder lever puts game in EBX (was EDI); this/slot stay EDI/ESI vs retail ESI/EDI (+SIB fallout).
// observer stays home-al vs retail bl. s-early/s-late tried (one normalizes, one keeps shape). Untried: count-ordering levers.

// Retail 0x004404AC, 526 bytes: slot-widget enable cascade (see bank note).
void AptMpGameSetup::rva004404AC(bool enable, int slot)
{
	Rva0043DA65 *holder = m_game;
	GameInfo *game = (GameInfo *)holder->rva0043DA65();
	int s = slot;
	bool observer;
	bool foundAI;
	if (!game)
		return;
	if (s == -1 || s >= 8)
		s = game->v13();
	if (s != -1 && s < 8)
	{
		observer = game->getConstSlot(s)->isObserver();
		MpGameSetupComboRef combo(m_colorCombo[s]);
		if (combo.m_window != NULL)
		{
			if (observer)
				combo.rva00323736(true);
			combo.m_window->winEnable(enable && !observer);
		}
	}
	if (m_handicap[s] != NULL)
		m_handicap[s]->winEnable(enable && !observer);
	GameWindow *hero = m_hero[s];
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
				HandleHeroSelection(s);
			}
		}
		UpdateHeroDisplay(s);
	}
	if (m_playerTemplate[s] != NULL)
		m_playerTemplate[s]->winEnable(enable);
	GameWindow **teamCombo = &m_team[s];
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
	if (game->v13() == s)
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