// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Complete ZH ControlBarCommand.cpp is the semantic guide. Named target WB
// 11180A0, assert file ControlBarCommand.cpp1005..1216, and native
// 53CF65..53D3551008 establish the target deltas and ten-case jump table.
// WB's 11188D0 template-overlay helper always returns null, and retail
// retains the template-query side effect before resetting the overlay to0.
// stlport
#include <vector>
typedef unsigned int UnsignedInt;
class ThingTemplate;
class Object;
class GameWindow;
class CommandSet { public: const class CommandButton *getCommandButton(int) const; };
struct CommandInventoryData { int current,last; GameWindow **windows; Object *transport; };

class GameWindow {
public:
    int winHide(bool); bool winIsHidden(); int winEnable(bool);
    unsigned int winSetStatus(unsigned int); unsigned int winClearStatus(unsigned int);
    unsigned int winGetStatus();
};
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
class CommandWindowManagerView {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual GameWindow *getWindow(GameWindow *, int);
};
struct CommandContainedQueryView;
class CommandContainView {
public:
    virtual void slot0();
    virtual void *asOpenContain();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual int getContainMax();
    virtual void slot29();
    virtual void slot30();
    virtual CommandContainedQueryView *rva0053BA4DQuery();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual int getExtraSlotsInUse();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void iterateContained(void (__cdecl *)(Object *,void *),void *,bool);
    virtual int getContainCount(int);
};
struct CommandProductionEntry { char unknown00[0x14]; float percent; };
class CommandProductionView {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual const CommandProductionEntry *firstProduction();
};
class Object {
public:
    int rva0028FBBE();
    void *rva0028BC58(int);
    bool isLocallyControlled() const;
};
struct CommandObjectView {
    char unknown00[4]; const char *objectTemplate;
    char unknown08[0x250-8]; CommandContainView *contain;
};
struct CommandDrawableView { char unknown00[0xFC]; Object *object; };
class BfmeMemberRV { public: bool bfmeAskRV(); };
class PlayerList;
extern PlayerList *ThePlayerList;
struct CommandPlayerListView { char unknown00[0x10]; BfmeMemberRV *localPlayer; };
class Gen_003bcb40 { public: void m(int); };
class CommandButton {
public:
    const ThingTemplate *rva0035B570() const;
    unsigned int options() const { return *(const unsigned int *)((const char *)this + 0x1C); }
    int type() const { return *(const int *)((const char *)this + 0x14); }
    bool enabled() const { return *((const unsigned char *)this + 0x105) != 0; }
};
void *GadgetButtonGetData(GameWindow *);
void GadgetButtonSetDisallowed(GameWindow *, int);
void GadgetCheckLikeButtonSetVisualCheck(GameWindow *, bool);
void Rva003284ED(GameWindow *, int);
void Rva003284B9(GameWindow *, int, int);
class ControlBar {
protected:
    void updateContextCommand();
    static void populateInvDataCallback(Object *,void *);
public:
    int rva0053BA87(const CommandButton *,Object *) const;
    void rva0053BB16(Object *,CommandSet *);
    void setControlCommand(GameWindow *,const CommandButton *);
    void rva0031D230();
    int rva0053BD66(const CommandButton *, GameWindow *, Object *, float *, bool) const;
private:
    char unknown00[0x50]; GameWindow *queueParent;
    char unknown54[0x6C-0x54]; CommandDrawableView *selected;
    char unknown70[0x80-0x70]; int lastInventoryCount;
    char unknown84[0xDC-0x84]; GameWindow *windows[32];
    char unknown15C[0x208-0x15C]; int clockColor;
};
// ?updateContextCommand@ControlBar@@IAEXXZ
void ControlBar::updateContextCommand()
{
    Object *obj = 0;
    if (selected) obj = selected->object;
    CommandContainView *contain = obj ? ((CommandObjectView *)obj)->contain : 0;
    if (contain && contain->getContainMax() > 0 && lastInventoryCount != contain->getContainCount(0)) {
        lastInventoryCount = contain->getContainCount(0);
        rva0031D230();
    }
    CommandProductionView *production = obj ? (CommandProductionView *)obj->rva0028BC58(0) : 0;
    if (queueParent->winIsHidden() == false) {
        ((Gen_003bcb40 *)this)->m(0);
        if (production) {
            const CommandProductionEntry *entry = production->firstProduction();
            if (entry) {
                static unsigned int winID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonQueue01");
                GameWindow *window = ((CommandWindowManagerView *)TheWindowManager)->getWindow(queueParent, winID);
                Rva003284B9(window, (int)entry->percent, clockColor);
            }
        }
    }
    bool locallyControlled = obj ? obj->isLocallyControlled() : false;
    for (int i = 0; i < 32; ++i) {
        GameWindow *win = windows[i];
        if (!win) continue;
        const CommandButton *command = (const CommandButton *)GadgetButtonGetData(win);
        if (!command) continue;
        float percent = 0;
        int availability = rva0053BD66(command, win, obj, &percent, false);
        bool disable = false;
        bool forceVisible = false;
        bool spectator = false;
        if (!locallyControlled) {
            if (((CommandPlayerListView *)ThePlayerList)->localPlayer->bfmeAskRV()) {
                spectator = true;
                if (availability != 0 && availability != 3 && availability != 4) {
                    forceVisible = true;
                    availability = 0;
                }
            } else disable = true;
        }
        if (availability == 3 && win->winIsHidden()) continue;
        if (availability == 0 && (command->options() & 0x00400000) && !forceVisible)
            availability = 3;
        win->winClearStatus(0x00400000);
        win->winClearStatus(0x01000000);
        win->winClearStatus(0x40000000);
        win->winClearStatus(0x80000000);
        GadgetButtonSetDisallowed(win, 0);
        if (command->type() == 0x10 && (locallyControlled || disable)) {
            if (obj && (*(const unsigned int *)(((CommandObjectView *)obj)->objectTemplate + 0x11C) & 0x80000000) && availability == 0) {
                win->winEnable(false);
                win->winClearStatus(8);
                win->winSetStatus(0x80000000);
            } else {
                win->winSetStatus(8);
                win->winSetStatus(0x01000000);
                if (availability == 3) win->winHide(true);
            }
            continue;
        }
        bool hide = false;
        int color = 0;
        switch (availability) {
        case 3: hide = true; break;
        case 0: case 4: case 8:
            win->winEnable(false); win->winSetStatus(0x80000000);
            if (availability == 4) GadgetButtonSetDisallowed(win, 1);
            if (availability == 8) win->winSetStatus(0x01000000);
            break;
        case 5:
            color = clockColor; win->winEnable(false); win->winSetStatus(0x00400000); break;
        case 6: case 7:
            win->winEnable(false); win->winSetStatus(0x01000000); break;
        case 9:
            color = clockColor; win->winEnable(true); win->winSetStatus(0x00400000); break;
        default: win->winEnable(true); break;
        }
        if (color < 1.0f && !spectator) Rva003284B9(win, (int)(percent * 100.0f), color);
        if (disable && (win->winGetStatus() & 8)) {
            win->winEnable(false); win->winSetStatus(0x40000000);
        }
        win->winHide(hide);
        if (!command->enabled()) win->winEnable(false);
        command->rva0035B570();
        Rva003284ED(win, 0);
        if (command->options() & 0x400) {
            if (availability == 2) GadgetCheckLikeButtonSetVisualCheck(win, true);
            else GadgetCheckLikeButtonSetVisualCheck(win, false);
        }
    }
}

// ?rva0053BB16@ControlBar@@QAEXPAVObject@@PAVCommandSet@@@Z
// Whole native53BB16..53BC7E360, WB1116DA0/595 and complete ZH file
// establish the transport inventory workflow. Native keeps both contain
// queries for side effects, uses open+DE and32 slots, and passes true to
// iteration. The callback data's native order is current/last/windows/obj.
void ControlBar::rva0053BB16(Object *transport,CommandSet *set)
{
    if(!transport||!set)return;
    CommandContainView *contain=((CommandObjectView *)transport)->contain;
    if(!contain)return;
    void *open=contain->asOpenContain();
    if(open&&!*(bool *)((char *)open+0xDE))return;
    contain->getContainMax();
    contain->getExtraSlotsInUse();
    int first=-1,last=-1;
    for(int i=0;i<32;++i){
        const CommandButton *button=set->getCommandButton(i);
        if(button&&button->type()==0x10){
            if(first==-1)first=i;
            last=i;
            if(windows[i]){
                windows[i]->winHide(false);
                windows[i]->winEnable(false);
                windows[i]->winClearStatus(0x200);
                Rva003284ED(windows[i],0);
                if(*((unsigned char *)transport+0x1C8)&0x20)windows[i]->winHide(true);
                setControlCommand(windows[i],button);
                if(*((unsigned char *)button+0x101))windows[i]->winSetStatus(0x4000000);
                else windows[i]->winClearStatus(0x4000000);
            }
        }
    }
    if(last>=0){
        CommandInventoryData data;
        data.windows=windows;data.current=first;data.last=last;data.transport=transport;
        contain->iterateContained(populateInvDataCallback,&data,true);
    }
    lastInventoryCount=contain->getContainCount(0);
}

// Retail53B946..53B96632B and WB111BFD0/49 prove this callback.
// Native availability53C040 passes it to the Castle owned-object iterator
// with a copied seven-word kind mask followed by a boolean result.
template<int N> class BitFlags;
class Thing { public: bool isAnyKindOf(const BitFlags<69> &) const; };
struct CommandCastleKindFilter { unsigned int mask[7]; bool matched; };
// ?Rva0053B946@@YAHPAVObject@@PAUCommandCastleKindFilter@@@Z
int __cdecl Rva0053B946(Object *object,CommandCastleKindFilter *filter)
{
    if(((Thing *)object)->isAnyKindOf(*(const BitFlags<69> *)filter->mask)){
        filter->matched=true;
        return 0;
    }
    return 1;
}

// Target WB1116A60 and native53B98C..53BA4D identify this static callback.
// ZH establishes its purpose; BFME2 repeats slots for the native object count,
// stores ObjectID at74 and enables only the first slot.
class Image;
const Image *__cdecl getButtonImage(ThingTemplate *, Object *);
void __cdecl GadgetButtonSetEnabledImage_Rva002C0433(GameWindow *, const Image *);
struct ControlBarInventoryEntry { GameWindow *window; int objectID; };
// Native32-slot window/ObjectID array atVA E05E20; zero-filled image storage.
// Shared by population, construction update, lookup, command processing and reset.
ControlBarInventoryEntry ControlBarInventoryEntries[32];


// ?populateInvDataCallback@ControlBar@@KAXPAVObject@@PAX@Z
void __cdecl ControlBar::populateInvDataCallback(Object *obj, void *infoParam)
{
	CommandInventoryData *info = (CommandInventoryData *)infoParam;
	if (info->current > info->last)
		return;
	ThingTemplate *tmpl = *(ThingTemplate **)((char *)obj + 4);
	const Image *img = getButtonImage(tmpl, obj);
	int count = obj->rva0028FBBE();
	int i = 0;
	if (count <= 0)
		return;
	do {
		GameWindow *w = info->windows[info->current];
		ControlBarInventoryEntries[info->current].window = w;
		ControlBarInventoryEntries[info->current].objectID = *(int *)((char *)obj + 0x74);
		info->current++;
		GadgetButtonSetEnabledImage_Rva002C0433(w, img);
		Rva003284ED(w, 0);
		if (i == 0) {
			w->winEnable(true);
			w->winSetStatus(8);
			w->winClearStatus(0x200);
		}
		else {
			w->winEnable(false);
			w->winClearStatus(8);
			w->winSetStatus(0x200);
		}
		i++;
	} while (i < count);
}

// Native53D9DC's local window-pointer vector is constructed through211E58.
// Explicitly instantiate only its empty base-header constructor from STLport.
template _STL::_Vector_base<GameWindow *, _STL::allocator<GameWindow *> >::_Vector_base(const _STL::allocator<GameWindow *> &);

// Native callback53BA4D..53BA87: cdecl(Object*,void*), complete58B.
// Availability53BD66 passes its address to contain iteration in case10.
// The query's purpose remains unknown: only slot7C/slotF4 and AL are proven.
class CommandContainedQueryView {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual bool queryF4();
};
// ?Rva0053BA4D@@YAXPAVObject@@PAX@Z
void __cdecl Rva0053BA4D(Object *object,void *userData)
{
    const char *objectTemplate=((CommandObjectView *)object)->objectTemplate;
    if(((const unsigned char *)objectTemplate)[0x115]&0x20){
        CommandContainView *contain=((CommandObjectView *)object)->contain;
        if(contain){
            CommandContainedQueryView *query=contain->rva0053BA4DQuery();
            if(query&&!query->queryF4())
                *((bool *)((char *)userData+4))=true;
        }
    }
}

class ModelConditionFlags
{
public:
	bool rva000B3EB3() const;
};

class Rva00263546
{
public:
	bool rva00263546(const Rva00263546 *other) const;
};

// ?rva0053BA87@ControlBar@@QBEHPBVCommandButton@@PAVObject@@@Z @0x0053BA87 90B
// Target evidence: checks ModelConditionFlags at first+0x1E0 and first+0x194 through
// rowed 0x000B3EB3; tests each against second+0x10C through rowed 0x00263546; returns 3
// for the first overlap or the second non-overlap and 2 otherwise.
// Native callers53BE4B/53CBA9/53CBC2 load ControlBar in ECX then push Object and
// CommandButton. WB1118910 stores its ECX receiver and returns with RET8.
// Target member ABI and argument roles are proven by these callers; const qualification
// follows the const parent call context. The method name remains address-derived.
int ControlBar::rva0053BA87(const CommandButton *firstOwner, Object *secondOwner) const
{
	ModelConditionFlags *firstFlags = (ModelConditionFlags *)((char *)firstOwner + 0x1E0);
	if (firstFlags->rva000B3EB3()
		&& ((Rva00263546 *)((char *)secondOwner + 0x10C))->rva00263546((const Rva00263546 *)firstFlags))
		return 3;

	ModelConditionFlags *secondFlags = (ModelConditionFlags *)((char *)firstOwner + 0x194);
	if (secondFlags->rva000B3EB3()
		&& !((Rva00263546 *)((char *)secondOwner + 0x10C))->rva00263546((const Rva00263546 *)secondFlags))
		return 3;

	return 2;
}
