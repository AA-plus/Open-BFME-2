// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small heap-allocator bodies from .text gaps no Ghidra function covers
// (twenty-third batch; see GapBodiesGE01.cpp), all inside the run of
// memory_pool.cpp's EA::Allocator::GeneralAllocator rows (0x00030D10..
// 0x00031BF0). Each begins after its neighbour's padding and ends in its own
// ret. Retail bytes establish every shape: chunks carry a previous-size word
// and a size word whose low three bits and top bit are flags (mask
// 0x7FFFFFF8), free chunks a forward (+8) and back (+0x0C) link; core blocks
// form a ring through +0x18/+0x1C around a sentinel at heap +0x448. The
// heap's own member names are not recovered, so each body keeps an
// address-derived name and the view below holds only the members they touch.

extern "C" __declspec(dllimport) void *__stdcall VirtualAlloc(void *address, unsigned long size, unsigned long type, unsigned long protect);
extern "C" __declspec(dllimport) int __stdcall VirtualFree(void *address, unsigned long size, unsigned long type);

struct GapChunk
{
	unsigned int m_prevSize;
	unsigned int m_size;
	GapChunk *m_fd;											// +0x08
	GapChunk *m_bk;											// +0x0C
};

struct GapCore
{
	char *m_base;
	unsigned int m_size;									// +0x04
	char m_pad08[0x18 - 0x08];
	GapCore *m_prev;										// +0x18
	GapCore *m_next;										// +0x1C
};

#define GAP_CHUNK_AT(p, offset) ((GapChunk *)((char *)(p) + (offset)))
#define GAP_CHUNK_SIZE(p) ((p)->m_size & 0x7FFFFFF8)

// --- 0x000309E0 (17B): is x a multiple of the power-of-two a.
bool rva000309E0(unsigned int x, unsigned int a)
{
	return (x & (a - 1)) == 0;
}

// --- 0x00030A00 (18B): round x up to the power-of-two a.
unsigned int rva00030A00(unsigned int x, unsigned int a)
{
	return (x + a - 1) & ~(a - 1);
}

// --- 0x00030B00 (21B): in-use bit of a chunk, kept in the next chunk's size.
int rva00030B00(GapChunk *chunk)
{
	return GAP_CHUNK_AT(chunk, GAP_CHUNK_SIZE(chunk))->m_size & 1;
}

// --- 0x00030B20 (21B): set it.
void rva00030B20(GapChunk *chunk)
{
	GAP_CHUNK_AT(chunk, GAP_CHUNK_SIZE(chunk))->m_size |= 1;
}

// --- 0x00030B40 (16B) / 0x00030B50 (14B): the same bit of the chunk at an
// explicit offset.
int rva00030B40(GapChunk *chunk, unsigned int offset)
{
	return GAP_CHUNK_AT(chunk, offset)->m_size & 1;
}

void rva00030B50(GapChunk *chunk, unsigned int offset)
{
	GAP_CHUNK_AT(chunk, offset)->m_size |= 1;
}

// --- 0x00030B70 (23B): store a size keeping the flag bits.
void rva00030B70(GapChunk *chunk, unsigned int size)
{
	chunk->m_size = (chunk->m_size & 0x80000007) | size;
}

// --- 0x00030BA0 (25B): link a chunk between fd and bk.
void rva00030BA0(GapChunk *chunk, GapChunk *fd, GapChunk *bk)
{
	chunk->m_fd = fd;
	chunk->m_bk = bk;
	fd->m_bk = chunk;
	bk->m_fd = chunk;
}

// --- 0x00030BC0 (23B): unlink a chunk.
void rva00030BC0(GapChunk *chunk)
{
	chunk->m_fd->m_bk = chunk->m_bk;
	chunk->m_bk->m_fd = chunk->m_fd;
}

// --- 0x000310F0 (36B): two fencepost chunks (8 then 9) after n bytes.
void rva000310F0(GapChunk *chunk, unsigned int n)
{
	GapChunk *post = GAP_CHUNK_AT(chunk, n);
	post->m_prevSize = n;
	post->m_size = 8;
	post = GAP_CHUNK_AT(post, 8);
	post->m_prevSize = 8;
	post->m_size = 9;
}

// --- 0x00031160 (70B): shrink a core's top chunk to the flagged size less
// nine, rounded down to eight, and close it with the 8/8/9 fencepost words.
GapChunk *rva00031160(GapChunk *chunk, unsigned int size, unsigned int flags)
{
	unsigned int value = size | flags;
	unsigned int n = ((value & 0x7FFFFFF8) - 9) & ~7u;
	chunk->m_size = (value & 0x80000007) | n;
	chunk->m_prevSize = 0;
	GapChunk *post = GAP_CHUNK_AT(chunk, n);
	post->m_prevSize = n;
	post->m_size = 8;
	*(unsigned int *)&post->m_fd = 8;
	*(unsigned int *)&post->m_bk = 9;
	return chunk;
}

struct GapBlockInfo
{
	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
};

struct GapBlockReport
{
	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0C;
	unsigned char m_type;									// +0x10
	unsigned char m_flag;									// +0x11
};

class Rva00030C50Heap
{
public:
	unsigned int rva00030C80(int bin);
	void rva00030CC0(bool on);
	bool rva00030CE0() const;
	void rva00030E90(int a, int b);
	void rva00030EB0(int a, int b);
	void rva00030ED0(unsigned char a, unsigned char b);
	void rva00031060(GapChunk *chunk, unsigned int size);
	void rva000311B0(const GapBlockInfo *info, GapBlockReport *report);
	void rva00031400(int value);
	bool rva000315C0(const char *p) const;
	void rva00031610(int a, unsigned int b);
	void rva00031640(GapCore *core, GapCore *before);
	void *rva00031710(unsigned int size, unsigned int *outSize);
	int rva00031750(void *p, unsigned int size);
private:
	int m_00;
	unsigned int m_04;
	char m_pad08[0x430 - 0x08];
	unsigned int m_binBits[6];								// +0x430
	GapCore m_cores;										// +0x448
	char *m_468;
	char m_pad46C[0x474 - 0x46C];
	unsigned char m_474;
	unsigned char m_475;
	char m_pad476[0x478 - 0x476];
	int m_478;
	unsigned int m_47C;
	int m_480;
	char m_pad484[0x498 - 0x484];
	bool m_topDown;											// +0x498
	char m_pad499[0x4AC - 0x499];
	int m_4AC;
	int m_4B0;
	char m_pad4B4[0x4B8 - 0x4B4];
	void (__cdecl *m_callback)(int value, int context);	// +0x4B8
	int m_callbackContext;									// +0x4BC
	int m_4C0;
	int m_4C4;
};

// --- 0x00030C80 (35B): test a bin bitmap bit.
unsigned int Rva00030C50Heap::rva00030C80(int bin)
{
	return (1 << (bin & 31)) & m_binBits[bin >> 5];
}

// --- 0x00030CC0 (29B): bit 0 of the +4 word.
void Rva00030C50Heap::rva00030CC0(bool on)
{
	if (on)
		m_04 |= 1;
	else
		m_04 &= ~1u;
}

// --- 0x00030CE0 (18B): the core ring's two links agree.
bool Rva00030C50Heap::rva00030CE0() const
{
	return m_cores.m_next == m_cores.m_prev;
}

// --- 0x00030E90 / 0x00030EB0 / 0x00030ED0 (23B each): pair setters.
void Rva00030C50Heap::rva00030E90(int a, int b)
{
	m_4AC = a;
	m_4B0 = b;
}

void Rva00030C50Heap::rva00030EB0(int a, int b)
{
	m_4C0 = a;
	m_4C4 = b;
}

void Rva00030C50Heap::rva00030ED0(unsigned char a, unsigned char b)
{
	m_474 = a;
	m_475 = b;
}

// --- 0x00031060 (28B): a free chunk of size n linked to itself, with the
// prev-in-use bit and the trailing size word.
void Rva00030C50Heap::rva00031060(GapChunk *chunk, unsigned int size)
{
	chunk->m_bk = chunk;
	chunk->m_fd = chunk;
	chunk->m_size = size | 1;
	GAP_CHUNK_AT(chunk, size)->m_prevSize = size;
}

// --- 0x000311B0 (35B): fill a block report of type 8.
void Rva00030C50Heap::rva000311B0(const GapBlockInfo *info, GapBlockReport *report)
{
	report->m_type = 8;
	report->m_00 = info->m_00;
	report->m_04 = info->m_04;
	report->m_0C = info->m_08;
	report->m_flag = 0;
}

// --- 0x00031400 (30B): forward a value to the optional callback.
void Rva00030C50Heap::rva00031400(int value)
{
	if (m_callback)
		m_callback(value, m_callbackContext);
}

// --- 0x000315C0 (69B): find the core holding p; true when p lies past the
// +0x468 mark.
bool Rva00030C50Heap::rva000315C0(const char *p) const
{
	for (const GapCore *core = m_cores.m_next; core != &m_cores; core = core->m_next)
		if (p >= core->m_base && p < core->m_base + core->m_size)
			return m_468 < p;
	return false;
}

// --- 0x00031610 (42B): a value and a count of at least one; clear +0x480.
void Rva00030C50Heap::rva00031610(int a, unsigned int b)
{
	if (b <= 0)
		b = 1;
	m_47C = b;
	m_478 = a;
	m_480 = 0;
}

// --- 0x00031640 (29B): insert a core ahead of another in the ring.
void Rva00030C50Heap::rva00031640(GapCore *core, GapCore *before)
{
	core->m_next = before;
	core->m_prev = before->m_prev;
	before->m_prev = core;
	core->m_prev->m_next = core;
}

// --- 0x00031710 (55B): commit a core with VirtualAlloc (top-down when +0x498
// is set) and report its size.
void *Rva00030C50Heap::rva00031710(unsigned int size, unsigned int *outSize)
{
	unsigned long type = 0x3000;
	if (m_topDown)
		type = 0x103000;
	void *p = VirtualAlloc(0, size, type, 4);
	if (p && outSize)
		*outSize = size;
	return p;
}

// --- 0x00031750 (21B): release a core.
int Rva00030C50Heap::rva00031750(void *p, unsigned int size)
{
	return VirtualFree(p, 0, 0x8000);
}
