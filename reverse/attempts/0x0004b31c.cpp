// ?gatherAnimationDebuggingInfo@W3DDisplay@@IAEXXZ
// partial score=0.81301 date=2026-10-13
// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include "unicode_string.h"

struct _iobuf;
extern "C" int __cdecl fprintf(_iobuf *, const char *, ...);
extern _iobuf *TheCRCFile;

class GameFont;
class Object;
class Drawable;

#define V4(a) virtual void a##0(); virtual void a##1(); virtual void a##2(); virtual void a##3();
#define V16(a) V4(a##0) V4(a##1) V4(a##2) V4(a##3)

class DisplayString {
public:
	virtual void v00();
	virtual void setText(UnicodeString text);
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void setFont(GameFont *font);
};

class DisplayStringManager {
public:
	V4(a) V4(b) V4(c) virtual void d0(); virtual void d1();
	virtual DisplayString *newDisplayString();
};
extern DisplayStringManager *TheDisplayStringManager;

class FontLibrary {
public:
	GameFont *getFont(const AsciiString *name, float pointSize, bool bold);
};
extern FontLibrary *TheFontLibrary;

struct GlobalLanguage {
	char pad[0xc8];
	AsciiString m_unicodeFontName;
	int m_unicodeFontSize;
	bool m_unicodeFontBold;
};
extern GlobalLanguage *TheGlobalLanguageData;

struct GlobalData {
	char pad[0x9cc];
	int m_animDebugMode;
};
extern GlobalData *TheGlobalData;
extern const char *TheAnimDebugModeNames[];
extern const char *TheWeaponSlotTypeNames[];
extern const char *TheWeaponStatusNames[];

class Keyboard {
public:
	bool isShift();
	bool isCtrl();
};
extern Keyboard *TheKeyboard;

class InGameUI {
public:
	V16(a) V16(b) V16(c) V16(d) // 64
	V4(e0) virtual void f0(); virtual void f1();  // 70
	virtual int getSelectCount();                 // 70
	virtual void g0(); virtual void g1(); virtual void g2(); virtual void g3(); // 71..74
	virtual Drawable *getFirstSelectedDrawable(); // 75
	V16(h) virtual void i0(); // 76..92
	virtual int getMousedOverDrawableID();        // 93
};
extern InGameUI *TheInGameUI;

class GameClient {
public:
	V16(a)
	virtual Drawable *findDrawableByID(int id);
};
extern GameClient *TheGameClient;

class GameLogic {
public:
	Object *findObjectByID(int id);
	bool isInMultiplayerGame();
	char pad0[0x40];
	unsigned int m_frame;
	char pad1[0x1b4 - 0x44];
	int m_logicDepth;
};
extern GameLogic *TheGameLogic;

class LogicGuard {
public:
	LogicGuard();
	~LogicGuard()
	{
		if (TheGameLogic)
			--TheGameLogic->m_logicDepth;
	}
};

struct ModelConditionFlags {
	unsigned int m_bits[19];
	void describe(AsciiString *out, int perLine) const;
	void buildDescription(AsciiString *out, const ModelConditionFlags &other, bool full, int perLine) const;
};
bool flagsEqual(const ModelConditionFlags *a, const ModelConditionFlags *b);

struct AnimRecord {
	AsciiString m_animationName;
	AsciiString m_animationDetails;
	ModelConditionFlags m_flags;
	int m_firstFrame;
	int m_lastFrame;
	AnimRecord() throw();
	~AnimRecord();
};

template <class T> class allocator { public: allocator() {} };

class AnimHistory {
public:
	AnimHistory(const allocator<int> &a = allocator<int>()) throw();
	~AnimHistory();
	AnimRecord *begin() { return m_start; }
	AnimRecord *end() { return m_finish; }
	int size() const { return m_finish - m_start; }
	AnimRecord &operator[](int i) { return m_start[i]; }
	void push_back(const AnimRecord &r);
	AnimRecord *erase(AnimRecord *first, AnimRecord *last);
	AnimRecord *m_start;
	AnimRecord *m_finish;
	AnimRecord *m_eos;
};

class DrawInterface {
public:
	V4(a) V4(b) virtual void c0(); // 0..8
	virtual int getAnimationCount();                 // 9
	virtual AsciiString getAnimationName(int i);     // 10
	virtual void c1();                               // 11
	virtual void getAnimationDescription(int i, AsciiString *desc, AsciiString *details); // 12
	virtual const char *getModelName();              // 13
};

class DrawModule {
public:
	V16(a) V16(b) V4(c0) V4(c1) virtual void d0(); // 0..40
	virtual DrawInterface *getDrawInterface();     // 41
	V4(e0) V4(e1) V4(e2) virtual void f0(); virtual void f1(); // 42..55
	virtual void buildSubObjectDescription(AsciiString *out, int perLine); // 56
};

struct ThingTemplate {
	char pad[0x64];
	char *m_nameData;
	const char *getNameText() const { return m_nameData ? m_nameData + 8 : ""; }
};

class Drawable {
public:
	DrawModule **getDrawModules();
	void *m_vtable;
	ThingTemplate *m_template;
	char pad0[0xfc - 8];
	Object *m_object;
	char pad1[0x258 - 0x100];
	ModelConditionFlags m_conditionFlags;
};

class ContainModule {
public:
	V16(a) V16(b) V16(c) V16(d) V4(e) // 0..67
	virtual Object *getContainedObject(); // 68
};

struct WeaponTemplate {
	char pad[8];
	char *m_nameData;
	const char *getNameText() const { return m_nameData ? m_nameData + 8 : ""; }
};

class Weapon {
public:
	float getPercentReadyToFire() const;
	int computeStatus(bool *out) const;
	int getStatus() const;
	void *m_vtable;
	WeaponTemplate *m_template;
	char pad[0x18 - 8];
	unsigned int m_nextShot;
};

class Object {
public:
	ContainModule *getContain() const;
	Drawable *getDrawable();
	const Weapon *getCurrentWeapon(int *slot) const;
	char pad[0x74];
	int m_id;
};

class W3DDisplay {
protected:
	void gatherAnimationDebuggingInfo();
	char pad[0x1d0];
	DisplayString *m_animDebugStrings[25];
};

void W3DDisplay::gatherAnimationDebuggingInfo()
{
	static int s_mode;
	static int s_prevID;
	static int s_lockedID;
	static AnimHistory s_history;
	UnicodeString text;
	AsciiString description;
	AnimRecord current;

	if (m_animDebugStrings[0] == 0) {
		GameFont *font;
		if (TheGlobalLanguageData && !TheGlobalLanguageData->m_unicodeFontName.isEmpty())
			font = TheFontLibrary->getFont(&TheGlobalLanguageData->m_unicodeFontName,
				(float)TheGlobalLanguageData->m_unicodeFontSize, TheGlobalLanguageData->m_unicodeFontBold);
		else
			font = TheFontLibrary->getFont(&AsciiString("FixedSys"), 8.0f, false);
		for (int i = 0; i < 25; ++i) {
			if (m_animDebugStrings[i] == 0) {
				m_animDebugStrings[i] = TheDisplayStringManager->newDisplayString();
				m_animDebugStrings[i]->setFont(font);
			}
		}
	}

	text.format(L"ANIMATION STATE DEBUGGER: History based on %S changes. (shift+w toggles)",
		TheAnimDebugModeNames[TheGlobalData->m_animDebugMode]);
	m_animDebugStrings[0]->setText(text);

	Object *object = 0;
	Drawable *drawable;
	if (TheKeyboard->isCtrl() || TheKeyboard->isShift()) {
		Drawable *hover = TheGameClient->findDrawableByID(TheInGameUI->getMousedOverDrawableID());
		if (hover) {
			object = hover->m_object;
			s_lockedID = 0;
			if (!object)
				goto selection;
			if (TheKeyboard->isCtrl())
				s_lockedID = object->m_id;
		}
	}
	int lockedID = s_lockedID;
	if (lockedID && TheGameLogic->findObjectByID(lockedID)) {
		object = TheGameLogic->findObjectByID(lockedID);
		if (!object)
			goto noObject;
		drawable = object->getDrawable();
	} else {
selection:
		s_lockedID = 0;
		if (TheInGameUI->getSelectCount() != 1) {
			drawable = TheGameClient->findDrawableByID(TheInGameUI->getMousedOverDrawableID());
			if (drawable)
				object = drawable->m_object;
		} else {
			drawable = TheInGameUI->getFirstSelectedDrawable();
			object = drawable->m_object;
			if (!object)
				goto noObject;
			ContainModule *contain = object->getContain();
			if (contain) {
				object = contain->getContainedObject();
				if (!object)
					goto noObject;
				drawable = object->getDrawable();
			}
		}
	}
	if (!object || !drawable)
		goto noObject;

	if (TheGameLogic->findObjectByID(s_prevID) != object || s_mode != TheGlobalData->m_animDebugMode) {
		s_prevID = object->m_id;
		s_history.erase(s_history.begin(), s_history.end());
		s_mode = TheGlobalData->m_animDebugMode;
	}

	{
		DrawModule **module = 0;
		DrawInterface *drawInterface = 0;
		DrawInterface *fallback = 0;
		DrawModule **modules = drawable->getDrawModules();
		if (modules) {
			for (module = modules; *module; ++module) {
				drawInterface = (*module)->getDrawInterface();
				if (drawInterface) {
					if (drawInterface->getAnimationCount() > 0)
						break;
					fallback = drawInterface;
				}
			}
		}
		if (!drawInterface)
			drawInterface = fallback;
		const char *modelName = 0;
		if (drawInterface)
			modelName = drawInterface->getModelName();
		if (!modelName)
			modelName = "n/a";
		text.format(L"LOCKED Object: %S (ID:%d) %S", drawable->m_template->getNameText(), object->m_id, modelName);
		if (s_lockedID)
			text.concat(L" -- release by Shift+mousing over any object");
		m_animDebugStrings[1]->setText(text);

		int slot;
		const Weapon *weapon = object->getCurrentWeapon(&slot);
		if (weapon) {
			unsigned int nextShot = weapon->m_nextShot;
			int percent = (int)(weapon->getPercentReadyToFire() * 100.0f);
			int status;
			if (TheGameLogic->isInMultiplayerGame()) {
				status = weapon->computeStatus(0);
			} else {
				LogicGuard guard;
				if (TheCRCFile)
					fprintf(TheCRCFile, "POTENTIAL DESYNC: Forced into EnterLogic State. (W3DDisplay::gatherAnimationDebuggingInfo)");
				status = weapon->getStatus();
				if (TheCRCFile)
					fprintf(TheCRCFile, "LeaveLogic() called.");
			}
			text.format(L"Weapon: %S(%S), NextShot:%d(%d%%), Status:%S", weapon->m_template->getNameText(),
				TheWeaponSlotTypeNames[slot], nextShot, percent, TheWeaponStatusNames[status]);
		} else {
			text.format(L"Weapon: n/a", drawable->m_template->getNameText(), object->m_id);
		}
		m_animDebugStrings[2]->setText(text);

		current.m_firstFrame = current.m_lastFrame = TheGameLogic->m_frame;
		text.format(L"CURRENT Frame: %d", current.m_firstFrame);
		m_animDebugStrings[3]->setText(text);

		if (drawInterface && *module) {
			(*module)->buildSubObjectDescription(&description, 4);
			text.format(L"SubObject Statii: (%S)", description.str());
			m_animDebugStrings[4]->setText(text);
			int count = drawInterface->getAnimationCount();
			if (count >= 1) {
				current.m_animationName = drawInterface->getAnimationName(0);
				drawInterface->getAnimationDescription(0, &description, &current.m_animationDetails);
				if (count >= 2)
					text.format(L"Blending From: %S", description.str());
				else
					text.format(L"CURRENT Animation: %S", description.str());
				m_animDebugStrings[6]->setText(text);
				text.format(L"%S", current.m_animationDetails.str());
				m_animDebugStrings[5]->setText(text);
			} else {
				text.format(L"CURRENT Animation: Doesn't have one!");
				m_animDebugStrings[6]->setText(text);
			}
			if (count >= 2) {
				current.m_animationName = drawInterface->getAnimationName(1);
				drawInterface->getAnimationDescription(1, &description, &current.m_animationDetails);
				text.format(L"Blending To: %S", description.str());
				m_animDebugStrings[7]->setText(text);
				text.format(L"%S", current.m_animationDetails.str());
				m_animDebugStrings[5]->setText(text);
			} else {
				text.format(L"No blend in progress");
				m_animDebugStrings[7]->setText(text);
			}
		}
	}

	current.m_flags = drawable->m_conditionFlags;
	current.m_flags.describe(&description, 4);
	text.format(L"CURRENT ModelConditionFlags: (%S)", description.str());
	m_animDebugStrings[8]->setText(text);

	if (s_history.size() == 0) {
		s_history.push_back(current);
	} else {
		switch (TheGlobalData->m_animDebugMode) {
		case 0: {
			AnimRecord &last = s_history[s_history.size() - 1];
			if (last.m_animationName.compare(current.m_animationName) == 0)
				last.m_lastFrame = current.m_lastFrame;
			else
				s_history.push_back(current);
			break;
		}
		case 1: {
			AnimRecord &last = s_history[s_history.size() - 1];
			if (flagsEqual(&last.m_flags, &current.m_flags))
				last.m_lastFrame = current.m_lastFrame;
			else
				s_history.push_back(current);
			break;
		}
		case 2: {
			AnimRecord &last = s_history[s_history.size() - 1];
			if (last.m_animationDetails.compare(current.m_animationDetails) == 0)
				last.m_lastFrame = current.m_lastFrame;
			else
				s_history.push_back(current);
			break;
		}
		}
	}

	{
		int size = s_history.size();
		if (size > 1) {
			s_history[size - 1].m_flags.buildDescription(&description, s_history[size - 2].m_flags, false, 4);
			text.format(L"CURRENT Delta ConditionFlags: %S\n", description.str());
			m_animDebugStrings[9]->setText(text);
			for (int i = 0; i < 5; ++i) {
				int index = size - i - 2;
				int previous = size - i - 3;
				if (previous < 0) {
					text.format(L"");
					m_animDebugStrings[10 + 3 * i]->setText(text);
					m_animDebugStrings[11 + 3 * i]->setText(text);
					m_animDebugStrings[12 + 3 * i]->setText(text);
				} else {
					if (i == 4) {
						AnimRecord &old = s_history[index];
						text.format(L"OLDEST Frame %d-%d: %S", old.m_firstFrame, old.m_lastFrame, old.m_animationDetails.str());
						m_animDebugStrings[22]->setText(text);
						text.format(L"OLDEST Animation: %S", old.m_animationName.str());
						m_animDebugStrings[23]->setText(text);
						old.m_flags.describe(&description, 4);
						text.format(L"OLDEST ModelConditionFlags: (%S)\n", description.str());
						m_animDebugStrings[24]->setText(text);
					} else {
						AnimRecord &old = s_history[index];
						text.format(L"OLD Frame %d-%d: %S", old.m_firstFrame, old.m_lastFrame, old.m_animationDetails.str());
						m_animDebugStrings[10 + 3 * i]->setText(text);
						text.format(L"OLD Animation: %S", old.m_animationName.str());
						m_animDebugStrings[11 + 3 * i]->setText(text);
						old.m_flags.buildDescription(&description, s_history[previous].m_flags, false, 4);
						text.format(L"OLD Delta ConditionFlags: (%S)\n", description.str());
						m_animDebugStrings[12 + 3 * i]->setText(text);
					}
				}
			}
		} else {
			text.format(L"Delta ModelConditions: n/a");
			m_animDebugStrings[9]->setText(text);
		}
	}
	return;

noObject:
	text.format(L"");
	for (int i = 1; i < 25; ++i)
		m_animDebugStrings[i]->setText(text);
	s_prevID = 0;
	s_history.erase(s_history.begin(), s_history.end());
	s_mode = TheGlobalData->m_animDebugMode;
}
