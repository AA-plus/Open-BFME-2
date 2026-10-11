// cl: /O1 /DNDEBUG /MD /arch:SSE /G7
// ?rva005F422C@Rva005F422C@@QAEXXZ, RVA 0x005F422C, 40 bytes.
// Packet pin supplies the address-derived name; retail installs vtable data 0x00879468 and releases the pointer at this-8.
extern const void *const g_00C79468[];
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva005F422C
{
public:
	void rva005F422C();
};

void Rva005F422C::rva005F422C()
{
	unsigned int subobject = *(unsigned int *)((char *)this - 0x14);
	unsigned int table = *(unsigned int *)(subobject + 4);
	*(unsigned int *)(table + (unsigned int)this - 0x14) = (unsigned int)g_00C79468;
	subobject = *(unsigned int *)((char *)this - 0x14);
	table = *(unsigned int *)(subobject + 4);
	*(unsigned int *)(table + (unsigned int)this - 0x18) = table - 0x14;
	TargetRef00217D4C *p = *(TargetRef00217D4C **)((char *)this - 8);
	if (p)
		ReleaseTreeHintRef00217D4C(p);
}

// Native 005F445D..005F4488 is the complete 43B RET4 deleting wrapper.
// Ghidra groups it with the preceding eight-byte CreateMovieClip thunk at
// 005F4455. WB01626880 independently shows this wrapper's three calls:
// the icon destructor above, the shared virtual-base destructor005F4179,
// then operator delete when flags bit0 is set. Its receiver is the virtual
// base at icon+14; return and deallocation use the complete icon pointer.
// Vtable C79468 slot0 reaches this body through vtordisp thunk005F4224.
// The original wrapper/type spelling remains unknown; this view declares
// only the verified secondary-receiver ABI and emits no synthetic vtable.
class Rva005F4179 { public: virtual ~Rva005F4179(); };
void __cdecl operator delete(void *);
class Rva005F445D { public: void *destroy(unsigned int flags); };

void *Rva005F445D::destroy(unsigned int flags)
{
    char *object = (char *)this - 0x14;
    Rva005F4179 *base = (Rva005F4179 *)(object + 0x14);
    ((Rva005F422C *)base)->rva005F422C();
    base->Rva005F4179::~Rva005F4179();
    if (flags & 1)
        operator delete(object);
    return object;
}
