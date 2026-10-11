// cl: /O1 /G7 /arch:SSE /MD /EHsc
//
// ?rva005D0034@Rva005D0C31@@UAEXHHH@Z, retail 0x005D0034 (77 bytes, RET 0x0C):
// the only slot of the listener vtable 0x00C75570 that Rva005D0C31 (and its
// identical twin Rva005D078B) install on their +0x10 base, the base the
// constructor appends to TheLivingWorldLogic's +0x6C list. When the event's
// second word is TheLivingWorldLogic's +0x98 value and its third word is the
// +0x14 value of the object the base keeps at +0x04, that object's +0x1C
// holder is given a new 8-byte callback on it (vtable 0x00C752A8; holder
// replacement rowed 0x00575674). The event word names are not known.
class Rva005D0034Target;

// The callback's owner pointer lives in a plain base, so it is stored before
// the callback's vtable, as in Rva005D0C87Ctor.cpp.
struct Rva005D0034CallbackBase
{
	Rva005D0034CallbackBase(Rva005D0034Target *owner) : m_owner(owner) {}
	Rva005D0034Target *m_owner;
};

class Rva005D0034Callback : public Rva005D0034CallbackBase
{
public:
	Rva005D0034Callback(Rva005D0034Target *owner) : Rva005D0034CallbackBase(owner) {}
	virtual void c0();
};

class Rva000AD6F4
{
public:
	void reset(void *callback);
};

class Rva005D0034Target
{
public:
	unsigned char m_pad00[0x14];
	int m_14;				// +0x14
	unsigned char m_pad18[0x1C - 0x18];
	Rva000AD6F4 m_holder1C;			// +0x1C
};

struct Rva005D0034LogicView
{
	unsigned char m_pad00[0x98];
	int m_98;				// +0x98
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva005CF8A1
{
public:
	Rva005CF8A1(void *p);
	virtual ~Rva005CF8A1();
protected:
	Rva005D0034Target *m_target;		// +0x04
	char m_pad08[0x10 - 8];
};

class Rva005D0C31Second
{
public:
	virtual void rva005D0034(int a, int b, int c) = 0;
};

class Rva005D0C31 : public Rva005CF8A1, public Rva005D0C31Second
{
public:
	Rva005D0C31(void *p);
	virtual ~Rva005D0C31();
	virtual void rva005D0034(int a, int b, int c);
};

void Rva005D0C31::rva005D0034(int a, int b, int c)
{
	if (b == ((Rva005D0034LogicView *)TheLivingWorldLogic)->m_98 && c == m_target->m_14)
		m_target->m_holder1C.reset(new Rva005D0034Callback(m_target));
}
