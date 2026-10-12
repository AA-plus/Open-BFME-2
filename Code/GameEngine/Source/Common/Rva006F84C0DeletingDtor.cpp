// cl: /O1 /MD
// ??_GRva006F84C0@@UAEPAXI@Z, retail 0x006F84C0, 35 bytes.
// Scalar deleting destructor: calls complete dtor at 0x006F8460
// (??1Rva006F8460 rowed 37B) then sized pool release via pinned
// 0x006DB270 with pool at 0x00E176E8 and class size 0x1C.

class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

// Existing Apt pool provider; retail callers load this global at VA 0x00E176E8.
extern Rva006DB270 *g_pChainBlockAllocator;

class Rva006F84C0
{
public:
	__declspec(noinline) virtual ~Rva006F84C0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[0x1C - 4]; // sizeof 0x1C for the sized delete
};

// ??1Rva006F84C0@@UAE@XZ present-unmatched
Rva006F84C0::~Rva006F84C0()
{
	m_pad[0] = 0;
}

void deleteRva006F84C0(Rva006F84C0 *p)
{
	delete p;
}
