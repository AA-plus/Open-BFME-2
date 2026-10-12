// cl: /DNDEBUG /MD /EHsc
// ?rva005C9886@Rva005C9886@@QBEPAVRva005C96EB@@PAX@Z,
// retail 0x005C9886..0x005C98C0, 58 bytes. Dedicated TU.
// Native allocates 0x26C and passes its sole opaque argument to the rowed
// 0x005C96EB constructor. The receiver is unused. The previous BFME1
// LocomotorStore allocation lead does not establish identity: the callee's
// Apt screen base and vtable C74B70 refute the Locomotor name (the actual
// Locomotor constructor is 1E449A, B0 bytes, table BDE888). Names are now
// address-derived; the original factory, owner and argument type are unknown.
// /O1 selects the native outlined EH prologue; the allocation cleanup is
// independently rowed at 0x007A0F25 from this parent's unwind state.

class Rva005C96EB
{
public:
    Rva005C96EB(void *ctx);
private:
    char m_body[0x26C];
};

class Rva005C9886
{
public:
    Rva005C96EB *rva005C9886(void *ctx) const;
};

inline Rva005C96EB *Rva005C9886::rva005C9886(void *ctx) const
{
    return new Rva005C96EB(ctx);
}

// A source-only address anchor emits the inline method's COMDAT, as before.
Rva005C96EB *(Rva005C9886::*_bfmeInlineAnchor_Rva005C9886_0)(void *) const = &Rva005C9886::rva005C9886;
