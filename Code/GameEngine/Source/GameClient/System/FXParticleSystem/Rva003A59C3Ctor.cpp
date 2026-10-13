// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0Rva003A59C3@@QAE@II@Z, retail 0x003A59C3, 127 bytes, EH thiscall RET 8.
// Identified by the rowed module factory 0x003AD03B (Rva003AC9AFCreate.cpp),
// the rowed base ctor 0x0055EFE1 and the copy ctor 0x003AE03D: the complete
// class has vfptrs at +0 and +8 (the Rva0055EFE1 base object, 12 bytes) plus
// a second base at +0x0C whose transient vtable is 0x00C1B568, i.e. the rowed
// Rva003AE07D (default ctor 0x003A5773, Real at +4). The class then installs
// 0x00C1B5E0 (+0), 0x00C1C780 (+8) and 0x00C1B5D0 (+0x0C). The second ctor
// argument is unread. Class and method names remain address-derived.
//
// The Rva0055EFE1 base is modelled as an MI pair so the +8 secondary vfptr
// exists in this TU; its out-of-line ctor at 0x0055EFE1 owns the construction
// stores. Both destructible bases arm retail's EH state stores: state 0 is
// zeroed before the +0x0C base's vptr store, and state 1 is set before the
// random-value call whose result is assigned to the base's Real.

float GetGameClientRandomValueReal(float lo, float hi, char *file, int line);

class Rva003A59C3B0A
{
public:
	virtual ~Rva003A59C3B0A() {}
	virtual void s0() {}
	virtual void s1() {}

private:
	int m_4;
};

class Rva003A59C3B0B
{
public:
	virtual void s0() {}
	virtual void s1() {}
};

class Rva0055EFE1 : public Rva003A59C3B0A, public Rva003A59C3B0B
{
public:
	Rva0055EFE1(unsigned int arg);
};

// Same shape as the rowed Rva003AE07D (V3PolyCopyCtors.cpp): vtable
// 0x00C1B568 and a Real at +4 zeroed by the default ctor.
class Rva003A59C3B3
{
public:
	Rva003A59C3B3() : m_real04(0.0f) {}
	virtual ~Rva003A59C3B3();
	virtual void s0() {}
	virtual void s1() {}

	float m_real04;
};

class Rva003A59C3 : public Rva0055EFE1, public Rva003A59C3B3
{
public:
	Rva003A59C3(unsigned int arg, unsigned int arg2);
	virtual void s0() {}
	virtual void s1() {}
};

Rva003A59C3::Rva003A59C3(unsigned int arg, unsigned int arg2)
	: Rva0055EFE1(arg)
{
	(void)arg2;
	m_real04 = GetGameClientRandomValueReal(
		0.7f, 1.3f,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpswindmodule.cpp",
		404);
}
