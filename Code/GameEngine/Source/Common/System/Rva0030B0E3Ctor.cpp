// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??0Rva0030B0E3@@QAE@XZ, retail 0x0030B0E3, 54 bytes.
// Ctor stores vtable 0x00808830 then zeroes +0xC/+0x10 and calls 0x0030B055 method.
// Evidence: caller chain from 0x0030B055 row; vtable store at [this].
// Native cleanup77A02F keeps this at offset0 and calls the full7B
// polymorphic base destructor7461F. The existing deleting-dtor unit
// independently proves this same base and slot0 relationship. Only its
// primary vptr is modelled here; other base fields and unused slots remain
// unspecified. The old empty nonpolymorphic base incorrectly moved to +4.
class Rva00074626
{
public:
	virtual ~Rva00074626();
};

class Rva0030B055
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void v3(int a, int b);
	virtual void s4();
	virtual void s5();
	virtual int v6();
	virtual void s7();
	virtual void v8(int a);
	virtual void v9(int a);
	void rva0030B055();
};

class Rva0030B0E3 : public Rva00074626
{
public:
	virtual ~Rva0030B0E3();
	virtual void s1();
	virtual void s2();
	virtual void v3(int a, int b);
	virtual void s4();
	virtual void s5();
	virtual int v6();
	virtual void s7();
	virtual void v8(int a);
	virtual void v9(int a);
	Rva0030B0E3();

private:
	int m_pad04;
	int m_pad08;
	int m_c;
	int m_d;
};

Rva0030B0E3::Rva0030B0E3()
	: m_c(0)
	, m_d(0)
{
	((Rva0030B055 *)this)->rva0030B055();
}
