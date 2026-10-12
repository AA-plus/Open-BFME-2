// ?rva00664370@Rva00664370@@UAEXHPAURva00664370Probe@@@Z
// partial score=0.6 date=2026-10-12
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// ?rva00664370@Rva00664370@@UAEXHPAURva00664370Probe@@@Z, retail
// 0x00664370..0x00664417 (167B): a Ghidra-unlisted slot of table 0x00CE3008
// in the online-services cluster (beside the rowed 0x00662B60 / 0x00662A80).
// For a probe in state 4: a non-zero result is reported through the
// diagnostic reporter's slot 2 ("probe err %d\n", the retail literal), the
// probe's slot 1 / slot 2 values go to the complete object's slot 23, the
// probe resets to state 0, is handed with the result to the +0x14 listener's
// slot 11 and passed to the complete object's rowed 0x00663E50; a zero result
// moves it to state 5 and tells the listener. The method sits in a +0x08
// interface; fields are named by offset.

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void __cdecl log(int level, const char *format, ...);
};

Rva007EB810Diag *Rva007EB810Get(void);						// 0x006587A0

struct BfmeThingVFD;
void __stdcall bfmeGoVFD(BfmeThingVFD *probe);				// 0x00663E50

struct Rva00664370Probe
{
	virtual void v0();
	virtual int *first(int *out);
	virtual int *second(int *out);
	int m_04;
	int m_state;											// +0x08
};

class Rva00664370Listener
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10();
	virtual void probeDone(Rva00664370Probe *probe, int result);
};

class Rva00664370Base0
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22();
	virtual void s23(int a, int b);
	int m_04;
	// 0x00663E50 takes the complete object in ECX (it is spelled in the ledger
	// as a __stdcall free body); the call goes through that body.
	void finish(Rva00664370Probe *probe)
	{
		union { void (__stdcall *entry)(BfmeThingVFD *); void (Rva00664370Base0::*method)(Rva00664370Probe *); } call;
		call.entry = bfmeGoVFD;
		(this->*call.method)(probe);
	}
};

class Rva00664370Iface
{
public:
	virtual void rva00664370(int result, Rva00664370Probe *probe);
	char m_pad0C[0x14 - 0x0C];
	Rva00664370Listener *m_listener;						// +0x14 (from the interface)
};

class Rva00664370 : public Rva00664370Base0, public Rva00664370Iface
{
public:
	virtual void rva00664370(int result, Rva00664370Probe *probe);
};

void Rva00664370::rva00664370(int result, Rva00664370Probe *probe)
{
	if (probe && probe->m_state == 4)
	{
		if (result)
		{
			Rva007EB810Get()->log(0, "probe err %d\n", result);
			int a, b;
			int *pa = probe->first(&a);
			int *pb = probe->second(&b);
			s23(*pb, *pa);
			probe->m_state = 0;
			m_listener->probeDone(probe, result);
			finish(probe);
		}
		else
		{
			probe->m_state = 5;
			m_listener->probeDone(probe, 0);
		}
	}
}
