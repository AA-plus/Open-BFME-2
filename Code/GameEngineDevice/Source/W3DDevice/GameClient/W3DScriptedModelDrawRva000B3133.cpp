// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva000B3133@Rva000B3133Module@@UAEPAVRva000B3133Part@@XZ, retail 0x000B3133 (24 bytes):
// the fourth slot of W3DScriptedModelDraw's second-base (+0x0C) interface tables (0x007CBBA0,
// 0x007CBF20, 0x007CC5B0, beside the rowed buildPlayingAnimationStringInfo and
// getAnimationFrameCount). The override reaches the complete object (this - 0x0C), asks its
// primary slot +0xC4 for an object and returns that object's +0x9C base, or null. The
// interface method and its types are not named in the target, so the views are address-named.
class Rva000B3133Head { public: virtual void h00(); char m_pad[0x9c - 4]; };
class Rva000B3133Part { public: virtual void p00(); };
class Rva000B3133Thing : public Rva000B3133Head, public Rva000B3133Part {};

class Rva000B3133Primary
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual void s44();
	virtual void s45();
	virtual void s46();
	virtual void s47();
	virtual void s48();
	virtual Rva000B3133Thing *slotC4();
private:
	int m_04;
	int m_08;
};

class Rva000B3133Interface
{
public:
	virtual Rva000B3133Part *rva000B3133();
};

class Rva000B3133Module : public Rva000B3133Primary, public Rva000B3133Interface
{
public:
	virtual Rva000B3133Part *rva000B3133();
};

Rva000B3133Part *Rva000B3133Module::rva000B3133()
{
	Rva000B3133Thing *thing = slotC4();
	if (thing)
		return thing;
	return 0;
}
