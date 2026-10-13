// cl: /MD
// ??0Rva0041AC6A@@QAE@XZ, retail 0x0041AC6A, 32 bytes.
// Evidence: leaf lane, caller at 0x0022FAC5, callee baseConstruct 0x001B4E63,
// vtable g_00C3ADD8 at +0, second vtable g_00C3ADC8 at +0xC overwriting g_00BBB554.
class BFME2NativeNetwork
{
public:
};

extern const void *const g_00BBB554[];
extern "C" const void *const __identifier("??_7Rva0041B790@@6BSubsystemInterface@@@")[];
extern "C" const void *const __identifier("??_7Rva0041B790@@6BSnapshot@@@")[];

// 0x001B4E63 is the rowed SubsystemInterface ctor.
class SubsystemInterface { public: SubsystemInterface(); };

class Rva0041AC6A
{
public:
	Rva0041AC6A();
	char m_pad[12];
	const void *volatile m_secondVptr;
};

Rva0041AC6A::Rva0041AC6A()
{
	reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface();
	m_secondVptr = (const void *)g_00BBB554;
	*(const void **)this = (const void *)__identifier("??_7Rva0041B790@@6BSubsystemInterface@@@");
	m_secondVptr = (const void *)__identifier("??_7Rva0041B790@@6BSnapshot@@@");
}
