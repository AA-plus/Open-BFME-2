// ?rva00032B00@@YAPAXI@Z
// partial score=0.85 date=2026-10-13
// ?rva00032B00@GeneralAllocator@Allocator@EA@@QAEPAXI@Z
// partial score=0.85 date=2026-10-13
// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
extern "C" __declspec(dllimport) void *__stdcall VirtualAlloc(void *address, unsigned int size, unsigned long type, unsigned long protect);
namespace EA
{
namespace Allocator
{
class GeneralAllocator
{
public:
	void *rva00032B00(unsigned int size);
private:
	unsigned int alignUp(unsigned int v) const { unsigned int a = m_alignment; return (v + a - 1) & ~(a - 1); }

	struct ListNode
	{
		unsigned int m_unk0;
		unsigned int m_size;
		unsigned int m_releaseSize;
		unsigned char m_unknownC;
		bool m_releaseDirect;
		bool m_releaseAllowed;
		unsigned char m_unknownF;
		void (__cdecl *m_releaseCallback)(GeneralAllocator *, void *, unsigned int, void *);
		void *m_releaseContext;
		ListNode *m_next;
		ListNode *m_prev;
	};
	unsigned char m_pad0[0x448];
	ListNode m_sentinel;
	unsigned char m_pad468[0x498 - 0x468];
	unsigned char m_topDown;
	unsigned char m_pad499[0x4D4 - 0x499];
	unsigned int m_alignment;
	unsigned int m_minCore;
	unsigned int m_commit;
};

void *GeneralAllocator::rva00032B00(unsigned int size)
{
	unsigned int rounded = alignUp(size);
	unsigned int flags = 1;
	if (rounded < m_minCore)
		rounded = alignUp(m_minCore);
	unsigned int reserve = (rounded + 0xFFFF) & 0xFFFF0000;
	ListNode *node = (ListNode *)VirtualAlloc(0, reserve, 0x2000, 4);
	if (node != 0)
	{
		rounded = 0x100000;
		if (m_commit > rounded)
			rounded = alignUp(m_commit);
		if (rounded > reserve)
			rounded = reserve;
		node = (ListNode *)VirtualAlloc(node, rounded, 0x1000, 4);
	}
	if (node == 0)
	{
		unsigned long type = 0x3000;
		if (m_topDown)
			type = 0x103000;
		node = (ListNode *)VirtualAlloc(0, rounded, type, 4);
		if (node != 0)
		{
			flags = 3;
			reserve = rounded;
		}
	}
	if (node != 0)
	{
		node->m_releaseSize = rounded;
		node->m_size = rounded;
		node->m_unk0 = ((unsigned int)node + 0x27) & 0xFFFFFFF8;
		node->m_unknownC = (flags >> 1) & 1;
		ListNode *list = &m_sentinel;
		bool nonEmpty = m_sentinel.m_prev != list;
		node->m_prev = list;
		node->m_releaseDirect = nonEmpty;
		node->m_unknownF = nonEmpty;
		bool *pe = &node->m_releaseAllowed;
		*pe = true;
		node->m_releaseCallback = 0;
		node->m_releaseContext = 0;
		node->m_next = list->m_next;
		list->m_next = node;
		node->m_next->m_prev = node;
		node->m_releaseSize = reserve;
		unsigned int *chunk = (unsigned int *)node->m_unk0;
		unsigned int chunkSize = ((unsigned int)node - (unsigned int)chunk + rounded) | flags;
		chunk[0] = 0;
		unsigned int fencepostOffset = (chunkSize & 0x7FFFFFF8) - 9;
		fencepostOffset &= 0xFFFFFFF8;
		chunk[1] = (chunkSize & 0x80000007) | fencepostOffset;
		unsigned int *fencepost = (unsigned int *)((char *)chunk + fencepostOffset);
		fencepost[0] = fencepostOffset;
		fencepost[1] = 8;
		fencepost[2] = 8;
		fencepost[3] = 9;
		return chunk;
	}
	return 0;
}
}
}
