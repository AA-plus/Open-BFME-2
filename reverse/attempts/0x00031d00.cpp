// ?rva00031D00@GeneralAllocator@Allocator@EA@@QAEHPBX@Z
// partial score=0.7 date=2026-10-13
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?rva00031D00@GeneralAllocator@Allocator@EA@@QAEHPBX@Z
// partial score=0.6 date=2026-10-13
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);

namespace EA { namespace Allocator {
class GeneralAllocator
{
public:
	struct Lock
	{
		unsigned char m_pad[0x18];
		int volatile m_count;
	};
	struct Node { unsigned int m_start; unsigned int m_size; };
	Node *rva00031680(const void *block);
	int rva00031D00(const void *block);

	unsigned char m_pad0[0x440];
	void *m_440;
	unsigned char m_pad444[0x460 - 0x444];
	unsigned int m_460;
	unsigned int m_464;
	unsigned char m_pad468[0x470 - 0x468];
	int m_470;
	unsigned char m_pad474[0x4D4 - 0x474];
	unsigned int m_4D4;
	unsigned char m_pad4D8[0x4E4 - 0x4D8];
	Lock *m_4E4;
};

int GeneralAllocator::rva00031D00(const void *block)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}
	int score = 0;
	int depth = m_470;
	if (depth <= 1)
	{

		m_470 = (depth + 1);
		const unsigned int *hdr = (const unsigned int *)block;
		unsigned int size = hdr[1];
		score = ((size & 0x7FFFFFF8) >= 0x40000000);
		if ((size & 2) != 0)
		{
			score += (rva00031680(block) != 0);
			unsigned int mask = m_4D4 - 1;
			score += ((((unsigned int)block - hdr[0]) & mask) != 0);
			score += ((((unsigned int)block + (size & 0x7FFFFFF8) + 0x10) & mask) != 0);
			_ReadWriteBarrier();
			score += ((((unsigned char)(unsigned int)block) & 7) != 0);
		}
		else
		{
			Node *node = rva00031680(block);
			score += (node == 0);
			score += ((unsigned int)block < node->m_start);
			unsigned int nodeEnd = node->m_start + node->m_size;
			score += ((unsigned int)block >= nodeEnd);
			unsigned int blockEnd = (unsigned int)block + (size & 0x7FFFFFF8);
			score += (blockEnd >= nodeEnd);
			if (block == m_440)
			{
				score += (hdr[2] != (unsigned int)block || hdr[3] != (unsigned int)block);
				score += ((size & 0x7FFFFFF8) < 0x10);
				score += ((unsigned char)~(*(const unsigned char *)(hdr + 1))) & 1 && 1;
				_ReadWriteBarrier();
			}
			else if (m_464 == m_460)
			{
				score += ((unsigned int)block < node->m_start);
				score += ((unsigned int)node + node->m_size - 0x10 < blockEnd);
			}
		}
		m_470 = (depth + 1) - 1;
	}
	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return score;
}

}}
