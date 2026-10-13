// ?rva00530212@Pathfinder@@QAEXPAVObject@@_N11@Z
// partial score=0.8620093232384183 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /I.
// Native 00530212..00530F47, RET16, 3381B. UNMATCHED reconstruction.
// 2026-10-13: full emitted body is 3380B; frame 0x164 versus retail 0x168.
// Reference-derived fixes: CRT float floorf/ceilf wrappers and long fistp
// conversion, -(c*STEP), ordered radius comparison, donor sphere locals.
// Target-derived fixes: removal tests type before layer; pinching checks the
// current layer once and counts neighboring clear types regardless of layer.
// Object::isMobile now uses the existing canonical owner at 0x002907A1.
// Residue: position copy folds +0x38 into its loads; box-cell CSE spills the
// receiver instead of the type; bounding-region call has different registers;
// stack homes differ. No proven original BFME2 member name: retain RVA name.
// Diagnostic-only call bindings: Drawable::rva0027A018 -> 0x0027A018,
// Pathfinder::rva0052E4C9 -> 0x0052E4C9 and rva0052F63F -> 0x0052F63F.
// They are not admitted pins. Official permute.fitness with those bindings:
// 0.8620093232384183; exact verification FAILS. Do not promote from length alone.
// Reviewed donor cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Upstream 24656f4d
// changes no relevant footprint body, ZH source, or VS2003 toolchain inputs.
// ZH AIPathfind.cpp classifyObjectFootprint/internal_classifyObjectFootprint
// provide the filtering/rasterization/pinching semantics. BFME-specific wall,
// portal, multi-shape, gate and layer checks are read from target bytes and WB.
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include <math.h>
#include "Code/Libraries/Include/Lib/ICoord2D.h"
struct FootprintCoord2D{float x,y;};
struct Region2D { float lx,ly,hx,hy; };
struct FootprintBounds{int lx,ly,hx,hy;};
class Rva0027C36A {public:Rva0027C36A();unsigned words[0xa8/4];};
class Drawable {public:
 bool rva0027267D(int,int,int,int);bool rva002726C3(int,int,int,int);
 int rva0027257B(int);bool rva00272C1E();void rva0027A018();
};
class Rva00279677{public:void rva00279677();};
struct BfmeVecVNB{float x,y,z; BfmeVecVNB(const float *v):x(v[0]),y(v[1]),z(v[2]){} };
class BfmeXformVNB{public:void bfmeApplyVNB(BfmeVecVNB*,float);};
struct BfmeShapeE15 {int type;int field4;float major,minor,offsetX,offsetY,offsetZ;bool flag1C;char pad1D[3];bool enabled;char pad21[3];};
class BfmeObjE15{public:BfmeShapeE15 *bfmeAtE15(int);};
class Rva0087E370{public:void method(const Coord3D&,float,Region2D&)const;};
struct FootprintTemplate {char pad[0x108];union {unsigned kinds[6];struct {unsigned kind0;unsigned pad1:28;unsigned isWall:1;unsigned isDefense:1;unsigned pad2:2;unsigned rest[4];};};unsigned words120;char pad124[0x4a0-0x124];float fenceWidth;__forceinline unsigned kind(int b)const{return kinds[b/32]&(1u<<(b%32));}};
enum ObjectStatusTypes{Status77=77,Status88=88};
class Object {public:
 Drawable *getDrawable()const;void rva0028AD32();void rva0028AD8C();void rva0028AD7C();bool isMobile()const;bool testStatus(ObjectStatusTypes)const;bool rva0006F039(int)const;
 char pad0[4];FootprintTemplate *templ;char pad8[0x38-8];Coord3D position;float orientation;char pad48[0xac-0x48];bool small;char padAD[0xd4-0xad];BfmeShapeE15 *begin,*end;
};
class Thing{public:float getHeightAboveTerrain()const;};
struct Rva0052DEEFArg;struct Rva0052DFB1Arg;struct In002E6BA1{int x,y;};
class PathfindCell {public:
 bool SetType_Dirty(int);bool rva0052DEEF(const Rva0052DEEFArg*,bool,In002E6BA1*);bool rva0052DFB1(const Rva0052DFB1Arg*);
 enum CellType{Clear=0,Water=1,Cliff=2,Reserved=3,Obstacle=4,Impassable=5}; __forceinline int type()const{return m_type;}__forceinline int layer()const{return m_layer;}__forceinline bool pinched()const{return m_pinched;}__forceinline void pinch(bool b){m_pinched=b;}
 __forceinline bool gate()const{return m_gate;}
 char pad[12];unsigned m_type:4;unsigned m_layer:6;unsigned m_low:6;unsigned m_pinched:1;unsigned m_gate:1;unsigned m_mid:4;unsigned m_22:1;unsigned m_23:1;unsigned m_high:8;
};
class Rva0052E001{public:bool rva0052E001(bool);};
class Rva0052E02F{public:bool rva0052E02F(bool);};
class PathfindZoneManager{public:void MarkDirty(int,int);};
extern "C" __declspec(dllimport)double __cdecl floor(double);
extern "C" __declspec(dllimport)double __cdecl ceil(double);
float Sin(float);float Cos(float);
static __forceinline long float2long(float f){long i;__asm{
 fld f
 fistp i
}return i;}
#define FLOOR(x) float2long(floorf(x))
#define CEIL(x) float2long(ceilf(x))
enum PathfindLayerEnum{LayerGround=1};
class Pathfinder{public:
 void rva00530212(Object*,bool,bool,bool);void rva0052F63F(Object*,bool);void rva0052E4C9(Object*,bool);PathfindCell *getCell(PathfindLayerEnum,int,int);
 char pad0[0x10];PathfindCell**map;FootprintBounds extent;char pad24[0x460-0x24];PathfindZoneManager zones;char pad461[0x1beb4-0x461];bool changedWall,changedGate;
};
void Pathfinder::rva00530212(Object*obj,bool insert,bool keepGate,bool goal)
{
 Drawable *drawable=obj->getDrawable();
 if(drawable){if(insert)drawable->rva0027A018();else ((Rva00279677*)drawable)->rva00279677();}
 if(obj->templ->kind(25)||obj->templ->kind(24)||obj->templ->kind(149))return;
 bool wall=obj->templ->isWall;
 if(!wall && obj->templ->fenceWidth>0.0f && !obj->templ->kind(61)){rva0052E4C9(obj,insert);return;}
 if(!insert){obj->rva0028AD32();if(!goal)obj->rva0028AD8C();}else obj->rva0028AD7C();
 if(!obj->templ->kind(7)||obj->isMobile()||obj->small||obj->testStatus(Status88))return;
 if(wall){if(obj->templ->kind(150))wall=obj->getDrawable()->rva00272C1E();else if(obj->testStatus(Status77))wall=false;}
 if(((Thing*)obj)->getHeightAboveTerrain()>10.0f&&!wall)return;
 if(wall&&drawable){float z;if(!drawable->rva0027257B((int)&z)){changedWall=true;rva0052F63F(obj,insert);return;}}
 bool gate=obj->templ->kind(137)||wall;
 bool bit22=insert ? ((obj->templ->words120>>9)&1)!=0:false;
 if((gate||bit22)&&!insert)changedGate=true;
 if(insert&&obj->templ->kind(120)&&obj->rva0006F039(94)){
  int x=(int)(obj->position.x*0.1f),y=(int)(obj->position.y*0.1f);
  for(int i=-60;i<=60;++i)for(int j=-60;j<=60;++j){PathfindCell*cell=getCell(LayerGround,x+i,y+j);if(cell&&cell->gate()){((Rva0052E001*)cell)->rva0052E001(false);zones.MarkDirty(x+i,y+j);}}
 }
 Rva0027C36A data;
 if(drawable){void*poly;if(drawable->rva0027267D((int)&data,(int)&poly,0,0)||drawable->rva002726C3((int)&data,(int)&poly,0,0))gate=true;}
 float angle=obj->orientation;
 for(int k=0;k<obj->end-obj->begin;++k){
  BfmeShapeE15 *shape=((BfmeObjE15*)((char*)obj+0xa8))->bfmeAtE15(k);
  if(!shape->enabled||shape->offsetZ>10.0f)continue;
  BfmeVecVNB pos(&obj->position.x);
  float c=Cos(angle),s=Sin(angle);
  ((BfmeXformVNB*)shape)->bfmeApplyVNB(&pos,angle);
  switch(shape->type){
  case 2:{
   float halfX=shape->major,halfY=shape->minor;
   float ydx=s*5.0f,ydy=-(c*5.0f),xdx=c*5.0f,xdy=s*5.0f;
   int nx=CEIL(2.0f*halfX/5.0f),ny=CEIL(2.0f*halfY/5.0f);
   float tlx=pos.x-halfX*c-halfY*s,tly=pos.y+halfY*c-halfX*s;
   for(int iy=0;iy<ny;++iy,tlx+=ydx,tly+=ydy){
    float x=tlx,y=tly;
    for(int ix=0;ix<nx;++ix,x+=xdx,y+=xdy){
     int cx=FLOOR((x+0.5f)*0.1f),cy=FLOOR((y+0.5f)*0.1f);
     if(cx<0||cy<0||cx>=extent.hx||cy>=extent.hy)continue;
     bool accept=false;
     if(map[cx][cy].layer()!=1){
      if(!gate)continue;
      int ty=map[cx][cy].type();
      if((ty==0||ty==3)&&insert)accept=true;
      if((ty==4||ty==3)&&!insert)accept=true;
      if(!accept)continue;
     }
     bool dirty;
     if(insert){
      if(gate){int ty=map[cx][cy].type();if(ty==2||ty==3){map[cx][cy].SetType_Dirty(0);zones.MarkDirty(cx,cy);}}
      In002E6BA1 p={cx,cy};dirty=map[cx][cy].rva0052DEEF((const Rva0052DEEFArg*)obj,false,&p);
     }else dirty=map[cx][cy].rva0052DFB1((const Rva0052DFB1Arg*)obj);
     if(dirty)zones.MarkDirty(cx,cy);
     if(gate&&!keepGate&&map[cx][cy].gate()!=insert){((Rva0052E001*)&map[cx][cy])->rva0052E001(insert);zones.MarkDirty(cx,cy);}
     if(((Rva0052E02F*)&map[cx][cy])->rva0052E02F(bit22))zones.MarkDirty(cx,cy);
    }
   }
  }break;
  case 0:case 1:{
   ICoord2D topLeft,bottomRight;
   FootprintCoord2D center,delta;
   float radius=shape->major;
   float r2,size;
   topLeft.x=FLOOR((pos.x-radius)*0.1f+0.5f)-1;
   topLeft.y=FLOOR((pos.y-radius)*0.1f+0.5f)-1;
   size=radius*0.1f;center.x=pos.x*0.1f;center.y=pos.y*0.1f;
   size+=0.4f;r2=size*size;
   bottomRight.x=(int)(topLeft.x+2*size+2);bottomRight.y=(int)(topLeft.y+2*size+2);
   for(int j=topLeft.y;j<bottomRight.y;++j)for(int i=topLeft.x;i<bottomRight.x;++i){
    delta.x=i+0.5f-center.x;delta.y=j+0.5f-center.y;
    if(!(delta.x*delta.x+delta.y*delta.y<=r2)||i<0||j<0||i>=extent.hx||j>=extent.hy||map[i][j].layer()!=1)continue;
    bool dirty;
    if(insert){In002E6BA1 p={i,j};dirty=map[i][j].rva0052DEEF((const Rva0052DEEFArg*)obj,false,&p);}
    else dirty=map[i][j].rva0052DFB1((const Rva0052DFB1Arg*)obj);
    if(dirty)zones.MarkDirty(i,j);
    if(gate&&map[i][j].gate()!=insert){((Rva0052E001*)&map[i][j])->rva0052E001(insert);zones.MarkDirty(i,j);}
    if(((Rva0052E02F*)&map[i][j])->rva0052E02F(bit22))zones.MarkDirty(i,j);
   }
  }break;
  }
 }
 Region2D world;
 ((Rva0087E370*)((char*)obj+0xa8))->method(obj->position,obj->orientation,world);
 FootprintBounds b; b.lx=FLOOR(world.lx*0.1f)-1; b.ly=FLOOR(world.ly*0.1f)-1; b.hx=CEIL(world.hx*0.1f)+1; b.hy=CEIL(world.hy*0.1f)+1;
 if(b.lx<extent.lx)b.lx=extent.lx;
 if(b.ly<extent.ly)b.ly=extent.ly;
 if(b.ly<extent.ly)b.ly=extent.ly;
 if(b.hx>extent.hx)b.hx=extent.hx;
 if(b.hy>extent.hy)b.hy=extent.hy;
 if(!insert)for(int j=b.ly;j<=b.hy;++j)for(int i=b.lx;i<=b.hx;++i){
  if(map[i][j].type()==5&&map[i][j].layer()==1){map[i][j].SetType_Dirty(0);zones.MarkDirty(i,j);}
 }
 for(int j=b.ly;j<=b.hy;++j)for(int i=b.lx;i<=b.hx;++i){
  if(map[i][j].layer()!=1)continue;
  map[i][j].pinch(false);
  if(map[i][j].type()==0){
   int total=0,ortho=0;
   for(int k=i-1;k<i+2;++k){if(k<extent.lx||k>extent.hx)continue;
    for(int l=j-1;l<j+2;++l){if(l<extent.ly||l>extent.hy)continue;
     if(k==i&&j==l)continue;
     if(map[k][l].type()==0){++total;if(k==i||l==j)++ortho;}
    }
   }
   if(ortho<2||total<4)map[i][j].pinch(true);
  }
 }
 for(int j=b.ly;j<=b.hy;++j)for(int i=b.lx;i<=b.hx;++i){
  if(map[i][j].layer()==1&&map[i][j].pinched()&&map[i][j].type()==0){map[i][j].SetType_Dirty(5);map[i][j].pinch(false);zones.MarkDirty(i,j);}
 }
 for(int j=b.ly;j<=b.hy;++j)for(int i=b.lx;i<=b.hx;++i){
  if(map[i][j].layer()==1&&map[i][j].type()==0){
   bool adjacent=false;
   for(int k=i-1;k<i+2;++k){if(k<extent.lx||k>extent.hx)continue;
    for(int l=j-1;l<j+2;++l){if(l<extent.ly||l>extent.hy)continue;
     if(k==i&&l==j)continue;if(k!=i&&l!=j)continue;
     if(map[k][l].type()==4){adjacent=true;break;}
    }
   }
   if(adjacent)map[i][j].pinch(true);
  }
 }
 if(wall&&drawable){float z;if(drawable->rva0027257B((int)&z))rva0052F63F(obj,insert);}
}
