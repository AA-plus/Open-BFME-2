// cl: /EHsc /MD
// ??0Rva000E6350@@QAE@XZ, retail 0x000E6350, 55 bytes.
// Ctor registering "Vegetation" via rowed Rva00153565Register; vtable at +0.
// Evidence: disassembly stores 0x007CEA04 then calls Register("Vegetation", this);
// Namespace base shares the primary vptr and owns EH state0.
void __cdecl Rva00153565Register(const char *name, void *obj);

// Target base tableBC6F24 has scalar deleting dtor7DFF2 then purecall.
// Existing binder and namespace units supply the class name and slot1 ABI;
// native cleanup763473 calls complete7B base dtorE14BD with receiver0.
class FXShaderParameterBinder;
typedef const char *D3DXHANDLE;
class FXShaderParameterSourceNamespace {
public:
    virtual ~FXShaderParameterSourceNamespace() {}
    virtual void ResolveBindings(const char *, D3DXHANDLE, FXShaderParameterBinder *) = 0;
};

class Rva000E6350 : public FXShaderParameterSourceNamespace {
public:
    virtual ~Rva000E6350();
    Rva000E6350();
    virtual void ResolveBindings(const char *, D3DXHANDLE, FXShaderParameterBinder *);
};

Rva000E6350::Rva000E6350()
{
    Rva00153565Register("Vegetation", this);
}
