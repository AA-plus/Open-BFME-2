// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
// ??0Rva005F3F73@@QAE@PAX0@Z, RVA 0x005F3F73, 39 bytes.
// Address-derived class; called with a 0x18-byte allocation by 0x005F412B.
extern "C" const void *const __identifier("??_7Rva005F3FFC@@6B@")[];

class Rva005F3F73
{
public:
	Rva005F3F73(void *first, void *second);

private:
	const void *m_vtable;
	void *m_first;
	void *m_second;
	int m_zero0C;
	int m_zero10;
	char m_zero14;
	char m_zero15;
};

Rva005F3F73::Rva005F3F73(void *first, void *second)
	: m_vtable(__identifier("??_7Rva005F3FFC@@6B@")), m_first(first), m_second(second),
	  m_zero0C(0), m_zero10(0), m_zero14(0), m_zero15(0)
{
}
