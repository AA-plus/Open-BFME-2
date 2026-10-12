// cl: /O1 /G7 /arch:SSE /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// Formation::optimizeUnits, WB 0x0113B070 FormationAssistant.cpp:431.
// Retail 0x0042550E..0x004256D5, RET4. No BF1/ZH FormationAssistant donor
// is available. STLport is the reference for vector storage and algorithms;
// retail establishes the record stride, object-ID field, pairwise swap cost,
// iteration limit, and position helper ABI. Remaining fields are unnamed.
#include <vector>
#include <algorithm>

#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Rva00422CA8 { public: bool operator()(int,int) const; };
// The sort family owns the retail specialization in stlport_int_sort_rva00422ca8.cpp.
// Refer to that definition rather than emitting the header's different generic body.
namespace _STL {
template<> void __unguarded_linear_insert<int*,int,Rva00422CA8>(int*,int,Rva00422CA8);
// Use the rowed providers rather than emit divergent generic algorithm copies.
template<> void sort<int*,Rva00422CA8>(int*,int*,Rva00422CA8);
template<> int* upper_bound<int*,int,Rva00422CA8>(int*,int*,const int&,Rva00422CA8);
}
void __cdecl rva004216A2(float *out,const float *base,const float *slot);
float __cdecl Rva004219F4DistSquared(const float *small,const float *object);
struct BfmeFormationSlot {
 int unknown00;
 ObjectID objectId;
 unsigned char unknown08[0x18];
};
class Formation {
 _STL::vector<BfmeFormationSlot> slots;
public:
 void optimizeUnits(const Coord3D *base);
};
void Formation::optimizeUnits(const Coord3D *base) {
 _STL::vector<long> order;
 order.reserve(slots.size());
 for(BfmeFormationSlot *slot=slots.begin();slot!=slots.end();++slot)
  order.push_back((long)slot);
 _STL::sort((int*)order.begin(),(int*)order.end(),Rva00422CA8());
 int limit=order.size()*order.size();
 long *first=order.begin();
 while(first!=order.end()) {
  long *last=(long*)_STL::upper_bound((int*)first,(int*)order.end(),*(int*)first,Rva00422CA8());
  for(long *current=first;current!=last;++current) {
   long *next=current+1;
   if(next==last)continue;
   BfmeFormationSlot *slot=(BfmeFormationSlot*)*current;
   Coord3D pos;
   rva004216A2(&pos.x,&base->x,(const float*)slot);
   Object *object=TheGameLogic->findObjectByID(slot->objectId);
   if(!object)continue;
   float original=Rva004219F4DistSquared(&pos.x,(const float*)object);
   while(next!=last) {
    BfmeFormationSlot *other=(BfmeFormationSlot*)*next;
    Coord3D otherPos;
    rva004216A2(&otherPos.x,&base->x,(const float*)other);
    ObjectID otherId=other->objectId;
    Object *otherObject=TheGameLogic->findObjectByID(otherId);
    if(otherObject) {
     // Native stores the rounded float cost before setting up the crossed call.
     float currentCost=(float)(original+Rva004219F4DistSquared(&otherPos.x,(const float*)otherObject));
     float crossCost=Rva004219F4DistSquared(&pos.x,(const float*)otherObject);
     if(currentCost > crossCost+Rva004219F4DistSquared(&otherPos.x,(const float*)object)) {
      if(--limit<0)return;
      ObjectID old=((BfmeFormationSlot*)*current)->objectId;
      ((BfmeFormationSlot*)*current)->objectId=otherId;
      ((BfmeFormationSlot*)*next)->objectId=old;
      object=otherObject;
      next=current;
      original=Rva004219F4DistSquared(&pos.x,(const float*)object);
     }
    }
    ++next;
   }
  }
  first=last;
 }
}

// Native 0x00422377..0x0042245F, RET0: output pointer followed by object view.
// Formation placement at 0x0042481E consumes the two grid dimensions. Native
// establishes the input radius at +0xB8 and template bit test at +0x11F.
// GeometryInfo's verified aggregate-shape provider supplies the 36-byte shape
// contract; its StringBase cleanup is independently owned at 0x00036410.
// The original helper name and dimension-structure name remain unknown.
#include "ascii_string.h"

struct FormationGeometryOffset : Coord3D {
 FormationGeometryOffset() { x=0.0f; y=0.0f; z=0.0f; }
};
static __forceinline int formationCellExtent(float radius) {
 return (int)(radius*2.0f+4.0f);
}
struct GeometryShape {
 int m_type;
 float m_height;
 float m_majorRadius;
 float m_minorRadius;
 FormationGeometryOffset m_offset;
 AsciiString m_name;
 bool m_enabled;
 bool m_flag21;
 char m_22[2];
 GeometryShape() : m_type(0),m_height(1.0f),m_majorRadius(1.0f),
  m_minorRadius(1.0f),m_enabled(true),m_flag21(true) {}
};
class GeometryInfo {
public:
 void rva006BD9C0(GeometryShape &out) const;
private:
 char unknown00[0x10];
public:
 float m_boundingCircleRadius;
private:
 char unknown14[0x24];
};
struct Rva00422377Flag {
 char unknown00[0x11F];
 unsigned char m_11F;
};
struct Rva00422377In {
 char unknown00[4];
 Rva00422377Flag *m_template;
 char unknown08[0xA0];
 GeometryInfo m_geometry;
};
struct Rva00422377Out { int x,y; };

void Rva00422377Get(Rva00422377Out *out,Rva00422377In *in) {
 if(!in) { out->x=0; out->y=0; return; }
 float f=1.0f+2.0f*in->m_geometry.m_boundingCircleRadius;
 Rva00422377Flag *flag=in->m_template;
 int y=(int)f;
 int x=y;
 if((flag->m_11F&4)!=0) {
  GeometryShape shape;
  in->m_geometry.rva006BD9C0(shape);
  y=formationCellExtent(shape.m_majorRadius);
  x=formationCellExtent(shape.m_minorRadius);
 }
 out->x=x;
 out->y=y;
}
