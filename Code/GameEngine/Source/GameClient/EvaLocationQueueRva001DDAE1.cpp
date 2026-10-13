// cl: /O1 /G7 /arch:SSE /Oy- /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /ICode/Libraries/Include
// stlport
//
// ?rva001DDAE1@Rva001DDAE1@@QAEXPAUCoord3D@@@Z @0x001DDAE1 (173B).
// Native 1DDAE1..1DDB8E and WB acd5a0 (unnamed): Eva location queue at +0x68
// (list of 16-byte records: frame, position), cursor at +0x6C, minimum distance
// at +0x94. Drops the oldest record when the new position is closer than the
// minimum distance (moving the cursor to end first when it sits on it), then
// appends (position, current frame). The delta temporary has an empty
// destructor in the debug build (EH state 0 across the erase), which is what
// gives retail's ESP save in the parameter home before the erase call.
// stlport
#include <list>
#include "Lib/Coord3D.h"
#include "../Common/GameLogicObjectLookupView.h"
class Rva0041F431 {public:Rva0041F431*rva0041F431();};
struct BfmeFloat4Record00469C61 {BfmeFloat4Record00469C61(){((Rva0041F431*)this)->rva0041F431();}unsigned int frame;Coord3D position;};
class Rva00357E14 {public:void rva00357E14(const BfmeFloat4Record00469C61&);};
typedef _STL::list<BfmeFloat4Record00469C61,_STL::allocator<BfmeFloat4Record00469C61> > EvaLocationList;
// The typed erase is the ICF twin of the rowed list<int>::erase 0x00438539: call it through the int view.
typedef _STL::list<int,_STL::allocator<int> > EvaIntList;
extern GameLogic*TheGameLogic;
class Rva001DDAE1 {public:void rva001DDAE1(Coord3D*);char pad0[0x68];EvaLocationList locations;EvaLocationList::iterator cursor;char pad70[0x94-0x70];float minimumDistance;};
void Rva001DDAE1::rva001DDAE1(Coord3D*position)
{
 if(!locations.empty()) {
  EvaLocationList::iterator first=locations.begin();
  struct DeltaCopy : Coord3D { ~DeltaCopy() {} } delta;delta.x=position->x;delta.y=position->y;delta.z=position->z;
  delta.x-=first->position.x;delta.y-=first->position.y;delta.z-=first->position.z;
  if(delta.z*delta.z+delta.y*delta.y+delta.x*delta.x<minimumDistance*minimumDistance) {
   if(cursor==first)cursor=locations.end();
   ((EvaIntList*)&locations)->erase(EvaIntList::iterator((EvaIntList::iterator::_Node*)first._M_node));
  }
 }
 BfmeFloat4Record00469C61 record;
 unsigned f=TheGameLogic->getFrame();
 record.position=*position;
 record.frame=f;
 ((Rva00357E14*)&locations)->rva00357E14(record);
}
