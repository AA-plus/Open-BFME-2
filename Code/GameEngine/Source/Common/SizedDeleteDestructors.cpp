// cl: /O2 /MD /EHsc
// The 33-byte deleting helper at 6CD6C0 was first transferred from the
// Open-BFME-1 SizedDeleteDestructors.cpp near sibling at 891D40, adapting
// its allocation size to 28B and its sized-free callback to E17730.
// Native initializer 6CC380 and the 70-byte constructor at 6CBC60 establish
// seven words of pool storage, without an inserted vptr. Shutdown 6CDF60
// calls the complete destructor at 6CC4C0; that five-byte wrapper tails to
// the rowed pool walk at 6DAFA0. The previous virtual view inserted a vptr
// store and an unowned base-destructor call into this wrapper.
// The explicit C++ deleting helper preserves native ECX, flags on the stack
// and RET4 without asserting the compiler-generated virtual class identity.
// Original class and helper names remain unresolved.
extern void (__cdecl *g_bfmeAptFreeSizeAtE17730)(void *,unsigned);
class Rva006CD6C0SizedDeleting {
public:
 __declspec(noinline) ~Rva006CD6C0SizedDeleting();
 static void operator delete(void *storage,unsigned size) {g_bfmeAptFreeSizeAtE17730(storage,size);}
 unsigned m_fields[7];
};

Rva006CD6C0SizedDeleting *__fastcall Rva006CD6C0Delete(Rva006CD6C0SizedDeleting *p,int,unsigned flags) {
 p->~Rva006CD6C0SizedDeleting();
 if(flags&1)Rva006CD6C0SizedDeleting::operator delete(p,sizeof(Rva006CD6C0SizedDeleting));
 return p;
}
