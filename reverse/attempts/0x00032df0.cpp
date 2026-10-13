// ?rva00032DF0@GeneralAllocator@Allocator@EA@@QAEPAXI@Z
// partial score=0.999 date=2026-10-13
// ?rva00032DF0@GeneralAllocator@Allocator@EA@@QAEPAXI@Z
// partial score=0.995 date=2026-10-12
// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
extern "C" __declspec(dllimport) void *__stdcall VirtualAlloc(void *address, unsigned int size, unsigned long type, unsigned long protect);
namespace EA
{
namespace Allocator
{
class GeneralAllocator
{
public:
	void *rva00032DF0(unsigned int size);
private:
	struct SmallNode
	{
		unsigned int m_base;
		unsigned int m_size;
		SmallNode *m_prev;
		SmallNode *m_next;
	};
	unsigned char m_pad0[0x488];
	unsigned int m_mapCount;
	unsigned int m_mapBytes;
	unsigned char m_pad490[0x498 - 0x490];
	unsigned char m_topDown;
	unsigned char m_pad499[0x49C - 0x499];
	SmallNode m_mapList;
};

void *GeneralAllocator::rva00032DF0(unsigned int size)
{
	unsigned int total = (size + 0x101E) & 0xFFFFF000;
	if (total >= size)
	{
		unsigned long type = 0x3000;
		if (m_topDown)
			type = 0x103000;
		void *memory = VirtualAlloc(0, total, type, 4);
		if (memory != 0)
		{
			++m_mapCount;
			m_mapBytes += total;
			total -= 0x10;
			unsigned int *header;
			unsigned int misalign = (unsigned int)memory & 7;
			if (misalign != 0)
			{
				unsigned int pad = 8 - misalign;
				header = (unsigned int *)((char *)memory + pad);
				total -= pad;
				header[0] = pad;
				header[1] = (total - pad) | 2;
			}
			else
			{
				header = (unsigned int *)memory;
				header[0] = 0;
				header[1] = total | 2;
			}
			SmallNode *node = (SmallNode *)((char *)header + total);
			node->m_base = total;
			node->m_size = 0x13;
			SmallNode *head = m_mapList.m_next;
			SmallNode *list = &m_mapList;
			node->m_prev = list;
			node->m_next = head;
			list->m_next = node;
			head->m_prev = node;
			return header + 2;
		}
	}
	return 0;
}
}
}
