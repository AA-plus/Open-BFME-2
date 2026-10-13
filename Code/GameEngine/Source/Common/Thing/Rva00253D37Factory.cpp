// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?ModuleFactoryDataAt00253D37@@YAPAVModuleData@@PAVINI@@@Z, retail
// 0x00253D37, 81 bytes.
//
// Evidence (retail body only; names are address-derived):
//  253d37: mov eax, FuncInfo / call __EH_prolog
//          new Rva00253E32 (operator new 0x18, then the rowed ctor at
//          0x00253E32), and when the INI argument is non-null run
//          INI::initFromINIMultiProc 0x0002DEB5 on it with the rowed
//          buildFieldParse at 0x004CEE09; return the new object.
// The factory is one of the module-factory registrations (the parse proc's
// byte-identical row is named UpgradeModuleData::buildFieldParse); the
// NotifyTargets/HordeNotify ownership question is not settled by these
// bytes, so the factory and its class keep address-derived names.

class MultiIniFieldParse;
class ModuleData;

class INI
{
public:
	void initFromINIMultiProc(void *instance, void (*proc)(MultiIniFieldParse &));
};

class UpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class Rva004CE6BA
{
public:
	Rva004CE6BA();

	int m_00;
	int m_04;
	float m_08;
	float m_0C;
};

class Rva00253E32Base
{
public:
	Rva00253E32Base() {}
	virtual ~Rva00253E32Base();

private:
	void *m_base4;
};

class Rva00253E32 : public Rva00253E32Base
{
public:
	Rva00253E32();
	virtual ~Rva00253E32();

private:
	Rva004CE6BA m_8;
};

ModuleData *ModuleFactoryDataAt00253D37(INI *ini)
{
	Rva00253E32 *obj = new Rva00253E32;
	if (ini)
		ini->initFromINIMultiProc(obj, &UpgradeModuleData::buildFieldParse);
	return (ModuleData *)obj;
}
