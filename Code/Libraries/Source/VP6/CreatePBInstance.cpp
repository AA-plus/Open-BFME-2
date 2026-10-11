// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b56f0.md plus retail only. No decoder source was consulted.
// VP6_CreatePBInstance, retail RVA 0x001B56F0 (216 bytes).
// Target 0x001B6400 forwards bytes to duck_malloc at 0x001B63C0.
// Its allocator and native14B body differ from NameKeyGenerator::Bucket's
// donor operator new. Address-derived identity; original class is unknown.
struct BfmeSubJX
{
	int m_bfmeGapJX[14];
	int m_bfme38JX;
};

struct CodecState
{
	unsigned char m_bfmeHeadJX[0x13c];
	BfmeSubJX *m_bfme13cJX;
	unsigned char m_bfmeGap0JX[0x64];
	int m_bfme1a4JX;
	int m_bfme1a8JX;
	unsigned char m_bfmeGap1JX[4];
	int m_bfme1b0JX;
	int m_bfme1b4JX;
	unsigned char m_bfmeGap2JX[0x7c];
	int m_bfme234JX;
	int m_bfme238JX;
	int m_bfme23cJX;
	int m_bfme240JX;
	unsigned char m_bfmeGap3JX[0x50];
	void *m_bfme294JX;
	void *m_bfme298JX;
};

extern int g_bfmeSharedJX;
// g_bfmeSharedJX: matched references place it at VA 0xe23300 (zero-filled .bss).
int g_bfmeSharedJX;

class BfmeThingJT;

extern "C" void *__cdecl memcpy(void *d, const void *s, unsigned int n);
extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

struct CodecState;

extern "C" CodecState * __cdecl VP6_CreatePBInstance();

extern int g_bfmeTableJX;
// g_bfmeTableJX: matched references place it at VA 0xe22d40 (zero-filled .bss).
int g_bfmeTableJX;

extern "C" int __cdecl VP6_AllocateTmpBuffers(BfmeThingJT *q);
void bfmeFreeOneJT(void *q);

class Rva001B6400Allocation
{
public:
	enum AllocationTag { BFME_ZERO_JX = 0 };

	static void *operator new(unsigned int n, AllocationTag m);
};
extern "C" void *__cdecl CreatePostProcInstance(void *q);
extern "C" BfmeSubJX *__cdecl VP6_CreateQuantizer();
extern "C" int __cdecl VP6_InitFrameDetails(CodecState *s);
struct PB_INSTANCE;

extern "C" void __cdecl VP6_InitialiseConfiguration(PB_INSTANCE *pbi);
struct BfmeHolderBZB;

extern "C" void __cdecl VP6_DeleteQuantizer(void **q);
extern "C" void __cdecl DeletePostProcInstance(BfmeHolderBZB *h);
extern "C" void __cdecl VP6_DeleteFrameInfo(void *q);
extern "C" void __cdecl VP6_DeletePBInstance(PB_INSTANCE **instance);

extern "C" CodecState * __cdecl VP6_CreatePBInstance()
{
	int cfg[14];

	cfg[0] = 0;
	cfg[1] = 0;
	cfg[2] = 0;
	cfg[3] = 0;
	cfg[4] = 8;
	cfg[5] = 8;
	cfg[6] = 0;
	cfg[7] = 0;
	cfg[8] = 0;
	cfg[9] = 0;
	cfg[10] = 0;
	cfg[11] = 0;
	cfg[12] = 0;
	cfg[13] = 0;

	CodecState *p = (CodecState *)Rva001B6400Allocation::operator new(0x4954, Rva001B6400Allocation::BFME_ZERO_JX);

	if (p == 0)
		return 0;

	memset(p, 0, 0x1255 * 4);
	memcpy((char *)p + 0x1b0, cfg, 14 * 4);

	if (VP6_AllocateTmpBuffers((BfmeThingJT *)p) == 0)
	{
		bfmeFreeOneJT(p);

		return 0;
	}

	p->m_bfme1a8JX = 0x46;
	p->m_bfme294JX = &g_bfmeTableJX;

	memset((char *)p + 0x3a0, 0, 0x16);
	memset((char *)p + 0x3b6, 0, 0x63 * 4);

	return p;
}
