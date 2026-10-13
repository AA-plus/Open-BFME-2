// cl: /DNDEBUG /MD /EHsc /I. /ICode/Libraries/Include
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
#include "Lib/ICoord2D.h"
// ?rva00273755@Drawable@@QAEXXZ @0x00273755 179B: Drawable anim draw with verified retail literal 0.5f via rowed getter 0x00270BA8 and Anim2D width/height plus draw 0x002D7127; tail to 0x002736A8 on stale frame.
// Evidence: offsets +0x354/+0x2C/+0x64 match Rva00270025 layout, TheGameLogic+0x40 frame check, m_460/m_468/m_46C rect math, callers 0x00279734, neighbours Drawable_rva00273648.
class GameLogic
{
public:
	unsigned char m_pad[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;

class Anim2DTemplate;
class Anim2DCollection;
extern Anim2DCollection *TheAnim2DCollection;
struct Rva002D752DNode;
#define BFME_SNAPSHOT_NAME_SLOT
#include "reference/shims/moduledata/Common/Snapshot.h"
class Anim2D : public Snapshot
{
public:
    Anim2D(Anim2DTemplate *animTemplate, Anim2DCollection *collectionSystem);
    void randomizeCurrentFrame();
    void reset();
    unsigned int getCurrentFrameHeight() const;
    unsigned int getCurrentFrameWidth() const;
protected:
    virtual ~Anim2D();
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
private:
    unsigned short m_currentFrame;
    unsigned int m_lastUpdateFrame;
    Anim2DTemplate *m_template;
    unsigned char m_status;
    unsigned short m_minFrame, m_maxFrame;
    unsigned int m_framesBetweenUpdates;
    float m_alpha;
    Anim2DCollection *m_collectionSystem;
    Anim2D *m_collectionSystemNext, *m_collectionSystemPrev;
    unsigned int m_cachedWidth, m_cachedHeight;
};
class Rva002D7127 : public Anim2D
{
public:
	void rva002D7127(int x, int y, int width, int height);
};

class Rva00270025
{
public:
	virtual ~Rva00270025();
    void rva0027006C(int);
	Rva002D7127 *m_items[14];
	unsigned int m_vals[14];
};

class Rva00270BA8
{
public:
	Rva00270025 *rva00270BA8();
private:
	unsigned char m_pad[0x354];
	Rva00270025 *m_354;
};

typedef float Real;
typedef int Int;
typedef bool Bool;





class Thing;
class Rva002AA123 {public:int rva002AA123(int);};
class Player {
public:
    bool rva002AA0DE(const Thing *);
    int getBattlePlansActiveSpecific(int n) {return ((Rva002AA123*)this)->rva002AA123(n);}
    int getNumBattlePlansActive() const {return m_searchAndDestroy+m_holdTheLine+m_bombard;}
    char m_pad000[0xac];
    int m_bombard, m_holdTheLine, m_searchAndDestroy;
};
class Image
{
public:
	Int getImageWidth() const
	{
		return *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(this) + 0x24);
	}
	Int getImageHeight() const
	{
		return *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(this) + 0x28);
	}
};

class GlobalData
{
public:
	char m_pad000[0xDC];
	Coord3D m_ammoPipWorldOffset;
	char m_padE8[0x0C];
	Coord2D m_ammoPipScreenOffset;
	char m_padFC[0x9BD - 0xFC];
	Bool m_showObjectHealth;
};
extern GlobalData *TheWritableGlobalData;

class PlayerList
{
	char m_pad000[0x10];
	Player *m_localPlayer;
public:
	Player *getLocalPlayer() const { return m_localPlayer; }
};
extern PlayerList *ThePlayerList;

class InGameUI
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63(); virtual void slot64(); virtual void slot65();
	virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75(); virtual void slot76(); virtual void slot77();
	virtual void slot78(); virtual void slot79(); virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87(); virtual void slot88(); virtual void slot89();
	virtual void slot90(); virtual void slot91(); virtual void slot92();
	virtual Int getMousedOverDrawableID() const;
};
extern InGameUI *TheInGameUI;
class View
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63(); virtual void slot64(); virtual void slot65();
	virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75(); virtual void slot76(); virtual void slot77();
	virtual void slot78(); virtual void slot79(); virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual Int worldToScreen(const Coord3D *, ICoord2D *);
};
extern View *TheTacticalView;
class Display
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61();
	virtual void drawImage(const Image *, Real, Real, Real, Real, Int color = -1, Int layer = 2);
};
extern Display *TheDisplay;

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
    char m_pad000[0x14];
    Real m_boundingSphereRadius; // target Object+A8+14 = Object+BC

};

class Object
{
public:
	Player *getControllingPlayer() const;
	Bool rva0028AEF5(void **outCapacity, unsigned *outAmmo) const;
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x38);
	}
	const GeometryInfo &getGeometryInfo() const
	{
		return *reinterpret_cast<const GeometryInfo *>(reinterpret_cast<const char *>(this) + 0xA8);
	}
};

class Drawable
{
public:
    void rva00273755();
    void rva002736A8();
    void drawAmmo();
    void rva002739D1();
private:
    unsigned char m_pad000[0xfc];
    Object *m_object;
    int m_id;
    unsigned char m_pad104[0x354-0x104];
    Rva00270025 *m_354;
    unsigned char m_pad358[0x43c-0x358];
    bool m_selected;
    unsigned char m_pad43d[0x460-0x43d];
    int m_460, m_464, m_468, m_46c;
    Rva00270025 *getIconInfo() { return ((Rva00270BA8 *)this)->rva00270BA8(); }
    void killIcon(int n) { if(m_354) m_354->rva0027006C(n); }
    static Rva002D752DNode **s_animationTemplates;
    static const Image *s_fullAmmo;
    static const Image *s_emptyAmmo;
};

void Drawable::rva00273755()
{
	if (m_354 == 0)
		return;
	if (((Rva00270BA8 *)this)->rva00270BA8()->m_items[10] == 0)
		return;
	unsigned int cur = TheGameLogic->m_frame;
	unsigned int v = ((Rva00270BA8 *)this)->rva00270BA8()->m_vals[10];
	if (v >= cur) {
		int dw = m_468 - m_460;
		int w = ((Rva00270BA8 *)this)->rva00270BA8()->m_items[10]->getCurrentFrameWidth();
		int h = ((Rva00270BA8 *)this)->rva00270BA8()->m_items[10]->getCurrentFrameHeight();
		int y = m_46c - h;
		int x = (int)((float)dw * 0.5f + (float)m_460 - (float)w * 0.5f);
		((Rva00270BA8 *)this)->rva00270BA8()->m_items[10]->rva002D7127(x, y, w, h);
	} else {
		rva002736A8();
	}
}

// BFME1 cee35b7d8 Drawable_drawAmmo.cpp and ZH Drawable.cpp are semantic
// guides. Target 273808..2739D1 independently shows the 43C gate, FC Object,
// full/empty images, 28AEF5 ammo pair, 460 left edge, and UI/View/Display slots.
// Target offsets DC/F8/9BD differ from donor GlobalData. The actual writable
// singleton is used; the position aggregate keeps the donor scalar-copy shape.
void Drawable::drawAmmo()
{
    const Object *obj = m_object;
    if (!TheWritableGlobalData->m_showObjectHealth) return;
    if (!m_selected) {
        InGameUI *ui = TheInGameUI;
        if (!ui) return;
        Int drawableID = m_id;
        if (ui->getMousedOverDrawableID() != drawableID) return;
    }
    Player *localPlayer = ThePlayerList->getLocalPlayer();
    if (obj->getControllingPlayer() != localPlayer) return;
    Int numTotal, numFull;
    if (!obj->rva0028AEF5(reinterpret_cast<void **>(&numTotal), reinterpret_cast<unsigned *>(&numFull))) return;
    if (!s_fullAmmo) return;
    const Image *emptyAmmo = s_emptyAmmo;
    if (!emptyAmmo) return;
    Real scale = 1.0f;
    Int boxWidth = (Int)((Real)emptyAmmo->getImageWidth()*scale);
    Int boxHeight = (Int)((Real)emptyAmmo->getImageHeight()*scale);
    ICoord2D screenCenter;
    Coord3D pos = {obj->getPosition()->x, obj->getPosition()->y, obj->getPosition()->z};
    pos.x += TheWritableGlobalData->m_ammoPipWorldOffset.x;
    pos.y += TheWritableGlobalData->m_ammoPipWorldOffset.y;
    pos.z += TheWritableGlobalData->m_ammoPipWorldOffset.z + obj->getGeometryInfo().getMaxHeightAbovePosition();
    if (TheTacticalView->worldToScreen(&pos, &screenCenter) != 0) return;
    Real bounding = obj->getGeometryInfo().m_boundingSphereRadius*scale;
    Int posx = m_460;
    Int posy = screenCenter.y + (Int)(TheWritableGlobalData->m_ammoPipScreenOffset.y*bounding);
    for (Int i=0; i<numTotal; ++i) {
        TheDisplay->drawImage(i<numFull ? s_fullAmmo : s_emptyAmmo, posx, posy+1,
            posx+boxWidth, posy+1+boxHeight, -1, 2);
        posx += boxWidth + 1;
    }
}

// ZH Drawable::drawBattlePlans is the semantic guide (BF1 cee35b7d8);
// WB CABB10 and complete native 2739D1..273C47 establish the renderer
// relationship, target no-argument ABI, player eligibility, slots7..9,
// and native rect members460/464. Original target spelling remains unknown.
// A volatile player carrier preserves the witnessed reloads per plan;
// eligibility uses the unqualified result. Snapshot-derived Anim2D is the
// owned 52-byte class from 2D6D63, replacing the old opaque storage view.
// Capture Y then X before getIconInfo; this retains height in EAX and width
// in EDI and pushes arguments before the getter. For the third icon, capture
// only the left edge and keep left+width*2 inside the call argument.
// Native allocation, constructor, draw, kill and EH relationships all match.
void Drawable::rva002739D1()
{
	Object *obj = m_object;
	if (!obj)
		return;
	Player *active = obj->getControllingPlayer();
    Player *volatile player = active;
	if (active && active->getNumBattlePlansActive() > 0 && active->rva002AA0DE((const Thing *)obj))
	{
		if (player->getBattlePlansActiveSpecific(1))
		{
			if (!getIconInfo()->m_items[7])
				getIconInfo()->m_items[7] = (Rva002D7127 *)new Anim2D((Anim2DTemplate *)s_animationTemplates[7], TheAnim2DCollection);
			int frameWidth = getIconInfo()->m_items[7]->getCurrentFrameWidth();
			int frameHeight = getIconInfo()->m_items[7]->getCurrentFrameHeight();
			int y=m_464+frameHeight;
            int x=m_460;
            getIconInfo()->m_items[7]->rva002D7127(x,y,frameWidth,frameHeight);
		}
		else
		{
			killIcon(7);
		}

		if (player->getBattlePlansActiveSpecific(2))
		{
			if (!getIconInfo()->m_items[8])
				getIconInfo()->m_items[8] = (Rva002D7127 *)new Anim2D((Anim2DTemplate *)s_animationTemplates[8], TheAnim2DCollection);
			int frameWidth = getIconInfo()->m_items[8]->getCurrentFrameWidth();
			int frameHeight = getIconInfo()->m_items[8]->getCurrentFrameHeight();
			int y=m_464+frameHeight;
            int x=m_460 + frameWidth;
            getIconInfo()->m_items[8]->rva002D7127(x,y,frameWidth,frameHeight);
		}
		else
		{
			killIcon(8);
		}

		if (player->getBattlePlansActiveSpecific(3))
		{
			if (!getIconInfo()->m_items[9])
				getIconInfo()->m_items[9] = (Rva002D7127 *)new Anim2D((Anim2DTemplate *)s_animationTemplates[9], TheAnim2DCollection);
			int frameWidth = getIconInfo()->m_items[9]->getCurrentFrameWidth();
			int frameHeight = getIconInfo()->m_items[9]->getCurrentFrameHeight();
			int y=m_464+frameHeight;
            int x=m_460;
            getIconInfo()->m_items[9]->rva002D7127(x+frameWidth*2,y,frameWidth,frameHeight);
		}
		else
		{
			killIcon(9);
		}
	}
}
