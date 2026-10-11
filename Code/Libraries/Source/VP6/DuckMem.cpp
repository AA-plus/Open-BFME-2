// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b6380.md 001b6390.md 001b63a0.md
// plus retail only. No decoder source was consulted.
// The EA duck_mem allocator shim: a global allocator object pointer at
// 0x00DFDA54 (ledger name G00DFDA54, an int cell) whose vtable slot 0 is
// allocate and slot 1 is free. All cdecl.
extern int G00DFDA54;

class DuckAllocator
{
public:
	virtual void *allocate(unsigned int size);
	virtual void release(void *block, int flag);
};

#define TheDuckAllocator (*(DuckAllocator **)&G00DFDA54)

extern "C" void __cdecl free(void *block);

// RVA 0x001B6380..0x001B638A: install the allocator object.
extern "C" void __cdecl duck_mem_set_allocator(DuckAllocator *allocator)
{
	TheDuckAllocator = allocator;
}

// RVA 0x001B6390..0x001B6396: return the installed allocator object.
extern "C" DuckAllocator *__cdecl duck_mem_get_allocator(void)
{
	return TheDuckAllocator;
}

// RVA 0x001B63A0..0x001B63BC: release through the object else the engine free.
extern "C" void __cdecl duck_free(void *block)
{
	DuckAllocator *host = TheDuckAllocator;
	if (host)
		host->release(block, 0);
	else
		free(block);
}
