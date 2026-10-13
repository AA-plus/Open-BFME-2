// ?rva00032160@GeneralAllocator@Allocator@EA@@QAEIPAX@Z
// partial score=0.92 date=2026-10-13
// ?rva00032160@GeneralAllocator@Allocator@EA@@QAEIPAX@Z
// partial score=0.45 date=2026-10-03
// no // cl: line: base flags -O2 -GR- -EHsc-

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

struct ListNode
{
	unsigned int m_0;
	unsigned char m_pad[8];
	ListNode *m_next;	// +0x0C
};

class GeneralAllocator
{
public:
	unsigned int rva00032160(void *block);
	int rva00031D00(void *block);

private:
	char m_pad0[0x49C];
	ListNode m_sentinel;	// +0x49C, next at +0x4A8
	char m_pad4AC[0x4E4 - 0x4AC];
	Lock *m_4E4;
};

unsigned int GeneralAllocator::rva00032160(void *block)
{
	Lock *lock = m_4E4;
	if (lock != 0) {
		EnterCriticalSection(lock);
		++lock->m_count;
	}

	unsigned int result = rva00031D00(block);
	result += (unsigned char)~(*(unsigned int *)((char *)block + 4) >> 1) & 1;

	ListNode *sentinel = &m_sentinel;
	ListNode *cur = m_sentinel.m_next;
	if (cur != sentinel) {
		unsigned int key = (unsigned int)block - *(unsigned int *)block;
		do {
			if ((unsigned int)cur - *(unsigned int *)cur == key)
				break;
			cur = cur->m_next;
		} while (cur != sentinel);
	}
	result += (cur == sentinel);

	if (lock != 0) {
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return result;
}

}
}
