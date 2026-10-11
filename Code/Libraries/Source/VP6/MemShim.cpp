// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b6420.md 001b6460.md plus retail
// only. No decoder source was consulted.
extern "C" void *__cdecl memset(void *block, int value, unsigned int bytes);
#pragma intrinsic(memset)

void *__cdecl bfmeAllocBlock(unsigned int bytes); // 0x001B63C0 duck_malloc core

// RVA 0x001B6420
extern "C" void *__cdecl duck_memset(void *destination, int value, unsigned int bytes)
{
	return memset(destination, value, bytes);
}

// RVA 0x001B6460
extern "C" void *__cdecl duck_calloc(unsigned int count, unsigned int size)
{
	unsigned int bytes = count * size;
	void *block = bfmeAllocBlock(bytes);
	if (block)
		memset(block, 0, bytes);
	return block;
}
