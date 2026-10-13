// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// ?Rva000ABD70Clear@@YAXXZ @0x000ABD70 42B
// Unlock free function that releases a cached virtual object and clears a
// global Dict. Evidence: ret-via-jmp tail to ?clear@Dict@@QAEXXZ, virtual
// slot-0 call with push 0 returning pointer freed via ??3@YAXPAX@Z, and
// dword [eax] nulled with /O1 and-idiom, globals g_00E00940/g_00E00944.

class Dict
{
public:
	void clear();
};

struct Inner
{
	virtual void *get(int x);
};

struct Outer
{
	Inner *m_ptr;
};

Outer * g_00E00940;	// retail RVA 0x00A00940 (.data, 4 bytes), defined here: nothing else owns it
extern Dict g_Va00E00944;
#define g_00E00944 g_Va00E00944
// ^ g_00E00944 is only an alias of the owned global g_Va00E00944 (ledger names column).

void Rva000ABD70Clear()
{
	Inner *p = g_00E00940->m_ptr;
	if (p) {
		void *r = p->get(0);
		::operator delete(r);
		g_00E00940->m_ptr = 0;
	}
	return g_00E00944.clear();
}
