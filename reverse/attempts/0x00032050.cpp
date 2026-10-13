// ?rva00032050@GeneralAllocator@Allocator@EA@@QAEIPAXI@Z
// partial score=0.8 date=2026-10-13
// ?rva00032050@GeneralAllocator@Allocator@EA@@QAEIPAXI@Z
// partial score=0.55 date=2026-10-03
// no // cl: line: base flags -O2 -GR- -EHsc-
// Banked attempt for ?rva00032050@GeneralAllocator@Allocator@EA@@QAEIPAXI@Z
// retail 0x0032050 (140 bytes). All five size adjustments are decoded and the
// arithmetic matches retail instruction-for-instruction; the miss is register
// allocation only. Retail keeps this in edi, the lock in esi, the block in ebx
// and spills the masked header to the +4 argument slot, leaving ebp unused.
// This source lets MSVC 7.1 put the header in edi and the lock in ebp, so the
// whole prologue/epilogue shifts by 5 bytes (135 vs 140). Semantics and the
// term order are as decoded from retail.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);

namespace EA
{
namespace Allocator
{

struct Lock
{
	unsigned char m_pad[0x18];
	int volatile m_count;
};

class GeneralAllocator
{
public:
	unsigned int rva00032050(void *block, unsigned int flags);
	int rva00031F90(void *block);

private:
	char m_pad[0x4E4];
	Lock *m_4E4;
};

unsigned int GeneralAllocator::rva00032050(void *block, unsigned int flags)
{
	Lock *lock = m_4E4;
	if (lock != 0) {
		EnterCriticalSection(lock);
		++lock->m_count;
	}

	unsigned int size = *(unsigned int *)((char *)block + 4) & 0x7FFFFFF8;
	int result = rva00031F90(block);
	_ReadWriteBarrier();
	result += (((unsigned char)size) & 7) != 0;
	result += size < 0x10;
	result += (((unsigned char)(unsigned int)block) & 7) != 0;
	result += size < 8;
	result += size >= flags + 0x10;

	if (lock != 0) {
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return result;
}

}
}
