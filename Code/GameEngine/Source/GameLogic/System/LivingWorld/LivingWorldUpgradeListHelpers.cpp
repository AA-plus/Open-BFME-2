// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Two stdcall living-world upgrade-list walkers (WB 0x00B57F60 is the
// second, unnamed): each non-null entry of a vector of upgrade templates is
// handed to the player's upgrade hooks (Rva002E15BC; WB names 0x002E1588
// LivingWorldPlayer::AddUpgrade and 0x002E15BC RemoveUpgrade).
//  - rva0020ED51, retail 0x0020ED51 (61 B): adds every entry of the given
//    list, forwarding the flag; reached through the forwarders 0x0020F2F1
//    and 0x0020F309. The pinned spelling passes the player and the flag as
//    plain words.
//  - rva0020ED8E, retail 0x0020ED8E (71 B): removes every entry of the
//    object's +0xD4 list; called from the battle hand-over 0x0020F832.
#include <vector>

class Rva002E15BC
{
public:
	void rva002E1588(void *upgrade, bool flag);	// 0x002E1588
	void rva002E15BC(void *upgrade);			// 0x002E15BC
};

struct Rva0020ED8EUpgradeOwner
{
	char m_pad00[0xD4];
	_STL::vector<void *> m_upgrades;	// +0xD4
};

void __stdcall rva0020ED51(void *list, int player, int flag)
{
	const _STL::vector<void *> &upgrades = *(const _STL::vector<void *> *)list;
	for (unsigned int i = 0; i < upgrades.size(); ++i)
	{
		if (upgrades[i])
			((Rva002E15BC *)player)->rva002E1588(upgrades[i], *(bool *)&flag);
	}
}

void __stdcall rva0020ED8E(Rva0020ED8EUpgradeOwner *owner, Rva002E15BC *player)
{
	const _STL::vector<void *> &upgrades = owner->m_upgrades;
	for (unsigned int i = 0; i < upgrades.size(); ++i)
	{
		if (upgrades[i])
			player->rva002E15BC(upgrades[i]);
	}
}
