// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native 5CE172..5CE1EB: primary +0, vbptr +4, base payload +8,
// derived context +C, shared reference-counted virtual base +10.
// The nonvirtual Rva005CC5E5 parent is independently proved by the
// base constructor146 and destructor84; adding it preserves this full121B.
// The third explicit argument supplies the +8 object whose +20 field
// receives this instance. The base call receives all three arguments.
class Rva0007DF07
{
public:
	Rva0007DF07() : count(0) {}
	virtual ~Rva0007DF07() {}
private:
	unsigned int count;
	friend struct Rva005CE172Handle;
	void addRef() { ++count; }
};

struct Rva005CE172Link
{
	char unknown00[0x20];
	void *owner;
};

struct Rva005CE172Context
{
	char unknown00[8];
	Rva005CE172Link *link;
};

class Rva005CC5E5 : public virtual Rva0007DF07
{
public:
 Rva005CC5E5() throw();
 virtual void slot0();
 virtual ~Rva005CC5E5();
};

class Rva005E87E0 : public Rva005CC5E5
{
public:
	Rva005E87E0(void *, void *, Rva005CE172Context *);
	virtual ~Rva005E87E0();
private:
	void *payload;
};

class Rva005CE172 : public Rva005E87E0
{
public:
	Rva005CE172(void *, void *, Rva005CE172Context *);
	virtual ~Rva005CE172();
private:
	Rva005CE172Link *context;
};

Rva005CE172::Rva005CE172(void *a, void *b, Rva005CE172Context *c)
	: Rva005E87E0(a, b, c), context(c->link)
{
	context->owner = this;
}

// ?rva005CE349@Rva005CE349@@QAE?AURva005CE172Handle@@PAX0@Z, retail 0x005CE349 (99B):
// a factory slot whose receiver keeps the constructor's context at +8. It
// allocates 0x18 bytes, constructs this class (most-derived flag 1) and
// returns a counted handle by hidden pointer (RET 0C); the AddRef reaches the
// shared Rva0007DF07 count through the vbptr at +4. Receiver and handle names
// are address-derived storage views.
struct Rva005CE172Handle
{
	Rva005CC5E5 *m_p;
	__forceinline Rva005CE172Handle(Rva005CC5E5 *p) : m_p(p)
	{
		if (p)
			p->addRef();
	}
	~Rva005CE172Handle();
};

struct Rva005CE349
{
	char m_prefix[8];
	Rva005CE172Context m_context;
	Rva005CE172Handle rva005CE349(void *a, void *b);
};

Rva005CE172Handle Rva005CE349::rva005CE349(void *a, void *b)
{
	return Rva005CE172Handle(new Rva005CE172(a, b, &m_context));
}
