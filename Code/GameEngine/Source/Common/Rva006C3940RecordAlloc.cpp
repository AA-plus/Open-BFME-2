// cl: /DNDEBUG /MD
//
// ?rva006C3940Alloc@Rva006C39F0Owner@@QAEPAXI@Z @ 0x006C3940 146B, ret 4
//
// Allocates one external debug record of the given size for the debug
// allocator. When the allocator's record allocator (+0x678) is the
// allocator itself, the +0x478 word is cleared for the duration and the
// request is retried through 0x00033ED0 with the 0x80000000 flag (two extra
// bytes) while the delayed-free list at +0x548 still has blocks to purge
// (0x006C33D0). A block gets the 16-bit word ten bytes short of its usable end
// cleared and chunk flag 4 set in its size field. Otherwise the request goes
// to the record allocator through 0x00035080 with flags 0.
//
// The allocate-and-mark step is an inline helper (the 0x006C40C0 worker in
// Rva006C4300Malloc.cpp has the same one): written inline in the loop, cl
// rotates the loop and duplicates the 0x00033ED0 call, which retail does not.
//
// Evidence: retail body; WorldBuilder's unoptimized twin at 0x007091F0 has
// the same control flow (its allocation is a virtual Malloc call that retail
// reaches directly). The name is the address-derived pin callers use.

namespace EA { namespace Allocator {
class GeneralAllocator
{
public:
	void *rva00035080(unsigned size, int flags);
};
} }

class Rva006C1F60
{
public:
	void *rva00033ED0(unsigned size, int flags);
	void rva006C33D0(int a, int b);
};

struct Rva006C3940Chunk
{
	unsigned priorSize;
	unsigned size;
	Rva006C3940Chunk *next;
	Rva006C3940Chunk *prev;
};

class Rva006C39F0Owner
{
public:
	void *rva006C3940Alloc(unsigned size);
private:
	void *mallocMarked(unsigned size, int flags)
	{
		unsigned request = size;
		if (flags & 0x80000000)
			request = size + 2;
		void *p = ((Rva006C1F60 *)this)->rva00033ED0(request, flags);
		if (p != 0) {
			unsigned n = ((unsigned *)p)[-1];
			unsigned usable = !(n & 2) ? (n & 0x7ffffff8) + 4 : (n & 0x7ffffff8);
			*(unsigned short *)((char *)p + usable - 10) = 0;
		}
		return p;
	}
	unsigned char m_pad0[0x478];
	unsigned m_478;
	unsigned char m_pad1[0x548 - 0x47c];
	Rva006C3940Chunk m_delayed;
	unsigned char m_pad2[0x678 - 0x558];
	EA::Allocator::GeneralAllocator *m_recordAllocator;
};

void *Rva006C39F0Owner::rva006C3940Alloc(unsigned size)
{
	if (m_recordAllocator == (EA::Allocator::GeneralAllocator *)this) {
		unsigned saved = m_478;
		m_478 = 0;
		void *p;
		for (;;) {
			p = mallocMarked(size, 0x80000000);
			if (p != 0) {
				((unsigned *)p)[-1] |= 4;
				break;
			}
			if (m_delayed.prev == &m_delayed)
				break;
			((Rva006C1F60 *)this)->rva006C33D0(0, 0);
		}
		m_478 = saved;
		return p;
	}
	return m_recordAllocator->rva00035080(size, 0);
}
