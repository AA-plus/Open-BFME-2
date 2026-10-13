// cl: /O1 /GX /DNDEBUG /MD
//
// ??0Rva0010F058@@QAE@H@Z at 0x0010F058 (108B).
// Ctor storing vtable 0x00BCFAAC with event member at +0x14 via rowed Rva0040F9D ctor
// plus InterlockedIncrement id at +0x20 and set. The +0x04 zero belongs to a polymorphic
// BASE subobject (vtable 0x00BC5128, folded: only the derived 0x00BCFAAC store survives).
// The four zero-initialised fields (+0x04, +0x08, +0x10, +0x24) are volatile: retail stores
// them ahead of the EH this-save / the event-ctor argument pushes, which only the volatile
// ordering constraint reproduces (3 volatile fields: nd 3, these four: exact).

class Rva0040F9D
{
public:
	virtual ~Rva0040F9D();
	Rva0040F9D(int a1, int a2, char const *a3, void *a4);
	bool set();
private:
	void *m_handle;
};

long Rva0010EFB1Inc();

class Rva0010F058Base
{
public:
	virtual ~Rva0010F058Base();
	Rva0010F058Base() : m_unused04(0) {}
	int volatile m_unused04;
};

class Rva0010F058 : public Rva0010F058Base
{
public:
	virtual ~Rva0010F058();
	Rva0010F058(int x);
private:
	void * volatile m_stream08;
	int m_arg0C;
	int volatile m_unused10;
	Rva0040F9D m_event14;
	int m_flag1C;
	long m_id20;
	int volatile m_unused24;
};

Rva0010F058::Rva0010F058(int x) : m_stream08(0), m_arg0C(x), m_unused10(0), m_event14(1, 0, 0, 0), m_flag1C(1), m_id20(Rva0010EFB1Inc()), m_unused24(0)
{
	m_event14.set();
}
