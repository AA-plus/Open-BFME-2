// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva00575125@@UAE@XZ retail 0x00574C6E 83B
// MI dtor: base Rva005746AF at +0 plus second base at +0x10 with member at +0x14.
// Evidence: vtable stores 0x0086E4C4 then 0x0086E4C0 then 0x0086E360; rowed erase 0x002B7250 with this=second arg+4 and arg=sub at +0x10; pinned base dtor 0x005746D2; caller 0x00574E6D deleting dtor; neighbours share /O1. Honest Rva name.
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
};
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *p);
};
class Rva005746AF
{
public:
	Rva005746AF(int arg);
	virtual ~Rva005746AF();
private:
	int m_04;
	unsigned long m_08;
	TreeHintRef00217D4C m_0C;
};
class Rva00575125Second
{
public:
	virtual ~Rva00575125Second();
};
// ??1Rva00575125Second@@UAE@XZ present-unmatched
inline Rva00575125Second::~Rva00575125Second() {}
class Rva00575125 : public Rva005746AF, public Rva00575125Second
{
public:
	virtual ~Rva00575125();
private:
	void *m_14;
};
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva00575125::~Rva00575125()
{
	((Rva002B7250 *)((char *)m_14 + 4))->rva002B7250((CreateAHeroData *)((char *)this + 0x10));
}

// ?bfmeAnchorRva00575125Dtor absent-from-retail
void bfmeAnchorRva00575125Dtor(Rva00575125 *p)
{
	p->Rva00575125::~Rva00575125();
}

