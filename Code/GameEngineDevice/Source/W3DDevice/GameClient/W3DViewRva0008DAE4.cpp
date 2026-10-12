// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva0008DAE4@W3DView@@UAEXXZ, retail 0x0008DAE4..0x0008DB18 (52 bytes, ends
// in a tail jump through vtable slot 0x17C). A W3DView reset step reached
// through the vtable (no direct callers): zoom back to 1.0 (+0x70), pitch
// to the 50 degree default (+0x6C = 0.87266463 rad), clear the flag byte at
// +0x243A, rebuild the camera transform (rowed 0x0008BE6B) and finish in the
// next virtual step. The ZH counterpart is W3DView::setAngleAndPitchToDefault
// (View::setAngleAndPitchToDefault then setCameraTransform); BFME2's field
// meanings are only partly established, so the name stays address-derived.

typedef float Real;

// The rowed StringBase<char>::set 0x000366F0 (BFME 2's AsciiString copy).
template <class T> class StringBase
{
public:
	void set(const StringBase &other);
private:
	T *m_data;
};

class W3DView
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
	virtual void s49();
	virtual void s50();
	virtual void s51();
	virtual void s52();
	virtual void s53();
	virtual void s54();
	virtual void s55();
	virtual void s56();
	virtual void s57();
	virtual void s58();
	virtual void s59();
	virtual void s60();
	virtual void s61();
	virtual void s62();
	virtual void s63();
	virtual void s64();
	virtual void s65();
	virtual void s66();
	virtual void s67();
	virtual void s68();
	virtual void s69();
	virtual void s70();
	virtual void s71();
	virtual void s72();
	virtual void s73();
	virtual void s74();
	virtual void s75();
	virtual void s76();
	virtual void s77();
	virtual void s78();
	virtual void s79();
	virtual void s80();
	virtual void s81();
	virtual void s82();
	virtual void s83();
	virtual void s84();
	virtual void s85();
	virtual void s86();
	virtual void s87();
	virtual void s88();
	virtual void s89();
	virtual void s90();
	virtual void s91();
	virtual void s92();
	virtual void s93();
	virtual void s94();
	virtual void step95();
	virtual void rva0008DAE4();
	virtual void rva000875A2(const StringBase<char> &first, const StringBase<char> &second);
	virtual void rva000875D6();

private:
	void setCameraTransform();

	char m_pad04[0x6C - 4];
	Real m_pitchAngle;		// +0x6C
	Real m_zoom;			// +0x70
	char m_pad74[0x2439 - 0x74];
	bool m_flag2439;		// +0x2439
	bool m_flag243A;		// +0x243A
	char m_pad243B[0x243C - 0x243B];
	StringBase<char> m_name243C;	// +0x243C
	StringBase<char> m_name2440;	// +0x2440
};

void W3DView::rva0008DAE4()
{
	m_zoom = 1.0f;
	m_flag243A = false;
	m_pitchAngle = 0.87266463f;
	setCameraTransform();
	step95();
}

// Retail 0x000875A2 (44 bytes) and 0x000875D6 (28 bytes), two more W3DView
// vftable entries with no direct callers: the first sets the +0x2439 flag and
// copies two strings into +0x243C and +0x2440; the second sets the +0x243A
// flag, zooms back to 1.0 and finishes in the same slot-0x17C step as above.
void W3DView::rva000875A2(const StringBase<char> &first, const StringBase<char> &second)
{
	m_flag2439 = true;
	m_name243C.set(first);
	m_name2440.set(second);
}

void W3DView::rva000875D6()
{
	m_flag243A = true;
	m_zoom = 1.0f;
	step95();
}
