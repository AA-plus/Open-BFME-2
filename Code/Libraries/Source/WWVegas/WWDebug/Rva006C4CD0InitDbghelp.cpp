// cl: /DNDEBUG /MD /Oi-
// ?initDbghelp@Rva006C4CD0Helper@@QAEXXZ
// retail 0x006C4CD0, 124 bytes. Dedicated TU.
//
// Opaque helper-class row: loads DbgHelp.dll once and resolves seven dbghelp
// entry points (SymInitialize, SymCleanup, StackWalk, SymFunctionTableAccess,
// SymGetModuleBase, SymGetSymFromAddr, SymGetLineFromAddr) into slots
// +8..+0x20, with the module handle at +0. Same-cluster callers at
// 0x6C4D8F/0x6C4FBC/0x6C5108; the cleanup sibling (~0x6C4D80) reads the flag
// at +4 and SymCleanup at +0xC before freeing the library. The true class
// name is unknown, so the RvaHelper name claims nothing beyond the address;
// the method name describes the proven behavior. Imports resolve by name
// (LoadLibraryA, GetProcAddress).

#ifndef NULL
#define NULL 0
#endif

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

typedef void *HMODULE;

extern "C" __declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *name);
extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(HMODULE module, const char *name);
extern "C" __declspec(dllimport) void *__stdcall GetCurrentProcess(void);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(HMODULE module);
extern "C" __declspec(dllimport) char *__cdecl strncpy(char *dst, const char *src, unsigned int n);

class Rva006C4CD0Helper
{
public:
	void initDbghelp(void);
	void uninitDbghelp(void);
	bool getSymbolName(unsigned long addr, char *buf, unsigned long maxlen);

	HMODULE m_hLib;			// +0x00
	unsigned char m_flag;		// +0x04 (byte-wide per retail mov al;
					// the 0x6C4D80 sibling stores it by byte)
	void *m_symInitialize;		// +0x08
	void *m_symCleanup;		// +0x0C
	void *m_stackWalk;		// +0x10
	void *m_symFunctionTableAccess;	// +0x14
	void *m_symGetModuleBase;	// +0x18
	void *m_symGetSymFromAddr;	// +0x1C
	void *m_symGetLineFromAddr;	// +0x20
};

// IMAGEHLP_SYMBOL prefix: only the header fields plus enough name bytes to
// make the 0x218 total the retail frame proves (4 displacement + 0x218).
struct DbgSymbolInfo
{
	unsigned long m_sizeOfStruct;	// +0x00
	unsigned long m_address;	// +0x04
	unsigned long m_size;		// +0x08
	unsigned long m_flags;		// +0x0C
	unsigned long m_maxNameLength;	// +0x10
	char m_name[0x204];		// +0x14
};

// ?initDbghelp@Rva006C4CD0Helper@@QAEXXZ
void Rva006C4CD0Helper::initDbghelp(void)
{
	if (m_hLib != NULL) {
		return;
	}
	m_hLib = LoadLibraryA("DbgHelp.dll");
	if (m_hLib == NULL) {
		return;
	}
	m_symInitialize = GetProcAddress(m_hLib, "SymInitialize");
	m_symCleanup = GetProcAddress(m_hLib, "SymCleanup");
	m_stackWalk = GetProcAddress(m_hLib, "StackWalk");
	m_symFunctionTableAccess = GetProcAddress(m_hLib, "SymFunctionTableAccess");
	m_symGetModuleBase = GetProcAddress(m_hLib, "SymGetModuleBase");
	m_symGetSymFromAddr = GetProcAddress(m_hLib, "SymGetSymFromAddr");
	m_symGetLineFromAddr = GetProcAddress(m_hLib, "SymGetLineFromAddr");
}

// ?uninitDbghelp@Rva006C4CD0Helper@@QAEXXZ
// retail 0x006C4D50, 43 bytes. Same TU: runs SymCleanup through the slot at
// +0xC when the flag at +4 says the table initialized, then frees the library.
void Rva006C4CD0Helper::uninitDbghelp(void)
{
	if (m_hLib == NULL) {
		return;
	}
	if (m_flag && m_symCleanup != NULL) {
		((int (__stdcall *)(void *))m_symCleanup)(GetCurrentProcess());
	}
	FreeLibrary(m_hLib);
}

// ?rva006C4E30@@YAXXZ
// retail 0x006C4E30, 27 bytes. Same TU: one-shot guard around initDbghelp;
// the first call through tail-jumps into initDbghelp on the TU-global
// helper object. Guard and object are adjacent in retail's image, so they
// are declared adjacently here.
static int g_rva006C4E30Guard = 0;
static Rva006C4CD0Helper g_rva006C4CD0Object;
void rva006C4E30(void)
{
	if (++g_rva006C4E30Guard == 1) {
		g_rva006C4CD0Object.initDbghelp();
	}
}

// ?rva006C4E50@@YAXXZ
// retail 0x006C4E50, 61 bytes. Same TU: guarded teardown twin of rva006C4E30;
// when the last user leaves it runs the SymCleanup slot, then frees the
// library. Mirrors uninitDbghelp's call shapes on the TU-global object.
void rva006C4E50(void)
{
	if (--g_rva006C4E30Guard != 0) {
		return;
	}
	if (g_rva006C4CD0Object.m_hLib == NULL) {
		return;
	}
	if (g_rva006C4CD0Object.m_flag && g_rva006C4CD0Object.m_symCleanup != NULL) {
		((int (__stdcall *)(void *))g_rva006C4CD0Object.m_symCleanup)(GetCurrentProcess());
	}
	FreeLibrary(g_rva006C4CD0Object.m_hLib);
}
// ?getSymbolName@Rva006C4CD0Helper@@QAE_NKPADK@Z
// retail 0x006C4D80, 167 bytes. Same TU: resolve an address to its symbol
// name through the slot at +0x1C, copying at most maxlen bytes into buf.
// SymInitialize runs once through the slot at +8 (flag at +4); the strncpy
// import resolves by name.
bool Rva006C4CD0Helper::getSymbolName(unsigned long addr, char *buf, unsigned long maxlen)
{
	if (m_hLib == NULL) {
		initDbghelp();
	}
	void *proc = GetCurrentProcess();
	if (!m_flag && m_symInitialize != NULL) {
		if (((int (__stdcall *)(void *, const char *, int))m_symInitialize)(proc, NULL, TRUE) != 0) {
			m_flag = 1;
		}
	}
	DbgSymbolInfo sym;
	sym.m_sizeOfStruct = 0x218;
	sym.m_maxNameLength = 0x200;
	unsigned long disp = 0;
	if (m_symGetSymFromAddr == NULL) {
		return false;
	}
	if (((int (__stdcall *)(void *, unsigned long, unsigned long *, DbgSymbolInfo *))m_symGetSymFromAddr)(proc, addr, &disp, &sym) != 0) {
		strncpy(buf, sym.m_name, maxlen);
		return true;
	}
	return false;
}

// Retail 0x006C50D0..0x006C52F2, 546B whole CDECL formatter.
// Four arguments (address array, unsigned count, output pointer, capacity)
// and pointer-distance return come from the retail stack accesses. The name
// stays address-derived. ZH Common/System/StackDump.cpp GetFunctionDetails
// and debug/debug_stack.cpp supply the DbgHelp symbol/line semantic guide;
// the target-specific multi-address loop, exact formats and buffer rules
// are independently visible in retail. BFME 1 reference revision 874e38488.
// In particular the hex fallback advances output without decrementing the
// remaining capacity, and symbol/line copies exclude NUL: retain that target
// behavior. Import verification proves bounded copies use strncpy. /Oi-
// keeps imported strncpy while only strlen/strcpy are explicitly intrinsic.
extern "C" __declspec(dllimport) int __cdecl sprintf(char *, const char *, ...);

extern "C" unsigned int __cdecl strlen(const char *);
extern "C" char *__cdecl strcpy(char *,const char *);
#pragma intrinsic(strlen, strcpy)
struct DbgLineInfo {
 unsigned long size; void *key; unsigned long line; const char *filename; unsigned long address;
};
unsigned int Rva006C50D0Describe(const unsigned long *addresses, unsigned int count, char *buffer, unsigned int capacity)
{
 char *current=buffer;
 *buffer=0;
 --capacity;
 void *process=GetCurrentProcess();
 if(!g_rva006C4CD0Object.m_hLib) g_rva006C4CD0Object.initDbghelp();
 if(!g_rva006C4CD0Object.m_flag && g_rva006C4CD0Object.m_symInitialize) {
  if(((int(__stdcall*)(void*,const char*,int))g_rva006C4CD0Object.m_symInitialize)(process,0,1))
   g_rva006C4CD0Object.m_flag=1;
 }
 if(g_rva006C4CD0Object.m_flag) {
 for(unsigned int i=0;i<count;++i) {
  unsigned long address=addresses[i];
  if(i>0 && capacity>0) { *current++=' '; --capacity; }
  DbgSymbolInfo symbol;
  symbol.m_sizeOfStruct=sizeof(symbol);
  symbol.m_maxNameLength=512;
  unsigned long displacement=0;
  if(g_rva006C4CD0Object.m_symGetSymFromAddr &&
    ((int(__stdcall*)(void*,unsigned long,unsigned long*,DbgSymbolInfo*))g_rva006C4CD0Object.m_symGetSymFromAddr)(process,address,&displacement,&symbol)) {
   char text[512];
   sprintf(text,"%hs() + %d",symbol.m_name,displacement);
   unsigned int length=strlen(text);
   if(capacity>length) { strncpy(current,text,length); current+=length;capacity-=length; }
   if(g_rva006C4CD0Object.m_symGetLineFromAddr) {
    DbgLineInfo line;
    line.size=sizeof(line);
    if(((int(__stdcall*)(void*,unsigned long,unsigned long*,DbgLineInfo*))g_rva006C4CD0Object.m_symGetLineFromAddr)(process,address,&displacement,&line)) {
     sprintf(text," \"%hs\", line %d",line.filename,line.line);
     length=strlen(text);
     if(capacity>length) { strncpy(current,text,length);current+=length;capacity-=length; }
    }
   }
  } else if(capacity>=10) {
   char textHex[32];
   sprintf(textHex,"0x%08x",address);
   unsigned int length=strlen(textHex);
   strcpy(current,textHex);
   current+=length;
  }
 }
 }
 return current-buffer;
}

// Retail 0x006C4FA0, 297 bytes: CDECL stack capture into (out, maxFrames).
// Ensures the dbghelp table, snapshots the current EBP/ESP/EIP into a
// minimal CONTEXT, walks with the table's StackWalk slot into a 0xA4
// STACKFRAME, skipping the current frame and storing at most maxFrames-1
// addresses plus a NULL terminator; returns the stored count. The EBP/ESP
// homes and the call-next EIP idiom have no intrinsic spelling, so they
// use the same small inline-asm blocks the fleet's landed x87 code uses.
// Native 6C4E90..6C4F94 vtable class-name recovery: VirtualQuery protect 2 on the
// vtable pointer then protect 0x30 on its first slot, the rowed getSymbolName on
// this TU's dbghelp object, a ??_7 strncmp, then strtok @ and strncpy. The second
// VirtualQuery's arguments sit in swapped registers unless the first-slot read is
// spelled as an equal-arm conditional (the late-folded ?: tie breaker).
struct DbgMemoryInfo
{
	void *baseAddress, *allocationBase;
	unsigned long allocationProtect, regionSize, state, protect, type;
};
extern "C" __declspec(dllimport) unsigned long __stdcall VirtualQuery(const void *, DbgMemoryInfo *, unsigned long);
extern "C" __declspec(dllimport) int __cdecl strncmp(const char *, const char *, unsigned int);
extern "C" __declspec(dllimport) char *__cdecl strtok(char *, const char *);
bool Rva006C4E90VtableName(void ***object, unsigned int size, char *out, unsigned int outSize)
{
	if (size >= 4)
	{
		void **vtable = (void **)**object;
		if (((unsigned long)vtable & 3) == 0)
		{
			DbgMemoryInfo info;
			if (VirtualQuery(vtable, &info, sizeof(info)) >= sizeof(info) && (info.protect & 2)
				&& VirtualQuery(object ? *vtable : *vtable, &info, sizeof(info)) >= sizeof(info) && (info.protect & 0x30))
			{
				char name[0x200];
				if (g_rva006C4CD0Object.getSymbolName((unsigned long)vtable, name, sizeof(name))
					&& strlen(name) > 4 && strncmp(name, "??_7", 4) == 0)
				{
					char *token = strtok(name + 4, "@");
					if (token)
					{
						*token = 0;
						strncpy(out, name + 4, outSize);
						return true;
					}
				}
			}
		}
	}
	return false;
}

extern "C" __declspec(dllimport) void *__stdcall GetCurrentThread(void);

struct BfmeCaptureContext
{
	unsigned long ContextFlags;	// +0x00
	unsigned char m_pad04[0xB4 - 4];
	unsigned long Ebp;		// +0xB4
	unsigned long Eip;		// +0xB8
	unsigned char m_padBC[0xC4 - 0xBC];
	unsigned long Esp;		// +0xC4
	unsigned char m_padC8[0x2CC - 0xC8];
};

struct BfmeCaptureAddress
{
	unsigned long Offset;		// +0x00
	unsigned short Segment;		// +0x04
	unsigned short m_pad6;		// +0x06
	unsigned long Mode;		// +0x08
};

struct BfmeCaptureFrame
{
	BfmeCaptureAddress m_pc;	// +0x00
	BfmeCaptureAddress m_ret;	// +0x0C
	BfmeCaptureAddress m_frame;	// +0x18
	BfmeCaptureAddress m_stack;	// +0x24
	unsigned char m_rest[0xA4 - 0x30];
};

typedef int (__stdcall *BfmeStackWalkFn)(unsigned long machine, void *process,
	void *thread, BfmeCaptureFrame *frame, BfmeCaptureContext *context,
	int readMemory, void *tableAccess, void *moduleBase, int translate);

int rva006C4FA0Capture(void **out, unsigned int maxFrames)
{
	unsigned int count = 0;
	if (g_rva006C4CD0Object.m_hLib == NULL)
		g_rva006C4CD0Object.initDbghelp();
	if (g_rva006C4CD0Object.m_stackWalk == NULL)
		goto done;
	void *process = GetCurrentProcess();
	void *thread = GetCurrentThread();
	BfmeCaptureContext context;
	for (unsigned i = 0; i < sizeof(context) / sizeof(unsigned long); i++)
		((unsigned long *)&context)[i] = 0;
	context.ContextFlags = 0x10001;
	__asm mov DWORD PTR [ebp-0x2c4], ebp
	__asm mov DWORD PTR [ebp-0x2b4], esp
	__asm call eip_next2
	__asm eip_next2: pop DWORD PTR [ebp-0x2c0]
	unsigned last = maxFrames;
	BfmeCaptureFrame frame;
	for (unsigned i = 0; i < sizeof(frame) / sizeof(unsigned long); i++)
		((unsigned long *)&frame)[i] = 0;
	frame.m_pc.Offset = context.Eip;
	int skip = 0;
	--last;
	frame.m_pc.Mode = 3;
	frame.m_stack.Offset = context.Esp;
	frame.m_stack.Mode = 3;
	frame.m_frame.Offset = context.Ebp;
	frame.m_frame.Mode = 3;
	if (last == 0)
		goto done;
	do {
		if (!((BfmeStackWalkFn)g_rva006C4CD0Object.m_stackWalk)(0x14C, process, thread, &frame, &context, 0, g_rva006C4CD0Object.m_symFunctionTableAccess, g_rva006C4CD0Object.m_symGetModuleBase, 0))
			goto done;
		if (frame.m_frame.Offset == 0)
			goto done;
		if (skip > 0)
			out[count++] = (void *)frame.m_pc.Offset;
		skip++;
	} while (count < last);
done:
	out[count] = 0;
	return count;
}
