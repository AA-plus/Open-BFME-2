// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /ICode/GameEngine/Source/GameLogic/System /Ireference/shims/moduledata /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00420F3F..0x00421084 (325 bytes), secondary Snapshot transfer.
// WB 0x01292D20 names DelayedExperienceLevelGrantSystem::DoXfer and asserts
// entry.experienceLevel != NULL. Retail's 0x00420E67 destructor proves the
// primary 12-byte system base, Snapshot at +0x0C, list at +0x10 and load flag
// at +0x14. MSVC's secondary-base override uses Snapshot-relative this.
// GameEngine::init registers 0x00DFECC4 as TheExperienceLevelSystem.
// The owned 0x0028951F lookup resolves its level NameKey; level +0x10 is an
// AsciiString copied through StringBase<char>'s 0x000365F0 constructor.
// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f's named level lookup
// corroborates the NameKey / level relationship; retail bytes establish ABI.
#include "ascii_string.h"
#include <list>
// Compare nodes directly instead of emitting a competing iterator-base copy.
namespace _STL {
template<class T, class L, class R>
static inline bool operator!=(const _List_iterator<T,L> &a, const _List_iterator<T,R> &b)
{ return a._M_node != b._M_node; }
}
#include "Common/Snapshot.h"
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString &); NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Overridable;
class Rva0028951F { public: const Overridable *rva0028951F(int); };
class ExperienceLevelSystem;
ExperienceLevelSystem *TheExperienceLevelSystem = 0;
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Xfer;
void XferObjectID(Xfer *, ObjectID *);
struct GrantVersion { GrantVersion(unsigned char a,unsigned char b):minimum(a),current(b){} unsigned char minimum,current; };
class Xfer { public: virtual ~Xfer();
virtual bool IsLoading() const;
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual Xfer &xferVersion(GrantVersion *);
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
virtual Xfer &xferAsciiString(AsciiString *);
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual Xfer &xferInt(int *);
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual Xfer &xferBool(bool *);
};
// Reuse the ledger-owned 12-byte list footprint (push_back at 0x00420DF3).
struct BfmePod12 { ObjectID object; const Overridable *level; bool grant; };
template<> void _STL::list<BfmePod12>::push_back(const BfmePod12 &);
template<> void _STL::_List_base<int,_STL::allocator<int> >::clear();
struct GrantLevelNameView { unsigned char unknown[0x10]; AsciiString name; };
class GameEngineDeletingBase { public: virtual ~GameEngineDeletingBase(); private: char unknown04[8]; };
#include <vector>

class Module;
class ModelConditionFlags {public: bool rva000B3EB3()const; int words[19];};
struct Rva0039B2E6Input;
class Rva0039B2E6 {public:void rva0039B2E6(const Rva0039B2E6Input &);};
class Rva001E431E {public:void rva001E431E(const int *);};
class Rva00496CA8 {public:void rva00496CA8(int);};
class CreateAHeroHero {public:bool UpdateCommandSet(unsigned);};
class CreateAHeroManager {public:void *rva002197A6(int);};
extern CreateAHeroManager *TheCreateAHeroManager;
extern int g_Va00DBA4E4;
enum ModelConditionFlagType { GRANT_LEVEL_FX=0xd2 };
struct GrantTemplateView {char unknown[0x11f];unsigned char flags;};
struct GrantLogicFrameView {char unknown[0x40];unsigned frame;};
struct GrantApplyLevelView {
 char unknown[0x30];
 _STL::vector<AsciiString> attributes;
 char gap3c[0x10];
 _STL::vector<void*> upgrades;
 ModelConditionFlags modelConditions;
 char gapA4[0x58];
 unsigned rank;
 bool banner;
 char gap101[3];
 int emotion;
};

enum ObjectStatusTypes { OBJECT_STATUS_58 = 0x58 };
class Object {
public:
    bool testStatus(ObjectStatusTypes) const;
    bool addAttributeModifierToPool(const AsciiString &,int);
    void rva00293077(const void *);
    void setSpecialModelConditionState(ModelConditionFlagType,unsigned);
    void rva0028EC68(int,void *,int);
protected:
    Module *findModule(NameKeyType)const;
    friend class DelayedExperienceLevelGrantSystem;
public:
    GrantTemplateView *getTemplate()const{return m_template;}
    int getObjectKey()const{return m_objectKey;}
    Rva0039B2E6 *getTracker()const{return m_tracker;}
    unsigned char isEffectivelyDead() const { return m_privateStatus & 1; }
private:
    unsigned char unknown000[4];
    GrantTemplateView *m_template;
    char unknown008[0x74-8];
    int m_objectKey;
    char unknown078[0x264-0x78];
    Rva0039B2E6 *m_tracker;
    char unknown268[0x438-0x268];
    unsigned char m_privateStatus; // +0x438
};
class DelayedExperienceLevelGrantSystem : public GameEngineDeletingBase, public Snapshot {
public:
    virtual void xfer(Xfer *);
    virtual void update();
    void rva00420B61(const Overridable *,Object *);
    void rva00420C8E(const Overridable *level, Object *obj, bool grant);
private:
    _STL::list<BfmePod12> entries;
    bool loading;
};
void DelayedExperienceLevelGrantSystem::xfer(Xfer *xfer) {
    GrantVersion version(1,1);
    xfer->xferVersion(&version);
    if (xfer->IsLoading()) {
        // Retail uses the already-owned folded int list clear at 0x0023DAA5.
        reinterpret_cast<_STL::_List_base<int,_STL::allocator<int> > *>(&entries)->clear();
        loading = true;
        int count;
        xfer->xferInt(&count);
        while (count > 0) {
            BfmePod12 entry;
            XferObjectID(xfer,&entry.object);
            xfer->xferBool(&entry.grant);
            AsciiString name;
            xfer->xferAsciiString(&name);
            entry.level = reinterpret_cast<Rva0028951F *>(TheExperienceLevelSystem)->rva0028951F(TheNameKeyGenerator->nameToKey(name));
            if (entry.level) entries.push_back(entry);
            --count;
        }
    } else {
        int count = entries.size();
        xfer->xferInt(&count);
        _STL::list<BfmePod12>::iterator end=entries.end();
        for (_STL::list<BfmePod12>::iterator it=entries.begin();it._M_node!=end._M_node;) {
            XferObjectID(xfer,&it->object);
            xfer->xferBool(&it->grant);
            AsciiString name(reinterpret_cast<const GrantLevelNameView *>(it->level)->name);
            xfer->xferAsciiString(&name);
            ++it;
        }
    }
}

// Native 0x00420C8E..0x00420DF3, complete 357B including RET12.
// WB 0x01292920 supplies the two indexed loops, hero command update, optional
// level FX, tracker, model flags, banner and emotion branches. Its helper name
// is absent: keep an honest address-derived member name. Retail accesses alone
// establish the borrowed level/object field offsets; no complete layout claim.
// The legacy queue-update note's 355B extent omitted RET12's two operand bytes.
// Same-unit definition did not close that update's EBX/EBP allocation residue.
// BFME1 cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 confirms the pending-record
// phase and level application purpose; BFME2 adds hero/banner/upgrade behavior.
// The FX helper00420B61 is target-admitted but still lacks a C++ provider.
void DelayedExperienceLevelGrantSystem::rva00420C8E(const Overridable *data,Object *obj,bool grant) {
 const GrantApplyLevelView *level=(const GrantApplyLevelView *)data;
 for(unsigned i=0;i<level->attributes.size();++i)
  obj->addAttributeModifierToPool(level->attributes[i],-1);
 for(unsigned j=0;j<level->upgrades.size();++j)
  obj->rva00293077(level->upgrades[j]);
 if(obj->getTemplate()->flags&0x40) {
  CreateAHeroHero *hero=(CreateAHeroHero *)TheCreateAHeroManager->rva002197A6(obj->getObjectKey());
  if(hero)hero->UpdateCommandSet(level->rank);
 }
 unsigned frame=((const GrantLogicFrameView *)TheGameLogic)->frame;
 if(grant && frame>=10) {
  rva00420B61(data,obj);
  obj->setSpecialModelConditionState(GRANT_LEVEL_FX,g_Va00DBA4E4*3);
 }
 obj->getTracker()->rva0039B2E6(*(const Rva0039B2E6Input *)data);
 if(level->modelConditions.rva000B3EB3())
  ((Rva001E431E *)obj)->rva001E431E(level->modelConditions.words);
 if(level->banner) {
  static NameKeyType bannerKey=TheNameKeyGenerator->nameToKey("BannerCarrierUpdate");
  Module *banner=obj->findModule(bannerKey);
  if(banner)((Rva00496CA8 *)banner)->rva00496CA8(level->rank);
 }
 if(level->emotion!=-1)obj->rva0028EC68(level->emotion,0,1);
}
