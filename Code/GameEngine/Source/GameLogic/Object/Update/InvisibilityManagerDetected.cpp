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
// map<int,int> find otherwise instantiates the less<int>::operator() COMDAT
// (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
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
typedef _STL::pair<const int,int> IntIntPair;
typedef _STL::_Rb_tree<int,IntIntPair,_STL::_Select1st<IntIntPair>,_STL::less<int>,_STL::allocator<IntIntPair> > MapIntIntTree;
// The int-keyed lookup ICF-folds onto the rowed map<int,int> _M_find 0x00388F63.
struct DetectionTreeNode {unsigned color;void *parent,*left,*right;int key;Rva004393D6 record;};
struct Rva004389DBInfo;
class Rva00438389 {public:Object *detector;unsigned char allied;char pad5[31];Rva00438389 &rva00438389();};
class Xfer;
class Rva00439E0C {public:void *vtable;InvisibilityRecordMap records;
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
 DetectionTreeNode *node=(DetectionTreeNode*)((MapIntIntTree*)&records)->find(scratch.id)._M_node;
 if(node==*(DetectionTreeNode**)&records) {
  Rva00438FA7 empty;
  records[scratch.id]=(const Rva004393D6&)empty;
  node=(DetectionTreeNode*)((MapIntIntTree*)&records)->find(scratch.id)._M_node;
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
enum ObjectID
{
	INVALID_ID = 0
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
		DetectionTreeNode *node=(DetectionTreeNode*)((MapIntIntTree*)&records)->find((int&)id)._M_node;
		if (node == *(DetectionTreeNode**)&records)
		{
			Rva00438FA7 empty;
			records[(int&)id]=(const Rva004393D6&)empty;
			node=(DetectionTreeNode*)((MapIntIntTree*)&records)->find((int&)id)._M_node;
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
