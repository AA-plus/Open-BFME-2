// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native272A6A..272AD5:107B cdecl Object*, callback context*.
// WB CA3EF0 is the corresponding unnamed callback in Drawable.cpp;
// WB CA3700 names its caller Drawable::onComingOutOfShroud.
// The context is a Drawable pointer followed by its sighted-event integer.
// Target facts: Drawable template4/obscured440, Object template4/status438,
// ThingTemplate event59C/kind47. WB offsets differ; no donor layout is used.
// The original callback spelling remains unknown.
class Drawable;
class Player;
class ThingTemplate
{
public:
    __forceinline bool isKindOf(int kind) const
    { return (kindOf[kind >> 3] & (1 << (kind & 7))) != 0; }
    char pad000[0x108];
    unsigned char kindOf[0x20];
    char pad128[0x59C - 0x128];
    int sightedEvent;
};
class Object
{
public:
    Drawable *getDrawable() const;
    bool rva00294471(void *player, int mode);
    const ThingTemplate *getTemplate() const { return thingTemplate; }
    bool isEffectivelyDead() const { return (status & 1) != 0; }
private:
    void *vptr;
    const ThingTemplate *thingTemplate;
    char pad008[0x438 - 8];
    unsigned char status;
};
class Drawable
{
public:
    const ThingTemplate *getTemplate() const { return thingTemplate; }
private:
    void *vptr;
    const ThingTemplate *thingTemplate;
};
struct BfmeDrawableSightedView
{
    char pad000[0x440];
    unsigned char obscured;
};
class PlayerList
{
public:
    Player *getLocalPlayer() const { return localPlayer; }
private:
    char pad000[0x10];
    Player *localPlayer;
};
extern PlayerList *ThePlayerList;
struct BfmeSightedEventContext
{
    Drawable *drawable;
    int event;
};

int rva00272A6A(Object *object, void *userData)
{
    if (!object) goto reject;
    Drawable *drawable = object->getDrawable();
    BfmeSightedEventContext *context = (BfmeSightedEventContext *)userData;
    if (drawable == context->drawable || !drawable ||
        ((BfmeDrawableSightedView *)drawable)->obscured) goto reject;
    const ThingTemplate *thingTemplate = drawable->getTemplate();
    if (!thingTemplate || thingTemplate->sightedEvent != context->event ||
        object->isEffectivelyDead()) goto reject;
    if (!object->rva00294471(ThePlayerList->getLocalPlayer(), 1)) goto reject;
    if (object->getTemplate()->isKindOf(47)) goto reject;
    return 0;
reject:
    return 1;
}

// Native2706F0..27070C: complete28B cdecl callback; its address is passed
// by the native onComingOutOfShroud body at278B90 to the member iterator.
// Existing72B owner2706A8 ends immediately before it; rowed74B27070C
// begins immediately after it. The callback sets the drawable status bit40
// and returns1. Its original name and the unused second argument are unknown.
struct BfmeDrawableStatus114View
{
    char pad000[0x114];
    unsigned int status;
};
int rva002706F0(Object *object, int unused)
{
    if (object)
    {
        Drawable *drawable = object->getDrawable();
        if (drawable)
            ((BfmeDrawableStatus114View *)drawable)->status |= 0x40;
    }
    return 1;
}
