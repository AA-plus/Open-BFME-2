// cl: /O1 /DNDEBUG /MD
//
// Forwarders through the global Debug object: mov ecx, [theDebug];
// mov eax, [ecx]; jmp [eax+4*slot]. Slots are counted in the Debug vtable
// 0x007BE810 (data ledger); every target slot body there ends in a plain ret,
// so none takes stack arguments. Which public Debug entry points these are is
// not established: address-named free functions, no referencing site found in
// this pass. The view below models only the vtable slots used.
class Debug
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual bool slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void * slot40();
	virtual void * slot41();
	virtual void * slot42();
};
extern Debug *theDebug;

// ?rva00038370@@YAXXZ @0x00038370: theDebug slot 22
void rva00038370()
{
	theDebug->slot22();
}

// ?rva00038380@@YA_NXZ @0x00038380: theDebug slot 24
bool rva00038380()
{
	return theDebug->slot24();
}

// ?rva0003BC60@@YAPAXXZ @0x0003BC60: theDebug slot 40
void * rva0003BC60()
{
	return theDebug->slot40();
}

// ?rva0003BC70@@YAPAXXZ @0x0003BC70: theDebug slot 41
void * rva0003BC70()
{
	return theDebug->slot41();
}

// ?rva0003D370@@YAPAXXZ @0x0003D370: theDebug slot 42
void * rva0003D370()
{
	return theDebug->slot42();
}

// ?rva00225A1F@@YAXXZ @0x00225A1F: theDebug slot 37
void rva00225A1F()
{
	theDebug->slot37();
}
