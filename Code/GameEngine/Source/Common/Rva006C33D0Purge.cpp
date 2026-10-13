// cl: /MD /DNDEBUG /EHsc
//
// ?rva006C33D0@Rva006C1F60@@QAEXHH@Z @ 0x006C33D0 643B, ret 8
//
// Debug-allocator delayed-free purge: (policy, limit). Under the scoped
// +0x4E4 lock and with the +0x530 depth counter raised, blocks are taken off
// the front of the delayed-free list (head chunk at +0x548, first block via
// its +0x554 link) and really freed through 0x006C3180, keeping the list's
// block count (+0x558) and byte volume (+0x55C) in step. Policy 0 empties the
// list; 1 stops once the count is within the limit; 2 once the volume is;
// 3 frees blocks whose stored time (the first word of the freed data) is
// later than now + limit seconds, the threshold clamped to 0 on overflow.
// Each block's size comes from 0x00032A20 before it is unlinked.
//
// Evidence: retail body; WorldBuilder's unoptimized twin at 0x00709370 has
// the same four policies with asserts naming the counters
// ("(mDelayedFreeListSize == 0) && (mDelayedFreeVolume == 0)",
// "nUsableSize < 0x40000000"). Its policy-3 loop reads the time into a
// variable first zeroed, and only that spelling gives retail's register
// choice for the chunk and data pointers there. Names are address-derived.

struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *);
int Rva00030DF0Release(Rva00030DD0Lock *);
extern "C" __declspec(dllimport) unsigned long __stdcall GetTickCount();

namespace EA { namespace Allocator {
class GeneralAllocator
{
public:
	unsigned rva00032A20(const void *);
};
} }

struct GeneralAllocatorDebugBlock;

class GeneralAllocatorDebug : public EA::Allocator::GeneralAllocator
{
public:
	void rva006C3180(GeneralAllocatorDebugBlock *);
};

struct DelayedChunk
{
	unsigned prevSize, size;
	DelayedChunk *prev, *next;
};

struct Guard
{
	Guard(Rva00030DD0Lock *p) : lock(p)
	{
		if (lock)
			Rva00030DD0AddRef(lock);
	}
	~Guard()
	{
		if (lock)
			Rva00030DF0Release(lock);
	}
	Rva00030DD0Lock *lock;
};

class Rva000353B0
{
public:
	void *rva00034d10(int a, int b, int c, int d);
	void *rva000353F0(int a, int b, int c, int d);
};

class Rva006C1F60 : public GeneralAllocatorDebug
{
public:
	void rva006C33D0(int policy, int limit);
	void *rva00033ED0(unsigned int size, int flags);
	void *rva006C1CC0(unsigned int size, int flags);
	void *rva006C37E0(int a, int b, int c, int d);
	void *rva006C3810(int a, int b, int c, int d);

	char unknown0[0x4e4];
	Rva00030DD0Lock *lock;
	char unknown4e8[0x530 - 0x4e8];
	unsigned depth;
	char unknown534[0x548 - 0x534];
	DelayedChunk head;
	unsigned count, total;

	__forceinline void remove(DelayedChunk *chunk)
	{
		char *data = (char *)chunk + 8;
		unsigned size = rva00032A20(data);
		chunk->prev->next = chunk->next;
		chunk->next->prev = chunk->prev;
		--count;
		total -= size;
		rva006C3180((GeneralAllocatorDebugBlock *)chunk);
	}
};

void Rva006C1F60::rva006C33D0(int policy, int limit)
{
	Guard guard(lock);
	++depth;
	if (policy == 0) {
		while (head.next != &head)
			remove(head.next);
	} else if (policy == 1) {
		while (head.next != &head) {
			if (count <= (unsigned)limit)
				break;
			remove(head.next);
		}
	} else if (policy == 2) {
		while (head.next != &head) {
			if (total <= (unsigned)limit)
				break;
			remove(head.next);
		}
	} else if (policy == 3) {
		unsigned now = GetTickCount() / 1000;
		unsigned threshold = now + (unsigned)limit;
		if (threshold < now)
			threshold = 0;
		while (head.next != &head) {
			DelayedChunk *chunk = head.next;
			char *data = (char *)chunk + 8;
			unsigned size = rva00032A20(data);
			unsigned freedTime = 0;
			freedTime = (unsigned)chunk->prev;
			if (freedTime <= threshold)
				break;
			chunk->prev->next = chunk->next;
			chunk->next->prev = chunk->prev;
			--count;
			total -= size;
			rva006C3180((GeneralAllocatorDebugBlock *)chunk);
		}
	}
	--depth;
}

// Retail 0x006C3810 (43 B, ret 0x10): purge the whole delayed-free list
// (policy 0) and then forward the four arguments to the allocator body at
// 0x00034D10, returning its result. Its twin 0x006C37E0 does the same in
// front of 0x000353F0. Names address-derived.
void *Rva006C1F60::rva006C3810(int a, int b, int c, int d)
{
	rva006C33D0(0, 0);
	return ((Rva000353B0 *)this)->rva00034d10(a, b, c, d);
}

void *Rva006C1F60::rva006C37E0(int a, int b, int c, int d)
{
	rva006C33D0(0, 0);
	return ((Rva000353B0 *)this)->rva000353F0(a, b, c, d);
}

// Retail 0x006C1CC0 (71 B, ret 8), next to the location formatter: allocate
// through 0x00033ED0 (two extra bytes when the flags' sign bit is set) and,
// on success, clear the 16-bit word 10 bytes before the end of the block's
// usable size (header +4 masked 0x7FFFFFF8, plus 4 unless bit 1 is set).
// Name address-derived.
void *Rva006C1F60::rva006C1CC0(unsigned int size, int flags)
{
	if (flags & 0x80000000)
		size += 2;
	void *block = rva00033ED0(size, flags);
	if (block)
	{
		unsigned int header = ((unsigned int *)block)[-1];
		unsigned int usable;
		if ((header & 2) == 0)
			usable = (header & 0x7FFFFFF8) + 4;
		else
			usable = header & 0x7FFFFFF8;
		*(unsigned short *)((char *)block + usable - 0xA) = 0;
	}
	return block;
}
