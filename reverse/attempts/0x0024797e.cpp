// ?DoXfer@GameLogicSnapshot@@QAEXPAVXfer@@@Z
// partial score=0.99 date=2026-10-14
// ?DoXfer@GameLogicSnapshot@@QAEXPAVXfer@@@Z
// partial score=0.99 date=2026-10-13
// ?DoXfer@GameLogicSnapshot@@QAEXPAVXfer@@@Z
// partial score=0.99 date=2026-10-13
// r6 2026-10-14: the AsciiString::compare(const char*) throw() shim that landed
// for 0x32B1E1 does not touch this body; the needed declaration is
// StringBase<T>::compare(const StringBase<T>&) throw() in string_base.h. With it
// the body is 2197 B (was 2208) and the ONLY residue is still the frame: retail
// sub esp,0x70 puts it at [ebp-0x3c]/[ebp-0x38] where the empty Rva0004224C guard
// (ctor out-of-line 0x4224c, this=[ebp-0x38], inlined dtor) shares [ebp-0x38];
// ours reserves the guard slot and puts it at [ebp-0x40]/[ebp-0x3c], 349-350
// diffs. Re-tested declaration order (it before/after guard, it at top, it in
// branch, guard after it): no change. Dropping the `first` temp (first(&it)
// directly) gives frame 0x70 but loses retail's -0x34/-0x30 copy and moves the
// guard to -0x34 (350 diffs). cl 7.1 free-places this empty guard only onto an
// unused slot, never over a live local; not reproducible from source shape.
// NOTE: needs reference/shims/bfme2_ascii/string_base.h `int compare(const StringBase<T> &str) const throw();` (not landed: shim edit = full gate) so the compare temp has no EH state.
// With that shim: 2197 B vs 2195, 343 diffs, all from one frame wall. Retail frame
// sub esp,0x70 puts the hash iterator `it` at [ebp-0x3c] so its second word shares
// [ebp-0x38] with the empty FP guard (Rva0004224C, EH state 3, live to the end);
// ours gives the guard its own slot (it at [ebp-0x40], frame 0x74), shifting every
// slot below and swapping ebx/eax in `it=first`. No change (343 each): guard ctor
// inline in-class (GameLogicInit.cpp model, free-places onto [ebp+8] in 0x248558,
// but here [ebp+8] holds i/AsciiString/esp save), noinline inline, declared-only,
// visible rva000421FD + setFPMode, /EHs, reference-bound temporary guard. Toy TUs:
// cl 7.1 free-places the empty guard only onto an unused slot (an enregistered
// param home), never over a live local. WB 0x00D097E0 has no guard object (inline
// m_1b8 ++/--). Fixed here: TheGameLogic declared as the converged real global;
// m_158 typed vector<Rva00243B52DestroyEntry *> so clear() calls retail's 0x31BD55
// (the void* erase pin resolves to 0x27400).
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist
// stlport
//
// GameLogic::DoXfer, retail 0x0024797E (2195 B, RET 4; WB 0x00D097E0, GameLogic.cpp 7168..7472).
// The receiver is the Snapshot sub-object at GameLogic+0x0C (the body subtracts 0x0C
// to reach the logic for its out-of-line calls). Structure follows the WB debug body and
// Zero Hour's GameLogic::xfer; BFME 2's save format adds the skirmish game info and
// preferences block, the buildable overrides, the control bar overrides and the
// Snapshot-valued sub-systems. Members keep offset names (receiver-relative offsets
// are the Snapshot view's, GameLogic offset = receiver offset + 0x0C).
#include "ascii_string.h"
#include "unicode_string.h"
#include <set>
#include <map>
#include <hash_map>

class Xfer;
class Object;
struct Rva00243B52DestroyEntry;
class Snapshot { public: virtual void slot00(); };

struct XferVersionInfo
{
	XferVersionInfo(unsigned char a, unsigned char b) : m_a(a), m_b(b) {}
	unsigned char m_a, m_b;
};

struct Coord3DBase { float x, y, z; };

class Xfer
{
public:
	virtual void slot00();
	virtual bool isLoading();
	virtual bool isStoring();
	virtual bool isCRC();
	virtual bool isLightCRC();
	virtual void beginBlock(const char *name);
	virtual void endBlock();
	virtual void skipBlock(const char *name);
	virtual void slot20();
	virtual void slot24();
	virtual void xferVersion(XferVersionInfo *version);
	virtual void slot2C();
	virtual void xferSnapshot(Snapshot *snapshot);
	virtual void slot34(); virtual void slot38(); virtual void slot3C(); virtual void slot40();
	virtual void slot44(); virtual void slot48(); virtual void slot4C(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual Xfer &xferCoord3D(Coord3DBase *value);
	virtual void slot64();
	virtual Xfer &xferUnicodeString(UnicodeString *value);
	virtual Xfer &xferAsciiString(AsciiString *value);
	virtual Xfer &slot70();
	virtual Xfer &slot74();
	virtual Xfer &xferUnsignedInt(unsigned int *value);
	virtual Xfer &xferInt(int *value);
	virtual Xfer &xferUnsignedShort(unsigned short *value);
	virtual Xfer &slot84();
	virtual Xfer &slot88();
	virtual Xfer &slot8C();
	virtual Xfer &xferBool(bool *value);
};

enum ObjectID { INVALID_ID = 0 };
void XferObjectID(Xfer *xfer, ObjectID *id);
void XferBuildableStatus(Xfer *xfer, int *value);
void XferGameDifficulty(Xfer *xfer, int *value);

struct ObjectTOCEntry;
class CommandButton;
class Team;
class ThingTemplate
{
public:
	void GetAssetList(int assets, int mode);
};

struct Rva001408C0Target;
typedef _STL::set<Rva001408C0Target *, _STL::less<Rva001408C0Target *>,
	_STL::allocator<Rva001408C0Target *> > Rva001408C0Set;

class AssetList
{
public:
	AssetList() : m_treeLayoutPad(0), m_changed(true) {}

private:
	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

struct AssetLoadMode
{
	bool m_alternate;
	AssetLoadMode() : m_alternate(false) {}
};

void bfmeMergeReceiverKeys(int value);

struct CreateMask
{
	CreateMask() { memset(m_bits, 0, sizeof(m_bits)); }
	unsigned int m_bits[4];
};

class ThingFactory
{
public:
	Object *rva002D0A23(const ThingTemplate *tt, Team *team, const CreateMask &mask, ObjectID id);
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

class Player { public: char m_pad00[0x2ec]; Team *m_defaultTeam; };
class PlayerList { public: char m_pad00[0x18]; Player *m_neutralPlayer; };
extern PlayerList *ThePlayerList;

class ControlBar { public: const CommandButton *findCommandButton(const AsciiString &name); };
extern ControlBar *TheControlBar;

class GameInfo
{
public:
	GameInfo();
	virtual ~GameInfo();
	virtual void slot04();
	virtual void slot08();
	virtual void xfer(Xfer *xfer);
	virtual void slot10(); virtual void slot14(); virtual void slot18();
	virtual void slot1C(); virtual void slot20(); virtual void slot24();
	virtual void reset();
	void init();
	void endGame();
	void clearSlotList();
	char m_pad04[0x10 - 4];
	bool m_inGame;
	char m_rest[0xDC - 0x11];
};
class SkirmishGameInfo : public GameInfo
{
public:
	SkirmishGameInfo();
	virtual ~SkirmishGameInfo();
	char m_rest2[0xE3C - 0xDC];
};
extern GameInfo *TheSkirmishGameInfo;
extern GameInfo *TheGameInfo;

class SkirmishPreferences
{
public:
	SkirmishPreferences(int tag);
	virtual ~SkirmishPreferences();
	virtual bool write();
	UnicodeString Rva0043B9F5();
	void setCurrentUserName(const UnicodeString &name);

private:
	char m_pad04[0x20 - 4];
};

class LinearCampaignManager;
class CaveSystem;
class LargeGroupAudio;
class DelayedExperienceLevelGrantSystem;
extern LinearCampaignManager *TheLinearCampaignManager;
extern CaveSystem *TheCaveSystem;
extern LargeGroupAudio *TheLargeGroupAudio;
extern DelayedExperienceLevelGrantSystem *TheDelayedExperienceLevelGrantSystem;

// Pointer conversion to a Snapshot sub-object at +off, null-guarded as a base conversion is.
static __forceinline Snapshot *snapshotAt(void *p, int off) { return p ? (Snapshot *)((char *)p + off) : 0; }

class GameLogic;
extern GameLogic *TheGameLogic;
class Rva000421FD
{
public:
	void rva000421FD(void);
};
struct LogicFPView { char opaque[0x1B4]; int depth; };
class Rva0004224C
{
public:
	Rva0004224C(void)
	{
		if (TheGameLogic)
			((Rva000421FD *)TheGameLogic)->rva000421FD();
	}
	~Rva0004224C(void) { if (TheGameLogic) --((LogicFPView *)TheGameLogic)->depth; }
};

struct Rva0023E887Source { int m_00; const char *m_text; };
class Rva0023E887
{
public:
	Rva0023E887(const Rva0023E887Source &source);
private:
	int m_00;
	AsciiString m_text;
};

struct TreeKey00242F5E { int m_id; AsciiString m_name; };
struct TreeOpaqueMapped242F5E { unsigned int m_bits; };
bool operator<(const TreeKey00242F5E &a, const TreeKey00242F5E &b);
typedef _STL::map<TreeKey00242F5E, TreeOpaqueMapped242F5E, _STL::less<TreeKey00242F5E>, _STL::allocator<_STL::pair<const TreeKey00242F5E, TreeOpaqueMapped242F5E> > > ControlBarOverrideMap;

enum BuildableStatus { BUILDABLE_STATUS_UNKNOWN = 0 };
namespace rts
{
	template <class T> struct hash { size_t operator()(const T &value) const; };
	template <class T> struct equal_to { bool operator()(const T &left, const T &right) const; };
}
typedef _STL::pair<const AsciiString, BuildableStatus> BuildableStatusPair;
typedef _STL::hash_map<AsciiString, BuildableStatus, rts::hash<AsciiString>,
	rts::equal_to<AsciiString>, _STL::allocator<BuildableStatusPair> > BuildableMap;

class Rva000411084 { public: void *next(); void *m_current; void *m_table; };
class Rva000427195 { public: void *first(Rva000411084 *iter); };

// GameLogic as the logic-relative calls see it.
class GameLogic
{
public:
	unsigned int getObjectCount();
	void prepareLogicForObjectLoad();
	void xferObjectTOC(Xfer *xfer);
	ObjectTOCEntry *findTOCEntryByName(AsciiString name);
};
class Rva0023E7B4 { public: void *rva0023E7B4(unsigned short key); };

struct ObjectView
{
	char m_pad00[4];
	ThingTemplate *m_template;
	char m_pad08[0x38 - 8];
	Coord3DBase m_position;
	char m_pad44[0x74 - 0x44];
	ObjectID m_id;
	char m_pad78[0x8C - 0x78];
	ObjectView *m_next;
};

struct BfmeFormattedText { char *text; int tag; };
extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *result, int tag, const char *format, ...);
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern int g_guardTargetTypeThrowInfo;

static __forceinline void throwXferException()
{
	BfmeFormattedText tmp;
	bfmeFormatText(&tmp, 5, (const char *)0);
	_CxxThrowException(&tmp, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
	__assume(0);
}

static __forceinline bool differs(const UnicodeString &a, const UnicodeString &b) throw() { return a.compare(b) != 0; }

// The Snapshot sub-object of GameLogic (receiver of DoXfer); offsets are receiver-relative.
class GameLogicSnapshot
{
public:
	void DoXfer(Xfer *xfer);

private:
	char m_pad00[4];
	BuildableMap m_buildableOverrides;                   // +0x04 (GameLogic +0x10)
	ControlBarOverrideMap m_controlBarOverrides;         // +0x18
	char m_pad2C[0x2c - 0x18 - sizeof(ControlBarOverrideMap)];
	unsigned int m_timestamp;                            // +0x2C
	char m_pad30[0x34 - 0x30];
	unsigned int m_frame;                                // +0x34
	char m_pad38[0x88 - 0x38];
	int m_88;
	bool m_scoring;                                      // +0x8C
	bool m_8d, m_8e, m_8f;
	char m_pad90[0x93 - 0x90];
	bool m_93;
	int m_94;
	int m_98;
	char m_pad9C[0xA0 - 0x9C];
	ObjectView *m_objList;                               // +0xA0
	char m_padA4[0x104 - 0xA4];
	int m_mode;                                          // +0x104
	int m_second;                                        // +0x108
	int m_10c;
	bool m_110;
	char m_pad111[0x158 - 0x111];
	_STL::vector<Rva00243B52DestroyEntry *> m_158;
	Snapshot *m_164;
	Snapshot *m_168;
	Snapshot *m_16c;
	int m_170;
	unsigned int m_174;
};

void GameLogicSnapshot::DoXfer(Xfer *xfer)
{
	XferVersionInfo version(1, 8);
	xfer->xferVersion(&version);

	int mode = m_mode;
	xfer->xferInt(&mode);
	m_mode = mode;
	int second = m_second;
	xfer->xferInt(&second);
	int curMode = m_mode;
	m_second = second;

	if (curMode == 2 || second == 0) {
		if (xfer->isLoading()) {
			if (!TheSkirmishGameInfo) {
				TheSkirmishGameInfo = new SkirmishGameInfo;
			} else if (TheSkirmishGameInfo->m_inGame) {
				TheSkirmishGameInfo->endGame();
			}
			TheGameInfo = TheSkirmishGameInfo;
			TheSkirmishGameInfo->init();
			TheSkirmishGameInfo->clearSlotList();
			TheSkirmishGameInfo->reset();
		}
		TheSkirmishGameInfo->xfer(xfer);
	}

	if (version.m_b >= 4 && m_mode == 2) {
		SkirmishPreferences prefs(0);
		UnicodeString name = prefs.Rva0043B9F5();
		xfer->xferUnicodeString(&name);
		bool changed = xfer->isLoading() && differs(prefs.Rva0043B9F5(), name);
		if (changed) {
			prefs.setCurrentUserName(name);
			prefs.write();
		}
	}

	if (xfer->isCRC())
		xfer->xferUnsignedInt(&m_timestamp);
	xfer->xferUnsignedInt(&m_frame);
	xfer->xferInt(&m_170);
	xfer->xferBool(&m_110);

	if (xfer->isLightCRC()) {
		for (ObjectView *obj = m_objList; obj; obj = obj->m_next) {
			Coord3DBase pos;
			pos.x = obj->m_position.x;
			pos.y = obj->m_position.y;
			pos.z = obj->m_position.z;
			xfer->xferCoord3D(&pos);
		}
		return;
	}

	Rva0004224C guard;
	GameLogic *logic = (GameLogic *)((char *)this - 0x0C);
	logic->xferObjectTOC(xfer);
	if (xfer->isLoading())
		logic->prepareLogicForObjectLoad();
	unsigned int objectCount = logic->getObjectCount();
	xfer->xferUnsignedInt(&objectCount);

	Rva000411084 it;
	ObjectID id;
	Team *defaultTeam;
	if (xfer->isStoring()) {
		for (ObjectView *obj = m_objList; obj; obj = obj->m_next) {
			ObjectTOCEntry *entry = logic->findTOCEntryByName(*(AsciiString *)((char *)obj->m_template + 0x64));
			if (entry == 0)
				throwXferException();
			xfer->xferUnsignedShort((unsigned short *)((char *)entry + 4));
			id = obj->m_id;
			XferObjectID(xfer, &id);
			xfer->beginBlock("Object");
			xfer->xferSnapshot((Snapshot *)((char *)obj + 0x60));
			xfer->endBlock();
		}
	} else {
		defaultTeam = ThePlayerList->m_neutralPlayer->m_defaultTeam;
		for (unsigned int i = 0; i < objectCount; ++i) {
			unsigned short tocID;
			xfer->xferUnsignedShort(&tocID);
			AsciiString *entryName = (AsciiString *)((Rva0023E7B4 *)logic)->rva0023E7B4(tocID);
			if (entryName == 0)
				throwXferException();
			XferObjectID(xfer, &id);
			const ThingTemplate *tt = TheThingFactory->findTemplate(*entryName);
			if (tt == 0) {
				xfer->skipBlock("Object");
				continue;
			}
			AssetLoadMode mode;
			AssetList assets;
			((ThingTemplate *)tt)->GetAssetList((int)&assets, (int)&mode);
			bfmeMergeReceiverKeys((int)&assets);
			Object *obj = TheThingFactory->rva002D0A23(tt, defaultTeam, CreateMask(), id);
			xfer->beginBlock("Object");
			xfer->xferSnapshot(snapshotAt(obj, 0x60));
			xfer->endBlock();
		}
	}

	if (version.m_b < 7)
		xfer->xferSnapshot((Snapshot *)TheLinearCampaignManager);
	xfer->xferSnapshot(snapshotAt(TheCaveSystem, 0x0C));
	xfer->xferSnapshot(m_164);
	xfer->xferSnapshot(m_168);
	xfer->xferSnapshot(m_16c);
	xfer->xferSnapshot(snapshotAt(TheLargeGroupAudio, 0x0C));
	xfer->xferBool(&m_scoring);
	xfer->xferInt(&m_10c);

	if (xfer->isStoring()) {
		{
			Rva000411084 first;
			((Rva000427195 *)&m_buildableOverrides)->first(&first);
			it = first;
		}
		char *node = (char *)it.m_current;
		while (node) {
			{
				AsciiString name = *(AsciiString *)(node + 4);
				int status = *(int *)(node + 8);
				xfer->xferAsciiString(&name);
				XferBuildableStatus(xfer, &status);
			}
			it.next();
			node = (char *)it.m_current;
		}
		AsciiString empty;
		xfer->xferAsciiString(&empty);
	} else {
		if (!m_buildableOverrides.empty())
			throwXferException();
		for (;;) {
			AsciiString name;
			xfer->xferAsciiString(&name);
			if (name.isEmpty())
				break;
			int status;
			XferBuildableStatus(xfer, &status);
			m_buildableOverrides[name] = (BuildableStatus)status;
		}
	}

	xfer->xferBool(&m_8d);
	xfer->xferBool(&m_8e);
	xfer->xferBool(&m_8f);
	xfer->xferInt(&m_94);
	if (version.m_b >= 3)
		XferGameDifficulty(xfer, &m_98);
	xfer->xferUnsignedInt(&m_174);

	if (xfer->isStoring()) {
		for (ControlBarOverrideMap::iterator it = m_controlBarOverrides.begin(); it != m_controlBarOverrides.end(); ++it) {
			AsciiString value = it->second.m_bits ? *(AsciiString *)(it->second.m_bits + 0x10) : AsciiString::TheEmptyString;
			int slot = it->first.m_id;
			AsciiString key = it->first.m_name;
			xfer->xferInt(&slot).xferAsciiString(&key).xferAsciiString(&value);
		}
		int end = -1;
		xfer->xferInt(&end);
	} else {
		if (!m_controlBarOverrides.empty())
			throwXferException();
		for (;;) {
			if (version.m_b >= 5) {
				int slot;
				xfer->xferInt(&slot);
				if (slot < 0)
					break;
				AsciiString key;
				AsciiString value;
				xfer->xferAsciiString(&key).xferAsciiString(&value);
				const CommandButton *button = 0;
				if (!value.isEmpty())
					button = TheControlBar->findCommandButton(value);
				m_controlBarOverrides[(const TreeKey00242F5E &)_STL::make_pair(slot, key)].m_bits = (unsigned int)button;
			} else {
				AsciiString name;
				xfer->xferAsciiString(&name);
				if (name.isEmpty())
					break;
				AsciiString value;
				xfer->xferAsciiString(&value);
				const CommandButton *button = 0;
				if (!value.isEmpty())
					button = TheControlBar->findCommandButton(value);
				const char *rest = name.str() + 1;
				Rva0023E887Source source;
				source.m_00 = name.str()[0] - '0';
				source.m_text = rest;
				Rva0023E887 key(source);
				m_controlBarOverrides[(const TreeKey00242F5E &)key].m_bits = (unsigned int)button;
			}
		}
	}

	xfer->xferInt(&m_88);
	if (version.m_b >= 2)
		xfer->xferBool(&m_93);
	if (version.m_b >= 8)
		xfer->xferSnapshot(snapshotAt(TheDelayedExperienceLevelGrantSystem, 0x0C));
	m_158.clear();
}
