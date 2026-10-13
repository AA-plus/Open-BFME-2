// cl: /MD
// ?postInit@Rva00598F24@@QAEXXZ @0x00598F24 27B via global store lookup plus add
// Evidence: thiscall void; pushes Player at this+0x2C; rowed rva002A8F24 0x002A8F24 via global g_00DFEEF8; rowed addInfoReceiver 0x004DFEC8 with this as ModuleData; caller 0x004EBFBA
class Player;
class ModuleData;
class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
};
extern Rva002A8F24 *g_00DFEEF8;
class AIStatCollector
{
public:
	void addInfoReceiver(const ModuleData *data);
};
class Rva00598F24
{
public:
	void postInit();
private:
	char m_pad[0x2C];
	Player *m_player;
};
void Rva00598F24::postInit()
{
	void *store = g_00DFEEF8->rva002A8F24(m_player);
	((AIStatCollector *)store)->addInfoReceiver((const ModuleData *)(void *)this);
}
