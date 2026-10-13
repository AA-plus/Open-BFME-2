// ?rva001E7ECA@Locomotor@@QAE_NPAVObject@@PBUCoord3D@@@Z
// partial score=0.9189885324707414 date=2026-10-13
// ?rva001E7ECA@Locomotor@@QAE_NPAVObject@@PBUCoord3D@@@Z
// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// BF1 cee35b7d8 Locomotor.cpp handleBehaviorZ and clean ZH Locomotor.cpp2220
// are the semantic guide. Native1E7ECA..1E84C1 is1527B plus36B jump table;
// nine-case routing independently read:0 ground 1 sea 2/3 dynamic 4/5 fixed
// 6 buildings 7 highest layer 8 future goal; mode9 uses interface slot142.
// Original method spelling remains uncertain; class is known from WB1E46E1.
// Target proves data behavior70 flags44 height48 damping50 matrix68 and
// Object future198/flag1A6 disabled1C8 model118 and flags438.
// Rva1E40D9Get is the owned stdcall view of an unused-this member. The MSVC
// single-inheritance member-pointer adapter keeps the native ECX setup.
// Reuse canonical PartitionRangeQueryCallView; filter64/mask28 lifetimes
// and temporary base-vptr restore are target-observed. Existing FPS owner
// g_Va00DBA4E4 is read in this bank only; no second datum or alias introduced.
// Current1561 versus native1563 including table; frame88 and initial1E7F27
// structure exact; branch scheduling argument homes and FP stores remain.
#include "Coord3D.h"
#include "PartitionRangeQueryCallView.h"
class GameLogic;extern GameLogic *TheGameLogic;
struct LocoFrameView{char pad[0x40];unsigned frame;};
class GlobalData;extern GlobalData*TheWritableGlobalData;
struct LocoGlobalView{char pad[0xc4];float falling;};
extern int g_Va00DBA4E4;
enum KindOfType{KINDOF_9A=0x9a};enum PathfindLayerEnum{GROUND=1};
struct LocoDefinition{char pad[0x70];int behavior;};
struct LocoObjectTemplate{char pad[0x11f];unsigned char flags11f;};
class Rva00373EC6;
class Object{public:
 bool isKindOf(KindOfType)const;int rva0028B511()const;void*rva0029439D();Rva00373EC6*rva0028F4BC();void rva0028AE6D();
 void *vptr;LocoObjectTemplate *definition;char pad8[0x38-8];Coord3D pos;char pad44[0x118-0x44];unsigned char model118;char pad119[0x198-0x119];Coord3D future;char pad1a4[2];bool futureFlag;char pad1a7[0x1c8-0x1a7];unsigned char disabled;char pad1c9[0x438-0x1c9];unsigned char flags438;
};
template<int N>class LocoSlots:public LocoSlots<N-1>{public:virtual void gap(char(*)[N]);};template<>class LocoSlots<0>{};
class LocoInterface:public LocoSlots<142>{public:virtual bool permits();};
struct Rva001E41D3Result {float x,y,z;};
class Rva001E41D3 {public:Rva001E41D3Result rva001E41D3();};
class Rva001E434A {public:void*rva001E434A();};
class Rva0028E8D4 {public:void rva0028E8D4(float*)const;};
class Rva001E46E1 {public:float rva001E46E1(Object*);bool rva001E5F1D(Object*,const Coord3D*,float*);};
float __stdcall Rva001E40D9Get(float,float);
bool Rva001E3679(int);
class GeometryInfo{public:float getMaxHeightAbovePosition()const;};
class StealthUpdate{public:void markAsDetected(unsigned,int,Object*,bool);};
struct LocoStealthView{char pad[0x3c];int active;};
class TerrainLogic{public:PathfindLayerEnum getHighestLayerForDestination(const Coord3D*,bool);};extern TerrainLogic*TheTerrainLogic;
class LocoTerrainView:public LocoSlots<6>{public:
 virtual float ground(float,float,Coord3D*);
 virtual float layer(float,float,int,Coord3D*,bool);
 virtual void gap8();virtual void gap9();virtual void gap10();virtual void gap11();virtual void gap12();virtual void gap13();virtual void gap14();virtual void gap15();virtual void gap16();virtual void gap17();virtual void gap18();
 virtual bool underwater(float,float,float*,float*,unsigned char*);
};
class BfmeFixedStorage0004543D{public:BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D&)throw();unsigned bits[7];};
template<int N>class BitFlags{public:unsigned bits[7];};extern BitFlags<116>KINDOFMASK_NONE;
class Rva00045411BitSet{public:Rva00045411BitSet(int,int);unsigned bits[7];};
class Rva000421C8{public:Rva000421C8():next(0){}virtual ~Rva000421C8(){}virtual bool allow(Object*)=0;virtual int getPlayerMask(){return -1;}Rva000421C8*next;};
class Rva0004584D:public Rva000421C8{public:Rva0004584D(const BfmeFixedStorage0004543D&,const BfmeFixedStorage0004543D&);virtual ~Rva0004584D(){}virtual bool allow(Object*);BfmeFixedStorage0004543D required,excluded;};
extern PartitionManager*ThePartitionManager;
struct LocoMatrix{float values[12];void set(const Rva001E41D3Result&p){values[3]=p.x;values[7]=p.y;values[11]=p.z;}};
class Locomotor {public:
 bool rva001E7ECA(Object*,const Coord3D*);float rva001E6532(Object*,const Coord3D*,float);
 __forceinline float surfaceAt(float x,float y){typedef float(Locomotor::*Member)(float,float);union Convert{float(__stdcall*fn)(float,float);Member member;}c;c.fn=Rva001E40D9Get;return(this->*c.member)(x,y);}
 void setTranslation(const Rva001E41D3Result&p){((LocoMatrix*)matrix)->set(p);}
 void*vptr;LocoDefinition*data;char pad8[0x40-8];float speed40;unsigned flags44;float height48,min4c,damping50;char pad54[0x68-0x54];float matrix[12];
};
bool Locomotor::rva001E7ECA(Object*object,const Coord3D*goal){
 volatile bool requires=true;int mode=data->behavior;
 if(mode==9){LocoInterface*iface=(LocoInterface*)object->rva0029439D();if(!iface||!iface->permits())mode=0;}
 Rva001E41D3Result pos=((Rva001E41D3*)this)->rva001E41D3();union ScratchPoint {Coord3D normal;Coord3D future;};ScratchPoint work;
 switch(mode){
 case 8:{pos.z=goal->z;object->futureFlag=true;*(Rva001E41D3Result*)&object->future=pos;float surface=0;((Rva001E46E1*)this)->rva001E5F1D(object,(const Coord3D*)&pos,&surface);return false;}
 case 0:{
  if((object->disabled&8)||object->isKindOf(KINDOF_9A))break;
  float surface=0;int layer=object->rva0028B511();
  if(!((Rva001E46E1*)this)->rva001E5F1D(object,(const Coord3D*)&pos,&surface)){
   surface=((LocoTerrainView*)TheTerrainLogic)->layer(pos.x,pos.y,layer,0,true);
   if(((LocoFrameView*)TheGameLogic)->frame>(unsigned)g_Va00DBA4E4 && (layer==16||Rva001E3679(layer)) && pos.z-surface>20.0f)surface=pos.z;
  }
  pos.z=surface;setTranslation(pos);requires=false;break;
 }
 case 1:{requires=false;if(object->disabled&8)break;
  float water;if(((LocoTerrainView*)TheTerrainLogic)->underwater(pos.x,pos.y,&water,0,0))pos.z=water;
  else pos.z=((LocoTerrainView*)TheTerrainLogic)->layer(pos.x,pos.y,object->rva0028B511(),0,true);
  if(object->definition->flags11f&8){float speed=speed40;pos.z+=(speed/(((Rva001E46E1*)this)->rva001E46E1(object)+0.1f)+1.0f)*height48;}
  else pos.z+=height48;
  setTranslation(pos);break;
 }
 case 4:case 5:{requires=true;volatile bool relative=data->behavior==4;float surface=relative?surfaceAt(pos.x,pos.y):0.0f;pos.z=height48+(relative?surface:0.0f);setTranslation(pos);break;}
 case 6:{requires=true;pos.z=((LocoTerrainView*)TheTerrainLogic)->ground(pos.x,pos.y,0);float highest=0.0f;
  BfmeWideResult result=ThePartitionManager->iterateObjectsInRange((const Coord3D*)&pos,1.0f,1,&Rva0004584D(*(const BfmeFixedStorage0004543D*)&Rva00045411BitSet(0,7),*(const BfmeFixedStorage0004543D*)&KINDOFMASK_NONE),0);
  Object*entry;while((entry=result.next())!=0){float h=((GeometryInfo*)((char*)entry+0xa8))->getMaxHeightAbovePosition();if(h>highest)highest=h;}
  pos.z=height48+highest;setTranslation(pos);break;
 }
 case 7:{requires=true;if(height48!=0.0f || (bool)((flags44>>3)&1)){
  int layer=object->rva0028B511();if(layer==1)layer=TheTerrainLogic->getHighestLayerForDestination((const Coord3D*)&pos,0);
  Coord3D &normal=work.normal;float preferred=((LocoTerrainView*)TheTerrainLogic)->layer(pos.x,pos.y,layer,&normal,false)+height48;
  if((bool)((flags44>>3)&1))preferred=goal->z;
  float delta=((pos.z+(preferred-pos.z)*damping50)-pos.z)/((float)g_Va00DBA4E4*2.0f);
  if(delta!=0.0f){pos.z+=delta;setTranslation(pos);}
 }break;}
 case 2:case 3:{requires=true;if(height48!=0.0f || (bool)((flags44>>3)&1)){
  float surface=data->behavior==2?surfaceAt(pos.x,pos.y):0.0f;
  float preferred=rva001E6532(object,goal,surface)+surface;
  if((bool)((flags44>>3)&1))preferred=goal->z;
  float delta;if(object->flags438&1)delta=((LocoGlobalView*)TheWritableGlobalData)->falling;
  else delta=((pos.z+(preferred-pos.z)*damping50)-pos.z)/((float)g_Va00DBA4E4*2.0f);
  if(delta!=0.0f){pos.z+=delta;setTranslation(pos);}
  if(delta>0.5f){if(!(object->model118&0x80)){object->model118|=0x80;object->rva0028AE6D();}
   Rva00373EC6*stealth=object->rva0028F4BC();if(stealth && ((LocoStealthView*)stealth)->active)((StealthUpdate*)stealth)->markAsDetected(0,1,0,true);
  }else if(object->model118&0x80){object->model118&=0x7f;object->rva0028AE6D();}
 }break;}
 }
 const Coord3D*anchor=(const Coord3D*)((Rva001E434A*)object)->rva001E434A();Coord3D &future=work.future;
 future.x=anchor->x;future.y=anchor->y;Coord3D current;((Rva0028E8D4*)object)->rva0028E8D4((float*)&current);
 future.z=pos.z*2.0f-current.z;object->futureFlag=true;object->future=future;return requires;
}
