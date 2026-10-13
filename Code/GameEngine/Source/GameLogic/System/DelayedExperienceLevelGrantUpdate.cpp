// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/moduledata /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Update slot of the delayed experience-level grant queue (xfer lives in DelayedExperienceLevelGrantXfer.cpp).
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
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString &); };
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
enum ObjectStatusTypes { OBJECT_STATUS_58 = 0x58 };
class Object {
public:
    bool testStatus(ObjectStatusTypes) const;
    unsigned char isEffectivelyDead() const { return m_privateStatus & 1; }
public:
    unsigned char unknown000[0x438];
    unsigned char m_privateStatus; // +0x438
};
class DelayedExperienceLevelGrantSystem : public GameEngineDeletingBase, public Snapshot {
public:
    virtual void xfer(Xfer *);
    virtual void update();
    void rva00420C8E(struct ExperienceLevelView *level, Object *obj, bool grant);
private:
    _STL::list<BfmePod12> entries;
    bool loading;
};
// Retail 0x00420EB3..0x00420F0E (91 bytes), slot 10 (update) of the primary
// table 0x00C3BDC4 beside reset 0x00420B55: each queued entry whose object
// still exists, and is not effectively dead unless it carries status 0x58,
// gets its level applied by 0x00420C8E (unrowed, pinned from this call);
// then the queue is emptied through the same folded list clear xfer uses.
// The GameLogic receiver as an equal-arm conditional (late-folded ?:) reproduces retail's
// register order for the findObjectByID call (W7-R1 lever).
void DelayedExperienceLevelGrantSystem::update() {
    for (_STL::list<BfmePod12>::iterator it=entries.begin(); it!=entries.end(); ++it) {
        Object *obj = (TheGameLogic ? TheGameLogic : TheGameLogic)->findObjectByID(it->object);
        if (obj && !(obj->isEffectivelyDead() && !obj->testStatus(OBJECT_STATUS_58)))
            rva00420C8E((ExperienceLevelView *)it->level, obj, it->grant);
    }
    reinterpret_cast<_STL::_List_base<int,_STL::allocator<int> > *>(&entries)->clear();
}
