// cl: /O1 /DNDEBUG /MD
//
// Singleton forwarders: each loads a global object pointer into ecx and
// tail-jumps a rowed member of it (mov ecx, [global]; jmp). The globals are
// declared with their ledger types (TheScriptEngine is a converged address);
// the targets are only declared here so the calls are not inlined. Which
// callers or classes these wrappers belong to is not established: they are
// address-named free functions, and no referencing site was found for them
// in this pass.
class AsciiString;

class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;
class LivingWorldCampaignManager { public: bool rva003B8CAC(); };

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002B317CBumpCounter { public: int bump(); };

class ScriptEngine { public: void AppendDebugMessage(const AsciiString &strToAdd, bool forcePause); };
extern ScriptEngine *TheScriptEngine;

class Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
class Rva006FB860 { public: void rva006FA340(); };

// ?rva002B298C@@YA_NXZ @0x002B298C: TheCampaignManager -> 0x003B8CAC
bool rva002B298C()
{
	return ((LivingWorldCampaignManager *)TheCampaignManager)->rva003B8CAC();
}

// ?rva002E061D@@YAHXZ @0x002E061D: TheLivingWorldLogic -> bump 0x002B317C
int rva002E061D()
{
	return ((Rva002B317CBumpCounter *)TheLivingWorldLogic)->bump();
}

// ?rva003BA938@@YGXABVAsciiString@@_N@Z @0x003BA938: TheScriptEngine ->
// AppendDebugMessage 0x00205263 with both stack arguments (callee pops them).
void __stdcall rva003BA938(const AsciiString &strToAdd, bool forcePause)
{
	TheScriptEngine->AppendDebugMessage(strToAdd, forcePause);
}

// ?rva006CC5F0@@YAXXZ @0x006CC5F0: the Apt object at 0x00E176D0 -> 0x006FA340
void rva006CC5F0()
{
	((Rva006FB860 *)g_bfmeAptPtrAtE176D0)->rva006FA340();
}

// Null-guarded variants: if the global object exists, tail-jump its member
// (mov ecx, [global]; test ecx, ecx; je ret; jmp). Same naming as above.
class Rva00108660ResourceManager;
extern Rva00108660ResourceManager *Rva00DEC2D8Manager;
class Rva00109236 { public: void rva00109236(); };
class Rva00109DCF { public: void rva00108E28(); };

class Q1Receiver0134FAAC { public: void Rva00624790(); };
extern Q1Receiver0134FAAC *TheQ1Receiver;

// ?rva0009A328@@YAXXZ @0x0009A328: Rva00DEC2D8Manager -> 0x00109236
void rva0009A328()
{
	if (Rva00DEC2D8Manager)
		((Rva00109236 *)Rva00DEC2D8Manager)->rva00109236();
}

// ?rva0009A487@@YAXXZ @0x0009A487: Rva00DEC2D8Manager -> 0x00108E28
void rva0009A487()
{
	if (Rva00DEC2D8Manager)
		((Rva00109DCF *)Rva00DEC2D8Manager)->rva00108E28();
}

// ?rva0061F190@@YAXXZ @0x0061F190: TheQ1Receiver -> 0x00624790
void rva0061F190()
{
	if (TheQ1Receiver)
		TheQ1Receiver->Rva00624790();
}
