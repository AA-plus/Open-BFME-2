// cl: /MD
// ??0Rva005FAB16@@QAE@ABUPayload005FAB16@@@Z, RVA 0x005FAB16, 30 bytes.
// Ctor storing vtable 0x00879EB4 at +0, zeroing +4, copying 16 bytes from
// arg+0 to this+8 via 4x movsd. Evidence: caller 0x005FAC76; vtable DIR32
// filled by gate; neighbours use /O1 /MD.
inline void *operator new(unsigned int, void *p) { return p; }
#include "BattlePromptCallbackPayloadView.h"
struct Rva005FAB16 {
    virtual void _vf() {}
    int m4;
    Payload005FAB16 m8;
    Rva005FAB16(const Payload005FAB16 &o);
};
Rva005FAB16::Rva005FAB16(const Payload005FAB16 &o) : m4(0), m8(o) {}

// Two more constructors of this shape, each installing its own vtable (the only
// differing operand): 0x005F4C52 (VA 0xc794d4), 0x005F4C70 (VA 0xc794dc). The virtual is declared inline and
// empty so the vtable the compiler emits resolves in this unit. Owners keep
// their addresses.

struct Rva005F4C52 {
    virtual void _vf() {}
    int m4;
    Payload005FAB16 m8;
    Rva005F4C52(const Payload005FAB16 &o);
};
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva005F4C52::Rva005F4C52(const Payload005FAB16 &o) : m4(0), m8(o) {}

// ?bfmeAnchorRva005F4C52Ctor absent-from-retail
void *bfmeAnchorRva005F4C52Ctor(void *where, const Payload005FAB16 &o)
{
	return ::new (where) Rva005F4C52(o);
}

struct Rva005F4C70 {
    virtual void _vf() {}
    int m4;
    Payload005FAB16 m8;
    Rva005F4C70(const Payload005FAB16 &o);
};
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva005F4C70::Rva005F4C70(const Payload005FAB16 &o) : m4(0), m8(o) {}

// ?bfmeAnchorRva005F4C70Ctor absent-from-retail
void *bfmeAnchorRva005F4C70Ctor(void *where, const Payload005FAB16 &o)
{
	return ::new (where) Rva005F4C70(o);
}
