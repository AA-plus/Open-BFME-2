// ?rva005421AA@Rva00541F1F@@QBE?AVRva0053FC99@@XZ
// partial score=0.94 date=2026-10-13
// ?rva005421AA@Rva00541F1F@@QBE?AVRva0053FC99@@XZ
// partial score=0.94 date=2026-10-13
// cl: /EHsc /DNDEBUG /MD
// In-TU rebuild in the copy-ctor TU: full clone shape decoded (nothrow new
// 0x64 + rowed copy ctor, rowed 53FC81 attach, rowed 53FC99 copyout into the
// hidden result, inline holder destroy via rowed 53FA32). 116/123: missing
// the push-push-and-zero frame homes and the 1-0-2 EH state numbering (ours
// 0-1-2 with separate copied home); nothrow/throwing new and nested-scope
// variants do not renumber. Twin 0x540A88 shares the wall (0x44 + rowed
// 540845). t=40 model=muse-spark
class Rva0053F8E5DwordCounter;
class Rva0053FA0A
{
public:
	void rva0053FA32();
};

class Rva0053FC81
{
public:
	Rva0053FC81 *rva0053FC81(Rva0053F8E5DwordCounter *p);
	~Rva0053FC81()
	{
		if (m_ptr)
			((Rva0053FA0A *)m_ptr)->rva0053FA32();
	}

private:
	Rva0053F8E5DwordCounter *m_ptr;
};

struct Rva0053FC99Src
{
	Rva0053F8E5DwordCounter *m_ptr;
};

class Rva0053FC99
{
public:
	Rva0053FC99 *rva0053FC99(Rva0053FC99Src *s);

private:
	Rva0053F8E5DwordCounter *m_ptr;
};

void *operator new(unsigned int size);

class Rva00541F1F : public Rva0053FADE
{
public:
	Rva00541F1F(const Rva00541F1F &other);
	virtual ~Rva00541F1F();
	Rva0053FC99 rva005421AA() const;

private:
	Rva00541913 m_24;
	Rva00541A6E m_44;
};

Rva00541F1F::Rva00541F1F(const Rva00541F1F &other) :
	Rva0053FADE(other),
	m_24(other.m_24),
	m_44(other.m_44)
{
}
// ?rva005421AA@Rva00541F1F@@QBE?AVRva0053FC99@@XZ @0x005421AA 123B: clone
// slot. Copies the animation into a fresh 0x64-byte object and hands it
// back in a reference-counted pointer: the raw pointer is attached by the
// rowed 0x0053FC81 setter and copied out by the rowed 0x0053FC99 setter
// (whose single-pointer source layout matches the holder, so the address
// reinterpretation is layout-sound); the holder's inline destructor
// releases through the rowed 0x0053FA32.
Rva0053FC99 Rva00541F1F::rva005421AA() const
{
	Rva00541F1F *copied = new Rva00541F1F(*this);
	Rva0053FC81 holder;
	holder.rva0053FC81((Rva0053F8E5DwordCounter *)copied);
	Rva0053FC99 result;
	result.rva0053FC99((Rva0053FC99Src *)&holder);
	return result;
}
