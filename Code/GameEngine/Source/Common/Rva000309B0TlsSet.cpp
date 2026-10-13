// cl: /GX-
// ?rva000309B0@Rva000309B0@@QAEXXZ @ 0x000309B0 21B
// TLS heap-id setter: if the TLS index at 0x00DB35A4 is not -1, stores this
// object's +0x00 pointer into that TLS slot via TlsSetValue. Evidence: IAT
// TlsSetValue at 0x00BBA198, TLS index 0x00DB35A4 holding the calling
// thread's heap id, callers at 0x0062265B 0x0062214F load ecx then call.
// Honest address-derived name: owner unproven. No STL.
// MemoryPool::g_heapTlsIndex: the TLS slot index at VA 0xdb35a4 (retail .data initial value 0xffffffffu),
// set by MemoryPool init via TlsAlloc; the name is retail's own namespace MemoryPool spelling.
namespace MemoryPool { unsigned long g_heapTlsIndex = 0xffffffffu; }
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long index, void *value);
extern "C" __declspec(dllimport) void *__stdcall TlsGetValue(unsigned long index);

class Rva000309B0
{
public:
	void rva000309B0();
	Rva000309B0 *rva00030980(void *newValue);
private:
	void *m_value;
};

void Rva000309B0::rva000309B0()
{
	unsigned long index = MemoryPool::g_heapTlsIndex;
	if (index != (unsigned long)-1)
		TlsSetValue(index, m_value);
}

// ?rva00030980@Rva000309B0@@QAEPAV1@PAX@Z @ 0x00030980 46B
// TLS heap-id swap: if the TLS index at 0x00DB35A4 is not -1 saves the old
// TLS value into +0x00 and sets the slot to the arg returning this. Evidence:
// IAT TlsGetValue at 0x00BBA194 TlsSetValue at 0x00BBA198 same index as
// rva000309B0 at 0x000309B0 callers at 0x0022EFCC 0x00622003 0x006224B1.
// Honest address-derived method of Rva000309B0.
Rva000309B0 *Rva000309B0::rva00030980(void *newValue)
{
	if (MemoryPool::g_heapTlsIndex != (unsigned long)-1) {
		m_value = TlsGetValue(MemoryPool::g_heapTlsIndex);
		TlsSetValue(MemoryPool::g_heapTlsIndex, newValue);
	}
	return this;
}
