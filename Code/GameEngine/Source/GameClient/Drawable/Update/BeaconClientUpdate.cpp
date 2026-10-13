// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// BFME2 BeaconClientUpdate smoke helper355B at4C9674 and hideBeacon216B at4C97D7.
// Clean ZH BeaconClientUpdate.cpp and BF1 cee35b7d8
// BeaconClientUpdateClientUpdate.cpp supply the semantic/structural guide.
// Target literals BeaconSmoke%6.6X / BeaconSmokeFFFFFF, DrawableFC Object,
// Object indicator-color callback28B026, particle factory/lookup callbacks,
// and target setters independently support identity. Target ParticleSystem
// ID+A8 and InGameUI deselect slot67 differ from the donor and are measured.
// The same-TU static helper receives Drawable in ESI, result storage on stack;
// retaining hideBeacon in this TU reproduces that compiler-private convention.
// Factories and handle assignment retain donor throw() contracts; target has
// no temporary EH states around their calls. Owned RvaSmartPtr12 copy/assign/
// unlink are reused, with opaque setter names retained where identity is unknown.
// clientUpdate225B at4C98AF uses the existing writable
// g_secondsPerLogicFrame owner from INI_parseAccelerationReal.cpp atDBA4F8.

#include "Lib/Coord3D.h"
#include "ascii_string.h"
enum ParticleSystemID
{
    INVALID_PARTICLE_SYSTEM_ID = 0
};
class ParticleSystem
{
  public:
    char pad[0xa8];
    ParticleSystemID id;
};
ParticleSystem *Make001FCBD7();
class RvaSmartPtr12
{
  public:
    RvaSmartPtr12(const RvaSmartPtr12 &);
    RvaSmartPtr12 &operator=(const RvaSmartPtr12 &) throw();
    void rva0004CBC0() throw();
    char bytes[12];
};
class BfmeParticleSystemHandle
{
  public:
    BfmeParticleSystemHandle() : system(0), previous(0), next(0)
    {
    }
    __forceinline BfmeParticleSystemHandle(const BfmeParticleSystemHandle &r)
    {
        ((RvaSmartPtr12 *)this)->RvaSmartPtr12::RvaSmartPtr12(*(const RvaSmartPtr12 *)&r);
    }
    __forceinline BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &r) throw()
    {
        *(RvaSmartPtr12 *)this = *(const RvaSmartPtr12 *)&r;
        return *this;
    }
    __forceinline ~BfmeParticleSystemHandle() throw()
    {
        if (system)
            ((RvaSmartPtr12 *)this)->rva0004CBC0();
    }
    operator bool() const
    {
        return system != 0;
    }
    ParticleSystem *operator->() const
    {
        return system ? system : Make001FCBD7();
    }
    ParticleSystem *system;
    BfmeParticleSystemHandle *previous, *next;
};
class BeaconClientUpdate;
class ParticleSystemTemplate;
class ParticleSystemManager
{
    friend class BeaconClientUpdate;

  public:
    ParticleSystemTemplate *findTemplate(const AsciiString &) const;
    BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *, bool) throw();

  private:
    BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID) throw();
};
extern ParticleSystemManager *TheParticleSystemManager;
class Rva0055A88BDwordField;
class Rva001F3C20Slot
{
  public:
    void set(const Rva0055A88BDwordField *);
};
struct Rva001F3899Arg;
class Rva001F3899Slot
{
  public:
    void set(const Rva001F3899Arg &);
};
class Rva001F3852ByteOneSetter
{
  public:
    void enable();
};
class Object
{
  public:
    int getIndicatorColor() const;
};
class Drawable
{
  public:
    char pad[0xfc];
    Object *object;
    void setDrawableHidden(bool);
    void rva00272A02(bool);
    void setSelectable(bool);
    const Coord3D *getPosition() const;
};
class Rva00270260
{
  public:
    bool rva00270260();
};
class Thing
{
  public:
    void setPositionZ(float);
};
class InGameUI;
extern InGameUI *TheInGameUI;
struct BeaconUIView
{
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void deselectDrawable(Drawable *);
};
class GameLogic;
extern GameLogic *TheGameLogic;
struct ClockView
{
    char pad[0x40];
    unsigned frame;
};
enum RadarEventType
{
    RADAR_EVENT_BEACON_PULSE = 6
};
class Radar
{
  public:
    void createEvent(const Coord3D *, RadarEventType, float);
};
extern Radar *TheRadar;

struct BeaconClientUpdateModuleData
{
    char pad[8];
    unsigned framesBetweenRadarPulses, radarPulseDuration;
};
class BeaconClientUpdate
{
  public:
    virtual void clientUpdate();
    void hideBeacon();
    const BeaconClientUpdateModuleData *data;
    Drawable *draw;
    ParticleSystemID id;
    unsigned lastRadarPulse;
};
static BfmeParticleSystemHandle createParticleSystem(Drawable *draw)
{
    BfmeParticleSystemHandle system;
    if (draw)
    {
        Object *obj = draw->object;
        if (obj)
        {
            AsciiString name;
            name.format("BeaconSmoke%6.6X", 0xffffff & obj->getIndicatorColor());
            const ParticleSystemTemplate *particleTemplate =
                TheParticleSystemManager->findTemplate(name);
            if (particleTemplate)
            {
                system = TheParticleSystemManager->createParticleSystem(particleTemplate, true);
                if (system)
                {
                    Coord3D offset;
                    offset.x = 0;
                    offset.y = 0;
                    offset.z = 3;
                    ((Rva001F3C20Slot *)system.operator->())
                        ->set((const Rva0055A88BDwordField *)draw);
                    ((Rva001F3899Slot *)system.operator->())->set(*(const Rva001F3899Arg *)&offset);
                }
            }
            else
            {
                name.format("BeaconSmokeFFFFFF");
                const ParticleSystemTemplate *failsafeTemplate =
                    TheParticleSystemManager->findTemplate(name);
                if (failsafeTemplate)
                {
                    system = TheParticleSystemManager->createParticleSystem(failsafeTemplate, true);
                    if (system)
                        ((Rva001F3C20Slot *)system.operator->())
                            ->set((const Rva0055A88BDwordField *)draw);
                }
            }
        }
    }
    return system;
}
void BeaconClientUpdate::hideBeacon()
{
    Drawable *drawable = draw;
    if (drawable)
    {
        drawable->setDrawableHidden(true);
        drawable->rva00272A02(false);
        drawable->setSelectable(false);
        ((BeaconUIView *)TheInGameUI)->deselectDrawable(drawable);
    }
    BfmeParticleSystemHandle system;
    if (drawable && id == INVALID_PARTICLE_SYSTEM_ID)
    {
        system = createParticleSystem(drawable);
        if (system)
            id = system->id;
    }
    if (id != INVALID_PARTICLE_SYSTEM_ID)
    {
        BfmeParticleSystemHandle system = TheParticleSystemManager->findParticleSystemByID(id);
        if (system)
            ((Rva001F3852ByteOneSetter *)system.operator->())->enable();
    }
}

extern float g_secondsPerLogicFrame;
void BeaconClientUpdate::clientUpdate()
{
    Drawable *drawable = draw;
    if (!drawable)
        return;
    if (id == INVALID_PARTICLE_SYSTEM_ID)
    {
        BfmeParticleSystemHandle system = createParticleSystem(drawable);
        if (system)
            id = system->id;
    }
    if (!((Rva00270260 *)drawable)->rva00270260())
    {
        const BeaconClientUpdateModuleData *md = data;
        if (((ClockView *)TheGameLogic)->frame > lastRadarPulse + md->framesBetweenRadarPulses)
        {
            TheRadar->createEvent(drawable->getPosition(), RADAR_EVENT_BEACON_PULSE,
                                  md->radarPulseDuration * g_secondsPerLogicFrame);
            lastRadarPulse = ((ClockView *)TheGameLogic)->frame;
        }
    }
    else
    {
        drawable->setSelectable(false);
        ((BeaconUIView *)TheInGameUI)->deselectDrawable(drawable);
        ((Thing *)drawable)->setPositionZ(-100.0f);
    }
}
