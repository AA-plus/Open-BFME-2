// ?rva00433F7F@Rva00433F7F@@QAEXXZ
// partial score=0.95 date=2026-10-13
// ?rva00433F7F@Rva00433F7F@@QAEXXZ
// partial score=0.93 date=2026-09-29
// ?rva00433F7F@Rva00433F7F@@QAEXXZ
// partial score=0.93 date=2026-09-29
// cl: /O1 /MD
//
// ?rva00433F7F@Rva00433F7F@@QAEXXZ, retail 0x00433F7F, 94 bytes.
// __thiscall void method reading this+0x288 and this+0x28c as GameWindow*.
// Calls rowed GadgetListBoxGetSelected then rowed Rva003253BEGet just landed.
// Evidence: chain lane calls 0x003253BE; callers 0x004340BD 0x00434324.

class GameWindow;

void GadgetListBoxGetSelected(GameWindow *listbox, int *selectList);
void *GadgetListBoxGetItemData(GameWindow *window, int a, int b);

class Rva00433F7F
{
public:
	void rva00433F7F();
private:
	char m_pad[0x288];
	GameWindow *m_win288;
	GameWindow *m_win28c;
};

// ?rva00433F7F@Rva00433F7F@@QAEXXZ present-unmatched
void Rva00433F7F::rva00433F7F()
{
	int sel;
	if (m_win288 != 0)
	{
		GadgetListBoxGetSelected(m_win288, &sel);
		GadgetListBoxGetItemData(m_win288, sel, 0);
		if (sel < 0)
		{
			if (m_win28c != 0)
			{
				GadgetListBoxGetSelected(m_win28c, &sel);
				GadgetListBoxGetItemData(m_win28c, sel, 0);
			}
		}
	}
}
