// ?rva00439965@Rva00243177@@QAEXXZ
// partial score=0.93 date=2026-10-13
// ?rva00439965@Rva00243177@@QAEXXZ
// partial score=0.93 date=2026-10-13
// ?rva00439965@Rva00243177@@QAEXXZ
// partial score=0.9 date=2026-10-12
// ?rva00439E0C@Rva00439E0C@@QAE_NPAVObject@@0HH@Z, retail 0x00439E0C (307 bytes),
// WorldBuilder's InvisibilityManager::detected (explicit WB boundary 0x00839E0C).
// Finds or creates the object's detection record in the manager's int-keyed map
// (subscript 0x00439C73), extends its duration (0x0043822E), runs the detection
// walk 0x0043966A and, when 0x00438E5B accepts it, the feedback 0x004389DB.
// Body carried from the banked attempt (score 0.96), callee spellings now bound
// to the rowed/pinned members of the Rva00439E0C view.
// cl: /I. /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfmelist /D_STLP_USE_MALLOC /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <map>
#include <vector>
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
enum Relationship { ENEMIES,NEUTRAL,ALLIES };class Team;
class Player {public:Relationship getRelationship(const Team*)const;char pad[0x2EC];const Team *team;};
struct DetectionTemplate {char pad[0x115];unsigned char kind;};
class Object {public:void *vtable;DetectionTemplate *objectTemplate;char pad8[0x30];Coord3D position;char pad44[0x30];int id;Object *rva002931F5(bool);Player *getControllingPlayer()const;};
struct BfmePod196 {int a[49];};
class Rva00438FC5 {public:~Rva00438FC5();char bytes[16];};
class Rva00438FA7:public Rva00438FC5 {public:Rva00438FA7();};
struct Rva004393D6:public _STL::list<BfmePod196> {int a,b,c;Rva004393D6();~Rva004393D6();Rva004393D6 &operator=(const Rva004393D6&);};
typedef _STL::map<int,Rva004393D6,_STL::less<int>,_STL::allocator<_STL::pair<const int,Rva004393D6> > > InvisibilityRecordMap;
template<> Rva004393D6 &InvisibilityRecordMap::operator[](const int&);
class Rva00388F63Map {public:void *find(int*);};
struct DetectionTreeNode {unsigned color;void *parent,*left,*right;int key;Rva004393D6 record;};
struct Rva004389DBInfo;
class Rva00438389 {public:Object *detector;unsigned char allied;char pad5[31];Rva00438389 &rva00438389();};
class Xfer;
class Rva00439E0C {public:void *vtable;InvisibilityRecordMap records;unsigned word10,nextFrame;
 bool rva0043979D(Object*,Rva004393D6*);
 void rva00439F3F(Xfer*);
 bool rva00439E0C(Object*,Object*,int,int);
 void rva0043822E(Rva004393D6*,unsigned int);
 int rva0043966A(Object*,const Coord3D*,Rva004393D6*,Rva004389DBInfo*);
 bool rva00438E5B(Object*,int,Rva004393D6*,Rva004389DBInfo*,unsigned int);
 void rva004389DB(Object*,Rva004389DBInfo*,int);
};
bool Rva00439E0C::rva00439E0C(Object *object,Object *volatile detectorInput,int duration,int feedback)
{
 if(!object)return false;
 if(!(object->objectTemplate->kind&0x20) && object->rva002931F5(false))return false;
 union RecordScratch {int id;Rva004393D6 *record;} scratch;
 scratch.id=object->id;
 DetectionTreeNode *node=(DetectionTreeNode*)((Rva00388F63Map*)&records)->find(&scratch.id);
 if(node==*(DetectionTreeNode**)&records) {
  Rva00438FA7 empty;
  records[scratch.id]=(const Rva004393D6&)empty;
  node=(DetectionTreeNode*)((Rva00388F63Map*)&records)->find(&scratch.id);
 }
 Object *detector=detectorInput;
 scratch.record=&node->record;
 bool allied=false;
 if(detector) {Player *detectorPlayer=detector->getControllingPlayer();allied=detectorPlayer->getRelationship(object->getControllingPlayer()->team)==2;}
 rva0043822E(scratch.record,duration);
 Rva00438389 info;info.rva00438389();
 int state=rva0043966A(object,&object->position,scratch.record,(Rva004389DBInfo*)&info);
 info.allied=allied;info.detector=detector;
 if(rva00438E5B(object,state,scratch.record,(Rva004389DBInfo*)&info,duration)) {rva004389DB(object,(Rva004389DBInfo*)&info,feedback);return true;}
 return false;
}

typedef bool Bool;
struct XferVersion {unsigned char version,current;};
class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual Xfer &xferTypeName(const char *const &name);
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
	virtual Xfer &xferInt(int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual Xfer &xferSlot90(int *value);
};
void XferObjectID(Xfer *xfer, ObjectID *objectID);

class Rva00438758Interface;
class Rva004382FC
{
public:
	Rva004382FC();
	void rva00438758(Rva00438758Interface*);
private:
	char bytes[196];
};
struct Rva004390F7Element;
namespace _STL {
	template<> void list<Rva004390F7Element>::push_back(const Rva004390F7Element&);
}

// Native00439F3F..0043A047, RET4: receive keyed detection records and append
// their transferred 196-byte entries. Prologue/EH and complete return prove
// the boundary; earlier no-boundary reports decoded another image address.
// Field access and transfer ordering are target facts; original method and
// record identities remain unknown. Existing record constructor/destructor
// bindings and the rowed list append retain their provider spellings.
void Rva00439E0C::rva00439F3F(Xfer *xfer)
{
	int count;
	xfer->xferInt(&count);
	while (count)
	{
		--count;
		ObjectID id;
		XferObjectID(xfer,&id);
		DetectionTreeNode *node=(DetectionTreeNode*)((Rva00388F63Map*)&records)->find((int*)&id);
		if (node == *(DetectionTreeNode**)&records)
		{
			Rva00438FA7 empty;
			records[(int&)id]=(const Rva004393D6&)empty;
			node=(DetectionTreeNode*)((Rva00388F63Map*)&records)->find((int*)&id);
		}
		Rva004393D6 *record=&node->record;
		xfer->xferInt(&record->a);
		xfer->xferInt(&record->b);
		xfer->xferInt(&record->c);
		int n;
		xfer->xferInt(&n);
		while (n)
		{
			--n;
			Rva004382FC entry;
			entry.rva00438758((Rva00438758Interface*)xfer);
			((_STL::list<Rva004390F7Element>*)record)->push_back((const Rva004390F7Element&)entry);
		}
		--n;
	}
}

// Use the established four-byte vector providers. These ABI views carry
// ObjectIDs, as proven by the lookup call; no new folded identity is pinned.
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
 template<> _Vector_base<ObjectID,allocator<ObjectID> >::_Vector_base(const allocator<ObjectID>&);
 template<> void vector<ObjectID>::push_back(const ObjectID&);
 template<> inline _Vector_base<ObjectID,allocator<ObjectID> >::~_Vector_base() {if(_M_start)Rva00030830GameFree(_M_start);}
}
struct Rva00439862Element {char bytes[8];};
typedef _STL::_Rb_tree<Rva00439862Element,Rva00439862Element,_STL::_Identity<Rva00439862Element>,_STL::less<Rva00439862Element>,_STL::allocator<Rva00439862Element> > InvisibilityEraseProvider;
namespace _STL {template<> unsigned InvisibilityEraseProvider::erase(const Rva00439862Element&);}
extern GameLogic *TheGameLogic;
extern unsigned g_Va00DBA4E4;
class Rva00243177 {public:void rva00439965();};

// Native00439965..00439A22 is a complete EH-prologue/RET body. WB127FD30
// independently confirms the frame gate and gather-then-erase traversal.
// Manager +4 tree, +14 next frame, node +10 ObjectID and +14 record are
// target accesses. Established provider spellings do not resolve the original
// manager name or the erase provider's donor-derived element type.
void Rva00243177::rva00439965()
{
 Rva00439E0C *manager=(Rva00439E0C*)this;
 unsigned frame=TheGameLogic->getFrame();
 if(frame<manager->nextFrame)return;
 manager->nextFrame=frame+g_Va00DBA4E4;
 _STL::vector<ObjectID> remove;
 InvisibilityRecordMap *records=&manager->records;
 DetectionTreeNode *node=(DetectionTreeNode*)((DetectionTreeNode*)*(void**)records)->left;
 while(node!=*(DetectionTreeNode**)records) {
  Object *object=TheGameLogic->findObjectByID((ObjectID)node->key);
  Rva004393D6 *record=&node->record;
  if(!object || !manager->rva0043979D(object,record))remove.push_back((const ObjectID&)node->key);
  node=(DetectionTreeNode*)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base*)node);
 }
 ObjectID *id=remove.begin();
 if(id!=remove.end())do {
  ((InvisibilityEraseProvider*)records)->erase((const Rva00439862Element&)*id);
  ++id;
 }while(id!=remove.end());
}
