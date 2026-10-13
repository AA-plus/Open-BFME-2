// cl: /O2 /arch:SSE /MD /EHsc /I.
// PooledString::setString at 0x006CB7C0, next to getHash (0x006CB780) in the same
// /O2 run as string_inline.cpp. Ghidra's 489 omits the trailing RET 4; the full
// body ends at 0x006CB9AC (492 B). Entry next0, folded-case alias4 and text8 are
// established by target comparisons; the 36-byte lock is the existing target ABI
// at 0x4411C1 (flag +20 and CS +8 witnessed by Enter/LeaveCriticalSection). The
// original pool names are unknown.
#define _DLL
#include <string.h>
#include "Code/GameEngine/Include/Common/Rva00041004Lock.h"

template<class T> __forceinline volatile T &r1_vwrite(T &value) { return *(volatile T *)&value; }

extern "C" {
    __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *);
    __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *);
}

namespace _STL {
    template<class T> class allocator {
    public:
        static T *allocate(unsigned, const void *);
    };
}

struct PooledStringEntry {
    PooledStringEntry *next;
    PooledStringEntry *noCase;
    char text[1];
};

extern PooledStringEntry ThePooledStringEmptyEntry;

class PooledString {
private:
    void setString(const char *text);
    unsigned getHash(const char *, int) const;
    PooledStringEntry *m_entry;
};

PooledStringEntry *PooledStringPoolBuckets[0x2B7B];
char *PooledStringPoolBuffer;
unsigned PooledStringPoolUsed;

class PooledStringGuard {
public:
    Rva00041004 *lock;
    bool held;
    PooledStringGuard(Rva00041004 &l) : lock(&l), held(false)
    {
        if (!lock->m_flag) EnterCriticalSection(&lock->m_cs);
        held = true;
    }
    ~PooledStringGuard()
    {
        if (!lock->m_flag) LeaveCriticalSection(&lock->m_cs);
    }
};

void PooledString::setString(const char *text)
{
    if (text && *text) {
        unsigned hash = getHash(text, strlen(text));
        static Rva00041004 poolLock(1);
        PooledStringGuard guard(poolLock);
        PooledStringEntry **bucket = &PooledStringPoolBuckets[hash % 0x2B7B];
        PooledStringEntry *entry = *bucket;
        for (; entry; entry = entry->next)
            if (strcmp(text, entry->text) == 0) {
                m_entry = entry;
                return;
            }
        unsigned bytes = (unsigned)(strlen(text) + sizeof(PooledStringEntry));
        if ((unsigned)(PooledStringPoolUsed + bytes) > 0x40000) {
            r1_vwrite(PooledStringPoolBuffer) = _STL::allocator<char>::allocate(0x40000, (const void *)(('s' << 16) | ('t' << 8) | 'r'));
            r1_vwrite(PooledStringPoolUsed) = 0;
        }
        entry = (PooledStringEntry *)(PooledStringPoolBuffer + PooledStringPoolUsed);
        PooledStringPoolUsed = PooledStringPoolUsed + bytes;
        strcpy(entry->text, text);
        PooledStringEntry *alias = *bucket;
        for (; alias; alias = alias->next)
            if (_strcmpi(text, alias->text) == 0) {
                if (alias->noCase) alias = alias->noCase;
                break;
            }
        entry->noCase = alias;
        entry->next = *bucket;
        *bucket = entry;
    }
    else m_entry = &ThePooledStringEmptyEntry;
}
