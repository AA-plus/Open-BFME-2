// ??0Rva003A59C3@@QAE@II@Z
// partial score=0.96 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0Rva003A59C3@@QAE@I@Z, retail 0x003A59C3, 127 bytes.
//
// Evidence: the rowed base ctor ??0Rva0055EFE1@@QAE@I@Z (0x0055EFE1) takes the
// single unsigned argument, then three vtable stores at +0/+8/+0xC and a
// float at +0x10 filled with the rowed GetGameClientRandomValueReal
// 0x00234111 (1.3f, 0.7f, file, 404). The file literal is the retail path at
// VA 0x00B1B4F8, fxpswindmodule.cpp, which is this class's source file; the
// first stored vtable 0x00C1B5E0 and the revised ret 8 extent (the previous
// 105-byte claim had the wrong start) complete the identity. Class and
// method names remain address-derived.

float GetGameClientRandomValueReal(float lo, float hi, char *file, int line);

class Rva0055EFE1
{
public:
	Rva0055EFE1(unsigned int arg);
	virtual void s0();
	virtual void s1();
	virtual ~Rva0055EFE1();

private:
	int m_4;
};

class Rva003A59C3B2
{
public:
	virtual void s0();
	virtual void s1();
};

class Rva003A59C3B3
{
public:
	virtual void s0();
	virtual void s1();
};

class Rva003A59C3 : public Rva0055EFE1, public Rva003A59C3B2, public Rva003A59C3B3
{
public:
	Rva003A59C3(unsigned int arg, unsigned int arg2);
	virtual void s0();
	virtual void s1();

private:
	float m_10;
};

Rva003A59C3::Rva003A59C3(unsigned int arg, unsigned int arg2)
	: Rva0055EFE1(arg), m_10(0.0f)
{
	(void)arg2;
	m_10 = GetGameClientRandomValueReal(
		1.3f, 0.7f,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpswindmodule.cpp",
		404);
}
