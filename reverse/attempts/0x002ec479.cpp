// ?rva002EC479@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@0@Z
// partial score=0.76381 date=2026-10-13
// ?rva002EC479@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@0@Z
// cl: /I. /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /ICode/Libraries/Include/Lib /I.
// Crack-M: native1098/frame4C, measured candidate1099/frame48, score0.76381.
// WB D3A7D0 supplies the nested perimeter loops, radius post-decrement and ABI.
// Actual visible 2E7875/162 +2EBC14/32 helpers restore native loop-invariant
// hoisting. Copy-constructed aggregate adapter improves register allocation;
// source helpers are the home TU at c1bf9419d4, using its proven floor blocker.
// Division by -2 already matches PUSH -2/POP ECX/CDQ/IDIV ECX; do not retry it.
// Remaining: base.y stays in ESI instead of stack, frame48 vs4C, different
// preserved-register roles and inner-switch induction locals; not byte-exact.
// Full home context, actual hidden-return ABI, empty dtors and loop scopes
// did not close it. A700-trial permute run produced semantically invalid
// reordered statements; those variants were discarded, not banked.
// Native2EC479..2EC8C3 complete1098 RET12; WB D3A7D0 independently
// corroborates target-footprint perimeter and range query, not a callable name.
// Native Object/template/cell offsets below are target observations.
#include "Coord3D.h"
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" double __cdecl fabs(double);
#include "Code/Libraries/Include/Lib/ICoord2D.h"
enum PathfindLayerEnum {OBSERVED_LAYER_1=1};
enum WeaponSlotType {OBSERVED_SLOT_0=0};
enum NameKeyType {NAMEKEY_INVALID=0};
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
class Object;class Module;class Weapon;
class Rva002C9400ByteField {public:unsigned char get()const;};
class Weapon {public:float getAttackRange(const Object*)const;void *vptr;Rva002C9400ByteField *definition;};
struct AttackQueryTemplate {char pad[0x108];unsigned kind[8];unsigned kindOf(unsigned k)const{return kind[k>>5]&(1U<<(k&31));}};
class Object {
 friend class Pathfinder;
public:
 const Weapon *getCurrentWeapon(WeaponSlotType*)const;
 int rva0028B511()const;
 unsigned char rva002957FC();
 float rva00263763(const void*)const;
 float rva0028EFB8(const Coord3D*,Object*,const Coord3D*);
 void *vptr;AttackQueryTemplate *definition;char pad8[0x38-8];Coord3D position;
 char pad44[0x74-0x44];int id;char pad78[0xB8-0x78];float observedSize;
protected:
 Module *findModule(NameKeyType)const;
};
class Rva00460C73FloatChase32Field {public:float get()const;};
class Rva004C5772CmpBoolField {public:bool get()const;};
class DynamicPortalBehaviour {public:static Module *rva004608E0(Object*);void rva00460CBA(Coord3D*);};
template<int N> class QueryTerrainSlots:public QueryTerrainSlots<N-1>{public:virtual void gap(char(*)[N])=0;};
template<>class QueryTerrainSlots<0>{};
class TerrainLogic:public QueryTerrainSlots<44>{public:virtual bool querySurface(Object*,int)=0;};
extern TerrainLogic *TheTerrainLogic;
struct QueryCellInfo {char pad[0x28];int structure;};
class PathfindCell {public:QueryCellInfo *info;char pad4[8];unsigned flags;int layer()const{return(flags>>4)&63;}unsigned char type()const{return(unsigned char)(flags&15);}};
ICoord2D *Rva002EBC14Cell(ICoord2D*,void*,const Coord3D*);
int Rva002E9B31Get(void*);
int Rva002E6E6CGet(int);
int Rva002E6E8AGet(int);
// The already matched callback family demonstrates the floor-to-FISTP
// compiler blocker; this tiny inline x87 conversion preserves native rounding.
static __forceinline int queryFloor(float f){float v=(float)floor(f);int i;__asm {
 fld [v]
 fistp [i]
 }return i;}
class Pathfinder {public:bool rva002EC479(Object*,const Coord3D*,Object*);PathfindCell *getCell(PathfindLayerEnum,int,int);};
static const float PATHFINDER_CELL_INV = 1.0f / 10.0f;
__declspec(noinline) ICoord2D* __cdecl Rva002E7875WorldToCell(ICoord2D* out, bool center, const Coord3D* pos)
{
	int ix;
	int iy;
	if (center) {
		ix = queryFloor(pos->x * PATHFINDER_CELL_INV);
		iy = queryFloor(pos->y * PATHFINDER_CELL_INV);
	} else {
		ix = queryFloor(pos->x * PATHFINDER_CELL_INV + 0.5f);
		iy = queryFloor(pos->y * PATHFINDER_CELL_INV + 0.5f);
	}
	out->x = ix;
	out->y = iy;
	return out;
}

bool Rva002EBBFBIsOdd(void *);
__declspec(noinline) ICoord2D *__cdecl Rva002EBC14Cell(ICoord2D *out,void *p,const Coord3D *pos) {
 Rva002E7875WorldToCell(out,Rva002EBBFBIsOdd(p),pos);return out;
}
struct FootprintCell:ICoord2D {FootprintCell(){} FootprintCell(const FootprintCell &p){x=p.x;y=p.y;} };
static __forceinline FootprintCell footprintCell(void *object,const Coord3D *position){FootprintCell cell;Rva002EBC14Cell(&cell,object,position);return cell;}
bool Pathfinder::rva002EC479(Object *attacker,const Coord3D *from,Object *target)
{
 const Weapon *weapon=attacker->getCurrentWeapon(0);
 if(!weapon || !weapon->definition->get())return false;
 FootprintCell base=footprintCell(attacker,from);
 int diameter=Rva002E9B31Get(attacker);
 int half=diameter/-2;base.x+=half;base.y+=half;
 float cellRange=weapon->getAttackRange(target)/10.0f;
 int radius=queryFloor(cellRange+0.1f);
 if(target->definition->kindOf(7)){
  int layers[2];layers[0]=attacker->rva0028B511();int count=1;
  if(!(unsigned char)Rva002E6E6CGet(layers[0]) && TheTerrainLogic->querySurface(attacker,layers[0])){layers[1]=1;count=2;}
  bool foundWall=false;
  while(radius-->=0){
   for(int j=diameter;j>=0;--j){
    for(int side=0;side<4;++side){
     ICoord2D p;
     switch(side){
      case 0:p.x=base.x+j;p.y=base.y-1;break;
      case 1:p.x=base.x+diameter;p.y=base.y+j;break;
      case 2:p.x=base.x+diameter-j-1;p.y=base.y+diameter;break;
      case 3:p.x=base.x-1;p.y=base.y+diameter-j-1;break;
     }
     for(int l=0;l<count;++l){
      PathfindCell *cell=getCell((PathfindLayerEnum)layers[l],p.x,p.y);
      if(cell){
       if(cell->layer()!=layers[0] && (unsigned char)Rva002E6E8AGet(cell->layer()) && cell->type()==5)foundWall=true;
       int structure=cell->info?cell->info->structure:0;
       if(structure==target->id)return true;
      }
     }
    }
   }
   diameter+=2;--base.x;--base.y;
  }
  if(target->definition->kindOf(0x3C)){
   float size=attacker->observedSize;
if(target->definition->kindOf(0x96))size=0.0f;
   size+=20.0f;
   if(target->rva0028EFB8(&target->position,attacker,from)<size*size && (target->definition->kindOf(0x96)||foundWall))return true;
  }
  return false;
 }
 if(target->definition->kindOf(0xB8) && target->rva002957FC())return attacker->rva00263763(target)<5.0;
 FootprintCell targetBase=footprintCell(target,&target->position);
 int targetDiameter=Rva002E9B31Get(target);
 int targetHalf=targetDiameter/-2;targetBase.x+=targetHalf;targetBase.y+=targetHalf;
 int targetHiX=targetBase.x+targetDiameter,targetHiY=targetBase.y+targetDiameter;
 int hiX=base.x+diameter+radius,hiY=base.y+diameter+radius;
 base.x-=radius;int loY=base.y-radius;
 if(base.x<=targetHiX && targetBase.x<=hiX && loY<=targetHiY && targetBase.y<=hiY)return true;
 if(target->definition->kindOf(0x5D)){
  Module *portal=DynamicPortalBehaviour::rva004608E0(target);
  static NameKeyType key=TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
  Module *module=target->findModule(key);
  if(portal && module && ((Rva004C5772CmpBoolField*)module)->get()){
   Coord3D offset;((DynamicPortalBehaviour*)portal)->rva00460CBA(&offset);
   offset.x-=from->x;offset.y-=from->y;offset.z-=from->z;
   if(fabs(offset.z)<20.0f){
    float size=attacker->observedSize;
    size+=((Rva00460C73FloatChase32Field*)portal)->get();
    if(fabs(offset.x)<size && fabs(offset.y)<size)return true;
   }
  }
 }
 return false;
}
