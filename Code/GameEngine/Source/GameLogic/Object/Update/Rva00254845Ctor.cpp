// cl: /O1 /GX- /MD /DNDEBUG
//
// ??0Rva00254845@@QAE@XZ, retail 0x00254845, 18 bytes.
// Frameless ctor over the rowed OpenContain base (0x253487) at offset 0: calls
// the base ctor, then stores folded vtable 0x00BF2558 at +0. No own members.
extern "C" const void *const vtbl_00BF2558[];  // ??_7WeaponSetUpgradeModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BF2558=??_7WeaponSetUpgradeModuleData@@6B@")

class ModuleData;
class MultiIniFieldParse;
class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};
class BuildableHeroListUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};
class AllowBannerSpawnUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};

class Rva00253487Base
{
public:
	Rva00253487Base();

protected:
	void *m_vtable; // +0

private:
	unsigned char m_pad[0x118 - 4];
};

class Rva00254845 : public Rva00253487Base
{
public:
	Rva00254845();
};

Rva00254845::Rva00254845()
{
	m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00BF2558));
}

class Rva0025480BData : public Rva00253487Base
{
public:
	__forceinline Rva0025480BData()
	{
		m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00BF2558));
	}
};

// ?ModuleFactoryDataAt0025480B@@YAPAVModuleData@@PAVINI@@@Z @0x0025480B (58B)
ModuleData *ModuleFactoryDataAt0025480B(INI *ini)
{
	Rva0025480BData *data = new Rva0025480BData;
	if (ini)
		ini->initFromINIMultiProc(data, BuildableHeroListUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

// ?ModuleFactoryDataAt00254857@@YAPAVModuleData@@PAVINI@@@Z @0x00254857 (58B)
ModuleData *ModuleFactoryDataAt00254857(INI *ini)
{
	Rva0025480BData *data = new Rva0025480BData;
	if (ini)
		ini->initFromINIMultiProc(data, AllowBannerSpawnUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
