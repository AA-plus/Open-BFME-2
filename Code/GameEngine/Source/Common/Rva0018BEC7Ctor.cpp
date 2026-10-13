// cl: /EHsc /MD
// ??0Rva0018BEC7@@QAE@XZ, retail 0x0018BEC7, 66 bytes.
// Ctor registering "WW3D" via rowed Rva00153565Register; vtable at +0 plus member vtable at +4.
// Evidence: disassembly stores 0x007D5BE4/0x007D5BD4 then calls Register("WW3D", this);
// caller0x0017414B; namespace base at0 arms state0, namespace member at4 state1.
void __cdecl Rva00153565Register(const char *name, void *obj);

// Both native cleanup states reach the complete7B namespace-base dtorE14BD.
// The primary namespace interface comes from the verified binder/namespace
// units; member ctor18BE7E and tableBD5BD4 establish its primary vptr at4.
// Original leaf/member application names and unused leaf slots remain unknown.
class FXShaderParameterBinder;
typedef const char *D3DXHANDLE;
class FXShaderParameterSourceNamespace {
public:
    virtual ~FXShaderParameterSourceNamespace() {}
    virtual void ResolveBindings(const char *, D3DXHANDLE, FXShaderParameterBinder *) = 0;
};

class Rva0018BEC7_Member : public FXShaderParameterSourceNamespace {
public:
    Rva0018BEC7_Member();
    virtual ~Rva0018BEC7_Member() {}
    virtual void ResolveBindings(const char *, D3DXHANDLE, FXShaderParameterBinder *);
};
// ??0Rva0018BEC7_Member@@QAE@XZ @0x0018BE7E 9B: the default constructor, storing the
// class's own vtable (VA 0x00BD5BD4) and returning this.
Rva0018BEC7_Member::Rva0018BEC7_Member()
{
}

class Rva0018BEC7 : public FXShaderParameterSourceNamespace {
public:
    virtual ~Rva0018BEC7();
    Rva0018BEC7();
    virtual void ResolveBindings(const char *, D3DXHANDLE, FXShaderParameterBinder *);
    Rva0018BEC7_Member m_member;
};

Rva0018BEC7::Rva0018BEC7()
{
    Rva00153565Register("WW3D", this);
}
