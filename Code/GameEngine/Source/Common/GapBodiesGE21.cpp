// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG
// CRT replacement shims from .text gaps no Ghidra function covers, between
// the matched wwmath wrappers (0x0002FBC0) and mem_ops.cpp's operator
// new/delete (0x0002FD60..0x0002FDE0). Each begins after its neighbour's
// padding and ends in its own ret or tail jump. They route the C heap through
// the game's pluggable memory-manager slots, the counterparts of BFME 1's
// Rva00881D70CrtShims.cpp (donor shapes only: BFME 2's allocate slot takes a
// third tag word, read from these bodies). The inlined strlen/strcpy loops and
// the rep stos memset are the /O2 intrinsic forms. Names stay address-derived
// except the two operator new overloads, whose ABI is the one Zero Hour's
// GameMemory.h declares for the file/line forms.
#include <string.h>
#include <stdlib.h>

typedef void *(__cdecl *GameAllocateFunction)(unsigned int, int, const void *);
extern "C" GameAllocateFunction __gameMemAllocatePtr;	// VA 0x00DE0404

namespace _STL
{
	template <class T> class allocator;
	template <> class allocator<char>
	{
	public:
		static char *allocate(unsigned int n, const void *hint);	// 0x000307F0
	};
}

// Tag the duplicating shims pass to the byte allocator: the multi-character
// constant 'str' (dword 0x00737472 in the pushes).
#define GAP_RTS_TAG ((const void *)'str')

// --- 0x0002FBD0 (54B): calloc: count*size bytes, class 0, zero-filled.
void *rva0002FBD0(unsigned int count, unsigned int size)
{
	unsigned int bytes = count * size;
	void *block = __gameMemAllocatePtr(bytes, 0, 0);
	if (block)
		memset(block, 0, bytes);
	return block;
}

// --- 0x0002FC60 (19B): malloc: class 0.
void *rva0002FC60(unsigned int size)
{
	return __gameMemAllocatePtr(size, 0, 0);
}

// --- 0x0002FCA0 (24B): realloc through the resize slot VA 0x00DE0400 with
// two zero words.
extern void *g_00DE0400;

void *rva0002FCA0(void *block, unsigned int size)
{
	return ((void *(__cdecl *)(void *, unsigned int, int, int))g_00DE0400)(block, size, 0, 0);
}

// --- 0x0002FCC0 (68B): strdup through the rowed allocator<char>::allocate.
char *rva0002FCC0(const char *s)
{
	if (s)
	{
		char *copy = _STL::allocator<char>::allocate(strlen(s) + 1, GAP_RTS_TAG);
		if (copy)
			return strcpy(copy, s);
	}
	return 0;
}

// --- 0x0002FD10 (58B): wcsdup through the same allocator, msvcr71 wcslen
// and wcscpy imports.
wchar_t *rva0002FD10(const wchar_t *s)
{
	if (s)
	{
		wchar_t *copy = (wchar_t *)_STL::allocator<char>::allocate(wcslen(s) * 2 + 2, GAP_RTS_TAG);
		if (copy)
			return wcscpy(copy, s);
	}
	return 0;
}

// --- 0x0002FD50 (6B): _mbsdup forwarder (tail jump through the import).
extern "C" __declspec(dllimport) unsigned char *__cdecl _mbsdup(const unsigned char *s);

unsigned char *rva0002FD50(const unsigned char *s)
{
	return _mbsdup(s);
}

// --- 0x0002FDC0 / 0x0002FE00 (22B each): the file/line operator new forms,
// class 1 scalar and class 2 array, tail-jumping into the allocate slot over
// their own argument words.
void *__cdecl operator new(unsigned int size, const char *, int)
{
	return __gameMemAllocatePtr(size, 1, 0);
}

void *__cdecl operator new[](unsigned int size, const char *, int)
{
	return __gameMemAllocatePtr(size, 2, 0);
}

// --- 0x0002FFA0 (25B): run the rowed resolver 0x00030730, register the
// slot at VA 0x00DE040C with atexit, then tail-call the slot at VA 0x00DE0410.
void Rva00030730Init();
extern void *g_00DE040C;
extern void *g_00DE0410;

void rva0002FFA0()
{
	Rva00030730Init();
	atexit((void (__cdecl *)(void))g_00DE040C);
	((void (__cdecl *)(void))g_00DE0410)();
}

// --- 0x0002F980 (22B): the registry block's once-gate on its own, ahead of
// the getters at 0x0002F9C0 that inline the same test; tail-jumps to the
// rowed LoadRegistryValues 0x0002F840.
extern bool g_registryValuesLoaded;
void LoadRegistryValues();

void rva0002F980()
{
	if (!g_registryValuesLoaded)
	{
		g_registryValuesLoaded = true;
		LoadRegistryValues();
	}
}
