// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// Path::DoXfer, retail [0x003661FC,0x003664DD) RET4, 737 bytes. WorldBuilder
// F1F180 names Path::DoXfer (pathfinder_path.cpp lines 1039..1073). Zero
// Hour's Path::xfer supplies the serialization order (version, node count,
// nodes written tail first, optimized link by node id); the target replaces
// ZH's PathNode::m_id with a node->id map on save and an id->node map on load,
// adds the per-node waypoint word and the current-node id, and skips the
// whole transfer for a light CRC. Layouts and slots come from the native body.
//
// The save map is a genuine STLport map<unsigned,int> instantiation: its
// operator[] and the helpers it drives compile to the shared retail map
// bodies (0x2077D6 subscript, 0x4FF3B6 lower bound, 0x358211 hinted insert,
// 0x20673B/0x4D795B insert_unique, 0x4D9C49 _M_insert, 0x382B7F create node,
// 0x60C9D9 construct). With the template bodies visible, cl sees that the
// subscript does not retain the key reference, which is what lets the loop
// key, the optimized-link key and the load-side waypoint share one frame slot.
#include <map>
#include <new>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Xfer
{
public:
	virtual void slot00(); virtual void slot01(); virtual bool IsStoring() const;
	virtual void slot03(); virtual bool IsLightCRC() const;
	virtual void slot05(); virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09();
	struct Version { unsigned char value, current; Version() : value(1), current(1) {} };
	virtual Xfer &xferVersion(Version *);
	virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual Xfer &xferCoord3D(Coord3D *);
	virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual Xfer &xferReal(float *);
	virtual void slot29(); virtual Xfer &xferUnsignedInt(unsigned *); virtual Xfer &xferInt(int *);
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35(); virtual Xfer &xferBool(bool *);
};
Xfer *XferPathfindLayerEnum(Xfer *, int *);
enum PathfindLayerEnum { LAYER_INVALID = 0 };

class PathNode
{
public:
	PathNode(const Coord3D *, PathfindLayerEnum) throw();
	PathNode *next, *previous, *optimized;
	Coord3D position;
	PathfindLayerEnum layer;
	bool canOptimize;
	unsigned waypoint;
};
class Rva0026E4A0 { public: Rva0026E4A0 &set(Rva0026E4A0 *) throw(); };
class Rva00065964ObjectPool { public: void *rva002635C2() throw(); };
extern Rva00065964ObjectPool g_pathNodePool;

// Save-side node -> id map (rowed out-of-line destructor 0x36528F).
class Rva00364A37
{
public:
	~Rva00364A37();
	_STL::map<int, void *> map;
	__forceinline int &idOf(const unsigned &key) { return ((_STL::map<unsigned, int> *)this)->operator[](key); }
	__forceinline int &idOf(PathNode *const &node) { return ((_STL::map<unsigned, int> *)this)->operator[]((const unsigned &)node); }
};

// Load-side id -> node map (rowed out-of-line destructor 0x3652C7).
class Rva00364A60
{
public:
	~Rva00364A60();
	_STL::map<int, void *> map;
	__forceinline PathNode *&get(const int &key) { return (PathNode *&)((_STL::map<int, int> *)this)->operator[](key); }
	__forceinline void find(const int &key, PathNode *&result)
	{
		_STL::map<int, int> *m = (_STL::map<int, int> *)this;
		_STL::map<int, int>::iterator i = m->find(key);
		if (i != m->end())
			result = (PathNode *)i->second;
	}
};

class Path
{
public:
	void DoXfer(Xfer *);
	int unknown00;
	PathNode *head, *tail;
	bool optimized, blocked;
	PathNode *current;
	float distance;
	Coord3D goal;
	int unknown24;
};

void Path::DoXfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version;
	xfer->xferVersion(&version);
	int count = 0;
	for (PathNode *node = head; node; node = node->next)
		++count;
	xfer->xferInt(&count);
	if (xfer->IsStoring()) {
		Rva00364A37 ids;
		unsigned key;
		PathNode *node = tail;
		while ((key = (unsigned)node), node) {
			ids.idOf(key) = count;
			xfer->xferInt(&count);
			Coord3D position;
			position.x = node->position.x; position.y = node->position.y; position.z = node->position.z;
			xfer->xferCoord3D(&position);
			int layer = node->layer;
			XferPathfindLayerEnum(xfer, &layer);
			bool canOpt = node->canOptimize;
			xfer->xferBool(&canOpt);
			int optID = -1;
			if (node->optimized)
				optID = ids.idOf((unsigned)node->optimized);
			xfer->xferInt(&optID);
			unsigned waypoint = node->waypoint;
			xfer->xferUnsignedInt(&waypoint);
			--count;
			node = node->previous;
		}
		int currentID = 0;
		if (current)
			currentID = ids.idOf(current);
		xfer->xferInt(&currentID);
	} else {
		Rva00364A60 nodes;
		while (count) {
			int nodeID;
			xfer->xferInt(&nodeID);
			Coord3D position; position.x = 0; position.y = 0; position.z = 0;
			xfer->xferCoord3D(&position);
			int layer;
			XferPathfindLayerEnum(xfer, &layer);
			bool canOpt;
			xfer->xferBool(&canOpt);
			int optID = -1;
			xfer->xferInt(&optID);
			unsigned waypoint = 0x7fffffff;
			xfer->xferUnsignedInt(&waypoint);
			void *storage = g_pathNodePool.rva002635C2();
			PathNode *node = storage ? new (storage) PathNode(&position, (PathfindLayerEnum)layer) : 0;
			nodes.get(nodeID) = node;
			node->canOptimize = canOpt; node->waypoint = waypoint;
			PathNode *optNode = 0;
			if (optID > 0)
				nodes.find(optID, optNode);
			head = (PathNode *)&((Rva0026E4A0 *)node)->set((Rva0026E4A0 *)head);
			if (!tail)
				tail = node;
			if (optNode)
				node->optimized = optNode;
			--count;
		}
		int currentID;
		xfer->xferInt(&currentID);
		PathNode *curNode = 0;
		if (currentID)
			curNode = nodes.get(currentID);
		current = curNode;
		unknown24 = -1;
	}
	xfer->xferBool(&optimized).xferBool(&blocked).xferCoord3D(&goal).xferReal(&distance);
	xfer->xferInt(&unknown00);
}
