// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// LivingWorldRegionManager::rva0020FB8B, retail 0x0020FB8B (132 B; WB
// 0x00B56900, unnamed; called from LivingWorldLogic::OnBattleComplete
// 0x002BAF7E): finds the pending battle (+0x14 list) with the completed
// battle's id (+0x34), notifies TheLivingWorldManager with its +0x30
// field (0x00212655), moves the battle to the completed list (+0x20) and
// drops it from the pending one. The lists keep the element spellings their
// rowed vector members carry (erase 0x001FF51F, reserve 0x002B712E,
// push_back 0x004DFCB0).
#include <vector>

class ModuleData;

struct LivingWorldBattleIDView
{
	char m_pad00[0x30];
	int m_30;		// +0x30
	int m_id;		// +0x34
};
class LivingWorldBattle;

class Rva00DFE1C8Host
{
public:
	void rva00212655(int value);	// 0x00212655
};
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;	// 0x00DFE1C8

class LivingWorldRegionManager
{
public:
	void rva0020FB8B(LivingWorldBattle *battle);
private:
	char m_pad00[0x14];
	_STL::vector<void *> m_pendingBattles;			// +0x14
	_STL::vector<const ModuleData *> m_doneBattles;	// +0x20
};

void LivingWorldRegionManager::rva0020FB8B(LivingWorldBattle *battle)
{
	for (unsigned int i = 0; i < m_pendingBattles.size(); ++i)
	{
		if (((LivingWorldBattleIDView *)battle)->m_id == ((LivingWorldBattleIDView *)m_pendingBattles[i])->m_id)
		{
			((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00212655(((LivingWorldBattleIDView *)battle)->m_30);
			m_doneBattles.reserve(m_pendingBattles.size());
			m_doneBattles.push_back((const ModuleData *)battle);
			m_pendingBattles.erase(m_pendingBattles.begin() + i);
			return;
		}
	}
}
