// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004B8DCA@SupplyCenterCreate@@SA?AW4NameKeyType@@XZ @0x004B8DCA
// (69B): cached pool-name key for SupplyCenterCreate. The class
// identity comes from the pool-name string the body pushes
// ("SupplyCenterCreate"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Object;
class ModuleData;

class ResourceGatheringManager
{
public:
	void rva004F5C44(Object *obj);
};

class Player
{
public:
	char m_pad000[0x2E4];
	ResourceGatheringManager *m_resourceGatheringManager;
};

class PlayerList
{
public:
	Player *getNthPlayer(int i);
	char m_pad00[0x14];
	int m_playerCount;
};

extern PlayerList *ThePlayerList;

class Module
{
public:
	virtual ~Module();
protected:
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class CreateModuleInterface
{
public:
	virtual void onCreate() = 0;
	virtual void onBuildComplete() = 0;
	virtual void createSlot2() = 0;
	virtual bool shouldDoOnBuildComplete() const = 0;
};

class CreateModule : public Module, public BehaviorModuleInterface, public CreateModuleInterface
{
protected:
	bool m_needToRunOnBuildComplete;
};

class SupplyCenterCreate : public CreateModule
{
public:
	static NameKeyType rva004B8DCA();
	virtual void onBuildComplete();
};

// ?rva004B8DCA@SupplyCenterCreate@@SA?AW4NameKeyType@@XZ
NameKeyType SupplyCenterCreate::rva004B8DCA()
{
	static NameKeyType TheSupplyCenterCreatePoolKey =
		TheNameKeyGenerator->nameToKey("SupplyCenterCreate");
	return TheSupplyCenterCreatePoolKey;
}

// ?onBuildComplete@SupplyCenterCreate@@UAEXXZ @0x004B8E2B (77B)
void SupplyCenterCreate::onBuildComplete()
{
	if (!shouldDoOnBuildComplete())
		return;

	m_needToRunOnBuildComplete = false;

	if (ThePlayerList == 0)
		return;

	for (int playerIndex = ThePlayerList->m_playerCount - 1; playerIndex >= 0; --playerIndex)
	{
		Player *currentPlayer = ThePlayerList->getNthPlayer(playerIndex);
		if (currentPlayer == 0)
			continue;
		ResourceGatheringManager *manager = currentPlayer->m_resourceGatheringManager;
		if (manager == 0)
			continue;
		manager->rva004F5C44(getObject());
	}
}

