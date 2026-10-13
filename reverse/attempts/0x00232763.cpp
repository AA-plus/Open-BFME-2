// ?translateKey@Keyboard@@QAEGG@Z
// partial score=0.9 date=2026-10-13
// ?translateKey@Keyboard@@QAEGG@Z
// partial score=0.9 date=2026-10-13
// ?translateKey@Keyboard@@QAEGG@Z
// partial score=0.9 date=2026-10-13
// cl: /DNDEBUG /MD /EHsc /O1 /G7
//
// Two Keyboard key-table accessors (formerly rowed as AIPlayer::rva002326AE
// and AIPlayer::rva00232643; the class is Keyboard, see Keyboard.cpp):
//
//   0x002326AE  77B  getPrintableKey: Zero Hour's
//                    Keyboard::getPrintableKey(UnsignedByte key, Int state)
//                    over m_keyNames[256] at +0x81C (three WideChars per
//                    key), returning 0 out of range. The name and signature
//                    are Zero Hour's and fit the body exactly (inferred).
//                    Callers 0x00325AC6 and 0x0035962B.
//   0x00232643  17B  rva00232643: bit KEY_STATE_DOWN of m_keyStatus[key]'s
//                    state (+0x1C, 8-byte KeyboardIO). Zero Hour has no
//                    one-argument key-down query, so the name stays
//                    address-derived. Callers 0x0042F8AF and 0x005B1FFA.
//
// The imul by 6 for the key-name stride needs /G7.

typedef int Int;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

// upstream layout: GeneralsMD/Code/GameEngine/Include/GameClient/Keyboard.h
struct KeyboardIO
{
	UnsignedByte key;
	UnsignedByte status;
	UnsignedShort state;
	UnsignedInt sequence;
};

// Zero Hour Keyboard.h key codes and modifier bits (BFME2 values read off
// retail 0x00232763's dispatch and modifier stores; they match ZH).
enum
{
	KEY_LCTRL = 0x1D,
	KEY_LSHIFT = 0x2A,
	KEY_RSHIFT = 0x36,
	KEY_LALT = 0x38,
	KEY_CAPS = 0x3A,
	KEY_RCTRL = 0x9D,
	KEY_RALT = 0xB8,
	KEY_STATE_DOWN = 0x0002,
	KEY_STATE_LSHIFT = 0x0010,
	KEY_STATE_RSHIFT = 0x0020,
	KEY_STATE_LCONTROL = 0x0004,
	KEY_STATE_RCONTROL = 0x0008,
	KEY_STATE_LALT = 0x0040,
	KEY_STATE_RALT = 0x0080,
	KEY_STATE_CAPSLOCK = 0x0200,
	KEY_STATE_SHIFT2 = 0x0400
};

enum
{
	KeyboardStatus_UNUSED = 0,
	KeyboardStatus_USED = 1
};

extern "C" __declspec(dllimport) Int __cdecl iswalpha(WideChar key);

// Slot view for Keyboard's pure getCapsState (vtable slot 14, 0x00BE81F0).
// DirectInputKeyboard fills it with GetKeyState(VK_CAPITAL). Only the slot
// is used; nothing here is defined or emitted.
class KeyboardCapsView
{
public:
#define V(n) virtual void pad##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07)
	V(08) V(09) V(10) V(11) V(12) V(13)
#undef V
	virtual bool getCapsState();
};

class Keyboard
{
public:
	enum { MAX_KEY_STATES = 3 };
	enum { KEY_NAMES_COUNT = 256 };

	WideChar getPrintableKey(UnsignedByte key, Int state);
	bool rva00232643(UnsignedByte key);
	WideChar translateKey(WideChar keyCode);
	bool isShift();

private:
	// Zero Hour's getKeyStatusData/getKeyStateBit factored as the shr/test
	// idiom the rowed rva00232643 sibling proves (all retail call sites pass
	// KEY_STATE_DOWN, i.e. bit 1).
	UnsignedByte getKeyStatusData(UnsignedByte key) { return m_keyStatus[key].status; }
	bool getKeyStateBit(UnsignedByte key)
	{
		return (((unsigned char)m_keyStatus[key].state) >> 1) & 1;
	}
	void setKeyStatusData(UnsignedByte key, UnsignedByte data) { m_keyStatus[key].status = data; }

private:
	char m_unmodelled00[0x0C];
	UnsignedShort m_modifiers;							// +0x0C
	UnsignedByte m_shift2Key;							// +0x0E
	char m_unmodelled0F[0x1C - 0x0F];
	KeyboardIO m_keyStatus[256];						// +0x1C
	struct
	{
		WideChar stdKey;
		WideChar shifted;
		WideChar shifted2;
	} m_keyNames[KEY_NAMES_COUNT];						// +0x81C
};

WideChar Keyboard::getPrintableKey(UnsignedByte key, Int state)
{
	if (key >= KEY_NAMES_COUNT)
		return 0;
	if (state < 0 || state >= MAX_KEY_STATES)
		return 0;
	if (state == 0)
		return m_keyNames[key].stdKey;
	if (state == 1)
		return m_keyNames[key].shifted;
	return m_keyNames[key].shifted2;
}

bool Keyboard::rva00232643(UnsignedByte key)
{
	return (((unsigned char)m_keyStatus[key].state) >> 1) & 1;
}

// ?translateKey@Keyboard@@QAEGG@Z @0x00232763 445B. Zero Hour's
// Keyboard::translateKey (reference/open-bfme-1 Keyboard.cpp) with BFME2's
// offsets (+0x0C/+0x0E/+0x1C/+0x81C), BFME2's virtual getCapsState (slot 14)
// and direct iswalpha import: range-check, modifier scancode switch (caps
// toggles CAPSLOCK with the shared-mask ecx shape), shift2 short-circuit,
// SHIFT2 table, isShift-or-(caps-and-alpha) shifted table, else standard.
WideChar Keyboard::translateKey(WideChar keyCode)
{
	if (keyCode > 0x00FF)
		return keyCode;

	UnsignedByte ubKeyCode = (UnsignedByte)keyCode;
	switch (ubKeyCode)
	{
		case KEY_CAPS:
			if (getKeyStatusData(KEY_CAPS) == KeyboardStatus_UNUSED)
			{
				if (getKeyStateBit(KEY_CAPS))
				{
					if (m_modifiers & KEY_STATE_CAPSLOCK)
						m_modifiers &= ~KEY_STATE_CAPSLOCK;
					else
						m_modifiers |= KEY_STATE_CAPSLOCK;
				}
				setKeyStatusData(KEY_CAPS, KeyboardStatus_USED);
			}
			return 0;

		case KEY_LSHIFT:
			if (getKeyStateBit(KEY_LSHIFT))
				m_modifiers |= KEY_STATE_LSHIFT;
			else
				m_modifiers &= ~KEY_STATE_LSHIFT;
			return 0;

		case KEY_RSHIFT:
			if (getKeyStateBit(KEY_RSHIFT))
				m_modifiers |= KEY_STATE_RSHIFT;
			else
				m_modifiers &= ~KEY_STATE_RSHIFT;
			return 0;

		case KEY_LCTRL:
			if (getKeyStateBit(KEY_LCTRL))
				m_modifiers |= KEY_STATE_LCONTROL;
			else
				m_modifiers &= ~KEY_STATE_LCONTROL;
			return 0;

		case KEY_RCTRL:
			if (getKeyStateBit(KEY_RCTRL))
				m_modifiers |= KEY_STATE_RCONTROL;
			else
				m_modifiers &= ~KEY_STATE_RCONTROL;
			return 0;

		case KEY_LALT:
			if (getKeyStateBit(KEY_LALT))
				m_modifiers |= KEY_STATE_LALT;
			else
				m_modifiers &= ~KEY_STATE_LALT;
			return 0;

		case KEY_RALT:
			if (getKeyStateBit(KEY_RALT))
				m_modifiers |= KEY_STATE_RALT;
			else
				m_modifiers &= ~KEY_STATE_RALT;
			return 0;

		default:
			if (ubKeyCode == m_shift2Key)
			{
				if (getKeyStateBit(m_shift2Key))
					m_modifiers |= KEY_STATE_SHIFT2;
				else
					m_modifiers &= ~KEY_STATE_SHIFT2;
				return 0;
			}

			if (m_modifiers & KEY_STATE_SHIFT2)
				return m_keyNames[ubKeyCode].shifted2;

			if (isShift() || ((KeyboardCapsView *)this)->getCapsState() && iswalpha(m_keyNames[ubKeyCode].stdKey))
				return m_keyNames[ubKeyCode].shifted;

			return m_keyNames[ubKeyCode].stdKey;
	}
}
