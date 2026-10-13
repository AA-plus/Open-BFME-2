// ?rva001E6B8B@Locomotor@@QAEXPAVObject@@PBUCoord3D@@MM@Z
// partial score=0.99 date=2026-10-13
// ?rva001E6B8B@Locomotor@@QAEXPAVObject@@PBUCoord3D@@MM@Z
// partial score=0.768859 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ob1 /EHsc /ICode/Libraries/Include
// Native1E6B8B..1E6F22 RET16. Locomotor movement variant; original method name
// unknown. ZH locomotor infantry/wheels movement supplies the angle, reverse
// and speed modulation semantics; target offsets and flag decisions are native.
#include "Lib/Coord3D.h"
static __forceinline void CoordSub(Coord3D *p,const Coord3D *v){p->x-=v->x;p->y-=v->y;p->z-=v->z;}
static __forceinline void CoordScale(Coord3D *p,float s){p->x*=s;p->y*=s;p->z*=s;}
extern "C" float atan2f(float,float);
extern "C" double __cdecl fabs(double);
float normalizeAngle(float);
enum ObjectStatusTypes{status26=0x26};
struct Rva0028AC4EEntry {char pad00[4];struct LocoMovementData *data;};
class ModelConditionFlags {public:
 unsigned int test(unsigned int bit)const{return m_words[bit>>5]&(1U<<(bit&0x1f));}
 void clear(unsigned int bit){m_words[bit>>5]&=~(1U<<(bit&0x1f));}
 void set(unsigned int bit){m_words[bit>>5]|=(1U<<(bit&0x1f));}
 unsigned int m_words[19];
};
class Object {public:
 const Coord3D *getPosition()const{return &position;}
 __forceinline void clearModelConditionState(unsigned int mc){if(model.test(mc)!=0){model.clear(mc);rva0028AE6D();}}
 __forceinline void setModelConditionState(unsigned int mc){if(model.test(mc)==0){model.set(mc);rva0028AE6D();}}
 bool rva0006F039(int)const;bool testStatus(ObjectStatusTypes)const;
 const Rva0028AC4EEntry *rva0028AC4E()const;void rva0028AE6D();
 char pad00[0x38];Coord3D position;float orientation;
 char pad48[0x10C-0x48];ModelConditionFlags model;
 char pad158[0x274-0x158];Object *parent274;
};
struct LocoMovementData{
 char pad00[0x64];float value64;
 char pad68[0x74-0x68];int type74;
 char pad78[0xD3-0x78];bool flagD3;
 char padD4[4];int reverseD8;
};
class Rva001E46E1 {public:float rva001E46E1(Object*);float rva001E4845(Object*);};
class Rva001E6007 {public:void rva001e6007(unsigned,unsigned,float,float);};
class Rva001E685F {public:void rva001E685F(int,int,int);};
class Locomotor {public:
 void rva001E6B8B(Object*,const Coord3D*,float,float);
 LocoMovementData *dormantData()const{return data;}
 char pad00[4];LocoMovementData *data;
 char pad08[0x40-8];float speed40;unsigned flags44;
 char pad48[0x98-0x48];bool state98;
};
void Locomotor::rva001E6B8B(Object *obj,const Coord3D *goal,float distance,float desiredSpeed)
{
 if(dormantData()&&!dormantData()){static bool cache=obj->rva0006F039(0x41);(void)cache;}
 if(data->flagD3&&goal->z>obj->position.z)return;
 float maxSpeed=((Rva001E46E1*)this)->rva001E46E1(obj);
 if(desiredSpeed>maxSpeed)desiredSpeed=maxSpeed;
 float actualSpeed=speed40;
 float angle=obj->orientation;
 float desiredAngle=atan2f(goal->y-obj->getPosition()->y,goal->x-obj->getPosition()->x);
 const Coord3D *position=obj->getPosition();
 Coord3D delta;
 delta.x=position->x;delta.y=position->y;delta.z=position->z;
 delta.x-=goal->x;delta.y-=goal->y;delta.z-=goal->z;delta.z=0;
 if(delta.length()<0.1f)desiredAngle=angle;
 float relative=normalizeAngle(desiredAngle-angle);
 delta.x=goal->x;delta.y=goal->y;delta.z=goal->z;
 bool moveBackwards=false;
 if(data->reverseD8&&obj->rva0006F039(0x41))moveBackwards=true;
 if(obj->testStatus(status26)&&obj->parent274&&obj->parent274->rva0028AC4E()&&obj->parent274->rva0028AC4E()->data->reverseD8)moveBackwards=true;
 if(actualSpeed==0.f){
  if(moveBackwards){maxSpeed*=0.5f;flags44&=~0x100U;flags44|=0x80U;}
  else {obj->clearModelConditionState(4*32+28);flags44&=~0x80U;}
  state98=false;
 }
 if(!moveBackwards){
  bool mb=(flags44>>7)&1;if(mb){obj->clearModelConditionState(4*32+28);flags44&=~0x80U;}
 }else {
  flags44|=0x80U;
  obj->setModelConditionState(4*32+28);
  relative=normalizeAngle(normalizeAngle(desiredAngle-3.1415927410125732f)-angle);
  delta=*position;
  CoordScale(&delta,2.f);CoordSub(&delta,goal);
 }
 ((Rva001E685F*)this)->rva001E685F((int)obj,(int)&delta,0);
 if(data->value64>0.f){
  if(((Rva001E46E1*)this)->rva001E4845(obj)>=actualSpeed)relative*=2.f;
  else if(actualSpeed>maxSpeed*0.5f)relative=0.f;
 }
 bool reduceSpeed=true;
 if(data->type74==7||data->type74==4)reduceSpeed=false;
 const float QUARTERPI=0.78539819f;
 float angleCoeff=(float)fabs(relative);angleCoeff/=QUARTERPI;
 if(angleCoeff>0.9f)angleCoeff=0.9f;
 float goalSpeed=desiredSpeed;
 if(!reduceSpeed)goalSpeed=(1.f-angleCoeff)*desiredSpeed;
 if(desiredSpeed>0.f)((Rva001E6007*)this)->rva001e6007((unsigned)obj,(unsigned)goal,distance,goalSpeed);
 else speed40=0.f;
}
