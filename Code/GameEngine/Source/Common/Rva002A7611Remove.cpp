// cl: /DNDEBUG /MD /EHsc
//
// ?RemoveUpgradableCommandPointsFromBonus@Command@@QAEXHW4ObjectID@@@Z @0x002A7611 51B
// WorldBuilder Command.cpp:421 names it Command::RemoveUpgradableCommandPointsFromBonus;
// Command is the holder at Player +0x60.
// Evidence: thiscall ret 8; walks the 12-byte BfmeE12 vector at +0x20
// (begin +0x20, finish +0x24), and on the first element whose second word
// equals the second argument and whose first word equals the first argument
// hands it to the rowed single-element erase ?erase@Rva002A75DA 0x002A75DA
// (its sole caller is this body) and stops. Sole caller 0x004B86FF. No donor
// body found in reference/open-bfme-1.

struct BfmeE12
{
	int a;
	int b;
	int c;
};

class Rva002A75DA
{
public:
	BfmeE12 *erase(BfmeE12 *position);
	BfmeE12 *m_start;
	BfmeE12 *m_finish;
};

enum ObjectID
{
	INVALID_ID = 0
};

class Command
{
public:
	void RemoveUpgradableCommandPointsFromBonus(int value, ObjectID id);

private:
	unsigned char m_pad[0x20];
	Rva002A75DA m_list; // +0x20
};

void Command::RemoveUpgradableCommandPointsFromBonus(int value, ObjectID id)
{
	for (BfmeE12 *it = m_list.m_start; it != m_list.m_finish; ++it)
	{
		if (it->b == id && it->a == value)
		{
			m_list.erase(it);
			return;
		}
	}
}
