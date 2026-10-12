// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// ?rva0003A210@@YAXXZ, retail 0x0003A210..0x0003A24B (59B): a Ghidra-unlisted
// static-initialiser body of the debug library (reached from the CRT
// initialiser table). BFME 2's take on Zero Hour's Debug::PreStatic hook: it
// initialises the 0x00DE0884 critical section, asks the main module for the
// exported "?PreStaticInit@Debug@@CAPAV1@XZ" (falling back to the local rowed
// copy 0x000385F0), stores the instance it returns in theDebug and registers
// the rowed Debug::StaticExit 0x000399C0 with atexit.
struct DebugCriticalSection;

extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(DebugCriticalSection *section);
extern "C" __declspec(dllimport) void *__stdcall GetModuleHandleA(const char *name);
extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(void *module, const char *name);
extern "C" int __cdecl atexit(void (__cdecl *fn)(void));

void rva0003A210();

class Debug
{
	friend void rva0003A210();
	static Debug *PreStaticInit();							// 0x000385F0
	static void StaticExit();								// 0x000399C0
};

extern DebugCriticalSection g_bfmeCsDWC;
extern Debug *theDebug;

typedef Debug *(*DebugPreStaticInitProc)();

void rva0003A210()
{
	InitializeCriticalSection(&g_bfmeCsDWC);
	void *module = GetModuleHandleA(0);
	DebugPreStaticInitProc init = (DebugPreStaticInitProc)GetProcAddress(module, "?PreStaticInit@Debug@@CAPAV1@XZ");
	if (!init)
		init = &Debug::PreStaticInit;
	theDebug = init();
	atexit(&Debug::StaticExit);
}
