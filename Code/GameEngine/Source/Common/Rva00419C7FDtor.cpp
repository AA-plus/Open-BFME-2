// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX
//
// ??1Rva00419C7F@@UAE@XZ, retail 0x00419C7F, 48 bytes. Dtor releasing
// AsciiString at +8 then restoring base vtable 0x007C0990. Evidence: vtable
// store plus rowed releaseBuffer 0x00036410; caller deleting dtor
// 0x00419C63; same EH shape as PillageModuleDataDtor (novtable derived,
// inline base restoring g_00BC0990, empty body).
#include "ascii_string.h"

extern "C" const void *const __identifier("??_7DebugIOConBase@@6B@")[];

class DebugIOInterfaceBase
{
public:
	virtual ~DebugIOInterfaceBase();
	virtual int Read(char *buf, int maxchar);
	virtual void Write(int type, const char *src, const char *str);
	virtual void EmergencyFlush();
	virtual void Execute(void *dbg, const char *cmd, bool structured, unsigned argn, const char *const *argv);
	virtual void Delete();
};

// ??1DebugIOInterfaceBase@@UAE@XZ present-unmatched
inline DebugIOInterfaceBase::~DebugIOInterfaceBase()
{
	*(const void * *)this = __identifier("??_7DebugIOConBase@@6B@");
}

class __declspec(novtable) Rva00419C7F : public DebugIOInterfaceBase
{
public:
	virtual ~Rva00419C7F();
private:
	int m_pad04;
	AsciiString m_08;
};

Rva00419C7F::~Rva00419C7F() {}
