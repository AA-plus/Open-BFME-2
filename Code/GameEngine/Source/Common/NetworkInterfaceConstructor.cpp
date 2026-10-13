// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// The native network allocation path constructs a 0x40-byte object at
// 0x0065E4A8, then calls this body before invoking the virtual init slot. The
// base constructor is a separately pinned retail body at 0x005B4E63.

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64 *frequency);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *counter);

extern "C" const void *const __identifier("??_7Rva0025E4CD@@6B@")[];

// 0x001B4E63 is the rowed SubsystemInterface ctor.
class SubsystemInterface { public: SubsystemInterface(); };

class BFME2NativeNetwork
{
public:
	void *construct(void);

private:
	void *m_vtable;
	char m_baseFields[8];
	void *m_connectionManager;
	int m_state;
	char m_unknown14[4];
	__int64 m_performanceFrequency;
	__int64 m_lastPerformanceCounter;
	__int64 m_accumulator;
	bool m_stallTimerRunning;
	char m_unknown31[3];
	unsigned int m_stallCount;
	bool m_flag38;
	int m_lastValue;
};

void *BFME2NativeNetwork::construct(void)
{
	reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface();
	m_lastValue = -1;
	m_connectionManager = 0;
	m_state = 0;
	m_accumulator = 0;
	m_stallTimerRunning = false;
	m_stallCount = 0;
	m_flag38 = false;
	m_vtable = (void *)__identifier("??_7Rva0025E4CD@@6B@");
	QueryPerformanceFrequency(&m_performanceFrequency);
	QueryPerformanceCounter(&m_lastPerformanceCounter);
	return this;
}
