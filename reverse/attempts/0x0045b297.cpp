// ?update@AimWeaponBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.9784 date=2026-10-13
// ?update@AimWeaponBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.976 date=2026-10-13
// Clean BFME1 cee35b7d8 AimWeaponBehaviorUpdate.cpp supplies update purpose
// and MI hierarchy; target ctor45B226, module data45B1DD, pool45B198 and
// tableC41948 independently establish Aim identity and data8/C/10/14.
// Retail45B297..45B49B full516B; secondary this+10, owner-8/data-C,
// flag+10/primary20, Object aim38C/current38/AI258/model-word120.
// Target AI slot111, weapon template flag156, two-byte active|weapon test,
// target bits178/179/180/181/182 and all direct callees established independently.
// Fully resolved516B: final8 SIMD instructions retain distance in XMM1 on
// no-notify edge; retail frees XMM1 for low threshold then reloads distance
// unconditionally after notifier. Typed Words test/set removes LEA/load/store
// (raw array and per-branch templates 518B); direct temporary array references
// remove a6B pointer spill and fix weapon/length/ten stack homes. Copy+sub+
// float-operand/double-return length helper fixes mixed SSE/x87 exactly.
// Real donor return512-masks and attack/idle rules differ, reconciled from
// target; no donor-only layout, globals or unsupported identity claimed.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /I. /ICode/Libraries/Include
#include <math.h>
#include "Lib/Coord3D.h"
enum UpdateSleepTime {UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff};
enum WeaponSlotType {PRIMARY_WEAPON=0};
class Drawable {public:void rva00274176(bool);};
class Thing {public:Drawable*getDrawable()const;};
struct AimWeaponTemplate {char pad[0x156];bool useAimConditions;};
class Weapon {public:bool rva002C9586();char pad[4];AimWeaponTemplate*data;};
class AimAIView {public:
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
virtual void s44();
virtual void s45();
virtual void s46();
virtual void s47();
virtual void s48();
virtual void s49();
virtual void s50();
virtual void s51();
virtual void s52();
virtual void s53();
virtual void s54();
virtual void s55();
virtual void s56();
virtual void s57();
virtual void s58();
virtual void s59();
virtual void s60();
virtual void s61();
virtual void s62();
virtual void s63();
virtual void s64();
virtual void s65();
virtual void s66();
virtual void s67();
virtual void s68();
virtual void s69();
virtual void s70();
virtual void s71();
virtual void s72();
virtual void s73();
virtual void s74();
virtual void s75();
virtual void s76();
virtual void s77();
virtual void s78();
virtual void s79();
virtual void s80();
virtual void s81();
virtual void s82();
virtual void s83();
virtual void s84();
virtual void s85();
virtual void s86();
virtual void s87();
virtual void s88();
virtual void s89();
virtual void s90();
virtual void s91();
virtual void s92();
virtual void s93();
virtual void s94();
virtual void s95();
virtual void s96();
virtual void s97();
virtual void s98();
virtual void s99();
virtual void s100();
virtual void s101();
virtual void s102();
virtual void s103();
virtual void s104();
virtual void s105();
virtual void s106();
virtual void s107();
virtual void s108();
virtual void s109();
virtual void s110();
virtual unsigned char attacking()const;
};
class Rva0028F59A {public:Rva0028F59A(int,int);int words[19];};
class Rva000B6253 {public:Rva000B6253 *rva000B6253(int,unsigned,unsigned,unsigned,unsigned,unsigned);int words[19];};
class Rva001E42F2 {public:void rva001E42F2(const int*);};
class Object {public:
 Weapon *getCurrentWeapon(WeaponSlotType*);
 void rva0028AE6D();void rva0028CFB2(const int*,const int*);
 char pad00[0x38];Coord3D position;char pad44[0x10c-0x44];struct Words {unsigned v[19];__forceinline unsigned test(unsigned mask)const{return v[5]&mask;}__forceinline void set(unsigned mask){v[5]|=mask;}} model;
 char pad158[0x258-0x158];AimAIView*ai;
 char pad25c[0x38c-0x25c];Coord3D aim;
};
class AimWeaponBehaviorModuleData {public:char pad[8];float low,high,nearRange,farRange;};
class Module {public:virtual void anchor();AimWeaponBehaviorModuleData*data;Object*object;};
class BehaviorInterface {public:virtual void other();};
class UpdateInterface {public:virtual UpdateSleepTime update();};
class AimWeaponBehavior:public Module,public BehaviorInterface,public UpdateInterface {public:unsigned frame;int index,reserved;bool aiming;virtual UpdateSleepTime update();};
__forceinline const int *aimFlagWords(const Rva0028F59A &v){return v.words;}
struct AimDelta {
 float x,y,z;
 __forceinline AimDelta(const AimDelta&p):x(p.x),y(p.y),z(p.z){}
 __forceinline void sub(const AimDelta&p){x-=p.x;y-=p.y;z-=p.z;}
 __forceinline double lengthSqr2D()const{return y*y+x*x;}
};
UpdateSleepTime AimWeaponBehavior::update(){
 Object*o=object;
 AimAIView*ai=o->ai;
 Drawable*draw=((const Thing*)o)->getDrawable();
 Weapon*w=o->getCurrentWeapon(0);
 if(!ai || !draw || !w)return UPDATE_SLEEP_FOREVER;
 bool changed=false;
 unsigned char active=ai->attacking();active|=w->rva002C9586();
 if(w->data->useAimConditions && active){
  AimDelta delta(*(const AimDelta*)&o->aim);delta.sub(*(const AimDelta*)&o->position);
  float len=(float)sqrt(delta.lengthSqr2D());
  float ten=10.0f;
  float*chosen=10.0f>len?&ten:&len;
  float denom=*chosen;
  const AimWeaponBehaviorModuleData*md=data;
  float pitch=delta.z/denom;
  unsigned mask;
  if(pitch>md->high)mask=0x40000;
  else if(pitch<md->low)mask=0x100000;
  else mask=0x80000;
  aiming=true;
  if(!(o->model.test(mask))){o->model.set(mask);o->rva0028AE6D();}
  if(denom<md->nearRange){aiming=true;o->rva0028CFB2(static_cast<const Rva0028F59A&>(Rva0028F59A(0,182)).words,static_cast<const Rva0028F59A&>(Rva0028F59A(0,181)).words);}
  else if(denom>md->farRange){aiming=true;o->rva0028CFB2(static_cast<const Rva0028F59A&>(Rva0028F59A(0,181)).words,static_cast<const Rva0028F59A&>(Rva0028F59A(0,182)).words);}
  changed=true;
 }
 if(aiming && !active){
  aiming=false;
  Rva000B6253 flags;
  ((Rva001E42F2*)o)->rva001E42F2(flags.rva000B6253(0,181,182,180,179,178)->words);
  changed=true;
 }
 if(changed)draw->rva00274176(false);
 return UPDATE_SLEEP_NONE;
}
