// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?update@MineshaftPortalNetworkManager@@UAEXXZ @0x003734FD (670B).
// Native 3734FD..37379B and WB MineshaftPortalNetworkManager::update (wpA/wpB
// asserts at MineshaftPortalBehaviour.cpp:337..395; the registration calls and
// asserts are compiled out of retail). For every portal network (the map at
// +0x10: key at node+0x10, group at node+0x14) whose group is flagged changed:
// clear the flag, score every portal of the group by the mean squared 2D
// distance to the others (portal slot 0x8C of TheTerrainLogic, position at
// +0xC/+0x10) and keep the three highest scores in a float-keyed multimap
// (insert_equal 0x004EA301, erase 0x005530A8 of the folded POD tree, dtor
// 0x00372FBC). A portal that is not kept is re-linked through 0x00373158 when
// its 0x002E6ECA test passes, as is each evicted one. Then every kept portal is
// linked to every other kept one (hasLink 0x00372CEC, addLink 0x00272306) and
// handed to the pathfinder (0x002E8FE5) when the 0x002E6ECA test fails.
// The map ctor is the ICF-folded 12-byte empty-tree body 0x0033C432; the
// local's dtor is the rowed 0x00372FBC.
// Evicting the smallest score goes through a throw() helper: without it the
// by-value iterator argument of the erase call saves ESP, which retail does not.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include <set>
#include <vector>
#include <new>
#include "../../../Common/GameLogicObjectLookupView.h"

struct TreeOpaqueMapped00372FF4 { unsigned int m_bits; };
typedef _STL::pair<const float, TreeOpaqueMapped00372FF4> TreeValue00372FF4;
typedef _STL::_Rb_tree<float, TreeValue00372FF4, _STL::_Select1st<TreeValue00372FF4>, _STL::less<float>, _STL::allocator<TreeValue00372FF4> > Tree00372FF4;
typedef _STL::_Rb_tree<int, int, _STL::_Identity<int>, _STL::less<int>, _STL::allocator<int> > SetIntTree;

class Rva00372F00 { public: ~Rva00372F00(); };

struct LocalTree {
    void *header;
    unsigned int count;
    int pad;
    __forceinline LocalTree() { ((_STL::map<int, void *> *)this)->_STL::map<int, void *>::map(); }
    __forceinline ~LocalTree() { ((Rva00372F00 *)this)->~Rva00372F00(); }
};

static __forceinline void eraseFirst(LocalTree *tree) throw()
{
    ((SetIntTree *)tree)->erase(SetIntTree::iterator((SetIntTree::_Link_type)((_STL::_Rb_tree_node_base *)tree->header)->_M_left));
}
class Rva00373373Portal {
public:
    virtual void *destroy(unsigned int flags);
    unsigned int id;
    char pad08[4];
    float x, y, z;
};
class Rva0037381C { public: void rva00373158(Rva00373373Portal *portal, int key); };
class Rva002E6ECA { public: int get() const; };
class Rva00372CA8 { public: bool rva00372CEC(int value); };
class Waypoint { public: void addLink(Waypoint *other); };
class Rva002E9042 { public: void rva002E8FE5(void *portal); };
class AI { public: char pad[0x10]; Rva002E9042 *pathfinder; };
extern AI *TheAI;
class TerrainLogic {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33(); virtual void slot34();
    virtual Rva00373373Portal *portalAt(unsigned int id);
};
extern TerrainLogic *TheTerrainLogic;

struct NetGroup : public _STL::vector<ObjectID> { bool changed; };
struct NetNode : _STL::_Rb_tree_node_base { int key; NetGroup *group; };
struct TreeNode : _STL::_Rb_tree_node_base { float key; ObjectID id; };

class Rva0037381CMap { public: void *header; unsigned int count; };
class Rva003732BFSubsystem { public: virtual ~Rva003732BFSubsystem(); char pad04[8]; };
class Rva003732BFSnapshot { protected: virtual void crc(void *xfer); virtual void xfer(void *xfer) = 0; virtual void loadPostProcess(); };
class MineshaftPortalNetworkManager : public Rva003732BFSubsystem, public Rva003732BFSnapshot
{
public:
    virtual void xfer(void *xfer);
    virtual void update();
    Rva0037381CMap map;
};

void MineshaftPortalNetworkManager::update()
{
    _STL::_Rb_tree_node_base *mapHeader = (_STL::_Rb_tree_node_base *)map.header;
    for (NetNode *node = (NetNode *)mapHeader->_M_left; node != (NetNode *)mapHeader;
         node = (NetNode *)_STL::_Rb_global<bool>::_M_increment(node)) {
        if (!node->group->changed)
            continue;
        node->group->changed = false;
        LocalTree tree;
        ObjectID *end = node->group->end();
        for (ObjectID *it = node->group->begin(); it != end; ++it) {
            Rva00373373Portal *portal = TheTerrainLogic->portalAt(*it);
            float sum = 0.0f;
            for (ObjectID *jt = node->group->begin(); jt != end; ++jt) {
                if (*it != *jt) {
                    Rva00373373Portal *other = TheTerrainLogic->portalAt(*jt);
                    float dx = portal->x - other->x;
                    float dy = portal->y - other->y;
                    sum += dy * dy + dx * dx;
                }
            }
            if (node->group->size() > 1)
                sum /= (float)(node->group->size() - 1);
            if (tree.count == 0 || tree.count < 3) {
                TreeOpaqueMapped00372FF4 m = { (unsigned)*it };
                TreeValue00372FF4 v(sum, m);
                ((Tree00372FF4 *)&tree)->insert_equal(v);
            } else {
                if (sum > ((TreeNode *)((_STL::_Rb_tree_node_base *)tree.header)->_M_left)->key) {
                    Rva00373373Portal *old = TheTerrainLogic->portalAt(((TreeNode *)((_STL::_Rb_tree_node_base *)tree.header)->_M_left)->id);
                    if ((unsigned char)((Rva002E6ECA *)old)->get())
                        ((Rva0037381C *)this)->rva00373158(old, node->key);
                    eraseFirst(&tree);
                    TreeOpaqueMapped00372FF4 m = { (unsigned)*it };
                    TreeValue00372FF4 v(sum, m);
                    ((Tree00372FF4 *)&tree)->insert_equal(v);
                } else {
                    if ((unsigned char)((Rva002E6ECA *)portal)->get())
                        ((Rva0037381C *)this)->rva00373158(portal, node->key);
                }
            }
        }
        _STL::_Rb_tree_node_base *treeHeader = (_STL::_Rb_tree_node_base *)tree.header;
        for (TreeNode *a = (TreeNode *)treeHeader->_M_left; a != (TreeNode *)treeHeader;
             a = (TreeNode *)_STL::_Rb_global<bool>::_M_increment(a)) {
            Rva00373373Portal *wa = TheTerrainLogic->portalAt(a->id);
            for (TreeNode *b = (TreeNode *)((_STL::_Rb_tree_node_base *)tree.header)->_M_left; b != (TreeNode *)treeHeader;
                 b = (TreeNode *)_STL::_Rb_global<bool>::_M_increment(b)) {
                Rva00373373Portal *wb = TheTerrainLogic->portalAt(b->id);
                if (wa != wb) {
                    if (!((Rva00372CA8 *)wa)->rva00372CEC((int)wb)) {
                        ((Waypoint *)wa)->addLink((Waypoint *)wb);
                        ((Waypoint *)wb)->addLink((Waypoint *)wa);
                    }
                    if (!(unsigned char)((Rva002E6ECA *)wa)->get())
                        TheAI->pathfinder->rva002E8FE5(wa);
                    if (!(unsigned char)((Rva002E6ECA *)wb)->get())
                        TheAI->pathfinder->rva002E8FE5(wb);
                }
            }
        }
    }
}
