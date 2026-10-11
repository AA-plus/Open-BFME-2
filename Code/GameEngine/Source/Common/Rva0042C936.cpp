// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0042C936@Rva0042C936@@QAEPAV1@UHolder0042C936@@@Z, retail 0x0042C936, 65 bytes.
// Setter with ownership-transfer holder: takes old at +0, stores released holder ptr,
// calls old virtual slot0 with 0, deletes returned pointer via rowed operator delete,
// returns this. Evidence: single caller 0x0042CA4B, __thiscall via ecx plus ret 4,
// chain sibling of 0x0042C1F9 with identical 65B shape and same // cl.
void __cdecl operator delete(void *p);

struct Rva0042C936Helper
{
	virtual void *virt0(int x);
};

#include <memory>

class Rva0042C993Pointee
{
public:
	virtual ~Rva0042C993Pointee();
};

struct Holder0042C936
{
	Holder0042C936(_STL::auto_ptr<Rva0042C993Pointee> &a) : p(reinterpret_cast<Rva0042C936Helper *>(a.release())) {}
	Rva0042C936Helper *p;
	~Holder0042C936();
	Rva0042C936Helper *release();
};

class Rva0042C936
{
public:
	Rva0042C936Helper *m_ptr;
	Rva0042C936 *rva0042C936(Holder0042C936 h);
};

// ??1Holder0042C936@@QAE@XZ present-unmatched
inline Holder0042C936::~Holder0042C936()
{
	if (p)
		::operator delete(p);
}

// ?release@Holder0042C936@@QAEPAURva0042C936Helper@@XZ present-unmatched
inline Rva0042C936Helper *Holder0042C936::release()
{
	Rva0042C936Helper *t = p;
	p = 0;
	return t;
}

Rva0042C936 *Rva0042C936::rva0042C936(Holder0042C936 h)
{
	Rva0042C936Helper *old = m_ptr;
	m_ptr = h.release();
	void *q = old ? old->virt0(0) : 0;
	::operator delete(q);
	return this;
}

// ?rva0042CA4B@Rva0042CA4B@@QAEXXZ, retail 0x0042CA4B, 146 bytes (EH), reached
// through the pinned 7B thunk 0x0042CADD (mov ecx [ecx]; jmp). Once the
// living world exists and its pinned 0x0004253A check passes, clears the
// byte at +0x94 of the +0x08 object; when the logic's +0xF4 value differs
// from the one cached at +0x10, clears the +0x14 holder (rowed 0x000AD6F4),
// hands it the object the banked factory 0x0042C9BA (pinned) builds for that
// value and the +0x08 object -- the holder's constructor releases the
// factory's auto_ptr straight into the setter's by-value argument, as an
// auto_ptr conversion does -- and caches the value. The emptied auto_ptr's
// destructor (a virtual delete) runs after the call.
class Rva000AD6F4
{
public:
	void clear();
};

// The factory's owner: a pointer released into the returned auto_ptr
// (rowed 0x0042C993 in StrategicInGameUITurnPhaseFactory.cpp), filled
// through the rowed 0x00575674 and cleared by 0x000AD6F4.
class Object;
class Rva00575674 { public: void rva00575674(Object *object); };
class Rva00577838 : public Rva0042C993Pointee { public: Rva00577838(int argument); char m_data[4]; };
class Rva0042C993Holder
{
public:
	Rva0042C993Holder() : ptr(0) {}
	~Rva0042C993Holder() { ((Rva000AD6F4 *)this)->clear(); }
	void reset(Rva0042C993Pointee *p) { ((Rva00575674 *)this)->rva00575674((Object *)p); }
	_STL::auto_ptr<Rva0042C993Pointee> release();
	Rva0042C993Pointee *ptr;
};

// ?Rva0042C9BAFactory@StrategicInGameUI@@YA?AU?$auto_ptr@VRva0042C993Pointee@@@_STL@@HH@Z,
// retail 0x0042C9BA, 145 bytes: kind 2 builds an eight-byte Rva00577838 for
// the argument; the owner's contents return as an auto_ptr. As with
// CreateTurnPhaseBehavior and its Update caller, the file-static noinline
// definition beside its only caller (0x0042CA4B below) is what keeps the
// hidden result in ESI from entry. The genuine STLport transfer type is
// required; a private one-word auto_ptr_ref instead makes cl choose EDI.
namespace StrategicInGameUI
{
	static __declspec(noinline) _STL::auto_ptr<Rva0042C993Pointee> Rva0042C9BAFactory(int kind, int argument)
	{
		Rva0042C993Holder behavior;
		switch (kind)
		{
		case 2:
			behavior.reset(new Rva00577838(argument));
			break;
		}
		return behavior.release();
	}
}

// The bool query at 0x0004253A is the rowed BfmeSelectionState::isSelectionLocked,
// called on TheLivingWorldLogic as in MilesAudioSubtitleConsumer.cpp.
class BfmeSelectionState { public: bool isSelectionLocked() const; };

class LivingWorldLogic
{
public:
	unsigned char m_pad00[0xf4];
	int m_f4;	// +0xF4
};
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva0042CA4BTarget
{
	unsigned char m_pad00[0x94];
	bool m_94;	// +0x94
};

class Rva0042CA4B
{
public:
	void rva0042CA4B();
private:
	unsigned char m_pad00[0x08];
	Rva0042CA4BTarget *m_08;	// +0x08
	unsigned char m_pad0C[0x04];
	int m_10;					// +0x10
	Rva0042C936 m_14;			// +0x14
};

void Rva0042CA4B::rva0042CA4B()
{
	if (TheLivingWorldLogic && reinterpret_cast<BfmeSelectionState *>(TheLivingWorldLogic)->isSelectionLocked())
	{
		m_08->m_94 = false;
		int value = TheLivingWorldLogic->m_f4;
		if (value != m_10)
		{
			reinterpret_cast<Rva000AD6F4 *>(&m_14)->clear();
			m_14.rva0042C936(StrategicInGameUI::Rva0042C9BAFactory(value, (int)m_08));
			m_10 = value;
		}
	}
}

// ?rva0042CADD@Rva0042CADDOwner@@QAEXXZ @0x0042CADD 7B, directly after
// rva0042CA4B: forwards to the object held at +0. Its caller at 0x0023911C
// tail-calls it on a non-null pointer read from +0x1C. Owner and name are
// address-derived.
class Rva0042CADDOwner
{
public:
	void rva0042CADD();
private:
	Rva0042CA4B *m_target00;
};

void Rva0042CADDOwner::rva0042CADD()
{
	m_target00->rva0042CA4B();
}
