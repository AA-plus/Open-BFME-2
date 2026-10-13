// ?rva005E4202@Rva005E4202@@QAEXXZ
// partial score=0.95 date=2026-10-13
// Exact-main-body formulation for the map<int,SBServer> interior cleanups
// 0x005E4202 (66B) and twin 0x005E426F (66B). Both compile to retail-exact
// main bodies under the owner TU's flags; the commit gate refuses only the
// 3-byte .text$x unwind funclet (ours `lea ecx,[ebp-0x10]; jmp`, retail
// `sub ecx,0x10; jmp`): retail destroys a base at this-0x10 from incoming
// ecx with no stack access, so the parent must be a real base subobject,
// not a stack local (any local forces the lea). Retail FuncInfo tryCount=0
// (pure unwind, no try/catch). Needs the true class hierarchy; the vtable
// thunk 0x005E3C67 -> deleting wrapper 0x005E41D7 calling 0x005E4202 smells
// of a secondary-entry/base-variant dtor. Twin additionally needs rowed
// 0x005F4891 (91B virtual-base dtor, callees rowed) for its second call.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
class Rva005E3A76 { public: void rva005E3A76(); };
class Rva005F422C { public: void rva005F422C(); };
class Rva005F4891 { public: void rva005F4891(); };
struct PeerParent1 { char *receiver; __forceinline ~PeerParent1() { reinterpret_cast<Rva005F422C*>(receiver - 0x10)->rva005F422C(); } };
struct PeerParent2 { char *receiver; __forceinline ~PeerParent2() { reinterpret_cast<Rva005F4891*>(receiver - 0x10)->rva005F4891(); } };
class Rva005E4202 { public: void rva005E4202(); };
class Rva005E426F { public: void rva005E426F(); };
void Rva005E4202::rva005E4202()
{
    PeerParent1 parent = { (char*)this };
    unsigned view = (unsigned)((char*)this - 0x24) ? -1 : 0;
    view &= (unsigned)((char*)this - 0x14);
    view += 0x14;
    reinterpret_cast<Rva005E3A76*>(view)->rva005E3A76();
}
void Rva005E426F::rva005E426F()
{
    PeerParent2 parent = { (char*)this };
    unsigned view = (unsigned)((char*)this - 0x30) ? -1 : 0;
    view &= (unsigned)((char*)this - 0x14);
    view += 0x14;
    reinterpret_cast<Rva005E3A76*>(view)->rva005E3A76();
}
