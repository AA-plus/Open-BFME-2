// ?rva0043DC40@AptMpGameSetup@@QAEXH@Z
// partial score=0.93 date=2026-10-13
// Retail 0x0043DC40, 53 bytes: picks the games list sort column (the same
// column again toggling to the next value). The next value is computed
// first so the argument load precedes the column load, as retail does.
void AptMpGameSetup::rva0043DC40(int column)
{
	int next = column + 1;
	int old = m_sortColumn;
	if (old == column)
		m_sortColumn = next;
	else
	{
		m_sortColumn = column;
		if (old != next)
			m_previousSortColumn = old;
	}
	m_2bc = true;
}

// Retail 0x0043DF22, 79 bytes: the number of accepted seated humans (human
// non-observer slots whose accepted flag is set). The accepted flag is
// compared against the observer result register rather than immediate zero.
unsigned int AptMpGameSetup::rva0043DF22()
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return 0;
	unsigned int count = 0;
	for (unsigned int i = 0; i < 8; ++i)
	{
		GameSlot *slot = game->getSlot(i);
		if (!slot)
			continue;
		if (!slot->isHuman())
			continue;
		bool observer = slot->isObserver();
		if (observer)
			continue;
		if (slot->m_accepted == observer)
			continue;
		++count;
	}
	return count;
}
