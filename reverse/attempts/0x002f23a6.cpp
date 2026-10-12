// ?rva002F23A6@Rva002F23A6@@QAE_NPAVObject@@HHPAUCoord3D@@0@Z
// partial score=0.7 date=2026-10-12
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include "../Code/Libraries/Include/Lib/Coord3D.h"
#include "../Code/Libraries/Include/Lib/ICoord2D.h"
enum PathfindLayerEnum {LAYER_UNKNOWN=0,LAYER_GROUND=1};
enum NameKeyType {NAMEKEY_INVALID=-1};
class Module {};
struct ThingTemplateView {
 char pad00[0x108]; unsigned char kind[24];
 char pad120[0x56c-0x120]; int diameter;
 char pad570[0x634-0x570]; unsigned char human;
 __forceinline bool has(int k) const {return (kind[k/8]&(1<<(k%8)))!=0;}
};
class Thing {public:
 void getUnitDirectionVector2D(Coord3D &) const;
 char unknown00[4]; ThingTemplateView *definition; char unknown08[0x38-8]; Coord3D position;
 const Coord3D *getPosition() const {return &position;}
};
class Object: public Thing {public:
 void rva0028C2DD(Coord3D *) const;
 int rva0028B511() const;
 bool rva0028AFBB() const;
protected: Module *findModule(NameKeyType) const; friend class Rva002F23A6;
};
class Rva002CB35CObj {public:bool rva002CB35C(int,void *,void *,void *,float,int);};
class Rva002E7964 {public:void rva002E7964(ICoord2D *,unsigned char,const Coord3D *);};
class PathfindCell {public:char unknown00[8];unsigned short zone;unsigned short unknown0a;unsigned flags;};
struct Rva002E8BCFSrc {char unknown00[0x10];int mask;char unknown14;bool flag;};
class Rva002E8BCF {public:
 Rva002E8BCF(const Rva002E8BCFSrc*,bool,int,bool);
 int a;bool b,c;int d;bool e;
};
class BfmeTripleRC {};
class Gen_003D5670 {public:
 Gen_003D5670(int,int,int,int,int,int,unsigned char,unsigned char,int,int,BfmeTripleRC*,unsigned char);
 unsigned char storage[0x3c];
};
class Rva002E99F9Sub460 {public:unsigned short rva0053241F(void *,unsigned short);unsigned short rva00531FD4(void *,unsigned short);};
class Pathfinder {public:
 bool rva002ED313(Object *);
 void AdjustMeleeOffset(Object *,Object *,Coord3D *);
 PathfindCell *getCell(PathfindLayerEnum,int,int);
 PathfindCell *rva002E8BF8(PathfindLayerEnum,const Coord3D *);
 unsigned char bfmeWrapE6E90(void *,void *,void *,void *,void *,void *);
 bool rva002EEA8A(const ICoord2D *,int,ICoord2D *,void *,int);
};
void Rva002EBCA7Split(void *,int *,unsigned char *);
class TerrainLogic {public:PathfindLayerEnum getLayerForDestination(Object *,const Coord3D *);};
extern TerrainLogic *TheTerrainLogic;
class GlobalData {public:char unknown00[0x11ec];int searchLimit;};
extern GlobalData *TheWritableGlobalData;
class NameKeyGenerator {public:NameKeyType nameToKey(const char *);};
extern NameKeyGenerator *TheNameKeyGenerator;
class DynamicPortalBehaviour {public:static Module *rva004608E0(Object *);};
class Rva004C5772CmpBoolField {public:bool get() const;};
struct SearchCoordinate:Coord3D {
 SearchCoordinate(const Coord3D &p){x=p.x;y=p.y;z=p.z;}
 void scale(float f){x*=f;y*=f;z*=f;}
 void add(const Coord3D &p){x+=p.x;y+=p.y;z+=p.z;}
};
class Rva002F23A6 {public:bool rva002F23A6(Object *,int,int,Coord3D *,Object *);};
bool Rva002F23A6::rva002F23A6(Object *unit,int weapon,int locomotor,Coord3D *dest,Object *victim)
{
 Pathfinder *path=(Pathfinder *)this;
 Rva002CB35CObj *range=(Rva002CB35CObj *)weapon;
 if(range->rva002CB35C((int)unit,(void*)unit->getPosition(),victim,(void*)victim->getPosition(),0.0f,1) && path->rva002ED313(unit)) {
   *dest=*unit->getPosition();return true;
 }
 SearchCoordinate start(*unit->getPosition());
 Coord3D direction;
 unit->getUnitDirectionVector2D(direction);
 direction.x*=10.0f;direction.y*=10.0f;
 start.add(direction);
 SearchCoordinate delta(start);
 delta.x-=dest->x;delta.y-=dest->y;delta.z=0;
 delta.normalize();delta.scale(10.0f);
 if((victim->definition->has(7)||victim->definition->has(60))&&!victim->definition->has(150))
   path->AdjustMeleeOffset(unit,victim,&delta);
 int radius;unsigned char centered;
 Rva002EBCA7Split(unit,&radius,&centered);
 for(int attempt=0;attempt<2;++attempt) {
   victim->rva0028C2DD(dest);
   if(victim->definition->has(150))delta.x=delta.y=delta.z=0;
   dest->x+=delta.x;dest->y+=delta.y;dest->z+=delta.z;
   if(!centered){dest->x+=5.0f;dest->y+=5.0f;}
   ICoord2D cell;
   ((Rva002E7964 *)this)->rva002E7964(&cell,1,dest);
   if(cell.x<0)return false;
   PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(unit,dest);
   PathfindCell *destinationCell=path->getCell(layer,cell.x,cell.y);
   PathfindCell *originCell=path->rva002E8BF8((PathfindLayerEnum)unit->rva0028B511(),&start);
   if(!originCell)return false;
   if(victim->definition->has(60)&&!victim->definition->has(150))layer=LAYER_GROUND;
   int diameter=unit->definition->diameter;
   unsigned char special=unit->definition->human;
   Rva002E8BCF query((const Rva002E8BCFSrc *)locomotor,!special,diameter-1,unit->rva0028AFBB());
   Rva002E99F9Sub460 *zones=(Rva002E99F9Sub460 *)((char*)this+0x460);
   unsigned originZone=zones->rva0053241F(&query,originCell->zone);
   bool bridge=false;
   if((originCell->flags&15)==4) {
      bridge=true;
      originZone=zones->rva00531FD4(&query,(unsigned short)originZone);
      originZone=zones->rva0053241F(&query,(unsigned short)originZone);
   }
   unsigned destinationZone=zones->rva0053241F(&query,destinationCell->zone);
   if(originZone==destinationZone && path->bfmeWrapE6E90(unit,(void*)cell.x,(void*)cell.y,(void*)layer,(void*)radius,(void*)centered) && range->rva002CB35C((int)unit,(void*)unit->getPosition(),victim,dest,0.0f,1))return true;
   bool deployed=false;
   if(victim->definition->has(93)) {
      Module *portal=DynamicPortalBehaviour::rva004608E0(victim);
      static NameKeyType deployKey=TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
      Module *power=victim->findModule(deployKey);
      if(portal && power && ((Rva004C5772CmpBoolField *)power)->get())deployed=true;
   }
   ICoord2D output;
   if(path->rva002EEA8A(&cell,TheWritableGlobalData->searchLimit,&output,
      &Gen_003D5670((int)this,(int)&query,(int)unit,(int)victim,weapon,radius,centered,bridge,originZone,layer,(BfmeTripleRC *)dest,deployed),1))return true;
   if(victim->definition->has(150)&&layer!=LAYER_GROUND) {
      if(path->rva002EEA8A(&cell,TheWritableGlobalData->searchLimit*2,&output,
         &Gen_003D5670((int)this,(int)&query,(int)unit,(int)victim,weapon,radius,centered,bridge,originZone,LAYER_GROUND,(BfmeTripleRC *)dest,deployed),1))return true;
   }
   if(delta.y*delta.y+delta.x*delta.x<=1.0f)break;
   delta.x=delta.y=delta.z=0;
 }
 return false;
}
