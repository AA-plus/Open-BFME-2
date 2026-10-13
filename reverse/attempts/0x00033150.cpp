// ?rva00033150@GeneralAllocator@Allocator@EA@@QAEXPBX@Z
// partial score=0.997 date=2026-10-14
// ?rva00033150@GeneralAllocator@Allocator@EA@@QAEXPBX@Z
// partial score=0.997 date=2026-10-14 round5: nd3, 374/374 bytes.
// SOLE residue: the mapped-release counter home register. Retail: mov ebp,[edi+0x48C]; sub ebp,ebx; ... mov [edi+0x48C],ebp.
// Ours (best): mov edx,[edi+0x48C]; sub edx,ebx; ... mov [edi+0x48C],edx. Everything else (fast-bin push,
// boundary-tag coalesce, sentinel branch, 64K trim, mapped unlink/MEM_RELEASE) matches instruction-for-instruction.
// The volatile member + _ReadWriteBarrier before the counter and the prefix->total reuse are load-bearing:
// removing any of them costs 20+ instruction diffs. 2831 search trials from this source found no improvement.
// Port: add m_head440 (+0x440), m_unknown488 (+0x488), m_unknown48C (+0x48C), m_unknown4C8 (+0x4C8),
// m_unknown4CC (+0x4CC) to the memory_pool.cpp GeneralAllocator view (m_unknown48C volatile) and define the
// body there; the class view below keeps the same offsets.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// cl: /O2 /GR- /EHsc-
extern "C" __declspec(dllimport) int __stdcall VirtualFree(void *address, unsigned int size, unsigned long type);
namespace EA 

{
 namespace Allocator 
 
 {
  struct Rva00031BF0Chunk 
  
  {
   unsigned previousSize;
   unsigned size;
   Rva00031BF0Chunk* previous;
   Rva00031BF0Chunk* next;
   
  }
  ;
  class GeneralAllocator
  
  {
   public:
   void rva00033150(const void *block);
   bool rva00031BB0(const void *block);
   unsigned int rva00032C60(unsigned int size);
   private:
   unsigned int m_unknown0;
   unsigned int m_maxFastSize;
   Rva00031BF0Chunk* m_fastBins[10];
   Rva00031BF0Chunk* m_bins[256];
   char m_pad430[0x10];
   Rva00031BF0Chunk *m_head440;
   char m_pad444[4];
   char m_pad448[0x488-0x448];
   unsigned int m_unknown488;
   volatile unsigned int m_unknown48C;
   char m_pad490[0x4C8 - 0x490];
   unsigned int m_unknown4C8;
   volatile unsigned int m_unknown4CC;
   char m_pad4D0[0x4E4 - 0x4D0];
   void *m_4E4;
   
  }
  ;
  void GeneralAllocator::rva00033150(const void *block)
  
  {
   if (block == 0)
   return;
   Rva00031BF0Chunk *chunk = (Rva00031BF0Chunk *)((char *)block - 8);
   unsigned int header = chunk->size;
   unsigned int size = header & 0x7FFFFFF8;
   if (size <= m_maxFastSize)
   
   {
    m_maxFastSize |= 1;
    Rva00031BF0Chunk **bin = &m_fastBins[(size >> 3) - 2];
    chunk->next = *bin;
    chunk->size = chunk->size | 0x80000004;
    *bin = chunk;
    return;
    
   }
   if ((header & 2) == 0)
   
   {
    Rva00031BF0Chunk *next = (Rva00031BF0Chunk *)((char *)chunk + size);
    unsigned int nextSize = next->size & 0x7FFFFFF8;
    if ((header & 1) == 0)
    
    {
     unsigned int prevSize = chunk->previousSize;
     chunk = (Rva00031BF0Chunk *)((char *)chunk - prevSize);
     size += prevSize;
     chunk->size = size | 1;
     next->previousSize = size;
     chunk->previous->next = chunk->next;
     chunk->next->previous = chunk->previous;
     
    }
    if ((*(unsigned int *)((char *)next + nextSize + 4) & 1) != 0)
    
    {
     next->size &= 0xFFFFFFFE;
     next->previousSize = size;
     
    }
    else
    
    {
     next->previous->next = next->next;
     next->next->previous = next->previous;
     size += nextSize;
     chunk->size = size | 1;
     *(unsigned int *)((char *)chunk + size) = size;
     
    }
    if (chunk != m_head440 && next != m_head440)
    
    {
     Rva00031BF0Chunk *bin = (Rva00031BF0Chunk *)((char *)this + 0x30);
     Rva00031BF0Chunk *old = bin->next;
     chunk->previous = bin;
     chunk->next = old;
     bin->next = chunk;
     old->previous = chunk;
     
    }
    else
    
    {
     m_head440 = chunk;
     chunk->next = chunk;
     chunk->previous = chunk;
     chunk->size = size | 1;
     *(unsigned int *)((char *)chunk + size) = size;
     
    }
    if (size >= 0x10000)
    
    {
     void *end = (char *)chunk + size;
     if (rva00031BB0(end) && size >= m_unknown4C8)
     rva00032C60(m_unknown4CC);
     
    }
    
   }
   else
   
   {
    Rva00031BF0Chunk *next = (Rva00031BF0Chunk *)((char *)chunk + size);
    unsigned int prefix = chunk->previousSize;
    void *data = (char *)chunk - prefix;
    prefix += size + 0x10;
    next->previous->next = next->next;
    next->next->previous = next->previous;
    _ReadWriteBarrier();
    m_unknown48C -= prefix;
    --m_unknown488;
    VirtualFree(data, 0, 0x8000);
    
   }
   
  }
  
 }
 
}
