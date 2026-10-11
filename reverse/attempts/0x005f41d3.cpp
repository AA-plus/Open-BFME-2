// ??0Rva005F41D3@@QAE@PAX00@Z
// partial score=0.95 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /MD /EHsc
class Rva005F4096 {void *p;};
class Rva005F4179Base {public:virtual ~Rva005F4179Base();protected:int count;};
class Rva005F4179:public Rva005F4179Base {public:Rva005F4179(void *clip);virtual ~Rva005F4179(); virtual void DoUpdate();private:Rva005F4096 leaf;};
struct IconHolder {void *p; IconHolder():p(0){} };
class Rva005F41D3:public virtual Rva005F4179 {
public:Rva005F41D3(void *owner,void *clip,void *entry);virtual ~Rva005F41D3(); virtual void DoUpdate();
private:void *owner;void *entry;IconHolder ref;
};
Rva005F41D3::Rva005F41D3(void *o,void *c,void *e):Rva005F4179(c),owner(o),entry(e),ref(){}
