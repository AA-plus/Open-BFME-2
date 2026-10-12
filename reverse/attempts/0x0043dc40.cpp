// ?rva0043DC40@AptMpGameSetup@@QAEXH@Z
// partial score=0.9 date=2026-10-13
// ?rva0043DC40@AptMpGameSetup@@QAEXH@Z
// partial score=0.9 date=2026-10-13
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// FRAGMENT for Code/GameEngine/Source/GameClient/GUI/MpGameSetupSlots.cpp (needs its AptMpGameSetup view).
// Retail 0x0043DC40, 53 bytes: games-list sort-column pick. Wall: reg numbering (retail column:EAX/old:EDX/next:ESI via single ESI save; best variant c/old/next gives column:ESI/old:EDX/next:EDI, 49B). Tried: next-first, dual inline column+1 (inc, 46B), c-copy-first.

// Retail 0x0043DC40, 53 bytes: picks the games list sort column (the same
// column again toggling to the next value). The next value is computed
// first so the argument load precedes the column load, as retail does.
void AptMpGameSetup::rva0043DC40(int column)
{
	int c = column;
	int old = m_sortColumn;
	int next = c + 1;
	if (old == c)
		m_sortColumn = next;
	else
	{
		m_sortColumn = c;
		if (old != next)
			m_previousSortColumn = old;
	}
	m_2bc = true;
}
